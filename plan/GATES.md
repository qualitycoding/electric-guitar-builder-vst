# Human gates — amendment 03

The v1 gates are archived in `plan/archive/v1/GATES.md`. `G-LISTEN` closed with `proceed` on 2026-11-05 (EXECUTION_LOG, D-16 caveat). No G-001 (no math/computational profile) and no G-002 (no release, publication or deployment; A-011) apply.

## G-LISTEN-2 — blind realism and demo acceptance for the amended engine

- Trigger: S-LISTEN-2, after S-REVIEW, S-ADVERSARIAL, S-108 and all frozen tests pass on CI.
- Evidence bundle: commit marked `[gate-evidence G-LISTEN-2]`; orphan branch `gate-evidence/G-LISTEN-2`; 12 onset-preserving one-second A/B pairs at 44.1 kHz/24-bit, −23 dBFS RMS, 10 ms end fade, sides from seed `20261111 + round`; base64 answer key; `reports/reference_clip_correlation.json` (every reference clip ≥ 0.99 against its decoded source); `reports/feature_comparison_a03.md` (S-108); the 24 per-setting demo renders of S-LISTEN-2 (`demos/a03/`, including re-rendered palm-mute and pick-angle demos, R-016) with metadata; reference attribution and checksums; T-023..T-028 and T-040..T-051 reports.
- Questions (sides not disclosed): (1) Which clip in each pair is the reference? (2) Do any demos sound unrealistic, synthetic, discontinuous, excessively noisy or otherwise unacceptable — which, and at what time? (3) Do the pickup-load, body-type, neck-joint and pluck-position demos change the sound in a way you find plausible? (4) Should the project proceed, iterate, rescope or stop?
- Responses: `proceed`; `proceed-abx` (run the ABX re-validation of D-16 before closing); `iterate: <timestamped notes>`; `extend-rounds: <n>` (owner extension route, recorded, L-20261106T180500Z); `proceed-with-rescope: <text>`; `stop`.
- Branches: `proceed` only with ≤ 8/12 correct and no unresolved realism finding → S-RETRO. `proceed-abx` → run ABX per the `audio-blind-listening-validation` skill, then return to this gate with the result. `iterate` → one general mechanism change inside D-021..D-028 (or a recorded amendment request if outside, D-034), rerun all frozen tests, new seed, next round; maximum three rounds unless `extend-rounds`. After the last round only `proceed-with-rescope` or `stop`. A listener answer that is the exact complement of the key means a broken bundle (L-20261106T010000Z): halt and rebuild, the round does not count.

## G-003 — lessons and knowledge stores

- Trigger: S-KNOW after S-RETRO.
- Evidence: `GATE-G-003.md` listing every lesson and knowledge ID, title and tags from both runs; the source register `K-20261119T120000Z-source-register-guitar-physics` on its own line with 19 sources, 3 'none stated' and 3 'unknown' licences; proposed targets `qualitycoding/lessons` and `qualitycoding/knowledge` (A-021).
- Responses: `push-to-proposed`; `push-to: <lesson-target> [knowledge-target]`; `do-not-push`.
- Branches: as 3.7.2 of the protocol: push separately, regenerate indexes, retry up to three times per store, bundle fallback. The five v1 entries without front matter are normalised to the Appendix A/B templates in S-RETRO before the push (R-012).
