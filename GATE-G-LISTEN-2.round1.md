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

## 7. Evidence record

Orphan branch `gate-evidence/G-LISTEN-2`, marker commit `50e39293bf0c321b3de1196194d9910f71a15a54` ([gate-evidence G-LISTEN-2] round 1), 108 files, verified from the downloaded zip with `sha256sum -c SHA256SUMS` (0 failures).

SHA-256 of the pair and demo files (full list in `SHA256SUMS` on the branch):

```
c5a1d9d25b49cd2bdd685689beff42365cdfd0a08cd228f29ba69d690a76266b  demos/a03/listen/demo_body_type-1.wav
7f5987f9a4c1b30373e8b8ffb33b651afd33d3a50819cf20187e70096b4f9f7f  demos/a03/listen/demo_body_type-2.wav
161d09e71eaf298fb95f856d21a7593b9ee6b67d48ba3ef97bebfdae3af842c1  demos/a03/listen/demo_body_type-3.wav
e52d9cf6677ab5446e1fb708670c4b4a1d6f8c86dffcd502b4fa7f6c66d00c03  demos/a03/listen/demo_neck_joint-1.wav
6be270757e3ee856d125c57e9abdd067880df90e02bb546f6acb34dc8daf2018  demos/a03/listen/demo_neck_joint-2.wav
3847c163c069c0e31e33b7cb4d01c18b852eca3c80b983f2a8bf33cad0a25f56  demos/a03/listen/demo_neck_joint-3.wav
6c841e27dda1f257b62170eae6522e9aa4d7b6b8ba9eae8aba0e1e85e51b032b  demos/a03/listen/demo_palm_mute-1.wav
2f39ee6bd7be02d7879b2ba5ed8147bba4a902e29c1e83bb535cad0aa589b7e6  demos/a03/listen/demo_palm_mute-2.wav
36068ba63f08936b27097bfe7775f96037fa9ca5b0ed1ab6b84e6e9469bfa460  demos/a03/listen/demo_palm_mute-3.wav
ae8aa16a3b228395e5fab6658db0bd766bf6b42d61e6246f5ead7545e2a6e204  demos/a03/listen/demo_palm_mute-4.wav
f342536b97cd97bcb309b35e72f273375ba5752585eb079df5ced6ec48f15c9e  demos/a03/listen/demo_palm_mute-5.wav
edfe40c974906a46d1114f4a58c3ec0a8b6b789299e094f902066f829c32789b  demos/a03/listen/demo_pick_angle-1.wav
9e8aee3ace3bd713351038aa08d7d3512952e345a38b2f64ba9183fe1c436542  demos/a03/listen/demo_pick_angle-2.wav
dc36b684205e387f021bb7bc01079fd334a8a2e4389e90ebe0984fefd3c01ac9  demos/a03/listen/demo_pick_angle-3.wav
e27eb2e81f59fb1df12ee0e2ef4c3fc01ba822b6ad39499b7bbb83a7a86d24b4  demos/a03/listen/demo_pick_angle-4.wav
8762bfaee260d1b35afe1caecd3e1bc9b2df393a566cacb22d873b9c79cf88b8  demos/a03/listen/demo_pickup_load-1.wav
a72544271945ee4583d5c7647d761b8630d4fec7a83711dd0b0e57eb77b175d7  demos/a03/listen/demo_pickup_load-2.wav
40c15dfa1c9cc797981853f1d8c6c1eecadaa7fe02e861561bfab3ed06d3974a  demos/a03/listen/demo_pickup_load-3.wav
b671cf3aae9f5caa39d4105d40852f53e9147817fbc8051f585fd5b4724d3479  demos/a03/listen/demo_pickup_load-4.wav
ea45f866903ab15e8fd5f86f8ef0668f99c897b5e4b3299ba7ad6726c47cc185  demos/a03/listen/demo_pickup_load-5.wav
1762b5da20c7c9e64273b0b1d16db23fe6bd2c8075b425fe3e89944249ba6e94  demos/a03/listen/demo_pluck_position-1.wav
7017b6f10409b0ffbd11df5fa1c20b255a6e560cfd978154a200313d87fb8be6  demos/a03/listen/demo_pluck_position-2.wav
91af8e46d979ca28903ccdfc994fefe73f13872f6a946bd633c616ee90fcdda1  demos/a03/listen/demo_pluck_position-3.wav
b6d9838ce1a7a1594c0eeb01bea47358f35f503936799aba51482c64e293c49c  demos/a03/listen/demo_pluck_position-4.wav
11659f7e98caf936eff4890e092b07ea4dbd0a061f31129998acf44e5117430d  demos/a03/listen/GAINS.json
e6586c3213a7e9be9d791026d5b7f89655741960ff2b881b46af9f1e00e5d6aa  pairs/pair_10_A.wav
5567d793c0bfe8aea2aebe3d860abe56fc206c8815bfda09362bff7199ccc96d  pairs/pair_10_B.wav
89083b573a31a26700a1d55ce1145672ab6220a9820a463e7c854e9ccc7c651d  pairs/pair_11_A.wav
764059e572f15effb95530c305f83c6ed36c88d05fa0ae953dd5181abe5856c8  pairs/pair_11_B.wav
4172e0f501e150fcbd9322786d2ffd374ca559c03ee250c69684158cce065acc  pairs/pair_12_A.wav
a77d27725bca4968a0117b3c58df98bbf0eb5d4879a352bcbf6add6cc92ac4b1  pairs/pair_12_B.wav
100b87110111325a62da2cbc9121ef0f0b425a5db521b37328433f8bfea7b7c5  pairs/pair_1_A.wav
c871744f57a70b43a5222637702de484087ff768ba8c9ef01ba7269d04448253  pairs/pair_1_B.wav
40a8f7ad5dab58391bc3ca0851f10f1b847d004bf4359cd8e6b5be1a64309606  pairs/pair_2_A.wav
f442a4fdfc9579d252de5aa6d7ec845eb4b33baa128607535f659e1dce3e2796  pairs/pair_2_B.wav
22f023e9240d57c6d962714b778c2f1fef05cb80649f4d17b2d0489e6e75701b  pairs/pair_3_A.wav
6b7c1db1d42d073be44aa4a0d5b5f5176a52e7e116525d9c7a064941dbd3d160  pairs/pair_3_B.wav
67b538aecc80ffd4cece7193ad1aef2f00f12bb3ea9ec666b50bee8b5ec3810d  pairs/pair_4_A.wav
ae98e51bb911cb51a29d2fd68a99eeaa4d1e5198aa7d11fd103a9a1de42d89b6  pairs/pair_4_B.wav
c5a6d6d5f43bb40cb9a066a62abcfafc5770d859c40e7ffcef129536f57a5de2  pairs/pair_5_A.wav
bbc536daeabbf976b3f0ee496d06c3e7b2722bcab6f1f7baf40988ec45659b54  pairs/pair_5_B.wav
a43bb72f81fcf1caba4a7eae739ae09330d1b587b11bc6220724feee07d06c5f  pairs/pair_6_A.wav
ec2c9e3ba6108c2991298fe6fb6ff020e26d78fffcf708114ed73f6db3c85321  pairs/pair_6_B.wav
6576abdd87e6fe7e1def0e7563706712b6c0463cbc72f65856dbdb721f247de7  pairs/pair_7_A.wav
fdbd4d64a4942c0e72475c49a151041cf5eb35e179ce3dd590d901424d5d4396  pairs/pair_7_B.wav
bcef09f2b9822fc0681f5c396110ef6b1ad056606ffafc08c7fa68fc629fdbf6  pairs/pair_8_A.wav
eee0641fa766aa548db448cbcb0434608c65efca30791f5288924e1321a1d391  pairs/pair_8_B.wav
2abae5a332e428cd02816e0f69aab8a1bc03b65f21659d4202bf15022be1a168  pairs/pair_9_A.wav
e431579399e0708bc1c71e555454de923da7f1ef95314616425d2b28ecb52faf  pairs/pair_9_B.wav
```
