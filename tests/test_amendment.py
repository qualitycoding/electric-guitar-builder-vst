# AMENDMENT tests — added per plan/ADDENDUM-G-LISTEN-SUSTAINED-TIMBRE.md.
# The frozen suite (test_contract.py, T-001..T-030) is untouched; this file
# adds T-031..T-035, which verify signal-path stages that the frozen tests
# cannot see (master gain, pickup electrical resonance, body response,
# fretted pickup comb, series/parallel loading). Each must fail on review
# baseline 4928520.
import os, subprocess, unittest
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
BIN = Path(os.environ.get('EGB_CONTRACT_BIN', ROOT / 'build/egb_contract'))


class Amendment(unittest.TestCase):
    maxDiff = None

    def run_case(self, case):
        self.assertTrue(BIN.is_file(), f'contract binary missing: {BIN}')
        p = subprocess.run([str(BIN), case], cwd=ROOT, text=True,
                           capture_output=True, timeout=180)
        self.assertEqual(p.returncode, 0,
                         f'{case} failed: {p.stdout}{p.stderr}')

    def test_031(self):
        """T-031 — Amendment: master-gain ratios in rendered audio."""
        self.run_case("T-031")

    def test_032(self):
        """T-032 — Amendment: pickup electrical resonance at the specified centre."""
        self.run_case("T-032")

    def test_033(self):
        """T-033 — Amendment: body-response output effect independent of body decay."""
        self.run_case("T-033")

    def test_034(self):
        """T-034 — Amendment: pickup-null movement with fret / speaking length."""
        self.run_case("T-034")

    def test_035(self):
        """T-035 — Amendment: parallel/series gain and loading contracts."""
        self.run_case("T-035")


if __name__ == '__main__':
    unittest.main()
