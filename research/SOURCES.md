# Sources and evidence class

1. Planning protocol v3.11, qualitycoding/skills commit `108db6313f24293e9b161ec5bdf6c4aac2af3e06`: process authority.
2. `audio-blind-listening-validation` from that commit: listening-pair construction, disclosure, iteration and evidence requirements.
3. JUCE repository, commit `91ad83ae34a81e0833b1a2b0866f54846370ae53`: framework pin and AGPLv3 open-source compatibility basis; implementer rechecks the pin before fetch.
4. Guitar-TECHS v1, Zenodo record `14963133`, CC BY 4.0: primary reference-audio source. Publisher checksums and local P1 verification are in `research/audio/REFERENCES.json`.
5. `research/spikes/reference_metrics.json`: 138 analysed P1 notes; measured onset/attack and reference spread.
6. `research/spikes/model_spike.json`: executable architecture feasibility evidence, not proof of production realism.
7. GitHub hosted-runner documentation: versioned labels `ubuntu-24.04`, `ubuntu-24.04-arm`, `windows-2025`, `macos-15`; Alpine 3.22 is the libc-variant container.

No source supports a claim that a material choice exactly reproduces a commercial guitar, that every construction variable is isolated in the dataset, or that the Python spike is the production engine.

## Amendment 03 sources (working list; the source register is `knowledge/K-20261119T120000Z-source-register-guitar-physics.md`)

8. Owner research document 'Electric Guitar Audio Synthesis' (Google Doc 1tCDHtA7Mai4Vhsk2WKa8Z3E5fIw5jxmrWAmg4bAZY0k): lead only (A-017).
9. M. Zollner, *Physics of the Electric Guitar*, ch. 5 (parts a, b, c) and ch. 7, GITEC English edition PDFs: Tier 1 monograph; locators in `research/claims.json`.
10. J. D. Tillman, 'Response Effects of Guitar Pickup Position and Width' (till.com, 2000/2002).
11. H. E. W. Lemme, 'The Secrets of Electric Guitar Pickups' (buildyourguitar.com re-host of the 1986 *Electronic Musician* article, © Lemme).
12. H. Fleischer, 'Dead spots of electric guitars and basses', ASA/EAA/DAGA 1999 (acoustics.org pressroom).
13. C. Traube and J. O. Smith III, 'Extracting the fingering and the plucking points on a guitar string from a recording', IEEE WASPAA 2001.
14. P. Biltoft, 'Pickup Inductance' (Planet Z) and OzValveAmps 'Pickups': Tier 4 inductance ranges, used only as non-load-bearing defaults (C-016).
15. Command verification: JUCE pin and toolchain unchanged from `plan/ENVIRONMENT.md`; new commands verified in `research/spikes/` (1.3.6).
