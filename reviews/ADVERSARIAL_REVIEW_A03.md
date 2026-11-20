# Adversarial review, Amendment 03 (S-ADVERSARIAL)

Harness: `research/spikes/adversarial_a03.cpp` (links `egb_core`, release build at the S-REVIEW fix commit); output `research/spikes/adversarial_a03_output.txt` (414 ok, 1 break line).
Reviewer: same session as S-106/S-REVIEW (owner instruction); independence reduced, as noted in `reviews/CODE_REVIEW_A03.md`.

## Attacks and results
| Area | Attack | Result |
|---|---|---|
| Electrics | fs 2000/8000/22050/44100/48000/96000/192000 x 3 pickup types x cable 0 and 2000 pF x amp 0.05 and 10 MOhm x pot 250k and 1M x parallel/series, 16 voices, all pickups on | 336 cases, output finite, peak <= 1.0 (tanh stage) in every case. The 0 pF / 10 MOhm / 96 kHz case from the plan is included. |
| Filter stability | pole-radius sweep over the full accepted rate range (2 kHz..384 kHz) and parameter corners | worst radius 0.9971 after the F-01 fix (was 1.44 before it, see CODE_REVIEW_A03 F-01) |
| Structure | pluck 0.05 and 0.5 x 3 bodies x 3 joints x 3 fingerboards at 16 voices | 54 cases finite, peak in (0, 1] |
| Automation | cable/pot/amp toggled every block at block size 1 (20000 blocks) and 2048 (40 blocks), notes retriggered | finite output both |
| Validation | NaN, -tiny, 0, inf, denormal, out-of-range choice values for the seven parameters | all rejected by `ParameterSnapshot::validate` |
| State fuzz | schemaVersion '2abc', 3, 0; missing v2 ID; 'nan'; '1e999'; hex-float; unknown ID; v2 payload labelled v1; child element; empty/short/0xFF junk; truncations every 7 bytes | all rejected or crash-free, state unchanged, except B-01 |

## Breaks
| ID | Severity | Break | Disposition |
|---|---|---|---|
| B-01 | Low | State attribute `body_type="1.5"` is accepted as 1: `juce::XmlElement::getIntAttribute` truncates non-integer text, so the snapshot's integer check never sees a fraction. The same applies to every integer attribute since v1 (neck_material, pickup types and others). Result is a valid in-range value, no memory or numerical hazard. | Accepted risk, Low. Not corrected: a stricter parse would change v1 state behaviour (frozen T-020/T-036 premises) and needs a planner amendment if the owner wants it. |

Counts: Critical 0, High 0, Low 1 (accepted). No Critical/High open; no new frozen tests required.
Not attacked: pluginval and host automation through a real VST3 host (unavailable here, v1 D-8).
