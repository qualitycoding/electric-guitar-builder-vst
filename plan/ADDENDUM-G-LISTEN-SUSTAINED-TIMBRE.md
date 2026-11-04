# G-LISTEN addendum — sustained-timbre diagnosis and ranked repair plan

Date: 2026-11-05  
Status: implementation guidance after the recorded **STOP** at G-LISTEN  
Applies to: `impl-20261104T030000Z`  
Review baseline: commit `492852093629c151ed9aced220ead61751297e52`

This addendum preserves the existing three-round gate result. It does not authorise a fourth round under the old sequence, modify frozen tests, or claim that any proposed mechanism has passed listening. A new listening sequence and fresh seeds require owner authorisation.

## 1. Finding

The HANDOFF correctly locates the residual defect in sustained timbre: round 3 made attack comparable, but the listener still identified 11/12 references and reported a pronounced reed-like sustained tone. Source inspection strengthens that hypothesis into several confirmed implementation defects.

The 30/30 contract result does not clear these defects. Some tests prove only that a parameter changes output, not that its specified physical stage is connected or correct.

### 1.1 The two polarisations collapse to one static oscillator per mode

At review-baseline `src/engine.cpp` lines 268–296, both polarisations have the same frequency and are merged with an exact trigonometric identity. The resulting single sinusoid cannot produce inter-polarisation beating, a changing polarisation orbit, or two-stage decay from unequal polarisation damping. Each mode is therefore only an exponentially decaying sinusoid.

This is the most direct implementation explanation for the static/reed-like sustained state.

### 1.2 Pickup sensing uses open scale instead of fretted speaking length

At lines 223–228, `speakingM` is calculated and discarded. At lines 241–258, pickup position is divided by `tables.scaleM`. Fretting changes frequency without correctly changing the pickup's fractional sensing position or modal comb.

### 1.3 Computed pickup/body/master stages do not process audio

- `vPickupFilter[]` is copied into each voice but never applied.
- `vBodyGain` is calculated but never used.
- `vMasterLin` is calculated but never used.
- The final loop at lines 480–485 measures peak and applies `tanh`, despite a comment claiming body/master processing.

The rendered instrument is therefore much closer to an untreated modal bank than to the planned pickup/body architecture.

### 1.4 The tests miss the omissions

T-003 accepts any maximum output difference above `1e-7` as a measurable construction effect. T-004 checks waveform differences and broad HF energy, but not pickup electrical resonance or correct fretted-position comb behaviour. Green tests therefore do not establish signal-path completeness.

## 2. Ranked solutions

### Rank 1 — Restore genuine dual-polarisation sustained-string dynamics

**Highest expected impact on the specific static/reed-like discriminator.**

Maintain two independent modal states per mode with:

- slightly different frequencies;
- unequal damping coefficients;
- independent initial amplitudes and phases;
- pick-angle-dependent energy distribution;
- separate pickup projection coefficients.

Do not merge the polarisations unless frequency, envelope and pickup coefficients are genuinely identical. A suitable starting model is `f[m,v]=f[m]`, `f[m,h]=f[m]+delta_f[m]`, with bounded slowly mode-dependent splitting and separate decay multipliers. Calibrate globally on P1 only, never per note or listening pair.

Expected observable results are deterministic beating, non-monotonic partial envelopes and sustained spectral evolution after the onset. Do not substitute random vibrato, chorus or an arbitrary LFO: those imitate movement without repairing the string mechanism.

Research basis:

- Trautmann and Rabenstein, *Multirate Simulations of String Vibrations Including Nonlinear Fret-String Interactions Using the Functional Transformation Method*, EURASIP JASP 2004. Reports approximately 0.25 Hz fundamental polarisation splitting in an electric-guitar experiment. https://asp-eurasipjournals.springeropen.com/articles/10.1155/S1110865704402114
- Välimäki et al., *Plucked String Models: From the Karplus-Strong Algorithm to Digital Waveguides and Beyond*, discusses mistuned dual-polarisation beating and pickup-output waveguide models. https://research.aalto.fi/en/publications/plucked-string-models-from-the-karplus-strong-algorithm-to-digital/

### Rank 2 — Complete and correct pickup/body/output processing

**Highest-certainty correctness fix and lowest architectural risk; required regardless of listening outcome.**

1. Divide pickup distance from the bridge by `speakingM`.
2. Keep separate modal output accumulators for enabled pickups.
3. Process each pickup through its electrical resonance filter.
4. Apply phase and parallel/series combination after sensing/electrical response.
5. Apply a bounded neck/body filter or resonance network.
6. Apply `vMasterLin` before the safety stage.
7. Make series gain and shared loading agree with D-013.

Separate pickup accumulators are necessary when pickup filters differ; applying one filter after precombining the pickup combs is not equivalent. Process only enabled pickups and profile before optimising.

Static filtering alone may not remove the reed-like quality, but leaving these stages disconnected invalidates construction-control and reference-calibration assumptions.

### Rank 3 — Add passive nonlinear string/termination coupling

Use only if ranks 1–2 improve the result but a sustained-state finding remains. Add one bounded mechanism per iteration:

1. amplitude-dependent tension modulation;
2. weak transverse-to-longitudinal coupling and phantom partials;
3. passive bridge/fret contact or intermittent termination at high amplitude.

These mechanisms can couple partial envelopes and create new spectral components. They carry greater stability, tuning and performance risk than ranks 1–2 and are not the first repair.

### Rank 4 — Replace the string core with coupled dual-polarisation digital waveguides

Fallback if two modal polarisations plus separate pickup paths cannot meet T-017 or the listening requirement. Use independent fractional-delay tuning and loop-loss filters, passive bridge coupling, and explicit pluck/pickup transfer functions. This is a substantial rewrite and is not preferred before the localised repairs.

## 3. Required execution order

### A. Establish a correctness baseline (rank 2)

Implement the signal-path repairs without claiming a listening improvement. Add new tests through the formal amendment machinery; do not edit existing frozen files in place. At minimum, the new tests must fail on review baseline `4928520` and verify:

- exact master-gain ratios in rendered audio;
- pickup electrical resonance at the specified centre frequency;
- body-response output effect independent of body decay;
- pickup-null movement with fret/speaking length;
- parallel/series gain and loading contracts.

Run all existing tests plus the amended tests on release, ASan and UBSan builds. Commit, push and remote-verify the correctness baseline separately.

### B. Test the sustained-tone mechanism (rank 1)

Without changing onset again, add true dual polarisation and tests for:

- deterministic beating at a specified small frequency splitting;
- two-stage decay under unequal polarisation damping;
- pick angle changing polarisation energy distribution;
- finite bounded output and T-017 performance.

Evaluate per-partial envelope curvature, beating depth and spectral-shape variation during 0.2–0.9 s in addition to the existing average one-third-octave metric. Do not tune to P2 or blind-pair clips.

### C. Run a new authorised listening sequence

Preserve the old stopped record. Use fresh seeds, regenerate pairs/KEY (remove the stale key before regeneration), and retain onset/normalisation rules. Do not alter pair production to make discrimination harder. A quantitative pass never overrides an unresolved qualitative realism finding.

### D. Escalate only on evidence

If sustained-state criticism remains, try rank 3 as one mechanism change. Keep rank 4 as the architecture fallback. Do not make another attack/click/global-envelope adjustment: round 3 already established that attack matching does not address the remaining discriminator.

## 4. Evidence limitation

The inspected evidence-branch commits contain `GATE-G-LISTEN.md` but not the referenced WAV payloads. This diagnosis therefore rests on the recorded listener findings and source inspection, not a new independent listening test or audio-feature analysis.
