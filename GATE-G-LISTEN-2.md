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

## 7. Evidence record

Branch `gate-evidence/G-LISTEN-2`, marker commit `b652ac02dfd3b3839246e65139409bc7ba71da83` ([gate-evidence G-LISTEN-2] round 2); zip verified with `sha256sum -c SHA256SUMS` (0 failures). Hashes of the pairs and listening copies:

```
0211d25c6622812fbfa775ad902203728ab11989846226c00986a9c2c210907d  demos/a03/listen/demo_body_type-1.wav
7f5d113fe45028d7bb27d536ffb317cc157b1dec3fa87c296e18e07d9cb88bc5  demos/a03/listen/demo_body_type-2.wav
e6db02eec21fb3670e3b83e2b2b64d2397adbee012a184f5933c704f88bad076  demos/a03/listen/demo_body_type-3.wav
0c9af2dd3195dbd57e5558e0be8caf74ae44e7b29f9e45c1c82d234d6b59b727  demos/a03/listen/demo_neck_joint-1.wav
e0f92f781dd55070950e6eda58fa68efcc416b84ab3440b06ace87ee0d967280  demos/a03/listen/demo_neck_joint-2.wav
27082fd5683ed0b5b51204cd0c485b5af8f7701cc53111b3fc58e748b89c9a3d  demos/a03/listen/demo_neck_joint-3.wav
19bbb4d533e554107170817f350006dfed1ddba4198ebc6c21bca4921cb885e8  demos/a03/listen/demo_palm_mute-1.wav
ac9c953a0b1a61c0f13b222e26b81710845bef403b958a43b1ef027f0c93ac21  demos/a03/listen/demo_palm_mute-2.wav
8771b7e2726a1f301618d7ad5ad9485c66b51235c44890ac57e0d2f8c6f9d776  demos/a03/listen/demo_palm_mute-3.wav
e874fd61971b909aa71d2f6fb459e896b043f951b4e3dc8cf4c30955be7286d4  demos/a03/listen/demo_palm_mute-4.wav
f44b14abff0d428780ee325e05d94eee4056321138791d7cb73e6426d46a1d5d  demos/a03/listen/demo_palm_mute-5.wav
24a842d49844ae0195186a9eecd4313d105b1269b2d80401733c9f0c06cfdaf7  demos/a03/listen/demo_pick_angle-1.wav
23a5eb27cdc58476a03c2f8cecb04f1944d493ddf139bc84f20382ceca587dcc  demos/a03/listen/demo_pick_angle-2.wav
83caa025e9c41d5a3e082e543539de2586a8ba26d055782c5ca207a008b533fa  demos/a03/listen/demo_pick_angle-3.wav
abb78cee8c258a416ef14309ee2703b641fbba8a9f65af451795c825c2e03a37  demos/a03/listen/demo_pick_angle-4.wav
559e089c064c3a04d50e8df61c058e383e4cee4b98de1367535550526b7a95da  demos/a03/listen/demo_pickup_load-1.wav
ceebe292a7d1b77df51a09e4ea41d174482378d3209bb05c4ef8af19a32cae94  demos/a03/listen/demo_pickup_load-2.wav
707a9160ecbe340ae61f352f2a2da1eb512a408bbf6c7fffb6311ee6bf3e925d  demos/a03/listen/demo_pickup_load-3.wav
f6c5f4935199f657d6fecbd434d636a95eb21a5de8f62126807c2f4f00d78d7f  demos/a03/listen/demo_pickup_load-4.wav
0a07a06d2d7a225139fd4dff9d9088bd2125725a2fa73807470c0f77dc896589  demos/a03/listen/demo_pickup_load-5.wav
0ccfb2648cb9af6c6322d62a44e01bf84037f1a46aa47251fda1f4d2e0a13855  demos/a03/listen/demo_pluck_position-1.wav
4027610765557746a8f6f6f415696b86af1e63ef492af0eee3c3822f9f88f63e  demos/a03/listen/demo_pluck_position-2.wav
3696b07e6d74006c740b74976398b8616855c10fcdfea55f656efcddcf5c6626  demos/a03/listen/demo_pluck_position-3.wav
ae08df728c43e3cb652b073884a313f6196270f9b17085af1cb89f7393085071  demos/a03/listen/demo_pluck_position-4.wav
ef161ea997b5cb5555094ef8f21cb31e4895f189153fe2fef24eb3029bcf51dc  demos/a03/listen/GAINS.json
e6586c3213a7e9be9d791026d5b7f89655741960ff2b881b46af9f1e00e5d6aa  pairs/pair_10_A.wav
b4d7089fa26542e59e0af7ce7938a4de7fe34e9cd927789690b514800cfe14e8  pairs/pair_10_B.wav
71bff6c1517a9232012a88ee4a93e11703619d66e7fe89acfcd37d9dd2601971  pairs/pair_11_A.wav
764059e572f15effb95530c305f83c6ed36c88d05fa0ae953dd5181abe5856c8  pairs/pair_11_B.wav
a77d27725bca4968a0117b3c58df98bbf0eb5d4879a352bcbf6add6cc92ac4b1  pairs/pair_12_A.wav
d555c72df4da44c3681aeaef5ebda2d6768279c85de174e61f50f5fd16e31ea2  pairs/pair_12_B.wav
100b87110111325a62da2cbc9121ef0f0b425a5db521b37328433f8bfea7b7c5  pairs/pair_1_A.wav
d3e1af55827862fb3c51ea03c01674281a1fbda7864dbf302fc984c324e1f722  pairs/pair_1_B.wav
0be5478b27ab9e22c235ee6a286dd72d44cd22f49849f7394fd928aaca4f43e3  pairs/pair_2_A.wav
40a8f7ad5dab58391bc3ca0851f10f1b847d004bf4359cd8e6b5be1a64309606  pairs/pair_2_B.wav
22f023e9240d57c6d962714b778c2f1fef05cb80649f4d17b2d0489e6e75701b  pairs/pair_3_A.wav
781d2485bb1682f4e64626091e09f95c12d554fa86b938ea4e2b79912e07f77c  pairs/pair_3_B.wav
33f9377e5059f9cc82b1b551a3bc95dad67e6a16affc212593a32636ab0d4d4a  pairs/pair_4_A.wav
67b538aecc80ffd4cece7193ad1aef2f00f12bb3ea9ec666b50bee8b5ec3810d  pairs/pair_4_B.wav
c5a6d6d5f43bb40cb9a066a62abcfafc5770d859c40e7ffcef129536f57a5de2  pairs/pair_5_A.wav
c196a46c02f520814e2558b8abf5dcc56d369aeb38941710d524ed9f115112e9  pairs/pair_5_B.wav
32bfc03eccbf14f871ac32e8a7d8c02861506d1d44f7735ad777a8f4013507ff  pairs/pair_6_A.wav
a43bb72f81fcf1caba4a7eae739ae09330d1b587b11bc6220724feee07d06c5f  pairs/pair_6_B.wav
8e815c27aa4f3ff217091ce56e713d2eb85908962623f57e20e85cc7cf12b478  pairs/pair_7_A.wav
6576abdd87e6fe7e1def0e7563706712b6c0463cbc72f65856dbdb721f247de7  pairs/pair_7_B.wav
a4313f232539031d4c0edc45bc7412918f35b79316b9f47d11747b61b5c04cc1  pairs/pair_8_A.wav
bcef09f2b9822fc0681f5c396110ef6b1ad056606ffafc08c7fa68fc629fdbf6  pairs/pair_8_B.wav
e431579399e0708bc1c71e555454de923da7f1ef95314616425d2b28ecb52faf  pairs/pair_9_A.wav
7ac2bb4969affeb373af315b1ee18599faf25693e7a90de5d6c1864551530c4a  pairs/pair_9_B.wav
```
