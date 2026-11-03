# Traceability

## Success criteria

| Criterion | Tests | Producing steps |
|---|---|---|
| SC1 | T-001, T-002, T-003, T-004, T-018 | S-001–S-006, S-CI, S-LISTEN |
| SC2 | T-005, T-006, T-013 | S-001–S-006, S-CI, S-LISTEN |
| SC3 | T-007, T-008 | S-001–S-006, S-CI, S-LISTEN |
| SC4 | T-009 | S-001–S-006, S-CI, S-LISTEN |
| SC5 | T-010, T-011, T-013, T-014, T-020, T-022 | S-001–S-006, S-CI, S-LISTEN |
| SC6 | T-017, T-019, T-021, T-029, T-030 | S-001–S-006, S-CI, S-LISTEN |
| SC7 | T-023, T-024, T-025, T-026, T-027, T-028 | S-001–S-006, S-CI, S-LISTEN |
## Platform mapping

| Intake platform | CI job/waiver |
|---|---|
| Windows 11 x64 | `windows-2025` (Windows 11 API-compatible x64 coverage; no separate Windows 10 support claimed) |
| macOS 15 ARM64 | `macos-15` |
| Ubuntu 24.04 x64 | `ubuntu-24.04` |
| Linux ARM64 additional coverage | `ubuntu-24.04-arm` |
| Alpine libc variant | `alpine:3.22` on `ubuntu-24.04` |

## Tests

| Test | Requirement/claim | Gate step |
|---|---|---|
| T-001 | Unit: SC1/D-003 parameter IDs, ranges, defaults and invalid-state rejection. | S-001–S-006 |
| T-002 | Unit: SC1/D-004 tension, inharmonicity, fret and pluck formulas against expected_values.json; 1e-12 relative tolerance. | S-001–S-006 |
| T-003 | Unit: SC1/D-004 each construction control has bounded finite isolated-stage effect and fret size cannot change pitch. | S-001–S-006 |
| T-004 | Unit: SC1/D-003/D-004 per-string pickup sensing, aperture, type, phase and parallel/series combination. | S-001–S-006 |
| T-005 | Unit: SC2/D-004 pick angle/depth attack and noise expected values and monotonic boundaries. | S-001–S-006 |
| T-006 | Integration: SC2/D-004 palm mute continuum, exact zero bypass, monotone damping/cutoff and 20 ms smoothing. | S-001–S-006 |
| T-007 | Unit: SC3/D-003 MIDI 40–88, per-string tuning and 0.01-cent string-model pitch error. | S-001–S-006 |
| T-008 | Integration: SC3 finite audio at 44100, 48000, 88200 and 96000 Hz with modes below 0.45 sample rate. | S-001–S-006 |
| T-009 | Integration: SC4/D-006 frozen 16-voice worst case has pre-safety finite output and post-safety peak <=1; no renderer normalisation. | S-001–S-006 |
| T-010 | Integration: SC5/D-006 same build/platform repeated float32 output is bit-identical; cross-platform maximum error <=1e-6. | S-001–S-006 |
| T-011 | Unit: D-005 valid APVTS schemaVersion=1 round trip; unknown IDs, NaN and >256 KiB rejected atomically. | S-001–S-006 |
| T-012 | Security: D-005 event UTF-8/schema/time validation, 1 MiB/10000-event caps, malformed input and non-execution. | S-001–S-006 |
| T-013 | Integration: SC5/D-005 structural changes affect new voices only; continuous controls crossfade without zipper discontinuities. | S-001–S-006 |
| T-014 | Integration: SC5/D-005 instrumented host run proves no audio-thread allocation, lock, I/O, logging or APVTS tree replacement. | S-001–S-006 |
| T-015 | Operational: startup, reset, graceful shutdown and interruption resume produce valid output without leaked voices. | S-001–S-006 |
| T-016 | Operational: invalid sample rates/block sizes/voice counts and resource exhaustion fail explicitly and recover after reset. | S-001–S-006 |
| T-017 | Performance: A-009 pinned 16-voice benchmark meets per-runner budget; three runs, median gate and >10% spread rerun once. | S-CI |
| T-018 | Integration: SC1/SC2 parameter automation persists through host state and produces deterministic offline bounce. | S-001–S-006 |
| T-019 | Security: dependency vulnerability scan has no unresolved Critical/High shipped finding and no suppressed report. | S-CI |
| T-020 | Integration: D-001/D-005 VST3 and headless renderer share identical engine output for one frozen event file. | S-001–S-006 |
| T-021 | Operational: D-010 pluginval and ASan/UBSan pass supported host behaviours; failure is not excluded. | S-CI |
| T-022 | Integration: D-005 metadata contains commit, lock hash, seed, all parameters, event hash, UTC timestamp, rate, unclipped peak and platform. | S-001–S-006 |
| T-023 | Integration: D-007 calibration uses P1 only; P2 remains held out and no per-note corrective constants exist. | S-001–S-006 |
| T-024 | Integration: D-008 onset alignment and stable-window extraction reproduce committed reference_metrics.json within 1e-9. | S-001–S-006 |
| T-025 | Integration: D-008 21-band vectors and leave-one-out reference spread reproduce 24.538530602719486 dB within 1e-9. | S-001–S-006 |
| T-026 | Integration: SC7/D-008 candidate median band RMS <=24.538530602719486 dB and median attack in [8.208333333333334,31.541666666666668] ms. | S-001–S-006 |
| T-027 | Integration: D-009 pair builder makes 12 one-second onset pairs, RMS -23 dBFS, 10 ms fade, 24-bit/44.1 kHz and seeded sides/key. | S-LISTEN |
| T-028 | Operational: D-009 demos render reproducibly from event files and evidence branch/marker commit contain hashes and delivery URLs. | S-LISTEN |
| T-029 | Operational: D-010 CI workflow schema, versioned matrix, fail-fast false, artefact postconditions and no failure swallowing. | S-CI |
| T-030 | Security/operational: repository secret scan, licence attribution, checksum verification and clean shutdown/resume evidence. | S-CI |

Every C-001–C-008 maps through D-001–D-012 to the cited tests; no N/A artefact is required.
