# Amendment 03 — research round 3 (adversarial pass and empirical verification)

## R5 — adversarial pass on load-bearing claims

The adversarial reading looked for evidence against each load-bearing claim among the sources already opened, and for known errata.

- C-010 (velocity): Zollner §5.5.5 adds that the magnet's nonlinearity bends the flux curve at large excursions. This does not falsify velocity transduction for small excursions; nonlinearity stays out of scope (D-024).
- C-011/C-012 (load model): Zollner §5.9.2 shows eddy currents lower the resonance peak, strongly on some humbuckers. The two-element model overstates humbucker Q. Mitigation: per-type eddy loss as a parallel resistance is rejected for v2 (no measured values in text form); the risk is carried as R-010 and the listening gate.
- C-019 (humbucker comb): Lemme ('sensing at two points has a much smaller effect') against Zollner ('highly significant treble loss on the bass strings'). Contradiction on magnitude, not mechanism. Resolution: the mechanism is a geometric identity (spike-verified), and the unequal-coil weight 10^(−2.5/20) from Zollner keeps the notch finite; magnitude is judged at G-LISTEN-2.
- C-024/C-027 (neck modes): the research document assigns maple 245/480 Hz and mahogany 195/390 Hz. Zollner shows the frequencies vary by specimen and support by tens of hertz. The document's values are rejected as wood facts; D-022 keeps two neck-material frequency sets inside the measured 200/450 Hz ± 50 Hz spread and labels them as parameterisation (A-008).
- C-028/C-029 (joint, fingerboard): no measured support found; the only measurement found contradicts the document. D-023 implements the owner's requested controls as bounded parameterisations of the neck-mode model, labelled, with effects no larger than measured specimen spread, and records the evidence gap (R-011).

## R6 — empirical verification

`research/spikes/physics_oracle.py` (output `research/spikes/physics_oracle_stdout.txt`, `research/spikes/physics_expected.json`) verifies by computation: the document's RLC numbers (C-033), the factor-two table errors (C-013, C-014), the loaded-resonance range of the chosen defaults (C-017), the bearing-absorption range (C-023), the pluck amplitude law by numerical Fourier integration (C-022), and the humbucker identity (C-019).

## Saturation

Round 3 produced no new load-bearing claim and no unresolved contradiction (the C-019 magnitude contradiction is resolved by D-021 and carried to the listening gate). Research stops after round 3.

## Sources checked

| Source | URL | Accessed | Outcome | Note |
|---|---|---|---|---|
| (no new external sources; adversarial pass over round 1–2 sources) | — | 2026-11-12 | — | — |
