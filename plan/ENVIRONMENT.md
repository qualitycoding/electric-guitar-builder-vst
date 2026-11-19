# Environment and CI contract

## Pins

- C++20; CMake 3.31.6; Ninja 1.11.1.4; Python 3.12.
- JUCE 8.0.15 at commit `91ad83ae34a81e0833b1a2b0866f54846370ae53`, fetched only in S-001 as a Git submodule/shallow pinned checkout; AGPLv3 open-source licensing path.
- Research packages are exactly `requirements-lock.txt`; its SHA-256 is recorded in render metadata.
- pluginval 1.0.4 for VST3 host validation; OSV-Scanner v2.2.4 for dependency scanning. If a pinned download is unavailable or its published checksum cannot be verified, S-000 blocks rather than substituting silently.

## Verified planning setup

From the repository root:
```sh
python -m pip install --target .tools -r requirements-lock.txt
PYTHONPATH=.tools python -c "import cmake,numpy,scipy,soundfile,mido; print('imports ok')"
mkdir -p /tmp/egb-tools/bin
cp .tools/cmake/data/bin/cmake /tmp/egb-tools/bin/cmake
cp .tools/bin/ninja /tmp/egb-tools/bin/ninja
cp -R .tools/cmake/data/share /tmp/egb-tools/share
chmod 755 /tmp/egb-tools/bin/cmake /tmp/egb-tools/bin/ninja
/tmp/egb-tools/bin/cmake --version
/tmp/egb-tools/bin/ninja --version
```
The durable repository mount does not support execution. Re-stage at each turn start; after a native build, copy `build/egb_contract` to `/tmp/egb-tools/bin/egb_contract`, chmod it, and set `EGB_CONTRACT_BIN` there. On normal workstations execute `build/egb_contract` directly and omit staging.

## Frozen suite

```sh
/tmp/egb-tools/bin/cmake -S . -B build -G Ninja -DCMAKE_MAKE_PROGRAM=/tmp/egb-tools/bin/ninja
/tmp/egb-tools/bin/cmake --build build
EGB_CONTRACT_BIN=/tmp/egb-tools/bin/egb_contract python -m unittest discover -s tests -v
sha256sum -c tests/FROZEN_MANIFEST.sha256
```
All 30 cases must pass after implementation. `tests/RED_VERIFICATION.txt` records the expected planning-time red state and is not a production result.

## CI matrix

| Job | Runner/container | Scope |
|---|---|---|
| linux-x64 | `ubuntu-24.04` | VST3, renderer, all tests, sanitizers, pluginval, scans |
| windows-x64 | `windows-2025` | VST3, renderer, portable suite |
| macos-arm64 | `macos-15` | VST3, renderer, portable suite |
| linux-arm64 | `ubuntu-24.04-arm` | engine/renderer portable suite |
| alpine-x64 | `ubuntu-24.04` + `alpine:3.22` | engine/renderer libc-variant suite |
| oldest-toolchain | `ubuntu-24.04` | C++20/CMake 3.31.6/JUCE pinned lower bound |

Every matrix has `fail-fast: false`; print runner image, compiler and tool versions. No `-latest`, release, signing, notarisation or system plug-in installation. Performance budgets: on 2-core Linux x64, 16 voices at 48 kHz/128 samples must render 60 seconds in ≤48 seconds median of three; macOS ARM64 ≤48 seconds; Windows x64 ≤48 seconds. >10% spread triggers one rerun; persistent miss follows D-012. Budgets are per CI runner class and fail T-017.

## Amendment 03 — verified commands (planning run 20261111T150746Z, stable Claude cloud environment)

Pins unchanged (C++20, CMake 3.31.6, Ninja 1.11.1.4, Python 3.12, JUCE `91ad83ae34a81e0833b1a2b0866f54846370ae53`, numpy 2.5.4/scipy as `requirements-lock.txt`). Each command below was executed during planning; outputs are in `research/spikes/` or `tests/RED_VERIFICATION_A03.txt` (1.3.6 (a)). Paths outside the repository are examples; any directory outside the working tree works.

```sh
# toolchain (verified: cmake --version -> 3.31.6)
python3 -m venv ../egb-venv && ../egb-venv/bin/pip install cmake==3.31.6 ninja==1.11.1.4
export PATH="$PWD/../egb-venv/bin:$PATH"
# JUCE at the pinned commit (verified: HTTP 200, 22,896,965 bytes, extracts to JUCE-91ad83ae...)
mkdir -p ../juce-cache && curl -sL -o ../juce-cache/juce.tgz https://codeload.github.com/juce-framework/JUCE/tar.gz/91ad83ae34a81e0833b1a2b0866f54846370ae53 && tar -C ../juce-cache -xzf ../juce-cache/juce.tgz
# configure and build (verified: 36 s on 4 cores)
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DEGB_JUCE_DIR="$PWD/../juce-cache/JUCE-91ad83ae34a81e0833b1a2b0866f54846370ae53"
cmake --build build --target egb_contract -j4
# suites (verified: v1+amendment 39/39 OK in 138 s with the reference cache absent; physics 10 red by design at planning)
EGB_CONTRACT_BIN=$PWD/build/egb_contract python3 -m unittest discover -s tests -v
sha256sum -c tests/FROZEN_MANIFEST.sha256
# oracle (verified: reproduces physics_expected.json byte for byte)
python3 -m venv ../oracle-venv && ../oracle-venv/bin/pip install -r requirements-lock.txt
../oracle-venv/bin/python research/spikes/physics_oracle.py
```

With the licensed reference cache absent, T-023, T-024 and T-027 report SKIP and pass (D-17); `G-LISTEN-2` evidence needs the cache (S-LISTEN-2 step 1). The planning sandbox is classified `stable` (`.checkpoints/state.json`), so the `[ephemeral]` restaging of v1 is not required for this amendment; it remains valid on recycling platforms.
