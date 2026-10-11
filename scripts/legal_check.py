#!/usr/bin/env python3
"""Fail if tracked files could carry copyrighted game material (see LEGAL.md).

Checks every file Git tracks (or, with --staged, every staged file) for:
  * forbidden paths and extensions (ISO, ELF, object files, assembly, archives, media); .gz is
    allowed only when the decompressed payload is text that passes the text checks
  * binary magic numbers (ELF, ISO9660, PS2 IRX, ZIP/7z/RAR)
  * disassembly markers and dumps of consecutive 32-bit instruction words
  * references to files that must stay private (baserom/, extracted/, going-decompiled/)

Hashes, addresses, sizes, symbol names and authored C are allowed.
"""
from __future__ import annotations

import gzip
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BAD_EXT = {".iso", ".elf", ".bin", ".o", ".a", ".irx", ".wad", ".s", ".S", ".asm", ".7z", ".zip", ".rar",
           ".xz", ".bz2", ".tar", ".vag", ".adpcm", ".str", ".pss", ".tex", ".dds", ".ovl", ".exe", ".dll"}
BAD_DIRS = ("baserom/", "extracted/", "asm/", "asm_pp/", "going-decompiled/", "reference/", "work/", "toolchain/local/")
MAGIC = (b"\x7fELF", b"CD001", b"7z\xbc\xaf", b"Rar!", b"PK\x03\x04", b"\x1f\x8b")
ASM_MARKERS = re.compile(r"^\s*(glabel|\.set\s+noreorder|\.word\s+0x[0-9a-fA-F]{8}|INCLUDE_ASM\(.*asm/)", re.M)
HEX_DUMP = re.compile(r"(?:\b[0-9a-fA-F]{8}\b[ ,\t]+){16,}")
MAX_BINARY = 512 * 1024
PROJECT_ORIGINAL = {"assets/rac2-logo.png"}  # project-made emblem, not game art


def tracked(staged: bool) -> list[str]:
    cmd = ["git", "diff", "--cached", "--name-only", "--diff-filter=AM"] if staged else ["git", "ls-files"]
    return subprocess.run(cmd, cwd=ROOT, check=True, capture_output=True, text=True).stdout.split("\n")[:-1]


def check(rel: str) -> list[str]:
    problems = []
    p = ROOT / rel
    if not p.is_file():
        return problems
    suffix = p.suffix
    if rel.startswith(BAD_DIRS):
        problems.append("forbidden directory")
    if suffix in BAD_EXT:
        problems.append(f"forbidden extension {suffix}")
    if suffix == ".gz":  # JSON metadata only: inspect the decompressed text like any other file
        try:
            raw = gzip.decompress(p.read_bytes())
        except OSError:
            return problems + ["unreadable gzip"]
        if b"\0" in raw[:4096] or raw[:4] in MAGIC:
            return problems + ["compressed binary payload"]
        return problems + text_problems(rel, raw.decode("utf-8", errors="ignore"))
    head = p.read_bytes()[:4096]
    if any(head.startswith(m) or (m == b"CD001" and head[0x8001:0x8006] == m) for m in MAGIC):
        problems.append("binary container magic")
    if b"\0" in head:
        if rel not in PROJECT_ORIGINAL and p.stat().st_size > MAX_BINARY:
            problems.append(f"binary file larger than {MAX_BINARY // 1024} KiB")
        return problems
    if p.stat().st_size > 20 * 1024 * 1024:
        return problems
    return problems + text_problems(rel, p.read_text(encoding="utf-8", errors="ignore"))


def text_problems(rel: str, text: str) -> list[str]:
    problems = []
    if rel != "scripts/legal_check.py" and ASM_MARKERS.search(text):
        problems.append("disassembly marker")
    if HEX_DUMP.search(text):
        problems.append("dump of consecutive 32-bit words")
    return problems


def main() -> int:
    bad = {f: p for f in tracked("--staged" in sys.argv) if (p := check(f))}
    for f, p in sorted(bad.items()):
        print(f"{f}: {'; '.join(p)}")
    print(f"legal check: {len(bad)} flagged file(s)", file=sys.stderr)
    return 1 if bad else 0


if __name__ == "__main__":
    raise SystemExit(main())
