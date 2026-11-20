#!/usr/bin/env python3
"""S-108: spectral centroid, 21-band decay and tail level for reference vs v1 vs amended candidates.
Usage: feature_comparison_a03.py <v1_render_dir> <amended_render_dir> (raw float32 mono 48 kHz from render_t026_set)."""
import json, sys
from pathlib import Path
import numpy as np, soundfile as sf
from scipy.signal import butter, sosfiltfilt
sys.path.insert(0, str(Path(__file__).resolve().parent))
import analyse_reference as ar

FS = 48000
EDGES = 100 * 2 ** (np.arange(0, 22) / 3)
SETS = [(m, v) for m in (40, 45, 64) for v in (45, 85, 125)]

def features(clip):
    clip = np.asarray(clip, float)[:2 * FS]
    clip = clip - clip.mean()
    sustain = clip[int(.2 * FS):int(.7 * FS)]
    sp = np.abs(np.fft.rfft(sustain * np.hanning(len(sustain)), 32768)) ** 2
    fr = np.fft.rfftfreq(32768, 1 / FS)
    centroid = float(np.sum(fr * sp) / np.sum(sp))
    t = np.arange(len(clip)) / FS
    decay = []
    for a, b in zip(EDGES[:-1], EDGES[1:]):
        hi = min(b, 0.45 * FS)
        sos = butter(2, [a, hi], btype='band', fs=FS, output='sos')
        env = np.sqrt(sosfiltfilt(butter(2, 20, 'low', fs=FS, output='sos'), sosfiltfilt(sos, clip) ** 2).clip(1e-24))
        w = (t >= .2) & (t <= 1.2)
        y = 20 * np.log10(env[w] + 1e-12)
        decay.append(float(np.polyfit(t[w], y, 1)[0]))  # dB/s, negative = decaying
    rms = lambda s: np.sqrt(np.mean(s ** 2)) + 1e-20
    tail = float(20 * np.log10(rms(clip[int(1.2 * FS):int(1.5 * FS)]) / rms(clip[int(.2 * FS):int(.7 * FS)])))
    return centroid, decay, tail

def cand(d):
    out = {}
    for m, v in SETS:
        x = np.fromfile(Path(d) / f'{m}-{v}.f32', dtype=np.float32)
        out[(m, v)] = features(x)
    return out

def summarise(rows):
    c = [r[0] for r in rows]; d = np.array([r[1] for r in rows]); t = [r[2] for r in rows]
    return {'centroid_hz_median': float(np.median(c)), 'tail_db_median': float(np.median(t)),
            'decay_db_per_s_median_by_band': [round(float(v), 2) for v in np.median(d, axis=0)]}

def main():
    import os
    root = Path(os.environ['EGB_P1_DIR'])
    x, fs = sf.read(root / 'audio/directinput/directinput_allsinglenotes.wav'); assert fs == FS
    x = x if x.ndim == 1 else x.mean(axis=1)
    refs = [n for n in ar.notes(root / 'midi/midi_allsinglenotes.mid') if n['velocity'] >= 100 and n['midi'] in (40, 45, 64)]
    rows = []
    for n in refs:
        a = ar.analyse(n, x, fs)
        s = int(a['onset_seconds'] * fs)
        rows.append(features(x[s:s + 2 * FS]))
    res = {'reference_P1_directinput': {'notes': len(rows), **summarise(rows)},
           'v1_61ab5ed': summarise(list(cand(sys.argv[1]).values())),
           'amended': summarise(list(cand(sys.argv[2]).values()))}
    json.dump(res, open('reports/feature_comparison_a03.json', 'w'), indent=1)
    lines = ['# Feature comparison before listening (S-108, Amendment 03)', '',
             'Candidate set: T-026 (MIDI 40/45/64 x velocity 45/85/125, default parameters, 1.6 s note, 48 kHz). Reference: P1 direct-input notes with the same MIDI numbers and velocity >= 100 (%d notes), onset from `scripts/analyse_reference.py`.' % len(rows), '',
             'Measures: centroid over 0.2-0.7 s (Hann, 32768-point FFT); 21 one-third-octave bands from 100 Hz, decay slope in dB/s from a linear fit of the band envelope over 0.2-1.2 s; tail level = RMS(1.2-1.5 s) / RMS(0.2-0.7 s) in dB. Medians over notes.', '',
             '| Measure | Reference | v1 (61ab5ed) | Amended |', '|---|---|---|---|']
    R, V, A = res['reference_P1_directinput'], res['v1_61ab5ed'], res['amended']
    lines.append(f"| Centroid, Hz | {R['centroid_hz_median']:.0f} | {V['centroid_hz_median']:.0f} | {A['centroid_hz_median']:.0f} |")
    lines.append(f"| Tail level, dB | {R['tail_db_median']:.1f} | {V['tail_db_median']:.1f} | {A['tail_db_median']:.1f} |")
    lines += ['', '| Band | Low edge Hz | Ref dB/s | v1 dB/s | Amended dB/s |', '|---|---|---|---|---|']
    for i in range(21):
        lines.append(f"| {i+1} | {EDGES[i]:.0f} | {R['decay_db_per_s_median_by_band'][i]} | {V['decay_db_per_s_median_by_band'][i]} | {A['decay_db_per_s_median_by_band'][i]} |")
    Path('reports/feature_comparison_a03.md').write_text('\n'.join(lines) + '\n')
    print('\n'.join(lines[:12]))
main()
