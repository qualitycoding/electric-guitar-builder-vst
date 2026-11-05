#pragma once
// Public engine interface for electric-guitar-builder-vst (D-001/D-003/D-005).
// Implementations must not change these signatures (plan S-001).
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <juce_audio_basics/juce_audio_basics.h>

namespace egb {

struct Result { bool ok; std::string error; };

enum class ParamType { Float, Int, Choice, Bool };

struct ParameterDescriptor {
  const char* id;
  ParamType type;
  double minValue;
  double maxValue;
  double defaultValue;
  const char* choices; // comma-separated for Choice, else empty
};

// Complete D-003 public parameter contract. Defaults per plan/DECISIONS.md.
struct ParameterSnapshot {
  double scaleLengthMm{647.7};
  double fretCrownHeightMm{1.1};
  double fretCrownWidthMm{2.4};
  int neckMaterial{0};   // 0 maple, 1 mahogany
  int bodyMaterial{0};   // 0 alder, 1 ash, 2 mahogany, 3 basswood
  int stringMaterial{0}; // 0 nickel, 1 steel
  std::array<double, 6> stringGaugeIn{0.010, 0.013, 0.017, 0.026, 0.036, 0.046};
  std::array<int, 6> tuningOffsetSemitones{0, 0, 0, 0, 0, 0};
  std::array<int, 3> pickupType{0, 1, 0};        // 0 single_coil, 1 p90, 2 humbucker
  std::array<double, 3> pickupFromBridgeMm{25.0, 65.0, 120.0};
  std::array<bool, 3> pickupEnabled{true, true, false};
  std::array<bool, 3> pickupPhaseInverted{false, false, false};
  int pickupCombination{0}; // 0 parallel, 1 series
  double pickAngleDeg{15.0};
  double pickDepthMm{1.2};
  double palmMute{0.0};
  double masterGainDb{-6.0};

  static const std::vector<ParameterDescriptor>& descriptors();
  static Result validate(const ParameterSnapshot&);
  bool operator==(const ParameterSnapshot&) const;
};

struct Event {
  enum class Type { NoteOn, NoteOff, Control };
  double timeSeconds;
  Type type;
  int midiNote;
  int velocity;
  int channel;
  int controlId;   // -1 for note events
  double controlValue;
};

struct EventFile {
  std::string text;
  std::uint64_t seed{20261104};
  static Result parse(const std::string& text, std::vector<Event>& out,
                      std::uint64_t& seedOut, std::string& error);
};

struct RenderMetadata { std::string json; };

struct RenderResult {
  std::vector<float> monoPcm;
  RenderMetadata metadata;
  // Diagnostics required by D-006/T-009.
  double preSafetyPeak{0.0};
  double postSafetyPeak{0.0};
  std::string status{"ok"};
};

class Engine {
public:
  Engine();
  ~Engine();
  void prepare(double sampleRate, int maxBlockSize, int voices);
  void setParameters(const ParameterSnapshot&);
  void render(juce::AudioBuffer<float>&, const juce::MidiBuffer&);
  void reset();
  // D-006: voice seed derivation is (globalSeed, stringIndex, noteCounter).
  void setSeed(std::uint64_t seed);
  // D-006 diagnostics: peak of the production signal immediately before the
  // tanh safety stage, accumulated across renderBlock calls since last reset.
  double lastPreSafetyPeak() const;

  struct Impl;
private:
  Impl* impl;
};

RenderResult renderEventFile(const EventFile&, const ParameterSnapshot&, double sampleRate);

} // namespace egb
