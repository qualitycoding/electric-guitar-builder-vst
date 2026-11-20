# G-LISTEN-2 round 1: diagnosis from the listener's words

Listener: 12/12 correct; non-real clips "synthetic and reed-like"; pick-angle demos "reedy" (`GATE-G-LISTEN-2.RESPONSE.md`).
Method (audio-blind-listening-validation, step 7): measurements on the 12 pairs of the bundle (reference vs candidate, 1.0 s clips), median over pairs. Scripts were run ad hoc from the decoded key; numbers below are reproducible from `pairs/` and `pairs/KEY.b64`.

## Measured differences
1. **Static partials (matches "reed-like").** Residual level modulation of a partial over 0.1-0.85 s after removing a quadratic decay trend (100 ms windows, 25 ms hop): harmonic 1 ref 0.04 dB / cand 0.05 dB; harmonic 2 ref **0.67** dB / cand **0.05** dB; harmonic 3 ref **0.57** dB / cand **0.05** dB. The candidate's upper partials are about 12 times smoother than a real string's. A perfectly steady, strictly periodic harmonic set is what a reed produces.
2. **Brighter, flatter spectrum.** Early harmonic levels re the strongest harmonic (dB, ref | cand): h2 -19 | 0, h3 -34 | -12, h4 -56 | -17, h5 -66 | -39. Spectral centroid 500-1000 Hz (ref) vs 860-1590 Hz (cand) in all 12 pairs.
3. **Uniform decay across harmonics.** Candidate harmonics 1-16 decay at -9 to -17 dB/s with no clear frequency dependence; the reference's harmonics 2-4 decay at -31 to -45 dB/s (higher ones are at the recording's noise floor). Envelope over 0.15 to 0.85 s: ref -10.8 dB, cand -7.6 dB (median), consistent with S-108's tail finding (-2.6 vs -10.8 dB on the T-026 notes).

## Caveats
- The reference recordings' pickup selection is not recorded in `REFERENCES.json` (the dataset covers bridge, neck and bridge-neck configurations), while candidates use the default pickups (25 mm and 65 mm from the bridge, parallel). Differences in harmonic levels in (2) therefore mix engine and configuration effects; (1) and (3) do not depend on pickup position.
- Pick-angle demos sounding reedy at every setting agrees with (1): the polarisation split (D-014, beating 0.10*sqrt(m+1) Hz, periods of several seconds) cannot create modulation inside a 1 s clip.

## What the plan allows next (G-LISTEN-2 branches, D-034)
- `iterate` = one general mechanism change inside D-021..D-028, never editing their coefficients, a new seed (20261113), all frozen tests rerun. Candidate mechanisms that address (1): tension-modulation pitch glide and nonlinear partial coupling (the deferred "stage D" of the G-LISTEN addendum), which lie outside D-021..D-028 and therefore need a recorded amendment request. Candidate mechanisms for (2)/(3): a steeper frequency-dependent string damping term (v1 `modeDecayDbPerS`, outside D-021..D-028 as well).
- `proceed-with-rescope` or `stop` remain available at any gate response.
