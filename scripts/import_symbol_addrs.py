#!/usr/bin/env python3
"""Export USA v1.01 candidate symbol metadata to an explicit private review file.

Never updates the maintained symbol maps and never infers another release's
addresses. Review and merge individual names separately; this adds no credit.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
NAME = re.compile(r"[A-Za-z_]\w*\Z", re.ASCII)


def review_output(path: Path) -> Path:
    """Require an unused outside-repository or Git-ignored review destination."""
    path = path.resolve()
    if path.exists():
        raise ValueError(f"Refusing to overwrite {path}")
    if path == ROOT or ROOT in path.parents:
        # Canonical maps remain protected even if a local ignore rule covers them.
        if ROOT / "symbol_addrs" in path.parents:
            raise ValueError("Do not write imports into maintained symbol_addrs/")
        ignored = subprocess.run(["git", "-C", str(ROOT), "check-ignore", "-q", str(path)],
                                 check=False).returncode == 0
        if not ignored:
            raise ValueError("Output inside the repository must be Git-ignored for private review")
    return path


def add_symbol(symbols: dict[str, int], name: str, address: object) -> None:
    if not NAME.fullmatch(name) or isinstance(address, bool):
        raise ValueError(f"Invalid symbol {name!r}")
    number = int(address, 0) if isinstance(address, str) else address
    if not isinstance(number, int) or not 0 <= number <= 0xFFFFFFFF:
        raise ValueError(f"Invalid address for {name!r}")
    if name in symbols and symbols[name] != number:
        raise ValueError(f"Conflicting addresses for {name!r}")
    symbols[name] = number


def candidate_symbols(data: dict, target: dict) -> dict[str, int]:
    if (data.get("target") != target["serial"] or
            data.get("reference_sha256") != target["boot"]["sha256"]):
        raise ValueError("Candidate metadata must identify the pinned USA v1.01 boot")
    symbols: dict[str, int] = {}
    for entry in data.get("functions", []):
        add_symbol(symbols, entry["symbol"], entry["address"])
    if not symbols:
        raise ValueError("No candidate symbols found")
    return symbols


def write_review(path: Path, symbols: dict[str, int], provenance: str) -> None:
    path = review_output(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("x", encoding="utf-8", newline="\n") as stream:
        stream.write(f"# PRIVATE REVIEW ONLY; no matching credit or maintained-map update\n# {provenance}\n\n")
        for name, address in sorted(symbols.items()):
            stream.write(f"{name} = 0x{address:08x};\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--input", type=Path, default=ROOT / "progress/candidates.json")
    parser.add_argument("--region", required=True, choices=("ntsc-u",),
                        help="Candidate metadata is USA v1.01 only; no PAL/v2 address inference")
    parser.add_argument("--output", type=Path, required=True, help="Unused private review file")
    args = parser.parse_args()
    output = review_output(args.output)
    raw = args.input.read_bytes()
    target = json.loads((ROOT / "config/target.json").read_bytes())
    symbols = candidate_symbols(json.loads(raw), target)
    write_review(output, symbols, f"region=ntsc-u; input_sha256={hashlib.sha256(raw).hexdigest()}; "
                 f"boot_sha256={target['boot']['sha256']}")
    print(f"Wrote {len(symbols)} symbols for private review to {output}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError, TypeError) as error:
        raise SystemExit(f"Symbol export failed: {error}")
