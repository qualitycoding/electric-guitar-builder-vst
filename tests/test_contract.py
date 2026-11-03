# FROZEN — DO NOT MODIFY
"""Contract tests for electric-guitar-builder-vst. Run after S-000 builds egb_contract."""
import os, subprocess, unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
BIN=Path(os.environ.get('EGB_CONTRACT_BIN',ROOT/'build/egb_contract'))
class Contract(unittest.TestCase):
    maxDiff=None
    def run_case(self, case):
        self.assertTrue(BIN.is_file(), f'contract binary missing: {BIN}')
        p=subprocess.run([str(BIN),case],cwd=ROOT,text=True,capture_output=True,timeout=120)
        self.assertEqual(p.returncode,0,f'{case} failed: {p.stdout}{p.stderr}')
    def test_001(self):
        """T-001 — Unit: SC1/D-003 parameter IDs, ranges, defaults and invalid-state rejection."""
        self.run_case("T-001")

    def test_002(self):
        """T-002 — Unit: SC1/D-004 tension, inharmonicity, fret and pluck formulas against expected_values.json; 1e-12 relative tolerance."""
        self.run_case("T-002")

    def test_003(self):
        """T-003 — Unit: SC1/D-004 each construction control has bounded finite isolated-stage effect and fret size cannot change pitch."""
        self.run_case("T-003")

    def test_004(self):
        """T-004 — Unit: SC1/D-003/D-004 per-string pickup sensing, aperture, type, phase and parallel/series combination."""
        self.run_case("T-004")

    def test_005(self):
        """T-005 — Unit: SC2/D-004 pick angle/depth attack and noise expected values and monotonic boundaries."""
        self.run_case("T-005")

    def test_006(self):
        """T-006 — Integration: SC2/D-004 palm mute continuum, exact zero bypass, monotone damping/cutoff and 20 ms smoothing."""
        self.run_case("T-006")

    def test_007(self):
        """T-007 — Unit: SC3/D-003 MIDI 40–88, per-string tuning and 0.01-cent string-model pitch error."""
        self.run_case("T-007")

    def test_008(self):
        """T-008 — Integration: SC3 finite audio at 44100, 48000, 88200 and 96000 Hz with modes below 0.45 sample rate."""
        self.run_case("T-008")

    def test_009(self):
        """T-009 — Integration: SC4/D-006 frozen 16-voice worst case has pre-safety finite output and post-safety peak <=1; no renderer normalisation."""
        self.run_case("T-009")

    def test_010(self):
        """T-010 — Integration: SC5/D-006 same build/platform repeated float32 output is bit-identical; cross-platform maximum error <=1e-6."""
        self.run_case("T-010")

    def test_011(self):
        """T-011 — Unit: D-005 valid APVTS schemaVersion=1 round trip; unknown IDs, NaN and >256 KiB rejected atomically."""
        self.run_case("T-011")

    def test_012(self):
        """T-012 — Security: D-005 event UTF-8/schema/time validation, 1 MiB/10000-event caps, malformed input and non-execution."""
        self.run_case("T-012")

    def test_013(self):
        """T-013 — Integration: SC5/D-005 structural changes affect new voices only; continuous controls crossfade without zipper discontinuities."""
        self.run_case("T-013")

    def test_014(self):
        """T-014 — Integration: SC5/D-005 instrumented host run proves no audio-thread allocation, lock, I/O, logging or APVTS tree replacement."""
        self.run_case("T-014")

    def test_015(self):
        """T-015 — Operational: startup, reset, graceful shutdown and interruption resume produce valid output without leaked voices."""
        self.run_case("T-015")

    def test_016(self):
        """T-016 — Operational: invalid sample rates/block sizes/voice counts and resource exhaustion fail explicitly and recover after reset."""
        self.run_case("T-016")

    def test_017(self):
        """T-017 — Performance: A-009 pinned 16-voice benchmark meets per-runner budget; three runs, median gate and >10% spread rerun once."""
        self.run_case("T-017")

    def test_018(self):
        """T-018 — Integration: SC1/SC2 parameter automation persists through host state and produces deterministic offline bounce."""
        self.run_case("T-018")

    def test_019(self):
        """T-019 — Security: dependency vulnerability scan has no unresolved Critical/High shipped finding and no suppressed report."""
        self.run_case("T-019")

    def test_020(self):
        """T-020 — Integration: D-001/D-005 VST3 and headless renderer share identical engine output for one frozen event file."""
        self.run_case("T-020")

    def test_021(self):
        """T-021 — Operational: D-010 pluginval and ASan/UBSan pass supported host behaviours; failure is not excluded."""
        self.run_case("T-021")

    def test_022(self):
        """T-022 — Integration: D-005 metadata contains commit, lock hash, seed, all parameters, event hash, UTC timestamp, rate, unclipped peak and platform."""
        self.run_case("T-022")

    def test_023(self):
        """T-023 — Integration: D-007 calibration uses P1 only; P2 remains held out and no per-note corrective constants exist."""
        self.run_case("T-023")

    def test_024(self):
        """T-024 — Integration: D-008 onset alignment and stable-window extraction reproduce committed reference_metrics.json within 1e-9."""
        self.run_case("T-024")

    def test_025(self):
        """T-025 — Integration: D-008 21-band vectors and leave-one-out reference spread reproduce 24.538530602719486 dB within 1e-9."""
        self.run_case("T-025")

    def test_026(self):
        """T-026 — Integration: SC7/D-008 candidate median band RMS <=24.538530602719486 dB and median attack in [8.208333333333334,31.541666666666668] ms."""
        self.run_case("T-026")

    def test_027(self):
        """T-027 — Integration: D-009 pair builder makes 12 one-second onset pairs, RMS -23 dBFS, 10 ms fade, 24-bit/44.1 kHz and seeded sides/key."""
        self.run_case("T-027")

    def test_028(self):
        """T-028 — Operational: D-009 demos render reproducibly from event files and evidence branch/marker commit contain hashes and delivery URLs."""
        self.run_case("T-028")

    def test_029(self):
        """T-029 — Operational: D-010 CI workflow schema, versioned matrix, fail-fast false, artefact postconditions and no failure swallowing."""
        self.run_case("T-029")

    def test_030(self):
        """T-030 — Security/operational: repository secret scan, licence attribution, checksum verification and clean shutdown/resume evidence."""
        self.run_case("T-030")
