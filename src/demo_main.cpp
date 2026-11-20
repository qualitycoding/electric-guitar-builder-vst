// egb_demo <events-file> <out.wav> [<parameter_id>=<value> ...]
// Renders an event file at 44.1 kHz with the default snapshot plus the given assignments (applied
// through the descriptor table) and writes a 24-bit WAV and <out.wav>.json metadata. Exit 2 on a
// usage error, unknown parameter ID, non-numeric value or a value the snapshot validation rejects.
#include "egb/Engine.h"
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

// Compact SHA-256 (FIPS 180-4) for the event-file hash in the metadata; portable, no popen.
static std::string sha256Hex(const std::string& msg) {
  static const std::uint32_t K[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
    0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
    0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
    0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
  std::uint32_t h[8] = {0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};
  std::string m = msg;
  const std::uint64_t bits = (std::uint64_t)msg.size() * 8;
  m.push_back((char)0x80);
  while (m.size() % 64 != 56) m.push_back((char)0);
  for (int i = 7; i >= 0; --i) m.push_back((char)((bits >> (8 * i)) & 0xff));
  auto rotr = [](std::uint32_t x, int n) { return (x >> n) | (x << (32 - n)); };
  for (size_t off = 0; off < m.size(); off += 64) {
    std::uint32_t w[64];
    for (int i = 0; i < 16; ++i)
      w[i] = ((std::uint32_t)(unsigned char)m[off + 4 * i] << 24) | ((std::uint32_t)(unsigned char)m[off + 4 * i + 1] << 16) |
             ((std::uint32_t)(unsigned char)m[off + 4 * i + 2] << 8) | (std::uint32_t)(unsigned char)m[off + 4 * i + 3];
    for (int i = 16; i < 64; ++i) {
      const std::uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
      const std::uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    std::uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
    for (int i = 0; i < 64; ++i) {
      const std::uint32_t t1 = hh + (rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25)) + ((e & f) ^ (~e & g)) + K[i] + w[i];
      const std::uint32_t t2 = (rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
      hh = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
    }
    h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
  }
  char out[65];
  for (int i = 0; i < 8; ++i) std::snprintf(out + 8 * i, 9, "%08x", h[i]);
  return out;
}

static const char* platformString() {
#if defined(_WIN32)
  return "windows-x64";
#elif defined(__APPLE__)
  return "macos-arm64";
#elif defined(__linux__) && defined(__aarch64__)
  return "linux-arm64";
#elif defined(__linux__)
  return "linux-x64";
#else
  return "unknown";
#endif
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
  const std::string eventSha = sha256Hex(ss.str());
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
  std::tm utc{};
#if defined(_WIN32)
  gmtime_s(&utc, &now);
#else
  gmtime_r(&now, &utc);
#endif
  char ts[32]; std::strftime(ts, sizeof ts, "%Y-%m-%dT%H:%M:%SZ", &utc);
  const char* plat = platformString();
  md << "},\"event_file\":\"" << argv[1] << "\",\"event_sha256\":\""
     << eventSha
     << "\",\"utc_timestamp\":\"" << ts << "\",\"sample_rate\":" << (int)fs
     << ",\"unclipped_peak\":" << r.preSafetyPeak << ",\"post_safety_peak\":" << r.postSafetyPeak
     << ",\"platform\":\"" << plat << "\"}";
  std::ofstream(std::string(argv[2]) + ".json") << md.str() << "\n";
  return 0;
}
