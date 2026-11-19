// Amendment 03 physics (plan/DECISIONS.md D-021..D-028). Mirrors
// research/spikes/physics_oracle.py function by function.
#include "egb/Physics.h"
#include "egb/Engine.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace {
constexpr double kNotImplemented = std::numeric_limits<double>::quiet_NaN();
constexpr double kPi = 3.14159265358979323846;

struct Coil { double L, R, C; };
constexpr Coil kCoil[3] = {{2.2, 6000.0, 110e-12}, {6.0, 8000.0, 130e-12}, {4.2, 8000.0, 150e-12}};

struct Res { double f, g, q; };
struct NeckMode { double f, g, q; };
constexpr NeckMode kNeck[2][2] = {{{205.0, 0.006, 25.0}, {450.0, 0.004, 25.0}},
                                  {{203.0, 0.006, 18.0}, {446.0, 0.004, 18.0}}};
constexpr double kJoint[3][2] = {{1.00, 1.00}, {1.00, 0.90}, {1.03, 0.80}};
constexpr double kFb[3][2] = {{1.00, 1.00}, {0.98, 1.00}, {0.97, 0.95}};

struct BridgeSpec { double base; int n; Res peaks[2]; double bb, corner; };
constexpr BridgeSpec kBridge[3] = {
    {1e-4, 0, {{0, 0, 1}, {0, 0, 1}}, 0.0, 2000.0},
    {3e-4, 1, {{230.0, 0.003, 6.0}, {0, 0, 1}}, 0.0, 2000.0},
    {1e-3, 2, {{180.0, 0.02, 5.0}, {400.0, 0.012, 5.0}}, 0.003, 2000.0}};

double resonant(double f, double f0, double gpk, double q) {
  const double r = f / f0 - f0 / f;
  return gpk / (1.0 + q * q * r * r);
}
double sincx(double x) { return std::fabs(x) < 1e-12 ? 1.0 : std::sin(x) / x; }

double neckShape(int k, double x, double L0) {
  const double x2 = L0 * (1.0 - std::pow(2.0, -2.0 / 12.0));
  const double x10 = L0 * (1.0 - std::pow(2.0, -10.0 / 12.0));
  const double x12 = L0 / 2.0;
  if (k == 0) return std::cos(kPi * x / (2.0 * x10));
  return std::sin(kPi * (x - x2) / (x12 - x2));
}
} // namespace

namespace egb::phys {
CoilParams coilParams(int type) {
  const Coil& c = kCoil[std::clamp(type, 0, 2)];
  return {c.L, c.R, c.C};
}

double loadResistanceOhm(double potKohm, double ampMohm) {
  return 1.0 / (2.0 / (potKohm * 1e3) + 1.0 / (ampMohm * 1e6));
}

AnalogRlc rlcAnalog(int type, double potKohm, double cablePf, double ampMohm) {
  const Coil& c = kCoil[std::clamp(type, 0, 2)];
  const double rl = loadResistanceOhm(potKohm, ampMohm);
  const double ct = c.C + cablePf * 1e-12 + kAmpInputCapacitanceF;
  AnalogRlc a{};
  a.a2 = c.L * ct;
  a.a1 = c.R * ct + c.L / rl;
  a.a0 = 1.0 + c.R / rl;
  a.fresHz = 1.0 / (2.0 * kPi * std::sqrt(a.a2));
  a.q = std::sqrt(a.a2 * a.a0) / a.a1;
  a.rloadOhm = rl;
  a.ctotalF = ct;
  return a;
}

Biquad rlcDigital(const AnalogRlc& an, double fs) {
  const double w = 2.0 * kPi * an.fresHz;
  const double k = w / std::tan(kPi * an.fresHz / fs);
  const double A2 = an.a2 * k * k, A1 = an.a1 * k, A0 = an.a0;
  const double d0 = A2 + A1 + A0;
  return {1.0 / d0, 2.0 / d0, 1.0 / d0, 2.0 * (A0 - A2) / d0, (A2 - A1 + A0) / d0};
}

double pluckAmplitude(int m, double R) {
  return 2.0 * std::sin(m * kPi * R) / (double(m) * m * kPi * kPi * R * (1.0 - R));
}

double velocityGain(double fm, double f1) { return fm / f1; }

double horizontalCoupling(double fm, int type) {
  const double x = fm * kHorizontalCouplingM[std::clamp(type, 0, 2)] / 200.0;
  return 1.0 / (1.0 + x * x);
}

double pickupSpatial(int m, double xp, double Ls, int type) {
  type = std::clamp(type, 0, 2);
  const double k = m * kPi / Ls;
  const double ap = sincx(k * kApertureM[type] / 2.0);
  double s;
  if (type == 2) {
    const double d = kHumbuckerPoleSpacingM;
    const double g = std::pow(10.0, kHumbuckerSecondCoilDb / 20.0);
    s = (std::sin(k * (xp - d / 2.0)) + g * std::sin(k * (xp + d / 2.0))) / (1.0 + g);
  } else {
    s = std::sin(k * xp);
  }
  return s * ap;
}

double neckConductance(double f, int neck, int joint, int fb, double xBearing, double L0) {
  neck = std::clamp(neck, 0, 1); joint = std::clamp(joint, 0, 2); fb = std::clamp(fb, 0, 2);
  const double fj = kJoint[joint][0], gj = kJoint[joint][1];
  const double ff = kFb[fb][0], gf = kFb[fb][1];
  double g = 0.0;
  for (int k = 0; k < 2; ++k) {
    const NeckMode& nm = kNeck[neck][k];
    const double phi = neckShape(k, xBearing, L0);
    g += resonant(f, nm.f * fj * ff, nm.g * gj * gf, nm.q) * phi * phi;
  }
  return g;
}

double bridgeConductance(double f, int body) {
  const BridgeSpec& b = kBridge[std::clamp(body, 0, 2)];
  double g = b.base + b.bb / (1.0 + (f / b.corner) * (f / b.corner));
  for (int i = 0; i < b.n; ++i) g += resonant(f, b.peaks[i].f, b.peaks[i].g, b.peaks[i].q);
  return g;
}

double waveImpedance(double tensionN, double mu) { return std::sqrt(tensionN * mu); }

double structuralDecayDbPerS(double fm, double f1, double W, int neck, int joint, int fb, int body,
                             double xBearing, double L0) {
  double a2 = 4.0 * W * (neckConductance(fm, neck, joint, fb, xBearing, L0) + bridgeConductance(fm, body));
  a2 = std::min(a2, 0.5);
  return 10.0 * std::log10(std::exp(1.0)) * f1 * (-std::log(1.0 - a2));
}
} // namespace egb::phys


namespace egb {
PickupElectricalDebug debugPickupElectrical(const ParameterSnapshot&, int, double) {
  return {kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented};
}
} // namespace egb
