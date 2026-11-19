# Pre-mortem round 4 (amendment 03)

Separated pass over the plan as amended in round 3 (same tier substitution as round 3).

Scenario: the implementer follows the plan exactly and halts. Walked every halt path: S-000 (missing tool → BLOCKED), S-101 (probe passes → fix job), S-102 (oracle mismatch → TEST_CHALLENGE), S-104 (T-026 → D-034 three iterations then TEST_CHALLENGE), S-105 (gain rule, performance rule), S-106 (CI), S-108 (checksum, correlation), S-LISTEN-2 (demo-difference check, gate branches), S-KNOW (bundle fallback). Every path ends in a defined artefact and does not require a planner answer outside `TEST_CHALLENGE.md`/`BLOCKED.md`.

New findings: none Critical or High. One Low: the D-034 gain rule's −1.5 dB steps could, in principle, attenuate the default patch until T-031's master-gain ratio test fails — no: T-031 measures a ratio between two master-gain settings, which a fixed global constant does not change. Recorded here, no plan change.

Convergence: round 4 finds 0 Critical and 0 High risks. Phase 4 ends.

## Addendum after D-035 (4.7 iteration)

Changed steps S-REVIEW and S-ADVERSARIAL: failure mode 'reviewer unavailable, implementer reviews own code' — Medium, mitigated by D-035 disclosure in the gate bundle. No Critical/High.
