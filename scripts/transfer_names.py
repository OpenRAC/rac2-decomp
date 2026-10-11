#!/usr/bin/env python3
"""Carry the function names of the USA v2.00 symbol file over to the USA v1.01 boot.

``symbol_addrs/usa-v2/symbol_addrs.txt`` holds the names Promises/RC2-Going-Decompiled established for v2.00.
A name moves to v1.01 only when its function (v2.00 address) and exactly one function of the v1.01 boot have
the same relocation-masked digest (``unique_estimate.digest``) and the digest is unique on both sides. The rows
are appended to ``symbol_addrs/usa/symbol_addrs.txt`` below a generated marker; placeholder ``func_`` rows at the
same address are replaced. Nothing but names and addresses is written.

    python scripts/transfer_names.py --v2 baserom/SCUS_972.68 --v1 <reference>/boot.elf
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
MARKER = "# --- names carried from USA v2.00 and SDK libraries by scripts/transfer_names.py (generated; digest-matched, unique on both sides) ---"
SYM = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")


def without_generated_block(lines, marker):
    """Remove this tool's block while retaining other generated sections."""
    if marker not in lines:
        return list(lines)
    start = lines.index(marker)
    end = next((i for i in range(start + 1, len(lines))
                if lines[i].startswith("# --- ")), len(lines))
    return lines[:start] + lines[end:]


def digests(path: Path, pinned: str) -> dict[int, tuple[int, str]]:
    data = path.read_bytes()
    if hashlib.sha256(data).hexdigest() != pinned:
        raise SystemExit(f"{path} is not the pinned boot executable")
    ranges = ue.code_words(data)
    return {a: (s, ue.digest(ue.slice_words(ranges, a, s))) for a, s in ue.extents(ranges)}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--v2", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--v1", type=Path, required=True)
    args = ap.parse_args()
    f2 = digests(args.v2, regions.load("ntsc-u-v2").target["boot"]["sha256"])
    f1 = digests(args.v1, regions.load("ntsc-u").target["boot"]["sha256"])
    count1, count2 = {}, {}
    for _, d in f1.values():
        count1[d] = count1.get(d, 0) + 1
    for _, d in f2.values():
        count2[d] = count2.get(d, 0) + 1
    by_digest = {d: a for a, (_, d) in f1.items() if count1[d] == 1}
    target = ROOT / "symbol_addrs/usa/symbol_addrs.txt"
    lines = target.read_text(encoding="utf-8").splitlines()
    lines = without_generated_block(lines, MARKER)
    placeholders = {}
    for i, line in enumerate(lines):
        m = SYM.match(line)
        if m:
            placeholders[int(m.group(2), 16)] = (i, m.group(1))
    named: dict[int, str] = {}
    for line in (ROOT / "symbol_addrs/usa-v2/symbol_addrs.txt").read_text(encoding="utf-8").splitlines():
        m = SYM.match(line)
        if not m or re.match(r"(func|FUN)_[0-9A-Fa-f]{8}$", m.group(1)) or "type:func" not in m.group(3) and "size:" in m.group(3):
            continue
        address = int(m.group(2), 16)
        if address in f2 and count2[f2[address][1]] == 1 and f2[address][1] in by_digest:
            named[by_digest[f2[address][1]]] = m.group(1)
    sdk = ROOT / "config/datamine/ntsc-u-sdk-matches.tsv"
    if sdk.exists():  # SDK library functions found by scripts/match_sdk_libs.py; v2.00 names win on conflict
        found: dict[int, set[str]] = {}
        for line in sdk.read_text(encoding="utf-8").splitlines():
            if line and not line.startswith("#"):
                cols = line.split("\t")
                found.setdefault(int(cols[0], 16), set()).add(cols[4])
        for address, names in found.items():
            if len(names) == 1 and address not in named and address in f1:
                named[address] = next(iter(names))
    existing_names = {m.group(1) for line in lines if (m := SYM.match(line))}
    rows = []
    replaced = set()
    for address, name in sorted(named.items()):
        prior = placeholders.get(address)
        if prior and not prior[1].startswith(("func_", "FUN_")):
            continue
        if name in existing_names:
            continue
        rows.append((address, name))
        existing_names.add(name)
        if prior:
            replaced.add(prior[0])
    keep = [line for index, line in enumerate(lines) if index not in replaced]
    out = keep + ["", MARKER] + [f"{n} = 0x{a:08X}; // type:func size:0x{f1[a][0]:X} - name (v2.00 Promises or SDK library match), digest match"
                                 for a, n in rows]
    target.write_text("\n".join(out) + "\n", encoding="utf-8")
    print(f"carried {len(rows)} names to v1.01 ({len(named) - len(rows)} skipped as clashes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
