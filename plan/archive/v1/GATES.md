# Human gates

## G-LISTEN — blind realism and demo acceptance

- Trigger: S-LISTEN, after S-REVIEW and S-ADVERSARIAL and all quantitative tests pass.
- Evidence: commit marked `[gate-evidence G-LISTEN]`; orphan `gate-evidence/G-LISTEN` branch; 12 onset-preserving one-second A/B pairs at 44.1 kHz/24-bit, −23 dBFS RMS and 10 ms end fade; encoded answer key and seed; delivery URLs; all demo WAVs/event files/metadata; reference attribution/checksums; T-023–T-028 reports.
- Listener questions, without disclosing sides: (1) Which clip in each pair is the reference? (2) Do any demos sound unrealistic, synthetic, discontinuous, excessively noisy or otherwise unacceptable? Where and when? (3) Should the project proceed, iterate, rescope or stop?
- Allowed responses: `proceed`; `iterate: <timestamped notes>`; `proceed-with-rescope: <text>`; `stop`.
- Branches: proceed only with ≤8/12 correct and no unresolved qualitative realism finding. `iterate` applies one general mechanism change, reruns all frozen tests and creates a new seed (20261104 + round); maximum three rounds. After a third failure, only `proceed-with-rescope` or `stop` is allowed. Rescope requires a documented plan amendment; stop ends delivery without weakening tests.

## G-003 — lessons and knowledge stores

- Trigger: S-KNOW after completed S-RETRO.
- Evidence: `GATE-G-003.md` listing every lesson/knowledge ID, title and tag; proposed `qualitycoding/Lessons` and `qualitycoding/knowledge` targets.
- Responses: `push-to-proposed`; `push-to: <lesson-target> [knowledge-target]`; `do-not-push`.
- Branches: push separately and verify indexes/remote hashes; on rejection rebase/regenerate and retry at most three times per store. If no response/unreachable, create and report the specified Git bundle. `do-not-push` completes without store pushes.

No G-001/G-002 applies: math/computational result gates are N/A and no external release or deployment is planned.
