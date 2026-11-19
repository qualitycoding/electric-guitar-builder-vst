// Planning sketch of include/egb/Physics.h (L-20261004T150400Z): a complete
// implementation written against the header alone, used only to show that
// T-040..T-044 have a zero-exit green path. Not production code; the
// implementer writes src/physics.cpp in S-102 (it may start from this file).
#include "egb/Physics.h"
#include "egb/Engine.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace egb::phys {
namespace {
constexpr double kPi = 3.14159265358979323846;
struct Peak { double f, g, q; };
const Peak kNeck[2][2] = {{{205.0, 0.006, 25.0}, {450.0, 0.004, 25.0}}, {{203.0, 0.006, 18.0}, {446.0, 0.004, 18.0}}};
const double kJoint[3][2] = {{1.00, 1.00}, {1.00, 0.90}, {1.03, 0.80}};
const double kFb[3][2] = {{1.00, 1.00}, {0.98, 1.00}, {0.97, 0.95}};
double resonant(double f, double f0, double g, double q) { const double x = f / f0 - f0 / f; return g / (1.0 + q * q * x * x); }
double sincx(double x) { return std::abs(x) < 1e-12 ? 1.0 : std::sin(x) / x; }
}
CoilParams coilParams(int t) {
  switch (t) { case 1: return {6.0, 8000.0, 130e-12}; case 2: return {4.2, 8000.0, 150e-12}; default: return {2.2, 6000.0, 110e-12}; }
}
double loadResistanceOhm(double potKohm, double ampMohm) { return 1.0 / (2.0 / (potKohm * 1e3) + 1.0 / (ampMohm * 1e6)); }
AnalogRlc rlcAnalog(int type, double potKohm, double cablePf, double ampMohm) {
  const auto c = coilParams(type);
  const double rl = loadResistanceOhm(potKohm, ampMohm);
  const double ct = c.capacitanceF + cablePf * 1e-12 + kAmpInputCapacitanceF;
  AnalogRlc a{};
  a.a2 = c.inductanceH * ct; a.a1 = c.resistanceOhm * ct + c.inductanceH / rl; a.a0 = 1.0 + c.resistanceOhm / rl;
  a.fresHz = 1.0 / (2.0 * kPi * std::sqrt(a.a2)); a.q = std::sqrt(a.a2 * a.a0) / a.a1; a.rloadOhm = rl; a.ctotalF = ct;
  return a;
}
Biquad rlcDigital(const AnalogRlc& an, double fs) {
  const double w = 2.0 * kPi * an.fresHz, k = w / std::tan(kPi * an.fresHz / fs);
  const double A2 = an.a2 * k * k, A1 = an.a1 * k, A0 = an.a0, d0 = A2 + A1 + A0;
  return {1.0 / d0, 2.0 / d0, 1.0 / d0, 2.0 * (A0 - A2) / d0, (A2 - A1 + A0) / d0};
}
double pluckAmplitude(int m, double R) { return 2.0 * std::sin(m * kPi * R) / (m * m * kPi * kPi * R * (1.0 - R)); }
double velocityGain(double fm, double f1) { return fm / f1; }
double horizontalCoupling(double fm, int t) { const double x = fm * kHorizontalCouplingM[std::clamp(t, 0, 2)] / 200.0; return 1.0 / (1.0 + x * x); }
double pickupSpatial(int m, double xp, double Ls, int t) {
  const double k = m * kPi / Ls;
  const double ap = sincx(k * kApertureM[std::clamp(t, 0, 2)] / 2.0);
  if (t == 2) {
    const double d = kHumbuckerPoleSpacingM, g = std::pow(10.0, kHumbuckerSecondCoilDb / 20.0);
    return (std::sin(k * (xp - d / 2.0)) + g * std::sin(k * (xp + d / 2.0))) / (1.0 + g) * ap;
  }
  return std::sin(k * xp) * ap;
}
double neckConductance(double f, int neck, int joint, int fb, double x, double L0) {
  const double x2 = L0 * (1 - std::pow(2.0, -2.0 / 12)), x10 = L0 * (1 - std::pow(2.0, -10.0 / 12)), x12 = L0 / 2;
  const double phi[2] = {std::cos(kPi * x / (2.0 * x10)), std::sin(kPi * (x - x2) / (x12 - x2))};
  double g = 0;
  for (int k = 0; k < 2; ++k) {
    const auto& p = kNeck[neck][k];
    g += resonant(f, p.f * kJoint[joint][0] * kFb[fb][0], p.g * kJoint[joint][1] * kFb[fb][1], p.q) * phi[k] * phi[k];
  }
  return g;
}
double bridgeConductance(double f, int body) {
  if (body == 1) return 3e-4 + resonant(f, 230.0, 0.003, 6.0);
  if (body == 2) return 1e-3 + 0.003 / (1.0 + (f / 2000.0) * (f / 2000.0)) + resonant(f, 180.0, 0.02, 5.0) + resonant(f, 400.0, 0.012, 5.0);
  return 1e-4;
}
double waveImpedance(double T, double mu) { return std::sqrt(T * mu); }
double structuralDecayDbPerS(double fm, double f1, double W, int neck, int joint, int fb, int body, double x, double L0) {
  const double a2 = std::min(4.0 * W * (neckConductance(fm, neck, joint, fb, x, L0) + bridgeConductance(fm, body)), 0.5);
  return 10.0 * std::log10(std::exp(1.0)) * f1 * (-std::log(1.0 - a2));
}
} // namespace egb::phys

namespace egb {
std::vector<ModeDebug> debugModeTable(const ParameterSnapshot&, int, int, double) { return {}; }
PickupElectricalDebug debugPickupElectrical(const ParameterSnapshot&, int, double) {
  const double n = std::numeric_limits<double>::quiet_NaN(); return {n, n, n, n, n, n, n};
}
}
