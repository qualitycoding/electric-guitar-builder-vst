# Feature comparison before listening (S-108, Amendment 03)

Candidate set: T-026 (MIDI 40/45/64 x velocity 45/85/125, default parameters, 1.6 s note, 48 kHz). Reference: P1 direct-input notes with the same MIDI numbers and velocity >= 100 (8 notes), onset from `scripts/analyse_reference.py`.

Measures: centroid over 0.2-0.7 s (Hann, 32768-point FFT); 21 one-third-octave bands from 100 Hz, decay slope in dB/s from a linear fit of the band envelope over 0.2-1.2 s; tail level = RMS(1.2-1.5 s) / RMS(0.2-0.7 s) in dB. Medians over notes.

| Measure | Reference | v1 (61ab5ed) | Amended |
|---|---|---|---|
| Centroid, Hz | 361 | 1824 | 282 |
| Tail level, dB | -10.8 | -6.6 | -2.6 |

| Band | Low edge Hz | Ref dB/s | v1 dB/s | Amended dB/s |
|---|---|---|---|---|
| 1 | 100 | -9.53 | -7.84 | -5.63 |
| 2 | 126 | -8.28 | -7.35 | -4.47 |
| 3 | 159 | -4.33 | -3.96 | -8.45 |
| 4 | 200 | -9.22 | -3.96 | -8.48 |
| 5 | 252 | -11.09 | -2.39 | -7.32 |
| 6 | 317 | -10.56 | -7.08 | -8.52 |
| 7 | 400 | -12.26 | -6.42 | -5.03 |
| 8 | 504 | -20.0 | -5.45 | -4.07 |
| 9 | 635 | -16.36 | -3.96 | -4.07 |
| 10 | 800 | -19.5 | -2.85 | -5.56 |
| 11 | 1008 | -22.07 | -7.31 | -4.76 |
| 12 | 1270 | -25.13 | -7.07 | -7.2 |
| 13 | 1600 | -17.18 | -6.34 | -3.94 |
| 14 | 2016 | -13.3 | -14.42 | -9.55 |
| 15 | 2540 | -9.13 | -19.19 | -10.56 |
| 16 | 3200 | -12.69 | -23.96 | -15.09 |
| 17 | 4032 | -13.73 | -26.13 | -20.35 |
| 18 | 5080 | -13.3 | -29.7 | -27.4 |
| 19 | 6400 | -12.48 | -44.73 | -32.76 |
| 20 | 8063 | -11.77 | -39.91 | -34.57 |
| 21 | 10159 | -11.19 | -44.88 | -40.77 |

## Reading (not a gate)
- The amended engine's centroid (282 Hz) is much closer to the reference (361 Hz) than v1 (1824 Hz); v1 was far too bright.
- Bands 14-21 (above 2 kHz): the reference decays slowly (-9 to -14 dB/s) where both candidates decay fast (amended -10 to -41 dB/s), so the amended high end still dies faster than the reference. Whether the reference's flat slopes there are real decay or a noise floor in the DI recording was not checked.
- Tail level: amended -2.6 dB against reference -10.8 dB and v1 -6.6 dB, i.e. the amended note sustains too strongly at 1.2-1.5 s. Low bands 1-2 decay more slowly than the reference's.
- Reproduce: `scripts/render_t026_set.cpp` (built against each commit) then `scripts/feature_comparison_a03.py`. Only 8 reference notes match the MIDI numbers at velocity >= 100, so medians are coarse.
