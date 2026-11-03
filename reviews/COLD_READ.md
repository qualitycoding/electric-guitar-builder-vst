# Cold-read record

No subagent/alternate tier is available (A-012); the single model performed separated dry-run and mechanical passes, with the required tier substitution recorded rather than claiming independent agents.

## Pass 1 — dry run

1. **High ambiguity:** material, fret-width and pickup values were qualitative; an implementer would still choose DSP coefficients. **Resolution:** added D-013 with exact coefficient tables, formulas, note allocation and voice stealing; linked it to S-002/S-003.
2. **High inconsistency:** A-009 permits 0.80 RTF while the draft CI text used much shorter numeric limits. **Resolution:** all three runner classes now use 60 seconds rendered in ≤48 seconds, median of three, matching 0.80 RTF.
3. **Coverage ambiguity:** `windows-2025` is not a Windows 11 desktop runner. **Resolution:** added D-014 waiver and honest Windows 11 host-test limitation.

## Pass 2 — fresh dry run and mechanical verification

Result: **zero unresolved items**. S-000 opens the plan; S-RETRO/S-KNOW close it. All T-001–T-030, D-001–D-014, C-001–C-008, A-001–A-012 and gate IDs resolve. All intake platforms map in TRACEABILITY, S-REVIEW/S-ADVERSARIAL precede S-LISTEN, D-011 records mutation opt-out, and no N/A artefact is required. All produced paths are named by an earlier step or are conditional failure records. Numeric gates lead to failing test cases; no load-bearing command swallows failure.

Re-run after pre-mortem hardening: **zero new unresolved items**; D-013/D-014 links and performance text are consistent.
