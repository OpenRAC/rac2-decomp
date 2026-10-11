#!/usr/bin/env python3
"""Record which boot functions reference a source-file name string, using a running Ghidra MCP server.

The retail boot keeps the names of a few source files (``hud.cpp``, ``loaders.cpp``, ``map.cpp``, ``gui/...``)
as strings that assert and debug calls pass around. Every function that references such a string is a proven
member of that source file. This script lists the strings of the program open in the headless Ghidra REST server
(``GHIDRA_MCP_AUTH_TOKEN`` for the bearer token), finds the ones that name a ``.c``/``.cpp`` file, follows their
cross-references and writes ``<function start> <file> <string address>`` rows. Only addresses and file names are
written, never the string table or instructions.

    podman run ... (see docs/V2-SETUP.md section 9) ; python scripts/ghidra_anchors.py --url http://127.0.0.1:18089
"""
from __future__ import annotations

import argparse
import json
import os
import re
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FILE = re.compile(r"((?:[A-Za-z0-9_]+/)*[A-Za-z0-9_]+\.(?:cpp|c))\b")
BOOT_MAX = 0x300000  # strings above this address are overlay-space mirrors


def fetch(url: str, token: str, path: str) -> dict:
    request = urllib.request.Request(f"{url}/{path}", headers={"Authorization": f"Bearer {token}"})
    return json.load(urllib.request.urlopen(request, timeout=120))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--url", default="http://127.0.0.1:8089")
    ap.add_argument("--output", type=Path, default=ROOT / "config/segments/ntsc-u-file-anchors.tsv")
    args = ap.parse_args()
    token = os.environ.get("GHIDRA_MCP_AUTH_TOKEN", "")
    if not token:
        raise SystemExit("set GHIDRA_MCP_AUTH_TOKEN to the server's bearer token")
    strings, offset = [], 0
    while True:
        page = fetch(args.url, token, f"list_strings?offset={offset}&limit=2000")
        strings += page["strings"]
        offset += len(page["strings"])
        if not page["strings"] or offset >= page.get("total", offset + 1):
            break
    rows = {}
    for item in strings:
        address = int(item["address"], 16)
        if address >= BOOT_MAX or ".c:" in item["value"]:  # "989snd.c: message" is a log prefix, not a file argument
            continue
        match = FILE.search(item["value"])
        if not match:
            continue
        # a stray byte may precede the name inside the string item: try the next two offsets when nothing references it
        for skip in range(3):
            start = address + match.start() + skip
            refs = fetch(args.url, token, f"get_xrefs_to?address={start:08x}&limit=500")["references"]
            if refs:
                name = item["value"][match.start() + skip:]
                name = FILE.match(name).group(1) if FILE.match(name) else match.group(1)
                break
        else:
            continue
        for ref in refs:
            function = ref.get("from_function")
            if function and function.startswith("FUN_"):
                rows[(int(function[4:], 16), name)] = start
    lines = ["# Functions that reference a source-file name string in the USA v1.01 boot (found with Ghidra, scripts/ghidra_anchors.py).",
             "# Columns: function start, source file, address of the file-name string. Addresses and names only."]
    lines += [f"0x{f:08X}\t{name}\t0x{s:08X}" for (f, name), s in sorted(rows.items())]
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"{len(rows)} anchors")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
