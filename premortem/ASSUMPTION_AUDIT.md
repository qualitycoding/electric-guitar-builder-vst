# Assumption and premise audit

Adversarial separated pass under A-012. Evidence was re-read where locally checkable. No item was falsified. Unverifiable items are risks, not silent confirmations.

## Assumptions

| ID | Verdict | Evidence/consequence |
|---|---|---|
| A-001 | confirmed | JUCE pin exists; environment/tool imports executed. |
| A-002 | confirmed | JUCE open-source licensing path and AGPLv3 compatibility recorded; not a legal opinion. |
| A-003 | confirmed | Declared labels mapped; exact Windows 11 desktop limitation moved to D-014/R-002. |
| A-004 | confirmed | D-003/D-013 encode geometry and note/fret allocation. |
| A-005 | confirmed | D-005/T-008/T-016 cover rates, voices and block boundaries. |
| A-006 | unverifiable | No listener response exists yet; R-006/G-LISTEN blocks perceptual acceptance. |
| A-007 | confirmed | Zenodo record and CC BY 4.0 attribution/checksum register checked; P1 MD5 verified. |
| A-008 | confirmed | This is a scope limit, not a wood-science claim; D-013 coefficients and listening gate align. |
| A-009 | unverifiable | No production engine exists to benchmark; T-017 and D-012 enforce the budget. |
| A-010 | confirmed | Store paths loaded at R0 and G-003 requires confirmation. |
| A-011 | confirmed | No release/deploy step or G-002 path exists. |
| A-012 | confirmed | Session tool inventory has no subagent facility; substitutions disclosed. |

## Decision premises

| ID | Verdict | Evidence/consequence |
|---|---|---|
| D-001 | confirmed | Executable spike supports feasibility; realism not inferred. |
| D-002 | confirmed | Goal excludes named-model selector. |
| D-003 | confirmed | Complete user controls and public schema present. |
| D-004 | confirmed | Executable formulas and numeric oracles checked. |
| D-005 | confirmed | Interfaces, caps and real-time constraints are testable. |
| D-006 | confirmed | Seeded deterministic design and safety tests present. |
| D-007 | confirmed | Reference roles and held-out prohibition explicit. |
| D-008 | confirmed | Metrics regenerated from committed P1 results. |
| D-009 | confirmed | Matches listening skill; human outcome remains unknown. |
| D-010 | confirmed | Versioned labels recorded; Windows waiver separated. |
| D-011 | confirmed | Opt-out rationale explicit; reviews cover gaps. |
| D-012 | confirmed | All anticipated forks have blocking/reversible rules. |
| D-013 | confirmed | Closed coefficient contract matches spike where applicable; added controls bounded by tests. |
| D-014 | confirmed | Runner labels are image families; no exact Win11 desktop claim. |

## Single-source/inferred and load-bearing claims

| ID | Verdict | Evidence/consequence |
|---|---|---|
| C-001 | confirmed | Primary Zenodo source. |
| C-002 | confirmed | Committed measured result. |
| C-003 | confirmed | Committed measured result. |
| C-004 | confirmed | Executable feasibility only. |
| C-005 | confirmed | Spike JSON checked; not production proof. |
| C-006 | confirmed | Conservative inference; no unsupported fidelity claim. |
| C-007 | confirmed | Pinned primary repository. |
| C-008 | confirmed | GitHub runner documentation; exact desktop waiver separate. |

## Frozen-test premises

Confirmed: stubs are buildable, all fixtures exist, numeric oracles are generated rather than hand-typed, red failures are not-implemented assertions, and thresholds trace to D-004/D-006/D-008/A-009. T-017's production performance outcome and G-LISTEN's perceptual outcome are unknown by design and have explicit failure branches. Resulting risks: R-001–R-007. No L/K amendment is required because no premise was falsified.

---

# Amendment 03 — assumption and premise audit (4.7)

Separated adversarial pass by the planning agent (fresh-context agents unavailable, R-017). Each item was restated, its falsifying evidence named, and checked where checkable on 2026-11-19.

| Item | Premise | Falsifying evidence sought | Check performed | Verdict | Resulting IDs |
|---|---|---|---|---|---|
| A-013 | `61ab5ed` is the default-branch head with CI green on six jobs | a later default-branch commit or a red run | `git ls-remote origin HEAD` = 61ab5ed at intake; EXECUTION_LOG run 42078599189 | confirmed | — |
| A-014 | Scope items (a)–(f) are implementable without fretless | a scope item needing nonlinear contact | D-021..D-028 are linear per-mode terms | confirmed | — |
| A-015 | v1 presets need not sound identical | owner statement otherwise | intake answer 'defaults' adopted item 3 verbatim | confirmed | — |
| A-016 | Changed frozen tests go through 2E.4 | a weakened test | T-001, T-011, T-032 retired with records; no threshold edited | confirmed | D-030 |
| A-017 | The research document is a lead, not an authority | — | its tables failed two checks (C-013, C-014) | confirmed | C-013, C-014, C-015, C-027 |
| A-018 | G-LISTEN-2 can reuse the v1 12-pair protocol | broken v1 tooling | T-027/T-028 pass at planning; R-016 found demo `control` lines ignored → S-LISTEN-2 changed | confirmed (with R-016 change) | R-016 |
| A-019 | A-009 budget still achievable | measured T-017 over budget | not measurable before implementation | unverifiable | R-015, D-034 |
| A-020 | hobby; Guitar-TECHS CC BY 4.0 unchanged | licence change | v1 REFERENCES.json unchanged; not re-fetched this run | unverifiable | R-006 (v1), S-108 checksum rule |
| A-021 | stores `qualitycoding/lessons` and `qualitycoding/knowledge` exist and are readable | fetch failure | both fetched at recorded commits | confirmed | — |
| A-022 | push access granted | rejected push | six pushes verified with `ls-remote` | confirmed | — |
| A-023 | subject tags exist in store taxonomy | unknown facet | schema check passes on all amendment entries | confirmed | — |
| A-024 | fresh-context subagents available for cold read, pre-mortem, audit | agent failure | both cold-read agents failed with HTTP 429 before output | **falsified** | L-20261119T150000Z-review-agents-assumed-available, K-20261119T150100Z-subagent-review-capacity-rate-limited, D-035 |
| D-021 premise | humbucker comb with 2.5 dB imbalance matches measured depth | depth outside 15–25 dB | oracle: 16.9 dB | confirmed | C-019 |
| D-022 premise | engine μ and T come from solid-wire density on the open scale | different code | `Mapping.h` lines 39–47 read | confirmed | — |
| D-025 premise | T-035 series gain contract compatible with summed-coil RLC | T-035 requires 1/N gain | T-035 asserts series gain > 1.6, parallel ≈ 1; resonance shift predicted 680 Hz > 300 Hz | confirmed for the gain contract and the resonance values; the shift is not visible to T-035's peak search (see the T-035 resonance row, D-037) | D-037 |
| D-029 premise | v1 state has exactly 35 parameter attributes and descriptor 0 is `scale_length_mm` | count ≠ 35 | fixture: 35 attributes + schemaVersion; `src/engine.cpp:813` | confirmed | — |
| D-030 premise | T-004, T-033, T-034, T-035 survive | prediction failure | T-034 null indices 6/3 unchanged by D-021 (single coil at 108 mm); T-035 predicted shift 680 Hz; T-004/T-033 are direction-of-effect checks — not numerically predicted | unverifiable (T-004, T-033) | R-022, D-034 route |
| D-034 premise | a fixed gain constant does not break T-031 | T-031 absolute level | T-031 checks a ratio between master-gain settings | confirmed | — |
| C-025 | conductance mostly < 0.01 s/kg | contrary measurement | single Tier 1 source; no contrary source found | unverifiable | R-018 |
| C-026 | wood affects electric sound mainly via neck below 1 kHz | contrary measurement | single Tier 1 source | unverifiable | R-018 |
| C-028, C-029 | no measured joint/fingerboard effect | a measurement showing one | C-028 **falsified** on 2026-11-19 by a targeted search (Mottola 2007; Paté et al.); superseded by C-034. C-029: none found | C-028 falsified; C-029 unverifiable | C-034, L-20261119T160200Z-absence-of-evidence-without-targeted-search, K-20261119T160000Z-c-034-neck-joint-evidence, R-011 |
| C-030 | hollow/semi bridge conductance significant up to 2 kHz | contrary measurement | single Tier 1 source | unverifiable | R-018 |
| Frozen premise (T-045) | rendered band ratios move by ≥ half the analogue |H| prediction | partial distribution differs between renders | same note and pickup in both renders; only the load changes | confirmed (argument) | — |
| Frozen premise (T-048) | polarisation beating cancels between solid and hollow renders | different beating | same seed and splitting in both renders | confirmed (argument; measured 6.603 vs 6.598 dB/s after D-037) | — |
| Frozen premise (T-048 allocation) | MIDI 45 in the test plays on string index 4 | test events on a channel that selects another string | **falsified** at S-104: channel 1 selects string 0 (D-013) | falsified | D-037, R-023, L-20261120T090000Z-oracle-premise-not-run-on-the-tests-actual-input |
| Frozen premise (T-035 resonance check) | the series/parallel resonance shift is visible as the dominant frequency in 1000-3500 Hz | another partial dominates both renders | **falsified** by planner prediction before S-105 (1319 Hz dominates both) | falsified | D-037 |

## Falsified item handling

A-024 → lesson and knowledge item written; amendment D-035 changes how S-REVIEW and S-ADVERSARIAL obtain fresh context. Re-run after D-035: mechanical cold-read script (no new items) and a pre-mortem pass over S-REVIEW/S-ADVERSARIAL (round 4 addendum below). Audit pass 2 over the changed set (A-024/D-035): D-035's fallback is executable without the planner; verdict confirmed.

Post-audit correction (2026-11-19, owner question): C-028 falsified → superseded by C-034. D-023's implementation is unchanged because its bounded, claim-free design already matches 'small and inconsistent'; only its wording and basis changed, so no re-freeze or re-plan was needed (no test depends on C-028).

Post-audit correction (implementation, S-103): the D-030 premise 'no other frozen test is challenged at planning time' was falsified by T-022 → D-036. Re-checked by a full sweep of hashed files; no further hit.

Post-audit correction (implementation, S-104): two frozen-test premises falsified (T-048 string allocation; T-035 resonance visibility) → D-037.

Post-audit correction (implementation, S-106): frozen premise 'T-021's sanitizer evidence is satisfiable by a truthful log of the amended suite' falsified → D-038; v1 evidence integrity question → R-024.

| Frozen premise (T-021) | a truthful sanitizer log of the amended suite satisfies T-021 | literal count, self-reading, T-017 timeout | **falsified** at S-106 | falsified | D-038, R-024 |

Post-audit correction (frozen-test audit, 2026-11-20): frozen premises falsified — T-007 (note on the high-E string), T-037 (decay direction), T-045/T-035 (rectangular band measurement), T-027 (hard-coded seed) — and the D-013 channel rule's fitness for channel-1 input (R-023) → D-039.

| Frozen premises (T-007, T-037, T-045/T-035 measurement, T-027 seed) and D-013 channel rule | each holds on the amended engine with correct allocation | audit runs on real inputs | **falsified** 2026-11-20 | falsified | D-039, R-023 |

Counts (28 items): 15 confirmed, 7 falsified, 6 unverifiable (the D-030 premise row moved from unverifiable to falsified; two premise rows added) (24 items; the C-028/C-029 row counts once each way).
