#!/bin/sh
# Amendment 03 (D-038): run every frozen test except test_017 (release-build performance
# budget, gates in the release suite) and test_021 (the checker of these logs) under ASan
# and under UBSan. Writes reports/asan_suite.txt and reports/ubsan_suite.txt directly; no
# seeding or second pass. Usage, from the repository root:
#   EGB_ASAN_BIN=<asan egb_contract> EGB_UBSAN_BIN=<ubsan egb_contract> sh scripts/run_sanitizer_suites.sh
set -eu
: "${EGB_ASAN_BIN:?set EGB_ASAN_BIN}"
: "${EGB_UBSAN_BIN:?set EGB_UBSAN_BIN}"
IDS=$(python3 - <<'PY'
import re
ids = []
for mod, cls in (("test_contract", "Contract"), ("test_amendment", "Amendment"), ("test_physics", "Physics")):
    for name in re.findall(r"^    def (test_\d+)\(", open(f"tests/{mod}.py").read(), re.M):
        if name not in ("test_017", "test_021"):
            ids.append(f"tests.{mod}.{cls}.{name}")
print(" ".join(ids))
PY
)
export ASAN_OPTIONS="detect_leaks=1:halt_on_error=0"
export UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=0"
rc=0
EGB_CONTRACT_BIN="$EGB_ASAN_BIN" python3 -m unittest -v $IDS > reports/asan_suite.txt 2>&1 || rc=1
EGB_CONTRACT_BIN="$EGB_UBSAN_BIN" python3 -m unittest -v $IDS > reports/ubsan_suite.txt 2>&1 || rc=1
grep -q "ERROR: AddressSanitizer" reports/asan_suite.txt && rc=1
grep -q "runtime error" reports/ubsan_suite.txt && rc=1
echo "sanitizer suites rc=$rc"
exit $rc
