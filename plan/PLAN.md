# Zero-question execution plan — amendment 03 (guitar physics research)

**Status: READY**

- Profiles: `software`; flags `audio = true`, `software.deploys = false`, `math.exploration = false`, `courseware = false`.
- Protocol: planning protocol v3.15 (`qualitycoding/skills` `ef99285`).
- Claims added (C-009..C-035, 25): 10 verified, 10 corroborated, 4 single-source (carried as risks R-011, R-018), 1 superseded (C-028 → C-034); 19 load-bearing in force.
- Tests: 12 added (T-040..T-051: 6 unit, 4 integration, 1 measurement-validity, 1 guard); 3 retired (T-001, T-011, T-032); 48 active in total. Red at handoff: 11 by design (T-022 amended by D-036).
- Steps: 13 (S-000, S-101..S-106, S-REVIEW, S-ADVERSARIAL, S-108, S-LISTEN-2, S-RETRO, S-KNOW). Gates: 2 (G-LISTEN-2, G-003).
- Risks (amendment, residual): 0 Critical, 0 High, 12 Medium, 3 Low.
- Assumption audit: 15 confirmed, 6 falsified (A-024 → D-035; C-028 → C-034; D-030 premise → D-036; T-048 allocation and T-035 resonance premises → D-037; T-021 premise → D-038), 6 unverifiable (each a risk).
- Code review, adversarial review and mutation: not yet run (implementation steps); mutation opt-out D-033.
- Review capacity: the cold read, pre-mortem and audit were separated self passes after fresh-context agents were rate-limited (R-017, D-035).

Branch: generation `gen-20261111T150746Z-guitar-physics-research`; implementation `impl-20261111T150746Z-guitar-physics-research`. The v1 plan is archived in `plan/archive/v1/PLAN.md`; its completed steps are not repeated. Each green chunk is committed, pushed and verified with `git ls-remote` immediately (Rule 6). Independent steps may run concurrently only where `Depends on` and `Exclusive resources` allow.

### S-000 Environment and access verification
- Tier: Haiku
- Profile: software; audio=true
- Depends on: none
- Inputs: `plan/ENVIRONMENT.md` (Amendment 03 section); `requirements-lock.txt`; credentials from the host credential environment only
- Actions: 1. `git switch -c impl-20261111T150746Z-guitar-physics-research` from the generation branch head. 2. Set a repository-local git identity if `git config user.email` prints nothing (L-20261111T151000Z). 3. Run every command of the Amendment 03 section of `plan/ENVIRONMENT.md`; record versions. 4. Probe `codeload.github.com`, `github.com`, `api.github.com` and `zenodo.org` reachability with timestamps (L-20261105T220500Z, L-20261102T085622Z). 5. Run `sha256sum -c tests/FROZEN_MANIFEST.sha256` and the full suite: expect T-022 and T-040..T-046, T-048..T-050 to fail and every other test to pass (T-022 is red until S-103 brings the descriptor count to 42, D-036). 5a. Record the pre-safety peaks printed by T-009 and T-051 on this unmodified engine in `reports/a03_s000_environment.txt` (baseline for the D-034 gain rule). 6. Append to `EXECUTION_LOG.md` under a heading `## Amendment 03` (UTC, step, attempt, result, commit, note). 7. Commit, push, compare `git ls-remote` with HEAD.
- Outputs: `EXECUTION_LOG.md`; `.checkpoints/state.json`; `reports/a03_s000_environment.txt`
- Evidence produced: none
- Done when: all checks pass; the red/green split equals step 5; the report exists, is non-empty and lists every tool version and probe time.
- Checkpoint: run_id, branch, tool versions, environment class, last verified commit.
- On failure: halt and write `BLOCKED.md` listing exactly what is missing; retry only transient network failures three times with visible backoff.
- Gate: none
- Relevant decisions/claims: D-020, D-032
- Lessons applied: L-20261111T151000Z-fresh-clone-has-no-commit-identity, L-20261105T220500Z-probe-reachability-and-reprobe-before-download-steps, L-20261007T150100Z-no-credentials-in-command-lines
- Exclusive resources: none

### S-101 Freeze enforcement in CI
- Tier: Haiku
- Profile: software
- Depends on: S-000
- Inputs: `.github/workflows/ci.yml`; D-032
- Actions: 1. Add a job `frozen-manifest` (`runs-on: ubuntu-24.04`, `defaults.run.shell: bash`) whose single step runs `set -o pipefail; sha256sum -c tests/FROZEN_MANIFEST.sha256`. 2. Push a scratch branch `a03-manifest-probe` with one byte appended to `tests/test_physics.py`; confirm the job fails on that branch; delete the branch. 3. Confirm it passes on the implementation branch. 4. Run `python3 -m unittest tests.test_contract -k test_029` locally (T-029 workflow schema still green).
- Outputs: `.github/workflows/ci.yml`; `reports/a03_manifest_probe.txt` (run URLs and conclusions)
- Evidence produced: D-032 control
- Done when: the probe run concluded `failure` and the implementation-branch run concluded `success`; T-029 passes; the report names both run IDs.
- Checkpoint: both run IDs.
- On failure: if the probe passes, the check cannot fail — fix the job until it does (Rule 14); never mark it informational.
- Gate: none
- Relevant decisions/claims: D-032
- Lessons applied: L-20261029T000000Z-green-ci-gate-never-ran, L-20261031T100000Z-actions-run-steps-have-no-pipefail
- Exclusive resources: CI runners

### S-102 Physics functions
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-000
- Inputs: `include/egb/Physics.h`; `research/spikes/physics_oracle.py`; `research/spikes/physics_sketch/physics_sketch.cpp`; D-021..D-028
- Actions: 1. Replace the `egb::phys` stubs in `src/physics.cpp` with an implementation of every Physics.h function exactly as D-021..D-028 and the oracle define (the planning sketch may be used as a start). Keep the two inspection stubs (`debugModeTable`, `debugPickupElectrical`) until S-104/S-105. 2. Build; run T-040..T-044, T-047. 3. Run the full suite to expose regressions. 4. Commit, push, verify.
- Outputs: `src/physics.cpp`; `reports/a03_s102_suite.txt`
- Evidence produced: T-040, T-041, T-042, T-043, T-044
- Done when: T-040..T-044 and T-047 pass; every test that passed at S-000 still passes; the report exists and lists each test with its result.
- Checkpoint: commit, green test IDs.
- On failure: compare with the oracle function by function; never edit `include/egb/Physics.h` or `research/spikes/physics_expected.json` (hashed). An oracle-versus-header disagreement is a `TEST_CHALLENGE.md`.
- Gate: none
- Relevant decisions/claims: D-021..D-028; C-010..C-030
- Lessons applied: L-20261007T150300Z-hand-typed-frozen-constant, L-20261009T120009Z-plate-stretch-direction-taken-from-plan
- Exclusive resources: none

### S-103 Parameter contract v2 and state schema 2
- Tier: Sonnet
- Profile: software
- Depends on: S-000
- Inputs: `include/egb/Engine.h` (new fields); `src/engine.cpp` descriptors/validate/operator==; `src/plugin_processor.cpp`; D-029; `tests/physics/state_v1.xml`
- Actions: 1. Append the seven D-029 descriptors after the 35 v1 descriptors, with exact IDs, types, ranges, defaults and choice strings. 2. Extend `validate` and `operator==` to the seven fields. 3. Write `schemaVersion="2"`; load version 2 (42 IDs exactly) and version 1 (35 IDs exactly, new fields defaulted); reject anything else atomically. 4. Include the new parameters in render metadata through the descriptor array (T-022). 5. Run T-049, T-050, T-018, T-022 and the full suite. 6. Commit, push, verify.
- Outputs: `src/engine.cpp`; `src/plugin_processor.cpp`; `reports/a03_s103_suite.txt`
- Evidence produced: T-049, T-050
- Done when: T-049, T-050, T-018 and T-022 (amended by D-036) pass and no previously passing test fails; the report exists.
- Checkpoint: commit, descriptor count 42.
- On failure: a change to any v1 descriptor is a public-interface change — halt with `BLOCKED.md`.
- Gate: none
- Relevant decisions/claims: D-029, D-005, D-036
- Lessons applied: L-20261008T173531Z-editor-note-labels-diverged-from-midi-map, L-20261007T150800Z-host-facing-accessors-missing
- Exclusive resources: none

### S-104 Engine: excitation, velocity, spatial sampling, structural loss, inspection table
- Tier: Fable (Mythos)
- Profile: software; audio=true
- Depends on: S-102, S-103
- Inputs: `src/engine.cpp` voice build (lines around `buildVoice`); D-021, D-022, D-023, D-026, D-027, D-028
- Actions: 1. In `buildVoice`, replace the v1 excitation average with `pluckAmplitude(m, pluckPosition)`, multiply by `velocityGain(fm, f1)`, replace the vertical aperture term with `pickupSpatial(m, xp, speakingM, type)` and set the horizontal amplitude to `vertical × horizontalCoupling(fm, type)`. 2. Compute `W` from `map.tensionN` and the string's μ, `xBearing = scaleM − speakingM`, and add `structuralDecayDbPerS(...)` to both polarisations' decay. 3. Implement `debugModeTable` by calling the same per-mode builder the voice uses (no second formula). 4. Keep every other v1 stage (contact burst, polarisation split, palm mute, AVX2 path) unchanged. 5. Run T-046, T-048, then the full suite including T-026, T-036..T-039 and T-017. 6. Commit, push, verify.
- Outputs: `src/engine.cpp`; `src/physics.cpp` (inspection table); `reports/a03_s104_suite.txt` with T-026 and T-017 numbers
- Evidence produced: T-046, T-048
- Done when: T-046 and T-048 pass, every previously passing test still passes, the report records T-026's band RMS and attack values and T-017's medians.
- Checkpoint: commit, T-026 and T-017 values.
- On failure: T-026 or T-017 regressions follow D-034; frozen failures follow D-030; no hashed file is edited.
- Gate: none
- Relevant decisions/claims: D-021..D-028, D-034, D-037; C-019..C-030
- Lessons applied: L-20261009T161100Z-audio-thread-takes-mutex-and-copies-vectors-not-in-premortem, L-20261004T150500Z-cross-library-float-fix-regressed-passing-cases
- Exclusive resources: none

### S-105 Engine: pickup electrical stage
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-104
- Inputs: `src/engine.cpp` pickup filter and recombination; D-025
- Actions: 1. Replace the D-013 peaking filter with `rlcDigital(rlcAnalog(...))` per pickup path (parallel) or one summed-coil RLC (series), coefficients computed at snapshot time. 2a. Wrap the body of `Engine::render` in `juce::ScopedNoDenormals` (R-020). 2. Smooth cable/amplifier changes with the existing 20 ms rule by interpolating the analogue parameters and recomputing coefficients once per block (no allocation). 3. Implement `debugPickupElectrical`. 4. Remove the unused `pickupSpec` resonance/Q fields only where no frozen file references them (`include/egb/Mapping.h` is not hashed and no hashed file calls `egb::pickupSpec`; keep the function and its signature for the v1 aperture constants that `kHorizontalCouplingM` mirrors, and stop using its resonance and Q values in the engine). 5. Run T-045, T-051, T-004, T-013, T-014, T-033..T-035 (T-035 as amended by D-037), T-009, T-017 and the full suite. 6. Commit, push, verify.
- Outputs: `src/engine.cpp`; `include/egb/Mapping.h` (if changed); `reports/a03_s105_suite.txt`
- Evidence produced: T-045, T-051
- Done when: the D-034 gain rule has been evaluated against the S-000 baseline and its outcome recorded; the whole suite passes — 48 tests run (28 v1 after retiring T-001/T-011, 8 amendment after retiring T-032, 12 physics), of which T-023, T-024 and T-027 SKIP-pass while the reference cache is absent (D-17) — T-051 prints its pre-safety peak, and the report exists.
- Checkpoint: commit, suite totals, pre-safety peak.
- On failure: D-034 rules; a frozen failure → `TEST_CHALLENGE.md`.
- Gate: none
- Relevant decisions/claims: D-025, D-034, D-037; C-011, C-012, C-017
- Lessons applied: L-20261008T173530Z-gain-staging-masked-by-normalising-renderers, L-20261028T220000Z-decibelstogain-minusinfinity-misuse
- Exclusive resources: none

### S-106 Full regression, sanitizers and performance
- Tier: Sonnet
- Profile: software
- Depends on: S-105, S-101
- Inputs: v1 sanitizer scripts `scripts/run_sanitizer_suites.sh`; T-017; T-021
- Actions: 1. Run the full suite on the release build; build ASan and UBSan binaries and run `EGB_ASAN_BIN=<asan egb_contract> EGB_UBSAN_BIN=<ubsan egb_contract> sh scripts/run_sanitizer_suites.sh` from the repository root (D-038: every frozen test except T-017 and T-021; exit 0 required); commit the two logs; re-run T-021 in the release suite. 2. Push and wait for CI on all six platform jobs plus `frozen-manifest`. 3. Record per-runner T-017 medians against A-009. 4. Run pluginval where reachable (v1 D-8 limitation applies otherwise, reported honestly).
- Outputs: `reports/asan_suite.txt`; `reports/ubsan_suite.txt`; `reports/a03_ci_run.txt` (run ID, per-job conclusion, T-017 medians)
- Evidence produced: T-017, T-021, CI evidence for SC6
- Done when: release, ASan and UBSan suites pass locally; every CI job concludes `success` on the pushed commit; reports exist and name the run ID.
- Checkpoint: CI run ID, commit.
- On failure: D-034 for T-017; sanitizer findings are engine fixes (D-012).
- Gate: none
- Relevant decisions/claims: D-010, D-012, D-032, D-034, D-038
- Lessons applied: L-20261029T000000Z-green-ci-gate-never-ran, L-20261101T140000Z-intermittent-host-failure-needs-a-stress-test
- Exclusive resources: CI runners

### S-REVIEW Traditional code review
- Tier: Opus (fresh context, did not author S-102..S-105)
- Profile: software
- Depends on: S-106
- Inputs: `git diff gen-20261111T150746Z-guitar-physics-research...HEAD`
- Actions: review per protocol 3.8 item 1: anti-patterns, untested paths (each new branch maps to T-040..T-051), audio-thread allocation/locks, input validation of the seven parameters, dependency currency (unchanged pins); classify findings per Rule 4; fix Critical/High before continuing, each fix a commit and, where it corrects the implementer's own mistake, a lesson.
- Outputs: `reviews/CODE_REVIEW_A03.md`
- Evidence produced: review record
- Done when: the file exists, every finding links to a fix commit or an `R-###`, and no Critical/High is open.
- Checkpoint: finding counts by severity.
- On failure: Critical/High unresolved → halt with `BLOCKED.md`.
- Gate: none
- Relevant decisions/claims: D-020..D-035
- Lessons applied: L-20261031T100100Z-verify-conformance-claims-against-the-tree, L-20261119T150000Z-review-agents-assumed-available
- Exclusive resources: none

### S-ADVERSARIAL Adversarial review
- Tier: Opus (fresh context)
- Profile: software
- Depends on: S-REVIEW
- Inputs: implementation branch; D-021..D-029
- Actions: attack the new boundaries: NaN/denormal/extreme values for the seven parameters through state, automation and event files; cable 0 pF with 10 MΩ load at 96 kHz (filter stability); pluck position at both bounds; every body/joint/fingerboard combination at 16 voices; rapid automation at block sizes 1 and 2048; v1/v2 state fuzzing (truncated, duplicated attributes, schemaVersion strings). Each confirmed break becomes a new frozen test through the Phase 2 machinery (planner amendment) or an accepted risk with severity.
- Outputs: `reviews/ADVERSARIAL_REVIEW_A03.md`
- Evidence produced: review record; any new tests via amendment
- Done when: the file exists and no Critical/High break is open.
- Checkpoint: break counts.
- On failure: Critical/High → halt with `BLOCKED.md`.
- Gate: none
- Relevant decisions/claims: D-029, D-025, D-035
- Lessons applied: L-20261101T140000Z-intermittent-host-failure-needs-a-stress-test
- Exclusive resources: none

### S-108 Reference feature comparison before listening
- Tier: Sonnet
- Profile: software; audio=true
- Depends on: S-ADVERSARIAL
- Inputs: licensed reference cache (Guitar-TECHS, `research/audio/REFERENCES.json`); `scripts/analyse_reference.py`
- Actions: 1. Re-read the licence on the Zenodo record page and confirm CC BY 4.0 and the `redistributable` flag in `research/audio/REFERENCES.json` (A-020); obtain the reference cache per v1 `research/audio/REFERENCES.md` (checksums must match; on mismatch halt per D-012). 2. Run T-023..T-027 with the cache present and record values. 3. Compute spectral centroid, 21-band decay and tail level for candidate and reference on the T-026 note set; write `reports/feature_comparison_a03.md` with the v1 (61ab5ed) values beside the amended values. 4. Correlate every reference clip that will enter the pairs with its decoded source; write `reports/reference_clip_correlation.json` (each ≥ 0.99).
- Outputs: `reports/feature_comparison_a03.md`; `reports/reference_clip_correlation.json`
- Evidence produced: inputs to G-LISTEN-2
- Done when: T-023..T-027 pass with the cache present; both reports exist and parse; every correlation ≥ 0.99.
- Checkpoint: report hashes.
- On failure: a correlation < 0.99 means a broken decode — fix the pair builder, never issue the round; T-026 failure → D-034.
- Gate: none
- Relevant decisions/claims: D-031, D-008, D-012
- Lessons applied: L-20261106T010000Z-verify-blind-references-against-sources, L-20261106T180200Z-reference-fit-before-listening, L-20261106T180100Z-frozen-metric-caps-the-property-under-listening
- Exclusive resources: reference cache

### S-LISTEN-2 Blind listening and demos
- Tier: Sonnet
- Profile: software; audio=true
- Depends on: S-108
- Inputs: v1 pair builder and demo renderer (T-027/T-028 tooling); `demos/demo_phrase.events`; D-031; R-016
- Actions: 1. Add an executable target `egb_demo` (`src/demo_main.cpp`, linked to `egb_core`) with the fixed command line `egb_demo <events-file> <out.wav> [<parameter_id>=<value> ...]`: it builds a default `ParameterSnapshot`, applies each assignment through the descriptor table (unknown ID or invalid value → exit 2 with a message), renders with `renderEventFile` at 44.1 kHz and writes 24-bit WAV plus `<out.wav>.json` metadata. Event-file `control` lines are not used for demos, because the renderer parses but never applies them (R-016). 2. Render, for each setting below, `demos/demo_phrase.events` to `demos/a03/<demo>-<n>.wav`: `demo_pickup_load` pot index 0/1/2 at cable 600, then cable 200/1500 at pot index 0; `demo_body_type` body_type 0/1/2; `demo_neck_joint` neck_joint 0/1/2; `demo_pluck_position` pluck_position 0.08/0.18/0.30/0.45; and re-render v1 `demo_palm_mute` as palm_mute 0/0.25/0.5/0.75/1.0 and `demo_pick_angle` as pick_angle_deg −60/−20/20/60. 3. Build 12 pairs with seed `20261112` (round 1) and the v1 pair builder. 4. Commit `[gate-evidence G-LISTEN-2]` and push the orphan branch `gate-evidence/G-LISTEN-2` per the `audio-blind-listening-validation` skill; record delivery URLs. 5. Halt at G-LISTEN-2 with `GATE-G-LISTEN-2.md`.
- Outputs: `src/demo_main.cpp`; `CMakeLists.txt` (target `egb_demo`); `demos/a03/*.wav` and `.json` (24 renders); orphan branch `gate-evidence/G-LISTEN-2`; `GATE-G-LISTEN-2.md`
- Evidence produced: T-027 and T-028 on the new seed; gate bundle
- Done when: T-027 and T-028 pass on the new seed; all 24 renders exist, are non-empty, have peak ≤ 1.0, and within each demo every pair of settings differs in RMS-normalised spectrum by more than 0.5 dB in at least one octave band (shows the control was applied) — except `demo_neck_joint`, whose D-023 effects are bounded below specimen spread, where each pair must differ by a maximum absolute sample difference above 1e-5; `egb_demo` exits 2 on an unknown parameter (shown once); the evidence branch exists remotely with every listed file; `GATE-G-LISTEN-2.md` lists URLs and hashes.
- Checkpoint: evidence commit, seed, round.
- On failure: a demo whose settings do not differ means the parameter is not wired — fix the engine, never the check; otherwise per G-LISTEN-2 branches.
- Gate: G-LISTEN-2
- Relevant decisions/claims: D-031
- Lessons applied: L-20261106T180300Z-twelve-pairs-too-noisy-to-steer-iteration, L-20261106T180500Z-owner-extension-needs-a-recorded-route, L-20261007T151000Z-large-evidence-off-impl-branch, L-20261101T041800Z-perf-harness-must-exercise-what-it-reports
- Exclusive resources: evidence branch

### S-RETRO Retrospective
- Tier: Opus (fresh context)
- Profile: software; audio=true
- Depends on: every step above
- Inputs: `EXECUTION_LOG.md`, `DEVIATIONS.md`, gate records, CI history, `research/PRIOR_KNOWLEDGE.md`, `lessons/`, `knowledge/`
- Actions: protocol 3.7.1 questions 1–5; diff workflows and manifests against `plan/ENVIRONMENT.md` for undocumented substitutions; normalise the five v1 entries without front matter (`knowledge/K-20261104T*`, `lessons/L-20261104T10*`) to the Appendix A/B templates so the schema check passes (R-012).
- Outputs: `RETROSPECTIVE.md`; new lessons/knowledge items; amended source register rows
- Evidence produced: none
- Done when: every finding links to an `L-` or `K-` file and the Appendix C schema check exits 0 over `lessons/` and `knowledge/`.
- Checkpoint: counts.
- On failure: fix records; re-run the schema check.
- Gate: none
- Relevant decisions/claims: D-020
- Lessons applied: L-20261004T102010Z-plan-controls-not-traced-to-delivery
- Exclusive resources: none

### S-KNOW Lessons and knowledge push
- Tier: Haiku
- Profile: software; audio=true
- Depends on: S-RETRO
- Inputs: `lessons/`, `knowledge/`; A-021
- Actions: protocol 3.7.2 exactly, halting at G-003.
- Outputs: `GATE-G-003.md`; pushes to the stores or bundles
- Evidence produced: none
- Done when: per 3.7.2 item 4.
- Checkpoint: store commits.
- On failure: bundle fallback.
- Gate: G-003
- Relevant decisions/claims: A-021
- Lessons applied: L-20261007T150100Z-no-credentials-in-command-lines
- Exclusive resources: store repositories
