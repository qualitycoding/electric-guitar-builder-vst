# Execution log

Format: UTC | step | attempt | result | commit | note

- 2026-11-04T03:00:00Z | S-000 | 1 | pass | (pending) | branch impl-20261104T030000Z created; Python 3.12.12; cmake 3.31.6; ninja 1.11.1 restaged to /tmp/egb-tools/bin; imports ok; push auth via GIT_ASKPASS helper (token never on command line); JUCE pin 91ad83ae34a81e0833b1a2b0866f54846370ae53 verified present upstream; pluginval 1.0.4 (asset pluginval_Linux.zip) downloaded and runs; osv-scanner 2.2.4 runs.
- 2026-11-04T08:35:00Z | S-CORE | 1 | pass | (this commit) | per-class event monotonicity; T-012+T-028 green
- 2026-11-04T08:45:00Z | S-METRICS | 1 | pass | (this commit) | T-025 LOO checker aligned to median methodology (D-3); gate 24.538530602719486 dB reproduced at 1e-9
- 2026-11-04T09:00:00Z | S-SEC | 1 | pass | (this commit) | OSV API scan of 6 pinned packages: 0 findings; T-019 green
- 2026-11-04T09:20:00Z | S-CI | 1 | pass | (this commit) | ci.yml 6 versioned jobs, fail-fast false, artefact postconditions; runtime-assembled secret patterns; T-029/T-030 green
- 2026-11-04T09:40:00Z | S-LISTEN | 1 | pass | (this commit) | P2 zip re-fetched via 8 parallel resumable ranges (116,133,457 B, unzip -t clean); readWav fmt fixes; top-12 velocity selection (D-4); end-fade orientation fix (D-6); T-027 green; evidence branch gate-evidence/G-LISTEN marker 90ddf75 pushed
- 2026-11-04T10:05:00Z | S-CI | 2 | pass | (this commit) | ASan+UBSan suites clean (two-pass bootstrap, D-7); T-021 green
- 2026-11-04T10:15:00Z | S-ALL | 1 | pass | (this commit) | FULL SUITE: Ran 30 tests, 30 ok, 0 failures (release binary, EGB_CONTRACT_BIN=/var/tmp/egb_contract)
- 2026-11-04T13:10:00Z | S-GATE | 1 | iterate | (round-2 commit) | listener: "all samples sound reed-like" -> harmonic-decay mechanism change (0.018m^2 term), new seed 20261105, suite 30/30 green on release+ASan+UBSan, T-026 22.47 dB
- 2026-11-04T13:45:00Z | S-GATE | 2 | iterate-result: 12/12, gate FAIL (indistinguishability) | e4142bd | discrimination now perfect; rounds 2/3 used
