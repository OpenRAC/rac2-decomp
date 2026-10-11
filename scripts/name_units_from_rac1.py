#!/usr/bin/env python3
"""Name USA v1.01 boot units after the rac1-decomp source files whose functions they contain.

Going Commando's engine descends from Ratchet & Clank. rac1-decomp's published ``progress/report.json``
lists, per source file (``core/<name>``, ``game/<name>``), the function addresses and sizes of the PAL
boot. With your own copy of that boot executable (``SCES_509.16``) each function is digested with the
relocation-masking heuristic of ``unique_estimate.py`` and looked up in the v1.01 boot. Only digests that
are unique on both sides count. A file gives a row ``<v1.01 start> <file name>`` when its FIRST function is
matched and at least ``--min-functions`` of its functions match in the same order; the name is then the
rac1 file name. Nothing from either executable is stored.

    python scripts/name_units_from_rac1.py --rac1-elf <SCES_509.16> --rac1-report <rac1-decomp/progress/report.json> \
        --v1 <reference>/boot.elf
"""
from __future__ import annotations

import argparse
import hashlib
import json
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import region as regions  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
RAC1_SHA1 = "79956931bd62fafd8d20fa2eae796dbaf2e15e83"


def unique_digests(rows: list[tuple[int, int, str]]) -> dict[str, int]:
    counts = Counter(d for _, _, d in rows)
    return {d: a for a, _, d in rows if counts[d] == 1}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rac1-elf", type=Path, required=True)
    ap.add_argument("--rac1-report", type=Path, required=True)
    ap.add_argument("--v1", type=Path, required=True)
    ap.add_argument("--min-functions", type=int, default=2)
    ap.add_argument("--output", type=Path, default=ROOT / "config/segments/ntsc-u-boot.tsv")
    args = ap.parse_args()
    rac1 = args.rac1_elf.read_bytes()
    if hashlib.sha1(rac1).hexdigest() != RAC1_SHA1:
        raise SystemExit("not the pinned rac1 PAL boot executable (SCES_509.16)")
    v1 = args.v1.read_bytes()
    if hashlib.sha256(v1).hexdigest() != regions.load("ntsc-u").target["boot"]["sha256"]:
        raise SystemExit("not the pinned USA v1.01 boot executable")
    r1_ranges, v1_ranges = ue.code_words(rac1), ue.code_words(v1)
    v1_rows = [(a, s, ue.digest(ue.slice_words(v1_ranges, a, s))) for a, s in ue.extents(v1_ranges)]
    v1_unique = unique_digests(v1_rows)
    report = json.loads(args.rac1_report.read_text(encoding="utf-8"))
    rac1_unique: dict[str, int] = {}
    files: dict[str, list[tuple[int, str]]] = {}
    seen = Counter()
    for unit in report["units"]:
        group, _, name = unit["name"].partition("/")
        if group not in ("core", "game") or name.startswith("0"):  # address-named objects have no source name
            continue
        for fn in unit["functions"]:
            address, size = int(fn["metadata"]["virtual_address"]), int(fn["size"])
            words = ue.slice_words(r1_ranges, address, size)
            if words is None or size < 8:
                continue
            d = ue.digest(words)
            seen[d] += 1
            files.setdefault(name, []).append((address, d))
    rows, stats, pairs = [], [], []
    for name, funcs in sorted(files.items()):
        hits = [(i, v1_unique[d]) for i, (_, d) in enumerate(funcs) if seen[d] == 1 and d in v1_unique]
        ordered = all(b[1] > a[1] for a, b in zip(hits, hits[1:]))
        first = bool(hits) and hits[0][0] == 0
        pairs += [(v1a, name, funcs[i][0]) for i, v1a in hits]
        stats.append((name, len(funcs), len(hits), ordered, first))
        if first and ordered and len(hits) >= args.min_functions:
            rows.append((hits[0][1], name.replace("/", "_"), len(hits), len(funcs)))
    lines = [l for l in args.output.read_text(encoding="utf-8").splitlines()
             if not l.startswith("# named:") and not (l.split() and l.split()[2:3] == ["rac1"])]
    lines.append("# named: rows below come from scripts/name_units_from_rac1.py (rac1-decomp source file whose first function and at least")
    lines.append("# two more match in order; columns: v1.01 start, file name, rac1, matched functions, functions in the rac1 file).")
    taken = {int(l.split()[0], 0) for l in lines if l.split() and not l.startswith("#")}
    for address, name, n, total in sorted(rows):
        if address in taken:
            lines = [l for l in lines if not (l.split() and not l.startswith("#") and int(l.split()[0], 0) == address)]
        lines.append(f"0x{address:08X} {name} rac1 {n} {total}")
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    ref = args.output.with_name("ntsc-u-rac1-matches.tsv")
    ref.write_text("# v1.01 address, rac1-decomp source file, PAL address in that file's function (addresses only).\n"
                   "# Generated by scripts/name_units_from_rac1.py; both digests unique, relocation-masked.\n"
                   + "".join(f"0x{a:08X}\t{n}\t0x{r:08X}\n" for a, n, r in sorted(pairs)), encoding="utf-8")
    print(f"{len(files)} rac1 files; {sum(1 for s in stats if s[2])} with any match; named {len(rows)}")
    for name, total, hit, ordered, first in stats:
        if hit:
            print(f"  {name:<14} {hit:>3}/{total:<3} ordered={ordered} first={first}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
