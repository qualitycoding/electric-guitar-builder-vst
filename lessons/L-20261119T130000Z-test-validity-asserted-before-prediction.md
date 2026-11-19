---
id: L-20261119T130000Z-test-validity-asserted-before-prediction
title: A decision stated that a frozen test stays valid before its outcome was predicted under the new physics
status: active
supersedes: []
recurrence_of: L-20261008T173532Z-untested-claims-stated-as-fact-four-times
occurrences: 2
severity: High
tags: [domain:audio, tech:cpp, phase:specification, kind:verification-gap]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-19T13:00:00Z
---
## Trigger
An amendment changes a model stage (here pickup sampling and electrics) that existing frozen tests measure in rendered audio.
## What went wrong
D-030 first said T-032 'remains valid' because the new resonance frequencies still fell inside its bands. A prediction under the new physics showed the test's other premise (pickup types differ only electrically) is false; its ratio would be 0.76, not > 1.4.
## Correction
T-032 was retired through the test-challenge record, D-030 was rewritten with the prediction cited, and the remaining rendered tests were classified by premise.
## Prevention rule
Before stating that a frozen test survives an amendment, (1) grep every hashed test file for each constant, count and identifier the amendment changes, and classify every hit; and (2) run the oracle on each affected test's exact configuration and compare the predicted value with its threshold. Cite both outputs in the decision.
## Detection check
Every 'remains valid' or 'expected to hold' statement in an amendment's decisions names a spike output or a premise argument.
## Evidence
Occurrence 2: T-022 (`src/contract_main.cpp:1200`) asserted 35 metadata parameters; missed by D-030, caught by the implementer's TEST_CHALLENGE at S-103; resolved by D-036 with `research/spikes/a03_hashed_constant_sweep.txt`.
`research/spikes/t032_prediction_stdout.txt`; D-030.
