#!/usr/bin/env python3
"""Heuristic deduplicated size estimate for the accepted USA v1.01 target, as a decomp.dev report.

The loaded-byte total (boot plus 27 overlays, about 48.8 MB) counts engine code once per overlay. This
tool estimates structural repetition. It is an ESTIMATE, not a progress denominator: functions
are grouped by a digest of their words with relocatable fields masked by a register-tracking heuristic
(``jal``/``j`` targets, ``lui`` immediates, ``addiu``/``ori`` immediates and load/store offsets fed by a
``lui`` or ``$gp``). This destructive mask also erases non-address constants built with ``lui``,
member offsets and call identities; equal digests do not establish equivalent functions.
Boundaries are the heuristic discovery of ``function_size_rank.py``.

No matching credit is reported. Neither candidate matches nor accepted integration proofs can prove
that every body collapsed by this mask is equivalent. All matched/complete measures are zero solely
to represent unavailable credit in the objdiff schema; they are not official progress measurements.

``catalog`` (private input: the reference ``setup.py`` prepared) writes digests of structure only to
``config/estimates/ntsc-u.json``; ``report`` (CI-safe) turns it into an objdiff report v2.

    python scripts/unique_estimate.py catalog --reference <runtime>/runs/<run>/reference --elf baserom/SCUS_972.68
    python scripts/unique_estimate.py report --output build/decomp/unique-estimate-report.json
"""
from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import function_size_rank as rank  # noqa: E402
import region as regions  # noqa: E402

REGION = "ntsc-u"
ESTIMATE = ROOT / "config/estimates/ntsc-u.json"
LUI = 0x0F
ADDR_ALU = {0x08, 0x09, 0x0D, 0x19}  # addi addiu ori daddiu: propagate an address register
OTHER_ALU = {0x0A, 0x0B, 0x0C, 0x0E, 0x18}
MEM = set(range(0x20, 0x30)) | {0x1A, 0x1B, 0x1E, 0x1F, 0x31, 0x36, 0x37, 0x39, 0x3E, 0x3F}
LOADS = set(range(0x20, 0x28)) | {0x1A, 0x1B, 0x1E, 0x37}
GP = 28


def normalise(words: list[int]) -> list[int]:
    """Destructively mask address-like fields, including some constants and member offsets."""
    tracked: set[int] = set()
    out = []
    for w in words:
        op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op in (2, 3):
            w = op << 26
        elif op == LUI:
            tracked.add(rt)
            w &= 0xFFFF0000
        elif op in ADDR_ALU:
            if rs in tracked or rs == GP:
                tracked.add(rt)
                w &= 0xFFFF0000
            else:
                tracked.discard(rt)
        elif op in OTHER_ALU:
            tracked.discard(rt)
        elif op in MEM:
            if rs in tracked or rs == GP:
                w &= 0xFFFF0000
            if op in LOADS:
                tracked.discard(rt)
        elif op == 0:
            tracked.discard((w >> 11) & 31)
        out.append(w)
    return out


def digest(words: list[int]) -> str:
    return hashlib.sha1(struct.pack(f"<{len(words)}I", *normalise(words))).hexdigest()


def code_words(elf: bytes) -> dict[int, list[int]]:
    return {base: words for base, words in rank.load_code_ranges(elf)}


def slice_words(ranges: dict[int, list[int]], address: int, size: int) -> list[int] | None:
    for base, words in ranges.items():
        if base <= address and address + size <= base + len(words) * 4:
            i = (address - base) // 4
            return words[i:i + size // 4]
    return None


def extents(ranges: dict[int, list[int]]) -> list[tuple[int, int]]:
    """Function extents of one image (heuristic discovery, clipped so they never overlap)."""
    rows = []
    for base, words in ranges.items():
        end = base + len(words) * 4
        starts = [s for s in rank.discover_starts([(base, words)], {}) if base <= s < end]
        for i, start in enumerate(starts):
            nxt = starts[i + 1] if i + 1 < len(starts) else end
            size = rank.trim_size(words, base, start, nxt)
            if size >= 8:
                rows.append((start, min(size, nxt - start)))
    return rows


def object_cuts(ranges: dict[int, list[int]]) -> list[int]:
    """Start of every object after a run of 0xCDCDCDCD, the linker's fill between retail objects."""
    cuts = []
    for base, words in ranges.items():
        i = 0
        while i < len(words):
            if words[i] == 0xCDCDCDCD:
                j = i
                while j < len(words) and words[j] == 0xCDCDCDCD:
                    j += 1
                if j < len(words):
                    cuts.append(base + j * 4)
                i = j
            else:
                i += 1
    return cuts


def build_catalog(reference: Path, elf: Path) -> dict:
    region = regions.load(REGION)
    boot_bytes = elf.read_bytes()
    if hashlib.sha256(boot_bytes).hexdigest() != region.target["boot"]["sha256"]:
        raise SystemExit("ELF is not the pinned USA v1.01 boot executable")
    boot_ranges = code_words(boot_bytes)
    images = [("boot", boot_ranges)]
    for row in region.overlays["levels"]:
        path = reference / "levels" / row["level"] / "overlay.elf"
        overlay = path.read_bytes()
        if hashlib.sha256(overlay).hexdigest() != row["sha256"]:
            raise SystemExit(f"Overlay {row['level']} is not the pinned USA v1.01 reference")
        images.append((row["level"], code_words(overlay)))
    per_image = {}
    holders: dict[str, set[str]] = {}
    for name, ranges in images:
        rows = []
        for address, size in extents(ranges):
            d = digest(slice_words(ranges, address, size))
            rows.append((address, size, d))
            holders.setdefault(d, set()).add(name)
        per_image[name] = rows
    physical = {n: sum(r[1] for r in rows) for n, rows in per_image.items()}
    functions = {"boot": [], "shared": {}, "specific": {}}
    seen: set[str] = set()
    for address, size, d in per_image["boot"]:
        if d in seen:
            continue
        seen.add(d)
        functions["boot"].append([address, size, 0])
    for name, rows in per_image.items():
        if name == "boot":
            continue
        for address, size, d in rows:
            if d in seen:
                continue
            seen.add(d)
            kind = "shared" if len(holders[d] - {"boot"}) > 1 else "specific"
            functions[kind].setdefault(name, []).append([address, size, 0])
    return {"schema": 2, "target": region.serial, "version": "1.01", "heuristic": True,
            "matching_credit": "none",
            "boot_sha256": region.target["boot"]["sha256"],
            "overlay_sha256": {r["level"]: r["sha256"] for r in region.overlays["levels"]},
            "physical_code_bytes": physical, "boot_object_starts": sorted(object_cuts(boot_ranges)),
            "boot_code_sections": [[b, len(w) * 4] for b, w in boot_ranges.items()],
            "functions": functions,
            "note": "Structural estimate only. A destructive mask merges some different constants, member offsets "
                    "and call targets. Shared = a digest present in two or more overlays, specific = in one. "
                    "Matching credit is unavailable; all credit flags are zero. No bytes are stored."}


def level_title(level: str) -> str:
    number, _, name = level.partition("_")
    return f"Level {int(number):02d}: {name.replace('_', ' ').title()}"


def measures(code: int, matched: int, funcs: int, matched_funcs: int, units: int, complete_units: int) -> dict:
    pct = matched / code * 100 if code else 0
    fpct = matched_funcs / funcs * 100 if funcs else 0
    return {"fuzzyMatchPercent": pct, "totalCode": str(code), "matchedCode": str(matched), "matchedCodePercent": pct,
            "totalFunctions": funcs, "matchedFunctions": matched_funcs, "matchedFunctionsPercent": fpct,
            "completeCode": str(matched), "completeCodePercent": pct, "totalUnits": units, "completeUnits": complete_units,
            "totalData": "0", "matchedData": "0", "matchedDataPercent": 0, "completeData": "0", "completeDataPercent": 0}


def known_names() -> dict[int, str]:
    entry = regions.registry()["regions"][REGION]
    return {a: n for a, (n, _) in rank.read_symbols(ROOT / entry["symbols"]).items()} if entry.get("symbols") else {}


NAMES: dict[int, str] = {}
OVERLAY_NAMES: dict[str, dict[int, str]] = {}


def overlay_names() -> dict[str, dict[int, str]]:
    path = ROOT / "config/datamine/ntsc-u-overlay-names.tsv"
    out: dict[str, dict[int, str]] = {}
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            cols = line.split("\t")
            if len(cols) == 4 and not line.startswith("#"):
                out.setdefault(cols[0], {})[int(cols[1], 16)] = cols[2]
    return out


def unit(name: str, rows: list[list[int]], categories: list[str], named: bool = False, local: dict[int, str] | None = None) -> dict:
    # Legacy catalogues stored unpinned credit flags. Never consume them, even if nonzero.
    done = 0
    total = sum(r[1] for r in rows)
    return {"name": name, "measures": measures(total, done, len(rows), 0, 1, 0),
            "sections": [{"name": ".text", "size": str(total), "fuzzyMatchPercent": done / total * 100 if total else 0}],
            "functions": [{"name": (NAMES.get(r[0]) if named else (local or {}).get(r[0])) or f"func_{r[0]:08X}", "size": str(r[1]), "fuzzyMatchPercent": 0.0,
                           "metadata": {"virtualAddress": str(r[0])}} for r in rows],
            "metadata": {"complete": False, "autoGenerated": True, "progressCategories": categories,
                         "heuristic": True, "matchingCredit": "none"}}


def boot_units(catalog: dict, overrides: list[tuple[int, str]]) -> list[dict]:
    """Boot objects: starts after linker fill, plus optional contributor-named rows of config/segments."""
    cuts = sorted(set(catalog["boot_object_starts"]) | {a for a, _ in overrides} | {b for b, _ in catalog["boot_code_sections"]})
    names = {a: n for a, n in overrides}
    rows = sorted(catalog["functions"]["boot"])
    out = []
    first_section_end = min(catalog["boot_code_sections"])[0] + min(catalog["boot_code_sections"])[1]
    for i, cut in enumerate(cuts):
        end = cuts[i + 1] if i + 1 < len(cuts) else 1 << 32
        chunk = [r for r in rows if cut <= r[0] < end]
        if chunk:
            group = "core" if cut < first_section_end else "game"
            out.append(unit(f"{group}/{names.get(cut, f'{cut:08X}')}", chunk, ["executable", group], named=True))
    return out


def build_report(catalog: dict, overrides: list[tuple[int, str]] | None = None, names: dict[int, str] | None = None) -> dict:
    NAMES.clear()
    OVERLAY_NAMES.clear()
    OVERLAY_NAMES.update(overlay_names())
    NAMES.update(names or {})
    units = boot_units(catalog, overrides or [])
    levels = sorted(catalog["physical_code_bytes"].keys() - {"boot"}, key=lambda n: int(n.split("_")[0]))
    for level in levels:
        for kind, group in (("shared", "common"), ("specific", "levels")):
            rows = catalog["functions"][kind].get(level, [])
            if rows:
                cats = ["level_code", group] if kind == "shared" else ["level_code", group, f"level_{int(level.split('_')[0]):02d}"]
                units.append(unit(f"{'shared' if kind == 'shared' else 'levels'}/{level}", rows, cats, local=OVERLAY_NAMES.get(level)))
    cats = []
    names = [("executable", "Executable"), ("core", "Executable core code"), ("game", "Executable game code"), ("level_code", "Level code"),
             ("common", "Shared level code"), ("levels", "Level-specific code")]
    names += [(f"level_{int(l.split('_')[0]):02d}", level_title(l)) for l in levels]
    for cid, title in names:
        sub = [u for u in units if cid in u["metadata"]["progressCategories"]]
        if sub:
            cats.append({"id": cid, "name": title, "measures": measures(
                sum(int(u["measures"]["totalCode"]) for u in sub), sum(int(u["measures"]["matchedCode"]) for u in sub),
                sum(u["measures"]["totalFunctions"] for u in sub), sum(u["measures"]["matchedFunctions"] for u in sub),
                len(sub), sum(u["measures"]["completeUnits"] for u in sub))})
    total = sum(int(u["measures"]["totalCode"]) for u in units)
    done = sum(int(u["measures"]["matchedCode"]) for u in units)
    return {"version": 2, "measures": measures(total, done, sum(u["measures"]["totalFunctions"] for u in units),
                                               sum(u["measures"]["matchedFunctions"] for u in units), len(units),
                                               sum(u["measures"]["completeUnits"] for u in units)),
            "units": units, "categories": cats,
            "metadata": {"heuristic": True, "matchingCredit": "none",
                         "note": "Structural size estimate; zero matched measures mean unavailable credit, not official progress."}}


def read_overrides() -> list[tuple[int, str]]:
    path = ROOT / "config/segments/ntsc-u-boot.tsv"
    rows = []
    if path.exists():
        for line in path.read_text(encoding="utf-8").splitlines():
            if line.strip() and not line.startswith("#"):
                address, name = line.split()[:2]
                rows.append((int(address, 0), name))
    objects = ROOT / "config/datamine/ntsc-u-sdk-objects.tsv"
    if objects.exists():  # SDK library objects located by match_sdk_libs.py; explicit rows above win
        named = {a for a, _ in rows}
        for line in objects.read_text(encoding="utf-8").splitlines():
            if line and not line.startswith("#"):
                start, end, _, member, _ = line.split("\t")
                stem = member.rsplit(".", 1)[0]
                for address, name in ((int(start, 16), f"lib_{stem}"), (int(end, 16), f"{int(end, 16):08X}")):
                    if address not in named:
                        rows.append((address, name))
                        named.add(address)
    return rows


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("catalog")
    c.add_argument("--reference", type=Path, required=True)
    c.add_argument("--elf", type=Path, default=rank.DEFAULT_ELF)
    r = sub.add_parser("report")
    r.add_argument("--output", type=Path, required=True)
    args = ap.parse_args()
    if args.cmd == "catalog":
        ESTIMATE.parent.mkdir(parents=True, exist_ok=True)
        ESTIMATE.write_bytes((json.dumps(build_catalog(args.reference, args.elf), separators=(",", ":")) + "\n").encode("utf-8"))
        print(f"wrote {ESTIMATE.relative_to(ROOT)}")
        return 0
    report = build_report(json.loads(ESTIMATE.read_text(encoding="utf-8")), read_overrides(), known_names())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report) + "\n", encoding="utf-8")
    m = report["measures"]
    print(f"{m['totalCode']} estimated structural code bytes, {m['totalFunctions']} groups, "
          f"{m['totalUnits']} units [destructive heuristic; matching credit unavailable]")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
