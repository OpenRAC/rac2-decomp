#!/usr/bin/env python3
"""Carry the global-variable names of the USA v2.00 symbol file over to the USA v1.01 boot.

Functions that are identical in both executables (unique relocation-masked digest) address their globals at the
same instruction positions, so the i-th address a v2.00 function builds corresponds to the i-th address its v1.01
twin builds. Votes over all twins give an address map; a v2.00 data symbol (Promises/RC2-Going-Decompiled, see
CREDITS.md) moves to v1.01 only when every vote for its address agrees. Names and addresses only.

    python scripts/transfer_data_names.py --v2 baserom/SCUS_972.68 --v1 <reference>/boot.elf
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import region as regions  # noqa: E402
import transfer_names as tn  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
MARKER = "# --- data names carried from USA v2.00 by scripts/transfer_data_names.py (generated; every address vote agrees) ---"
GP = 0x1AEFF0
MEM = set(range(0x20, 0x30)) | {0x31, 0x37, 0x39, 0x3F}


def addresses(words: list[int]) -> list[int]:
    """Effective addresses a function builds or dereferences, in instruction order."""
    out, hi = [], {}
    for w in words:
        op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
        simm = imm - 0x10000 if imm & 0x8000 else imm
        if op == 0x0F:
            hi[rt] = imm << 16
        elif op in (9, 13) and (rs in hi or rs == 28):
            value = ((GP if rs == 28 else hi[rs]) + (simm if op == 9 else imm)) & 0xFFFFFFFF
            out.append(value)
            hi[rt] = value
        elif op in MEM and (rs in hi or rs == 28):
            out.append(((GP if rs == 28 else hi[rs]) + simm) & 0xFFFFFFFF)
        elif op not in (4, 5, 1, 2, 3, 6, 7):
            hi.pop(rt, None)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--v2", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--v1", type=Path, required=True)
    args = ap.parse_args()
    f2 = tn.digests(args.v2, regions.load("ntsc-u-v2").target["boot"]["sha256"])
    f1 = tn.digests(args.v1, regions.load("ntsc-u").target["boot"]["sha256"])
    r2, r1 = ue.code_words(args.v2.read_bytes()), ue.code_words(args.v1.read_bytes())
    c1, c2 = Counter(d for _, d in f1.values()), Counter(d for _, d in f2.values())
    twin = {d: a for a, (_, d) in f1.items() if c1[d] == 1}
    votes: dict[int, Counter] = defaultdict(Counter)
    pairs = 0
    for a2, (s2, d) in f2.items():
        if c2[d] != 1 or d not in twin:
            continue
        a1 = twin[d]
        e2, e1 = addresses(ue.slice_words(r2, a2, s2)), addresses(ue.slice_words(r1, a1, f1[a1][0]))
        if len(e2) == len(e1):
            pairs += 1
            for x, y in zip(e2, e1):
                votes[x][y] += 1
    mapping = {x: next(iter(c)) for x, c in votes.items() if len(c) == 1}
    code = [(b, b + len(w) * 4) for b, w in r1.items()]
    target = ROOT / "symbol_addrs/usa/symbol_addrs.txt"
    lines = target.read_text(encoding="utf-8").splitlines()
    if MARKER in lines:
        lines = lines[:lines.index(MARKER)]
    taken_names = {m.group(1) for l in lines if (m := tn.SYM.match(l))}
    taken_addr = {int(m.group(2), 16) for l in lines if (m := tn.SYM.match(l))}
    rows = []
    for line in (ROOT / "symbol_addrs/usa-v2/symbol_addrs.txt").read_text(encoding="utf-8").splitlines():
        m = tn.SYM.match(line)
        if not m or re.match(r"(func|FUN|D)_[0-9A-Fa-f]{8}$", m.group(1)):
            continue
        a2, name = int(m.group(2), 16), m.group(1)
        a1 = mapping.get(a2)
        if a1 is not None and name not in taken_names and a1 not in taken_addr and a2 >= 0x133B80:
            size = re.search(r"size:\s*(0x[0-9A-Fa-f]+|\d+)", m.group(3))
            kind = "type:func" if any(lo <= a1 < hi for lo, hi in code) else "type:data"
            rows.append((a1, name, size.group(1) if size else None, kind, sum(votes[a2].values())))
            taken_names.add(name)
            taken_addr.add(a1)
    out = lines + ["", MARKER] + [f"{n} = 0x{a:08X}; // {k}" + (f" size:{s}" if s else "") + f" votes:{v} - name from v2.00 (Promises)"
                                  for a, n, s, k, v in sorted(rows)]
    target.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"{pairs} twin functions, {len(mapping)} unambiguous addresses, {len(rows)} data names carried")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
