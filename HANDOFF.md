# HANDOFF — electric-guitar-builder-vst, G-LISTEN gate state

Date: 2026-11-05. Outcome of G-LISTEN: **STOP after round 3 of 3** —
all three listening rounds failed the ≤8/12 indistinguishability
criterion. The listener (user) has stopped the gate and wants a more
capable agent to propose a synthesis change. This document is the
briefing.

## 1. Repository state (verified on the remote)

- Implementation branch: `impl-20261104T030000Z`, head `d2f5ca3`
  (round-3 change `c160195` on top of `48f6211` ← `1b26c09` round 2).
- Evidence branch: `gate-evidence/G-LISTEN`, head `41d1ad3`
  (round-3 result commit; full listening history in `GATE-G-LISTEN.md`).
- Both verified via `git ls-remote` at the time of writing.
- 30/30 frozen contract tests green on the release binary, and
  genuinely rerun under ASan and UBSan (`reports/asan_suite.txt`,
  `reports/ubsan_suite.txt`, two-pass bootstrap per D-7/D-12).
- All gates passed except G-LISTEN. pluginval could not be executed in
  this environment (403 on release assets) — documented honestly in
  `reports/pluginval.txt` (D-8).

## 2. What the system is

A construction-controlled six-string electric-guitar VST3 plus a
deterministic headless renderer (`egb_contract` binary, driven by
`EGB_CONTRACT_BIN` through `python3 -m unittest discover -s tests -v`).
Construction parameters (scale, gauge, fret height, neck, pick angle,
pick depth, palm mute, velocity) flow through
`include/egb/Mapping.h::computeMapping` into per-mode modal synthesis in
`src/engine.cpp`. Reference playing style is derived from the licensed
Guitar-TECHS dataset (ATTRIBUTION.md, Zenodo 14963133, CC BY 4.0);
P2 single-note audio + MIDI live in a cache and are read by T-027.

Frozen artifacts — never modify: `tests/test_contract.py`,
`tests/fixtures/*`, `research/spikes/expected_values.json` (oracle pins
`computeMapping` outputs at 1e-12 only; rendered audio is NOT pinned).

Working rules that still bind any future agent: commit + push + verify
(`git ls-remote`) after every green chunk; no fabrication of tests,
logs, or results; deviations/lessons recorded in DEVIATIONS.md /
lessons/ / knowledge/.

## 3. G-LISTEN gate and the three rounds

Gate spec (`GATES.md`): 12 A/B pairs per round (which side is the real
Guitar-TECHS reference?), 44.1 kHz / 24-bit / 1.0 s / −23 dBFS RMS /
10 ms end fade; seed = 20261104 + round; **proceed only with ≤8/12
correct and no unresolved realism finding**; max 3 rounds, one general
mechanism change per round (DECISIONS.md diagnosis order: onset →
harmonic decay → pickup/body); after a third failure only
proceed-with-rescope or stop. The user chose **stop**.

| Round | Seed | Score | Listener's words | Mechanism changed |
|-------|------|-------|------------------|-------------------|
| 1 | 20261104 | 10/12 | "all samples sound reed-like" | none (baseline) → iterate |
| 2 | 20261105 | 12/12 | "reed-like again, chirp, doesn't sound picked" | harmonic decay: internal-friction term `0.8+0.025m+0.018m²` dB/s (D-11) |
| 3 | 20261106 | 11/12 | "still reed-like; timbral difference pronounced, attack now comparable" | onset/envelope: immediate shaped pick click + initial fast-decay body envelope (D-12) |

Full per-round keys, responses, p-values, and WAV hashes:
`gate-evidence/G-LISTEN/GATE-G-LISTEN.md`.

## 4. The residual defect, as established by three rounds

- Discrimination stayed high throughout (83% → 100% → 92%) and the
  listener's complaint stayed "reed-like" throughout — the audible gap
  is in the **sustained state**, not the attack. Round 3 explicitly
  confirmed the onset now matches ("attack is comparable"); the
  listener still identified 11/12 from sustained timbre alone.
- Round 2 killed the high-partial sustain (partials now decay in tens
  of ms). Round 3 killed the onset swell and added a physical initial
  decay. Neither touched the **body/pickup stage** — the third item in
  DECISIONS.md's diagnosis order, never reached because the gate caps
  iterations at three.
- Likely remaining gap (hypothesis, not established fact): the modal
  body is a bank of exponentially decaying sinusoids with per-mode
  decay and static pickup/fret filtering. A real string's sustained
  state is not: it has nonlinear coupling between modes (stretching,
  fret/contact intermittency), time-varying termination, and a pickup
  that imposes its own comb/coloration plus magnetic nonlinearity.
  Round-2/3 changes shaped the envelope; nothing shaped the *spectrum
  of the sustained tone*, which is where the listener keeps hearing
  "reed" (a reed sustains with a static harmonic spectrum; a plucked
  string's sustained spectrum is alive — beating, drifting, decaying
  unevenly across partials).
- Supporting measurement from round 3: the candidate's fundamental
  barely decayed (≈0.84 dB/s at m=1); after the initial-decay envelope
  the 1 s tail is plausible in level but still spectrally static.

## 5. Where to look first (for the next agent)

1. `GATE-G-LISTEN.md` on the evidence branch — the complete listening
   record.
2. `DEVIATIONS.md` D-11, D-12 — exactly what was changed in rounds 2/3
   and why (with calibration sweeps).
3. `src/engine.cpp` — `buildVoice` (click generation block, round 3),
   `renderBlock` pass 2 (envelope: attack ramp × initial-decay ×
   amplitude, click added unramped), mode loop (SSE2 and scalar paths).
4. `include/egb/Mapping.h` — `computeMapping` (frozen oracle pins these
   outputs), `modeDecayDbPerS` (round-2 mechanism).
5. `src/contract_main.cpp` — T-005 (onset energy vs depth), T-026
   (attack measurement: 10–90% of a 20 Hz one-pole-smoothed envelope,
   gate [8.208, 31.542] ms; band-RMS gate 24.538530602719486 dB),
   T-027 (pair builder; note it only writes `pairs/KEY.txt` if missing —
   `rm -f pairs/KEY.txt` before regenerating).
6. Calibration gotchas learned the hard way: T-026's attack measurement
   collapses onto any loud immediate click above ~+6 dB over
   pick_noise_db (+4.0 dB was the sweet spot, ~17.8 ms); a prominent
   early click also breaks T-005's "first-5 ms energy increases with
   pick depth" unless click gain tracks picking amplitude.

## 6. Constraint surface for any proposed change

- One general mechanism change per gate round; the user may define a
  new gate round sequence, but the existing G-LISTEN record stands as
  failed (stop was recorded at evidence head `41d1ad3`).
- Any change must keep 30/30 contract tests green (release + ASan +
  UBSan, regenerate the sanitizer logs with
  `scripts/bootstrap_sanitizer_logs.sh`) and regenerate pairs/demos via
  the T-027/T-028 paths with a fresh seed.
- Do not "fix" the residual realism gap by weakening pair production
  (fade shape, normalization, note selection) — that path was
  identified and explicitly rejected as gate-gaming in round 3.
- Environment: cmake restaged at `/var/tmp/cmakepkg/bin/cmake` (wiped
  on container recycle — restage from `.tools/cmake/data`); sanitizer
  builds configured with `-DCMAKE_CXX_FLAGS="-fsanitize=address|undefined
  -fno-omit-frame-pointer"` into `/var/tmp/egb-{asan,ubsan}`; use
  detached `setsid nohup` retry loops for anything network or long-
  running (github.com:443 is intermittent; api.github.com is stable).
