# Profile and scope

## Status

- Active profile: `software` — the deliverable is a maintainable VST3 instrument and deterministic renderer.
- `audio = true` — the deliverable generates audio; `S-LISTEN` and `G-LISTEN` are mandatory.
- `software.deploys = false` — the plan builds and tests artefacts but does not release, publish, sign, notarise or deploy them.
- `math.exploration = false`, `courseware = false`.
- Environment: `ephemeral`; only repository commits and the durable mount are trusted across turns.

## Goal

Build a six-string electric-guitar instrument whose timbre is controlled by construction and playing parameters, not by selecting a named guitar model.

## In scope

VST3 on Windows x64, macOS ARM64 and Linux x64; a headless renderer using the same C++ engine; 16 voices; 24 frets; standard tuning plus per-string MIDI tuning offsets; construction, pickup and playing controls; deterministic event files; state persistence; CI; reference comparison; blind listening and demos.

## Out of scope

Amplifier, cabinet, effects, acoustic-guitar radiation, sample streaming, machine learning, seven/eight-string guitars, MPE, microtonal fret layouts, AAX/AU/VST2, installer/signing/notarisation and public release. These are not silent future promises.

## Success criteria

1. Every requested construction control is host-automatable, persistent and has a measured, bounded effect in the isolated engine stage.
2. Pick angle and depth alter attack/contact envelopes; palm mute is continuous from light to heavy and changes both damping and spectrum without zipper noise.
3. MIDI 40–88 produces the intended 12-TET pitch within 0.01 cents at the string model, with stable finite audio at 44.1, 48, 88.2 and 96 kHz.
4. The shipped signal path, without renderer-only normalisation, remains finite and at or below 0 dBFS in the frozen worst-case polyphonic test.
5. No audio-thread allocation, lock, file/network access or non-real-time state-tree operation; deterministic offline renders repeat bit-identically on the same build.
6. CI builds and tests every declared platform/architecture, with versioned runners and no swallowed failures.
7. Reference metrics pass frozen thresholds, and `G-LISTEN` passes with no more than 8 of 12 correct reference identifications and no unresolved qualitative realism finding, or the project stops/rescopes at that gate.

## Users, maintenance and data

Users are composers and sound designers working in VST3 hosts. Versioning is SemVer; no release is authorised by this plan. The instrument processes local MIDI/state only, collects no telemetry and retains no personal data. Reference audio is used only under its recorded licence and attribution.

## Threat model

Untrusted host state and event files may be malformed or excessively large; dependencies may contain known vulnerabilities; audio parameters may be NaN or out of range. No authentication boundary or network service exists. Clamp/reject at boundaries, cap input sizes, and never execute preset/event content.

## N/A sections

Mathematical specification/proofs, computational figure specification, publication/manuscript/novelty, courseware/learner trial and deployment operations are N/A. No plan step may require their artefacts.
