#!/usr/bin/env python3
"""Rank the functions of your own retail executable by size.

The tool reads the boot ELF you extracted from your own disc (default
``baserom/SCUS_972.68``), discovers function boundaries, joins them with the
repository's symbol files and campaign proofs, and prints a ranking. Only
addresses, sizes and names are produced; no instruction bytes are written.
Outputs go to ``build/`` (git-ignored) unless ``--output`` says otherwise.

Boundary discovery is heuristic (R5900 ``jal`` targets, ``addiu sp,sp,-N``
prologues, ``jr ra`` epilogues, symbol files). Treat sizes as candidates and
confirm in Ghidra before reserving a function.

Examples:
    python scripts/function_size_rank.py --category small --status todo --limit 30
    python scripts/function_size_rank.py --format csv --output build/rank.csv
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import sys
from pathlib import Path
from typing import NamedTuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
import region as regions  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_ELF = ROOT / "baserom" / "SCUS_972.68"
CANDIDATES = ROOT / "progress" / "candidates.json"

JR_RA = 0x03E00008
NOP = 0
SMALL, MEDIUM = 100, 500
SYM_RE = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;(.*)$")
TYPE_RE = re.compile(r"type:(\w+)")
DATA_PREFIXES = ("g_", "D_", "s_", "sc_", "k_")
SIZE_RE = re.compile(r"size:\s*(0x[0-9A-Fa-f]+|\d+)")


class Function(NamedTuple):
    address: int
    size: int
    name: str
    status: str  # matched | named | todo

    @property
    def category(self) -> str:
        return "small" if self.size <= SMALL else "medium" if self.size <= MEDIUM else "big"


CODE_SECTIONS = {"core.text", ".text"}  # skip .vutext (VU microcode), data and constants


def load_code_ranges(elf: bytes) -> list[tuple[int, list[int]]]:
    """Return (address, 32-bit words) for every EE code section of a 32-bit LE ELF."""
    if elf[:4] != b"\x7fELF" or elf[4] != 1 or elf[5] != 1:
        raise SystemExit("not a 32-bit little-endian ELF")
    shoff, = struct.unpack_from("<I", elf, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from("<HHH", elf, 0x2E)
    rows = [struct.unpack_from("<10I", elf, shoff + i * shentsize) for i in range(shnum)]
    strtab = rows[shstrndx][4]
    ranges = []
    for name_off, _, _, addr, off, size, *_ in rows:
        end = elf.index(b"\0", strtab + name_off)
        if elf[strtab + name_off:end].decode() in CODE_SECTIONS and size:
            ranges.append((addr, list(struct.unpack_from(f"<{size // 4}I", elf, off))))
    if not ranges:
        raise SystemExit("no .text/core.text section found")
    return ranges


def is_function(name: str, comment: str) -> bool:
    """Symbol files mix code and data; keep entries that are functions."""
    kind = TYPE_RE.search(comment)
    if kind:
        return kind.group(1) == "func"
    return not name.startswith(DATA_PREFIXES) and "size:" not in comment


def read_symbols(path: Path) -> dict[int, tuple[str, int | None]]:
    out: dict[int, tuple[str, int | None]] = {}
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8").splitlines():
        m = SYM_RE.match(line)
        if m and is_function(m.group(1), m.group(3)):
            size = SIZE_RE.search(m.group(3))
            out[int(m.group(2), 16)] = (m.group(1), int(size.group(1), 0) if size else None)
    return out


def discover_starts(ranges: list[tuple[int, list[int]]], symbols: dict[int, tuple[str, int | None]]) -> list[int]:
    def inside(addr: int) -> bool:
        return any(base <= addr < base + len(words) * 4 for base, words in ranges)

    starts = {a for a in symbols if a % 4 == 0 and inside(a)}
    for base, words in ranges:
        pending_from = 0  # a new function starts at the first non-nop word at or after this index
        for i, w in enumerate(words):
            pc = base + i * 4
            if w >> 26 == 3:  # jal
                tgt = (pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if inside(tgt):
                    starts.add(tgt)
            if pending_from is not None and i >= pending_from and w != NOP:
                starts.add(pc)
                pending_from = None
            if w == JR_RA:
                pending_from = i + 2  # skip the delay slot
    return sorted(starts)


def trim_size(words: list[int], base: int, start: int, nxt: int) -> int:
    """Drop trailing nop padding between the delay slot of the last jr ra and the next start."""
    lo, hi = (start - base) // 4, (nxt - base) // 4
    last_ret = -1
    for i in range(lo, hi):
        if words[i] == JR_RA:
            last_ret = i
    if last_ret >= 0:
        return (last_ret + 2 - lo) * 4
    j = hi
    while j > lo and words[j - 1] == NOP:
        j -= 1
    return max(j - lo, 1) * 4


def matched_addresses() -> set[int]:
    if not CANDIDATES.exists():
        return set()
    data = json.loads(CANDIDATES.read_text(encoding="utf-8"))
    return {f["address"] for f in data.get("functions", []) if f.get("matched")}


def build(elf_path: Path, region_name: str | None) -> list[Function]:
    data = elf_path.read_bytes()
    region = regions.load(region_name)
    entry = regions.registry()["regions"][region.name]
    pinned = region.target["boot"]["sha256"]
    matched: set[int] = set()
    symbols: dict[int, tuple[str, int | None]] = {}
    if hashlib.sha256(data).hexdigest() != pinned:
        print(f"warning: {elf_path.name} is not the pinned boot executable of {region.label};"
              " symbols and proofs are not applied.", file=sys.stderr)
    else:
        symbols = read_symbols(ROOT / entry["symbols"]) if entry.get("symbols") else {}
        if region.matching:  # campaign proofs exist only for the matching region
            matched = matched_addresses()
    ranges = load_code_ranges(data)
    starts = discover_starts(ranges, symbols)
    funcs = []
    for base, words in ranges:
        end = base + len(words) * 4
        mine = [x for x in starts if base <= x < end]
        for idx, start in enumerate(mine):
            nxt = mine[idx + 1] if idx + 1 < len(mine) else end
            size = trim_size(words, base, start, nxt)
            known = symbols.get(start)
            name = known[0] if known else f"func_{start:08X}"
            status = ("matched" if start in matched else
                      "named" if known and not name.startswith(("func_", "FUN_")) else "todo")
            funcs.append(Function(start, size, name, status))
    return funcs


def render(funcs: list[Function], fmt: str) -> str:
    if fmt == "json":
        return json.dumps([f._asdict() | {"category": f.category} for f in funcs], indent=1)
    if fmt == "csv":
        return "address,size,category,status,name\n" + "\n".join(
            f"0x{f.address:08X},{f.size},{f.category},{f.status},{f.name}" for f in funcs)
    rows = [f"{'ADDRESS':<12}{'SIZE':>7}  {'CATEGORY':<9}{'STATUS':<9}NAME"]
    rows += [f"0x{f.address:08X}  {f.size:>7}  {f.category:<9}{f.status:<9}{f.name}" for f in funcs]
    return "\n".join(rows)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", type=Path, default=DEFAULT_ELF, help="your extracted boot executable")
    ap.add_argument("--region", choices=regions.names(), default="ntsc-u",
                    help="game region (default: ntsc-u, the accepted USA v1.01 target; v2 is experimental)")
    ap.add_argument("--format", choices=("table", "csv", "json"), default="table")
    ap.add_argument("--category", choices=("small", "medium", "big", "all"), default="all")
    ap.add_argument("--status", choices=("todo", "named", "matched", "all"), default="all")
    ap.add_argument("--min-size", type=int, default=8, help="skip fragments below this size")
    ap.add_argument("--max-size", type=int)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--ascending", action="store_true", help="smallest first (default: largest first)")
    ap.add_argument("--output", type=Path, help="write here instead of stdout (keep it under build/)")
    ap.add_argument("--summary", action="store_true", help="print totals per category to stderr")
    args = ap.parse_args()

    if not args.elf.exists():
        print(f"error: {args.elf} not found. Extract SCUS_972.68 from your own disc into baserom/"
              " (see docs/START-HERE.md).", file=sys.stderr)
        return 2
    funcs = build(args.elf, args.region)
    if args.summary:
        for cat in ("small", "medium", "big"):
            sel = [f for f in funcs if f.category == cat]
            print(f"{cat:<7}{len(sel):>6} functions {sum(f.size for f in sel):>9} bytes", file=sys.stderr)
        print(f"total  {len(funcs):>6} functions {sum(f.size for f in funcs):>9} bytes", file=sys.stderr)
    sel = [f for f in funcs
           if f.size >= args.min_size and (args.max_size is None or f.size <= args.max_size)
           and args.category in ("all", f.category) and args.status in ("all", f.status)]
    sel.sort(key=lambda f: (f.size, f.address) if args.ascending else (-f.size, f.address))
    if args.limit:
        sel = sel[:args.limit]
    text = render(sel, args.format)
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(text + "\n", encoding="utf-8")
        print(f"wrote {len(sel)} functions to {args.output}", file=sys.stderr)
    else:
        print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
