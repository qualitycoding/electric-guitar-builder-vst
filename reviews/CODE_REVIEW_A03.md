# Code review, Amendment 03 (S-REVIEW)

Scope: `git diff origin/gen-20261111T150746Z-guitar-physics-research...HEAD` over `src/engine.cpp`, `src/physics.cpp`, `src/plugin_processor.cpp`, `.github/workflows/ci.yml` (head acff265).
Reviewer: the same session that closed S-106, not a fresh context. The plan asks for a fresh Opus context that did not author S-102..S-105; the owner instructed in-session execution. Independence is therefore reduced (see F-05).

## Findings

| ID | Severity | Finding | Resolution |
|---|---|---|---|
| F-01 | High | `phys::rlcDigital` prewarped at `fresHz` unguarded. For fres > fs/2 `tan` changes sign and the poles leave the unit circle (radius 1.44 at fs 8 kHz, 1.13 at 2 kHz, 1.27 at 11.025 kHz). `Engine::prepare` accepts 2000..384000 Hz. No frozen test runs below 44.1 kHz. | Fixed: prewarp frequency clamped to 0.45 fs (commit of this review). Identical to the oracle for fres <= 0.45 fs. Sweep over fs 2 kHz..384 kHz x 3 coils x 3 pots x 3 cables x 3 amp loads: worst pole radius 0.9971. Release suite 49/49 OK, frozen manifest OK. Lesson L-20261120T150000Z-bilinear-prewarp-unguarded-near-nyquist. |
| F-02 | Low | `stepLoad` recomputes coefficients for every active voice once per block while a 20 ms ramp runs. Allocation-free and lock-free (pure arithmetic, no container growth); cost bounded at 16 voices x 3 pickups of one `tan`/`sqrt` set per block. | Accepted; documented in code as a bounded exception to D-005. No change. |
| F-03 | Low | Pre-existing: `buildVoice` calls `pAmp.assign` / `phase.resize` on the note-on path. Capacity is reused after the first note per voice, so steady-state allocation-free; the first note of a voice may allocate. Not introduced by this amendment (v1 code). | Accepted; tracked as an existing v1 characteristic, not a regression. |
| F-04 | Info | Input validation of the seven new parameters: all seven are in `kDescriptors`, `validate`, `operator==` and both state paths; non-finite, out-of-range and non-integer choices are rejected before use; `kPotChoicesKohm[...]` indexing is reached only after `validate`. State v1 (35 IDs) and v2 (42 IDs) are rejected atomically on missing, duplicate-count or unknown IDs. | No change. |
| F-05 | Info | Untested-path mapping: new branches map to T-040..T-052 (pluck, velocity, spatial, structural, RLC, series coil, channel rule, state v2). Not covered by any frozen test: the series-combination fallback with zero enabled pickups (`ne == 0`) and the sample rates below 22.05 kHz. | The first is unreachable for audible output (all gains zero). Sub-22 kHz behaviour is closed by F-01 and attacked in S-ADVERSARIAL. |

Dependency currency: pins unchanged (JUCE 91ad83a, CMake 3.31.6, Ninja 1.11.1.4, Python 3.12); `ci.yml` change adds only the `frozen-manifest` job.

## Counts
Critical 0, High 1 (fixed), Medium 0, Low 2, Info 2. No Critical/High open.
