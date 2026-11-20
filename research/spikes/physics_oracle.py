"""Amendment 03 physics oracle (D-021..D-028). Executable specification for
include/egb/Physics.h. Generates research/spikes/physics_expected.json, which
the frozen cases T-040..T-046 read. Run:
  /home/claude/projects/venv-torch/bin/python research/spikes/physics_oracle.py
Every expected value in the JSON is produced by executing these functions on
the exact test inputs (L-20261008T151500Z); nothing is typed by hand."""
import json, math, sys
import numpy as np

# ---------- D-025 pickup electrics ----------
# Per-type coil (L henry, R ohm, C farad). Sources: C-016/C-017 (ranges),
# chosen inside the measured ranges; values are a parameterisation (A-008).
COIL = {0: (2.2, 6000.0, 110e-12),   # single_coil
        1: (6.0, 8000.0, 130e-12),   # p90
        2: (4.2, 8000.0, 150e-12)}   # humbucker (two coils in series)
AMP_INPUT_CAP_F = 150e-12            # Zollner 5.15, p. 5-168 (C-012)
POT_CHOICES_KOHM = (250.0, 500.0, 1000.0)

def load_resistance(pot_kohm, amp_mohm):
    """Volume and tone pots (both pot_kohm, fully open) in parallel with the
    amplifier input resistance (C-012)."""
    rp = pot_kohm * 1e3
    ra = amp_mohm * 1e6
    return 1.0 / (2.0 / rp + 1.0 / ra)

def rlc_analog(ptype, pot_kohm, cable_pf, amp_mohm):
    L, R, C = COIL[ptype]
    Rl = load_resistance(pot_kohm, amp_mohm)
    Ct = C + cable_pf * 1e-12 + AMP_INPUT_CAP_F
    a2 = L * Ct
    a1 = R * Ct + L / Rl
    a0 = 1.0 + R / Rl
    fres = 1.0 / (2.0 * math.pi * math.sqrt(a2))
    q = math.sqrt(a2 * a0) / a1
    return dict(a2=a2, a1=a1, a0=a0, fres=fres, q=q, rload=Rl, ctotal=Ct)

def analog_mag(an, f):
    s = 2j * math.pi * f
    return abs(1.0 / (an['a2'] * s * s + an['a1'] * s + an['a0']))

def rlc_digital(an, fs):
    """Bilinear transform with prewarping at the analogue resonance:
    s = k (1 - z^-1)/(1 + z^-1), k = 2 pi fres / tan(pi fres / fs).
    Returns normalised (b0,b1,b2,a1,a2) with a0 = 1."""
    w = 2.0 * math.pi * an['fres']
    k = w / math.tan(math.pi * an['fres'] / fs)
    A2, A1, A0 = an['a2'] * k * k, an['a1'] * k, an['a0']
    d0 = A2 + A1 + A0
    b = [1.0 / d0, 2.0 / d0, 1.0 / d0]
    a = [2.0 * (A0 - A2) / d0, (A2 - A1 + A0) / d0]
    return b + a

def digital_mag(c, f, fs):
    z = np.exp(1j * 2 * math.pi * f / fs)
    num = c[0] + c[1] / z + c[2] / z ** 2
    den = 1 + c[3] / z + c[4] / z ** 2
    return float(abs(num / den))

# ---------- D-027 pluck ----------
def pluck_amplitude(m, R):
    """Traube & Smith 2001 eq. (9), h = 1 (C-022)."""
    return 2.0 * math.sin(m * math.pi * R) / (m * m * math.pi * math.pi * R * (1.0 - R))

# ---------- D-026 velocity ----------
def velocity_gain(fm, f1):
    return fm / f1

HCOUPLE_M = {0: 0.018, 1: 0.022, 2: 0.028}
def horizontal_coupling(fm, ptype):
    return 1.0 / (1.0 + (fm * HCOUPLE_M[ptype] / 200.0) ** 2)

# ---------- D-021 spatial sampling ----------
APERTURE_M = {0: 0.008, 1: 0.016, 2: 0.005}   # effective window width (single-coil, P-90, per humbucker pole)
HB_POLE_SPACING_M = 0.0185                    # Zollner 5.4.4: 18-19 mm (C-019)
HB_SECOND_COIL_GAIN = 10 ** (-2.5 / 20)       # Zollner 5.4.4: 2-3 dB weaker coil (C-019)

def sincx(x):
    return 1.0 if abs(x) < 1e-12 else math.sin(x) / x

def pickup_spatial(m, xp, Ls, ptype):
    """Velocity-sensing weight of mode m at a pickup centred xp metres from the
    bridge on a speaking length Ls; wavenumber k = m pi / Ls (C-020)."""
    k = m * math.pi / Ls
    ap = sincx(k * APERTURE_M[ptype] / 2.0)
    if ptype == 2:
        d = HB_POLE_SPACING_M
        g = HB_SECOND_COIL_GAIN
        s = (math.sin(k * (xp - d / 2.0)) + g * math.sin(k * (xp + d / 2.0))) / (1.0 + g)
    else:
        s = math.sin(k * xp)
    return s * ap

# ---------- D-022/D-023/D-028 structural loss ----------
NECK_MODES = {  # neck material -> [(f Hz, peak conductance s/kg, Q)]
    0: [(205.0, 0.006, 25.0), (450.0, 0.004, 25.0)],   # maple
    1: [(203.0, 0.006, 18.0), (446.0, 0.004, 18.0)],   # mahogany (E/rho within 1 %, higher loss)
}
JOINT = {0: (1.00, 1.00), 1: (1.00, 0.90), 2: (1.03, 0.80)}          # bolt_on, set_neck, neck_through: (f scale, G scale)
FINGERBOARD = {0: (1.00, 1.00), 1: (0.98, 1.00), 2: (0.97, 0.95)}    # maple, rosewood, ebony
BRIDGE = {  # body type -> (baseline s/kg, [(f, peak, Q)], broadband s/kg, broadband corner Hz)
    0: (1e-4, [], 0.0, 2000.0),                                   # solid (Zollner 7.10.1: 1e-4 negligible)
    1: (3e-4, [(230.0, 0.003, 6.0)], 0.0, 2000.0),                 # chambered
    2: (1e-3, [(180.0, 0.02, 5.0), (400.0, 0.012, 5.0)], 0.003, 2000.0),  # hollow (Zollner 7.11)
}

def resonant_conductance(f, f0, gpk, q):
    return gpk / (1.0 + q * q * (f / f0 - f0 / f) ** 2)

def neck_shape(k, x, L0):
    """Bending mode shapes along the neck as a function of the bearing's
    distance x (m) from the nut (C-024): mode 1 node at fret 10, mode 2 nodes
    at frets 2 and 12."""
    x2 = L0 * (1 - 2 ** (-2 / 12)); x10 = L0 * (1 - 2 ** (-10 / 12)); x12 = L0 / 2
    if k == 0:
        return math.cos(math.pi * x / (2.0 * x10))
    return math.sin(math.pi * (x - x2) / (x12 - x2))

def neck_conductance(f, neck, joint, fb, x_bearing, L0):
    fj, gj = JOINT[joint]; ff, gf = FINGERBOARD[fb]
    g = 0.0
    for k, (f0, gpk, q) in enumerate(NECK_MODES[neck]):
        phi = neck_shape(k, x_bearing, L0)
        g += resonant_conductance(f, f0 * fj * ff, gpk * gj * gf, q) * phi * phi
    return g

def bridge_conductance(f, body):
    base, peaks, bb, corner = BRIDGE[body]
    g = base + bb / (1.0 + (f / corner) ** 2)
    for f0, gpk, q in peaks:
        g += resonant_conductance(f, f0, gpk, q)
    return g

def wave_impedance(tension, mu):
    return math.sqrt(tension * mu)

def structural_decay_db_per_s(fm, f1, W, neck, joint, fb, body, x_bearing, L0):
    """Extra decay of a mode at fm from absorption at both bearings
    (C-023): energy loss per reflection a^2 = 4 W G, one reflection per
    bearing per fundamental period; dB/s = 10 log10(e) f1 sum(a^2)."""
    a2 = 4.0 * W * (neck_conductance(fm, neck, joint, fb, x_bearing, L0) + bridge_conductance(fm, body))
    a2 = min(a2, 0.5)
    return 10.0 * math.log10(math.e) * f1 * (-math.log(1.0 - a2))

# ---------- string helpers (same as Mapping.h) ----------
RHO, E = 7850.0, 200e9
def string_tm(scale_m, gauge_in, f0):
    d = gauge_in * 0.0254
    mu = RHO * math.pi * d * d / 4
    T = mu * (2 * scale_m * f0) ** 2
    return T, mu

def main():
    out = {"generator": "research/spikes/physics_oracle.py", "rlc": [], "digital": [], "spatial": [], "pluck": [],
           "structural": [], "load": [], "checks": {}}
    pr = lambda *a: print(*a)
    # load resistance (C-012)
    for pot in POT_CHOICES_KOHM:
        for amp in (0.05, 1.0, 10.0):
            out["load"].append(dict(pot_kohm=pot, amp_mohm=amp, rload=load_resistance(pot, amp)))
    pr("load 250k pots, 1M amp:", load_resistance(250, 1.0), "(Zollner 111.1 kOhm)")
    pr("load 500k pots, 1M amp:", load_resistance(500, 1.0), "(Zollner 200 kOhm)")
    # RLC grid
    for t in (0, 1, 2):
        for pot in POT_CHOICES_KOHM:
            for cab in (0.0, 200.0, 600.0, 1500.0, 2000.0):
                for amp in (0.05, 1.0, 10.0):
                    an = rlc_analog(t, pot, cab, amp)
                    out["rlc"].append(dict(type=t, pot_kohm=pot, cable_pf=cab, amp_mohm=amp, **an))
    for t, name in ((0, "single_coil"), (1, "p90"), (2, "humbucker")):
        an = rlc_analog(t, (250, 500, 500)[t], 600.0, 1.0)
        pr(f"default-load {name}: fres {an['fres']:.1f} Hz, Q {an['q']:.3f}, peak {20*math.log10(analog_mag(an, an['fres'])/analog_mag(an,10)):.2f} dB")
    # the research document's own case (single pot load, no amp capacitance)
    L, R, C = 2.6, 6200.0, 110e-12
    Rl = 250e3 * 1e6 / (250e3 + 1e6); Ct = C + 600e-12
    a2, a1, a0 = L * Ct, R * Ct + L / Rl, 1 + R / Rl
    doc = dict(fres=1 / (2 * math.pi * math.sqrt(a2)), q=math.sqrt(a2 * a0) / a1)
    out["checks"]["document_single_coil"] = doc
    pr("document single coil reproduces:", doc, "(document: 3.70 kHz, Q 2.53)")
    # digital
    for fs in (44100.0, 48000.0, 88200.0, 96000.0):
        for t in (0, 1, 2):
            an = rlc_analog(t, 250.0, 600.0, 1.0)
            c = rlc_digital(an, fs)
            mags = {str(f): digital_mag(c, f, fs) for f in (100.0, 1000.0, an['fres'], 2 * an['fres'], 8000.0)}
            amag = {str(f): analog_mag(an, f) for f in (100.0, 1000.0, an['fres'], 2 * an['fres'], 8000.0)}
            out["digital"].append(dict(fs=fs, type=t, coeffs=c, mag=mags, analog_mag=amag, fres=an['fres']))
            assert abs(digital_mag(c, an['fres'], fs) / analog_mag(an, an['fres']) - 1) < 1e-9
    pr("digital prewarped biquad matches analogue magnitude at fres to 1e-9 at all four rates")
    # spatial
    for t in (0, 1, 2):
        for xp in (0.025, 0.040, 0.065, 0.120, 0.160):
            for Ls in (0.6477, 0.6477 / 2 ** (5 / 12), 0.6477 / 2):
                for m in (1, 2, 3, 5, 8, 13, 21, 34, 55):
                    out["spatial"].append(dict(type=t, xp=xp, Ls=Ls, m=m, s=pickup_spatial(m, xp, Ls, t)))
    # aperture first null (C-013): rectangular width W, open E2
    f_open, L0 = 82.41, 0.648
    for w in (0.012, 0.010, 0.024):
        pr(f"aperture W={w*1000:.0f} mm: first null 2 L f0 / W = {2*L0*f_open/w:.0f} Hz; document table value {L0*f_open/w:.0f} Hz")
    pr(f"humbucker d=19 mm two-point notch f0 L / d = {f_open*L0/0.019:.0f} Hz; document table 1405 Hz")
    out["checks"]["aperture_null_12mm"] = 2 * L0 * f_open / 0.012
    out["checks"]["hb_notch_19mm"] = f_open * L0 / 0.019
    # humbucker identity: equal weights reduce to sin(kx) cos(kd/2)
    for m in range(1, 60):
        k = m * math.pi / L0; xp = 0.04; d = 0.019
        lhs = 0.5 * (math.sin(k * (xp - d / 2)) + math.sin(k * (xp + d / 2)))
        rhs = math.sin(k * xp) * math.cos(k * d / 2)
        assert abs(lhs - rhs) < 1e-12
    pr("humbucker sum-to-product identity verified for m = 1..59 (C-019)")
    # humbucker two-pole comb in travelling-wave form |1 + g e^{-jkd}|/(1+g):
    # deepest at kd = pi, i.e. mode m = Ls/d (Zollner 5.4.4: half-wavelength pole spacing)
    Ls = 0.6477
    comb = [abs(1 + HB_SECOND_COIL_GAIN * np.exp(-1j * m * math.pi / Ls * HB_POLE_SPACING_M)) / (1 + HB_SECOND_COIL_GAIN) for m in range(1, 80)]
    mnotch = 1 + int(np.argmin(comb))
    out["checks"]["hb_comb_min_mode_open"] = mnotch
    out["checks"]["hb_comb_min_depth_db"] = 20 * math.log10(min(comb))
    out["checks"]["hb_comb_min_mode_expected"] = Ls / HB_POLE_SPACING_M
    pr(f"humbucker comb minimum at mode {mnotch} (Ls/d = {Ls/HB_POLE_SPACING_M:.2f}), depth {20*math.log10(min(comb)):.1f} dB with 2.5 dB coil imbalance")
    # single-coil aperture attenuation at 5 kHz on open E2 (Zollner: little influence)
    m5k = 5000.0 / 82.41
    att = 20 * math.log10(abs(sincx(m5k * math.pi / Ls * APERTURE_M[0] / 2)))
    out["checks"]["sc_aperture_db_5k_E2"] = att
    pr(f"single-coil aperture at 5 kHz on open E2: {att:.2f} dB")
    # pluck: verify eq. (9) by numerical Fourier integration of a triangle
    for R in (0.05, 0.10, 0.18, 0.25, 0.33, 0.5):
        x = np.linspace(0, 1, 200001)
        y = np.where(x <= R, x / R, (1 - x) / (1 - R))
        for m in (1, 2, 3, 4, 5, 7, 10, 20):
            num = 2 * np.trapezoid(y * np.sin(m * np.pi * x), x)
            assert abs(num - pluck_amplitude(m, R)) < 1e-8, (R, m, num, pluck_amplitude(m, R))
            out["pluck"].append(dict(m=m, R=R, a=pluck_amplitude(m, R)))
    pr("pluck amplitude eq. (9) matches numerical Fourier integration to 1e-8 for 6 positions x 8 modes (C-022)")
    # bearing absorption reproduction (C-023): E2, G = 0.001 s/kg, light and heavy sets
    for gauge, wound_factor in ((0.042, 0.70), (0.052, 0.70)):
        T, mu = string_tm(0.648, gauge, 82.41)
        T *= wound_factor; mu *= wound_factor   # wound strings carry ~70 % of the solid-wire mass (assumption, inferred)
        W = wave_impedance(T, mu)
        pr(f"E2 gauge {gauge}: W = {W:.3f} kg/s, 4WG at G=0.001 -> {400*W*0.001:.3f} % (Zollner: 0.22-0.44 %)")
    # structural cases
    L0 = 0.6477
    cases = []
    for (midi_open, gauge) in ((40, 0.046), (55, 0.017), (64, 0.010)):
        for fret in (0, 1, 2, 5, 7, 10, 12):
            f1 = 440 * 2 ** ((midi_open + fret - 69) / 12)
            Ls = L0 / 2 ** (fret / 12)
            T, mu = string_tm(Ls, gauge, f1)
            W = wave_impedance(T, mu)
            xb = L0 - Ls
            for neck in (0, 1):
                for joint in (0, 1, 2):
                    for fb in (0, 1, 2):
                        for body in (0, 1, 2):
                            for m in (1, 2, 3):
                                fm = m * f1
                                cases.append(dict(midi=midi_open + fret, fret=fret, gauge=gauge, f1=f1, m=m, fm=fm, W=W, xb=xb,
                                                  neck=neck, joint=joint, fb=fb, body=body,
                                                  gneck=neck_conductance(fm, neck, joint, fb, xb, L0),
                                                  gbridge=bridge_conductance(fm, body),
                                                  extra_db_s=structural_decay_db_per_s(fm, f1, W, neck, joint, fb, body, xb, L0)))
    out["structural"] = cases
    # dead-spot demonstration: G string fretted so f1 is closest to neck mode 1 vs a semitone away
    best = None
    for fret in range(0, 13):
        f1 = 440 * 2 ** ((55 + fret - 69) / 12)
        d = abs(f1 - 205.0)
        if best is None or d < best[0]:
            best = (d, fret)
    fret = best[1]
    def g_extra(fr):
        f1 = 440 * 2 ** ((55 + fr - 69) / 12); Ls = L0 / 2 ** (fr / 12)
        T, mu = string_tm(Ls, 0.017, f1)
        return structural_decay_db_per_s(f1, f1, wave_impedance(T, mu), 0, 0, 0, 0, L0 - Ls, L0)
    ds = dict(fret=fret, extra_at_dead_spot=g_extra(fret), extra_semitone_below=g_extra(fret - 1), extra_semitone_above=g_extra(fret + 1))
    out["checks"]["dead_spot_G_string"] = ds
    pr("dead spot (G string, maple, bolt-on, solid):", ds)
    hol = structural_decay_db_per_s(110.0, 110.0, 0.6, 0, 0, 0, 2, 0.0, L0) - structural_decay_db_per_s(110.0, 110.0, 0.6, 0, 0, 0, 0, 0.0, L0)
    out["checks"]["hollow_minus_solid_A2_db_s"] = hol
    pr(f"hollow minus solid extra decay, A2 fundamental: {hol:.2f} dB/s")
    # full-range parameter sweep (L-20261007T150600Z): every new control, finite and bounded
    sweep = []
    for t in (0, 1, 2):
        for pot in POT_CHOICES_KOHM:
            for cab in np.linspace(0, 2000, 9):
                for amp in (0.05, 0.1, 0.47, 1.0, 3.3, 10.0):
                    an = rlc_analog(t, pot, float(cab), amp)
                    assert math.isfinite(an['fres']) and 0.05 < an['q'] < 12, an  # heavy 50 kOhm loads legitimately give Q near 0.27
                    sweep.append((an['fres'], an['q']))
    fr = [s[0] for s in sweep]; qs = [s[1] for s in sweep]
    out["checks"]["sweep_fres_range"] = [min(fr), max(fr)]
    out["checks"]["sweep_q_range"] = [min(qs), max(qs)]
    pr(f"full sweep: fres {min(fr):.0f}-{max(fr):.0f} Hz, Q {min(qs):.2f}-{max(qs):.2f}")
    for R in np.linspace(0.05, 0.5, 10):
        assert all(math.isfinite(pluck_amplitude(m, float(R))) for m in range(1, 200))
    mx = max(c["extra_db_s"] for c in cases)
    out["checks"]["structural_max_db_s"] = mx
    pr(f"structural extra decay max over grid: {mx:.2f} dB/s")
    # ---- integration predictions for rendered tests (T-045, T-048) ----
    def hdb(an, f): return 20 * math.log10(analog_mag(an, f))
    integ = {}
    a15, a02 = rlc_analog(0, 250.0, 1500.0, 1.0), rlc_analog(0, 250.0, 200.0, 1.0)
    flo, fhi = a15['fres'], a02['fres']
    integ['cable'] = dict(f_lo=flo, f_hi=fhi, predicted_delta_db=(hdb(a15, flo) - hdb(a15, fhi)) - (hdb(a02, flo) - hdb(a02, fhi)))
    p1k, p250 = rlc_analog(0, 1000.0, 600.0, 1.0), rlc_analog(0, 250.0, 600.0, 1.0)
    integ['pot'] = dict(f_peak=p1k['fres'], f_ref=450.0, predicted_delta_db=(hdb(p1k, p1k['fres']) - hdb(p1k, 450.0)) - (hdb(p250, p1k['fres']) - hdb(p250, 450.0)))
    hi, lo = rlc_analog(0, 250.0, 600.0, 10.0), rlc_analog(0, 250.0, 600.0, 0.05)
    integ['amp'] = dict(f_peak=hi['fres'], f_ref=450.0, predicted_delta_db=(hdb(hi, hi['fres']) - hdb(hi, 450.0)) - (hdb(lo, hi['fres']) - hdb(lo, 450.0)))
    # T-048: MIDI 45 is played on channel 5, which D-013 maps to string index 4 (open A, gauge 0.036);
    # tension uses the engine's Mapping.h formula on the open scale. (Corrected by D-037: the first
    # version assumed first-fit allocation, but channels 1-6 select the string directly.)
    T, mu = string_tm(0.6477, 0.036, 110.0)
    W = wave_impedance(T, mu)
    dh = structural_decay_db_per_s(110.0, 110.0, W, 0, 0, 0, 2, 0.0, 0.6477) - structural_decay_db_per_s(110.0, 110.0, W, 0, 0, 0, 0, 0.0, 0.6477)
    integ['body_hollow_minus_solid_A2'] = dict(W=W, predicted_delta_db_s=dh)
    # T-035 (amended by D-037): series loading moves band energy towards the series resonance.
    # MIDI 64 on channel 1 -> string 0 (open high E, 0.010 in); two humbuckers at 60 mm; window from 0.3 s.
    f0, Ls = 329.63, 0.6477
    T, mu = string_tm(Ls, 0.010, f0)
    Wt = wave_impedance(T, mu)
    dd = 0.010 * 0.0254
    Bt = min(math.pi ** 3 * 200e9 * dd ** 4 / (64 * T * Ls * Ls), 0.02)
    term = min(0.0005 + 0.0004 * 1.1 + 0.0002 * 0.8, 0.01)
    Lc, Rc, Cc = COIL[2]
    par = rlc_analog(2, 250.0, 600.0, 1.0)
    Rl = load_resistance(250.0, 1.0); Ct = Cc / 2 + 600e-12 + AMP_INPUT_CAP_F
    a2, a1, a0 = 2 * Lc * Ct, 2 * Rc * Ct + 2 * Lc / Rl, 1 + 2 * Rc / Rl
    ser = dict(a2=a2, a1=a1, a0=a0, fres=1 / (2 * math.pi * math.sqrt(a2)))
    def band_db(an, fc):
        e = 0.0
        for m in range(1, 40):
            fm = m * f0 * math.sqrt(1 + Bt * m * m)
            if abs(fm - fc) > 200: continue
            a = pluck_amplitude(m, 0.18) * velocity_gain(fm, f0) * pickup_spatial(m, 0.060, Ls, 2) * analog_mag(an, fm)
            dec = (0.8 + 0.025 * m + 0.018 * m * m) * (1 + 100 * term) + structural_decay_db_per_s(fm, f0, Wt, 0, 0, 0, 0, 0.0, 0.6477)
            e += (a * 10 ** (-dec * 0.35 / 20)) ** 2
        return 10 * math.log10(e)
    fs_, fp_ = ser['fres'], par['fres']
    d_par = band_db(par, fs_) - band_db(par, fp_)
    d_ser = band_db(ser, fs_) - band_db(ser, fp_)
    integ['t035_series'] = dict(f_series=fs_, f_parallel=fp_, predicted_delta_db=d_ser - d_par)
    out['integration'] = integ
    for k, v in integ.items(): pr('integration', k, v)
    json.dump(out, open("research/spikes/physics_expected.json", "w"), indent=0)
    pr("wrote research/spikes/physics_expected.json")

if __name__ == "__main__":
    main()
