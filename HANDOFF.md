# HANDOFF — amendment 03: guitar physics research

**Start here.** This branch carries an amendment plan that incorporates the owner's research document *Electric Guitar Audio Synthesis* into the electric-guitar-builder VST. The v1 handoff, plan and gates are archived in `plan/archive/v1/`; the v1 implementation is already merged at `61ab5ed` (CI green on six jobs).

## Purpose

Replace three heuristic stages of the modal engine with sourced physics and add the controls the owner asked for: a loaded RLC pickup circuit (pot, cable, amplifier), velocity transduction, wavenumber-domain pickup sampling with a two-pole humbucker, neck/bridge structural loss (dead spots), body type, neck joint, fingerboard and pluck position (A-014, D-020..D-034). Fretless operation is out of scope (D-024). The research document was treated as a lead: its tables contain factor-of-two errors (C-013, C-014), its load model omits the tone pot (C-015), and its joint/fingerboard/wood claims are unsupported by measurement (C-027..C-029).

## Active profiles

`software`, `audio = true` (`plan/PROFILE.md`). Environment for planning: stable. No release (A-011).

## Reading order

1. This file. 2. `plan/PROFILE.md` (amendment section). 3. `plan/ASSUMPTIONS.md` A-013..A-024. 4. `plan/DECISIONS.md` D-020..D-034 (and D-001..D-014 for unchanged behaviour). 5. `plan/PLAN.md`. 6. `plan/GATES.md`. 7. `plan/TRACEABILITY.md` (amendment section). 8. `plan/ENVIRONMENT.md` (Amendment 03 section). 9. `premortem/RISK_REGISTER.md` R-008..R-015. 10. `research/PRIOR_KNOWLEDGE.md` (amendment checklist). 11. `include/egb/Physics.h` and `research/spikes/physics_oracle.py`.

## Environment, suite and freeze

Follow `plan/ENVIRONMENT.md`, Amendment 03 section. Run the suite with `EGB_CONTRACT_BIN=$PWD/build/egb_contract python3 -m unittest discover -s tests -v` and verify the freeze with `sha256sum -c tests/FROZEN_MANIFEST.sha256`. At handoff, T-040..T-046 and T-048..T-050 fail against stubs by design (`tests/RED_VERIFICATION_A03.txt`), and so does T-022 since its amendment to 42 parameters (D-036); T-047 and T-051 pass; the other 35 v1/amendment tests pass. Retired tests: T-001, T-011, T-032 (`tests/FROZEN.md`).

## Steps at a glance

S-000 → S-101 (CI freeze job) ‖ S-102 (physics functions) ‖ S-103 (parameters, state v2) → S-104 (engine physics) → S-105 (electrical stage) → S-106 (regression, sanitizers, CI) → S-REVIEW → S-ADVERSARIAL → S-108 (reference features) → S-LISTEN-2 [G-LISTEN-2] → S-RETRO → S-KNOW [G-003].

## Human gates

G-LISTEN-2 (listening) and G-003 (stores). While halted at a gate you may continue any step that does not depend on its outcome; no external or irreversible action is in scope.

## Halt and deviation protocol

Default rule (protocol 3.2): choose the most reversible option that does not expand scope, log it in `DEVIATIONS.md` with rationale, and continue — unless it touches frozen tests, security, data integrity, a public interface, or research integrity, in which case halt and write `BLOCKED.md`. A frozen test that seems wrong: halt and write `TEST_CHALLENGE.md`; never edit a hashed file. Every substitution of a tool, pin, flag, timeout or config file is written to `DEVIATIONS.md` when made (Rule 14). Append one line per step attempt to `EXECUTION_LOG.md` under `## Amendment 03`.

## Rules restated verbatim (protocol v3.15)

6. **Everything Is Committed** `[All]`: No finding, decision, proof, figure spec, or artifact exists unless it is committed to the generation branch.
    * **Push cadence** `[All]`, on **every** platform (stable and ephemeral): after every successful chunk — a plan step turning green, a frozen-test amendment round closed, a review or gate record committed — immediately push the working branch to the remote, then verify with `ls-remote` that the remote matches local HEAD. Retry transient failures with backoff (on flaky networks prefer HTTP/1.1 with a raised `http.postBuffer`); report any remote/local mismatch instead of assuming the push landed. On ephemeral platforms this is the primary defense against losing work; on stable platforms it is cheap insurance and keeps collaborators and CI current.

9. **Integrity** `[All]`: No step may fabricate, cherry-pick without disclosure, or manually alter data, test results, benchmarks, or figures. In addition:
   * `[computational, publication]` Every reported number is generated from committed results, not transcribed by hand.
   * `[publication]` Generative-AI images are never used as data figures. AI assistance is disclosed according to the venue's policy, as recorded in `plan/ASSUMPTIONS.md`.

11. **Lessons** `[All]`: Whenever the executing agent corrects its own execution, it records a lesson before continuing. The *executing agent* is the planning agent while it runs this protocol, and the implementing agent while it runs the plan. A *correction* is any of:
    * redoing or reverting something the agent did;
    * a command, assumption, or edit that failed and was fixed by taking a different approach;
    * a check (test, cold read, proof review, pre-mortem, CI) that caught the agent's own mistake;
    * a correction from the human.

    Retrying the same action after a transient failure is not a correction, and neither is a failure the protocol plans for (such as tests failing red against stubs).
    * Each lesson is one file, `lessons/L-<YYYYMMDDTHHMMSSZ>-<slug>.md`, on the working branch, using the template in Appendix A. It is committed before work continues.
    * A lesson carries the *identifying information* that lets a future agent recognise the situation before repeating the mistake: the trigger (the circumstances and observable signals), the mistake, the correction, a prevention rule written as one imperative, checkable instruction, and a detection check.
    * Every lesson is classified with tags from the store taxonomy (Appendix C), so lessons can be read as a group: for example, all `tech:java` lessons, or all `domain:audio` lessons.
    * If the mistake repeats a lesson loaded in R0, the new lesson names it in `recurrence_of` and strengthens its prevention rule; a recurrence means the earlier rule did not work.
    * If the same mistake recurs within the run, increase `occurrences` on the run's existing lesson and add the new evidence, instead of writing a second file.

12. **Knowledge Base** `[All]`: All supporting research and derived knowledge is recorded as knowledge items, so later work can reuse it instead of researching it again. Whenever either agent discovers a new fact about the task's Subject (its technologies, formats, APIs, platforms, tools, mathematical objects, or venues), it adds an item before continuing.
    * Each item is one file, `knowledge/K-<YYYYMMDDTHHMMSSZ>-<slug>.md`, on the working branch, using the template in Appendix B. It records the fact, its source and locator, the version it applies to, its confidence, and the claim it derives from (`C-###`), if any.
    * Every item is classified with tags from the store taxonomy (Appendix C), including at least one `subject:` tag, so it can be found again.
    * A fact that turns out wrong or outdated is never edited away: a new item `supersedes` it, so the history remains.
    * The sources behind the facts are recorded too. At the end of the research rounds (R7), one **source register** item lists every external source checked during the run, with its content, licence and terms of use (Appendix B). A source that is not in the register has not been checked, as far as a later run is concerned.

13. **Lesson & Knowledge Stores** `[All]`: Lessons and knowledge items persist across tasks in separate stores recorded at intake (`A-###`; layout in Appendix C). The default lesson store is a repository named `Lessons`; the default knowledge store is a repository named `knowledge`, both owned by the same account as the target repository. Stores are read at the start of research (R0) and written only at the end of implementation, after gate `G-003` (3.7.2); lessons go to the lesson store and knowledge items go to the knowledge store. During a run, new lessons and items accumulate on the working branch. Lessons and items must never contain credentials, tokens, secrets, or personal data; redact them (for example, `github_pat_***`).

Lessons and knowledge items accumulate in `lessons/` and `knowledge/` on the implementation branch; lessons go to the lesson store `qualitycoding/lessons` and knowledge items to the knowledge store `qualitycoding/knowledge`, only after G-003. The plan begins with S-000 and ends with S-RETRO and S-KNOW.
