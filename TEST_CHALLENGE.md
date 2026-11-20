# TEST_CHALLENGE: T-027 pair builder (frozen file src/contract_main.cpp, `t027`)

Raised by S-108 step 4 (reference-clip correlation) on branch ccr-8c6ea14a-9nm7iz. Halting per 2E.4 / DR-04: the defect is in a hashed file, which is not modified.

## Item
T-027 (D-009): "12 one-second onset pairs ... 24-bit/44.1 kHz". Code: `src/contract_main.cpp` lines ~1672-1675 and 1685-1700.

## Evidence
- `P2/audio/directinput/directinput_allsinglenotes.wav` is 48000 Hz (soundfile info, 2 channels, 24-bit).
- `t027` copies `fsOut = 44100` consecutive source samples (`refClip[k] = ref.samples[rs + k]`) and writes them with `writeWav24(..., fsOut)`. No resampling.
- Result: the reference side plays 48000/44100 = 1.0884x fast (+1.47 semitones, 8.8% shorter in time, 0.919 s of source instead of 1.0 s). The candidate side is rendered correctly at 44100 Hz, so every pair differs in pitch and speed by construction.
- `reports/reference_clip_correlation.json`: correlation of each pair's reference side with its source decoded independently (soundfile) and resampled to 44.1 kHz is 0.008-0.071 for all 12 pairs; the S-108 requirement is >= 0.99. Against the source samples relabelled as 44.1 kHz it is 1.0, which confirms the decode itself is exact and only the rate label is wrong.
- The reference side of earlier gate rounds (G-LISTEN rounds 1-4) is built by the same code.

## Why it matters
Listeners compared a reference 1.47 semitones sharp and fast against the candidate. G-LISTEN round 4's "reversed discrimination direction" (5/12, listeners found the reference side less realistic, D-16 caveat) is consistent with this artefact and should not be read as evidence about the engine. D-031's rule against issuing a round with a broken decode applies.

## Proposed fix (for the planner)
In `t027`, resample the reference window from `ref.fs` to `fsOut` (take 1.0 s = `ref.fs` source samples, polyphase 147/160 for 48 -> 44.1 kHz or a generic rational resampler) before RMS normalisation and the fade; add a check in the test that each written reference clip correlates >= 0.99 with an independent decode of its source window (the Python check in this repository's S-108 report reproduces it). Re-hash the manifest in the amendment. S-LISTEN-2 must not issue a round before this is fixed; the G-LISTEN verdict caveat in D-16 should be re-examined.
