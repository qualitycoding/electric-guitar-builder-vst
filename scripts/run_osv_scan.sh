#!/bin/sh
# Genuine dependency vulnerability scan via the OSV API (v1/query), one call
# per pinned package in requirements-lock.txt. Writes reports/osv_scan.json in
# the osv-scanner JSON shape consumed by T-019. No findings are suppressed;
# the report records exactly what the API returned on the scan date.
set -eu
cd "$(dirname "$0")/.."
mkdir -p reports
python3 - <<'PY'
import json, urllib.request, datetime

pkgs = []
for line in open("requirements-lock.txt"):
    line = line.strip()
    if not line or line.startswith("#"):
        continue
    name, ver = line.split("==")
    pkgs.append((name.strip(), ver.strip(), "PyPI"))

results = []
findings = []
for name, ver, eco in pkgs:
    body = json.dumps({"package": {"name": name, "ecosystem": eco}, "version": ver}).encode()
    req = urllib.request.Request("https://api.osv.dev/v1/query", data=body,
                                 headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.load(resp)
    vulns = data.get("vulns", [])
    entry = {"source": {"path": "requirements-lock.txt", "type": "lockfile"},
             "package": {"name": name, "version": ver, "ecosystem": eco},
             "groups": [], "vulns": []}
    for v in vulns:
        sev = [{"type": s.get("type", "CVSS"), "score": s.get("score", "")}
               for s in v.get("severity", [])]
        entry["vulns"].append({"id": v.get("id", ""), "severity": sev})
        findings.append((name, v.get("id")))
    results.append(entry)

report = {
    "results": results,
    "scan_date_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "scanner": "OSV API v1/query per pinned package (scripts/run_osv_scan.sh)",
    "summary": {"total_packages": len(pkgs), "total_vulns": len(findings)},
}
with open("reports/osv_scan.json", "w") as f:
    json.dump(report, f, indent=2)
print(f"scanned {len(pkgs)} packages, {len(findings)} findings")
PY
