# TEST_CHALLENGE — T-048 premise contradicts the v1 channel/string rule

Raised by the implementing agent at S-104 (2026-11-19T20:37:00Z). No hashed file was edited.

**Test:** T-048 (`tests/physics/physics_cases.cpp` `t048`, hashed). It renders `noteEvents(45, 100, 1.6)` for `bodyType` 0 and 2 and requires the measured 110 Hz decay difference to be at least half of `integration.body_hollow_minus_solid_A2.predicted_delta_db_s` (6.5976 dB/s, W = 0.7346 kg/s).

**Premise that fails:** `research/spikes/physics_oracle.py` states that MIDI 45 "is allocated to string index 4 (open A, gauge 0.036) by the engine's first-fit rule". The test's events carry channel 1 (`noteEvents`: `note_on 45 100 1`). D-013 (plan/DECISIONS.md line 106, implemented at `Engine::Impl::noteOn`) says an event on channel 1-6 *uses that string*; first-fit applies only to other channels. Channel 1 is string index 0 (high E, 0.010 in), so the engine plays 110 Hz on that string at fret -19 (tension 8.08 N, W = 0.057 kg/s). Structural decay there is 0.51 dB/s hollow versus 0.011 solid, so the measured difference is 0.5 dB/s, below the 3.3 dB/s threshold.

**Evidence the physics is wired correctly (D-034 first bullet does not apply):**
- `debugModeTable` for string 4, fret 0 gives structural 6.755 dB/s hollow versus 0.149 solid for mode 1: a 6.6 dB/s difference, equal to the oracle's prediction. The voice and the table share `forEachMode`.
- The voice built for channel 1 prints structural 0.0111 (solid) and 0.5169 (hollow) on string 0 fret -19; these equal `structuralDecayDbPerS` for that string's W.
- Rendering the same note on channel 7 (first-fit, string 4) separates hollow from solid by about 4-5 dB over 0.6 s at 110 Hz (power, Goertzel), in line with 13 dB/s power for a 6.6 dB/s amplitude difference.

**Options:** (a) amend the events in T-048 (and `noteEvents` use for it) to a channel outside 1-6 or channel 5, which is string index 4, then re-hash; (b) if the owner wants engine behaviour changed so a note below a string's open pitch is rejected or re-allocated, record that as a v1 amendment, which would also touch other frozen tests. Option (a) is the smaller change. T-046's pluck check also uses channel 1 on string 0, but it passes and does not depend on W.

**State:** S-104 code is complete and committed (T-046 passes; T-048 red because of the premise above). S-105 not started. T-035 is red until S-105 for a separate expected reason (see reports/a03_s104_suite.txt).
