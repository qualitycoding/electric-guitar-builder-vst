#!/usr/bin/env python3
"""Segment Guitar-TECHS P1 DI audio from its MIDI and measure reference spread."""
import json
from pathlib import Path
import mido
import numpy as np
import soundfile as sf
from scipy.signal import butter, sosfilt, sosfiltfilt

ROOT = Path(__file__).resolve().parent / 'reference' / 'P1_singlenotes'
AUDIO = ROOT / 'audio/directinput/directinput_allsinglenotes.wav'
MIDI = ROOT / 'midi/midi_allsinglenotes.mid'


def notes(path):
    mid = mido.MidiFile(path)
    out = []
    for track in mid.tracks[1:]:
        now = 0.0
        active = {}
        for msg in track:
            now += msg.time * mid.ticks_per_beat and 0  # replaced below
        now_ticks = 0
        for msg in track:
            now_ticks += msg.time
            seconds = mido.tick2second(now_ticks, mid.ticks_per_beat, 1_000_000)
            if msg.type == 'note_on' and msg.velocity > 0:
                active[msg.note] = (seconds, msg.velocity)
            elif msg.type in ('note_off', 'note_on') and msg.note in active:
                start, velocity = active.pop(msg.note)
                out.append({'string': track.name, 'midi': msg.note, 'velocity': velocity,
                            'start': start, 'end': seconds})
    return sorted(out, key=lambda n: n['start'])


def envelope(x, fs):
    sos = butter(2, 20, btype='low', fs=fs, output='sos')
    return sosfiltfilt(sos, np.abs(x)) if len(x) > 9 else sosfilt(sos, np.abs(x))


def analyse(note, x, fs):
    # MIDI may be up to 100 ms early/late. Confirm onset with a high threshold,
    # then extend back to a lower threshold without clipping slow attacks.
    centre = int(note['start'] * fs)
    lo, hi = max(0, centre - int(.12 * fs)), min(len(x), centre + int(.12 * fs))
    env = envelope(x[lo:hi], fs)
    peak = float(env.max())
    confirm = np.flatnonzero(env > .20 * peak)
    onset = lo + (int(confirm[0]) if len(confirm) else int(env.argmax()))
    back_lo = max(0, onset - int(.05 * fs))
    back = envelope(x[back_lo:onset + 1], fs)
    below = np.flatnonzero(back < .05 * peak)
    onset = back_lo + (int(below[-1]) + 1 if len(below) else 0)
    clip = x[onset:onset + int(2.0 * fs)].astype(float)
    clip -= np.mean(clip)
    e = envelope(clip, fs)
    p = float(e.max())
    i10 = int(np.flatnonzero(e >= .1 * p)[0])
    i90 = int(np.flatnonzero(e >= .9 * p)[0])
    attack_ms = 1000 * (i90 - i10) / fs
    sustain = clip[int(.2 * fs):int(.7 * fs)]
    spectrum = np.abs(np.fft.rfft(sustain * np.hanning(len(sustain)), 32768))
    freqs = np.fft.rfftfreq(32768, 1 / fs)
    power = spectrum ** 2
    centroid = float(np.sum(freqs * power) / np.sum(power))
    # One-third-octave log-power profile, normalised to remove loudness.
    edges = 100 * 2 ** (np.arange(0, 22) / 3)
    bands = []
    for a, b in zip(edges[:-1], edges[1:]):
        mask = (freqs >= a) & (freqs < b)
        bands.append(float(10 * np.log10(np.sum(power[mask]) + 1e-20)))
    bands = np.array(bands)
    bands -= bands.max()
    rms = np.sqrt(np.mean(clip ** 2)) + 1e-20
    t60 = float(60 / max(1e-9, -20 * np.log10((np.sqrt(np.mean(clip[int(1.5*fs):] ** 2)) + 1e-20) / rms) / 1.5))
    return {**note, 'onset_seconds': onset / fs, 'attack_ms': attack_ms,
            'centroid_hz': centroid, 't60_proxy_seconds': t60, 'bands_db': bands.tolist()}


def main():
    x, fs = sf.read(AUDIO)
    ns = [n for n in notes(MIDI) if n['velocity'] >= 100]
    rows = [analyse(n, x, fs) for n in ns]
    bands = np.array([r['bands_db'] for r in rows])
    # Candidate/reference distance is RMS band error. Freeze a permissive gate at
    # the 95th percentile of reference leave-one-out distances, not an invented value.
    distances = []
    for i in range(len(rows)):
        others = np.delete(bands, i, axis=0)
        med = np.median(others, axis=0)
        distances.append(float(np.sqrt(np.mean((bands[i] - med) ** 2))))
    result = {
        'source': str(AUDIO.relative_to(Path(__file__).resolve().parent)),
        'note_count': len(rows),
        'attack_ms_quantiles': np.quantile([r['attack_ms'] for r in rows], [0, .05, .5, .95, 1]).tolist(),
        'centroid_hz_quantiles': np.quantile([r['centroid_hz'] for r in rows], [0, .05, .5, .95, 1]).tolist(),
        't60_proxy_seconds_quantiles': np.quantile([r['t60_proxy_seconds'] for r in rows], [0, .05, .5, .95, 1]).tolist(),
        'reference_loo_band_rms_db_quantiles': np.quantile(distances, [0, .5, .95, 1]).tolist(),
        'proposed_band_rms_db_gate': float(np.quantile(distances, .95)),
        'notes': rows,
    }
    out = Path(__file__).resolve().parent / 'reference_metrics.json'
    out.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k != 'notes'}, indent=2))

if __name__ == '__main__':
    main()
