# Zero-question execution plan

Do not begin until S-000 passes. Independent steps may run concurrently only when dependencies and exclusive resources permit. Each green chunk is committed, pushed and remote-verified immediately.

### S-000 Environment and access verification
- Tier: Haiku
- Profile: software; audio=true
- Depends on: none
- Inputs: `plan/ENVIRONMENT.md`; `requirements-lock.txt`; GitHub credentials supplied through the host credential environment, never command arguments
- Actions: 1. Re-run the ephemeral-environment probe and record durable/non-executable mounts. 2. `git switch -c impl-<run_id>` from the generation branch. 3. Run every setup/version command in `plan/ENVIRONMENT.md`, restaging executables under `/tmp`. 4. Verify repository write access with an authenticated dry-run and host reachability; verify pinned JUCE/pluginval/OSV downloads and published checksums without printing credentials. 5. Create `EXECUTION_LOG.md` and append every attempt as UTC, step, attempt, pass/fail/blocked, commit and note. 6. Commit, push, and compare `git ls-remote` with HEAD.
- Outputs: `EXECUTION_LOG.md`; `.checkpoints/state.json`; environment verification report
- Evidence produced: none
- Done when: All access and version checks pass; branch exists remotely at the same hash. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record run_id, branch, tool versions, mount class and last verified commit.
- On failure: Halt before delivery and write `BLOCKED.md`; no rollback of generation artefacts. Retry only transient network failures three times with visible backoff.
- Gate: none
- Relevant decisions/claims: D-010, D-012; C-007, C-008
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: none

### S-001 Project skeleton, parameters and validated boundaries
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-000
- Inputs: `include/egb/Engine.h`; `plan/DECISIONS.md` D-003–D-005; `tests/test_contract.py`; pinned JUCE
- Actions: 1. Fetch JUCE at its exact commit and add the CMake VST3/headless targets using C++20. 2. Implement every D-003 APVTS parameter with stable ID/range/default and complete `ParameterSnapshot`. 3. Implement atomic whole-snapshot validation, schemaVersion=1 state, bounded event parser and error results. 4. Replace only the T-001/T-011/T-012/T-016 stub dispatch paths; run those cases plus the whole suite to expose regressions. 5. Commit/push/verify after green.
- Outputs: `src/` and `include/egb/` production interfaces; `CMakeLists.txt`; state/event implementation; test reports
- Evidence produced: T-001, T-011, T-012, T-016
- Done when: Those four tests pass; invalid input is rejected atomically; caps are enforced. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record green test IDs, JUCE hash and commit.
- On failure: Revert the step commit with `git revert <commit>` if the public interface was accidentally changed; otherwise fix forward and rerun. Interface change requires `BLOCKED.md`.
- Gate: none
- Relevant decisions/claims: D-002, D-003, D-005, D-012; C-007
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: none

### S-002 Deterministic modal string engine
- Tier: Fable (Mythos)
- Profile: software; audio=true
- Depends on: S-001
- Inputs: D-001/D-004–D-006; `research/spikes/model_spike.py`; `research/spikes/expected_values.json`; frozen events
- Actions: 1. Implement preallocated 16-voice, six-string, dual-polarisation modal voices and seeded contact noise. 2. Implement the exact tension, stiffness, excitation, fret-length and sample-rate ceiling formulas; use causal short-input-safe filtering. 3. Implement prepare/render/reset, per-voice seed derivation and production master/safety path. 4. Run T-002/T-007–T-010/T-015/T-020/T-022 and the full suite. 5. Commit/push/verify.
- Outputs: Modal voice/engine source; deterministic renderer core; numeric and audio test reports
- Evidence produced: T-002, T-007, T-008, T-009, T-010, T-015, T-020, T-022
- Done when: Listed tests pass, output is finite and deterministic, metadata is complete and no renderer normalisation exists. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record engine commit, oracle hash, sample-rate results and peaks.
- On failure: One general mechanism fix per iteration; `git revert <commit>` for a broken step. Metric miss follows D-012 diagnosis order, never threshold edits.
- Gate: none
- Relevant decisions/claims: D-001, D-004, D-005, D-006, D-012, D-013; C-004, C-005
- Lessons applied: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
- Exclusive resources: none

### S-003 Construction, pickup and articulation controls
- Tier: Fable (Mythos)
- Profile: software; audio=true
- Depends on: S-002
- Inputs: D-003/D-004; expected-value oracles; frozen events
- Actions: 1. Add bounded fret termination, neck/body coefficient sets and per-string material/gauge effects. 2. Add three position/aperture/type pickup nodes, phase, enable and parallel/series combination. 3. Add pick-angle/depth envelopes/noise, continuous palm damping/cutoff and 20 ms smoothing; structural changes affect new voices only. 4. Run T-003–T-006/T-013/T-018 and the full suite. 5. Commit/push/verify.
- Outputs: Construction/pickup/articulation DSP; automation and isolated-stage reports
- Evidence produced: T-003, T-004, T-005, T-006, T-013, T-018
- Done when: All listed tests pass, effects are bounded and measurable, zero mute is exact bypass and pitch is independent of fret geometry. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record control-sweep results and commit.
- On failure: Diagnose excitation, decay, pickup then body; revert only the defective step commit. Any public-contract or frozen-test change requires `TEST_CHALLENGE.md` and halt.
- Gate: none
- Relevant decisions/claims: D-002, D-003, D-004, D-005, D-012, D-013; C-006
- Lessons applied: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
- Exclusive resources: none

### S-004 Real-time VST3 integration and host safety
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-003
- Inputs: D-005/D-006; JUCE pin; pluginval pin; VST3/headless targets
- Actions: 1. Connect the same engine to VST3 and headless renderer with preallocated block/max-voice configuration. 2. Add atomic parameter handoff and bounded background coefficient tables; prohibit audio-thread allocation, locks, I/O, logging and APVTS replacement. 3. Add allocation/lock instrumentation, ASan/UBSan and pluginval runs. 4. Run T-014/T-020/T-021 plus full suite. 5. Commit/push/verify.
- Outputs: VST3 plug-in target; host validation, sanitizer and real-time instrumentation reports
- Evidence produced: T-014, T-020, T-021
- Done when: All listed tests and host/sanitizer checks pass; VST3 and renderer outputs match. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record host versions, sanitizer logs and commit.
- On failure: Fix the engine and rerun; never exclude failing host behaviour. Revert the integration commit if the renderer no longer matches.
- Gate: none
- Relevant decisions/claims: D-001, D-005, D-006, D-012; C-007
- Lessons applied: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
- Exclusive resources: audio device/host validation runner

### S-005 Reference analysis and held-out quantitative gate
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-004
- Inputs: `research/audio/REFERENCES.*`; P1/P2 archives; `research/spikes/analyse_references.py`; D-007/D-008
- Actions: 1. Create `scripts/analyse_reference.py` from the committed spike with deterministic alignment/window/band behaviour. 2. Verify source checksums and attribution; download only licensed references outside frozen unit tests. 3. Fit no per-note constants; calibrate only on P1, evaluate P2 held out, and report distribution shift without retuning. 4. Run T-023–T-026 plus full suite. 5. Commit/push/verify reports, not ignored audio archives.
- Outputs: Reference analyser; P1/P2 metric JSON and human-readable report; attribution evidence
- Evidence produced: T-023, T-024, T-025, T-026
- Done when: Reference extraction reproduces frozen values and candidate medians meet D-008; held-out separation is demonstrated. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record dataset checksums, metric hashes and commit.
- On failure: Checksum/licence mismatch writes `BLOCKED.md`; metric miss follows D-012. Never retune on P2 or weaken the threshold.
- Gate: none
- Relevant decisions/claims: D-007, D-008, D-012; C-001, C-002, C-003, C-005
- Lessons applied: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
- Exclusive resources: reference download cache

### S-CI Cross-platform CI, performance and supply-chain gates
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-005
- Inputs: `plan/ENVIRONMENT.md`; D-010–D-012; all source/tests; pinned scanner and runner labels
- Actions: 1. Add `.github/workflows/ci.yml` with the exact six-job matrix, `fail-fast: false`, version reporting and artefact postconditions. 2. Add pinned three-run performance harness and per-runner budgets; run T-017. 3. Run OSV dependency scan, secret scan, pluginval/sanitizer aggregation and licence/checksum checks for T-019/T-021/T-029/T-030. 4. Upload workflow-run reports only after asserting non-empty valid files; push and inspect every required job.
- Outputs: CI workflow; performance, vulnerability, secret, platform and licence reports
- Evidence produced: T-017, T-019, T-021, T-029, T-030
- Done when: Every matrix job passes, all listed tests pass, budgets gate and no failure-swallowing idiom exists. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record workflow run ID, per-platform commits and performance medians/spreads.
- On failure: Persistent performance miss reduces modal count highest-frequency-first down to 12 modes then blocks; Critical/High vulnerability requires a verified fix or halt. Do not rerun indefinitely.
- Gate: none
- Relevant decisions/claims: D-006, D-010, D-011, D-012, D-014; C-008
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: CI workflow run

### S-REVIEW Traditional fresh-context code review
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-CI
- Inputs: Full implementation diff; all A/D/C/T artefacts; dependency release/deprecation notices
- Actions: 1. Use a reviewer who authored none of the code. 2. Review dead/duplicated code, hidden mutation, clarity, complexity, abstraction leaks, path-to-test coverage, hostile memory/file handling, secrets and dependency currency. 3. Classify findings by Rule 4; fix Critical/High before proceeding. 4. Link each finding to a fix commit or accepted R-ID; rerun full suite and push/verify.
- Outputs: `reviews/CODE_REVIEW.md`; fix commits and updated execution log
- Evidence produced: All previously green T-001–T-030
- Done when: Review is complete, every finding is resolved/linked, no Critical/High remains and full suite is green. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record reviewer context, findings and fix commits.
- On failure: New required tests follow unfreeze/research/red/refreeze and cold-read amendment; reviewer may not edit frozen tests directly.
- Gate: none
- Relevant decisions/claims: D-011, D-012
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: none

### S-ADVERSARIAL Adversarial review and misuse probing
- Tier: Fable (Mythos)
- Profile: software; audio=true
- Depends on: S-REVIEW
- Inputs: Full implementation; `plan/ASSUMPTIONS.md`; state/event boundaries; dependency-failure controls
- Actions: 1. Use a fresh reviewer and challenge every code-expressed assumption. 2. Fuzz malformed/truncated/oversized state and events, NaN parameters, voice/resource exhaustion, reset/interruption, extreme automation and dependency failures. 3. Turn each confirmed break into a frozen-test amendment or accepted risk; Critical/High blocks. 4. Rerun full suite and push/verify.
- Outputs: `reviews/ADVERSARIAL_REVIEW.md`; reproduced cases, fixes or risk links
- Evidence produced: All previously green T-001–T-030 plus any amended tests
- Done when: No unresolved Critical/High break; every finding has evidence and disposition. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record attack cases, outcomes and fixes.
- On failure: Stop on data corruption/security/public-interface impact and write `BLOCKED.md`; test changes use `TEST_CHALLENGE.md`.
- Gate: none
- Relevant decisions/claims: D-005, D-006, D-011, D-012
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: none

### S-LISTEN Blind listening and reproducible demos
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-ADVERSARIAL
- Inputs: P2/technique/scale/chord/music references; D-007–D-009; canonical blind-listening skill script; event files
- Actions: 1. Build 12 onset-preserving one-second pairs from clip starts at 44.1 kHz/24-bit, RMS −23 dBFS, 10 ms end fade, base seed 20261104 plus disclosed round; encode the key. 2. Headlessly render single notes across pitch/dynamics, light/medium/heavy palm mute, pick-angle/depth extremes, pickup combinations and construction extremes, scales, chords and a short musical phrase. 3. Run T-027/T-028; create orphan evidence branch, marker commit `[gate-evidence G-LISTEN]`, hashes and delivery URLs. 4. Present G-LISTEN and follow only its recorded branch; maximum three rounds.
- Outputs: Pair set/key, demo event files/WAV/metadata, `GATE-G-LISTEN.md`, evidence branch and URLs
- Evidence produced: T-027, T-028; G-LISTEN result
- Done when: Pair/demo checks pass and human response is proceed, amended proceed-with-rescope, or stop; never claim realism without gate outcome. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record round, seed, score, qualitative findings, evidence commit and branch.
- On failure: Iterate one general mechanism change per disclosed round with a new seed and full tests; after three failed rounds permit only rescope/stop.
- Gate: G-LISTEN
- Relevant decisions/claims: D-007, D-008, D-009, D-012; C-001, C-002, C-003
- Lessons applied: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
- Exclusive resources: listener and evidence branch

### S-RETRO Fresh-context retrospective
- Tier: Opus
- Profile: software; audio=true
- Depends on: S-LISTEN
- Inputs: Execution history, commits, deviations/block/challenge/gate records, CI, prior knowledge, lessons and knowledge
- Actions: 1. Have Haiku collect one digest; fresh Opus reviews records once without rerunning or changing deliverables. 2. Answer every protocol 3.7.1 question, diff workflows/manifests against environment pins, and link every finding to a lesson or knowledge item. 3. Run Appendix C schema checks; commit/push/verify.
- Outputs: `RETROSPECTIVE.md`; any missing `lessons/L-*.md` and `knowledge/K-*.md`
- Evidence produced: none
- Done when: Every finding links to L/K IDs, execution log is complete and schema checks pass. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record retrospective commit and unresolved findings.
- On failure: Do not alter deliverables; record omissions as lessons/knowledge and resolve schema errors before continuing.
- Gate: none
- Relevant decisions/claims: D-012
- Lessons applied: all run lessons
- Exclusive resources: none

### S-KNOW Push lessons and knowledge stores
- Tier: Haiku
- Profile: software; audio=true
- Depends on: S-RETRO
- Inputs: `RETROSPECTIVE.md`; `lessons/`; `knowledge/`; proposed qualitycoding store targets
- Actions: 1. Write `GATE-G-003.md` and halt for target confirmation. 2. On approval copy lessons and knowledge separately into Appendix C layouts, regenerate indexes, commit/push/verify each. 3. On moved targets, pull/regenerate/retry at most three times per store; on no response/failure create `lessons-<run_id>.bundle` and/or `knowledge-<run_id>.bundle`. 4. Append final execution-log entry.
- Outputs: `GATE-G-003.md`; separate store commits/indexes or bundle fallback paths
- Evidence produced: none
- Done when: Approved pushes and indexes are remote-verified, response is do-not-push, or fallback bundles exist and contain the expected refs. Every listed output exists, is non-empty, and parses or passes its stated sanity check.
- Checkpoint: Record store targets, response, hashes or bundles.
- On failure: Never print/store credentials. Retry rejection three times; then use bundle fallback and report it.
- Gate: G-003
- Relevant decisions/claims: D-012
- Lessons applied: L-20261104T014500Z-credentials-in-command-lines
- Exclusive resources: one store at a time
