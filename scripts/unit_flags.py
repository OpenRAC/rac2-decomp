#!/usr/bin/env python3
"""Per-unit compiler flags of the USA v2.00 split, mapped to the USA v1.01 boot.

Promises/RC2-Going-Decompiled (permission record: PR #74) measured, per translation unit, which ``-G`` value and extra
``cc1`` flags reproduce the retail bytes, and the address below which code comes from the SDK compiler (16-byte ``sq``
register saves) and above which from the engine compiler (8-byte ``sd`` saves). Only those facts are read from
``tools/ee/objdiff_build.sh``; no code is copied. Each unit start is mapped to v1.01 through the boundary rows written by
``map_segments.py`` (column 4 is the v2.00 start), and the engine boundary through the digest of the function that starts it.

    python scripts/unit_flags.py --script <objdiff_build.sh> --v2 baserom/SCUS_972.68 --v1 <reference>/boot.elf
"""
from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import map_segments as ms  # noqa: E402
import region as regions  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
CASE = re.compile(r'^\s*usa/(?:cod|text)/([0-9A-Fa-f]+)\)\s*GFLAG="(-G\d+)";(?:\s*CC1EXTRA="([^"]*)";)?')
BOUNDARY = re.compile(r"^ENGINE_BOUNDARY=(0x[0-9A-Fa-f]+)", re.M)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--script", type=Path, required=True)
    ap.add_argument("--v2", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--v1", type=Path, required=True)
    ap.add_argument("--output", type=Path, default=ROOT / "config/segments/ntsc-u-unit-flags.tsv")
    args = ap.parse_args()
    text = args.script.read_text(encoding="utf-8")
    segments = ROOT / "config/segments/ntsc-u-boot.tsv"
    by_v2 = {}
    for line in segments.read_text(encoding="utf-8").splitlines():
        cols = line.split()
        if cols and not line.startswith("#") and len(cols) >= 5 and cols[2] in ms.CODE_KINDS:
            by_v2[int(cols[3], 16)] = int(cols[0], 16)
    rows, missing = [], []
    for line in text.splitlines():
        m = CASE.match(line)
        if m:
            offset = int(m.group(1), 16)
            v2 = offset + ms.DELTA
            v1 = by_v2.get(v2) or by_v2.get(next((a for a in by_v2 if v2 <= a <= v2 + 0x20), -1))
            (rows if v1 else missing).append((v1, v2, m.group(1).upper(), m.group(2), (m.group(3) or "").strip()))
    f2, _ = ms.functions(args.v2, regions.load("ntsc-u-v2").target["boot"]["sha256"])
    f1, _ = ms.functions(args.v1, regions.load("ntsc-u").target["boot"]["sha256"])
    boundary = int(BOUNDARY.search(text).group(1), 16)
    index = {a: i for i, (a, _, _) in enumerate(f2)}
    runs: dict[tuple[str, ...], list[int]] = {}
    for n in range(1, ms.MAX_RUN + 1):
        for i in range(len(f1) - n + 1):
            runs.setdefault(tuple(d for _, _, d in f1[i:i + n]), []).append(f1[i][0])
    engine_v1 = None
    for n in range(1, ms.MAX_RUN + 1):
        key = tuple(d for _, _, d in f2[index[boundary]:index[boundary] + n]) if boundary in index else ()
        if key and len(runs.get(key, [])) == 1:
            engine_v1 = runs[key][0]
            break
    lines = ["# Per-unit compiler flags measured on the USA v2.00 split (Promises/RC2-Going-Decompiled; permission: PR #74), mapped to v1.01.",
             "# Default for every other unit: -G0 and no extra flags. Columns: v1.01 start, v2.00 start, v2.00 unit offset, -G, extra cc1 flags.",
             f"# Compiler arm boundary: code below it comes from the SDK compiler (16-byte sq saves), at and above it from the engine compiler (8-byte sd saves): "
             f"v2.00 0x{boundary:08X}" + (f", v1.01 0x{engine_v1:08X}" if engine_v1 else ", v1.01 not matched")]
    lines += [f"0x{v1:08X}\t0x{v2:08X}\t{unit}\t{g}\t{extra}" for v1, v2, unit, g, extra in sorted(rows)]
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"{len(rows)} units mapped, {len(missing)} without a v1.01 start; engine boundary v1.01: "
          f"{'0x%08X' % engine_v1 if engine_v1 else 'unmatched'}")
    for _, v2, unit, *_ in missing:
        print(f"  unmapped unit {unit} (v2.00 0x{v2:08X})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
