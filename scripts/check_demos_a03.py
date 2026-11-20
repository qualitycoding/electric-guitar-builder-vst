#!/usr/bin/env python3
"""S-LISTEN-2 done-when check for demos/a03: non-empty, peak <= 1.0, settings differ (octave-band spectrum > 0.5 dB
after RMS normalisation, or max abs sample difference > 1e-5 for demo_neck_joint)."""
import itertools, glob, re, sys
import numpy as np, soundfile as sf
demos = {}
for f in sorted(glob.glob('demos/a03/listen/*.wav')):  # D-041: checks run on the listening copies
    demos.setdefault(re.sub(r'-\d+\.wav$', '', f.split('/')[-1]), []).append(f)
bad = 0
def bands(x, fs):
    x = x / (np.sqrt(np.mean(x ** 2)) + 1e-20)
    p = np.abs(np.fft.rfft(x)) ** 2; fr = np.fft.rfftfreq(len(x), 1 / fs)
    edges = [62.5 * 2 ** k for k in range(11)]  # octave bands 62.5 Hz .. 64 kHz, capped by Nyquist
    return np.array([10 * np.log10(p[(fr >= a) & (fr < b)].sum() + 1e-20) for a, b in zip(edges[:-1], edges[1:]) if a < fs / 2])
total = 0
for name, files in demos.items():
    data = [sf.read(f) for f in files]; total += len(files)
    for f, (x, fs) in zip(files, data):
        ok = len(x) > 0 and np.max(np.abs(x)) <= 1.0 and np.max(np.abs(x)) > 0
        print(('ok   ' if ok else 'BAD  ') + f'{f} samples={len(x)} peak={np.max(np.abs(x)):.4f} rms_dbfs={20*np.log10(np.sqrt(np.mean(x**2))+1e-20):.1f}'); bad += not ok
    for (fa, (xa, fs)), (fb, (xb, _)) in itertools.combinations(zip(files, data), 2):
        if name in ('demo_neck_joint', 'demo_body_type'):  # D-041
            n = min(len(xa), len(xb)); d = float(np.max(np.abs(xa[:n] - xb[:n]))); ok = d > 1e-5; msg = f'max |diff| = {d:.3g}'
        else:
            n = min(len(xa), len(xb)); d = float(np.max(np.abs(bands(xa[:n], fs) - bands(xb[:n], fs)))); ok = d > 0.5; msg = f'max octave-band diff = {d:.2f} dB'
        print(('ok   ' if ok else 'BAD  ') + f'{fa.split("/")[-1]} vs {fb.split("/")[-1]}: {msg}'); bad += not ok
print(f'files={total} bad={bad}')
sys.exit(1 if bad else 0)
