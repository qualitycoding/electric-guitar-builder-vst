# Deviations

- D-1 (S-000): The durable mount rejected JUCE's ~280 MiB packfile ("File too large"), so the pinned JUCE checkout lives at /tmp/JUCE (detached at 91ad83ae34a81e0833b1a2b0866f54846370ae53) and the repo records it as a gitlink submodule (third_party/JUCE) with .gitmodules. Builds pass JUCE dir via CMake; CI fetches the submodule normally.
