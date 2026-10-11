#!/usr/bin/env python3
"""Heuristic deduplicated size estimate for the accepted USA v1.01 target, as a decomp.dev report.

The loaded-byte total (boot plus 27 overlays, about 48.8 MB) counts engine code once per overlay. This
tool estimates how much of that is distinct. It is an ESTIMATE, not a progress denominator: functions
are grouped by a digest of their words with relocatable fields masked by a register-tracking heuristic
(``jal``/``j`` targets, ``lui`` immediates, ``addiu``/``ori`` immediates and load/store offsets fed by a
``lui`` or ``$gp``). Functions that differ only in non-address constants stay distinct; address-like
fields never do. Boundaries are the heuristic discovery of ``function_size_rank.py``.

Credit is conservative and comes only from already accepted proofs: a distinct body counts as matched
only when a function recorded as matched in ``progress/candidates.json`` or ``progress/levels/`` has the
same digest over exactly the same extent. Nothing here adds or changes matching credit.

``catalog`` (private input: the reference ``setup.py`` prepared) writes digests of structure only to
``config/estimates/ntsc-u.json``; ``report`` (CI-safe) turns it into an objdiff report v2.

    python scripts/unique_estimate.py catalog --reference <runtime>/runs/<run>/reference --elf baserom/SCUS_972.68
    python scripts/unique_estimate.py report --output build/decomp/unique-estimate-report.json
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
import region as regions  # noqa: E402

REGION = "ntsc-u"
ESTIMATE = ROOT / "config/estimates/ntsc-u.json"
LUI = 0x0F
ADDR_ALU = {0x08, 0x09, 0x0D, 0x19}  # addi addiu ori daddiu: propagate an address register
OTHER_ALU = {0x0A, 0x0B, 0x0C, 0x0E, 0x18}
MEM = set(range(0x20, 0x30)) | {0x1A, 0x1B, 0x1E, 0x1F, 0x31, 0x36, 0x37, 0x39, 0x3E, 0x3F}
LOADS = set(range(0x20, 0x28)) | {0x1A, 0x1B, 0x1E, 0x37}
GP = 28


def normalise(words: list[int]) -> list[int]:
    """Mask relocatable fields; keep every other word exact."""
    tracked: set[int] = set()
    out = []
    for w in words:
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op in (2, 3):
            w = op << 26
        elif op == LUI:
            tracked.add(rt)
            w &= 0xFFFF0000
        elif op in ADDR_ALU:
            if rs in tracked or rs == GP:
                tracked.add(rt)
                w &= 0xFFFF0000
            else:
                tracked.discard(rt)
        elif op in OTHER_ALU:
            tracked.discard(rt)
        elif op in MEM:
            if rs in tracked or rs == GP:
                w &= 0xFFFF0000
            if op in LOADS:
                tracked.discard(rt)
        elif op == 0:
            tracked.discard((w >> 11) & 31)
        out.append(w)
    return out


def digest(words: list[int]) -> str:
    return hashlib.sha1(struct.pack(f"<{len(words)}I", *normalise(words))).hexdigest()


def code_words(elf: bytes) -> dict[int, list[int]]:
    return {base: words for base, words in rank.load_code_ranges(elf)}


def slice_words(ranges: dict[int, list[int]], address: int, size: int) -> list[int] | None:
    for base, words in ranges.items():
        if base <= address and address + size <= base + len(words) * 4:
            i = (address - base) // 4
            return words[i:i + size // 4]
    return None


def extents(ranges: dict[int, list[int]]) -> list[tuple[int, int]]:
    """Function extents of one image (heuristic discovery, clipped so they never overlap)."""
    rows = []
    for base, words in ranges.items():
        end = base + len(words) * 4
        starts = [s for s in rank.discover_starts([(base, words)], {}) if base <= s < end]
        for i, start in enumerate(starts):
            nxt = starts[i + 1] if i + 1 < len(starts) else end
            size = rank.trim_size(words, base, start, nxt)
            if size >= 8:
                rows.append((start, min(size, nxt - start)))
    return rows


def accepted(level: str | None) -> list[tuple[int, int]]:
    """(address, size) of functions an accepted proof records as matched for the boot or one level."""
    if level is None:
        data = json.loads((ROOT / "progress/candidates.json").read_text(encoding="utf-8"))
        return [(f["address"], f["size"]) for f in data["functions"] if f.get("matched")]
    data = json.loads((ROOT / f"progress/levels/{level}.json").read_text(encoding="utf-8"))
    return [(f["address"], f["size"]) for f in data["functions"] if f.get("matched") and f.get("integrated")]


def build_catalog(reference: Path, elf: Path) -> dict:
    region = regions.load(REGION)
    boot_bytes = elf.read_bytes()
    if hashlib.sha256(boot_bytes).hexdigest() != region.target["boot"]["sha256"]:
        raise SystemExit("ELF is not the pinned USA v1.01 boot executable")
    images = [("boot", code_words(boot_bytes), accepted(None))]
    for row in region.overlays["levels"]:
        path = reference / "levels" / row["level"] / "overlay.elf"
        images.append((row["level"], code_words(path.read_bytes()), accepted(row["level"])))
    credited: set[str] = set()
    for _, ranges, proofs in images:
        for address, size in proofs:
            words = slice_words(ranges, address, size)
            if words is not None:
                credited.add(digest(words))
    seen: dict[str, int] = {}
    units, physical = [], {}
    for name, ranges, _ in images:
        total = new = new_credit = 0
        for address, size in extents(ranges):
            words = slice_words(ranges, address, size)
            d = digest(words)
            total += size
            if d not in seen:
                seen[d] = size
                new += size
                if d in credited:
                    new_credit += size
                units.append([name, address, size, int(d in credited)])
        physical[name] = {"physical_code_bytes": total, "new_distinct_bytes": new, "new_credited_bytes": new_credit}
    return {"schema": 1, "target": region.serial, "version": "1.01", "heuristic": True,
            "boot_sha256": region.target["boot"]["sha256"],
            "overlay_sha256": {r["level"]: r["sha256"] for r in region.overlays["levels"]},
            "images": physical,
            "distinct_functions": [u for u in units if u[0] == "boot"],
            "note": "Estimate only. Distinct bodies are counted once by a relocation-masking heuristic; credited "
                    "bytes come solely from accepted proofs of identical digest and extent."}


def measures(code: int, matched: int, units: int, complete_units: int) -> dict:
    pct = matched / code * 100 if code else 0
    return {"totalCode": str(code), "matchedCode": str(matched), "matchedCodePercent": pct, "totalData": "0",
            "matchedData": "0", "matchedDataPercent": 0, "completeCode": str(matched), "completeCodePercent": pct,
            "completeData": "0", "completeDataPercent": 0, "fuzzyMatchPercent": pct, "totalUnits": units,
            "completeUnits": complete_units}


def build_report(catalog: dict) -> dict:
    units, cats = [], []
    for name, row in catalog["images"].items():
        size, done = row["new_distinct_bytes"], row["new_credited_bytes"]
        group = "boot" if name == "boot" else "levels"
        units.append({"name": f"{group}/{name}/distinct-code", "measures": measures(size, done, 1, int(size == done and size > 0)),
                      "sections": [{"name": ".text", "size": str(size), "fuzzyMatchPercent": done / size * 100 if size else 0}],
                      "metadata": {"complete": size > 0 and size == done, "autoGenerated": True,
                                   "moduleName": name, "progressCategories": [group]}})
    for cid, title in (("boot", "Boot ELF"), ("levels", "Level overlays (distinct code only)")):
        sub = [u for u in units if cid in u["metadata"]["progressCategories"]]
        cats.append({"id": cid, "name": title, "measures": measures(
            sum(int(u["measures"]["totalCode"]) for u in sub), sum(int(u["measures"]["matchedCode"]) for u in sub),
            len(sub), sum(u["measures"]["completeUnits"] for u in sub))})
    total = sum(int(u["measures"]["totalCode"]) for u in units)
    done = sum(int(u["measures"]["matchedCode"]) for u in units)
    return {"version": 2, "measures": measures(total, done, len(units), sum(u["measures"]["completeUnits"] for u in units)),
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
        ESTIMATE.parent.mkdir(parents=True, exist_ok=True)
        ESTIMATE.write_text(json.dumps(build_catalog(args.reference, args.elf), separators=(",", ":")) + "\n", encoding="utf-8")
        print(f"wrote {ESTIMATE.relative_to(ROOT)}")
        return 0
    report = build_report(json.loads(ESTIMATE.read_text(encoding="utf-8")))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report) + "\n", encoding="utf-8")
    m = report["measures"]
    print(f"{m['matchedCode']} / {m['totalCode']} distinct code bytes ({m['matchedCodePercent']:.4f}%) [heuristic estimate]")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
