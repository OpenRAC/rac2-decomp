#!/usr/bin/env python3
"""Compile one C function with the GNU EE chain and compare it with the retail bytes.

The C file must define the function (named like the symbol or given by --symbol).
Only the function's own instruction words are compared; relocated fields (calls,
globals) differ by design, so use leaf functions or read the diff accordingly.
The ELF must be the pinned v2.00 boot and the extent must equal a catalogued function.
A result is an exploratory candidate: it adds no matching credit until the target-specific
compiler is qualified and a complete linked-byte proof exists.
Needs the chain via scripts/wsl_chain.py (on Linux: tools/linux/sitecustomize.py).

    python scripts/try_function.py src/try/IntToFloat.c --address 0x284690 --size 16
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import region as regions  # noqa: E402
import wsl_chain  # noqa: E402

CATALOG = Path(__file__).resolve().parents[1] / "config/regions/ntsc-u-v2/catalog.json"


def object_text(path: Path, section_hint: str) -> tuple[bytes, dict[int, int]]:
    b = path.read_bytes()
    shoff, = struct.unpack_from("<I", b, 0x20)
    entsize, num, strndx = struct.unpack_from("<HHH", b, 0x2E)
    rows = [struct.unpack_from("<10I", b, shoff + i * entsize) for i in range(num)]
    names = rows[strndx][4]
    found = {b[names + r[0]:b.index(b"\0", names + r[0])].decode(): b[r[4]:r[4] + r[5]] for r in rows}
    for key in (f".text.{section_hint}", ".text"):
        if key in found:
            relocs = {}
            rel = found.get(".rel" + key, b"")
            for i in range(0, len(rel), 8):
                offset, info = struct.unpack_from("<II", rel, i)
                relocs[offset] = info & 0xFF
            return found[key], relocs
    raise SystemExit(f"no code section in object; sections: {sorted(found)}")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", type=Path)
    ap.add_argument("--address", type=lambda x: int(x, 0), required=True)
    ap.add_argument("--size", type=int, required=True)
    ap.add_argument("--symbol")
    ap.add_argument("--region", default="ntsc-u-v2", choices=("ntsc-u", "ntsc-u-v2"),
                    help="ntsc-u: accepted v1.01 (pass --elf <reference>/boot.elf, extents are heuristic); ntsc-u-v2: experimental v2.00")
    ap.add_argument("--elf", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--mask-relocs", action="store_true", help="ignore relocated fields (calls, globals) when comparing")
    ap.add_argument("--record", action="store_true", help="on MATCH, add the proof to progress/v2/matches.json")
    ap.add_argument("--flags", default="-O2 -G0 -ffunction-sections")
    args = ap.parse_args()
    symbol = args.symbol or args.source.stem
    data = args.elf.read_bytes()
    pinned = regions.load(args.region).target["boot"]["sha256"]
    if hashlib.sha256(data).hexdigest() != pinned:
        raise SystemExit(f"{args.elf} is not the pinned {args.region} boot executable ({pinned[:12]}...)")
    if args.size <= 0 or args.size % 4:
        raise SystemExit("--size must be a positive multiple of 4")
    if args.region == "ntsc-u-v2":
        extents = {f[0]: f[1] for f in json.loads(CATALOG.read_text(encoding="utf-8"))["functions"]}
    else:  # v1.01: the extent is the Ghidra function body; accept any size multiple of 4 inside code
        extents = {args.address: args.size}
    if extents.get(args.address) != args.size:
        raise SystemExit(f"0x{args.address:X} is not a catalogued function of exactly {args.size} bytes"
                         f" (catalogue extent: {extents.get(args.address)}); check function_size_rank.py")
    reference = None
    for base, words in rank.load_code_ranges(data):
        if base <= args.address < base + len(words) * 4:
            i = (args.address - base) // 4
            reference = words[i:i + args.size // 4]
    if reference is None or len(reference) != args.size // 4:
        raise SystemExit("the extent is not fully inside one code section")
    raw_reference = list(reference)
    with tempfile.TemporaryDirectory(dir=Path.home() / "rac2-private") as tmp:
        obj, asm = Path(tmp) / "f.o", Path(tmp) / "f.s"
        wsl_chain.compile_c(args.source, args.flags.split(), obj, asm, Path(tmp) / "log.txt")
        raw, relocs = object_text(obj, symbol)
        print(asm.read_text())
    ours = list(struct.unpack(f"<{len(raw) // 4}I", raw))
    if args.mask_relocs:  # relocated fields are filled by the linker: compare everything else
        masks = {4: 0xFC000000, 5: 0xFFFF0000, 6: 0xFFFF0000, 7: 0xFFFF0000}  # JMP26, HI16, LO16, GPREL16
        for offset, kind in relocs.items():
            if kind in masks and offset // 4 < len(ours):
                ours[offset // 4] &= masks[kind]
                reference[offset // 4] &= masks[kind]
        print(f"masked {len(relocs)} relocated field(s)")
    print(f"reference {len(reference)} words, ours {len(ours)} words")
    ok = len(ours) == len(reference) and ours == reference
    for i in range(max(len(ours), len(reference))):
        a = reference[i] if i < len(reference) else None
        c = ours[i] if i < len(ours) else None
        print(f"{'  ' if a == c else '!!'} +{i * 4:02X} ref {a if a is None else f'{a:08X}'} ours {c if c is None else f'{c:08X}'}")
    print("MATCH" if ok else "DIFFERENT")
    if ok and args.record and args.region != "ntsc-u-v2":
        raise SystemExit("--record is only for the experimental v2.00 route")
    if ok and args.record:
        record_match(args, symbol, reference, raw_reference)
    return 0 if ok else 1


def record_match(args, symbol: str, words: list[int], raw: list[int]) -> None:
    path = Path(__file__).resolve().parents[1] / "progress/v2/matches.json"
    doc = json.loads(path.read_text(encoding="utf-8")) if path.exists() else {"schema": 1, "target": "SCUS_972.68", "version": "2.00",
                                                                             "status": "exploratory", "matches": []}
    source = args.source.resolve().relative_to(path.parents[2])
    row = {"symbol": symbol, "address": args.address, "size": args.size, "source": source.as_posix(),
           "source_sha256": hashlib.sha256(args.source.read_bytes()).hexdigest(), "flags": args.flags, "relocs_masked": args.mask_relocs,
           "reference_sha256": hashlib.sha256(struct.pack(f"<{len(raw)}I", *raw)).hexdigest(),
           "compared_sha256": hashlib.sha256(struct.pack(f"<{len(words)}I", *words)).hexdigest()}
    doc["matches"] = sorted([m for m in doc["matches"] if m["address"] != args.address] + [row], key=lambda m: m["address"])
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(doc, indent=1) + "\n", encoding="utf-8")
    print(f"recorded {symbol} in {path.relative_to(path.parents[2])}")


if __name__ == "__main__":
    raise SystemExit(main())
