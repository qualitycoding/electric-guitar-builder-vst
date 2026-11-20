---
id: L-20261120T120000Z-v1-test-encoded-an-impossible-direction
title: A frozen threshold calibrated on an artefact asserted a physically impossible direction and passed for years of runs
status: active
supersedes: []
recurrence_of: L-20261106T180100Z-frozen-metric-caps-the-property-under-listening
occurrences: 1
severity: High
tags: [domain:audio, tech:cpp, phase:specification, kind:verification-gap]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-20T12:00:00Z
---
## Trigger
A frozen test whose threshold was set from a measurement on the implementation, for a mechanism with a known physical direction (here: two-stage decay of two unequally damped components).
## What went wrong
v1 T-037 required the early decay slope to exceed the late one by 0.5 dB/s. A sum of decaying exponentials can only slow down, so the physical direction is the opposite. The test passed only because its note sounded on the slack high-E string at fret −24 (R-023).
## Correction
D-039: direction corrected (late slope less negative than early), threshold recalibrated on the correct string (measured 0.195; threshold 0.1).
## Prevention rule
For every frozen threshold on a physical mechanism, write the mechanism's sign or monotonicity from first principles in the test comment and check that the asserted inequality has that sign before calibrating its magnitude.
## Detection check
Each mechanism test's comment states the expected sign with its reason, and the inequality in the check matches it.
## Evidence
reviews/FROZEN_TEST_AUDIT_A03.md; D-039.
