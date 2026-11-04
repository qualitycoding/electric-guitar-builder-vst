# Attribution

## Guitar-TECHS reference dataset

Reference audio and MIDI used for calibration (P1) and held-out validation
(P2) come from the **Guitar-TECHS** dataset:

- Record: Zenodo **14963133** — https://zenodo.org/records/14963133
- Licence: **CC BY 4.0** — https://creativecommons.org/licenses/by/4.0/
- Citation: Guitar-TECHS: a multitrack dataset of electric guitar techniques
  (direct-input recordings with aligned MIDI annotations).

Per the licence terms, attribution to the Guitar-TECHS authors is required for
redistribution of the reference material. This project uses the
`directinput_allsinglenotes` reference renders for metric extraction only
(onset alignment, one-third-octave band profiles, attack estimation); no
reference audio is embedded in or shipped with the plug-in.

Local cache (not committed): `reference/P1_singlenotes`, `reference/P2_singlenotes`
under the development machine's reference cache directory.

## JUCE

The VST3/headless targets build against the JUCE framework (modular subset,
compiled directly). JUCE is distributed under the ISC-style JUCE licence;
see `third_party/JUCE` / the JUCE module headers for the full licence text.

## Tooling

- CMake, Ninja — BSD-style licences.
- Python packages pinned in `requirements-lock.txt` (numpy, scipy, soundfile,
  mido, cmake, ninja) — their respective OSI licences.
