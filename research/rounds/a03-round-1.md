# Amendment 03 — research round 1 (breadth)

Run `20261111T150746Z-guitar-physics-research`. R0 is recorded in `research/PRIOR_KNOWLEDGE.md` (Amendment 03 section). Question tree: `research/QUESTION_TREE.md`, branch Q6.

## R1 — decomposition (see Q6 in the question tree)

Q6.1 pickup electrics and load; Q6.2 velocity transduction; Q6.3 position, aperture and humbucker spatial sampling; Q6.4 neck and body structural loss (dead spots); Q6.5 neck joint, fingerboard, body type; Q6.6 pluck position; Q6.7 verification of the research document's own numbers.

## R2 — findings

- Q6.7: the document's pickup-circuit numbers reproduce (single coil 3704 Hz, Q 2.51 against its 3.70 kHz and 2.53). Its aperture table gives the first null as f0·L/w; its own formula and code give 2·f0·L/w (×2 error). Its humbucker table gives 1405 Hz; its cosine term gives 2811 Hz (×2 error) and its printed S_hb formula divides by L twice (dimensionally wrong). C-013, C-014, C-033.
- Q6.2: Tillman, Lemme and Zollner §5.5.5 agree that the induced voltage follows string velocity (Zollner shows a rectangular voltage for a triangular displacement). C-010.
- Q6.1: Lemme and Zollner §5.5.4/§5.15 describe the pickup as L in series with R, shunted by the winding capacitance, loaded by pots, cable and amplifier: a second-order low-pass with a resonance of 2–5 kHz and −12 dB/octave above. C-011. Zollner's load model uses the volume and tone pots in parallel with the amplifier's 1 MΩ (111 kΩ for 250 kΩ pots, 200 kΩ for 500 kΩ) plus about 150 pF amplifier input capacitance and about 100 pF/m of cable. The document's single-pot load is therefore wrong. C-012, C-015.
- Q6.1: inductance ranges (Strat-type 1.8–2.5 H, PAF 2.8–4.5 H, P-90 4.9–6.8 H; one measured 1970s Strat 2.2 H, 6.5 kΩ, 110 pF) from Planet Z and OzValveAmps; coil capacitance 10–150 pF (Zollner §5.5.3) or 80–200 pF (Lemme). C-016, C-017.
- Q6.3: Tillman gives the point response sin(π·x·f/(L·f_open)) and the rectangular-width response with first null at f = 2·L·f_open/W. Zollner §5.4.4 measured windows of several millimetres, roughly Gaussian, with little effect for single coils below the ~5 kHz electrical limit; humbuckers sample at two poles 18–19 mm apart, with coil sensitivities differing by 2–3 dB, giving a comb notch where the pole spacing is half a wavelength and a clear treble loss on the bass strings. Lemme calls the two-point effect much smaller than the inductance effect (contradiction on magnitude only). C-019, C-020, C-021.
- Q6.6: Traube & Smith (IEEE WASPAA 2001, eq. 9) give the ideal pluck amplitude C_n = 2h/(n²π²R(1−R))·sin(nπR). C-022.

## Sources checked

| Source | URL | Accessed | Outcome | Note |
|---|---|---|---|---|
| Research document 'Electric Guitar Audio Synthesis' (owner) | https://docs.google.com/document/d/1tCDHtA7Mai4Vhsk2WKa8Z3E5fIw5jxmrWAmg4bAZY0k | 2026-11-11 | used | lead document; owner's material; tables partly wrong (C-013, C-014) |
| J. D. Tillman, 'Response Effects of Guitar Pickup Position and Width' | https://till.com/articles/PickupResponse/ | 2026-11-11 | used | point and width formulas; velocity statement; © 2000-2002 Tillman, no licence |
| J. D. Tillman, 'Response Effects of Guitar Pickup Mixing' | https://till.com/articles/PickupMixing/ | 2026-11-11 | not relevant | mixing of two pickups; no new claim |
| H. Lemme, 'The Secrets of Electric Guitar Pickups' | http://buildyourguitar.com/resources/lemme/ | 2026-11-11 | used | equivalent circuit, 2–5 kHz resonance, peak 0–12 dB, humbucker remarks; © Lemme; HTTPS certificate expired, fetched over HTTP |
| H. Fleischer, 'Dead spots of electric guitars and basses' (ASA/EAA/DAGA '99) | https://acoustics.org/pressroom/httpdocs/137th/fleischer.html | 2026-11-11 | used | dead-spot mechanism via neck conductance; 430 Hz example; no licence stated |
| H. Fleischer, 'Investigating dead spots' PDF | http://www.luteria.ufpr.br/portal/wp-content/uploads/2013/08/dead_spots.pdf | 2026-11-11 | unreachable | scanned image PDF, no extractable text; re-host |
| Fleischer & Zwicker, 'Mechanical vibrations of electric guitars' PDF | http://www.luteria.ufpr.br/portal/wp-content/uploads/2013/08/mechanical.pdf | 2026-11-11 | unreachable | scanned image PDF; re-host |
| M. Zollner, Physics of the Electric Guitar, ch. 5.15 'Collection of data' | https://www.gitec-forum-eng.de/wp-content/uploads/2020/09/poteg-5-magnetic-pickups-c.pdf | 2026-11-11 | used | load model (p. 5-168/169) |
| M. Zollner, ch. 5 part a | https://www.gitec-forum-eng.de/wp-content/uploads/2020/09/poteg-5-magnetic-pickups-a.pdf | 2026-11-11 | used | §5.4.4 aperture, §5.5.3 capacitance, §5.5.4 Q, §5.5.5 velocity |
| M. Zollner, ch. 5 part b | https://www.gitec-forum-eng.de/wp-content/uploads/2020/09/poteg-5-magnetic-pickups-b.pdf | 2026-11-11 | corroborating | §5.9 equivalent circuits, eddy currents, coil coupling |
| P. Biltoft, 'Pickup Inductance' (Planet Z) | https://www.planetz.com/pickup-inductance/ | 2026-11-11 | used | inductance ranges; © Planet Z |
| OzValveAmps, 'Pickups' | https://ozvalveamps.org/pickups.html | 2026-11-11 | corroborating | measured 1970s Strat 2.2 H / 6.5 kΩ / 110 pF; no licence stated |
| UIUC Physics 406, pickup results | https://courses.physics.illinois.edu/phys406/sp2017/406emi_guitar_pickup_results.html | 2026-11-11 | not relevant | values only in linked spreadsheets |
| Traube & Smith, 'Extracting the fingering and the plucking points…' (WASPAA 2001) | https://www.ee.columbia.edu/~dpwe/papers/TraubS01-guitar.pdf | 2026-11-11 | used | eq. (9) pluck amplitude |
| CCRMA REALSIMPLE 'harmonics' theory page | https://ccrma.stanford.edu/realsimple/harmonics/Theory.html | 2026-11-11 | not relevant | no amplitude formula; CC BY 2.5 |
| CCRMA PASP pages (Ideal_Plucked_String_Displacement, Pick_Position_Comb_Filter) | https://ccrma.stanford.edu/~jos/pasp/ | 2026-11-11 | unreachable | HTTP 404 |
| Web search: pickup inductance tables | (query) | 2026-11-11 | corroborating | led to Planet Z and OzValveAmps |
