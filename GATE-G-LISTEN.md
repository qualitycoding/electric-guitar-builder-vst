G-LISTEN round 1 evidence (refresh after suite-green) — 2026-11-04T11:24:08Z
impl commit: c64bb29ea5d4f7ff9be33be55c39b39fc742bddf

Demo WAV hashes (sha256):
9f3db655f22275015ac056df7a00a1564d96ae0077b0a925ddf03597fe2a2d89  demos/demo_chords.wav
8088817ec9b03b122aaa223c5f44d637044c1f728d84b691532cdb58b5f4bf4b  demos/demo_palm_mute.wav
d309fb1d5f5a1748963a7903d3fdea39e22e7852e7acba01cfe91563a4b5bef8  demos/demo_phrase.wav
8b097c5c052910727cd181a5a36f310ae01c584441e2e64d6f08f189ed8a7f4d  demos/demo_pick_angle.wav
b391fe3b4cfe1f0f96328a518e0ec841b127aeb992b2bd38dd4af0a2af8079fa  demos/demo_pickups.wav
e555ba18bf0c1391f2046c5810a8fc169be1947c75c4922999c0a6f7596b829b  demos/demo_scale.wav

Pair WAV hashes (sha256):
e16b71a8c87d193538b09f2b7a4f3818162ec7cf2a765bf85132cf270389d808  pairs/pair_10_A.wav
447ffbc8b402d30890edcb9f6b49eee795fecd3a69a5f049a54140b7243aded4  pairs/pair_10_B.wav
6f7a48bd650dab8ad910897e449dce06458efaeffc988115492915948327835b  pairs/pair_11_A.wav
9290f069e1925dfc524141000da956f23d576911c316a39a191c535e684f74b1  pairs/pair_11_B.wav
c95f953550323d6de463befa4a99fb571e7da4bfe88e46018ec8245dcbbe51cf  pairs/pair_12_A.wav
d1170620d782b5388b5c13f4a0cb6ad802332e25ec27815534950c036f3ea089  pairs/pair_12_B.wav
61220df555475c081615308e6d022ac332e89b2457dd910969f459395ccdad48  pairs/pair_1_A.wav
cab5e274aa4d694cc42e4beb964193d7c2fbb250161517d7c559258b03eccfc9  pairs/pair_1_B.wav
25b006feb5b072ba28d8d8a743dd07e0c243fcfb7a7e4f2c7a60f6fb688fdee4  pairs/pair_2_A.wav
6c3a80abf303fc4c595d5ea7981f30aeb7f700ba8ea699cc8007e61b5e934383  pairs/pair_2_B.wav
827270e763a9b371dfbeb9894e5aeef70e467a7491e2a8c3694dab0c6c5f46d4  pairs/pair_3_A.wav
067312e5dca16ab54e9733d6e1018219a76726e7b9f9b2b687d716165a37cf2f  pairs/pair_3_B.wav
c5d055006c0fe98f0781bb0d64a9bc752997f3104388865e16e331f714d7583c  pairs/pair_4_A.wav
bced7af5867e0cac719a77f71083073e80ab4cb8c422c680369d476a2fc7186b  pairs/pair_4_B.wav
897d09222722336c801f1350d7eaa14d1911e1534a4b2378654b19d8f6918a9f  pairs/pair_5_A.wav
502d97470dc1921149ba9f51121fc13773599cb005a3a26ddfd36efbbde52a9e  pairs/pair_5_B.wav
b5664c525b9495925ed2c93810808dd83b93ba492f0bb020175a019a2bcfa1c7  pairs/pair_6_A.wav
dcddbcc8e06fe7ed268fd31e52000395817a58dfbb63c75033ad4566b2992693  pairs/pair_6_B.wav
3add28c33707cce02cb00339637fc929eb01e00141e4b12c335579564c764fc6  pairs/pair_7_A.wav
3e6225d3ed156d73be007028e603ea1b4f7f886a5e030478b3bb667e33ad54d1  pairs/pair_7_B.wav
8dca0c01f6404ccc0e646fe65290d9a363e871c49bfc363949d588772b35842a  pairs/pair_8_A.wav
f92a648c53eb5a033d4cfa5748bcc80399d3a6296ef392897d82e39c5630590a  pairs/pair_8_B.wav
bc29af7520559333487734a3d5095fb0d51f62575b487db8740aa9d62f473882  pairs/pair_9_A.wav
17ab53a37e63ada1ce78d80de5b2933460823bd7e21ab825a61eb6c185dfcd8a  pairs/pair_9_B.wav

Answer key (seed 20261104):
# seed 20261104; which side (A/B) is the reference per pair
pair_1 A
pair_2 B
pair_3 A
pair_4 B
pair_5 B
pair_6 B
pair_7 B
pair_8 B
pair_9 A
pair_10 A
pair_11 B
pair_12 B

== G-LISTEN round 1 result — 2026-11-04T12:33:43Z ==
seed: 20261104 | pairs: 12 | listener responses: Abbbbbbbaabb + B (pair 12)
score: 10/12 correct (83.3%); binomial p(>=10/12 at chance) ~= 0.019
misses: pair_3 (heard B, reference was A), pair_8 (heard B, reference was A)
outcome: reference discrimination above chance -> gate supports proceed
rounds used: 1 of 3

== CORRECTION 2026-11-04T12:50:00Z ==
The round-1 entry above recorded outcome "proceed". That was a misreading of
plan/GATES.md, which allows `proceed` only at <=8/12 correct. At 10/12 the
valid responses are `iterate`, `proceed-with-rescope` or `stop`. The recorded
score (10/12, misses pair_3/pair_8) is unchanged; only the outcome label was
wrong. Awaiting listener decision: iterate / proceed-with-rescope / stop.

== G-LISTEN round 2 — 2026-11-04T13:54:18Z ==
listener decision: iterate (round 1 finding: all samples sound reed-like)
mechanism change: harmonic decay — added internal-friction (stiffness)
damping quadratic in mode index: 0.8+0.025m+0.018m^2 dB/s (was 0.8+0.025m).
High partials now die in tens of ms like a real plucked string; low modes
keep the D-013 baseline. Rationale: reed-like = sustained harmonic spectrum.
seed: 20261105 (20261104 + round 1)
full frozen suite rerun: 30/30 pass (release, ASan, UBSan)
T-026: median band RMS 22.47 dB (gate 24.5385), median attack 23 ms (in range)

Demo WAV hashes (sha256, round 2):
2efb837a29af66ae6ba0eafead9ab1b55b00af66b5a6aba97f0d17276de29517  demos/demo_chords.wav
9979b5a476a1c22574a51b3aafa025315ece4c30b6a6c12b81b531830e100163  demos/demo_palm_mute.wav
59d56f48803793a9fe016ee86a56ebdc6e7e508749995c9efc2574c1ab23f632  demos/demo_phrase.wav
df7abb6c800857288e9dd0430768a62bf550af4736429ee80ac221c55c62cd1c  demos/demo_pick_angle.wav
bc38258a112814ddab789aaad4bc79940f86f45ff44c98abe00644a13caf9fe1  demos/demo_pickups.wav
ff22d98a4547da41082d546be72a7dc187eab28885cf499a55f1245d3dcb5da5  demos/demo_scale.wav

Pair WAV hashes (sha256, round 2, seed 20261105):
e16b71a8c87d193538b09f2b7a4f3818162ec7cf2a765bf85132cf270389d808  pairs/pair_10_A.wav
ed645afb340f992d6026c8e3bf7012db86e989912911ae43bb1cd0f251fb9f4b  pairs/pair_10_B.wav
8c2f2bf3dbeb7faefd89e3ad70ca3787c8e0f99689de727166fa78bbc178835d  pairs/pair_11_A.wav
9290f069e1925dfc524141000da956f23d576911c316a39a191c535e684f74b1  pairs/pair_11_B.wav
d1170620d782b5388b5c13f4a0cb6ad802332e25ec27815534950c036f3ea089  pairs/pair_12_A.wav
ff22860bcd0bb2387097ba51be5ff98b92e7df35ad8d5daa497a6eeb7ead9328  pairs/pair_12_B.wav
61220df555475c081615308e6d022ac332e89b2457dd910969f459395ccdad48  pairs/pair_1_A.wav
d85f0a6ea33b6b134e1c33eb2d9eb103110ae5fff151b5a97ce87f05fcbdd76e  pairs/pair_1_B.wav
757072595ded401970d3befe43ad460be9f6182bc04777564dcd3f50d0f4d2ee  pairs/pair_2_A.wav
6c3a80abf303fc4c595d5ea7981f30aeb7f700ba8ea699cc8007e61b5e934383  pairs/pair_2_B.wav
765e150b9dc81b4f382b516d17f8818e1a7ba6990ac78905f1e927d2f5da6830  pairs/pair_3_A.wav
827270e763a9b371dfbeb9894e5aeef70e467a7491e2a8c3694dab0c6c5f46d4  pairs/pair_3_B.wav
bced7af5867e0cac719a77f71083073e80ab4cb8c422c680369d476a2fc7186b  pairs/pair_4_A.wav
caa12f38af456d7c5d59214a583a48b8aee4feec0c11c4ba2bf80ee34231194c  pairs/pair_4_B.wav
99613de7e3eea7bc50bfcd3bdaf097f9bd14dd2f596805f7324bfcb4e1d5e0e5  pairs/pair_5_A.wav
502d97470dc1921149ba9f51121fc13773599cb005a3a26ddfd36efbbde52a9e  pairs/pair_5_B.wav
dcddbcc8e06fe7ed268fd31e52000395817a58dfbb63c75033ad4566b2992693  pairs/pair_6_A.wav
845cf390b7db3e53a9a45bc36cecdf8b3db9c7f1710ab1cf54a66b6925b6a653  pairs/pair_6_B.wav
3c3771db15ee3b723d0b3c7318b10e9eaa62b383f62d976f5af41b22a86ad4f6  pairs/pair_7_A.wav
3e6225d3ed156d73be007028e603ea1b4f7f886a5e030478b3bb667e33ad54d1  pairs/pair_7_B.wav
0a4080961be8a0b71b2600103950045ace6266051d9ee1ccd5b3e41c356d7523  pairs/pair_8_A.wav
f92a648c53eb5a033d4cfa5748bcc80399d3a6296ef392897d82e39c5630590a  pairs/pair_8_B.wav
b6068c420b24b91e0599697bd2c21760185e0a6ac7bf9fee8862381f67e9716c  pairs/pair_9_A.wav
bc29af7520559333487734a3d5095fb0d51f62575b487db8740aa9d62f473882  pairs/pair_9_B.wav

Answer key:
# seed 20261105 (G-LISTEN round 2); which side (A/B) is the reference per pair
pair_1 A
pair_2 B
pair_3 B
pair_4 A
pair_5 B
pair_6 A
pair_7 B
pair_8 B
pair_9 B
pair_10 A
pair_11 B
pair_12 A
