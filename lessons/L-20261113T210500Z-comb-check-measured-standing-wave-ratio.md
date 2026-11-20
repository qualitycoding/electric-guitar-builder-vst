---
id: L-20261113T210500Z-comb-check-measured-standing-wave-ratio
title: Oracle self-checks used the wrong quantity (standing-wave ratio for a comb notch) and a too-tight Q bound
status: active
supersedes: []
recurrence_of: L-20261004T162214Z-dsp-test-measured-wrong-quantity
occurrences: 3
severity: Medium
tags: [domain:audio, tech:python, phase:research, kind:verification-gap]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-13T21:05:00Z
---
## Trigger
Writing sanity checks inside a planning oracle for a filter or comb whose known answer comes from a source (here: humbucker notch at half-wavelength pole spacing; RLC Q over a load sweep).
## What went wrong
(1) A sweep assertion required Q > 0.3, but a 50 kOhm amplifier load legitimately gives Q = 0.27, so the oracle aborted. (2) The humbucker notch check divided the two-pole standing-wave weight by the single-point weight; near zeros of the single-point weight the ratio is dominated by cot(kx), and the minimum landed at mode 17 instead of the predicted 35.
## Correction
The Q bound became a finiteness/plausibility bound (0.05..12). The notch check now evaluates the comb in the form the source states, |1 + g e^{-jkd}|/(1+g), whose minimum is at mode 35 with 16.9 dB depth, inside the 15-25 dB the source reports.
## Prevention rule
Before writing an oracle assertion or a measurement helper, compute its quantity on the source's own worked case and on a synthetic signal with the dynamic range of the real material (for audio bands: a strong low partial at least 60 dB above the measured band), and confirm both reproduce the known answer; express bounds as physical plausibility limits, never as expected operating ranges.
## Detection check
Each oracle check line in the stdout names the source value it reproduces (e.g. '(Zollner 111.1 kOhm)').
## Evidence
Occurrence 3: T-045 and T-035 measured band levels with the v1 rectangular-window `bandEnergy`; T-047 validated it only on two tones 20 dB apart. On real renders it read 3.5 dB where the physics gives 17.3 dB. Found by the frozen-test audit; fixed by D-039 with a Hann helper and a 60 dB T-047 case.
`research/spikes/physics_oracle.py` history on the generation branch; stdout `research/spikes/physics_oracle_stdout.txt`.
