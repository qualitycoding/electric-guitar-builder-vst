#pragma once
// Planning stub only. S-001/S-002 implement these interfaces without changing them.
#include <cstdint>
#include <string>
#include <vector>
#include <juce_audio_basics/juce_audio_basics.h>
namespace egb {
struct Result { bool ok; std::string error; };
struct ParameterSnapshot { double scaleLengthMm{647.7}; static Result validate(const ParameterSnapshot&); };
struct EventFile { std::string text; std::uint64_t seed{20261104}; };
struct RenderMetadata { std::string json; };
struct RenderResult { std::vector<float> monoPcm; RenderMetadata metadata; };
class Engine {
public:
 void prepare(double sampleRate, int maxBlockSize, int voices);
 void setParameters(const ParameterSnapshot&);
 void render(juce::AudioBuffer<float>&, const juce::MidiBuffer&);
 void reset();
};
RenderResult renderEventFile(const EventFile&, const ParameterSnapshot&, double sampleRate);
}
