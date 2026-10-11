#!/usr/bin/env python3
"""Name boot functions after the PS2 SDK library functions they were linked from.

The retail boot statically links Sony SDK libraries (libcdvd, libpad2, libmc, libdma, libgraph, libvu0, ...).
Your own SDK mirror (``toolchain/sn-prodg-24`` and ``toolchain/sn-prodg-3.01``, git-ignored) holds those
libraries as ``ar`` archives of relocatable ELF objects with symbol names. Each library function is rebuilt
with its relocation fields masked from the real ``.rel`` entries, digested with ``unique_estimate.digest`` and
looked up in the boot; only digests unique on both sides count. Only addresses, sizes, library and symbol names
are written (``config/datamine/ntsc-u-sdk-matches.tsv``), never instruction bytes.

    python scripts/match_sdk_libs.py --elf <reference>/boot.elf [--libs toolchain/sn-prodg-24 toolchain/sn-prodg-3.01]
"""
from __future__ import annotations

import argparse
import hashlib
import struct
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import region as regions  # noqa: E402
import unique_estimate as ue  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
MASKS = {4: 0xFC000000, 5: 0xFFFF0000, 6: 0xFFFF0000, 7: 0xFFFF0000, 3: 0xFFFFFFFF}  # JMP26, HI16, LO16, GPREL16, 32-bit data
STT_FUNC = 2


def members(archive: bytes):
    """Yield (member name, bytes) of a GNU/BSD ``ar`` archive."""
    if archive[:8] != b"!<arch>\n":
        return
    pos, long_names = 8, b""
    while pos + 60 <= len(archive):
        name = archive[pos:pos + 16].decode("latin1").strip()
        size = int(archive[pos + 48:pos + 58].decode().strip())
        body = archive[pos + 60:pos + 60 + size]
        if name == "//":
            long_names = body
        elif name.startswith("/") and name[1:].isdigit() and long_names:
            start = int(name[1:])
            yield long_names[start:long_names.index(b"\n", start)].decode("latin1").rstrip("/"), body
        elif name not in ("/", "__.SYMDEF"):
            yield name.rstrip("/"), body
        pos += 60 + size + (size & 1)


def object_functions(blob: bytes):
    """(symbol, words with relocation fields zeroed) for every function symbol of one relocatable ELF."""
    if blob[:4] != b"\x7fELF" or blob[4] != 1 or blob[5] != 1:
        return
    shoff, = struct.unpack_from("<I", blob, 0x20)
    size, count, strndx = struct.unpack_from("<HHH", blob, 0x2E)
    rows = [struct.unpack_from("<10I", blob, shoff + i * size) for i in range(count)]
    names = rows[strndx][4]
    sec_names = [blob[names + r[0]:blob.index(b"\0", names + r[0])].decode() for r in rows]
    text_index = {i for i, n in enumerate(sec_names) if n == ".text" or n.startswith(".text.")}
    symtab = next((i for i, r in enumerate(rows) if r[1] == 2), None)
    if symtab is None:
        return
    strtab = rows[rows[symtab][6]][4]
    syms = []
    for off in range(rows[symtab][4], rows[symtab][4] + rows[symtab][5], 16):
        name, value, sz, info, _, shndx = struct.unpack_from("<IIIBBH", blob, off)
        if shndx in text_index and (info & 0xF) in (0, STT_FUNC) and not blob[strtab + name:strtab + name + 1] == b"\0":
            syms.append((value, sz, shndx, blob[strtab + name:blob.index(b"\0", strtab + name)].decode()))
    relocs = {}
    for r in rows:
        if r[1] == 9 and r[7] in text_index:
            for off in range(r[4], r[4] + r[5], 8):
                where, info = struct.unpack_from("<II", blob, off)
                relocs.setdefault(r[7], {})[where] = info & 0xFF
    for shndx in text_index:
        sec = rows[shndx]
        words = list(struct.unpack_from(f"<{sec[5] // 4}I", blob, sec[4]))
        for where, kind in relocs.get(shndx, {}).items():
            if where // 4 < len(words):
                words[where // 4] &= ~MASKS.get(kind, 0) & 0xFFFFFFFF if kind in (4, 5, 6, 7) else words[where // 4]
        ordered = sorted(s for s in syms if s[2] == shndx)
        for i, (value, sz, _, name) in enumerate(ordered):
            end = value + sz if sz else (ordered[i + 1][0] if i + 1 < len(ordered) else sec[5])
            if end > value and (end - value) % 4 == 0:
                yield name, words[value // 4:end // 4], value, sec[5]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--elf", type=Path, required=True)
    ap.add_argument("--libs", type=Path, nargs="+", default=[ROOT / "toolchain/sn-prodg-24", ROOT / "toolchain/sn-prodg-3.01"])
    ap.add_argument("--output", type=Path, default=ROOT / "config/datamine/ntsc-u-sdk-matches.tsv")
    args = ap.parse_args()
    elf = args.elf.read_bytes()
    if hashlib.sha256(elf).hexdigest() != regions.load("ntsc-u").target["boot"]["sha256"]:
        raise SystemExit("not the pinned USA v1.01 boot executable")
    ranges = ue.code_words(elf)
    boot = [(a, s, ue.digest(ue.slice_words(ranges, a, s))) for a, s in ue.extents(ranges)]
    count = Counter(d for _, _, d in boot)
    by_digest = {d: (a, s) for a, s, d in boot if count[d] == 1}
    found: dict[str, set[tuple[str, str, str]]] = {}
    where: dict[tuple[str, str], list[tuple[int, int, int]]] = {}  # (lib, member) -> (boot address, offset, text size)
    index: dict[str, tuple[int, int]] = {}
    scanned = 0
    for root in args.libs:
        for path in sorted(root.rglob("*.a")):
            if "/ee/lib/" not in path.as_posix():
                continue
            for member, blob in members(path.read_bytes()):
                for name, words, offset, text_size in object_functions(blob):
                    scanned += 1
                    d = ue.digest(words)
                    if d in by_digest:
                        found.setdefault(d, set()).add((path.name, member, name))
                        where.setdefault((path.name, member), []).append((by_digest[d][0], offset, text_size))
    lines = ["# Boot functions that equal a PS2 SDK library function (relocation-masked digest, unique in the boot).",
             "# Columns: boot function start, size, library, object member, symbol; several rows per address = identical bodies."]
    rows = []
    for d, hits in found.items():
        a, s = by_digest[d]
        for lib, member, name in sorted(hits):
            rows.append((a, s, lib, member, name))
    lines += [f"0x{a:08X}\t{s}\t{lib}\t{member}\t{name}" for a, s, lib, member, name in sorted(rows)]
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    objects = ["# SDK library objects located in the USA v1.01 boot: all matched functions of an object agree on its start,",
               "# it has two or more matches (or one covering the whole object), and it overlaps no better-supported object.",
               "# Columns: boot start, boot end, library, object member, matched functions."]
    cand = []
    for (lib, member), hits in sorted(where.items()):
        starts = {a - off for a, off, _ in hits}
        sizes = {size for _, _, size in hits}
        if len(starts) == 1 and len(sizes) == 1 and (start := next(iter(starts))) >= 0:
            if len(hits) >= 2 or hits[0][2] <= 0x1F0:
                cand.append((len(hits), start, start + hits[0][2], lib, member))
    chosen = []
    for n, start, end, lib, member in sorted(cand, key=lambda c: (-c[0], c[1])):
        if all(end <= c[0] or start >= c[1] or (c[0], c[1]) == (start, end) for c in chosen):
            chosen.append((start, end, lib, member, n))
    chosen = [c for c in sorted(chosen) if c[2] not in ("libg.a", "libm.a")]
    seen_ranges = set()
    for start, end, lib, member, n in chosen:
        if (start, end) not in seen_ranges:
            seen_ranges.add((start, end))
            objects.append(f"0x{start:08X}\t0x{end:08X}\t{lib}\t{member}\t{n}")
    args.output.with_name("ntsc-u-sdk-objects.tsv").write_text("\n".join(objects) + "\n", encoding="utf-8")
    print(f"{len(objects) - 2} located objects")
    print(f"scanned {scanned} library functions; {len(found)} boot functions matched ({len(rows)} rows)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
