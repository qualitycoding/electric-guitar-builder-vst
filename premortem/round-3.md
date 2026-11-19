# Pre-mortem round 3 (amendment 03, first round for this amendment)

Conducted by the planning agent as a separated pass (fresh-context agents unavailable: API rate limit; R-017, `.checkpoints/state.json` tier_substitutions).

## Incident report (software): six months after the amended engine shipped to the owner's DAW

The amended build passed every frozen test and G-LISTEN-2, yet the owner reports that (a) default patches sound harsher and clip on chords, (b) the 'neck joint' and 'fingerboard' switches 'do nothing', (c) a session saved before the update reopened with a different tone, and (d) CPU spikes when automating the cable control on a 64-sample buffer.

## Lens review

| Lens | Finding | Severity before | Mitigation added | Residual |
|---|---|---|---|---|
| Technical / gain staging | Velocity transduction adds +6 dB/octave; the tanh safety stage hides heavy clipping because T-009/T-051 only bound the post-safety peak. Planning measured a v1 pre-safety peak of 2.88 on the T-051 configuration. | High (R-019) | S-000 records the v1 pre-safety peak of T-009 and T-051; D-034 rule: if S-105's pre-safety peak at T-009 exceeds 2× the v1 value, apply one fixed global gain constant before the safety stage in −1.5 dB steps until it does not, logged in `DEVIATIONS.md`; never per-note. | Medium |
| Technical / numerics | The RLC biquads and modal decays produce denormals in tails; the engine has no denormal guard (grep: no `ScopedNoDenormals`/FTZ). | Medium (R-020) | S-105 action: wrap `Engine::render` in `juce::ScopedNoDenormals`; ASan/UBSan and T-017 rerun. | Low |
| Research assumptions | C-025, C-026, C-030 are single-source (Zollner) but load-bearing for D-022/D-028 magnitudes. | High | Values are anchored only qualitatively and labelled parameterisation (A-008); T-044/T-048 test the implementation of the decided model, not the physics claim; G-LISTEN-2 question 3 judges plausibility; R-013 and new R-018 record the evidence level. | Medium |
| Research assumptions | Neck joint and fingerboard controls are near-inaudible by design (C-034, C-029) — owner may see them as broken. | Medium (R-011) | D-023 wording rule; S-LISTEN-2 demo question 3 asks the owner directly. | Medium |
| Compatibility | v1 sessions reopen with new physics (A-015 accepted this). | Medium | A-015 records the owner's acceptance; T-050 guarantees deterministic migration. | Low |
| Real-time | Cable automation recomputes coefficients per block (D-025 exception). | Medium (R-021) | Bounded closed form, T-013/T-014 unchanged; S-ADVERSARIAL tests block sizes 1 and 2048 with rapid automation. | Low |
| Implementer misinterpretation | Humbucker coil orientation, `xBearing` sign and mode-shape origin could be implemented mirrored and still be self-consistent in the engine. | High | T-042/T-044 compare the functions with the oracle at 1e-12 and T-046 compares the engine table with the functions, so a mirrored implementation fails. | Low |
| Integrity | Frozen case logic previously unhashed. | High (R-008) | D-032 hashes it; S-101 proves the CI job fails on tampering. | Low |
| Past lessons | Checklist items 1–16 of `research/PRIOR_KNOWLEDGE.md` each map to a test, decision or step (see that file); item 9 (frozen metrics capping the audible property) is covered by S-108 before listening. | — | — | — |
| CI coverage | Platforms unchanged; `frozen-manifest` added; T-017 per-runner budgets unchanged. | Medium (R-015) | D-034 performance rule. | Medium |
| Supply chain / security | No new dependency; seven new state attributes validated atomically (T-049, T-050). | Low | — | Low |
| Operational | Listener availability (v1 R-006); reference cache download (S-108 checksum rule). | Medium | unchanged | Medium |

Critical/High after hardening: none (R-009, R-019 and the single-source research items are reduced to Medium by blocking decision rules or by confining tests to the decided model). Plan changes in this round: S-000 action 5a, S-105 action 2a, D-034 gain rule, R-018..R-021. Cold-read check re-run after the changes (mechanical script, zero new items).
