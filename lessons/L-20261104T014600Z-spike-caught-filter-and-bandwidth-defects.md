---
id: L-20261104T014600Z-spike-caught-filter-and-bandwidth-defects
title: Planning spikes caught a short-input filter failure and an under-bandwidth synthesis architecture
status: active
supersedes: []
recurrence_of: null
occurrences: 1
severity: High
tags: [domain:audio, phase:research, kind:verification-gap]
recorded_by: planner
run: 20261104T013000Z-electric-guitar-builder-vst
recorded_at: 2026-11-04T01:46:00Z
---
## Trigger
A new onset-analysis script or physical-model architecture is about to supply frozen test assumptions.
## What went wrong
Zero-phase filtering failed on an onset shorter than its padding; the first modal model missed the reference-envelope gate.
## Correction
Used causal filtering for short inputs and revised excitation bandwidth plus a global pickup/body calibration before freezing.
## Prevention rule
Run boundary inputs and pitch-matched architecture spikes before converting any DSP assumption into a frozen test.
## Detection check
`reference_metrics_summary.txt` covers 138 notes and `model_spike.json` records finite sweeps and `architecture_spike_pass: true`.
## Evidence
Committed spike scripts and outputs on the generation branch.
