// Planning spike: writes tests/physics/state_v1.xml from the v1 engine at
// commit 61ab5ed (PluginProcessor unchanged by amendment 03 planning).
// Build: see research/spikes/state_v1_fixture/README.md
#include "egb/PluginProcessor.h"
#include <fstream>
#include <memory>
int main(int argc, char** argv) {
  egb::EgbAudioProcessor proc;
  proc.currentParams.palmMute = 0.25;
  proc.currentParams.scaleLengthMm = 628.65;
  proc.engine.setParameters(proc.currentParams);
  juce::MemoryBlock mb; proc.getStateInformation(mb);
  std::unique_ptr<juce::XmlElement> x(egb::EgbAudioProcessor::getXmlFromBinary(mb.getData(), (int)mb.getSize()));
  std::ofstream(argv[1]) << x->toString().toStdString();
  return x ? 0 : 1;
}
