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
