---
id: K-20261119T150100Z-subagent-review-capacity-rate-limited
statement: "In a long Claude Code cloud session, spawned subagents share the session's usage limit; when it is reached they terminate immediately with an HTTP 429 rate_limit error and a reset time, producing no output."
status: current
supersedes: []
tags: [subject:claude-code-subagents, tech:claude-code, phase:planning]
applies_to_version: version-independent
source: { url: "", doi: "", title: "Task notifications in run 20261111T150746Z-guitar-physics-research", locator: "cold-read agent notifications, 2026-11-19", accessed: "2026-11-19", tier: 1 }
confidence: verified
derived_from: []
discovered_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-19T15:01:00Z
---
Observed directly: both agents (one Haiku, one Sonnet tier) failed with 'You've hit your session limit · resets 6:30pm (Europe/London)'. Plans that depend on fresh-context review need a fallback (D-035 in this project).
