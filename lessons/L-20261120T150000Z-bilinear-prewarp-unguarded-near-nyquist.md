---
id: L-20261120T150000Z-bilinear-prewarp-unguarded-near-nyquist
title: A bilinear transform prewarped at the analog resonance turned unstable once the resonance passed Nyquist, and no test sampled that regime
status: active
supersedes: []
recurrence_of: null
occurrences: 1
severity: High
tags: [domain:audio, tech:cpp, phase:implementation, kind:implementer-mistake]
recorded_by: implementer
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-20T15:00:00Z
---
## Trigger
Implementing a digital filter from an analog prototype whose natural frequency depends on user parameters (coil L, cable C, load), for an engine that accepts sample rates from 2 kHz.
## What went wrong
`rlcDigital` prewarped at `fresHz` with `tan(pi*fres/fs)`. For fres > fs/2 the tangent changes sign and the poles left the unit circle (radius 1.44 at 8 kHz, 1.13 at 2 kHz). Every frozen test runs at 44.1 kHz and above, so S-105 passed with the defect.
## Correction
S-REVIEW F-01: prewarp frequency clamped to 0.45 fs (identical for fres <= 0.45 fs); 49/49 frozen tests unchanged.
## Prevention rule
For every filter derived from user-controlled analog parameters, compute pole radius over the full accepted sample-rate range and parameter corners before closing the step, and clamp any prewarp or warp frequency below Nyquist.
## Detection check
A pole-radius sweep over fs in {2000, 4000, 8000, 11025, 22050, 44100, 96000, 384000} and the parameter corners shows radius < 1 everywhere.
## Evidence
reviews/CODE_REVIEW_A03.md F-01.
