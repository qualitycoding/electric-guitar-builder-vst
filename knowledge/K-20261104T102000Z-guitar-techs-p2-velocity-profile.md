# Guitar-TECHS P2 velocity profile (Zenodo 14963133)

Fact: the P2 `midi_allsinglenotes.mid` (1493 B, byte-identical in the record's
zip) has 137 note_ons and only SIX at velocity >= 100 (124, 115, 104, 103,
102, 101). P1 by contrast has 138 of 142 at >= 100. Any pipeline that assumes
"filter velocity >= 100, take 12" fails on P2; use top-N by velocity instead.

Also: the P2 directinput WAV (158,976,690 B header data, 48 kHz stereo 24-bit,
bext+junk chunks) needs a fmt parser that handles non-data chunks and the
exact field offsets — see readWav in src/contract_main.cpp.
