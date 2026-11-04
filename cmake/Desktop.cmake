# Desktop/CI build: full JUCE add_subdirectory path with the VST3 target.
# The default CMakeLists.txt builds the minimal-modules static target (for
# non-executable mounts and minimal hosts); this file is included by desktop
# CI to produce the real VST3 plug-in via juce_add_plugin.
#
# Usage (desktop CI only):
#   cmake -B build -DEGB_DESKTOP=ON
# or
#   cmake -B build -C cmake/Desktop.cmake

set(EGB_DESKTOP ON CACHE BOOL "Full JUCE desktop build with VST3 target")

if (NOT DEFINED EGB_JUCE_DIR OR NOT EXISTS "${EGB_JUCE_DIR}/CMakeLists.txt")
  # JUCE is pinned as a gitlink submodule at third_party/JUCE (see .gitmodules
  # and DEVIATIONS.md D-1). Fetch it on normal (executable) filesystems.
  find_package(Git REQUIRED)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init third_party/JUCE
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  set(EGB_JUCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/JUCE)
endif()

add_subdirectory(${EGB_JUCE_DIR} JUCE)

juce_add_plugin(egb_vst3
  COMPANY_NAME "qualitycoding"
  PLUGIN_MANUFACTURER_CODE EgbQ
  PLUGIN_CODE Egb1
  FORMATS VST3
  PRODUCT_NAME "Electric Guitar Builder"
  IS_SYNTH TRUE
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT FALSE)

target_sources(egb_vst3 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin_processor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp)

target_include_directories(egb_vst3 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(egb_vst3 PRIVATE
  JUCE_VST3_CAN_REPLACE_VST2=0
  EGB_COMMIT="${EGB_COMMIT}")

# The headless contract renderer stays available on desktop builds too.
add_executable(egb_contract_desktop
  ${CMAKE_CURRENT_SOURCE_DIR}/src/contract_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp)
target_include_directories(egb_contract_desktop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
