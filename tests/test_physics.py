# FROZEN — DO NOT MODIFY (amendment 03, plan/DECISIONS.md D-020..D-030)
"""Amendment 03 contract tests T-040..T-051. Case logic: tests/physics/physics_cases.cpp
(frozen with this file). Expected values: research/spikes/physics_expected.json from
research/spikes/physics_oracle.py."""
import os, subprocess, unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
BIN = Path(os.environ.get('EGB_CONTRACT_BIN', ROOT / 'build/egb_contract'))


class Physics(unittest.TestCase):
    maxDiff = None

    def run_case(self, case):
        self.assertTrue(BIN.is_file(), f'contract binary missing: {BIN}')
        p = subprocess.run([str(BIN), case], cwd=ROOT, text=True, capture_output=True, timeout=180)
        self.assertEqual(p.returncode, 0, f'{case} failed: {p.stdout}{p.stderr}')

    def test_040(self):
        """T-040 — Unit: D-025/C-011/C-012 analogue RLC coefficients and load model vs oracle, 1e-12 relative."""
        self.run_case("T-040")

    def test_041(self):
        """T-041 — Unit: D-025 prewarped digital biquad coefficients vs oracle at 44.1/48/88.2/96 kHz, 1e-10; stability."""
        self.run_case("T-041")

    def test_042(self):
        """T-042 — Unit: D-021/C-019/C-020 position, aperture and humbucker two-pole sampling vs oracle, 1e-12."""
        self.run_case("T-042")

    def test_043(self):
        """T-043 — Unit: D-027/C-022 pluck amplitude law vs oracle, 1e-12; node at R = 1/5; D-026 velocity gain."""
        self.run_case("T-043")

    def test_044(self):
        """T-044 — Unit: D-022/D-023/D-028/C-023 neck and bridge conductance and structural decay vs oracle, 1e-12; dead spot."""
        self.run_case("T-044")

    def test_045(self):
        """T-045 — Integration: D-025 rendered spectrum follows cable, pot and amplifier load (>= half the predicted dB change)."""
        self.run_case("T-045")

    def test_046(self):
        """T-046 — Integration: D-026/D-027 engine mode table composition (1e-9) and audible pluck node (>= 12 dB)."""
        self.run_case("T-046")

    def test_047(self):
        """T-047 — Unit: measurement helpers on synthetic signals (decay within 2 %, band level within 1.5 dB)."""
        self.run_case("T-047")

    def test_048(self):
        """T-048 — Integration: D-028 hollow body adds >= half the predicted fundamental decay versus solid."""
        self.run_case("T-048")

    def test_049(self):
        """T-049 — Unit: D-029 parameter contract v2, 42 descriptors (supersedes T-001 per D-030)."""
        self.run_case("T-049")

    def test_050(self):
        """T-050 — Unit: D-029 state schemaVersion 2 round trip and v1 migration (supersedes T-011 per D-030)."""
        self.run_case("T-050")

    def test_051(self):
        """T-051 — Guard: worst-case electrical and structural load stays finite and <= 1 after the safety stage."""
        self.run_case("T-051")


if __name__ == '__main__':
    unittest.main()
