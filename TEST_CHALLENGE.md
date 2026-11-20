# TEST_CHALLENGE — T-021 requires "Ran 30 tests" in the sanitizer logs

Raised by the implementing agent at S-106 (2026-11-20T03:49:50Z). No hashed file was edited.

**Test:** T-021 (`src/contract_main.cpp` lines 1156-1164, hashed). `suiteClean` requires the ASan and UBSan logs (`reports/asan_suite.txt`, `reports/ubsan_suite.txt`) to contain the literal `Ran 30 tests`, no `FAILED` and no sanitizer finding.

**Conflict:** the amended suite runs 48 tests (D-030, D-037), so a genuine unittest log says `Ran 48 tests`. T-021 cannot pass on a truthful sanitizer log. S-106 requires the ASan and UBSan suites to pass. The committed v1 logs (30 tests, from 61ab5ed) still satisfy T-021 only because they are stale; they do not exercise amendment 03 code.

**Evidence (genuine runs on b60f1e0-based tree 25d7fbd, committed as `reports/a03_asan_suite.txt` and `reports/a03_ubsan_suite.txt`):**
- ASan: 48 tests, 0 `ERROR: AddressSanitizer`, 0 leak reports; only T-021 fails (the literal above, and it reads the log while it is being written). T-017 passed under ASan (232 s total).
- UBSan: 0 `runtime error` lines; failures are T-021 (same literal) and T-017 (frozen 120 s harness timeout under instrumentation; Release+UBSan measures 64.5 s/run against the 48 s budget; D-15 already records this as an instrumentation cost, with T-017 green in the release build at 17.1 s median).

**Options:** (a) amend T-021's literal to the amended test count (48), re-hash, and re-run the v1 two-pass bootstrap (`scripts/bootstrap_sanitizer_logs.sh`) to regenerate the committed logs; (b) make `suiteClean` accept any `Ran N tests` with a trailing `OK`. Both change a hashed file, so they need the planner.

**State:** S-102..S-105 complete; S-101 partial (CI probe needs a scratch-branch push); S-106 blocked on this plus CI runs, which need pushes to other branches.
