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
