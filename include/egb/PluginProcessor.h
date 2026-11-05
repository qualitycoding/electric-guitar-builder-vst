#pragma once
#include "egb/Engine.h"

namespace egb {
// Host-processor facade sharing the production Engine. On desktop builds this
// class is wrapped by the JUCE AudioProcessor in cmake/Desktop.cmake (VST3);
// the headless renderer and the contract suite use this same class so both
// paths exercise identical DSP and state code (T-020).
class EgbAudioProcessor {
public:
  EgbAudioProcessor();
  ~EgbAudioProcessor();

  void prepareToPlay(double sampleRate, int samplesPerBlock);
  void releaseResources();
  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

  // D-005 state: XML with schemaVersion=1, max 256 KiB, atomic validation.
  void getStateInformation(juce::MemoryBlock& destData);
  void setStateInformation(const void* data, int sizeInBytes);

  static void copyXmlToBinary(const juce::XmlElement& xml, juce::MemoryBlock& destData);
  static juce::XmlElement* getXmlFromBinary(const void* data, int sizeInBytes);

  Engine engine;
  ParameterSnapshot currentParams;
};
} // namespace egb
