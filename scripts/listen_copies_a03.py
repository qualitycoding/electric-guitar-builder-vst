#!/usr/bin/env python3
"""D-041: listening copies of demos/a03 renders: one common gain per demo family so the loudest setting has -23 dBFS RMS
(peak <= 1.0); relative levels between settings are preserved. Writes demos/a03/listen/*.wav (24-bit) and GAINS.json."""
import glob, json, os, re
import numpy as np, soundfile as sf
os.makedirs('demos/a03/listen', exist_ok=True)
fam = {}
for f in sorted(glob.glob('demos/a03/*.wav')):
    fam.setdefault(re.sub(r'-\d+\.wav$', '', os.path.basename(f)), []).append(f)
gains = {}
for name, files in fam.items():
    data = [sf.read(f) for f in files]
    top = max(np.sqrt(np.mean(x ** 2)) for x, _ in data)
    g = 10 ** (-23 / 20) / top
    peak = max(np.max(np.abs(x)) for x, _ in data) * g
    assert peak <= 1.0, (name, peak)
    gains[name] = {'gain_linear': g, 'gain_db': 20 * np.log10(g), 'family_peak_after_gain': float(peak)}
    for f, (x, fs) in zip(files, data):
        sf.write('demos/a03/listen/' + os.path.basename(f), x * g, fs, subtype='PCM_24')
json.dump(gains, open('demos/a03/listen/GAINS.json', 'w'), indent=1)
print(json.dumps({k: round(v['gain_db'], 1) for k, v in gains.items()}))
