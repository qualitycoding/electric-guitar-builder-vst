# Cold read — amendment 03

## Tier substitution (Rule 5)

Pass 1 was dispatched to two fresh-context agents (dry-run reader and mechanical checker). Both stopped with an API rate-limit error before producing any output. Under the protocol's tier-fallback rule the planning agent ran both checks itself as separated passes, recorded in `.checkpoints/state.json` `tier_substitutions`. This is weaker than a fresh-context read; R-017 carries the residual risk and HANDOFF.md tells the implementer to raise any question as `BLOCKED.md`.

## Pass 1 (mechanical script + self dry run)

Mechanical script (ID resolution, paths, step order, template fields, swallow idioms, stale phrases): 20 findings. 8 fixed (short file names → full paths; demo files listed explicitly); 12 accepted with reasons (D-015/D-019 named only as skipped; `BLOCKED.md`/`TEST_CHALLENGE.md` are halt artefacts created on failure; stale-phrase hits describe what is replaced or retired).

Dry run findings, all resolved by amending the plan:
1. S-105 claimed `src/contract_main.cpp` calls `pickupSpec`; grep shows no hashed file does. Wording corrected.
2. Event-file `control` lines are parsed but never applied by the renderer (`src/engine.cpp` 950–967), so demos cannot sweep a parameter through event files. S-LISTEN-2 now specifies an `egb_demo` tool with a fixed CLI and per-setting renders, with a check that settings actually differ; v1 palm-mute and pick-angle demos are re-rendered. New risk R-016.
3. The neck-joint demo difference check could fail by design (D-023 bounds effects below specimen spread); its post-condition now requires a non-zero waveform difference instead of a 0.5 dB band difference.
4. D-025's 20 ms coefficient ramp conflicted with D-005 ('no coefficient rebuild' on the audio thread); D-025 now states a bounded, allocation-free exception, still gated by T-013/T-014.
5. S-LISTEN-2 lacked `Exclusive resources`; added.

## Pass 2 (mechanical script + self dry run on the amended plan)

Mechanical script: the 12 accepted findings only; no new items. Dry run: no new questions, undefined terms, missing inputs or unstated credentials found. Pass 2 returns zero unresolved items.
