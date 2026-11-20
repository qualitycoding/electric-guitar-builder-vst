// egb_demo <events-file> <out.wav> [<parameter_id>=<value> ...]
// Renders an event file at 44.1 kHz with the default snapshot plus the given assignments (applied
// through the descriptor table) and writes a 24-bit WAV and <out.wav>.json metadata. Exit 2 on a
// usage error, unknown parameter ID, non-numeric value or a value the snapshot validation rejects.
#include "egb/Engine.h"
#include <chrono>
#include <ctime>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <string>

using egb::ParameterSnapshot;
using Setter = std::function<void(ParameterSnapshot&, double)>;

static std::map<std::string, Setter> setters() {
  std::map<std::string, Setter> m;
  m["scale_length_mm"] = [](auto& p, double v) { p.scaleLengthMm = v; };
  m["fret_crown_height_mm"] = [](auto& p, double v) { p.fretCrownHeightMm = v; };
  m["fret_crown_width_mm"] = [](auto& p, double v) { p.fretCrownWidthMm = v; };
  m["neck_material"] = [](auto& p, double v) { p.neckMaterial = (int)v; };
  m["body_material"] = [](auto& p, double v) { p.bodyMaterial = (int)v; };
  m["string_material"] = [](auto& p, double v) { p.stringMaterial = (int)v; };
  m["pickup_combination"] = [](auto& p, double v) { p.pickupCombination = (int)v; };
  m["pick_angle_deg"] = [](auto& p, double v) { p.pickAngleDeg = v; };
  m["pick_depth_mm"] = [](auto& p, double v) { p.pickDepthMm = v; };
  m["palm_mute"] = [](auto& p, double v) { p.palmMute = v; };
  m["master_gain_db"] = [](auto& p, double v) { p.masterGainDb = v; };
  m["pickup_pot_kohm"] = [](auto& p, double v) { p.pickupPotIndex = (int)v; };
  m["cable_capacitance_pf"] = [](auto& p, double v) { p.cableCapacitancePf = v; };
  m["amp_input_impedance_mohm"] = [](auto& p, double v) { p.ampInputImpedanceMohm = v; };
  m["neck_joint"] = [](auto& p, double v) { p.neckJoint = (int)v; };
  m["body_type"] = [](auto& p, double v) { p.bodyType = (int)v; };
  m["fingerboard_material"] = [](auto& p, double v) { p.fingerboardMaterial = (int)v; };
  m["pluck_position"] = [](auto& p, double v) { p.pluckPosition = v; };
  for (int i = 0; i < 6; ++i) {
    const std::string n = std::to_string(i + 1);
    m["string_gauge_" + n + "_in"] = [i](auto& p, double v) { p.stringGaugeIn[i] = v; };
    m["tuning_offset_" + n + "_semitones"] = [i](auto& p, double v) { p.tuningOffsetSemitones[i] = (int)v; };
  }
  for (int i = 0; i < 3; ++i) {
    const std::string n = std::to_string(i + 1);
    m["pickup_" + n + "_type"] = [i](auto& p, double v) { p.pickupType[i] = (int)v; };
    m["pickup_" + n + "_from_bridge_mm"] = [i](auto& p, double v) { p.pickupFromBridgeMm[i] = v; };
    m["pickup_" + n + "_enabled"] = [i](auto& p, double v) { p.pickupEnabled[i] = v != 0; };
    m["pickup_" + n + "_phase_inverted"] = [i](auto& p, double v) { p.pickupPhaseInverted[i] = v != 0; };
  }
  return m;
}

static bool writeWav24(const std::string& path, const std::vector<float>& x, double fs) {
  std::ofstream o(path, std::ios::binary);
  if (!o) return false;
  auto u32 = [&](std::uint32_t v) { for (int i = 0; i < 4; ++i) o.put((char)((v >> (8 * i)) & 0xff)); };
  auto u16 = [&](std::uint16_t v) { o.put((char)(v & 0xff)); o.put((char)(v >> 8)); };
  const std::uint32_t dataSz = (std::uint32_t)(x.size() * 3);
  o.write("RIFF", 4); u32(36 + dataSz); o.write("WAVEfmt ", 8); u32(16); u16(1); u16(1);
  u32((std::uint32_t)fs); u32((std::uint32_t)fs * 3); u16(3); u16(24); o.write("data", 4); u32(dataSz);
  for (float f : x) {
    const double c = f > 1.0f ? 1.0 : f < -1.0f ? -1.0 : f;
    const std::int32_t v = (std::int32_t)std::lround(c * 8388607.0);
    o.put((char)(v & 0xff)); o.put((char)((v >> 8) & 0xff)); o.put((char)((v >> 16) & 0xff));
  }
  return (bool)o;
}

int main(int argc, char** argv) {
  if (argc < 3) { std::fprintf(stderr, "usage: egb_demo <events-file> <out.wav> [<parameter_id>=<value> ...]\n"); return 2; }
  std::ifstream in(argv[1]);
  if (!in) { std::fprintf(stderr, "egb_demo: cannot read %s\n", argv[1]); return 2; }
  std::stringstream ss; ss << in.rdbuf();
  ParameterSnapshot snap;
  std::map<std::string, std::string> assigned;
  const auto table = setters();
  for (int i = 3; i < argc; ++i) {
    const std::string a = argv[i];
    const auto eq = a.find('=');
    if (eq == std::string::npos) { std::fprintf(stderr, "egb_demo: expected <parameter_id>=<value>: %s\n", a.c_str()); return 2; }
    const auto it = table.find(a.substr(0, eq));
    if (it == table.end()) { std::fprintf(stderr, "egb_demo: unknown parameter id: %s\n", a.substr(0, eq).c_str()); return 2; }
    char* end = nullptr;
    const std::string val = a.substr(eq + 1);
    const double v = std::strtod(val.c_str(), &end);
    if (val.empty() || *end != 0) { std::fprintf(stderr, "egb_demo: non-numeric value: %s\n", a.c_str()); return 2; }
    it->second(snap, v);
    assigned[a.substr(0, eq)] = val;
  }
  const auto ok = ParameterSnapshot::validate(snap);
  if (!ok.ok) { std::fprintf(stderr, "egb_demo: invalid value: %s\n", ok.error.c_str()); return 2; }
  egb::EventFile ef; ef.text = ss.str();
  const double fs = 44100;
  const auto r = egb::renderEventFile(ef, snap, fs);
  if (r.status != "ok" || r.monoPcm.empty()) { std::fprintf(stderr, "egb_demo: render failed: %s\n", r.status.c_str()); return 1; }
  if (!writeWav24(argv[2], r.monoPcm, fs)) { std::fprintf(stderr, "egb_demo: cannot write %s\n", argv[2]); return 1; }
  std::string eventSha(64, '0');  // sha256sum of the event file (Linux demo tool)
  if (FILE* pp = popen((std::string("sha256sum '") + argv[1] + "'").c_str(), "r")) {
    char buf[65] = {0};
    if (std::fread(buf, 1, 64, pp) == 64) eventSha = buf;
    pclose(pp);
  }
  std::ostringstream md;
  md.precision(17);
  md << "{\"commit\":\"" << EGB_COMMIT << "\",\"lock_sha256\":\"" << EGB_LOCK_SHA256 << "\",\"seed\":" << ef.seed
     << ",\"parameters\":{";
  const auto& d = ParameterSnapshot::descriptors();
  for (size_t i = 0; i < d.size(); ++i) {
    const auto a = assigned.find(d[i].id);
    md << (i ? "," : "") << "\"" << d[i].id << "\":";
    if (a != assigned.end()) md << a->second; else md << d[i].defaultValue;
  }
  const std::time_t now = std::time(nullptr);
  char ts[32]; std::strftime(ts, sizeof ts, "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now));
#if defined(__aarch64__)
  const char* plat = "linux-arm64";
#else
  const char* plat = "linux-x64";
#endif
  md << "},\"event_file\":\"" << argv[1] << "\",\"event_sha256\":\""
     << eventSha
     << "\",\"utc_timestamp\":\"" << ts << "\",\"sample_rate\":" << (int)fs
     << ",\"unclipped_peak\":" << r.preSafetyPeak << ",\"post_safety_peak\":" << r.postSafetyPeak
     << ",\"platform\":\"" << plat << "\"}";
  std::ofstream(std::string(argv[2]) + ".json") << md.str() << "\n";
  return 0;
}
