cmake_minimum_required(VERSION 3.31.6)
project(electric_guitar_builder_vst VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The render inner loop is written for SIMD (4-lane, branch-free). Enable
# x86-64-v2 (SSE4.1, 2009+) when the compiler supports it; everything still
# compiles and runs correctly without it.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=x86-64-v2" EGB_HAS_X86_64_V2)
if(EGB_HAS_X86_64_V2)
  add_compile_options(-march=x86-64-v2)
endif()
# The modal accumulation pass has an 8-oscillator (2x 4-double) SIMD path
# gated on __AVX2__. Lane arithmetic is per-oscillator and identical across
# lane widths, so renders stay bit-identical (T-010).
check_cxx_compiler_flag("-mavx2" EGB_HAS_AVX2)
if(EGB_HAS_AVX2)
  # -ffp-contract=off: the SSE2 build has no FMA, so contraction must stay
  # disabled to keep renders bit-identical to the recorded reference values.
  add_compile_options(-mavx2 -ffp-contract=off)
endif()
# An 8-double (AVX-512) modal path was measured here and rejected: on the
# AVX-512 build host the 16-oscillator inner loop is SLOWER under ASan/UBSan
# than the 4-double AVX2 path (73 s vs 62 s ASan; 104 s vs 86 s UBSan per
# T-017 run) — the scalar extract/store traffic and licensing throttling eat
# the wider lanes' gain. The VEC8 branch in engine.cpp stays available but is
# compiled only when __AVX512F__ is defined, which no build flag enables.

get_filename_component(EGB_JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../egb-juce" ABSOLUTE CACHE)
if (NOT EXISTS "${EGB_JUCE_DIR}/modules/juce_core/juce_core.cpp")
  get_filename_component(EGB_JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/JUCE" ABSOLUTE)
endif()

# Minimal JUCE module set, compiled directly (no juceaide/helper tools, so the
# build works on non-executable mounts and minimal hosts). The full JUCE
# add_subdirectory path with the VST3 target is used on desktop CI; see
# cmake/Desktop.cmake.
add_library(egb_juce STATIC
  ${EGB_JUCE_DIR}/modules/juce_core/juce_core_CompilationTime.cpp
  ${EGB_JUCE_DIR}/modules/juce_core/juce_core.cpp
  ${EGB_JUCE_DIR}/modules/juce_events/juce_events.cpp
  ${EGB_JUCE_DIR}/modules/juce_audio_basics/juce_audio_basics.cpp)
target_include_directories(egb_juce PUBLIC ${EGB_JUCE_DIR}/modules)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/egb_AppConfig.h
"#pragma once\n"
"#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1\n"
"#define JUCE_MODULE_AVAILABLE_juce_core 1\n"
"#define JUCE_MODULE_AVAILABLE_juce_events 1\n"
"#define JUCE_MODULE_AVAILABLE_juce_audio_basics 1\n")
target_compile_options(egb_juce PUBLIC -include ${CMAKE_CURRENT_BINARY_DIR}/egb_AppConfig.h)
target_compile_definitions(egb_juce PUBLIC
  JUCE_GLOBAL_MODULE_SETTINGS=1
  JUCE_STANDALONE_APPLICATION=0
  JUCE_USE_CURL=0
  JUCE_WEB_BROWSER=0
  JUCE_WASAPI=0
  JUCE_DIRECTSOUND=0
  JUCE_ALSA=0
  JUCE_JACK=0
  JUCE_USE_XRANDR=0
  JUCE_USE_XINERAMA=0
  JUCE_USE_XCURSOR=0
  JUCE_USE_XCOMPOSITE=0
  JUCE_USE_XSHM=0
  JUCE_DISPLAY_SPLASH_SCREEN=0
  JUCE_REPORT_APP_USAGE=0
  JUCE_MODAL_LOOPS_PERMITTED=1)
if(APPLE)
  # JUCE module headers pull in Cocoa/Foundation on macOS, so every TU that
  # includes them must compile as Objective-C++.
  set_source_files_properties(
    ${EGB_JUCE_DIR}/modules/juce_core/juce_core_CompilationTime.cpp
    ${EGB_JUCE_DIR}/modules/juce_core/juce_core.cpp
    ${EGB_JUCE_DIR}/modules/juce_events/juce_events.cpp
    src/engine.cpp src/plugin_processor.cpp src/contract_main.cpp
    PROPERTIES LANGUAGE OBJCXX)
  target_link_libraries(egb_juce PUBLIC
    "-framework Cocoa" "-framework Carbon" "-framework IOKit"
    "-framework CoreServices" "-framework Security"
    "-framework SystemConfiguration" pthread)
else()
  target_link_libraries(egb_juce PUBLIC pthread dl rt)
endif()

add_library(egb_core STATIC src/engine.cpp src/plugin_processor.cpp)
target_include_directories(egb_core PUBLIC include)
target_link_libraries(egb_core PUBLIC egb_juce)

add_executable(egb_contract src/contract_main.cpp)
string(SHA256 EGB_LOCK_SHA256 "${CMAKE_CURRENT_SOURCE_DIR}/requirements-lock.txt")
execute_process(COMMAND git rev-parse HEAD WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE EGB_COMMIT OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
target_compile_definitions(egb_contract PRIVATE
  EGB_REPO_ROOT="${CMAKE_CURRENT_SOURCE_DIR}"
  EGB_COMMIT="${EGB_COMMIT}"
  EGB_LOCK_SHA256="${EGB_LOCK_SHA256}")
target_link_libraries(egb_contract PRIVATE egb_core)
