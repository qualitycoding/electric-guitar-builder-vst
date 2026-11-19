# Research question tree

## Q0 — Can a separate agent build a controllable electric-guitar VST3 without a named-model preset?
- **Q1 Controls and physics:** Which public parameters, units, ranges and formulas make fret geometry, neck/body material, strings, scale length, pickups and playing controls independently testable? Resolved by D-003/D-004, C-004/C-006 and T-001–T-008/T-013/T-018.
- **Q2 Architecture:** Can one deterministic C++ engine serve VST3 and headless rendering within real-time limits? Resolved by D-001/D-005/D-006, C-004 and T-009–T-022.
- **Q3 Reference:** Which licensed recordings support calibration, held-out evaluation, articulation comparisons and blind listening? Resolved by C-001–C-003, D-007–D-009 and `research/audio/REFERENCES.*`.
- **Q4 Acceptance:** What executable and human evidence distinguishes a regression screen from realism? Resolved by T-001–T-030 and G-LISTEN; metrics alone never establish realism.
- **Q5 Delivery:** Which platforms, tool pins, failure rules and evidence retention make execution resumable without a release? Resolved by D-010–D-012, `plan/ENVIRONMENT.md`, T-029/T-030 and G-003.

No open research question requires an implementer decision. Remaining uncertainty is explicitly carried by A-008/A-009 and the listening gate.

## Q6 — Amendment 03: which parts of the owner's research document change the engine, and with what evidence?
- **Q6.1 Pickup electrics and load** → D-025, T-040/T-041/T-045; C-011, C-012, C-015–C-018.
- **Q6.2 Velocity transduction** → D-026, T-046; C-010.
- **Q6.3 Position, aperture and humbucker sampling** → D-021, T-042; C-013, C-014, C-019–C-021.
- **Q6.4 Neck and body structural loss** → D-022, D-028, T-044; C-023–C-027, C-030.
- **Q6.5 Neck joint, fingerboard, body type** → D-023, D-028; C-028–C-030; R-011.
- **Q6.6 Pluck position** → D-027, T-043; C-022.
- **Q6.7 Correctness of the document's own numbers** → C-013, C-014, C-033.
