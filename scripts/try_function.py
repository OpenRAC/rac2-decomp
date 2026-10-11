#!/usr/bin/env python3
"""Compile one C function with the GNU EE chain and compare it with the retail bytes.

The C file must define the function (named like the symbol or given by --symbol).
Only the function's own instruction words are compared; relocated fields (calls,
globals) differ by design, so use leaf functions or read the diff accordingly.
The ELF must be the pinned boot for the selected region and the extent must equal
one whole catalogued body. Boundary quality is printed explicitly. Masked equality
is a diagnostic only; even raw equality is an uncredited exploratory candidate.
A result is an exploratory candidate: it adds no matching credit until the target-specific
compiler is qualified and a complete linked-byte proof exists.
Needs the chain via scripts/wsl_chain.py (on Linux: tools/linux/sitecustomize.py).

    python scripts/try_function.py src/try/IntToFloat.c --address 0x284690 --size 16
"""
from __future__ import annotations

import argparse
import gzip
import hashlib
import io
import json
import struct
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import region as regions  # noqa: E402
import wsl_chain  # noqa: E402
import unique_code_report as unique  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "config/regions/ntsc-u-v2/catalog.json"


def catalog_extent(region_name: str, address: int, size: int, pinned: str, root: Path = ROOT) -> tuple[str, str | None]:
    """Require one whole pinned catalogue extent, never a caller-defined slice.

    Boundary quality remains explicit: catalogue equality is not an original
    function certificate or a matching-admission proof.
    """
    if address < 0 or address % 4 or size <= 0 or size % 4 or address + size > 1 << 32:
        raise ValueError("address and size must define a positive, aligned 32-bit extent")
    if region_name == "ntsc-u-v2":
        doc = json.loads((root / "config/regions/ntsc-u-v2/catalog.json").read_bytes())
        if (doc.get("schema") != 1 or doc.get("target") != "SCUS_972.68"
                or doc.get("version") != "2.00" or doc.get("boot_sha256") != pinned):
            raise ValueError("Stale or wrong-target v2 catalogue")
        rows = doc["functions"]
        spans = [{"address": row[0], "size": row[1]} for row in rows]
        unique.no_overlap(spans)
        matches = [row for row in rows if row[0] == address]
        if len(matches) != 1 or matches[0][1] != size:
            raise ValueError("Not one whole catalogued v2 function extent")
        return "inferred v2 catalogue boundary", None

    path = root / "config/function-catalog/catalog.json"
    doc = json.loads(path.read_bytes())
    if doc.get("schema") != 1 or doc.get("target") != "SCUS_972.68":
        raise ValueError("Wrong-target function catalogue")
    unique.validate_pins(doc, root)
    programs = [row for row in doc["programs"] if row.get("program") == "boot"]
    chunks = [row for row in doc["function_chunks"] if row.get("program") == "boot"]
    if len(programs) != 1 or programs[0].get("reference_sha256") != pinned or len(chunks) != 1:
        raise ValueError("Stale boot function catalogue identity")
    chunk = chunks[0]
    limit = chunk.get("max_expanded_bytes")
    if (chunk.get("path") != "boot.ndjson.gz" or chunk.get("compression") != "gzip"
            or chunk.get("format") != "compact-ndjson-v1" or type(limit) is not int
            or not 0 < limit <= 32 * 1024 * 1024):
        raise ValueError("Invalid boot catalogue chunk")
    location = (path.parent / chunk["path"]).resolve()
    if not location.is_relative_to(root.resolve()):
        raise ValueError("Boot catalogue chunk escapes repository")
    payload = location.read_bytes()
    if hashlib.sha256(payload).hexdigest() != chunk.get("sha256"):
        raise ValueError("Stale compressed boot catalogue")
    with gzip.GzipFile(fileobj=io.BytesIO(payload)) as stream:
        expanded = stream.read(limit + 1)
    if len(expanded) > limit or hashlib.sha256(expanded).hexdigest() != chunk.get("expanded_sha256"):
        raise ValueError("Stale expanded boot catalogue")
    rows = [unique.expand_compact_row(json.loads(line), "boot", doc["normalizer"]["sha256"])
            for line in expanded.splitlines() if line.strip()]
    unique.no_overlap(rows)
    matches = [row for row in rows if row["address"] == address]
    if len(matches) != 1 or matches[0]["size"] != size:
        raise ValueError("Not one whole catalogued v1 function extent")
    row = matches[0]
    status = row["boundary"]["status"]
    if status not in ("qualified_complete", "flow_supported_inferred"):
        raise ValueError("Catalogue boundary is not a supported whole body")
    unique.sha(row["raw_sha256"])
    return status, row["raw_sha256"]


def object_text(path: Path, section_hint: str) -> tuple[bytes, dict[int, int]]:
    b = path.read_bytes()
    if b[:6] != b"\x7fELF\x01\x01" or struct.unpack_from("<H", b, 16)[0] != 1:
        raise ValueError("Expected a 32-bit little-endian ET_REL object")
    shoff, = struct.unpack_from("<I", b, 0x20)
    entsize, num, _strndx = struct.unpack_from("<HHH", b, 0x2E)
    rows = [struct.unpack_from("<10I", b, shoff + i * entsize) for i in range(num)]
    symbols = []
    for table in rows:
        if table[1] != 2:
            continue
        if table[6] >= num or rows[table[6]][1] != 3 or table[9] != 16 or table[5] % 16:
            raise ValueError("Invalid object symbol table")
        names = rows[table[6]]
        strings = b[names[4]:names[4] + names[5]]
        for offset in range(table[4], table[4] + table[5], 16):
            name, start, size, info, _, index = struct.unpack_from("<IIIBBH", b, offset)
            end = strings.find(b"\0", name)
            if end < 0:
                raise ValueError("Invalid object symbol name")
            if strings[name:end].decode() == section_hint and info & 15 == 2 and index:
                symbols.append((start, size, index))
    if len(symbols) != 1:
        raise ValueError("Requested symbol is not one defined STT_FUNC")
    start, size, index = symbols[0]
    if index >= num:
        raise ValueError("Invalid function section")
    section = rows[index]
    if (section[1] != 1 or section[2] & 6 != 6 or start % 4 or size <= 0 or size % 4
            or start + size > section[5] or section[4] + section[5] > len(b)):
        raise ValueError("Function is not a complete executable object symbol")
    relocs = {}
    for relocation in rows:
        if relocation[1] != 9 or relocation[7] != index:
            continue
        if relocation[9] != 8 or relocation[5] % 8:
            raise ValueError("Invalid object relocation table")
        for offset in range(relocation[4], relocation[4] + relocation[5], 8):
            position, info = struct.unpack_from("<II", b, offset)
            if position % 4 or position >= section[5]:
                raise ValueError("Relocation outside its executable section")
            if start <= position < start + size:
                if position - start in relocs:
                    raise ValueError("Duplicate function relocation")
                relocs[position - start] = info & 0xFF
    return b[section[4] + start:section[4] + start + size], relocs


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source", type=Path)
    ap.add_argument("--address", type=lambda x: int(x, 0), required=True)
    ap.add_argument("--size", type=int, required=True)
    ap.add_argument("--symbol")
    ap.add_argument("--region", default="ntsc-u-v2", choices=("ntsc-u", "ntsc-u-v2"),
                    help="ntsc-u: accepted v1.01 (pass --elf <reference>/boot.elf); ntsc-u-v2: experimental v2.00")
    ap.add_argument("--elf", type=Path, default=rank.DEFAULT_ELF)
    ap.add_argument("--mask-relocs", action="store_true", help="diagnostic only: ignore relocated fields (calls, globals)")
    ap.add_argument("--record", action="store_true", help="on equal comparison, add an exploratory record to progress/v2/matches.json")
    ap.add_argument("--flags", default="-O2 -G0 -ffunction-sections")
    args = ap.parse_args()
    if args.record and args.region != "ntsc-u-v2":
        raise SystemExit("--record is only for the experimental v2.00 route")
    symbol = args.symbol or args.source.stem
    data = args.elf.read_bytes()
    pinned = regions.load(args.region).target["boot"]["sha256"]
    if hashlib.sha256(data).hexdigest() != pinned:
        raise SystemExit(f"{args.elf} is not the pinned {args.region} boot executable ({pinned[:12]}...)")
    quality, reference_hash = catalog_extent(args.region, args.address, args.size, pinned)
    print(f"boundary: {quality}; exploratory comparison, no matching credit")
    reference = None
    for base, words in rank.load_code_ranges(data):
        if base <= args.address < base + len(words) * 4:
            i = (args.address - base) // 4
            reference = words[i:i + args.size // 4]
    if reference is None or len(reference) != args.size // 4:
        raise SystemExit("the extent is not fully inside one code section")
    raw_reference = list(reference)
    if reference_hash and hashlib.sha256(struct.pack(f"<{len(reference)}I", *reference)).hexdigest() != reference_hash:
        raise ValueError("Stale catalogue body hash")
    with tempfile.TemporaryDirectory(dir=Path.home() / "rac2-private") as tmp:
        obj, asm = Path(tmp) / "f.o", Path(tmp) / "f.s"
        wsl_chain.compile_c(args.source, args.flags.split(), obj, asm, Path(tmp) / "log.txt")
        raw, relocs = object_text(obj, symbol)
        print(asm.read_text())
    ours = list(struct.unpack(f"<{len(raw) // 4}I", raw))
    if args.mask_relocs:  # relocated fields are filled by the linker: compare everything else
        masks = {4: 0xFC000000, 5: 0xFFFF0000, 6: 0xFFFF0000, 7: 0xFFFF0000}  # JMP26, HI16, LO16, GPREL16
        for offset, kind in relocs.items():
            if kind in masks and offset // 4 < min(len(ours), len(reference)):
                ours[offset // 4] &= masks[kind]
                reference[offset // 4] &= masks[kind]
        print(f"masked {len(relocs)} relocated field(s)")
    print(f"reference {len(reference)} words, ours {len(ours)} words")
    ok = len(ours) == len(reference) and ours == reference
    for i in range(max(len(ours), len(reference))):
        a = reference[i] if i < len(reference) else None
        c = ours[i] if i < len(ours) else None
        print(f"{'  ' if a == c else '!!'} +{i * 4:02X} ref {a if a is None else f'{a:08X}'} ours {c if c is None else f'{c:08X}'}")
    print(("MASKED_EQUAL_DIAGNOSTIC" if args.mask_relocs else "RAW_EQUAL_CANDIDATE") if ok else "DIFFERENT")
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
