// STUB (amendment 03 red verification). The implementing agent replaces this
// file in S-102 with the D-021..D-028 implementation of include/egb/Physics.h
// and the inspection functions declared in include/egb/Engine.h.
#include "egb/Physics.h"
#include "egb/Engine.h"
#include <limits>

namespace {
constexpr double kNotImplemented = std::numeric_limits<double>::quiet_NaN();
}

namespace egb::phys {
CoilParams coilParams(int) { return {kNotImplemented, kNotImplemented, kNotImplemented}; }
double loadResistanceOhm(double, double) { return kNotImplemented; }
AnalogRlc rlcAnalog(int, double, double, double) {
  return {kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented};
}
Biquad rlcDigital(const AnalogRlc&, double) { return {kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented}; }
double pluckAmplitude(int, double) { return kNotImplemented; }
double velocityGain(double, double) { return kNotImplemented; }
double horizontalCoupling(double, int) { return kNotImplemented; }
double pickupSpatial(int, double, double, int) { return kNotImplemented; }
double neckConductance(double, int, int, int, double, double) { return kNotImplemented; }
double bridgeConductance(double, int) { return kNotImplemented; }
double waveImpedance(double, double) { return kNotImplemented; }
double structuralDecayDbPerS(double, double, double, int, int, int, int, double, double) { return kNotImplemented; }
} // namespace egb::phys

namespace egb {
std::vector<ModeDebug> debugModeTable(const ParameterSnapshot&, int, int, double) { return {}; }
PickupElectricalDebug debugPickupElectrical(const ParameterSnapshot&, int, double) {
  return {kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented, kNotImplemented};
}
} // namespace egb
