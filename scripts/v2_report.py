#!/usr/bin/env python3
"""Catalogue and decomp.dev report for USA v2.00.

``catalog`` (private input) reads your prepared reference and writes only structure to
``config/regions/ntsc-u-v2/catalog.json``: boot function addresses, sizes and names, boot section sizes
and, per level overlay, how much code is *new* after de-duplicating relocated copies of engine code
(``measure_unique.py`` method). No bytes are stored.

``report`` (CI-safe) turns the catalogue plus ``progress/v2/matches.json`` into an objdiff report v2
for decomp.dev. Totals are a heuristic de-duplication estimate (relocation fields and immediates normalised), not 27
copies of the engine and not the official progress denominator. Records in ``matches.json`` are
exploratory candidates: they are validated against the catalogue but add no matched code.

    python scripts/v2_report.py catalog --reference <runtime>/runs/<run>/reference --elf baserom/SCUS_972.68
    python scripts/v2_report.py report --output build/decomp/report.json
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import measure_unique  # noqa: E402
import region as regions  # noqa: E402

CATALOG = ROOT / "config/regions/ntsc-u-v2/catalog.json"
MATCHES = ROOT / "progress/v2/matches.json"
REGION = "ntsc-u-v2"


def measures(code: int, data: int, units: int, complete_code: int = 0, complete_units: int = 0) -> dict:
    pct = complete_code / code * 100 if code else 0
    fuzzy = complete_code / (code + data) * 100 if code + data else 0
    return {"totalCode": str(code), "matchedCode": str(complete_code), "matchedCodePercent": pct,
            "totalData": str(data), "matchedData": "0", "matchedDataPercent": 0,
            "completeCode": str(complete_code), "completeCodePercent": pct, "completeData": "0",
            "completeDataPercent": 0, "fuzzyMatchPercent": fuzzy, "totalUnits": units,
            "completeUnits": complete_units}


def build_catalog(reference: Path, elf: Path) -> dict:
    region = regions.load(REGION)
    data = elf.read_bytes()
    if hashlib.sha256(data).hexdigest() != region.target["boot"]["sha256"]:
        raise SystemExit("ELF is not the pinned USA v2.00 boot executable")
    entry = regions.registry()["regions"][REGION]
    symbols = rank.read_symbols(ROOT / entry["symbols"])
    functions = [[f.address, f.size, f.name] for f in sorted(rank.build(elf, REGION))]
    for row, nxt in zip(functions, functions[1:]):  # extents never overlap: clip at the next start
        row[1] = min(row[1], nxt[0] - row[0])
    boot = measure_unique.sections(reference / "boot.elf")
    code_names = {"core.text", ".text"}
    sections = {name: len(blob) for name, blob in boot.items()
                if name not in code_names and not name.startswith(".DVP") and blob and name not in ("", ".shstrtab")}
    seen: dict[bytes, int] = {}
    for name in code_names:
        for size, digest in measure_unique.bodies(boot[name]):
            seen.setdefault(digest, size)
    levels = {}
    for path in sorted((reference / "levels").glob("*/overlay.elf")):
        total = new = 0
        for size, digest in measure_unique.bodies(measure_unique.sections(path)[".text"]):
            total += size
            if digest not in seen:
                seen[digest] = size
                new += size
        levels[path.parent.name] = {"text_bytes": total, "new_unique_bytes": new}
    return {"schema": 1, "target": region.serial, "version": "2.00", "boot_sha256": region.target["boot"]["sha256"],
            "overlay_sha256": {row["level"]: row["sha256"] for row in region.overlays["levels"]},
            "functions": functions, "boot_data_sections": sections, "levels": levels,
            "note": "Structure only. Level code is counted once: bodies already present in the boot or an earlier "
                    "overlay (relocation fields masked) are not counted again."}


def build_report(catalog: dict, matches: list[dict]) -> dict:
    matched = {m["address"]: m for m in matches}
    sized = {f[0]: f[1] for f in catalog["functions"]}
    for address, match in matched.items():
        if sized.get(address) != match["size"]:
            raise SystemExit(f"match {match['symbol']} does not agree with the catalogue extent at 0x{address:X}")
        src = ROOT / match["source"]
        if hashlib.sha256(src.read_bytes()).hexdigest() != match["source_sha256"]:
            raise SystemExit(f"source of {match['symbol']} changed since it was recorded")
    units, code_boot, data_boot = [], 0, 0
    for address, size, name in catalog["functions"]:
        hit = address in matched
        units.append({"name": f"boot/{name}@{address:08X}",
                      "measures": measures(size, 0, 1),
                      "sections": [{"name": ".text", "size": str(size), "fuzzyMatchPercent": 0,
                                    "metadata": {"virtualAddress": str(address)}}],
                      "functions": [{"name": name, "size": str(size), "fuzzyMatchPercent": 0,
                                     "metadata": {"virtualAddress": str(address)}}],
                      "metadata": {"complete": False, "autoGenerated": True, "moduleName": "boot",
                                   "progressCategories": ["boot"]}})
        code_boot += size
    for section, size in sorted(catalog["boot_data_sections"].items()):
        units.append({"name": f"boot/{section}", "measures": measures(0, size, 1),
                      "sections": [{"name": section, "size": str(size), "fuzzyMatchPercent": 0}],
                      "metadata": {"complete": False, "autoGenerated": True, "moduleName": "boot",
                                   "progressCategories": ["boot"]}})
        data_boot += size
    code_levels = 0
    for level, row in catalog["levels"].items():
        size = row["new_unique_bytes"]
        units.append({"name": f"levels/{level}/unique-code", "measures": measures(size, 0, 1),
                      "sections": [{"name": ".text", "size": str(size), "fuzzyMatchPercent": 0}],
                      "metadata": {"complete": False, "autoGenerated": True, "moduleName": f"levels/{level}",
                                   "progressCategories": ["levels"]}})
        code_levels += size
    cats = []
    for cid, title in (("boot", "Boot ELF"), ("levels", "Level overlays (unique code)")):
        sub = [u for u in units if cid in u["metadata"]["progressCategories"]]
        cats.append({"id": cid, "name": title, "measures": measures(
            sum(int(u["measures"]["totalCode"]) for u in sub), sum(int(u["measures"]["totalData"]) for u in sub),
            len(sub), sum(int(u["measures"]["completeCode"]) for u in sub),
            sum(u["measures"]["completeUnits"] for u in sub))})
    return {"version": 2, "measures": measures(code_boot + code_levels, data_boot, len(units)),
            "units": units, "categories": cats}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("catalog")
    c.add_argument("--reference", type=Path, required=True)
    c.add_argument("--elf", type=Path, default=rank.DEFAULT_ELF)
    r = sub.add_parser("report")
    r.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.cmd == "catalog":
        CATALOG.write_text(json.dumps(build_catalog(args.reference, args.elf), separators=(",", ":")) + "\n",
                           encoding="utf-8")
        print(f"wrote {CATALOG.relative_to(ROOT)}")
        return 0
    catalog = json.loads(CATALOG.read_text(encoding="utf-8"))
    matches = json.loads(MATCHES.read_text(encoding="utf-8"))["matches"] if MATCHES.exists() else []
    report = build_report(catalog, matches)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report) + "\n", encoding="utf-8")
    m = report["measures"]
    print(f"{m['totalCode']} estimated unique code bytes, {m['totalUnits']} units; matched credit 0 by design; "
          f"{len(matches)} exploratory candidates ({sum(c['size'] for c in matches)} bytes, not credited)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
