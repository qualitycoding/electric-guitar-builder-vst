// S-ADVERSARIAL (Amendment 03) attack harness. Prints one line per attack; exit 1 on any break.
#include "egb/PluginProcessor.h"
#include <cmath>
#include <cstdio>
#include <string>
using namespace egb;
static int breaks = 0;
static void report(const std::string& n, bool ok, const std::string& d = "") {
  std::printf("%s  %s %s\n", ok ? "ok   " : "BREAK", n.c_str(), d.c_str());
  if (!ok) ++breaks;
}
struct Out { bool finite; double peak; };
static Out run(const ParameterSnapshot& p, double fs, int block, int voices, double seconds, int ch = 0) {
  Engine e; e.prepare(fs, std::max(block, 1), voices); e.setParameters(p);
  const int total = (int)(seconds * fs);
  Out o{true, 0};
  static const int notes[16] = {40,45,50,55,59,64,52,57,62,67,71,76,41,47,53,60};
  juce::AudioBuffer<float> buf(1, block);
  for (int pos = 0; pos < total; pos += block) {
    juce::MidiBuffer mb;
    if (pos == 0) for (int i = 0; i < voices && i < 16; ++i) mb.addEvent(juce::MidiMessage::noteOn(ch ? ch : 1 + i % 6, notes[i], (juce::uint8)127), 0);
    buf.clear(); e.render(buf, mb);
    for (int i = 0; i < block; ++i) { float s = buf.getSample(0, i); if (!std::isfinite(s)) o.finite = false; o.peak = std::max(o.peak, (double)std::fabs(s)); }
  }
  return o;
}
int main() {
  const double rates[] = {2000, 8000, 22050, 44100, 48000, 96000, 192000};
  ParameterSnapshot d;
  // 1. electrical corners at every rate, 16 voices
  for (double fs : rates) for (int t = 0; t < 3; ++t) for (double cab : {0.0, 2000.0}) for (double amp : {0.05, 10.0}) for (int pot = 0; pot < 3; pot += 2) {
    ParameterSnapshot p = d; p.pickupType = {t, t, t}; p.pickupEnabled = {true, true, true}; p.cableCapacitancePf = cab; p.ampInputImpedanceMohm = amp; p.pickupPotIndex = pot;
    for (int comb = 0; comb < 2; ++comb) { p.pickupCombination = comb;
      Out o = run(p, fs, 512, 16, 0.4);
      char n[160]; std::snprintf(n, sizeof n, "electrics fs=%g type=%d cable=%g amp=%g pot=%d comb=%d", fs, t, cab, amp, pot, comb);
      report(n, o.finite && o.peak <= 1.0001, "peak=" + std::to_string(o.peak)); }
  }
  // 2. pluck bounds x all body/joint/fingerboard at 16 voices
  for (double pp : {0.05, 0.5}) for (int b = 0; b < 3; ++b) for (int j = 0; j < 3; ++j) for (int f = 0; f < 3; ++f) {
    ParameterSnapshot p = d; p.pluckPosition = pp; p.bodyType = b; p.neckJoint = j; p.fingerboardMaterial = f;
    Out o = run(p, 44100, 256, 16, 0.3);
    char n[120]; std::snprintf(n, sizeof n, "structure pluck=%g body=%d joint=%d fb=%d", pp, b, j, f);
    report(n, o.finite && o.peak <= 1.0001 && o.peak > 0, "peak=" + std::to_string(o.peak));
  }
  // 3. rapid automation at block sizes 1 and 2048
  for (int blk : {1, 2048}) {
    Engine e; e.prepare(44100, blk, 16); bool fin = true;
    juce::AudioBuffer<float> buf(1, blk);
    for (int i = 0; i < (blk == 1 ? 20000 : 40); ++i) {
      ParameterSnapshot p = d; p.cableCapacitancePf = (i % 2) ? 0 : 2000; p.pickupPotIndex = i % 3; p.ampInputImpedanceMohm = (i % 2) ? 0.05 : 10;
      e.setParameters(p); juce::MidiBuffer mb; if (i % 50 == 0) mb.addEvent(juce::MidiMessage::noteOn(1 + i % 6, 60 + (i / 50) % 12 - 12 * ((i/50)%2), (juce::uint8)100), 0);
      buf.clear(); e.render(buf, mb);
      for (int k = 0; k < blk; ++k) if (!std::isfinite(buf.getSample(0, k))) fin = false;
    }
    report("automation block=" + std::to_string(blk), fin);
  }
  // 4. invalid values rejected, never reaching the engine
  {
    auto bad = [&](const char* n, ParameterSnapshot p) { report(std::string("reject ") + n, !ParameterSnapshot::validate(p).ok); };
    const double nan = std::nan(""), inf = INFINITY;
    ParameterSnapshot p;
    p = d; p.cableCapacitancePf = nan; bad("cable NaN", p);
    p = d; p.cableCapacitancePf = -1e-300; bad("cable -tiny", p);
    p = d; p.ampInputImpedanceMohm = 0; bad("amp 0", p);
    p = d; p.ampInputImpedanceMohm = inf; bad("amp inf", p);
    p = d; p.pluckPosition = 0.0; bad("pluck 0", p);
    p = d; p.pluckPosition = 1.0; bad("pluck 1", p);
    p = d; p.pickupPotIndex = 3; bad("pot 3", p);
    p = d; p.neckJoint = -1; bad("joint -1", p);
    p = d; p.bodyType = 99; bad("body 99", p);
    p = d; p.fingerboardMaterial = 3; bad("fb 3", p);
    p = d; p.pluckPosition = 4.9e-324; bad("pluck denormal", p);
  }
  // 5. state fuzzing
  {
    EgbAudioProcessor a; juce::MemoryBlock good; a.getStateInformation(good);
    std::unique_ptr<juce::XmlElement> xml(EgbAudioProcessor::getXmlFromBinary(good.getData(), (int)good.getSize()));
    auto tryState = [&](const char* n, juce::XmlElement& x, bool expectAccept) {
      EgbAudioProcessor b; ParameterSnapshot before = b.currentParams; juce::MemoryBlock m; EgbAudioProcessor::copyXmlToBinary(x, m);
      b.setStateInformation(m.getData(), (int)m.getSize());
      const bool accepted = !(b.currentParams == before) || expectAccept;
      report(std::string("state ") + n, expectAccept ? true : (b.currentParams == before));
      (void)accepted;
    };
    { juce::XmlElement x(*xml); x.setAttribute("schemaVersion", "2abc"); tryState("schemaVersion '2abc'", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("schemaVersion", 3); tryState("schemaVersion 3", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("schemaVersion", 0); tryState("schemaVersion 0", x, false); }
    { juce::XmlElement x(*xml); x.removeAttribute("cable_capacitance_pf"); tryState("missing v2 id", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("cable_capacitance_pf", "nan"); tryState("cable 'nan'", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("cable_capacitance_pf", "1e999"); tryState("cable 1e999", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("pluck_position", "0x1p-3"); tryState("pluck hex-float (must not change state)", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("body_type", "1.5"); tryState("body 1.5", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("extra_id", 1); tryState("unknown id", x, false); }
    { juce::XmlElement x(*xml); x.setAttribute("schemaVersion", 1); tryState("v2 payload labelled v1", x, false); }
    { juce::XmlElement x(*xml); x.addChildElement(new juce::XmlElement("child")); juce::MemoryBlock m; EgbAudioProcessor::copyXmlToBinary(x, m); EgbAudioProcessor b; b.setStateInformation(m.getData(), (int)m.getSize()); report("state child element no crash", true); }
    { EgbAudioProcessor b; for (int sz : {0, 1, 3, 8, 100}) { std::string junk(sz, '\xff'); b.setStateInformation(junk.data(), sz); } 
      for (int cut = 1; cut < (int)good.getSize(); cut += 7) b.setStateInformation(good.getData(), cut);
      report("state truncations no crash", true); }
  }
  std::printf("breaks=%d\n", breaks);
  return breaks ? 1 : 0;
}
