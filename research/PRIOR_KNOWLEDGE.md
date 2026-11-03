# Prior knowledge and lesson application

Loaded at R0 from knowledge store commit `e25f1c8a8e0a26850ffb006c8b4275ddf5272899` and lesson store commit `c96e2d87d71cdbc73f4218f19fe6b9fd8dfe4911`.

- JUCE/APVTS: keep stable parameter IDs, validate complete snapshots, never replace the state tree on the audio thread. Applied to D-003/D-005 and T-001/T-011/T-014/T-018.
- Real-time audio: preallocate voices/coefficients, smooth continuous controls, avoid allocation/locks/I/O. Applied to D-005 and T-013/T-014.
- Deterministic offline audio: derive per-voice seeds independently of scheduling and keep normalisation out of production rendering. Applied to D-006 and T-009/T-010/T-020/T-022.
- Reference validation: separate calibration and held-out material; preserve onsets and loudness-match only listening copies. Applied to D-007–D-009 and T-023–T-028.
- `L-20261007T150100Z-no-credentials-in-command-lines`: use environment-scoped credential helpers; never commit/log tokens. Recurred during planning as `L-20261104T014500Z-credentials-in-command-lines`; S-000/S-CI/S-KNOW include prevention.
- `L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects`: short-input filtering and inadequate modal bandwidth can invalidate evidence; S-001/S-004 require causal short-input handling and mode ceilings.

Knowledge gathered this run is in `knowledge/`; corrections are in `lessons/` and travel with the generation branch until G-003.
