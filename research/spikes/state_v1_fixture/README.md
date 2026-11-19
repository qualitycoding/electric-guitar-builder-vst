Generated during planning (amendment 03) against the v1 engine sources at 61ab5ed:

    c++ -std=c++20 -O1 -Iinclude -I<JUCE>/modules -include <build>/egb_AppConfig.h \
      research/spikes/state_v1_fixture/make_state_v1.cpp <build>/libegb_core.a <build>/libegb_juce.a -lpthread -ldl -lrt \
      -o /tmp/make_state_v1 && /tmp/make_state_v1 tests/physics/state_v1.xml

Output: `tests/physics/state_v1.xml` (frozen fixture for T-050). sha256 recorded in tests/FROZEN_MANIFEST.sha256.
