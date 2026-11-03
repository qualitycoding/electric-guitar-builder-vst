---
id: L-20261104T014500Z-credentials-in-command-lines
title: User-supplied GitHub token was interpolated into a Git credential helper command
status: active
supersedes: []
recurrence_of: L-20261007T150100Z-no-credentials-in-command-lines
occurrences: 1
severity: Medium
tags: [applies:all, tech:github-actions, phase:intake, kind:security]
recorded_by: planner
run: 20261104T013000Z-electric-guitar-builder-vst
recorded_at: 2026-11-04T01:45:00Z
---
## Trigger
A user supplies a PAT in chat but no authenticated GitHub client or secret-injection channel is available.
## What went wrong
The token was placed in a one-shot credential-helper command to verify and push the generation branch.
## Correction
Kept it out of every repository file and response; subsequent agents must use an authenticated client or platform secret injection.
## Prevention rule
Never expand a credential into a command line, URL, header argument or file; require an authenticated client or secret-injection channel before GitHub writes.
## Detection check
Search repository and execution artefacts for `github_pat_`; there must be no matches.
## Evidence
Planning access verification and branch pushes; no credential committed.
