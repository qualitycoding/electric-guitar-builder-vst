# Pre-mortem round 1

Separated adversarial pass under A-012 tier substitution.

## Incident report

Six months after delivery, users reject the instrument despite every test passing. Different material settings produce arbitrary rather than reproducible results, Windows 11 hosts expose untested behaviour, and the spectral median concealed individual unrealistic notes. Root causes were qualitative coefficient freedom, runner/OS conflation and treating metrics as perceptual proof.

## Lenses and findings

- Technical/research: D-013 was needed to close coefficient and allocation freedom; C-004/C-005 remain feasibility only. **High before mitigation, resolved.**
- CI/platform: Windows Server 2025 cannot be called a Windows 11 desktop trial. D-014 waiver added. **High before mitigation, resolved.**
- Performance: inconsistent RTF numbers could make a passing implementation miss the real criterion. ENVIRONMENT now matches A-009. **High before mitigation, resolved.**
- Integrity/listening: median metrics could hide bad outliers. S-LISTEN requires both score and zero unresolved qualitative findings; individual spike distances were disclosed. Medium residual.
- Security/operations: malformed state/events and resource exhaustion are bounded by T-011/T-012/T-015/T-016 and adversarial review. No network/auth/personal-data surface. Medium residual only for novel host behaviour.
- Past lessons: credential and modal/filter lessons are explicitly attached to relevant steps; no unapplied loaded lesson found.

Round result after hardening: 0 Critical, 0 High; residual items entered in the risk register.
