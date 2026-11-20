// Renders the T-026 candidate set (midi 40/45/64 x velocity 45/85/125, 1.6 s notes, 48 kHz, default parameters)
// as raw float32 mono files <out>/<midi>-<vel>.f32. Usage: render_t026_set <outdir>
#include "egb/Engine.h"
#include <cstdio>
#include <sstream>
#include <string>
int main(int argc, char** argv) {
  if (argc != 2) { std::fprintf(stderr, "usage: render_t026_set <outdir>\n"); return 2; }
  for (int midi : {40, 45, 64}) for (int vel : {45, 85, 125}) {
    std::ostringstream o; o.precision(10);
    o << "0.000000 note_on " << midi << " " << vel << " 1\n" << 1.6 << " note_off " << midi << " 0 1\n";
    egb::EventFile ef; ef.text = o.str(); ef.seed = 20261104;
    auto r = egb::renderEventFile(ef, egb::ParameterSnapshot{}, 48000);
    std::string p = std::string(argv[1]) + "/" + std::to_string(midi) + "-" + std::to_string(vel) + ".f32";
    FILE* f = std::fopen(p.c_str(), "wb"); if (!f) return 1;
    std::fwrite(r.monoPcm.data(), 4, r.monoPcm.size(), f); std::fclose(f);
  }
  return 0;
}
