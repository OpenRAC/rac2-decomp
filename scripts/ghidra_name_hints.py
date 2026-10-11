#!/usr/bin/env python3
"""List class-like names that diagnostic strings spell out, per program, with the functions that reference them.

Needs the headless Ghidra MCP server of docs/V2-SETUP.md with the boot and the 27 overlays in its project
(``GHIDRA_MCP_AUTH_TOKEN`` for the bearer token). A CamelCase token inside a string referenced by a function
(``LevelChunkCutsceneTrigger`` in a warning, ``HudHeroXP`` as a sprite name) is a naming hint for that function. Only the
token, the program, the function start and the string address are written, never the message text.

    GHIDRA_MCP_AUTH_TOKEN=... python scripts/ghidra_name_hints.py --url http://127.0.0.1:18089
"""
from __future__ import annotations

import argparse
import json
import os
import re
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TOKEN = re.compile(r"\b[A-Z][a-z0-9]+(?:[A-Z][a-z0-9]*)+\b|\b[A-Za-z]+_[A-Za-z0-9_]+\b")
SKIP = {"CS_", "D_", "g_"}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--url", default="http://127.0.0.1:8089")
    ap.add_argument("--output", type=Path, default=ROOT / "config/datamine/ntsc-u-name-hints-ghidra.tsv")
    args = ap.parse_args()
    key = os.environ.get("GHIDRA_MCP_AUTH_TOKEN", "")
    if not key:
        raise SystemExit("set GHIDRA_MCP_AUTH_TOKEN to the server's bearer token")

    def get(path: str) -> dict:
        request = urllib.request.Request(f"{args.url}/{path}", headers={"Authorization": f"Bearer {key}"})
        return json.load(urllib.request.urlopen(request, timeout=600))

    programs = sorted((f["name"] for f in get("list_project_files")["files"]), key=lambda n: (n != "boot.elf", int(n.split("_")[0]) if n[0].isdigit() else 0))
    rows = set()
    for program in programs:
        get(f"load_program_from_project?path=/{program}")
        get(f"switch_program?program={program}")
        strings, offset = [], 0
        while True:
            page = get(f"list_strings?offset={offset}&limit=2000")
            strings += page["strings"]
            offset += len(page["strings"])
            if not page["strings"] or offset >= page.get("total", offset + 1):
                break
        for item in strings:
            if int(item["address"], 16) >= 0x300000 and program == "boot.elf":
                continue
            tokens = {t for t in TOKEN.findall(item["value"]) if not t.startswith(tuple(SKIP)) and len(t) > 5}
            if not tokens:
                continue
            refs = get(f"get_xrefs_to?address={item['address']}&limit=50")["references"]
            for function in {r["from_function"] for r in refs if r.get("from_function", "").startswith("FUN_")}:
                for token in tokens:
                    # "named": the message labels itself with the function ("<name>: ...", "in <name>", "<name> WARNING")
                    t = re.escape(token)
                    named = re.match(rf"\W{{0,2}}{t}\s?:", item["value"]) or re.search(rf"\bin\s+{t}\b|\b{t}\s+(?:WARNING|ERROR)", item["value"])
                    form = "named" if named and "_" in token else "mention"
                    rows.add((program[:-4], int(function[4:], 16), token, int(item["address"], 16), form))
        if program != "boot.elf":
            get(f"close_program?name={program}")
    lines = ["# Class-like names spelled out by strings that a function references (found with Ghidra, scripts/ghidra_name_hints.py).",
             "# Columns: program, function start, name token, string address, form (named|mention). Naming hints only; no message text."]
    lines += [f"{p}\t0x{f:08X}\t{t}\t0x{s:08X}\t{form}" for p, f, t, s, form in sorted(rows)]
    args.output.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"{len(rows)} hints in {len(programs)} programs")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
