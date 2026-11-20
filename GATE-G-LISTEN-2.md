# GATE G-LISTEN-2: blind realism and demo acceptance for the amended engine (round 1)

Implementation commit: `3f0d08244ce1dafda02796a98d5cdfd9d803c2b3` on `ccr-8c6ea14a-9nm7iz`. Seed `20261112` (`20261111 + round 1`). Pass condition (frozen in the plan before listening): **no more than 8 of 12 correct** and no unresolved realism finding.

## Read this first

- **Earlier listening rounds (G-LISTEN 1-4) are not comparable.** Their reference clips were built at the wrong sample rate (48 kHz samples written as 44.1 kHz: +1.47 semitones, 8.8% fast; decision D-040). This round is the first with correct references: every reference clip correlates 1.000 with its independently decoded source (`reports/reference_clip_correlation.json`, requirement 0.99).
- The candidate is rendered on the string the reference was played on (D-039). The side holding the reference is drawn from the seed; the key is `pairs/KEY.b64` (base64). **Do not decode it until you have answered.**

## 1. Download

- Everything as one zip: https://github.com/qualitycoding/electric-guitar-builder-vst/archive/refs/heads/gate-evidence/G-LISTEN-2.zip
- Single files: `https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/<path>`
- Play the 12 pairs in order, `pair_N_A.wav` then `pair_N_B.wav`, once each, on your own headphones, then the demos.

## 2. Pairs (1.0 s, 44.1 kHz, 24-bit, -23 dBFS RMS, 10 ms end fade)

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

## 3. Demos (listening copies, one common gain per family, relative levels between settings kept; raw renders and metadata JSON sit beside them)

- **demo_pickup_load**: pot 250k/500k/1M at cable 600 pF (1-3), then 250k at cable 200 pF (4) and 1500 pF (5); gain 28.3 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-4.wav) , [5](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pickup_load-5.wav)
- **demo_body_type**: solid / chambered / hollow (1-3); gain 29.0 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_body_type-3.wav)
- **demo_neck_joint**: bolt-on / set-neck / neck-through (1-3); gain 29.0 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_neck_joint-3.wav)
- **demo_pluck_position**: pluck position 0.08 / 0.18 / 0.30 / 0.45 (1-4); gain 19.4 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pluck_position-4.wav)
- **demo_palm_mute**: palm mute 0 / 0.25 / 0.5 / 0.75 / 1.0 (1-5); gain 28.8 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-4.wav) , [5](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_palm_mute-5.wav)
- **demo_pick_angle**: pick angle 0 / 20 / 40 / 60 degrees (1-4); gain 31.4 dB. [1](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-1.wav) , [2](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-2.wav) , [3](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-3.wav) , [4](https://raw.githubusercontent.com/qualitycoding/electric-guitar-builder-vst/gate-evidence/G-LISTEN-2/demos/a03/listen/demo_pick_angle-4.wav)

## 4. Metrics (frozen thresholds; not relaxed)

- T-023..T-028 and T-040..T-052 pass, 49/49 with the licensed reference cache present (`reports/a03_g_listen2_suite.txt`); CI run `44745950937` on the merge before this round: all 7 jobs success.
- Reference clips vs source: 12/12 >= 0.99 (worst 1.000).
- Feature comparison before listening (`reports/feature_comparison_a03.md`, medians over 8 reference notes): spectral centroid reference 361 Hz, v1 1824 Hz, amended 282 Hz; tail level (1.2-1.5 s vs 0.2-0.7 s) reference -10.8 dB, v1 -6.6 dB, amended -2.6 dB. **The amended notes sustain too strongly at the end and the high bands (above 2 kHz) decay faster than the reference**; listen for a held note that does not die away or a high end that vanishes.
- Demo checks (`reports/a03_demo_checks.txt`): 24 files, peak <= 1.0, settings differ in every pair (62 checks).
- Known weak or symmetric controls (D-041): pick-angle sign has no effect (the model uses |angle|; demo set uses magnitudes); set-neck vs bolt-on differs by -66 dB; chambered vs hollow by -39 dB (solid vs either by -17 dB). Expect these to sound nearly identical.

## 5. Questions (the answer key is not disclosed)

1. For each pair 1-12, which clip is the reference, A or B? (e.g. `ABBA...`)
2. Do any demos sound unrealistic, synthetic, discontinuous, excessively noisy or otherwise unacceptable: which, and at what time?
3. Do the pickup-load, body-type, neck-joint and pluck-position demos change the sound in a way you find plausible?
4. Should the project proceed, iterate, rescope or stop?

## 6. Responses

`proceed` (only with <= 8/12 correct and no unresolved realism finding); `proceed-abx` (run the ABX re-validation before closing); `iterate: <timestamped notes>`; `extend-rounds: <n>`; `proceed-with-rescope: <text>`; `stop`. A listener answer that is the exact complement of the key means a broken bundle and does not count.

Reference attribution: Guitar-TECHS (Pedroza, Abreu, Corey, Roman), Zenodo record 14963133, CC BY 4.0; clips windowed, resampled to 44.1 kHz, loudness-matched and faded; no endorsement implied (`ATTRIBUTION.md`, `research/audio/REFERENCES.json`).
