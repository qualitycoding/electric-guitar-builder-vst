---
id: L-20261119T130100Z-test-written-against-guessed-processor-api
title: A frozen state test was first written against a guessed processor API
status: active
supersedes: []
recurrence_of: L-20261009T160900Z-juce-api-assumed-from-memory-compile-caught-and-version-floor-unchecked
occurrences: 1
severity: Medium
tags: [tech:cpp, tech:juce, phase:specification, kind:wrong-assumption]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-19T13:01:00Z
---
## Trigger
Writing a new test for a class the project already defines (here `EgbAudioProcessor`) from memory of a typical JUCE processor.
## What went wrong
T-050 first used `egb::PluginProcessor`, `setSnapshotForTest` and `snapshotForTest`, none of which exist; the project class is `egb::EgbAudioProcessor` with a public `currentParams`.
## Correction
Read `include/egb/PluginProcessor.h` and the v1 T-011 case, then rewrote T-050 on the real API before the first compile.
## Prevention rule
Before writing a test that touches an existing class, open its header and one existing test that uses it, and copy the call pattern.
## Detection check
The test compiles on the first build against the unmodified headers.
## Evidence
Planning history of `tests/physics/physics_cases.cpp` before commit a25b36b.
