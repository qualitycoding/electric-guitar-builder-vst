# Assumptions and intake defaults

The user answered the required task and supplied repository access. Optional decisions were resolved by these defaults; no further intake question is needed.

- **A-001 — Format and framework.** VST3 and a headless renderer use JUCE 8.0.15 and C++20. Consequence: reproducible cross-platform builds; AU/AAX/VST2 are excluded.
- **A-002 — Open-source licensing.** Project code is AGPLv3 so the JUCE open-source option is compatible. Consequence: a closed-source release would require a separate licensing decision outside this plan.
- **A-003 — Supported systems.** Windows 11 x64, macOS 15 ARM64 and Ubuntu 24.04 x64. Consequence: each maps to a CI job; mobile and older systems are unsupported.
- **A-004 — Instrument geometry.** Six strings, 24 frets, standard tuning, per-string offsets of ±12 semitones. Consequence: fret size changes termination/contact, not equal-tempered fret spacing.
- **A-005 — Polyphony and rates.** Sixteen voices at 44.1–96 kHz and host block sizes 1–2048 samples. Consequence: voice stealing and preparation are tested at these boundaries.
- **A-006 — Listener.** The repository owner or their delegate performs `G-LISTEN` on headphones. Consequence: implementation cannot declare perceptual realism without that response.
- **A-007 — Reference licence.** Guitar-TECHS v1 CC BY 4.0 may be windowed, loudness-matched and redistributed with attribution. Consequence: only DI tracks enter the reference bundle.
- **A-008 — Construction fidelity.** Material names select documented, bounded acoustic parameterisations; they are not claims of independently measured wood science. Consequence: global listening validates the instrument, while analytic tests validate each control's implementation.
- **A-009 — Performance budget.** Sixteen voices must render below 0.80 real-time factor on the specified CI benchmark class. This is an intentionally conservative project budget, not a measured claim about existing code; a miss requires optimisation, not silent relaxation.
- **A-010 — Storage.** Lessons and knowledge accumulate on the branch and are proposed for `qualitycoding/Lessons` and `qualitycoding/knowledge` at `G-003`.
- **A-011 — Release.** No external or irreversible release action is included. Consequence: `G-002` is not required; adding binaries/releases requires a plan amendment and that gate.
- **A-012 — Planning review capacity.** No subagents or alternate model tiers are available. The single available model performs separated mechanical and adversarial passes and records tier substitutions. Consequence: independent human review remains valuable but is not made a new gate.
