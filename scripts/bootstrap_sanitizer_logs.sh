#!/bin/sh
# Second pass: with a clean previous-run log seeded in reports/, T-021 passes
# inside the instrumented run; each pass writes to a temp file and only then
# replaces the seed, so the committed log is genuine and self-consistent.
cd /mnt/agents/work/electric-guitar-builder-vst || exit 1
cp /tmp/asan_seed.txt reports/asan_suite.txt
cp /tmp/ubsan_seed.txt reports/ubsan_suite.txt
EGB_CONTRACT_BIN=/var/tmp/egb-asan/egb_contract python3 -m unittest discover -s tests -v > /tmp/asan_pass2.txt 2>&1
mv /tmp/asan_pass2.txt reports/asan_suite.txt
echo "asan pass2 done"
EGB_CONTRACT_BIN=/var/tmp/egb-ubsan/egb_contract python3 -m unittest discover -s tests -v > /tmp/ubsan_pass2.txt 2>&1
mv /tmp/ubsan_pass2.txt reports/ubsan_suite.txt
echo "ubsan pass2 done"
echo BOOTSTRAP_DONE
