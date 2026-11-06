#!/usr/bin/env python3
"""
How much of the game's code is C: progress/report.json, in objdiff's report format (the one
ByteMatch reads, as rac1-decomp's), and the table in README.md.

  python3 tools/progress.py            # write both, after tools/build.py all (maintainers, on master)
  python3 tools/progress.py --check    # the report counts nothing that is not C; it may be behind
  python3 tools/progress.py --check --strict   # and it is not behind either
  python3 tools/progress.py --version pal      # another release's (pal, us2): progress/<version>/report.json

  python3 tools/progress.py           # after tools/build.py all
  python3 tools/progress.py --check   # CI: fail if src/ and the committed report disagree

Every distinct function counts once: the boot executable's functions, and each level function
of config/levels/functions.tsv that the boot does not also have (a function many levels share
is one function). A function is matched when its C linked into at least one program that came
out equal to the retail one (build/<program>/placed.json, written by tools/build.py).

Units and categories are rac1-decomp's: one unit per file of the boot (core/, game/), one for the
shared level code, one unit per level with all of that level's own functions; categories for the
boot executable, the level code, the shared and the level-specific code, and each level. A unit is
complete when every one of its functions is matched; the complete ("linked") code of the total and
of each category is the code of its complete units, summed as objdiff sums it, so it grows as units
are finished. src/ holds only C that links (a near miss goes to nonmatching/), so
--check, which needs neither the toolchain nor the game, requires the functions src/ has as C to be
exactly the report's matched ones.
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import levels  # noqa: E402

REPORT = ROOT / "progress/report.json"
NAME = r"(?:func_(?:(?:PAL|US2)_)?(?:L\d\d_)?[0-9A-F]{8}|sceIpuRestartDMA|_sysbitFlush)"
OTHER = {v for v in levels.VERSIONS if v != "us"}     # src/<version>/: another release's own C


def source_files(version: str = "us") -> list[Path]:
    """src/'s C of VERSION: everything outside the other releases' src/<version>/, and for
    another release its own src/<version>/ too."""
    out = []
    for path in sorted((ROOT / "src").rglob("*.c")):
        top = path.relative_to(ROOT / "src").parts[0]
        if top not in OTHER or top == version:
            out.append(path)
    return out
DEFINITION = re.compile(rf"^(?:[A-Za-z_][^;=#]*?\b)?({NAME})\s*\(")
MARKER = re.compile(rf'^(?:INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT)\("[^"]*",\s*({NAME})\);')


def source_functions(version: str = "us") -> dict[str, list[tuple[str, bool]]]:
    """src/ file -> [(function, has C)] in file order."""
    out = {}
    for path in source_files(version):
        found = []
        for line in path.read_text(errors="replace").splitlines():
            m = MARKER.match(line)
            if m:
                found.append((m.group(1), False))
                continue
            m = DEFINITION.match(line)
            if m and not line.rstrip().endswith(";") and not line.startswith(("extern", "typedef")):
                found.append((m.group(1), True))
        out[path.relative_to(ROOT).as_posix()] = found
    return out


HANDWRITTEN = re.compile(rf'^ASM_FUNC\("[^"]*",\s*({NAME})\);', re.M)


def handwritten(version: str = "us") -> set[str]:
    """Functions marked ASM_FUNC: assembly in the original too (VU0 and other routines no C
    compiles to), kept as assembly and counted as finished, as rac1-decomp counts them."""
    return {n for path in source_files(version) for n in HANDWRITTEN.findall(path.read_text(errors="replace"))}


def measures(fns: list[dict]) -> dict:
    total = sum(f["size"] for f in fns)
    matched = sum(f["size"] for f in fns if f["matched"])
    complete = total if fns and all(f["matched"] for f in fns) else 0
    pct = lambda a, b: 100.0 * a / b if b else 0.0
    return {"fuzzy_match_percent": pct(matched, total), "total_code": str(total),
            "matched_code": str(matched), "matched_code_percent": pct(matched, total),
            "total_functions": len(fns), "matched_functions": sum(1 for f in fns if f["matched"]),
            "matched_functions_percent": pct(sum(1 for f in fns if f["matched"]), len(fns)),
            "complete_code": str(complete), "complete_code_percent": pct(complete, total)}


def complete_measures(units: list[dict]) -> dict:
    """complete_code of a total or category: the code of its complete units (objdiff-core's report
    adds the units' measures up the same way), not all or nothing over every function."""
    total = sum(int(u["measures"]["total_code"]) for u in units)
    done = sum(int(u["measures"]["total_code"]) for u in units if u["metadata"]["complete"])
    return {"complete_code": str(done), "complete_code_percent": 100.0 * done / total if total else 0.0}


def check() -> None:
    report = json.loads(REPORT.read_text())
    matched = {f["name"] for u in report["units"] for f in u["functions"] if f["fuzzy_match_percent"] == 100.0}
    c_names = {n for fns in source_functions().values() for n, c in fns if c}
    by_hand = handwritten()
    in_c = c_names | by_hand
    # Names an audited identity split retired (levels.IDENTITY_SPLITS): the report
    # keeps them until a maintainer regenerates it on master.
    renamed = {n for spec in levels.IDENTITY_SPLITS.values() for n in spec[2]}
    gone = sorted(matched - in_c - renamed)
    if gone:
        sys.exit(f"progress/report.json counts {len(gone)} function(s) that are not C in src/, e.g. "
                 f"{', '.join(gone[:5])}: run tools/build.py all, then tools/progress.py")
    ahead = sorted(in_c - matched)
    if ahead and "--strict" in sys.argv:
        sys.exit(f"progress/report.json is behind src/ by {len(ahead)} function(s), e.g. "
                 f"{', '.join(ahead[:5])}: run tools/build.py all, then tools/progress.py")
    if ahead:
        # A pull request does not carry the report: a maintainer regenerates it on master.
        print(f"progress/report.json: {len(matched)} matched functions; "
              f"{len(set(ahead) & c_names)} C and {len(set(ahead) & by_hand)} original-assembly functions "
              "await the maintainer's report refresh")
    else:
        print(f"progress/report.json is current: {len(matched)} matched functions")


# --- another release ---------------------------------------------------------------------

def release_functions() -> dict[str, tuple[int, int, str, int | None]]:
    """The selected release's distinct functions: name -> (address, size, kind, level). The
    boot's (kind "boot", level None) and each level function the boot does not have."""
    out = {n: (a, s, "boot", None) for n, a, s in levels.read_boot_functions()}
    for name, kind, size, _, places in levels.read_catalogue():
        if kind != "boot":
            out[name] = (places[0][1], size, kind, places[0][0])
    return out


def release_report(version: str) -> dict:
    """objdiff's report for another release (pal, us2), from its catalogues, src/ and its
    build (build/<version>/<program>/placed.json). Units: one per file of the boot's C (src/
    and src/<version>/), "Shared level code", one per level; the categories are v1.01's."""
    import json as _json
    placed, differ = set(), set()
    programs = ["boot"] + [levels.level_dir(n) for n in sorted(levels.NAMES)]
    for program in programs:
        path = levels.build_dir() / program / "placed.json"
        if not path.is_file():
            sys.exit(f"no build of {version} {program}: run tools/build.py all --version {version} first")
        result = _json.loads(path.read_text())
        placed |= set(result["functions"])
        differ |= set(result["differ"])
    placed -= differ
    where = release_functions()
    file_of, has_c = {}, set()
    for path, fns in source_functions(version).items():
        for name, c in fns:
            if name in where:
                file_of[name] = path
                if c:
                    has_c.add(name)
    by_hand = handwritten(version) & set(where)
    title = lambda number: f"Level {number:02d}: {levels.NAMES[number].replace('_', ' ').title()}"
    groups = {}
    for name, (address, size, kind, level) in where.items():
        if kind == "boot":
            path = file_of.get(name, f"src/{version}/unplaced.c")
            unit = path.removeprefix("src/").removesuffix(".c")
            cats = ["executable", "game"]
            source = path
        elif kind == "shared":
            unit, source, cats = "Shared level code", "src/levels/shared", ["level_code", "common"]
        else:
            unit, source = title(level), f"src/levels/{levels.level_dir(level)}"
            cats = ["level_code", "levels", f"level_{level:02d}"]
        g = groups.setdefault(unit, {"rows": [], "source_path": source, "categories": cats})
        g["rows"].append({"name": name, "size": size, "address": address,
                          "matched": name in has_c and name in placed or name in by_hand})
    return build_report(groups, title)


def build_report(groups: dict, title) -> dict:
    units = []
    for unit, g in sorted(groups.items()):
        rows = sorted(g["rows"], key=lambda r: r["address"])
        base = rows[0]["address"]
        m = measures(rows)
        units.append({"name": unit,
                      "measures": {**m, "total_units": 1, "complete_units": int(m["complete_code"] == m["total_code"])},
                      "functions": [{"name": r["name"], "size": str(r["size"]),
                                     "fuzzy_match_percent": 100.0 if r["matched"] else 0.0,
                                     "address": str(r["address"] - base),
                                     "metadata": {"virtual_address": str(r["address"])}} for r in rows],
                      "metadata": {"complete": m["complete_code"] == m["total_code"],
                                   "source_path": g["source_path"], "progress_categories": g["categories"]},
                      "_rows": rows, "_category": g["categories"]})
    allrows = [r for u in units for r in u["_rows"]]
    wanted = [("executable", "Boot executable"), ("level_code", "Level code"), ("game", "Boot game code"),
              ("common", "Shared level code"), ("levels", "Level-specific code")]
    wanted += [(f"level_{n:02d}", title(n)) for n in sorted(levels.NAMES)]
    cats = []
    for cid, cname in wanted:
        members = [u for u in units if cid in u["_category"]]
        rows = [r for u in members for r in u["_rows"]]
        cats.append({"id": cid, "name": cname,
                     "measures": measures(rows) | complete_measures(members)})
    total = measures(allrows) | complete_measures(units)
    total.update({"total_units": len(units), "complete_units": sum(u["measures"]["complete_units"] for u in units)})
    for u in units:
        del u["_rows"], u["_category"]
    return {"version": 2, "measures": total, "categories": cats, "units": units}


def pending_boot_split(functions: list[dict], where: dict,
                       main: str = "func_00131D98", sound: str = "func_00131DE8",
                       head_size: int = 80, tail_size: int = 576) -> bool:
    """Recognize an unmatched report row predating a named, measured boot split.

    The catalogue repair validates the retail bodies. Without game data, CI can
    check the exact old/new names, boot extents and virtual address; it never
    rewrites the report or turns the old merged row into matching credit.
    """
    reported = {f["name"] for f in functions}
    # Validate this split independently; release_check requires the union of
    # all verified splits to explain every missing identity, without extras.
    if sound not in where or sound in reported or main not in where:
        return False
    address, size, kind, level = where[main]
    if ((size, kind, level) != (head_size, "boot", None)
            or where[sound] != (address + head_size, tail_size, "boot", None)):
        return False
    old = [f for f in functions if f["name"] == main]
    if len(old) != 1 or old[0]["fuzzy_match_percent"] != 0.0:
        return False
    try:
        return (old[0]["size"] == str(head_size + tail_size)
                and old[0]["metadata"]["virtual_address"] == str(address))
    except (KeyError, TypeError):
        return False


def pending_level_splits(functions: list[dict], where: dict) -> set[str] | None:
    """Missing identities explained by the exact old, wholly unmatched level rows.

    Catalogue generation checks the retail bodies and typed dispatch witnesses.
    CI checks the old/new extent graph without game data or report mutations.
    None denotes an invalid merged row, including one alongside reported children.
    """
    reported = {f["name"]:f for f in functions}
    missing = set()
    for name, spec in levels.LEVEL_FUNCTION_SPLITS.items():
        parts = spec[-1]
        old = reported.get(name)
        if not old or name not in where or old.get("size") != str(sum(n for _, n in parts)):
            continue
        address, _, kind, level = where[name]
        if old["fuzzy_match_percent"] != 0.0 or kind != spec[1]:
            return None
        try:
            if old["metadata"]["virtual_address"] != str(address):
                return None
        except (KeyError, TypeError):
            return None
        offset = 0
        for child, length in parts:
            if where.get(child) != (address + offset, length, kind, level):
                return None
            if child != name:
                if child in reported:
                    return None
                missing.add(child)
            offset += length
    return missing


def pending_release_splits(functions: list[dict], where: dict) -> set[str] | None:
    """Missing names explained by the exact old, wholly unmatched rows of a release's splits
    (levels.RELEASE_FUNCTION_SPLITS, levels.RELEASE_PLACE_SPLITS). None denotes an invalid
    old row, or a split whose new rows are not where the catalogues should have them."""
    reported = {f["name"]:f for f in functions}
    missing = set()
    for name, (size, parts) in levels.RELEASE_FUNCTION_SPLITS.items():
        old = reported.get(name)
        if not old or name not in where or old.get("size") != str(size):
            continue
        address, _, kind, level = where[name]
        if old["fuzzy_match_percent"] != 0.0:
            return None
        for part, offset, length in parts:
            if where.get(part) != (address + offset, length, kind, level):
                return None
            if part != name:
                if part in reported:
                    return None
                missing.add(part)
    for name, (_, _, child, _) in levels.RELEASE_PLACE_SPLITS.items():
        old = reported.get(name)
        if not old or name not in where or child not in where or child in reported:
            continue
        if old["fuzzy_match_percent"] != 0.0 or where[child][1] != where[name][1]:
            return None
        missing.add(child)
    return missing


def demoted_renames(version: str, functions: list, retired: set, missing: set, where: dict) -> dict:
    """Retired report rows that tools/carry.py --demote renamed for the release: each is
    listed in config/<version>/not_carried.tsv, is unmatched in the report, and has exactly
    one missing catalogue row of the release's own name at its reported address."""
    path = ROOT / levels.VERSIONS[version]["config"] / "not_carried.tsv"
    listed = set()
    if path.is_file():
        listed = {line.split("\t", 1)[0] for line in path.read_text().splitlines()
                  if line and not line.startswith("#")}
    prefix = f"func_{levels.VERSIONS[version]['tag']}_"
    out = {}
    for f in functions:
        name = f["name"]
        if name not in retired or name not in listed or f["fuzzy_match_percent"] != 0.0:
            continue
        address = f.get("metadata", {}).get("virtual_address")
        if address is None:
            continue
        found = [m for m in missing if m.startswith(prefix) and where[m][0] == int(address)]
        if len(found) == 1:
            out[name] = found[0]
    return out


def release_check(version: str, report_path: Path) -> None:
    """CI's check for another release, without the disc: the report counts only functions of
    the release's catalogues that are C (or ASM_FUNC) in src/ and src/<version>/, and every
    function of src/<version>/ is in its catalogues."""
    report = json.loads(report_path.read_text())
    where = release_functions()
    matched = {f["name"] for u in report["units"] for f in u["functions"] if f["fuzzy_match_percent"] == 100.0}
    c_names = {n for fns in source_functions(version).values() for n, c in fns if c}
    by_hand = handwritten(version)
    in_c = c_names | by_hand
    renamed = {n for spec in levels.IDENTITY_SPLITS.values() for n in spec[2]}
    gone = sorted(matched - (in_c & set(where)) - renamed)
    if gone:
        sys.exit(f"{report_path.relative_to(ROOT)} counts {len(gone)} function(s) that are not C in src/, e.g. "
                 f"{', '.join(gone[:5])}: run tools/build.py all --version {version}, then tools/progress.py --version {version}")
    total = sum(len(u["functions"]) for u in report["units"])
    functions = [f for u in report["units"] for f in u["functions"]]
    reported = {f["name"] for f in functions}
    retired = reported - set(where)
    missing = set(where) - reported
    split = pending_boot_split(functions, where)
    assertion_split = pending_boot_split(functions, where, "func_00115E28", "func_00115E38", 16, 48)
    if total != len(reported):
        sys.exit(f"{report_path.relative_to(ROOT)} has duplicate function rows")
    level_splits = pending_level_splits(functions, where)
    if level_splits is None:
        sys.exit(f"{report_path.relative_to(ROOT)} has an invalid merged level row")
    release_splits = pending_release_splits(functions, where)
    if release_splits is None:
        sys.exit(f"{report_path.relative_to(ROOT)} has an invalid merged release row")
    if "func_00131DE8" in where and not split and any(
            f["name"] == "func_00131D98" and f.get("size") == "656" for f in functions):
        sys.exit(f"{report_path.relative_to(ROOT)} has an invalid merged main/sound row")
    if "func_00115E38" in where and not assertion_split and any(
            f["name"] == "func_00115E28" and f.get("size") == "64" for f in functions):
        sys.exit(f"{report_path.relative_to(ROOT)} has an invalid merged abort/assertion row")
    if total != len(where) or retired or missing:
        # Boundary-only PRs leave the reports for a maintainer's later refresh.
        # Only measured unmatched remnants or the named unmatched merged rows
        # are tolerated. Unknown missing entries and duplicate compensation fail.
        explained = (level_splits | release_splits | ({"func_00131DE8"} if split else set())
                     | ({"func_00115E38"} if assertion_split else set()))
        # A name retired by an audited identity split explains its unreported parts.
        explained |= {n for spec in levels.IDENTITY_SPLITS.values() if set(spec[2]) & retired
                      for n, _ in spec[1] if n not in reported}
        # A demoted v1.01 name (config/<version>/not_carried.tsv), unmatched in the report,
        # explains exactly one missing release-named row at the same address.
        demoted = demoted_renames(version, functions, retired, missing, where)
        explained |= set(demoted.values())
        # Measured residues may retire in the same tree as exactly explained splits, and so
        # may the miscut rows a realigned stretch replaces (levels.RELEASE_PLACE_RUNS).
        realigned = {n for spec in levels.RELEASE_PLACE_RUNS.values() for n in spec[2]}
        known_split = bool(missing) and missing == explained
        known_boundary = ((retired or known_split)
                          and retired <= set(levels.FUNCTION_RESIDUES) | renamed | set(demoted) | realigned
                          and (not missing or known_split)
                          and total == len(where) + len(retired) - len(missing)
                          and all(f["fuzzy_match_percent"] == 0.0 for f in functions
                                  if f["name"] in retired - renamed))
        if not known_boundary or "--strict" in sys.argv:
            sys.exit(f"{report_path.relative_to(ROOT)} has {total} functions, the catalogues {len(where)}: "
                     f"regenerate it with tools/progress.py --version {version}")
        if retired:
            print(f"{report_path.relative_to(ROOT)} retains {len(retired)} unmatched catalogue remnants; "
                  "a maintainer regenerates it on master")
        if split:
            print(f"{report_path.relative_to(ROOT)} retains the unmatched merged main/sound row; "
                  "a maintainer regenerates it on master")
        if assertion_split:
            print(f"{report_path.relative_to(ROOT)} retains the unmatched merged abort/assertion row; "
                  "a maintainer regenerates it on master")
        if level_splits:
            print(f"{report_path.relative_to(ROOT)} predates {len(level_splits)} witnessed level entries; "
                  "a maintainer regenerates it on master")
    ahead = sorted((in_c & set(where)) - matched)
    if ahead and "--strict" in sys.argv:
        sys.exit(f"{report_path.relative_to(ROOT)} is behind src/ by {len(ahead)} function(s), e.g. {', '.join(ahead[:5])}")
    print(f"{report_path.relative_to(ROOT)}: {len(matched)} matched functions"
          + (f"; {len(set(ahead) & c_names)} C and {len(set(ahead) & by_hand)} original-assembly functions "
             "await the maintainer's report refresh" if ahead else
             ", matching credit current" if retired else ", current"))


def release_table(version: str, report: dict) -> None:
    """The release's line in docs/VERSIONS.md's table of totals."""
    doc = ROOT / "docs/VERSIONS.md"
    if not doc.is_file():
        return
    m = report["measures"]
    cats = {c["id"]: c["measures"] for c in report["categories"]}
    v = levels.VERSIONS[version]
    line = (f"| `{v['id']}` | {v['release']} | {m['matched_functions']:,} of {m['total_functions']:,} | "
            f"{int(cats['executable']['matched_code']):,} of {int(cats['executable']['total_code']):,} | "
            f"{int(cats['level_code']['matched_code']):,} of {int(cats['level_code']['total_code']):,} | "
            f"{int(m['matched_code']):,} of {int(m['total_code']):,} ({m['matched_code_percent']:.2f}%) |")
    text = doc.read_text()
    marker = f"| `{v['id']}` |"
    lines = [line if l.startswith(marker) else l for l in text.splitlines()]
    doc.write_text("\n".join(lines) + "\n")



def sync_check() -> None:
    """The releases agree: a function every release has (the same code, one name, one
    definition in src/) is matched in all of their reports or in none. Fails listing the
    functions one report counts and another does not; without the disc."""
    current = levels.VERSION
    status = {}
    for version, v in levels.VERSIONS.items():
        path = ROOT / v["report"]
        if not path.is_file():
            continue
        levels.select(version)
        names = set(release_functions())
        report = json.loads(path.read_text())
        matched = {f["name"] for u in report["units"] for f in u["functions"] if f["fuzzy_match_percent"] == 100.0}
        status[version] = (names, matched)
    levels.select(current)
    problems = []
    for a in status:
        for b in status:
            if a < b:
                common = status[a][0] & status[b][0]
                one = sorted((status[a][1] ^ status[b][1]) & common)
                if one:
                    problems.append(f"{a} and {b} disagree on {len(one)} function(s) both have, e.g. {', '.join(one[:6])}")
    if problems:
        sys.exit("the releases' reports are out of step (rebuild every release and regenerate "
                 "every report: docs/VERSIONS.md):\n  " + "\n  ".join(problems))
    print(f"the reports of {', '.join(status)} agree on every function they share")


def main() -> None:
    version = levels.version_argument()
    if version != "us":
        path = ROOT / levels.VERSIONS[version]["report"]
        if "--check" in sys.argv:
            release_check(version, path)
            sync_check()
            return
        report = release_report(version)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(json.dumps(report, indent=1) + "\n")
        release_table(version, report)
        m = report["measures"]
        print(f"{version}: {m['matched_functions']} of {m['total_functions']} functions, {m['matched_code']} of "
              f"{m['total_code']} bytes ({m['matched_code_percent']:.2f}%)")
        return
    if "--check" in sys.argv:
        check()
        sync_check()
        return
    placed, differ = set(), set()
    programs = ["boot"] + [levels.level_dir(n) for n in sorted(levels.NAMES)]
    for program in programs:
        path = ROOT / "build" / program / "placed.json"
        if not path.is_file():
            sys.exit(f"no build of {program}: run tools/build.py all first")
        result = json.loads(path.read_text())
        placed |= set(result["functions"])
        differ |= set(result["differ"])
    placed -= differ      # a function counts when it links at every place it has, not at some
    where = {n: (a, s) for n, a, s in levels.read_boot_functions()}
    for name, kind, size, _, places in levels.read_catalogue():
        if kind != "boot":
            where[name] = (places[0][1], size)
    # Units as rac1-decomp's report has them: one per file of the boot (core/, game/), one for the
    # shared level code ("Shared level code") and one per level holding all of that level's own
    # functions ("Level 04: Barlow").
    title = lambda number: f"Level {number:02d}: {levels.NAMES[number].replace('_', ' ').title()}"
    groups, in_c, by_hand = {}, set(), handwritten()          # unit name -> {"rows", "source_path", "categories"}
    for path, fns in source_functions().items():
        if not fns:
            continue
        rows = []
        for name, has_c in fns:
            address, size = where[name]
            if has_c:
                in_c.add(name)
            rows.append({"name": name, "size": size, "address": address,
                         "matched": has_c and name in placed or name in by_hand})
        if path.startswith(("src/core/", "src/game/")):
            unit, source, cats_of = path.removeprefix("src/").removesuffix(".c"), path, ["executable", "game"]
        elif path.startswith("src/levels/shared/"):
            unit, source = "Shared level code", "src/levels/shared"
            cats_of = ["level_code", "common"]
        else:
            number = int(Path(path).parent.name[:2])
            unit, source = title(number), Path(path).parent.as_posix()
            cats_of = ["level_code", "levels", f"level_{number:02d}"]
        g = groups.setdefault(unit, {"rows": [], "source_path": source, "categories": cats_of})
        g["rows"] += rows
    units = []
    for unit, g in groups.items():
        rows = sorted(g["rows"], key=lambda r: r["address"])
        base = rows[0]["address"]
        m = measures(rows)
        units.append({"name": unit,
                      "measures": {**m, "total_units": 1, "complete_units": int(m["complete_code"] == m["total_code"])},
                      "functions": [{"name": r["name"], "size": str(r["size"]),
                                     "fuzzy_match_percent": 100.0 if r["matched"] else 0.0,
                                     "address": str(r["address"] - base),
                                     "metadata": {"virtual_address": str(r["address"])}} for r in rows],
                      "metadata": {"complete": m["complete_code"] == m["total_code"],
                                   "source_path": g["source_path"], "progress_categories": g["categories"]},
                      "_rows": rows, "_category": g["categories"]})
    allrows = [r for u in units for r in u["_rows"]]
    wanted = [("executable", "Boot executable"), ("level_code", "Level code"), ("game", "Boot game code"),
              ("common", "Shared level code"), ("levels", "Level-specific code")]
    wanted += [(f"level_{n:02d}", title(n)) for n in sorted(levels.NAMES)]
    cats = []
    for cid, cname in wanted:
        members = [u for u in units if cid in u["_category"]]
        rows = [r for u in members for r in u["_rows"]]
        cats.append({"id": cid, "name": cname,
                     "measures": measures(rows) | complete_measures(members)})
    total = measures(allrows) | complete_measures(units)
    total.update({"total_units": len(units), "complete_units": sum(u["measures"]["complete_units"] for u in units)})
    for u in units:
        del u["_rows"], u["_category"]
    report = {"version": 2, "measures": total, "categories": cats, "units": units}
    if in_c - placed:
        print(f"{len(in_c - placed)} functions have C in src/ that does not link: move them to nonmatching/ "
              f"({', '.join(sorted(in_c - placed)[:5])})", file=sys.stderr)
    REPORT.parent.mkdir(exist_ok=True)
    REPORT.write_text(json.dumps(report, indent=1) + "\n")
    release_table("us", report)

    # README table
    placements = sum(len(json.loads((ROOT / "build" / p / "placed.json").read_text())["functions"])
                     for p in programs[1:])
    row = lambda label, m: (f"| {label} | {m['matched_functions']:,} of {m['total_functions']:,} | "
                            f"{int(m['matched_code']):,} of {int(m['total_code']):,} bytes |")
    table = "\n".join(["| | Functions | Code |", "| --- | ---: | ---: |",
                       row("Boot executable", cats[0]["measures"]), row("Levels", cats[1]["measures"]),
                       row("**Total**", total)[:-2] + f" ({total['matched_code_percent']:.2f}%) |", "",
                       f"The 27 levels hold {sum(len(r[4]) for r in levels.read_catalogue()):,} function "
                       f"placements; C covers {placements:,} of them.",
                       f"{len(by_hand):,} of the matched functions are the original's own assembly "
                       f"(`ASM_FUNC`), kept as assembly."])
    readme = ROOT / "README.md"
    text = readme.read_text()
    a, b = text.index("<!-- progress -->") + len("<!-- progress -->"), text.index("<!-- /progress -->")
    readme.write_text(text[:a] + "\n" + table + "\n" + text[b:])
    print(f"{total['matched_functions']} of {total['total_functions']} functions, {total['matched_code']} of "
          f"{total['total_code']} bytes ({total['matched_code_percent']:.2f}%)")


if __name__ == "__main__":
    main()
