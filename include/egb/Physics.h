#pragma once
// Amendment 03 physics contract (plan/DECISIONS.md D-021..D-028).
// The executable specification is research/spikes/physics_oracle.py; the
// frozen cases T-040..T-044 compare these functions with
// research/spikes/physics_expected.json at 1e-12 relative (1e-10 for the
// digital biquad). Implementations live in src/physics.cpp and must not
// change these signatures or constants (FROZEN with the amendment-03 tests).
// All functions are pure, allocation-free and safe to call when a voice
// starts or a parameter snapshot is applied; none is called per sample.

namespace egb::phys {

// ---- D-025 pickup electrics -------------------------------------------
struct CoilParams { double inductanceH, resistanceOhm, capacitanceF; };
// type: 0 single_coil, 1 p90, 2 humbucker (series coils).
CoilParams coilParams(int type);
inline constexpr double kAmpInputCapacitanceF = 150e-12;     // C-012
inline constexpr double kPotChoicesKohm[3] = {250.0, 500.0, 1000.0};
// Volume and tone pots (both potKohm, fully open) in parallel with the
// amplifier input resistance ampMohm (C-012). Returns ohms.
double loadResistanceOhm(double potKohm, double ampMohm);

struct AnalogRlc {
  double a2, a1, a0;   // H(s) = 1 / (a2 s^2 + a1 s + a0)
  double fresHz, q;    // 1/(2 pi sqrt(a2)), sqrt(a2 a0)/a1
  double rloadOhm, ctotalF;
};
AnalogRlc rlcAnalog(int type, double potKohm, double cablePf, double ampMohm);

// Normalised biquad, a0 = 1: y = b0 x + b1 x1 + b2 x2 - a1 y1 - a2 y2.
struct Biquad { double b0, b1, b2, a1, a2; };
// Bilinear transform prewarped at fresHz (D-025).
Biquad rlcDigital(const AnalogRlc& analog, double sampleRate);

// ---- D-027 pluck --------------------------------------------------------
// Traube & Smith (2001) eq. (9), h = 1; R = pluck point / speaking length,
// measured from the bridge, 0 < R < 1.
double pluckAmplitude(int mode, double R);

// ---- D-026 velocity transduction -----------------------------------------
// Mode velocity relative to the fundamental: fm / f1.
double velocityGain(double modeHz, double fundamentalHz);

// Horizontal-polarisation coupling relative to vertical (v1 constants kept,
// D-026): 1 / (1 + (modeHz * kHorizontalCouplingM[type] / 200)^2).
inline constexpr double kHorizontalCouplingM[3] = {0.018, 0.022, 0.028};
double horizontalCoupling(double modeHz, int type);

// ---- D-021 spatial sampling -----------------------------------------------
inline constexpr double kApertureM[3] = {0.008, 0.016, 0.005}; // single, p90, per humbucker pole
inline constexpr double kHumbuckerPoleSpacingM = 0.0185;       // C-019
inline constexpr double kHumbuckerSecondCoilDb = -2.5;         // C-019
// Sensing weight of mode m for a pickup centred xpM from the bridge on a
// speaking length speakingM (wavenumber k = m pi / speakingM).
double pickupSpatial(int mode, double xpM, double speakingM, int type);

// ---- D-022 / D-023 / D-028 structural loss --------------------------------
// neck: 0 maple, 1 mahogany; joint: 0 bolt_on, 1 set_neck, 2 neck_through;
// fingerboard: 0 maple, 1 rosewood, 2 ebony; body: 0 solid, 1 chambered, 2 hollow.
// xBearingM: distance of the string's neck-side bearing (nut or fret) from
// the nut; openScaleM: open scale length. Conductances in s/kg.
double neckConductance(double freqHz, int neck, int joint, int fingerboard,
                       double xBearingM, double openScaleM);
double bridgeConductance(double freqHz, int body);
double waveImpedance(double tensionN, double muKgPerM);
// Extra decay (dB/s) of a mode at modeHz on a string with fundamental
// fundamentalHz and wave impedance W, from absorption at both bearings
// (C-023): a^2 = min(4 W (Gneck + Gbridge), 0.5);
// dB/s = 10 log10(e) * f1 * (-ln(1 - a^2)).
double structuralDecayDbPerS(double modeHz, double fundamentalHz, double W,
                             int neck, int joint, int fingerboard, int body,
                             double xBearingM, double openScaleM);

} // namespace egb::phys
