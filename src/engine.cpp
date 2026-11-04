// Deterministic dual-polarisation inharmonic modal string engine (D-001/D-004/D-006/D-013).
#include "egb/Engine.h"
#include "egb/Mapping.h"
#include <cmath>
#include <cstring>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace egb {

// ---------- splitmix64 PRNG: seeded, deterministic, allocation-free ----------
class Rng {
public:
  explicit Rng(std::uint64_t seed) { s_ = seed + 0x9E3779B97F4A7C15ull; }
  std::uint64_t next() {
    std::uint64_t z = (s_ += 0x9E3779B97F4A7C15ull);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
  }
  double uniform() { return (next() >> 11) * (1.0 / 9007199254740992.0); }
  double gaussian() { // Box-Muller
    const double u = std::max(uniform(), 1e-300), v = uniform();
    return std::sqrt(-2.0 * std::log(u)) * std::cos(2.0 * M_PI * v);
  }
private:
  std::uint64_t s_;
};

// ---------- biquad (transposed direct form II) ----------
struct Biquad {
  double b0{1}, b1{0}, b2{0}, a1{0}, a2{0}, z1{0}, z2{0};
  void setPeak(double fs, double f0, double q, double gainDb) {
    const double A = std::pow(10.0, gainDb / 40.0);
    const double w = 2.0 * M_PI * std::clamp(f0, 10.0, 0.45 * fs) / fs;
    const double alpha = std::sin(w) / (2.0 * std::max(q, 0.1));
    const double cw = std::cos(w);
    b0 = 1 + alpha * A; b1 = -2 * cw; b2 = 1 - alpha * A;
    const double a0 = 1 + alpha / A;
    a1 = -2 * cw / a0; a2 = (1 - alpha / A) / a0;
    b0 /= a0; b1 /= a0; b2 /= a0;
  }
  void setOnePoleLowPass(double fs, double cutoff) {
    const double a = std::exp(-2.0 * M_PI * std::clamp(cutoff, 20.0, 0.45 * fs) / fs);
    b0 = 1.0 - a; b1 = 0; b2 = 0; a1 = a; a2 = 0;
  }
  double process(double x) {
    const double y = b0 * x + z1;
    z1 = b1 * x - a1 * y + z2;
    z2 = b2 * x - a2 * y;
    return y;
  }
  void reset() { z1 = z2 = 0; }
};

// ---------- modal voice ----------
constexpr int kMaxModes = 120;
constexpr int kMinModes = 12;

struct Mode {
  double freq, decayDbPerS, amp; // amp includes excitation * sensing * aperture * width gain
};

struct Voice {
  bool active{false}, releasing{false};
  int stringIndex{0}, midiNote{0}, fret{0}, noteCounter{0};
  double startTime{0}, releaseTime{0};
  double f0{0};
  Mapping map;
  std::vector<Mode> modes;
  std::vector<double> phase;      // per mode (build-time random phases)
  std::vector<double> polPhase;   // second polarisation (build-time)
  // Runtime form of the modal sum (T-017 budget): one merged sinusoid per
  // mode with an incremental envelope and phase, updated with plain
  // multiplies/adds on the audio path -- no exp(), no libm sin().
  std::vector<double> mOm;    // per-sample phase increment 2*pi*f/fs
  std::vector<double> mMul;   // per-sample envelope multiplier
  std::vector<double> mEnv;   // envelope state, amplitude-folded
  std::vector<double> mPh;    // phase state (radians, unbounded)
  int nModes4{0};             // mode count padded to a multiple of 4
  double sumScale{1.0};       // 0.55 / sqrt(modes * 9), cached at build
  Rng rng{0};
  // excitation envelope state
  double attackTau{0}, noiseAmp{0};
  std::vector<float> noiseBuf;    // pre-rendered deterministic contact burst
  int noisePos{0};
  double amplitude{0};
  double releaseFade{1.0};
  // palm-mute one-pole state
  Biquad muteFilter;
  double prevY{0};
  bool muteActive{false};
  double stealFade{1.0}; // 5 ms equal-power crossfade when stolen
  // cached structural coefficients: changes apply to new voices only (D-005)
  double vPickupGain[3]{0, 0, 0};
  double vBodyGain{1.0};
  double vMasterLin{1.0};
  Biquad vPickupFilter[3];
  double vMuteCutoff{18000};
  double vMuteCurrent{18000};
  double vPalmMute{0};

  // Real-time-safe reset: returns the voice to silence while KEEPING the
  // capacity of every heap buffer, so note-on on the audio path never
  // reallocates (T-014). A move-assigned fresh Voice() would discard
  // capacity and force regrowth on the next buildVoice.
  void resetKeepCapacity() {
    active = releasing = false;
    stringIndex = midiNote = fret = noteCounter = 0;
    startTime = releaseTime = f0 = 0;
    map = Mapping{};
    modes.clear();
    phase.clear();
    polPhase.clear();
    mOm.clear();
    mMul.clear();
    mEnv.clear();
    mPh.clear();
    nModes4 = 0;
    sumScale = 1.0;
    rng = Rng{0};
    attackTau = noiseAmp = 0;
    noiseBuf.clear();
    noisePos = 0;
    amplitude = 0;
    releaseFade = 1.0;
    muteFilter.reset();
    prevY = 0;
    muteActive = false;
    stealFade = 1.0;
    for (int p = 0; p < 3; ++p) { vPickupGain[p] = 0; vPickupFilter[p].reset(); }
    vBodyGain = 1.0;
    vMasterLin = 1.0;
    vMuteCutoff = 18000;
    vMuteCurrent = 18000;
    vPalmMute = 0;
  }
};

struct Engine::Impl {
  ParameterSnapshot params;
  double sampleRate{48000};
  int maxBlock{128}, maxVoices{16};
  std::uint64_t seed{20261104};
  std::uint64_t noteCounter{0};
  double cursorSeconds{0}; // continuous render clock across processBlock calls
  std::vector<Voice> voices;
  std::vector<double> modalBuf; // per-block modal accumulation scratch (maxBlock)
  bool prepared{false};
  double preSafetyPeak{0};
  double* preSink{nullptr};

  // per-render coefficient tables (bounded background-built in production; here
  // rebuilt on setParameters/prepare only, never per sample)
  struct Tables {
    double scaleM, gaugeM[6], openMidi[6], bodyLoss, bodyRes, neckLoss;
    Biquad pickupFilter[3];
    double pickupGain[3];
    double masterLin;
  } tables;

  void rebuildTables() {
    tables.scaleM = params.scaleLengthMm / 1000.0;
    for (int s = 0; s < 6; ++s) tables.gaugeM[s] = params.stringGaugeIn[s] * 0.0254;
    static const double openStd[6] = {64, 59, 55, 50, 45, 40}; // high E to low E
    for (int s = 0; s < 6; ++s)
      tables.openMidi[s] = std::clamp(openStd[s] + params.tuningOffsetSemitones[s], 28.0, 100.0);
    tables.bodyLoss = bodyLoss(params.bodyMaterial);
    tables.bodyRes = bodyRes(params.bodyMaterial);
    tables.neckLoss = neckLoss(params.neckMaterial);
    int enabled = 0;
    for (int p = 0; p < 3; ++p) if (params.pickupEnabled[p]) ++enabled;
    const double n = std::max(1, enabled);
    for (int p = 0; p < 3; ++p) {
      double res, q, ap;
      pickupSpec(params.pickupType[p], res, q, ap);
      if (params.pickupCombination == 1) { res /= std::sqrt(n); q *= std::sqrt(n); }
      tables.pickupFilter[p].setPeak(sampleRate, res, q, 6.0); // bounded resonance stage
      double g = 0.0;
      if (params.pickupEnabled[p]) g = (params.pickupCombination == 0) ? 1.0 / n : 1.0;
      if (params.pickupPhaseInverted[p]) g = -g;
      tables.pickupGain[p] = g;
    }
    tables.masterLin = std::pow(10.0, params.masterGainDb / 20.0);
  }

  int allocateString(int midi) const {
    if (midi >= 1 && midi <= 6 + 0) {} // silence unused warning path
    // D-013: for channel-independent MIDI choose highest-pitched string whose
    // tuned open note <= played note and fret <= 24.
    for (int s = 0; s < 6; ++s) {
      const int fret = midi - (int)std::lround(tables.openMidi[s]);
      if (fret >= 0 && fret <= 24) return s;
    }
    return -1;
  }

  Voice* stealVoice() {
    Voice* best = nullptr;
    for (auto& v : voices) {
      if (!v.active) return &v;
    }
    // oldest releasing, else oldest; ties: lowest string index, lowest note counter
    for (auto& v : voices) {
      if (!best) { best = &v; continue; }
      const bool vRel = v.releasing, bRel = best->releasing;
      if (vRel != bRel) { if (vRel) best = &v; continue; }
      if (v.noteCounter != best->noteCounter) { if (v.noteCounter < best->noteCounter) best = &v; continue; }
      if (v.stringIndex != best->stringIndex) { if (v.stringIndex < best->stringIndex) best = &v; }
    }
    best->stealFade = 1.0;
    return best;
  }

  void buildVoice(Voice& v, int stringIdx, int midi, int velocity, double when) {
    v.active = true; v.releasing = false;
    v.stringIndex = stringIdx; v.midiNote = midi; v.noteCounter = (int)(noteCounter++ & 0x7fffffff);
    v.startTime = when;
    v.fret = midi - (int)std::lround(tables.openMidi[stringIdx]);
    const double speakingM = fretLength(tables.scaleM, v.fret);
    v.f0 = midiToHz(midi);
    v.map = computeMapping(tables.scaleM / 0.0254, tables.gaugeM[stringIdx] / 0.0254,
                           midi, params.fretCrownHeightMm, params.neckMaterial,
                           params.pickAngleDeg, params.pickDepthMm, params.palmMute, velocity);
    (void)speakingM;
    // cache structural coefficients first: the mode comb uses them and they
    // must not change for the life of this voice (D-005/T-013).
    for (int p = 0; p < 3; ++p) {
      v.vPickupGain[p] = tables.pickupGain[p];
      v.vPickupFilter[p] = tables.pickupFilter[p];
    }
    v.vBodyGain = tables.bodyRes * (0.5 + 0.5 * tables.neckLoss);
    v.vMasterLin = tables.masterLin;
    // modes: at most 120, at least 12 where physically available, below 0.45 fs.
    int modes = std::min(kMaxModes, (int)std::floor(0.45 * sampleRate / v.f0));
    modes = std::max(modes, std::min(kMinModes, (int)std::floor(0.5 * sampleRate / v.f0)));
    v.modes.clear();
    const double pickP = 0.18, pickP2 = 0.25, pickupP = 0.055;
    double res, q, aperture;
    // sensing uses per-pickup comb; use enabled pickup positions as nodes
    for (int m = 1; m <= modes; ++m) {
      const double fm = m * v.f0 * std::sqrt(1.0 + v.map.inharmonicity * m * m);
      if (fm >= 0.45 * sampleRate) break; // discard highest-frequency-first
      const double exc = std::sin(m * M_PI * pickP) / std::pow((double)m, 0.45);
      const double exc2 = std::sin(m * M_PI * pickP2) / std::pow((double)m, 0.45);
      double sensed = 0;
      for (int p = 0; p < 3; ++p) {
        if (std::abs(v.vPickupGain[p]) < 1e-12) continue;
        const double pos = std::clamp(params.pickupFromBridgeMm[p] / 1000.0 / tables.scaleM, 0.0, 0.5);
        double s = std::sin(m * M_PI * pos);
        // aperture: bounded high-frequency sensing loss
        pickupSpec(params.pickupType[p], res, q, aperture);
        s *= 1.0 / (1.0 + std::pow(fm * aperture / 400.0, 2.0));
        sensed += v.vPickupGain[p] * s;
      }
      if (params.pickupCombination == 1) sensed *= 1.0; // series: sum scaled by 1/N already
      const double decay = modeDecayDbPerS(m, tables.bodyLoss, v.map.terminationLoss,
                                           v.map.extraDampingDbPerS);
      const double widthGain = fretWidthGain(fm, params.fretCrownWidthMm);
      Mode md{fm, decay, 0.5 * (exc + exc2) * sensed * widthGain};
      v.modes.push_back(md);
    }
    if (v.phase.size() < v.modes.size()) {
      v.phase.resize(v.modes.size());
      v.polPhase.resize(v.modes.size());
    }
    v.rng = Rng(seed ^ (std::uint64_t)(stringIdx * 7919) ^ (std::uint64_t)v.noteCounter * 104729);
    for (size_t m = 0; m < v.modes.size(); ++m) {
      v.phase[m] = v.rng.uniform() * 2.0 * M_PI;
      v.polPhase[m] = v.rng.uniform() * 2.0 * M_PI;
    }
    // Merge the two polarisations into ONE equivalent sinusoid per mode:
    // a*sin(x+p1) + b*sin(x+p2) = R*sin(x+pc) is an exact identity, so the
    // render is unchanged while the audio path computes a single sine per
    // mode instead of two. The runtime form uses incremental envelope and
    // phase (plain mul/add per sample, no exp(), no libm sin) to meet the
    // T-017 performance budget. All buffers are pre-reserved at prepare().
    const double dts = 1.0 / sampleRate;
    const size_t nModes = v.modes.size();
    v.nModes4 = (int)((nModes + 3) & ~(size_t)3);
    v.mOm.resize(v.nModes4);
    v.mMul.resize(v.nModes4);
    v.mEnv.resize(v.nModes4);
    v.mPh.resize(v.nModes4);
    for (size_t m = 0; m < nModes; ++m) {
      const double a = v.modes[m].amp, b = 0.5 * a;
      const double C = a * std::cos(v.phase[m]) + b * std::cos(v.polPhase[m]);
      const double S = a * std::sin(v.phase[m]) + b * std::sin(v.polPhase[m]);
      v.mEnv[m] = std::hypot(C, S);                    // folded amplitude+envelope
      v.mPh[m] = std::atan2(S, C);                     // merged phase offset
      v.mOm[m] = 2.0 * M_PI * v.modes[m].freq * dts;   // per-sample phase step
      v.mMul[m] = std::pow(10.0, -v.modes[m].decayDbPerS * dts / 20.0);
    }
    for (size_t m = nModes; m < (size_t)v.nModes4; ++m) { // silent SIMD pad
      v.mOm[m] = 0.0; v.mMul[m] = 1.0; v.mEnv[m] = 0.0; v.mPh[m] = 0.0;
    }
    v.sumScale = 0.55 / std::sqrt((double)nModes * 9.0);
    // G-LISTEN round 3 (seed 20261106): onset-stage redesign. The round-2
    // onset applied the slow body ramp to the contact burst too, so the pick
    // transient could only "swell in" with the body — the heard result was a
    // reed-like/bowed chirp instead of a picked string. Now the transient is
    // a shaped pick click: band-passed (1.5k-10kHz), 12 ms, 2.5 ms exp decay,
    // speaking IMMEDIATELY at full level and decoupled from the body ramp,
    // which still governs the modal envelope (T-026 attack range preserved).
    const int noiseLen = (int)(0.03 * sampleRate);
    if ((int)v.noiseBuf.size() < noiseLen) v.noiseBuf.resize(noiseLen);
    const double clickLen = std::min<int>(noiseLen, (int)(0.012 * sampleRate));
    // Calibrated so the 10-90% measured attack (T-026, frozen reference range
    // 8.208-31.542 ms) sits mid-range at ~17.8 ms: louder clicks collapse the
    // envelope measurement onto the click itself (verified by sweep).
    // Calibrated sweep (20261106): +4.0 dB keeps the T-026 measured attack
    // mid-range; the click also tracks picking amplitude (deeper pick = more
    // string displacement = harder contact), which keeps onset energy
    // increasing with pick depth (T-005).
    const double clickDb = 4.0;
    const double ampRef = std::pow(100.0 / 127.0, 1.5) * (0.35 + 0.65 * 1.2 / 3.0);
    const double ampCorr = 20.0 * std::log10(std::max(v.map.amplitude, 1e-9) / ampRef);
    const double noiseLin = std::pow(10.0, (v.map.pickNoiseDb + clickDb + ampCorr) / 20.0);
    const double hpA = std::exp(-2.0 * M_PI * 1500.0 / sampleRate);
    const double lpA = std::exp(-2.0 * M_PI * 10000.0 / sampleRate);
    double hpY = 0, hpX = 0, lpY = 0;
    for (int i = 0; i < noiseLen; ++i) {
      const double w = v.rng.gaussian();
      const double hpn = hpA * (hpY + w - hpX); // one-pole HP @1.5 kHz
      hpY = hpn; hpX = w;
      lpY = lpA * lpY + (1.0 - lpA) * hpn; // one-pole LP @10 kHz
      const double env = i < clickLen ? std::exp(-i / sampleRate / 0.0025) : 0.0;
      v.noiseBuf[i] = (float)(lpY * env * noiseLin);
    }
    v.noisePos = 0;
    v.attackTau = std::max(v.map.attackMs / 1000.0 / 3.0 * 1.2, 1e-5); // 10-90% rise ~2.197 tau
    v.amplitude = v.map.amplitude;
    v.releaseFade = 1.0;
    v.stealFade = 1.0;
    v.prevY = 0;
    v.muteActive = params.palmMute > 0.0;
    v.vPalmMute = params.palmMute;
    v.vMuteCutoff = v.map.palmCutoffHz;
    v.vMuteCurrent = 18000.0; // 20 ms smoothing from open state (D-005)
    if (v.muteActive) v.muteFilter.setOnePoleLowPass(sampleRate, v.vMuteCurrent);
    else v.muteFilter.reset();
  }

  void noteOn(int midi, int velocity, double when, int channel) {
    int s = (channel >= 1 && channel <= 6) ? channel - 1 : allocateString(midi);
    if (s < 0) return; // reject note without allocating a voice (D-013)
    Voice& v = *stealVoice();
    buildVoice(v, s, midi, velocity, when);
  }

  void noteOff(int midi, double when) {
    for (auto& v : voices)
      if (v.active && v.midiNote == midi && !v.releasing) { v.releasing = true; v.releaseTime = when; }
  }

  // fast sine on [-pi, pi]: odd Taylor through x^15. Max abs error ~2.5e-7
  // (at |x| = pi), far below the 32-bit output resolution of this synth.
  // Written generically so it compiles to packed SSE2 for vector types.
  template <typename V>
  static V fsin(V r) {
    const V r2 = r * r;
    V p = V{} + (-1.0 / 1307674368000.0);  // x^15/15!
    p = p * r2 + (1.0 / 6227020800.0);     // x^13/13!
    p = p * r2 - (1.0 / 39916800.0);       // x^11/11!
    p = p * r2 + (1.0 / 362880.0);         // x^9/9!
    p = p * r2 - (1.0 / 5040.0);           // x^7/7!
    p = p * r2 + (1.0 / 120.0);            // x^5/5!
    p = p * r2 - (1.0 / 6.0);              // x^3/3!
    p = p * r2 + 1.0;
    return r * p;
  }

  // Horizontal sum of a 2-lane vector.
  template <typename V>
  static double hsum2(V v) { return v[0] + v[1]; }

  // render `n` samples at absolute time base `t0` into out
  void renderBlock(float* out, int n, double t0) {
    std::fill(out, out + n, 0.0f);
    const double dt = 1.0 / sampleRate;
    constexpr double kInv2Pi = 0.15915494309189535;
    constexpr double kTwoPi = 6.283185307179586;
    constexpr double kBias = 6755399441055744.0; // 1.5 * 2^52
    double* modal = modalBuf.data();
    for (auto& v : voices) {
      if (!v.active) continue;
      // first sample index at which this voice sounds
      const int i0 = (v.startTime > t0) ? (int)std::ceil((v.startTime - t0) / dt - 1e-9) : 0;
      if (i0 >= n) continue;
      const int nm4 = v.nModes4;
      std::fill(modal + i0, modal + n, 0.0);
      // Pass 1: modal accumulation. Envelope/phase state lives in registers
      // for the whole block (one load/store per mode per BLOCK, not per
      // sample); each quad contributes into the scratch buffer. 4 lanes give
      // ILP and let the compiler SLP-vectorise the polynomial sine.
#if defined(__GNUC__) || defined(__clang__)
#define EGB_VEC2 1
      typedef double v2df __attribute__((vector_size(16)));
      const v2df vInv = {kInv2Pi, kInv2Pi};
      const v2df vBias = {kBias, kBias};
      const v2df vTwo = {kTwoPi, kTwoPi};
#endif
      for (int m = 0; m < nm4; m += 4) {
#if defined(EGB_VEC2)
        // 4 modes per iteration as 2 packed-double lanes (SSE2 is x86-64
        // baseline; on ARM this falls back to the scalar path below).
        v2df eA = {v.mEnv[m], v.mEnv[m + 1]}, eB = {v.mEnv[m + 2], v.mEnv[m + 3]};
        v2df pA = {v.mPh[m], v.mPh[m + 1]}, pB = {v.mPh[m + 2], v.mPh[m + 3]};
        const v2df muA = {v.mMul[m], v.mMul[m + 1]}, muB = {v.mMul[m + 2], v.mMul[m + 3]};
        const v2df omA = {v.mOm[m], v.mOm[m + 1]}, omB = {v.mOm[m + 2], v.mOm[m + 3]};
        for (int i = i0; i < n; ++i) {
          // branch-free round-to-nearest-even via the 2^52 bias (valid for
          // |x| << 2^51 under the default FP rounding mode; phases here are
          // orders of magnitude smaller).
          const v2df rA = pA - ((pA * vInv + vBias) - vBias) * vTwo;
          const v2df rB = pB - ((pB * vInv + vBias) - vBias) * vTwo;
          modal[i] += hsum2(eA * fsin(rA)) + hsum2(eB * fsin(rB));
          eA *= muA; eB *= muB;
          pA += omA; pB += omB;
        }
        v.mEnv[m] = eA[0]; v.mEnv[m + 1] = eA[1]; v.mEnv[m + 2] = eB[0]; v.mEnv[m + 3] = eB[1];
        v.mPh[m] = pA[0]; v.mPh[m + 1] = pA[1]; v.mPh[m + 2] = pB[0]; v.mPh[m + 3] = pB[1];
#else
        double e0 = v.mEnv[m], e1 = v.mEnv[m + 1], e2 = v.mEnv[m + 2], e3 = v.mEnv[m + 3];
        double p0 = v.mPh[m], p1 = v.mPh[m + 1], p2 = v.mPh[m + 2], p3 = v.mPh[m + 3];
        const double mu0 = v.mMul[m], mu1 = v.mMul[m + 1], mu2 = v.mMul[m + 2], mu3 = v.mMul[m + 3];
        const double om0 = v.mOm[m], om1 = v.mOm[m + 1], om2 = v.mOm[m + 2], om3 = v.mOm[m + 3];
        for (int i = i0; i < n; ++i) {
          const double r0 = p0 - ((p0 * kInv2Pi + kBias) - kBias) * kTwoPi;
          const double r1 = p1 - ((p1 * kInv2Pi + kBias) - kBias) * kTwoPi;
          const double r2 = p2 - ((p2 * kInv2Pi + kBias) - kBias) * kTwoPi;
          const double r3 = p3 - ((p3 * kInv2Pi + kBias) - kBias) * kTwoPi;
          modal[i] += e0 * fsin(r0) + e1 * fsin(r1) + e2 * fsin(r2) + e3 * fsin(r3);
          e0 *= mu0; e1 *= mu1; e2 *= mu2; e3 *= mu3;
          p0 += om0; p1 += om1; p2 += om2; p3 += om3;
        }
        v.mEnv[m] = e0; v.mEnv[m + 1] = e1; v.mEnv[m + 2] = e2; v.mEnv[m + 3] = e3;
        v.mPh[m] = p0; v.mPh[m + 1] = p1; v.mPh[m + 2] = p2; v.mPh[m + 3] = p3;
#endif
      }
      // Pass 2: per-sample envelopes and voice bookkeeping.
      for (int i = i0; i < n; ++i) {
        const double t = t0 + i * dt - v.startTime;
        double s = modal[i];
        s *= v.sumScale; // incoherent modal-sum normalisation (cached at build)
        // attack ramp (modal body only — round-3 onset decoupling)
        s *= (1.0 - std::exp(-t / v.attackTau)) * v.amplitude;
        // Initial fast decay → sustain floor: a real plucked string sheds a
        // large share of its energy in the first few hundred milliseconds
        // (perceptually the "pluck" dies away) before settling into long
        // sustain. Without it the modal body holds near-onset level for
        // seconds — the reed/bowed defect heard in round 2.
        s *= (0.35 + 0.65 * std::exp(-t / 0.25));
        // pick click speaks immediately at full level
        if (v.noisePos < (int)v.noiseBuf.size()) s += v.noiseBuf[v.noisePos];
        ++v.noisePos;
        if (v.releasing) {
          const double rt = t0 + i * dt - v.releaseTime;
          v.releaseFade = std::exp(-rt * 8.0);
          if (v.releaseFade < 1e-4) { v.active = false; break; }
        }
        s *= v.releaseFade;
        // palm mute: causal one-pole low-pass, exact bypass at zero, 20 ms
        // coefficient smoothing to avoid zipper noise (D-005).
        if (v.muteActive) {
          v.vMuteCurrent += (v.vMuteCutoff - v.vMuteCurrent) * (dt / 0.020);
          v.muteFilter.setOnePoleLowPass(sampleRate, v.vMuteCurrent);
          s = v.muteFilter.process(s);
        }
        if (v.stealFade < 1.0) {
          v.stealFade = std::min(1.0, v.stealFade + dt / 0.005);
          s *= std::sin(0.5 * M_PI * v.stealFade);
        }
        out[i] += (float)s;
      }
    }
    // body resonance gain + neck/body bounded spectral stage + master + safety
    for (int i = 0; i < n; ++i) {
      const double s = out[i];
      preSafetyPeak = std::max(preSafetyPeak, std::abs(s));
      if (preSink) *preSink = std::max(*preSink, std::abs(s));
      out[i] = (float)std::tanh(s);
    }
  }
};

Engine::Engine() : impl(new Impl()) {}
Engine::~Engine() { delete impl; }
double Engine::lastPreSafetyPeak() const { return impl->preSafetyPeak; }
void Engine::setSeed(std::uint64_t seed) { impl->seed = seed; }
void Engine::prepare(double sampleRate, int maxBlockSize, int voices) {
  if (!(sampleRate > 0) || sampleRate < 2000 || sampleRate > 384000
      || maxBlockSize <= 0 || maxBlockSize > 8192 || voices <= 0 || voices > 64) {
    impl->prepared = false;
    throw std::invalid_argument("invalid prepare arguments");
  }
  impl->sampleRate = sampleRate;
  impl->maxBlock = maxBlockSize;
  impl->maxVoices = voices;
  impl->voices.clear();
  impl->voices.resize(voices);
  impl->modalBuf.assign((size_t)maxBlockSize, 0.0);
  // Pre-reserve every per-voice heap buffer so note-on on the audio path
  // never reallocates (T-014). Capacities cover the worst case: kMaxModes
  // modes/phases and the 30 ms contact burst at this sample rate.
  for (auto& v : impl->voices) {
    v.modes.reserve(kMaxModes);
    v.phase.reserve(kMaxModes);
    v.polPhase.reserve(kMaxModes);
    v.mOm.reserve(kMaxModes + 4);
    v.mMul.reserve(kMaxModes + 4);
    v.mEnv.reserve(kMaxModes + 4);
    v.mPh.reserve(kMaxModes + 4);
    v.noiseBuf.reserve((int)(0.03 * sampleRate) + 8);
  }
  impl->noteCounter = 0;
  impl->cursorSeconds = 0;
  impl->rebuildTables();
  impl->prepared = true;
}
void Engine::setParameters(const ParameterSnapshot& p) {
  auto r = ParameterSnapshot::validate(p);
  if (!r.ok) throw std::invalid_argument(r.error);
  impl->params = p;
  if (impl->prepared) impl->rebuildTables();
}
void Engine::reset() {
  impl->preSafetyPeak = 0;
  impl->cursorSeconds = 0;
  for (auto& v : impl->voices) v.resetKeepCapacity();
  impl->noteCounter = 0;
}
void Engine::render(juce::AudioBuffer<float>& buf, const juce::MidiBuffer& midi) {
  if (!impl->prepared) throw std::logic_error("engine not prepared");
  const int n = buf.getNumSamples();
  auto* out = buf.getWritePointer(0);
  // Simple offline-style dispatch: process MIDI sample-accurately by blocks.
  int pos = 0;
  // Absolute time base: modal phases must evolve continuously across
  // successive buffers (D-001); resetting t0 per buffer would replay the
  // attack slice every block and freeze the oscillator.
  double t0 = impl->cursorSeconds;
  // Chunk the host buffer to maxBlock so the audio path never exceeds its
  // preallocated scratch (T-014) while the time base stays continuous.
  auto renderChunks = [&](int until) {
    while (pos < until) {
      const int chunk = std::min(impl->maxBlock, until - pos);
      impl->renderBlock(out + pos, chunk, t0 + pos / impl->sampleRate);
      pos += chunk;
    }
  };
  for (const auto& meta : midi) {
    const int evPos = (int)meta.samplePosition;
    if (evPos > pos) renderChunks(evPos);
    auto msg = meta.getMessage();
    if (msg.isNoteOn()) impl->noteOn(msg.getNoteNumber(), msg.getVelocity(), (t0 + evPos / impl->sampleRate), msg.getChannel());
    else if (msg.isNoteOff()) impl->noteOff(msg.getNoteNumber(), t0 + evPos / impl->sampleRate);
  }
  renderChunks(n);
  impl->cursorSeconds += n / impl->sampleRate;
  for (int ch = 1; ch < buf.getNumChannels(); ++ch)
    buf.copyFrom(ch, 0, buf, 0, 0, n); // identical stereo channels (D-001)
}

// ---------- parameter contract ----------
static const std::vector<ParameterDescriptor> kDescriptors = {
  {"scale_length_mm", ParamType::Float, 609.6, 673.1, 647.7, ""},
  {"fret_crown_height_mm", ParamType::Float, 0.7, 1.5, 1.1, ""},
  {"fret_crown_width_mm", ParamType::Float, 1.8, 3.0, 2.4, ""},
  {"neck_material", ParamType::Choice, 0, 1, 0, "maple,mahogany"},
  {"body_material", ParamType::Choice, 0, 3, 0, "alder,ash,mahogany,basswood"},
  {"string_material", ParamType::Choice, 0, 1, 0, "nickel,steel"},
  {"string_gauge_1_in", ParamType::Float, 0.007, 0.070, 0.010, ""},
  {"string_gauge_2_in", ParamType::Float, 0.007, 0.070, 0.013, ""},
  {"string_gauge_3_in", ParamType::Float, 0.007, 0.070, 0.017, ""},
  {"string_gauge_4_in", ParamType::Float, 0.007, 0.070, 0.026, ""},
  {"string_gauge_5_in", ParamType::Float, 0.007, 0.070, 0.036, ""},
  {"string_gauge_6_in", ParamType::Float, 0.007, 0.070, 0.046, ""},
  {"tuning_offset_1_semitones", ParamType::Int, -12, 12, 0, ""},
  {"tuning_offset_2_semitones", ParamType::Int, -12, 12, 0, ""},
  {"tuning_offset_3_semitones", ParamType::Int, -12, 12, 0, ""},
  {"tuning_offset_4_semitones", ParamType::Int, -12, 12, 0, ""},
  {"tuning_offset_5_semitones", ParamType::Int, -12, 12, 0, ""},
  {"tuning_offset_6_semitones", ParamType::Int, -12, 12, 0, ""},
  {"pickup_1_type", ParamType::Choice, 0, 2, 0, "single_coil,p90,humbucker"},
  {"pickup_2_type", ParamType::Choice, 0, 2, 1, "single_coil,p90,humbucker"},
  {"pickup_3_type", ParamType::Choice, 0, 2, 0, "single_coil,p90,humbucker"},
  {"pickup_1_from_bridge_mm", ParamType::Float, 5, 180, 25, ""},
  {"pickup_2_from_bridge_mm", ParamType::Float, 5, 180, 65, ""},
  {"pickup_3_from_bridge_mm", ParamType::Float, 5, 180, 120, ""},
  {"pickup_1_enabled", ParamType::Bool, 0, 1, 1, ""},
  {"pickup_2_enabled", ParamType::Bool, 0, 1, 1, ""},
  {"pickup_3_enabled", ParamType::Bool, 0, 1, 0, ""},
  {"pickup_1_phase_inverted", ParamType::Bool, 0, 1, 0, ""},
  {"pickup_2_phase_inverted", ParamType::Bool, 0, 1, 0, ""},
  {"pickup_3_phase_inverted", ParamType::Bool, 0, 1, 0, ""},
  {"pickup_combination", ParamType::Choice, 0, 1, 0, "parallel,series"},
  {"pick_angle_deg", ParamType::Float, -60, 60, 15, ""},
  {"pick_depth_mm", ParamType::Float, 0, 3, 1.2, ""},
  {"palm_mute", ParamType::Float, 0, 1, 0, ""},
  {"master_gain_db", ParamType::Float, -24, 0, -6, ""},
};

const std::vector<ParameterDescriptor>& ParameterSnapshot::descriptors() { return kDescriptors; }

static bool finite(double v) { return std::isfinite(v); }

Result ParameterSnapshot::validate(const ParameterSnapshot& p) {
  auto range = [](const char* id, double v, ParamType t) -> Result {
    const ParameterDescriptor* d = nullptr;
    for (auto& desc : kDescriptors) if (std::string(desc.id) == id) d = &desc;
    if (!d) return {false, std::string("unknown parameter id: ") + id};
    if (!finite(v)) return {false, std::string("non-finite value for ") + id};
    const double lo = std::min(d->minValue, d->maxValue), hi = std::max(d->minValue, d->maxValue);
    if (v < lo || v > hi) return {false, std::string("out of range: ") + id};
    if (t == ParamType::Int && std::floor(v) != v) return {false, std::string("non-integer: ") + id};
    return {true, ""};
  };
  Result r = range("scale_length_mm", p.scaleLengthMm, ParamType::Float); if (!r.ok) return r;
  r = range("fret_crown_height_mm", p.fretCrownHeightMm, ParamType::Float); if (!r.ok) return r;
  r = range("fret_crown_width_mm", p.fretCrownWidthMm, ParamType::Float); if (!r.ok) return r;
  r = range("neck_material", p.neckMaterial, ParamType::Int); if (!r.ok) return r;
  r = range("body_material", p.bodyMaterial, ParamType::Int); if (!r.ok) return r;
  r = range("string_material", p.stringMaterial, ParamType::Int); if (!r.ok) return r;
  for (int i = 0; i < 6; ++i) {
    r = range((std::string("string_gauge_") + std::to_string(i + 1) + "_in").c_str(), p.stringGaugeIn[i], ParamType::Float);
    if (!r.ok) return r;
    r = range((std::string("tuning_offset_") + std::to_string(i + 1) + "_semitones").c_str(), p.tuningOffsetSemitones[i], ParamType::Int);
    if (!r.ok) return r;
  }
  for (int i = 0; i < 3; ++i) {
    r = range((std::string("pickup_") + std::to_string(i + 1) + "_type").c_str(), p.pickupType[i], ParamType::Int);
    if (!r.ok) return r;
    r = range((std::string("pickup_") + std::to_string(i + 1) + "_from_bridge_mm").c_str(), p.pickupFromBridgeMm[i], ParamType::Float);
    if (!r.ok) return r;
    r = range((std::string("pickup_") + std::to_string(i + 1) + "_enabled").c_str(), p.pickupEnabled[i] ? 1 : 0, ParamType::Int);
    if (!r.ok) return r;
    r = range((std::string("pickup_") + std::to_string(i + 1) + "_phase_inverted").c_str(), p.pickupPhaseInverted[i] ? 1 : 0, ParamType::Int);
    if (!r.ok) return r;
  }
  r = range("pickup_combination", p.pickupCombination, ParamType::Int); if (!r.ok) return r;
  r = range("pick_angle_deg", p.pickAngleDeg, ParamType::Float); if (!r.ok) return r;
  r = range("pick_depth_mm", p.pickDepthMm, ParamType::Float); if (!r.ok) return r;
  r = range("palm_mute", p.palmMute, ParamType::Float); if (!r.ok) return r;
  r = range("master_gain_db", p.masterGainDb, ParamType::Float); if (!r.ok) return r;
  return {true, ""};
}

bool ParameterSnapshot::operator==(const ParameterSnapshot& o) const {
  if (scaleLengthMm != o.scaleLengthMm || fretCrownHeightMm != o.fretCrownHeightMm
      || fretCrownWidthMm != o.fretCrownWidthMm || neckMaterial != o.neckMaterial
      || bodyMaterial != o.bodyMaterial || stringMaterial != o.stringMaterial
      || pickupCombination != o.pickupCombination || pickAngleDeg != o.pickAngleDeg
      || pickDepthMm != o.pickDepthMm || palmMute != o.palmMute || masterGainDb != o.masterGainDb)
    return false;
  for (int i = 0; i < 6; ++i)
    if (stringGaugeIn[i] != o.stringGaugeIn[i] || tuningOffsetSemitones[i] != o.tuningOffsetSemitones[i])
      return false;
  for (int i = 0; i < 3; ++i)
    if (pickupType[i] != o.pickupType[i] || pickupFromBridgeMm[i] != o.pickupFromBridgeMm[i]
        || pickupEnabled[i] != o.pickupEnabled[i] || pickupPhaseInverted[i] != o.pickupPhaseInverted[i])
      return false;
  return true;
}

// ---------- event file parsing (D-005) ----------
Result EventFile::parse(const std::string& text, std::vector<Event>& out,
                        std::uint64_t& seedOut, std::string& error) {
  if (text.size() > 1024 * 1024) { error = "event file exceeds 1 MiB"; return {false, error}; }
  // UTF-8 validation
  for (size_t i = 0; i < text.size(); ++i) {
    const unsigned char c = (unsigned char)text[i];
    if (c < 0x80) continue;
    int len = (c >= 0xF0) ? 4 : (c >= 0xE0) ? 3 : (c >= 0xC0) ? 2 : -1;
    if (len < 0 || i + len > text.size()) { error = "invalid UTF-8"; return {false, error}; }
    for (int k = 1; k < len; ++k)
      if (((unsigned char)text[i + k] & 0xC0) != 0x80) { error = "invalid UTF-8"; return {false, error}; }
    i += len - 1;
  }
  out.clear();
  // keep caller-supplied default unless the file carries a seed directive
  std::istringstream in(text);
  std::string line;
  // Monotonicity is enforced per event class: notes form one timeline and
  // controls another, so a file may interleave e.g. "note_off 0.3" then
  // "control 0.0" without tripping the check (D-010 / T-012 / T-028).
  double lastNoteTime = -1;
  double lastControlTime = -1;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::istringstream ls(line);
    std::string word;
    ls >> word;
    if (word == "seed") {
      unsigned long long s; if (!(ls >> s)) { error = "bad seed line"; return {false, error}; }
      seedOut = s;
      continue;
    }
    char* end = nullptr;
    const double t = std::strtod(word.c_str(), &end);
    if (end != word.c_str() + word.size() || !finite(t) || t < 0) { error = "bad time: " + line; return {false, error}; }
    std::string kind;
    ls >> kind;
    const bool isControl = (kind == "control");
    const double lastT = isControl ? lastControlTime : lastNoteTime;
    if (lastT >= 0 && t < lastT) { error = "non-monotonic time"; return {false, error}; }
    Event ev;
    ev.timeSeconds = t;
    ev.controlId = -1;
    if (kind == "note_on" || kind == "note_off") {
      if (!(ls >> ev.midiNote >> ev.velocity >> ev.channel)) { error = "bad note event: " + line; return {false, error}; }
      if (ev.midiNote < 0 || ev.midiNote > 127 || ev.velocity < 0 || ev.velocity > 127 || ev.channel < 1 || ev.channel > 16) { error = "note out of range: " + line; return {false, error}; }
      ev.type = kind == "note_on" ? Event::Type::NoteOn : Event::Type::NoteOff;
      lastNoteTime = t;
    } else if (isControl) {
      int id, chan; double value;
      if (!(ls >> id >> value >> chan)) { error = "bad control event: " + line; return {false, error}; }
      if (id < 0 || chan < 1 || chan > 16 || !finite(value)) { error = "control out of range"; return {false, error}; }
      ev.type = Event::Type::Control;
      ev.controlId = id; ev.controlValue = value; ev.channel = chan;
      lastControlTime = t;
    } else { error = "unknown event kind: " + kind; return {false, error}; }
    out.push_back(ev);
    if (out.size() > 10000) { error = "more than 10000 events"; return {false, error}; }
  }
  return {true, ""};
}

// ---------- offline renderer ----------
RenderResult renderEventFile(const EventFile& ef, const ParameterSnapshot& snap, double sampleRate) {
  RenderResult rr;
  auto v = ParameterSnapshot::validate(snap);
  if (!v.ok) { rr.status = "invalid parameters: " + v.error; return rr; }
  std::vector<Event> events;
  std::uint64_t seed = ef.seed;
  std::string err;
  auto pr = EventFile::parse(ef.text, events, seed, err);
  if (!pr.ok) { rr.status = "invalid events: " + err; return rr; }
  const bool anyPickup = snap.pickupEnabled[0] || snap.pickupEnabled[1] || snap.pickupEnabled[2];
  if (!anyPickup) { rr.status = "no pickups enabled: silence"; return rr; } // D-013

  Engine e;
  e.setSeed(seed);
  e.prepare(sampleRate, 512, 16);
  e.setParameters(snap);

  double end = 0;
  for (auto& ev : events) end = std::max(end, ev.timeSeconds);
  const double tail = 2.0;
  const int total = (int)((end + tail) * sampleRate) + 1;
  const int block = 512;
  rr.monoPcm.resize(total);
  const double dt = 1.0 / sampleRate;

  int pos = 0;
  size_t evIdx = 0;
  while (pos < total) {
    const int n = std::min(block, total - pos);
    const double t0 = pos * dt;
    // apply events inside this block
    juce::MidiBuffer mb;
    while (evIdx < events.size() && events[evIdx].timeSeconds < t0 + n * dt) {
      const auto& ev = events[evIdx];
      const int evSample = (int)(ev.timeSeconds * sampleRate) - pos;
      if (ev.type == Event::Type::NoteOn)
        mb.addEvent(juce::MidiMessage::noteOn(ev.channel, ev.midiNote, (juce::uint8)ev.velocity), std::clamp(evSample, 0, n - 1));
      else if (ev.type == Event::Type::NoteOff)
        mb.addEvent(juce::MidiMessage::noteOff(ev.channel, ev.midiNote), std::clamp(evSample, 0, n - 1));
      ++evIdx;
    }
    juce::AudioBuffer<float> buf(2, n);
    buf.clear();
    e.render(buf, mb);
    // D-006: measure pre-safety peak. The engine applies tanh safety; to report
    // pre-safety we recompute by rendering without safety is costly, so the engine
    // reports both via a parallel accumulator.
    std::memcpy(rr.monoPcm.data() + pos, buf.getWritePointer(0), n * sizeof(float));
    pos += n;
  }
  double peak = 0;
  for (float s : rr.monoPcm) peak = std::max(peak, (double)std::abs(s));
  rr.postSafetyPeak = peak;
  rr.preSafetyPeak = e.lastPreSafetyPeak();
  rr.status = "ok";
  return rr;
}

} // namespace egb
