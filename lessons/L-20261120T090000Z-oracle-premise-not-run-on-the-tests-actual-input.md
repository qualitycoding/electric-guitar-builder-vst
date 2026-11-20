---
id: L-20261120T090000Z-oracle-premise-not-run-on-the-tests-actual-input
title: An oracle prediction assumed which string the engine would use instead of running the test's actual events through the engine's allocation rule
status: active
supersedes: []
recurrence_of: L-20261008T151500Z-reasoned-expected-value-wrong
occurrences: 1
severity: High
tags: [domain:audio, tech:cpp, phase:specification, kind:verification-gap]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-20T09:00:00Z
---
## Trigger
An expected value depends on engine state chosen from the test's input (string allocation, voice choice, routing), and the oracle models that choice by reading code rather than executing it on the exact input.
## What went wrong
T-048's prediction assumed MIDI 45 plays on the open A string through first-fit allocation. The test helper writes channel 1, and channels 1-6 select a string directly, so the engine played the note on the high-E string at fret −19 and the measured effect was a tenth of the prediction.
## Correction
D-037: the test now sends channel 5 explicitly; verified on the implementer's engine (6.603 dB/s measured against 6.598 predicted).
## Prevention rule
For every rendered test, write the events with every routing field explicit (channel, string) and confirm the engine's choice by calling its inspection function on the exact events before freezing the expected value.
## Detection check
Each rendered test in the frozen case file states its channel and the string it selects in a comment; the oracle records the same string.
## Evidence
Implementer TEST_CHALLENGE at commit 714ba03; D-037.
