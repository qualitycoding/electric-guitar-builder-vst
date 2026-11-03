# Electric Guitar Builder VST — implementation handoff

## Purpose and reading order

Build the six-string, construction-controlled VST3 and deterministic headless renderer specified here; do not add a named-guitar selector, samples, machine learning, amp/cabinet simulation or release activity. Active profile: `software`; `audio=true`; `software.deploys=false`.

Read in order: `plan/PROFILE.md` → `plan/ASSUMPTIONS.md` → `plan/DECISIONS.md` → `plan/ENVIRONMENT.md` → `plan/TRACEABILITY.md` → `plan/GATES.md` → `plan/PLAN.md` → `research/audio/REFERENCES.md`.

## Setup, tests and freeze

Run the exact setup in `plan/ENVIRONMENT.md`, including executable restaging on this ephemeral non-executable mount. Run `python -m unittest discover -s tests -v` with `EGB_CONTRACT_BIN` set as documented. Verify `sha256sum -c tests/FROZEN_MANIFEST.sha256`. Planning-time red evidence is `tests/RED_VERIFICATION.txt`; all 30 tests must be green for delivery. Implementers may not modify, skip, expect-fail or weaken frozen tests. A suspected invalid test requires `TEST_CHALLENGE.md` and the amendment procedure, not a local edit.

## Steps and gates

S-000 → S-001 → S-002 → S-003 → S-004 → S-005 → S-CI → S-REVIEW → S-ADVERSARIAL → S-LISTEN → S-RETRO → S-KNOW. Only G-LISTEN and G-003 apply; no release gate exists because no external release is authorised. Independent steps may continue while halted at a gate only if they do not depend on its outcome and perform no external/irreversible action.

On an unanticipated situation choose the most reversible scope-neutral option and log `DEVIATIONS.md`; halt with `BLOCKED.md` for frozen tests, security, data integrity, public interfaces or research integrity. Append one `EXECUTION_LOG.md` line per attempt.

## Protocol rules carried into execution

**Rule 6 — Everything Is Committed:** “No finding, decision, proof, figure spec, or artifact exists unless it is committed to the generation branch.” Push after every successful chunk — green step, closed amendment, review or gate record — then verify remote HEAD with `ls-remote`; retry transient failures with visible backoff and report mismatches.

**Rule 9 — Integrity:** “No step may fabricate, cherry-pick without disclosure, or manually alter data, test results, benchmarks, or figures.”

**Rule 11 — Lessons:** Whenever the executing agent corrects its own execution, record a lesson before continuing. Use one `lessons/L-<timestamp>-<slug>.md` per correction, with trigger, mistake, correction, imperative prevention rule, detection check and taxonomy tags; name recurrences and never include secrets.

**Rule 12 — Knowledge Base:** Record every newly discovered Subject fact before continuing in `knowledge/K-<timestamp>-<slug>.md`, including source/locator, applicable version, confidence, related claim and subject tags. Supersede wrong facts rather than erasing history.

**Rule 13 — Lesson & Knowledge Stores:** Accumulate lessons and knowledge on the working branch. At the end, after G-003, lessons go to the lesson store and knowledge to the separate knowledge store; planning items travel too. Never store credentials, tokens, secrets or personal data.

The plan begins with S-000 and ends with S-RETRO then S-KNOW. Stop after those closing steps; do not release, sign, notarise, install globally or deploy.
