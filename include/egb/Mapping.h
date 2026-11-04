#pragma once
// D-004 mapping formulas. These are the closed v1 coefficient contract (D-013);
// the executable oracle is research/spikes/model_spike.py and T-002 checks the
// two implementations agree to 1e-12 relative.
#include <algorithm>
#include <cmath>

namespace egb {

inline constexpr double kDensity = 7850.0;              // kg/m^3, nickel and steel (D-013)
inline constexpr double kYoungModulus = 200e9;          // Pa
inline constexpr double kA4 = 440.0;

// Material tables (D-013)
inline double neckLoss(int m)      { return m == 1 ? 1.2 : 0.8; }
inline double neckRes(int m)       { return m == 1 ? 0.85 : 1.0; }
inline double bodyLoss(int m)      { static const double t[4] = {1.0, 0.75, 1.2, 1.35}; return t[m & 3]; }
inline double bodyRes(int m)       { static const double t[4] = {1.0, 1.15, 0.85, 0.8}; return t[m & 3]; }
inline void pickupSpec(int type, double& resonanceHz, double& q, double& apertureM) {
  switch (type & 3) {
    case 1:  resonanceHz = 2900.0; q = 2.4; apertureM = 0.022; break; // p90
    case 2:  resonanceHz = 2400.0; q = 2.0; apertureM = 0.028; break; // humbucker
    default: resonanceHz = 3500.0; q = 2.8; apertureM = 0.018; break; // single_coil
  }
}

struct Mapping {
  double tensionN, inharmonicity, attackMs, pickNoiseDb;
  double extraDampingDbPerS, palmCutoffHz, terminationLoss, amplitude;
};

inline double midiToHz(double midi) { return kA4 * std::pow(2.0, (midi - 69.0) / 12.0); }

// Fret position: L_n = L_0 / 2^(n/12); fret dimensions never change this (D-003).
inline double fretLength(double openLengthM, int fret) {
  return openLengthM / std::pow(2.0, fret / 12.0);
}

inline Mapping computeMapping(double scaleInches = 25.5, double gaugeInches = 0.010,
                              double midi = 64.0, double fretHeightMm = 1.1,
                              int neck = 0, double pickAngleDeg = 15.0,
                              double pickDepthMm = 1.2, double palmMute = 0.0,
                              double velocity = 100.0) {
  const double scaleM = scaleInches * 0.0254;
  const double diameterM = gaugeInches * 0.0254;
  const double mu = kDensity * M_PI * diameterM * diameterM / 4.0;
  const double f0 = midiToHz(midi);
  Mapping p;
  p.tensionN = mu * std::pow(2.0 * scaleM * f0, 2.0);
  p.inharmonicity = std::pow(M_PI, 3) * kYoungModulus * std::pow(diameterM, 4)
                    / (64.0 * std::max(p.tensionN, 1e-6) * scaleM * scaleM);
  p.attackMs = std::clamp(5.0 + 6.0 * (1.0 - pickDepthMm / 3.0)
                              + 12.0 * std::abs(pickAngleDeg) / 60.0, 2.0, 30.0);
  p.pickNoiseDb = -38.0 + 10.0 * std::abs(pickAngleDeg) / 60.0 - 8.0 * pickDepthMm / 3.0;
  p.extraDampingDbPerS = 42.0 * std::pow(palmMute, 1.4);
  p.palmCutoffHz = 18000.0 * std::pow(900.0 / 18000.0, palmMute);
  p.terminationLoss = std::clamp(0.0005 + 0.0004 * fretHeightMm + 0.0002 * neckLoss(neck), 0.0, 0.01);
  p.amplitude = std::pow(velocity / 127.0, 1.5) * (0.35 + 0.65 * pickDepthMm / 3.0);
  return p;
}

// Mode decay in dB/s (D-013): baseline 0.8+0.025m dB/s before
// termination/material/palm terms; body loss scales resonance decay.
inline double modeDecayDbPerS(int mode, double bodyLossCoef, double terminationLoss,
                              double extraDampingDbPerS) {
  const double base = (0.8 + 0.025 * mode) * (1.0 + 100.0 * terminationLoss);
  return base * bodyLossCoef + extraDampingDbPerS / 8.0;
}

// Fret width high-frequency termination loss multiplier (D-013), interpolated
// linearly from 0 at 1 kHz to full at 8 kHz.
inline double fretWidthGain(double freqHz, double widthMm) {
  const double mul = std::clamp(1.0 + 0.2 * (widthMm - 2.4), 0.76, 1.24);
  const double g = std::clamp((freqHz - 1000.0) / 7000.0, 0.0, 1.0);
  return 1.0 + (mul - 1.0) * g;
}

} // namespace egb
