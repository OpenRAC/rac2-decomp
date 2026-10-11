#!/usr/bin/env python3
"""Estimate the real amount of unique EE code in a prepared reference (boot + level overlays).

Reads the ELFs that ``setup.py`` unpacked into your private runtime. Function bodies are split
at ``jr ra`` and hashed after masking relocatable fields (jump targets and 16-bit immediates),
so engine code linked at different addresses in different overlays counts once. This is a HEURISTIC
family estimate: immediates and load/store offsets are erased too, so functions that differ only in
constants or struct fields share a digest. It is not a progress denominator. Only counts
are printed; no bytes are written. The split is heuristic: data inside ``.text`` is included.

    python scripts/measure_unique.py --reference <runtime>/runs/<run>/reference [--output build/unique-v2.json]
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

JR_RA = 0x03E00008
IMM_OPS = {9, 13, 0x0F, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B, 0x31, 0x37, 0x39, 0x3F, 0x1E, 0x1F, 0x0C}


def sections(path: Path) -> dict[str, bytes]:
    b = path.read_bytes()
    shoff, = struct.unpack_from("<I", b, 0x20)
    entsize, num, strndx = struct.unpack_from("<HHH", b, 0x2E)
    rows = [struct.unpack_from("<10I", b, shoff + i * entsize) for i in range(num)]
    names = rows[strndx][4]
    return {b[names + r[0]:b.index(b"\0", names + r[0])].decode(): b[r[4]:r[4] + r[5]] for r in rows if r[3]}


def normalise(word: int) -> int:
    op = word >> 26
    return op << 26 if op in (2, 3) else word & 0xFFFF0000 if op in IMM_OPS else word


def bodies(data: bytes):
    words = struct.unpack(f"<{len(data) // 4}I", data[:len(data) // 4 * 4])
    start = i = 0
    while i < len(words):
        if words[i] == JR_RA:
            end = i + 2
            while end < len(words) and words[end] == 0:
                end += 1
            yield (end - start) * 4, hashlib.sha1(struct.pack(f"<{end - start}I", *map(normalise, words[start:end]))).digest()
            start = i = end
        else:
            i += 1
    if start < len(words):
        yield (len(words) - start) * 4, hashlib.sha1(struct.pack(f"<{len(words) - start}I", *map(normalise, words[start:]))).digest()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--reference", type=Path, required=True)
    ap.add_argument("--output", type=Path)
    args = ap.parse_args()
    seen: dict[bytes, int] = {}
    boot_total = 0
    boot = sections(args.reference / "boot.elf")
    for name in ("core.text", ".text"):
        for size, digest in bodies(boot[name]):
            boot_total += size
            seen.setdefault(digest, size)
    boot_unique = sum(seen.values())
    levels, overlay_total = {}, 0
    for path in sorted((args.reference / "levels").glob("*/overlay.elf")):
        total = new = 0
        for size, digest in bodies(sections(path)[".text"]):
            total += size
            if digest not in seen:
                seen[digest] = size
                new += size
        levels[path.parent.name] = {"text_bytes": total, "new_unique_bytes": new}
        overlay_total += total
    result = {"boot_text_bytes": boot_total, "boot_unique_bytes": boot_unique,
              "overlay_text_bytes_summed": overlay_total,
              "overlay_new_unique_bytes": sum(seen.values()) - boot_unique,
              "unique_total_bytes": sum(seen.values()), "levels": levels}
    print(json.dumps({k: v for k, v in result.items() if k != "levels"}, indent=1))
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(result, indent=1) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
