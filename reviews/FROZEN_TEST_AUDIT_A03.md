# Frozen-test audit — amendment 03 (2026-11-20)

Requested by the owner after the third implementation-time test challenge (T-022, T-048, T-021). Target: implementer commit `e36b982` merged locally with generation head `c44f4ec` (nothing pushed to the implementation branch). Builds: release, ASan, UBSan (`-fsanitize=address|undefined -fno-omit-frame-pointer`, RelWithDebInfo). Licensed Guitar-TECHS P1/P2 archives downloaded from Zenodo record 14963133 into a directory outside the repository; MD5 and size match `research/audio/REFERENCES.json` (P1 `ca0c4674…`, 108,626,613 B; P2 `40fbf03d…`, 116,133,457 B). No reference audio was committed.

## 1. Dynamic run — every frozen test on its real inputs

| Run | Result |
|---|---|
| Release suite, reference cache present, `.tools` installed | 48 run, 47 pass; T-021 fails only until the sanitizer logs exist |
| `scripts/run_sanitizer_suites.sh` (D-038) | ASan: 46 tests, OK, 0 findings. UBSan: 46 tests, OK, 0 findings. 4 min 31 s |
| T-021 on those logs | pass (46 listed, 46 expected) |
| T-023, T-024, T-026, T-027 with the cache (never run in CI) | pass. T-026: median band RMS 21.24 dB (gate 24.54; v1 22.47), median attack 13.54 ms (8.21–31.54) |

Conclusion: no further frozen-test conflict exists on the implementer's code as amended to D-038, provided the environment is set up as below.

## 2. Environment gaps found (fixed in the plan)

- T-024 and T-027 call `python3` with `PYTHONPATH=.tools` and need `numpy`, `scipy`, `soundfile` and `mido`. The v1 setup installs them with `pip install --target .tools -r requirements-lock.txt`; the amendment-03 environment section omitted it, so a fresh implementer following it alone fails both tests when the cache is present. Fixed in `plan/ENVIRONMENT.md`.
- S-106 said 'build ASan and UBSan binaries' without commands, and neither CMake nor CI defines them. The verified commands are now in S-106 and `plan/ENVIRONMENT.md`.

## 3. Static audit — what each rendered test actually plays

`research/spikes/a03_allocation_audit.txt` lists, for every rendered test, the note, channel, and the string and fret the D-013 rule selects. **Finding (R-023, raised to High):** the engine maps MIDI channels 1–6 to strings with no fret-range check. `noteEvents` (the shared test helper), both frozen fixtures and every v1 demo use channel 1, so any note below E4 plays on the high-E string at a negative fret: a speaking length up to four times the scale, at a few newtons of tension. Affected:

- **v1 tests:** T-003, T-006, T-012 (input validation; harmless), T-013, T-015, T-028 (demos), T-033 and T-036..T-038 (E2 on the high-E string at fret −24).
- **Amendment 03 tests:** T-045 and T-051 (via the fixture), plus T-009, T-010, T-020 and T-039 through the fixtures.
- **T-026:** two of its three candidate notes (MIDI 40, 45).
- **G-LISTEN pairs:** every pair candidate (T-027) is rendered on the high-E string. The 12 references (MIDI 71–86) were played on the D, G, B and high-E strings, so many v1 listening pairs compared the model's thinnest string with a recording on a thicker one.

Because channel 1 is the default MIDI output channel of most hosts, this is the product's default behaviour for a keyboard player, not only a test artefact.

## 4. Spike — cost of fixing the root cause

Planning spike (not committed to any implementation branch): `noteOn` uses channel 1–6 as the string only when the resulting fret is 0..24, otherwise allocates first-fit. Full suite with the cache: T-007, T-037 and T-045 fail (T-022 failed only because the spike tree had no `.git`). Those three were calibrated or predicted on the negative-fret behaviour. Any fix therefore needs test challenges for T-007, T-037 and T-045, and new evidence for T-026 and G-LISTEN-2. **This changes product behaviour and v1 listening evidence, so it is held for the owner's decision.**

## 5. Other observations

- `pathGain = 6.0` (+15.6 dB fixed output trim) added at S-105 is recorded in `DEVIATIONS.md`; T-051's pre-safety peak of 5.08 stays under the D-034 limit of 5.75.
- No hard-coded suite-size, CI-layout or parameter-count literal remains in the hashed files (sweeps in D-036 and D-038).

## 6. Outcome (2026-11-20)

Owner decision: fret-checked channel rule (D-039). Root-cause analysis of the three spike failures showed:
- **T-007:** its expected partial assumed the high-E gauge.
- **T-037:** it asserted a physically impossible decay direction.
- **T-045 (and T-035):** they measured through a rectangular-window helper that leaks low partials into weak bands. Once measured with a Hann window, they agree with the modal predictions within 1 dB.

T-027 also hard-coded the round-4 pair seed, which S-LISTEN-2 could not have changed (a fifth latent challenge). Its pair candidates now use the reference's string. Final verification: release 49/49, ASan 47 OK, UBSan 47 OK, 0 findings, with the reference cache. Details in D-039.
