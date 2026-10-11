#!/usr/bin/env python3
"""Carry a published USA v2.00 segmentation over to USA v1.01 by matching function bodies.

Promises/RC2-Going-Decompiled keeps a splat config for the v2.00 boot with the object/file boundaries it
established (``going-decompiled/config/usa/SCUS_972.68.yaml``). That project is GPL-2.0: only the
boundary addresses are read here, never its code. Each boundary is a function start in v2.00; the same
function (or the same run of up to eight consecutive functions, when one body is not unique) is looked up
in the v1.01 boot by a relocation-masked digest (``unique_estimate.digest``). Only unambiguous matches are
written, as ``<v1.01 address> <name>`` rows for ``config/segments/ntsc-u-boot.tsv``.

    python scripts/map_segments.py --yaml <SCUS_972.68.yaml> --v2 baserom/SCUS_972.68 --v1 <reference>/boot.elf
"""
from __future__ import annotations

import argparse
import hashlib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import region as regions  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
ROW = re.compile(r"^\s*-\s*\[\s*0x([0-9A-Fa-f]+)\s*,\s*(\w+)\s*,\s*([^\],]+?)\s*(?:,\s*([^\]]+?))?\s*\]")
CODE_KINDS = {"c", "cpp", "asm", "hasm", "lib"}
MAX_RUN = 8
DELTA = 0x100080  # file offset -> virtual address in the v2.00 boot


def boundaries(yaml: Path) -> list[tuple[int, str, str]]:
    """(v2 virtual address, kind, name) for every code subsegment of the cod/text segments."""
    rows, segment = [], None
    for line in yaml.read_text(encoding="utf-8").splitlines():
        m = re.match(r"^\s*-\s*name:\s*(\S+)", line)
        if m and not line.startswith("      "):
            segment = m.group(1)
        row = ROW.match(line)
        if row and segment in ("cod", "text") and row.group(2) in CODE_KINDS:
            name = (row.group(4) or row.group(3)).split("/")[-1]
            rows.append((int(row.group(1), 16) + DELTA, row.group(2), name))
    return rows


def functions(path: Path, verify: str | None) -> tuple[list[tuple[int, int, str]], dict[int, list[int]]]:
    data = path.read_bytes()
    if verify and hashlib.sha256(data).hexdigest() != verify:
        raise SystemExit(f"{path} is not the pinned boot executable")
    ranges = ue.code_words(data)
    return [(a, s, ue.digest(ue.slice_words(ranges, a, s))) for a, s in ue.extents(ranges)], ranges


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--yaml", type=Path, required=True)
    ap.add_argument("--v2", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--v1", type=Path, required=True)
    ap.add_argument("--output", type=Path, default=ROOT / "config/segments/ntsc-u-boot.tsv")
    args = ap.parse_args()
    f2, _ = functions(args.v2, regions.load("ntsc-u-v2").target["boot"]["sha256"])
    f1, _ = functions(args.v1, regions.load("ntsc-u").target["boot"]["sha256"])
    index2 = {a: i for i, (a, _, _) in enumerate(f2)}
    runs: dict[tuple[str, ...], list[int]] = {}
    for n in range(1, MAX_RUN + 1):
        for i in range(len(f1) - n + 1):
            runs.setdefault(tuple(d for _, _, d in f1[i:i + n]), []).append(f1[i][0])
    out, skipped = [], []
    for vaddr, kind, name in boundaries(args.yaml):
        i = index2.get(vaddr)
        if i is None:  # an object often starts on padding: snap to the first function within 0x20 bytes after it
            nxt = next((k for k, (a, _, _) in enumerate(f2) if vaddr < a <= vaddr + 0x20), None)
            if nxt is None:
                skipped.append((vaddr, "not a function start in v2.00"))
                continue
            i = nxt
        for n in range(1, MAX_RUN + 1):
            key = tuple(d for _, _, d in f2[i:i + n])
            if len(key) < n:
                break
            hits = runs.get(key, [])
            if len(hits) == 1:
                out.append((hits[0], kind, name, vaddr, n))
                break
        else:
            skipped.append((vaddr, "no unique v1.01 match"))
    lines = [line for line in args.output.read_text(encoding="utf-8").splitlines() if line.startswith("#") or not line.strip()]
    lines = [line for line in lines if not line.startswith("# mapped:")]
    lines.append("# mapped: rows below come from scripts/map_segments.py (boundaries of Promises/RC2-Going-Decompiled's v2.00 split,")
    lines.append("# matched by relocation-masked function digest; columns: v1.01 start, name, kind, v2.00 start, functions used to match).")
    seen = set()
    for address, kind, name, vaddr, n in sorted(out):
        if address in seen:
            continue
        seen.add(address)
        unit = f"lib_{name}" if kind == "lib" else f"{address:08X}"
        lines.append(f"0x{address:08X} {unit} {kind} 0x{vaddr:08X} {n}")
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"mapped {len(seen)} of {len(out) + len(skipped)} boundaries; skipped {len(skipped)}")
    for vaddr, why in skipped:
        print(f"  skipped 0x{vaddr:08X}: {why}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
