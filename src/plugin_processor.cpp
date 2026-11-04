// Host-processor facade over the shared engine. The desktop VST3 wrapper
// (cmake/Desktop.cmake) delegates to this exact class.
#include "egb/PluginProcessor.h"
#include <juce_core/juce_core.h>

namespace egb {

EgbAudioProcessor::EgbAudioProcessor() { engine.prepare(48000, 512, 16); }
EgbAudioProcessor::~EgbAudioProcessor() = default;

void EgbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  engine.prepare(sampleRate, std::max(1, samplesPerBlock), 16);
}
void EgbAudioProcessor::releaseResources() { engine.reset(); }

void EgbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) {
  // No allocation, locks, I/O or logging on this path (D-005/T-014).
  buffer.clear();
  engine.render(buffer, midi);
}

void EgbAudioProcessor::copyXmlToBinary(const juce::XmlElement& xml, juce::MemoryBlock& destData) {
  // Same wire format as juce::AudioProcessor::copyXmlToBinary: XML text
  // compressed with JUCE's GZIP, 8-byte header holding the uncompressed size.
  destData.reset();
  const juce::String xmlString = xml.toString();
  const int originalSize = xmlString.getNumBytesAsUTF8();
  destData.append(&originalSize, sizeof(originalSize));
  juce::MemoryOutputStream out(destData, true);
  juce::GZIPCompressorOutputStream gz(out);
  gz.writeText(xmlString, false, false, nullptr);
}

juce::XmlElement* EgbAudioProcessor::getXmlFromBinary(const void* data, int sizeInBytes) {
  if (sizeInBytes > (int)(256 * 1024 + 8) || sizeInBytes < 8) return nullptr;
  int originalSize = 0;
  std::memcpy(&originalSize, data, sizeof(originalSize));
  if (originalSize <= 0 || originalSize > 256 * 1024) return nullptr;
  juce::MemoryInputStream in(static_cast<const char*>(data) + sizeof(originalSize),
                             (size_t)sizeInBytes - sizeof(originalSize), false);
  juce::GZIPDecompressorInputStream gz(in);
  juce::MemoryBlock mb;
  mb.setSize((size_t)originalSize + 8);
  const int rd = gz.read(mb.getData(), originalSize);
  if (rd != originalSize) return nullptr;
  return juce::XmlDocument::parse(juce::String::createStringFromData(
      static_cast<const char*>(mb.getData()), rd)).release();
}

void EgbAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
  juce::XmlElement xml("egb_state");
  xml.setAttribute("schemaVersion", 1);
  const auto& p = currentParams;
  xml.setAttribute("scale_length_mm", p.scaleLengthMm);
  xml.setAttribute("fret_crown_height_mm", p.fretCrownHeightMm);
  xml.setAttribute("fret_crown_width_mm", p.fretCrownWidthMm);
  xml.setAttribute("neck_material", p.neckMaterial);
  xml.setAttribute("body_material", p.bodyMaterial);
  xml.setAttribute("string_material", p.stringMaterial);
  for (int i = 0; i < 6; ++i) {
    xml.setAttribute("string_gauge_" + juce::String(i + 1) + "_in", p.stringGaugeIn[i]);
    xml.setAttribute("tuning_offset_" + juce::String(i + 1) + "_semitones", p.tuningOffsetSemitones[i]);
  }
  for (int i = 0; i < 3; ++i) {
    xml.setAttribute("pickup_" + juce::String(i + 1) + "_type", p.pickupType[i]);
    xml.setAttribute("pickup_" + juce::String(i + 1) + "_from_bridge_mm", p.pickupFromBridgeMm[i]);
    xml.setAttribute("pickup_" + juce::String(i + 1) + "_enabled", p.pickupEnabled[i]);
    xml.setAttribute("pickup_" + juce::String(i + 1) + "_phase_inverted", p.pickupPhaseInverted[i]);
  }
  xml.setAttribute("pickup_combination", p.pickupCombination);
  xml.setAttribute("pick_angle_deg", p.pickAngleDeg);
  xml.setAttribute("pick_depth_mm", p.pickDepthMm);
  xml.setAttribute("palm_mute", p.palmMute);
  xml.setAttribute("master_gain_db", p.masterGainDb);
  copyXmlToBinary(xml, destData);
}

void EgbAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
  if (sizeInBytes > 256 * 1024) return; // D-005: reject > 256 KiB atomically
  std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
  if (!xml || xml->getIntAttribute("schemaVersion") != 1) return;
  bool anyUnknown = false;
  for (int i = 0; i < xml->getNumAttributes(); ++i) {
    const juce::String id = xml->getAttributeName(i);
    bool known = id == "schemaVersion";
    for (auto& d : ParameterSnapshot::descriptors())
      if (id == d.id) { known = true; break; }
    if (!known) anyUnknown = true;
  }
  if (anyUnknown) return; // atomic rejection of unknown IDs
  ParameterSnapshot p;
  p.scaleLengthMm = xml->getDoubleAttribute("scale_length_mm", p.scaleLengthMm);
  p.fretCrownHeightMm = xml->getDoubleAttribute("fret_crown_height_mm", p.fretCrownHeightMm);
  p.fretCrownWidthMm = xml->getDoubleAttribute("fret_crown_width_mm", p.fretCrownWidthMm);
  p.neckMaterial = xml->getIntAttribute("neck_material", p.neckMaterial);
  p.bodyMaterial = xml->getIntAttribute("body_material", p.bodyMaterial);
  p.stringMaterial = xml->getIntAttribute("string_material", p.stringMaterial);
  for (int i = 0; i < 6; ++i) {
    p.stringGaugeIn[i] = xml->getDoubleAttribute("string_gauge_" + juce::String(i + 1) + "_in", p.stringGaugeIn[i]);
    p.tuningOffsetSemitones[i] = xml->getIntAttribute("tuning_offset_" + juce::String(i + 1) + "_semitones", p.tuningOffsetSemitones[i]);
  }
  for (int i = 0; i < 3; ++i) {
    p.pickupType[i] = xml->getIntAttribute("pickup_" + juce::String(i + 1) + "_type", p.pickupType[i]);
    p.pickupFromBridgeMm[i] = xml->getDoubleAttribute("pickup_" + juce::String(i + 1) + "_from_bridge_mm", p.pickupFromBridgeMm[i]);
    p.pickupEnabled[i] = xml->getBoolAttribute("pickup_" + juce::String(i + 1) + "_enabled", p.pickupEnabled[i]);
    p.pickupPhaseInverted[i] = xml->getBoolAttribute("pickup_" + juce::String(i + 1) + "_phase_inverted", p.pickupPhaseInverted[i]);
  }
  p.pickupCombination = xml->getIntAttribute("pickup_combination", p.pickupCombination);
  p.pickAngleDeg = xml->getDoubleAttribute("pick_angle_deg", p.pickAngleDeg);
  p.pickDepthMm = xml->getDoubleAttribute("pick_depth_mm", p.pickDepthMm);
  p.palmMute = xml->getDoubleAttribute("palm_mute", p.palmMute);
  p.masterGainDb = xml->getDoubleAttribute("master_gain_db", p.masterGainDb);
  if (!ParameterSnapshot::validate(p).ok) return;
  currentParams = p;
  engine.setParameters(p); // validated whole-snapshot swap (D-005)
}

} // namespace egb
