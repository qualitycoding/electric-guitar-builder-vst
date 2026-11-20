# Frozen test record

- v1 freeze (run 20261104T013000Z): `tests/test_contract.py` T-001..T-030, fixtures, `research/spikes/expected_values.json`.
- Amendment 03 (run 20261111T150746Z-guitar-physics-research, D-030):
  - **Retired:** T-001 (35-descriptor contract) and T-011 (schemaVersion 1 round trip) — the amendment changes both contracts. Superseded by T-049 and T-050; their methods are removed from `tests/test_contract.py` and replaced by a RETIRED comment (L-20261009T161300Z).
  - **Retired:** T-032 (amendment test) — premise falsified by the D-021 humbucker sampling (planning prediction 0.76 < 1.4); superseded by T-040, T-041, T-045.
  - **Amended in place (D-036):** T-022 metadata parameter count 35 → 42 (`src/contract_main.cpp:1200`), after the implementer's TEST_CHALLENGE at S-103.
  - **Amended (D-037):** T-048 and the T-046 pluck render play on channel 5 (string index 4); T-035's resonance check replaced by an oracle-predicted band-energy shift; `physics_expected.json` gains `integration.t035_series` (other values byte-identical).
  - **Amended (D-038):** T-021 reads the expected sanitizer test set from the hashed test files (all except T-017 and T-021) instead of the literal `Ran 30 tests`; `scripts/bootstrap_sanitizer_logs.sh` removed, `scripts/run_sanitizer_suites.sh` rewritten.
  - **Amended (D-039):** T-007 (allocated-string gauge), T-027 (reference string channel; seed from `pairs/SEED.json`), T-035 and T-045 (Hann band measurement; T-045 modal predictions), T-037 (direction and threshold), T-047 (60 dB dynamic-range case); **added** T-052 (fret-checked channel rule).
  - **Added and frozen:** `tests/test_physics.py` (T-040..T-051), `tests/physics/physics_cases.cpp`, `tests/physics/state_v1.xml`, `research/spikes/physics_expected.json`, `include/egb/Physics.h`.
  - **Amended (D-040):** T-027 resamples the reference window from the recording's rate (48 kHz) to 44.1 kHz and asserts every written reference side correlates >= 0.99 with an independent decode of its source (`src/contract_main.cpp`, `resampleWindow` and the check after "12 pairs written").
  - **Newly hashed (R-008):** `tests/test_amendment.py` (T-031..T-039) and `src/contract_main.cpp`, which holds the executable logic of T-002..T-039; until this amendment only the Python wrappers were hashed.
- Verification: `sha256sum -c tests/FROZEN_MANIFEST.sha256`, run in CI by the `frozen-manifest` job added in S-101 (D-032).
