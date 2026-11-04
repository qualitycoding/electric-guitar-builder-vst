#!/bin/sh
# Run the full 30-case contract suite under ASan and under UBSan, capturing
# logs for T-021. Serial execution: two instrumented suites at once would
# thrash the 2-core runner.
cd /mnt/agents/work/electric-guitar-builder-vst || exit 1
export ASAN_OPTIONS="detect_leaks=1:halt_on_error=0"
export UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=0"
EGB_CONTRACT_BIN=/var/tmp/egb-asan/egb_contract python3 -m unittest discover -s tests -v > reports/asan_suite.txt 2>&1
echo "asan done rc=$?" >> reports/asan_suite.txt
EGB_CONTRACT_BIN=/var/tmp/egb-ubsan/egb_contract python3 -m unittest discover -s tests -v > reports/ubsan_suite.txt 2>&1
echo "ubsan done rc=$?" >> reports/ubsan_suite.txt
echo SANITIZER_SUITES_DONE
