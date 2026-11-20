# Feature comparison before listening (S-108, Amendment 03)

Candidate set: T-026 (MIDI 40/45/64 x velocity 45/85/125, default parameters, 1.6 s note, 48 kHz). Reference: P1 direct-input notes with the same MIDI numbers and velocity >= 100 (8 notes), onset from `scripts/analyse_reference.py`.

Measures: centroid over 0.2-0.7 s (Hann, 32768-point FFT); 21 one-third-octave bands from 100 Hz, decay slope in dB/s from a linear fit of the band envelope over 0.2-1.2 s; tail level = RMS(1.2-1.5 s) / RMS(0.2-0.7 s) in dB. Medians over notes.

| Measure | Reference | v1 (61ab5ed) | Amended |
|---|---|---|---|
| Centroid, Hz | 361 | 1824 | 290 |
| Tail level, dB | -10.8 | -6.6 | -3.8 |

| Band | Low edge Hz | Ref dB/s | v1 dB/s | Amended dB/s |
|---|---|---|---|---|
| 1 | 100 | -9.53 | -7.84 | -8.43 |
| 2 | 126 | -8.28 | -7.35 | -8.47 |
| 3 | 159 | -4.33 | -3.96 | -8.49 |
| 4 | 200 | -9.22 | -3.96 | -8.49 |
| 5 | 252 | -11.09 | -2.39 | -8.48 |
| 6 | 317 | -10.56 | -7.08 | -5.78 |
| 7 | 400 | -12.26 | -6.42 | -7.89 |
| 8 | 504 | -20.0 | -5.45 | -7.89 |
| 9 | 635 | -16.36 | -3.96 | -7.98 |
| 10 | 800 | -19.5 | -2.85 | -11.11 |
| 11 | 1008 | -22.07 | -7.31 | -10.36 |
| 12 | 1270 | -25.13 | -7.07 | -7.3 |
| 13 | 1600 | -17.18 | -6.34 | -10.66 |
| 14 | 2016 | -13.3 | -14.42 | -12.83 |
| 15 | 2540 | -9.13 | -19.19 | -11.56 |
| 16 | 3200 | -12.69 | -23.96 | -18.3 |
| 17 | 4032 | -13.73 | -26.13 | -16.27 |
| 18 | 5080 | -13.3 | -29.7 | -27.56 |
| 19 | 6400 | -12.48 | -44.73 | -30.16 |
| 20 | 8063 | -11.77 | -39.91 | -34.34 |
| 21 | 10159 | -11.19 | -44.88 | -39.91 |

## Reading (not a gate; regenerated for round 2 after D-042)
- Centroid on the T-026 set: amended 290 Hz vs reference 361 Hz (v1 1824 Hz). Tail level: amended -3.8 dB vs reference -10.8 dB (v1 -6.6 dB): notes still sustain too strongly late; the band decay table shows the high bands decaying faster than the reference above 2 kHz. D-042 changed neither (it only splits polarisation frequencies).
- On the 12 G-LISTEN-2 pairs the partial-level modulation (residual after a quadratic detrend, 0.1-0.85 s) is, reference / candidate round 1 / candidate round 2: harmonic 1 0.04 / 0.05 / 0.05 dB; harmonic 2 0.67 / 0.05 / 1.15 dB; harmonic 3 0.57 / 0.05 / 0.94 dB. See `reviews/G_LISTEN2_ROUND1_DIAGNOSIS.md`.
- Only 8 reference notes match the T-026 MIDI numbers at velocity >= 100, so medians are coarse.
