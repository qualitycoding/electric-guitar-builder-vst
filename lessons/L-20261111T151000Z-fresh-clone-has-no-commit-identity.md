---
id: L-20261111T151000Z-fresh-clone-has-no-commit-identity
title: A fresh clone in a new container had no git identity, so the first checkpoint commit failed
status: active
supersedes: []
recurrence_of: null
occurrences: 1
severity: Low
tags: [tech:git, phase:planning, kind:environment]
recorded_by: planner
run: 20261111T150746Z-guitar-physics-research
recorded_at: 2026-11-11T15:10:00Z
---
## Trigger
A repository cloned into a new session directory, with no global `user.name`/`user.email`, and a plan that commits checkpoints immediately.
## What went wrong
The first `git commit` of the run failed with 'Author identity unknown'; the chained push did not run.
## Correction
Set a repository-local identity (`git config user.name`, `git config user.email`) and re-ran the commit.
## Prevention rule
Run `git config user.email || git config user.email <noreply address>` as part of the branch-creation step, before the first commit.
## Detection check
`git config user.email` prints a value before the first commit of the run.
## Evidence
Planning transcript, commit `77f76ce` made after the fix.
