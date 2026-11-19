# Prior knowledge and lesson application

Loaded at R0 from knowledge store commit `e25f1c8a8e0a26850ffb006c8b4275ddf5272899` and lesson store commit `c96e2d87d71cdbc73f4218f19fe6b9fd8dfe4911`.

- JUCE/APVTS: keep stable parameter IDs, validate complete snapshots, never replace the state tree on the audio thread. Applied to D-003/D-005 and T-001/T-011/T-014/T-018.
- Real-time audio: preallocate voices/coefficients, smooth continuous controls, avoid allocation/locks/I/O. Applied to D-005 and T-013/T-014.
- Deterministic offline audio: derive per-voice seeds independently of scheduling and keep normalisation out of production rendering. Applied to D-006 and T-009/T-010/T-020/T-022.
- Reference validation: separate calibration and held-out material; preserve onsets and loudness-match only listening copies. Applied to D-007–D-009 and T-023–T-028.
- `L-20261007T150100Z-no-credentials-in-command-lines`: use environment-scoped credential helpers; never commit/log tokens. Recurred during planning as `L-20261104T014500Z-credentials-in-command-lines`; S-000/S-CI/S-KNOW include prevention.
- `L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects`: short-input filtering and inadequate modal bandwidth can invalidate evidence; S-001/S-004 require causal short-input handling and mode ceilings.

Knowledge gathered this run is in `knowledge/`; corrections are in `lessons/` and travel with the generation branch until G-003.

---

# Amendment 03 (run `20261111T150746Z-guitar-physics-research`) — R0

Loaded from lesson store `qualitycoding/lessons` at `9934bb560768cc56b25513e53cae2f743c7b9ef5` and knowledge store `qualitycoding/knowledge` at `af4c5457afd41f2ae8f0d05b184380650f15ddf4`. Matching tags: `domain:audio`, `domain:musical-acoustics`, `tech:juce`, `tech:cpp`, `tech:cmake`, `tech:github-actions`, `applies:all`. 132 active lessons matched (extracted mechanically from the five tag directories plus every `applies:all` lesson, sorted by severity then ID); all were read, and the ones that change this amendment are applied below. The remainder concern other tools (web audio, Mull, VCV Rack, release workflows, streaming APIs) or UI work and are not applicable because this amendment adds no UI, release, mutation-tool or browser work.

## Prevention-rule checklist (cold read and pre-mortem work from this list)

1. **Expected values come from a committed script run on the exact input** (L-20261007T150300Z, L-20261008T151500Z). Applied: every new oracle is produced by `research/spikes/physics_oracle.py` into `research/spikes/physics_expected.json`; T-040..T-046 read it.
2. **Every control-mapping formula is spiked across its full range and its default equals the spike operating point** (L-20261007T150600Z). Applied: `physics_oracle.py` sweeps every new parameter over its range (C-0xx), output committed.
3. **A new acceptance test must fail on the old implementation** (L-20261009T120003Z, L-20261106T120000Z). Applied: red verification of T-040+ against `61ab5ed` is a Phase 2 step with output committed in `tests/RED_VERIFICATION_A03.txt`; the green path is shown on the Python oracle.
4. **Freeze a test together with its executable form** (L-20261004T162211Z) and **account for every file in `tests/`** (L-20261004T150100Z). Applied: the C++ case file implementing T-040+ is listed in `tests/FROZEN_MANIFEST.sha256`; a `find tests -type f` listing is committed with the freeze. The v1 gap (case logic in `src/contract_main.cpp` was never hashed) becomes risk R-008.
5. **Sketch an implementation against a header before freezing it; compile JUCE code against pinned headers** (L-20261004T150400Z, L-20261008T173536Z, L-20261009T092006Z). Applied: `include/egb/Physics.h` is frozen only after a reference sketch compiles and passes the oracle tests in a planning spike.
6. **Re-derive constants from the cited measurement; check table orientation and factors** (L-20261009T120009Z, L-20261009T120004Z). Applied directly: the research document's aperture and humbucker tables disagree with its own formulas by ×2 (rejected claims C-013, C-014).
7. **Cite only sources opened in this run, with locators; count distinct publishers for `corroborated`** (L-20261009T120015Z, L-20261009T123005Z, L-20261004T102001Z, L-20261009T092004Z). Applied to `research/claims.json` and the round logs.
8. **Validate every DSP measurement on a synthetic signal with a known answer** (L-20261004T162214Z, L-20261009T120008Z). Applied: each new measurement helper in the case file has a synthetic self-check case (T-047).
9. **Numeric targets are set after measuring; frozen metrics must not cap the property under listening** (L-20261009T120011Z, L-20261106T180100Z, L-20261007T150400Z). Applied: T-026's reference thresholds are re-evaluated on the amended engine before G-LISTEN-2 (S-108), and numeric bounds in T-040+ are oracle-derived tolerances, not realism targets.
10. **Gain staging: the shipped path must stay ≤ 0 dBFS; print unclipped peaks** (L-20261008T173530Z, L-20261009T120001Z). Applied: velocity transduction adds +6 dB/octave, so T-009 and T-039 are re-run on the amended engine and a new worst-case load test (T-045) covers hollow body, series humbuckers and 1 MΩ load.
11. **Audio thread: no lock, allocation or wait** (L-20261009T161100Z). Applied: new coefficients are computed at voice start or parameter-snapshot time; T-014 re-runs.
12. **Listening: verify reference clips against sources; 12 pairs cannot steer iteration; compare features before round 1** (L-20261106T010000Z Critical, L-20261106T180300Z, L-20261106T180200Z). Applied in S-LISTEN-2: correlation ≥ 0.99 of each reference clip with its source, feature comparison report before round 1, no score-difference interpretation between rounds.
13. **Amendment batches leave stale wording** (L-20261107T201002Z). Applied: a stale-phrase grep (`fixed at 18%`, `pickupSpec`, `3500 Hz`, `schemaVersion=1` as current) is part of the 3.6 mechanical check.
14. **British English for all prose** (L-20261102T232000Z). Applied.
15. **Probe hosts at the start of each step needing them; give downloads a human fallback** (L-20261105T220500Z). Applied to S-000 and S-LISTEN-2.
16. **Stores probed, not defaulted** (L-20261027T121000Z, L-20261101T042300Z, L-20261022T120000Z). Applied: both stores were reached and their commits recorded above and in `state.json`.

## Knowledge items used

- `standard-guitar-tuning` (open-string frequencies) — seeds C-009 (E2 = 82.41 Hz used in the document's tables).
- `modal-resonator-implementation` (two-pole resonator impulse response) — informs D-021 (structural loss is applied as per-mode decay, not as an extra resonator).
- `frozen-test-manifest` (manifest must be re-frozen in the same change and checked in CI) — informs R-008 and S-101.
- Project items `K-20261104T020100Z-modal-guitar-spike` and `K-20261104T020000Z-guitar-techs-reference-separation` — the engine architecture and reference separation are unchanged.
