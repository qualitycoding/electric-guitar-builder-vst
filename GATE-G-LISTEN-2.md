# GATE G-LISTEN-2: blind realism and demo acceptance for the amended engine (round 2)

Implementation commit: `08d8270380288c21e3921392f95a1a019fe9177c` on `ccr-8c6ea14a-9nm7iz`. Seed `20261113` (`20261111 + round 2`). Pass condition (frozen before listening): **no more than 8 of 12 correct** and no unresolved realism finding. Round 1 (12/12 correct) is kept in `round-1/`; its answer key has been revealed, so this round uses a new seed and new pairs.

## What changed since round 1 (D-042)

You described the non-real clips as synthetic and reed-like. Measurements on the round-1 pairs showed the candidate's upper partials were almost perfectly steady (level modulation 0.05 dB for harmonics 2 and 3) where the real recordings wobble by about 0.6 dB. One mechanism was changed: the two string polarisations of every partial above the fundamental now beat at 1 Hz (they beat every several seconds before), with the fundamental unchanged. On the 12 pairs the candidate's harmonic 2 / 3 modulation is now 1.15 / 0.94 dB (reference 0.67 / 0.57; `reports/feature_comparison_a03.md`). **This removes a measured difference; whether it removes the reed-like impression is what this round tests.**
Not changed, still different from the references: the candidate is brighter with a flatter spectrum (harmonic 3 about -12 dB vs -36 dB re the strongest harmonic), its harmonics decay at nearly the same rate while the reference's upper harmonics die much faster, and the notes sustain too strongly late (tail -3.8 dB vs -10.8 dB). The reference recordings' pickup selection is unknown. If you still pick the references, please say what gives them away now.

## 1. Download

- Everything as one zip: https://github.com/qualitycoding/electric-guitar-builder-vst/archive/refs/heads/gate-evidence/G-LISTEN-2.zip
- Single files: `https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/<path>` (round 2 is at the root of the branch)
- Play the 12 pairs in order, `pair_N_A.wav` then `pair_N_B.wav`, once each, then the demos. The side holding the reference is in `pairs/KEY.b64` (base64): **do not decode it until you have answered.**

## 2. Pairs (1.0 s, 44.1 kHz, 24-bit, -23 dBFS RMS, 10 ms end fade; every reference clip correlates 1.000 with its source)

- pair 1: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_1_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_1_B.wav
- pair 2: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_2_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_2_B.wav
- pair 3: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_3_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_3_B.wav
- pair 4: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_4_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_4_B.wav
- pair 5: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_5_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_5_B.wav
- pair 6: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_6_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_6_B.wav
- pair 7: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_7_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_7_B.wav
- pair 8: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_8_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_8_B.wav
- pair 9: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_9_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_9_B.wav
- pair 10: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_10_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_10_B.wav
- pair 11: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_11_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_11_B.wav
- pair 12: https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_12_A.wav , https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/pairs/pair_12_B.wav

## 3. Demos (listening copies, one gain per family, relative levels kept; raw renders and metadata beside them)

- **demo_pickup_load**: pot 250k/500k/1M at cable 600 pF (1-3), 250k at 200 pF (4) and 1500 pF (5); gain 28.1 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-4.wav) , [5](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-5.wav)
- **demo_body_type**: solid / chambered / hollow (1-3); gain 28.9 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-3.wav)
- **demo_neck_joint**: bolt-on / set-neck / neck-through (1-3); gain 28.8 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-3.wav)
- **demo_pluck_position**: pluck position 0.08 / 0.18 / 0.30 / 0.45 (1-4); gain 19.2 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-4.wav)
- **demo_palm_mute**: palm mute 0 / 0.25 / 0.5 / 0.75 / 1.0 (1-5); gain 28.8 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-4.wav) , [5](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-5.wav)
- **demo_pick_angle**: pick angle 0 / 20 / 40 / 60 degrees (1-4); gain 30.9 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-4.wav)

Please listen again to the pick-angle demos, which you called reedy in round 1.

## 4. Metrics

- 50/50 frozen tests pass (release, reference cache present; ASan and UBSan 48 tests each, 0 findings): `reports/a04_s109_suite.txt`; new T-053 checks the partial modulation (red before D-042, green after).
- Demo checks: 24 files, settings differ in every pair (`reports/a03_demo_checks.txt`). Known weak controls (D-041): set-neck vs bolt-on -66 dB, chambered vs hollow -39 dB.

## 5. Questions (key not disclosed)

1. For each pair 1-12, which clip is the reference, A or B?
2. Do any demos sound unrealistic, synthetic, discontinuous, excessively noisy or otherwise unacceptable: which, and at what time? Do the clips you identify as not real still sound reed-like?
3. Do the pickup-load, body-type, neck-joint and pluck-position demos change the sound plausibly?
4. Should the project proceed, iterate, rescope or stop?

## 6. Responses

`proceed` (only with <= 8/12 correct and no unresolved realism finding); `proceed-abx`; `iterate: <notes>` (round 3 is the last round unless `extend-rounds: <n>`); `extend-rounds: <n>`; `proceed-with-rescope: <text>`; `stop`.

Reference attribution: Guitar-TECHS (Pedroza, Abreu, Corey, Roman), Zenodo record 14963133, CC BY 4.0; clips windowed, resampled to 44.1 kHz, loudness-matched and faded; no endorsement implied.
