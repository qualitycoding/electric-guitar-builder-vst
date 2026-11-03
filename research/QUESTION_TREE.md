# Research question tree

## Q0 — Can a separate agent build a controllable electric-guitar VST3 without a named-model preset?
- **Q1 Controls and physics:** Which public parameters, units, ranges and formulas make fret geometry, neck/body material, strings, scale length, pickups and playing controls independently testable? Resolved by D-003/D-004, C-004/C-006 and T-001–T-008/T-013/T-018.
- **Q2 Architecture:** Can one deterministic C++ engine serve VST3 and headless rendering within real-time limits? Resolved by D-001/D-005/D-006, C-004 and T-009–T-022.
- **Q3 Reference:** Which licensed recordings support calibration, held-out evaluation, articulation comparisons and blind listening? Resolved by C-001–C-003, D-007–D-009 and `research/audio/REFERENCES.*`.
- **Q4 Acceptance:** What executable and human evidence distinguishes a regression screen from realism? Resolved by T-001–T-030 and G-LISTEN; metrics alone never establish realism.
- **Q5 Delivery:** Which platforms, tool pins, failure rules and evidence retention make execution resumable without a release? Resolved by D-010–D-012, `plan/ENVIRONMENT.md`, T-029/T-030 and G-003.

No open research question requires an implementer decision. Remaining uncertainty is explicitly carried by A-008/A-009 and the listening gate.
