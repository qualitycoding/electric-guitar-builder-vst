#!/usr/bin/env python3
"""Fit the single global 21-band output correction on P1 calibration metrics.

D-007: calibration uses the P1 split ONLY. P2 stays held out and untouched.
The only fitted object in the project is this one global vector (no per-note
constants): correction_db = -median over P1 notes of the one-third-octave
band profile, applied identically to every rendered note.

Usage: python3 scripts/fit_p1_correction.py [out.json]
"""
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / 'research' / 'spikes' / 'reference_metrics.json'


def main() -> None:
    metrics = json.loads(SRC.read_text())
    notes = metrics['notes']
    bands = [n['bands_db'] for n in notes]
    assert all(len(b) == 21 for b in bands), 'expected 21 one-third-octave bands'
    median = [sorted(col)[len(col) // 2] for col in zip(*bands)]
    correction = [-m for m in median]
    out = {
        'fitted_on': 'P1 (Guitar-TECHS directinput_allsinglenotes, 138 notes, velocity>=100)',
        'held_out': 'P2 never read by this fit',
        'note_count': len(notes),
        'bands': '21 one-third-octave bands, 100 Hz .. ~20 kHz, peak-normalised',
        'correction_db': correction,
    }
    dst = Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / 'reports' / 'p1_correction.json'
    dst.parent.mkdir(parents=True, exist_ok=True)
    dst.write_text(json.dumps(out, indent=2) + '\n')
    print(json.dumps({k: v for k, v in out.items() if k != 'correction_db'}, indent=2))
    print('correction_db:', json.dumps(correction))


if __name__ == '__main__':
    main()
