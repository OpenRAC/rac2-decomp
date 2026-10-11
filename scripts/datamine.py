#!/usr/bin/env python3
"""Mine names and structure out of the retail boot executable you extracted from your own disc.

Everything it reads stays private. Full results go to ``--private`` (default ``extracted/datamine``, git-ignored).
Only identifiers and addresses are written to the tracked ``config/datamine/`` tables: source-file names,
function names that a diagnostic message spells out, identifier-like members of string tables (state and
enum names), SDK library tags, and the section map. Game text itself is never committed.

    python scripts/datamine.py --elf <reference>/boot.elf
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import region as regions  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
GP = 0x1AEFF0
SDK_TAG = re.compile(r"^(Ps2|PsII|sce|SCE)?[A-Za-z0-9_]*lib[a-z0-9_]+ ?\d{3,4}$|^PsIIlib\w+ \d+$")
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]{2,}$")
FILE = re.compile(r"^(?:[A-Za-z0-9_]+/)*[A-Za-z0-9_]+\.(?:cpp|c|h|s)$")
NAME_IN_MESSAGE = re.compile(r"(?:inside|in|from|by|calling|of)\s+((?:snd|sce|Sif|Gs|Dma|Pad|Cd|mc|Mc)[A-Za-z0-9_]{3,})")


def sections(elf: bytes) -> list[dict]:
    shoff, = struct.unpack_from("<I", elf, 0x20)
    size, count, strndx = struct.unpack_from("<HHH", elf, 0x2E)
    rows = [struct.unpack_from("<10I", elf, shoff + i * size) for i in range(count)]
    names = rows[strndx][4]
    out = []
    for name, kind, flags, addr, off, length, *_ in rows:
        if addr:
            out.append({"name": elf[names + name:elf.index(b"\0", names + name)].decode(), "addr": addr, "size": length,
                        "flags": flags, "nobits": kind == 8, "data": b"" if kind == 8 else elf[off:off + length]})
    return out


def strings(secs: list[dict]) -> dict[int, str]:
    found = {}
    for s in secs:
        if s["flags"] & 4 or s["nobits"] or s["name"].startswith(".DVP"):
            continue
        for m in re.finditer(rb"(?<![\x20-\x7e])[\x20-\x7e\n\t]{4,}(?=\0)", s["data"]):
            found[s["addr"] + m.start()] = m.group().decode("ascii")
    return found


def code_refs(ranges: dict[int, list[int]], found: dict[int, str]) -> dict[int, set[int]]:
    """string address -> set of function starts that build the address (lui+addiu/ori, or $gp+offset)."""
    refs: dict[int, set[int]] = defaultdict(set)
    lookup = sorted(found)
    import bisect

    def hit(value: int):
        i = bisect.bisect_right(lookup, value) - 1
        return lookup[i] if i >= 0 and value < lookup[i] + len(found[lookup[i]]) + 1 else None

    for start, size in ue.extents(ranges):
        words = ue.slice_words(ranges, start, size)
        hi: dict[int, int] = {}
        for w in words:
            op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
            simm = imm - 0x10000 if imm & 0x8000 else imm
            if op == 0x0F:
                hi[rt] = imm << 16
            elif op in (9, 13) and (rs in hi or rs == 28):
                value = ((GP if rs == 28 else hi[rs]) + (simm if op == 9 else imm)) & 0xFFFFFFFF
                if (s := hit(value)) is not None:
                    refs[s].add(start)
                hi[rt] = value
            elif op in range(0x20, 0x30) or op in (0x31, 0x39, 0x37, 0x3F):
                if rs in hi and (s := hit((hi[rs] + simm) & 0xFFFFFFFF)) is not None:
                    refs[s].add(start)
            elif op not in (4, 5, 1, 2, 3, 6, 7):
                hi.pop(rt, None)
    return refs


def pointer_tables(secs: list[dict], found: dict[int, str], minimum: int = 3) -> list[tuple[int, list[int]]]:
    tables = []
    for s in secs:
        if s["flags"] & 4 or s["nobits"]:
            continue
        data = s["data"]
        n = len(data) // 4
        words = struct.unpack(f"<{n}I", data[:n * 4])
        i = 0
        while i < n:
            if words[i] in found:
                j = i
                while j < n and (words[j] in found or words[j] == 0):
                    j += 1
                targets = [w for w in words[i:j] if w]
                if len(targets) >= minimum:
                    tables.append((s["addr"] + i * 4, targets))
                i = j
            else:
                i += 1
    return tables


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", type=Path, required=True)
    ap.add_argument("--private", type=Path, default=ROOT / "extracted/datamine")
    ap.add_argument("--public", type=Path, default=ROOT / "config/datamine")
    args = ap.parse_args()
    elf = args.elf.read_bytes()
    if hashlib.sha256(elf).hexdigest() != regions.load("ntsc-u").target["boot"]["sha256"]:
        raise SystemExit("not the pinned USA v1.01 boot executable")
    secs = sections(elf)
    found = strings(secs)
    ranges = ue.code_words(elf)
    refs = code_refs(ranges, found)
    tables = pointer_tables(secs, found)
    args.private.mkdir(parents=True, exist_ok=True)
    (args.private / "strings.json").write_text(json.dumps({f"{a:08X}": v for a, v in sorted(found.items())}), encoding="utf-8")
    (args.private / "string-refs.json").write_text(json.dumps({f"{a:08X}": sorted(f"{x:08X}" for x in fs) for a, fs in sorted(refs.items())}), encoding="utf-8")
    (args.private / "string-tables.json").write_text(json.dumps([{"address": f"{a:08X}", "strings": [found[t] for t in ts]} for a, ts in tables]), encoding="utf-8")
    args.public.mkdir(parents=True, exist_ok=True)
    # tracked tables: identifiers and addresses only
    files = [(a, v) for a, v in sorted(found.items()) if FILE.match(v) and a < 0x300000]
    lines = ["# Source-file name strings in the USA v1.01 boot and the functions that reference them (scripts/datamine.py).",
             "# Columns: string address, file name, referencing function starts. Addresses and names only."]
    for a, v in files:
        lines.append(f"0x{a:08X}\t{v}\t{','.join(f'0x{x:08X}' for x in sorted(refs.get(a, [])))}")
    (args.public / "ntsc-u-source-files.tsv").write_text("\n".join(lines) + "\n", encoding="utf-8")
    names = []
    for a, v in sorted(found.items()):
        if a >= 0x300000:
            continue
        for m in NAME_IN_MESSAGE.finditer(v):
            for fn in sorted(refs.get(a, [])):
                names.append(f"0x{fn:08X}\t{m.group(1)}\t0x{a:08X}")
    (args.public / "ntsc-u-name-hints.tsv").write_text(
        "# A function whose diagnostic message spells out the name of an SDK-style function it calls or implements (hint only).\n"
        "# Columns: referencing function start, spelled name, string address.\n" + "\n".join(sorted(set(names))) + "\n", encoding="utf-8")
    enum_rows = []
    for a, ts in tables:
        members = [found[t] for t in ts]
        if len(members) >= 4 and all(IDENT.match(m) for m in members):
            enum_rows.append(f"0x{a:08X}\t{len(members)}\t" + ",".join(members))
    (args.public / "ntsc-u-identifier-tables.tsv").write_text(
        "# Tables of pointers to identifier-like names (state, enum or asset-slot names) in the USA v1.01 boot.\n"
        "# Columns: table address, member count, member names in table order.\n" + "\n".join(enum_rows) + "\n", encoding="utf-8")
    tags = sorted({v for v in found.values() if SDK_TAG.match(v)})
    lines = ["# SDK library version tags in the USA v1.01 boot.", *tags]
    (args.public / "ntsc-u-sdk-tags.tsv").write_text("\n".join(lines) + "\n", encoding="utf-8")
    smap = ["# Section map of the USA v1.01 boot (name, address, size, flags).",
            *[f"{s['name']}\t0x{s['addr']:08X}\t{s['size']}\t0x{s['flags']:X}" for s in secs]]
    (args.public / "ntsc-u-sections.tsv").write_text("\n".join(smap) + "\n", encoding="utf-8")
    print(f"{len(found)} strings, {len(refs)} referenced from code, {len(tables)} pointer tables, "
          f"{len(files)} file names, {len(set(names))} name hints, {len(enum_rows)} identifier tables, {len(tags)} sdk tags")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
