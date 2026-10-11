#!/usr/bin/env python3
"""Name level-overlay functions that equal a named boot function or an SDK library function.

Level overlays carry copies of engine code. A function whose relocation-masked digest equals exactly one named
boot function (``symbol_addrs/usa/symbol_addrs.txt``) or a single SDK library symbol (your ``toolchain/`` mirror)
inherits that name. Copies of boot functions are not listed (they take the boot name). Output is addresses and names only: ``config/datamine/ntsc-u-overlay-names.tsv``.

    python scripts/name_overlay_functions.py --reference <runtime>/runs/<run>/reference
"""
from __future__ import annotations

import argparse
import hashlib
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import match_sdk_libs as sdk  # noqa: E402
import region as regions  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--reference", type=Path, required=True)
    ap.add_argument("--libs", type=Path, nargs="+", default=[ROOT / "toolchain/sn-prodg-24", ROOT / "toolchain/sn-prodg-3.01"])
    ap.add_argument("--output", type=Path, default=ROOT / "config/datamine/ntsc-u-overlay-names.tsv")
    args = ap.parse_args()
    region = regions.load("ntsc-u")
    boot = (args.reference / "boot.elf").read_bytes()
    if hashlib.sha256(boot).hexdigest() != region.target["boot"]["sha256"]:
        raise SystemExit("reference boot is not the pinned USA v1.01 executable")
    names = {a: n for a, (n, _) in rank.read_symbols(ROOT / regions.registry()["regions"]["ntsc-u"]["symbols"]).items()
             if not n.startswith(("func_", "FUN_"))}
    ranges = ue.code_words(boot)
    rows = [(a, ue.digest(ue.slice_words(ranges, a, s))) for a, s in ue.extents(ranges)]
    count = Counter(d for _, d in rows)
    known: dict[str, set[tuple[str, str]]] = {}
    for a, d in rows:
        if a in names and count[d] == 1:
            known.setdefault(d, set()).add((names[a], "boot"))
    for root in args.libs:
        for path in sorted(root.rglob("*.a")):
            if "/ee/lib/" in path.as_posix():
                for _, blob in sdk.members(path.read_bytes()):
                    for name, words, _, _ in sdk.object_functions(blob):
                        known.setdefault(ue.digest(words), set()).add((name, "sdk"))
    lines = ["# Level-overlay functions named by an identical named boot function or SDK library function (digest match).",
             "# Columns: level, function start, name, source (boot|sdk). Addresses and names only."]
    total = shared = 0
    boot_digests = set(count)  # an overlay copy of a boot function inherits the boot name through the boot, so it is not listed
    for row in region.overlays["levels"]:
        r = ue.code_words((args.reference / "levels" / row["level"] / "overlay.elf").read_bytes())
        for a, s in ue.extents(r):
            d = ue.digest(ue.slice_words(r, a, s))
            shared += d in boot_digests
            hit = None if d in boot_digests else known.get(d)
            if hit and len({n for n, _ in hit}) == 1:
                name, source = sorted(hit)[0]
                lines.append(f"{row['level']}\t0x{a:08X}\t{name}\t{source}")
                total += 1
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"{total} overlay-only functions named; {shared} overlay functions are copies of boot functions (named through the boot)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
