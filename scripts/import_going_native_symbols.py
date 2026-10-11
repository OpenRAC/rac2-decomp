#!/usr/bin/env python3
"""Read pinned Going Native symbol names into an explicit private review file.

Going Native's USA release is v2.00. Its addresses must never replace USA v1.01
maps. Only structural names and addresses are imported, not comments or code.
"""
from __future__ import annotations

import argparse
import hashlib
import re
import urllib.request
from pathlib import Path

from import_symbol_addrs import add_symbol, review_output, write_review

REPOSITORY = "Promises/RC2-Going-Decompiled"
REGIONS = {"usa-v2": "usa", "eu": "eu"}
SYMBOL = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9a-fA-F]+)\s*;", re.ASCII)


def source_url(revision: str, region: str) -> str:
    if not re.fullmatch(r"[0-9a-fA-F]{40}", revision):
        raise ValueError("Supply the full upstream commit SHA, never a mutable branch or tag")
    if region not in REGIONS:
        raise ValueError("Upstream symbols belong to usa-v2 or eu, never USA v1.01")
    return (f"https://raw.githubusercontent.com/{REPOSITORY}/{revision.lower()}/"
            f"going-decompiled/symbol_addrs/{REGIONS[region]}/symbol_addrs.txt")


def parse_symbols(text: str) -> dict[str, int]:
    symbols: dict[str, int] = {}
    for line in text.splitlines():
        match = SYMBOL.match(line)
        if match:
            add_symbol(symbols, match[1], match[2])
    if not symbols:
        raise ValueError("No upstream symbol definitions found")
    return symbols


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--revision", required=True, help="Full immutable upstream commit SHA")
    parser.add_argument("--region", required=True, choices=tuple(REGIONS))
    parser.add_argument("--output", required=True, type=Path, help="Unused private review file")
    args = parser.parse_args()
    output = review_output(args.output)
    url = source_url(args.revision, args.region)
    with urllib.request.urlopen(url, timeout=30) as response:
        raw = response.read()
    symbols = parse_symbols(raw.decode("utf-8"))
    write_review(output, symbols, f"region={args.region}; source={url}; "
                 f"source_sha256={hashlib.sha256(raw).hexdigest()}; names/addresses only")
    print(f"Wrote {len(symbols)} symbols for private review to {output}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError, TypeError) as error:
        raise SystemExit(f"Upstream symbol import failed: {error}")
