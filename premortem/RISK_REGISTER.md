# Risk register

| ID | Description | Lens | Severity | Likelihood | Root cause | Trace/mitigation |
|---|---|---|---|---|---|---|
| R-001 | Instrument passes spectral tests but sounds synthetic | Audio/research | Medium | Medium | Limited model/reference coverage | SC7, T-026–T-028, G-LISTEN; stop/rescope after three rounds |
| R-002 | Exact Windows 11 desktop host defect escapes CI | CI/operational | Medium | Medium | No hosted Windows 11 x64 runner | D-014, S-004 Windows 11 host responsibility, honest limitation |
| R-003 | P2 distribution differs from P1 | Research | Medium | Medium | Recording/performance variation | D-007/D-012, T-023; report shift, never fit P2 |
| R-004 | 16-voice performance misses conservative budget | Performance | Medium | Medium | Modal cost at high rates/polyphony | T-017, D-012 mode reduction then block |
| R-005 | Pinned dependency later gains Critical/High vulnerability | Supply chain | High impact, Medium residual severity after control | Low | Upstream disclosure | T-019, S-CI fixed-version amendment or halt |
| R-006 | Listener unavailable | Audio/human | Medium | Medium | A-006 cannot be proven in advance | G-LISTEN blocks realism claim; proceed-with-rescope/stop only |
| R-007 | Ephemeral mount loses executables or uncommitted work | Operational | Medium | Medium | Recycling/non-executable storage | S-000 restaging, durable commits, push/verify every green chunk |

No Critical/High unmitigated risk remains; R-005 has a blocking control and is not silently accepted.

## Amendment 03 risks (run 20261111T150746Z-guitar-physics-research)

| ID | Description | Lens | Severity | Likelihood | Root cause | Trace/mitigation |
|---|---|---|---|---|---|---|
| R-008 | Frozen v1 case logic in `src/contract_main.cpp` could be edited without detection (only wrappers were hashed) | Integrity | High | Medium | v1 manifest scope | D-032: contract_main.cpp and test_amendment.py now hashed; CI job S-101 shown to fail |
| R-009 | Replacing the v1 excitation with the physical pluck/velocity law changes timbre enough to fail T-026 (calibrated on v1) | Technical/audio | High | Medium | v1 constants were calibrated to references; amendment changes spectral slope | D-034 three-iteration rule inside fixed physics, then TEST_CHALLENGE; S-104 records T-026 values; S-108 feature comparison before listening |
| R-010 | Two-element RLC overstates humbucker resonance (eddy currents not modelled) | Research | Medium | Medium | C-018, D-024 | G-LISTEN-2 question 3; amendment request route (D-034) |
| R-011 | Neck-joint and fingerboard controls imply tonal effects research does not support | Research/integrity | Medium | High | Owner scope A-014 vs C-028/C-029 | D-023 bounds below specimen spread; no claims in names or docs; S-REVIEW checks wording |
| R-012 | Five v1 lesson/knowledge files lack front matter and would fail the store schema check at S-KNOW | Process | Medium | High | v1 run wrote them free-form | S-RETRO normalises them before G-003 |
| R-013 | Structural-loss coefficients (neck modes, bridge conductance) are a parameterisation; individual guitars differ by ±50 Hz and support conditions | Research | Medium | High | C-024, C-027 | A-008 wording; D-022 values inside measured ranges; listening gate |
| R-014 | Velocity transduction raises upper-partial level; with the hollow-body/series/high-load worst case the safety clipper is driven harder (planning: pre-safety peak 2.88 on v1 engine) | Technical | Medium | Medium | D-026 adds +6 dB/octave | T-051 guard and T-009; S-105 records pre-safety peak; gain staging unchanged (D-006) |
| R-015 | Electrical biquad per pickup adds cost and may push T-017 over A-009 on macOS/Windows runners | Performance | Medium | Low | D-025 adds 1–3 biquads per voice-sum path | D-034 rule (AVX2 path, then mode reduction); never relax budget |
