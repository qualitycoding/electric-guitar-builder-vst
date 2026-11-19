---
id: L-20261119T150000Z-review-agents-assumed-available
title: Intake assumed fresh-context review agents would be available; they were rate-limited when the cold read started
status: active
supersedes: []
recurrence_of: null
occurrences: 1
severity: Medium
tags: [applies:all, phase:planning, kind:wrong-assumption]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-19T15:00:00Z
---
## Trigger
A long planning run whose later phases (cold read, pre-mortem, audit) depend on spawning fresh-context agents, after many hours of session use.
## What went wrong
A-024 recorded subagents as available because the tool existed at intake. Both cold-read agents failed with HTTP 429 (session limit) before producing output.
## Correction
Ran separated self passes, recorded the tier substitution and R-017, and added D-035 so implementation reviews have a defined fallback.
## Prevention rule
Record agent availability as 'tool present, capacity unverified' at intake, and give every step that needs a fresh-context agent a written fallback (retry after reset, then a disclosed separated pass).
## Detection check
Every plan step whose tier says 'fresh context' names its fallback decision.
## Evidence
Task notifications for the two cold-read agents (rate_limit, HTTP 429); `reviews/COLD_READ_A03.md`.
