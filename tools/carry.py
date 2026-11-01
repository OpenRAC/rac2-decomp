#!/usr/bin/env python3
"""
Another release's function catalogues, carried from USA v1.01's by identical code.

  python3 tools/carry.py --version pal    # config/pal/boot/functions.tsv, config/pal/levels/functions.tsv
  python3 tools/carry.py --version us2    # config/us2/...
  python3 tools/carry.py --version pal --entries  # measured boundary repairs, existing identities
  python3 tools/carry.py --version pal --demote   # after tools/build.py all --version pal: what the build disproved

Needs the dumps of both releases (tools/levels.py dump, and with --version V). Writes the two
catalogues of release V in the formats of USA v1.01's (docs/VERSIONS.md), and
build/<V>/carry.json: which v1.01 function each of V's corresponds to and how it was found.

Every program of V is compared with the same program of v1.01, one code section at a time
(the boot's core.text and .text, a level's .text):

1. **Same code.** Each v1.01 function, in address order, is looked for in V's section: first
   where the previous one found predicts, else among the places whose first four words read
   the same, the nearest to the prediction after the previous find. It is found where V's
   words equal its own with every address masked (levels.cross_identity(): jump targets,
   address halves, $gp offsets; constants, stack slots and field offsets compared), with the
   same size. A function found takes the v1.01 cut.
2. **Changed code.** Between two finds, if V's stretch is as long as v1.01's, v1.01's cuts are
   copied to it at the same offsets (a constant differs, as 60 against 50 Hz).
3. **Other code.** A stretch of another length is cut where a function starts in V: its first
   word, every `jal` target, and the first word after a `jr $ra` and its delay slot that is
   not zero. A piece's size stops after its last return's delay slot when only zeros follow.

Then the catalogue rules of tools/levels.py apply unchanged: the linker's filler and an
epilogue's residue are not functions, and identical code (V's own levels.identity, its own
resident memory compared) is one function, the k-th copy in each level being one.

**Demotion.** `tools/carry.py --version V --demote` does not realign the release again. It
reads the release's last build, takes the functions whose C does not build to the release's
bytes, and makes them the release's own: they are listed in `config/<V>/not_carried.tsv`,
renamed for the release in the release's catalogues and given INCLUDE_ASM markers in
`src/<V>/`. The carried callers of a demoted function are demoted with it. Every other row
of the release's catalogues keeps its name, address and places.

**Names.** A function of V found as the same code as a v1.01 function takes its v1.01 name,
so the C in src/ is linked into V's programs by tools/build.py --version V at V's addresses
(the build checks every byte). Any other function is named for V: `func_<TAG>_XXXXXXXX` in
the boot and `func_<TAG>_LNN_XXXXXXXX` in the levels (TAG `PAL` or `US2`, the address V's),
and its C goes in src/<V>/.
"""
import json
import re
import struct
import sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf  # noqa: E402
import levels  # noqa: E402

JR_RA = 0x03E00008
WINDOW = 0x20000          # how far from the prediction a function is looked for
KEY = 16                  # bytes of a function's start that index its places


def boot_sections(path: Path) -> list[tuple[str, int, bytes]]:
    image = elf.read(path)
    out = []
    for s in image["sections"]:
        if s["name"] in ("core.text", ".text") and s["address"]:
            out.append((s["name"], s["address"], image["data"][s["offset"]:s["offset"] + s["size"]]))
    return out


def ident(b: bytes) -> bytes:
    return levels.cross_identity(b)


def jal_targets(data: bytes, base: int) -> set[int]:
    out = set()
    for k, x in enumerate(levels.words(data)):
        if x >> 26 == 3:
            out.add(((base + 4 * k) & 0xF0000000) | ((x & 0x3FFFFFF) << 2))
    return out


def cut(data: bytes, base: int, start: int, end: int, targets: set[int]) -> list[tuple[int, int]]:
    """Step 3: pieces of [START, END) at the places a function starts."""
    w = levels.words(data[start - base:end - base])
    starts = {start} | {t for t in targets if start < t < end}
    for k, x in enumerate(w):
        if x == JR_RA:
            j = k + 2
            while j < len(w) and w[j] == 0:
                j += 1
            if j < len(w):
                starts.add(start + 4 * j)
    starts = sorted(starts)
    pieces = []
    for a, b in zip(starts, starts[1:] + [end]):
        body = levels.words(data[a - base:b - base])
        size = len(body) * 4
        # stop after the last return's delay slot when only zeros follow it
        last = max((k for k, x in enumerate(body) if x >> 26 == 0 and x & 0x3F == 0x08), default=None)
        if last is not None and last + 2 <= len(body) and not any(body[last + 2:]):
            size = (last + 2) * 4
        if any(body[:size // 4]):
            pieces.append((a, size))
    return pieces


def align(us: tuple[int, bytes], us_ext: list[tuple[int, int, str]], v: tuple[int, bytes]) -> list[tuple]:
    """V's extents of one code section: (address, size, v1.01 name or None, how, v1.01 name of
    the function whose place it takes)."""
    ubase, udata = us
    vbase, vdata = v
    vend = vbase + len(vdata)
    index: dict[bytes, list[int]] = {}
    for k in range(0, len(vdata) - KEY + 1, 4):
        index.setdefault(ident(vdata[k:k + KEY]), []).append(vbase + k)
    target = {}
    for a, n, _ in us_ext:
        target[a] = ident(udata[a - ubase:a - ubase + n])

    def same(p: int, a: int, n: int) -> bool:
        return vbase <= p and p + n <= vend and ident(vdata[p - vbase:p - vbase + n]) == target[a]

    anchors, delta, last_end = [], vbase - ubase, vbase
    for i, (a, n, _) in enumerate(us_ext):
        predicted = a + delta
        found = None
        if predicted >= last_end and same(predicted, a, n):
            found = predicted
        elif n >= KEY:
            key = ident(udata[a - ubase:a - ubase + KEY])
            cands = [p for p in index.get(key, ()) if p >= last_end and abs(p - predicted) <= WINDOW
                     and same(p, a, n)]
            if cands and (n >= 64 or len(cands) == 1):
                found = min(cands, key=lambda p: abs(p - predicted))
        if found is not None:
            anchors.append((i, found))
            delta, last_end = found - a, found + n
    targets = jal_targets(vdata, vbase)
    out = []
    bounds = [(-1, ubase, vbase)] + [(i, us_ext[i][0], p) for i, p in anchors] + \
             [(len(us_ext), ubase + len(udata), vend)]
    for (i, ua, va), (j, ub, vb) in zip(bounds, bounds[1:]):
        if i >= 0:
            a, n, name = us_ext[i]
            out.append((va, n, name, "same", name, a))
            ua, va = a + n, va + n
        between = us_ext[i + 1:j]
        if vb <= va:
            continue
        if ub - ua == vb - va:
            for a, n, name in between:
                out.append((va + a - ua, n, None, "changed", name, a))
        else:
            for a, n in cut(vdata, vbase, va, vb, targets):
                out.append((a, n, None, "cut", None, None))
    return out


def align_program(job: tuple) -> tuple[str, list[tuple]]:
    program, version, us_ext = job
    levels.select("us")
    if program == "boot":
        us_secs = boot_sections(levels.BOOT)
        levels.select(version)
        v_secs = {name: (a, d) for name, a, d in boot_sections(levels.BOOT)}
        out = []
        for name, a, d in us_secs:
            mine = [e for e in us_ext if a <= e[0] < a + len(d)]
            out += align((a, d), mine, v_secs[name])
        return program, out
    us_text = levels.level_text(levels.DUMP / program)
    levels.select(version)
    return program, align(us_text, us_ext, levels.level_text(levels.DUMP / program))


def texts(program: str) -> list[tuple[int, bytes]]:
    if program == "boot":
        return [(a, d) for _, a, d in boot_sections(levels.BOOT)]
    return [levels.level_text(levels.DUMP / program)]


def read(spans: list[tuple[int, bytes]], address: int, size: int) -> bytes:
    for base, data in spans:
        if base <= address < base + len(data):
            return data[address - base:address - base + size]
    return b""


def calls(aligned: dict, version: str) -> None:
    """A function is the same code only if it also calls the same functions: every `jal` of
    the v1.01 function to a function of its program (or of the boot's resident code, from a
    level) must reach that function's place in V. One that does not is changed code (its
    callee changed, or the call goes elsewhere); repeated until no caller changes."""
    levels.select("us")
    us = {p: texts(p) for p in aligned}
    us_base = levels.LEVEL_BASE
    levels.select(version)
    v = {p: texts(p) for p in aligned}
    while True:
        where = {p: {e[5]: e[0] for e in ext if e[3] == "same"} for p, ext in aligned.items()}
        starts = {p: {e[5] for e in ext if e[5] is not None} for p, ext in aligned.items()}
        changed = 0
        for p, ext in aligned.items():
            for k, e in enumerate(ext):
                if e[3] != "same":
                    continue
                va, n, name, _, _, ua = e
                mine = levels.words(read(us[p], ua, n))
                theirs = levels.words(read(v[p], va, n))
                for i, (x, y) in enumerate(zip(mine, theirs)):
                    if x >> 26 != 3:
                        continue
                    target = ((ua + 4 * i) & 0xF0000000) | ((x & 0x3FFFFFF) << 2)
                    got = ((va + 4 * i) & 0xF0000000) | ((y & 0x3FFFFFF) << 2)
                    owner = "boot" if p != "boot" and target < us_base else p
                    if target in starts[owner] and where[owner].get(target) != got:
                        ext[k] = (va, n, None, "changed", name, ua)
                        changed += 1
                        break
        if not changed:
            return


def branch_target(x: int, at: int) -> int | None:
    """Where the conditional branch (or `b`) X at AT goes; None for anything else."""
    op, rt = x >> 26, (x >> 16) & 31
    if op in (4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 1 and rt in (0, 1, 2, 3)) or \
            (op == 0x11 and (x >> 21) & 31 == 8):
        off = x & 0xFFFF
        return at + 4 + 4 * (off - 0x10000 if off & 0x8000 else off)
    return None


def joins(aligned: dict, version: str) -> None:
    """A branch never leaves its function: two of V's extents one branches into the other
    are one function (V's own, changed code), as the catalogue rules join them; unless both
    are the same code as v1.01's and v1.01's branch crosses the same way."""
    import bisect
    levels.select("us")
    us = {p: texts(p) for p in aligned}
    levels.select(version)
    v = {p: texts(p) for p in aligned}
    for p, ext in aligned.items():
        ext.sort()
        starts = [e[0] for e in ext]
        merge = []
        for i, (va, n, _, how, _, ua) in enumerate(ext):
            for k, x in enumerate(levels.words(read(v[p], va, n))):
                t = branch_target(x, va + 4 * k)
                if t is None or va <= t < va + n:
                    continue
                j = bisect.bisect_right(starts, t) - 1
                if j < 0 or j == i or not (ext[j][0] <= t < ext[j][0] + ext[j][1]):
                    continue
                if how == "same" and ext[j][3] == "same":
                    y = levels.words(read(us[p], ua + 4 * k, 4))
                    if y and branch_target(y[0], ua + 4 * k) == ext[j][5]:
                        continue
                merge.append((min(i, j), max(i, j)))
        if not merge:
            continue
        merge.sort()
        groups = []
        for a, b in merge:
            if groups and a <= groups[-1][1]:
                groups[-1][1] = max(groups[-1][1], b)
            else:
                groups.append([a, b])
        out, i = [], 0
        for a, b in groups:
            out += ext[i:a]
            first, last = ext[a], ext[b]
            out.append((first[0], last[0] + last[1] - first[0], None, "cut", first[4], None))
            i = b + 1
        aligned[p] = out + ext[i:]


# Reasons tools/build.py gives for C that does not build to the bytes at a place: what
# --demote takes as "not the same code" (a knock-on "needs ... which is not C" is not one).
REAL = ("instruction at", "would be at", "differs", "bytes, expected", "needs two values")


def not_carried_path(version: str) -> Path:
    """config/<version>/not_carried.tsv."""
    return ROOT / levels.VERSIONS[version]["config"] / "not_carried.tsv"


def read_not_carried(path: Path) -> dict[str, str]:
    """The v1.01 functions a release does not carry, and what the build said of each."""
    out = {}
    if path.is_file():
        for line in path.read_text().splitlines():
            if line and not line.startswith("#"):
                name, why = line.split("\t", 1)
                out[name] = why
    return out


def write_not_carried(path: Path, names: dict[str, str]) -> None:
    """The list of what a release does not carry: every row that is there keeps its place
    and the reason it has, and what the build measured afresh is added at the end."""
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("# v1.01 function\twhat tools/build.py said (the first program) -- tools/carry.py --demote\n" +
                    "".join(f"{n}\t{w}\n" for n, w in names.items()), newline="\n")


def measured_not_carried(version: str) -> dict[str, str]:
    """What the release's last build shows is not the same code: the functions whose C does
    not build to the release's bytes, for a reason of the code itself. A knock-on row
    ("needs ... which is not C") is not one, and a function the release already owns is not
    v1.01's."""
    v = levels.VERSIONS[version]
    out = {}
    for placed in sorted((ROOT / v["build"]).glob("*/placed.json")):
        for name, why in json.loads(placed.read_text())["differ"].items():
            if not name.startswith("func_") or "_PAL_" in name or "_US2_" in name:
                continue
            if "which is not C" not in why and any(r in why for r in REAL):
                out.setdefault(name, f"{placed.parent.name}: {why}")
    return out


def not_carried(version: str) -> set[str]:
    """config/<version>/not_carried.tsv: v1.01 functions whose code equals this release's with
    every address masked but whose C does not build to it, as tools/build.py measured: an
    offset inside an address (a field of a large global) moved. They and their callers are
    the release's own functions."""
    return set(read_not_carried(not_carried_path(version)))


def demoted_names(direct: set[str], edges: list[tuple[str, str]], carried: set[str]) -> set[str]:
    """The functions the release does not carry: the measured ones, and every carried
    caller of one of them, to a fixed point (a caller's caller is a caller too). A caller
    the release already owns keeps its name: it is the release's own function already."""
    out = set(direct)
    while True:
        grown = {caller for caller, callee in edges if callee in out and caller in carried}
        if grown <= out:
            return out
        out |= grown


def release_names(tag: str, boot_rows: list, rows: list, demoted: set[str]) -> dict[str, str]:
    """The release's own name for each demoted function: the boot's copy by its address, a
    level's copy by its first place."""
    out = {}
    for name, address, _ in boot_rows:
        if name in demoted:
            out[name] = f"func_{tag}_{address:08X}"
    for name, _, _, _, places in rows:
        if name in demoted and name not in out:
            number, address = places[0]
            out[name] = f"func_{tag}_L{number:02d}_{address:08X}"
    return out


def demote_catalogue(tag: str, boot_rows: list, rows: list, demoted: set[str]) -> tuple:
    """The release's catalogues with the demoted functions named for the release.

    Only the demoted rows change: every other row keeps its name, address, size,
    fingerprint and places, and every row keeps its place in the file.
    """
    renames = release_names(tag, boot_rows, rows, demoted)
    new_boot = [(renames.get(name, name), address, size) for name, address, size in boot_rows]
    boot_names = {name for name, _, _ in new_boot}
    new_rows = []
    for name, kind, size, fp, places in rows:
        new = renames.get(name)
        if new is None:
            new_rows.append((name, kind, size, fp, places))
            continue
        if new in boot_names:
            kind = "boot"
        else:
            kind = "level" if len({p[0] for p in places}) == 1 else "shared"
        new_rows.append((new, kind, size, fp, places))
    for names in ([n for n, _, _ in new_boot], [n for n, *_ in new_rows]):
        if len(set(names)) != len(names):
            sys.exit("the demotion would give two functions of the release one name")
    return new_boot, new_rows, renames


def call_edges(boot_rows: list, rows: list) -> list[tuple[str, str]]:
    """(caller, callee) for every call the release's own code makes.

    The boot's calls are the boot's. A level holds the boot's resident functions (below
    levels.LEVEL_BASE) at the boot's addresses and its own code above that line, so a call
    from a level reaches the boot's function below it and the level's own above it.
    """
    edges = []
    spans = [(a, d) for _, a, d in boot_sections(levels.BOOT)]
    starts = {address: name for name, address, _ in boot_rows}
    for name, address, size in boot_rows:
        for target in jal_targets(read(spans, address, size), address):
            callee = starts.get(target)
            if callee:
                edges.append((name, callee))
    resident = {a: n for n, a, _ in boot_rows if a < levels.LEVEL_BASE}
    by_level = {}
    for name, _, size, _, places in rows:
        for number, address in places:
            by_level.setdefault(number, []).append((name, address, size))
    for number in sorted(by_level):
        base, data = levels.level_text(levels.DUMP / levels.level_dir(number))
        here = dict(resident)
        for name, address, _ in by_level[number]:
            here[address] = name
        for name, address, size in by_level[number]:
            body = data[address - base:address - base + size]
            for target in jal_targets(body, address):
                callee = here.get(target)
                if callee:
                    edges.append((name, callee))
    return edges


def write_catalogues(boot_rows: list, rows: list) -> None:
    """config/<version>/boot/functions.tsv and config/<version>/levels/functions.tsv, in the
    formats docs/VERSIONS.md gives them."""
    levels.BOOT_FUNCTIONS.parent.mkdir(parents=True, exist_ok=True)
    levels.BOOT_FUNCTIONS.write_text("# name\taddress\tsize -- tools/carry.py\n" + "".join(
        f"{name}\t{address:08X}\t{size}\n" for name, address, size in boot_rows), newline="\n")
    levels.LEVELS.mkdir(parents=True, exist_ok=True)
    lines = ["# name\tkind\tsize\tfingerprint\tlevels\tplaces (level:address) -- tools/carry.py"]
    for name, kind, size, fp, places in rows:
        lines.append(f"{name}\t{kind}\t{size}\t{fp}\t{len({p[0] for p in places})}\t" +
                     ",".join(f"{lv:02d}:{a:08X}" for lv, a in places))
    levels.CATALOGUE.write_text("\n".join(lines) + "\n", newline="\n")


def demote(version: str) -> None:
    """Take the functions the build disproves out of the release's carry.

    The measured ones and the carried callers of them become the release's own functions:
    they are listed in config/<version>/not_carried.tsv, renamed for the release in the
    release's catalogues and given INCLUDE_ASM markers in src/<version>/. The release is
    not realigned: every other row of its catalogues keeps its name, address and places.
    """
    tag = levels.VERSIONS[version]["tag"]
    levels.select(version)
    path = not_carried_path(version)
    names = read_not_carried(path)
    measured = measured_not_carried(version)
    for name in sorted(measured):
        names.setdefault(name, measured[name])
    write_not_carried(path, names)

    boot_rows = levels.read_boot_functions()
    rows = levels.read_catalogue()
    carried = {name for name, _, _ in boot_rows} | {name for name, *_ in rows}
    carried = {name for name in carried if not name.startswith(f"func_{tag}_")}
    direct = {name for name in names if name in carried}
    edges = call_edges(boot_rows, rows) if direct else []
    demoted = demoted_names(direct, edges, carried)
    if not demoted:
        print(f"{version}: {len(names)} functions not carried; none of them is carried here")
        return
    new_boot, new_rows, renames = demote_catalogue(tag, boot_rows, rows, demoted)
    write_sources(version, tag, new_boot, new_rows)
    write_catalogues(new_boot, new_rows)
    print(f"{version}: {len(demoted)} functions demoted ({len(direct)} measured, "
          f"{len(demoted) - len(direct)} their carried callers); {len(renames)} names changed")


def correct_level_entries(rows: list[tuple]) -> list[tuple]:
    """Apply measured entries without regrouping or renaming existing rows."""
    texts, out = {}, []
    for name, kind, size, fp, places in rows:
        if levels.function_residue(name, size):
            continue
        corrected = [(lv, *levels.function_extent(name, a, size)) for lv, a in places]
        if all((a, n) == (old, size) for (_, a, n), (_, old) in zip(corrected, places)):
            out.append((name, kind, size, fp, places))
            continue
        keys = set()
        for lv, a, n in corrected:
            if lv not in texts:
                texts[lv] = levels.level_text(levels.DUMP / levels.level_dir(lv))
            base, data = texts[lv]
            keys.add((levels.fingerprint(data[a - base:a - base + n], a), n))
        if len(keys) != 1:
            raise ValueError(f"{name}: corrected level copies differ")
        new_fp, new_size = next(iter(keys))
        out.append((name, kind, new_size, new_fp, [(lv, a) for lv, a, _ in corrected]))
    return out


def refresh_entries() -> None:
    """Repair measured extents in an existing release catalogue, retaining identities.

    This does not realign releases, revisit callee correspondences or promote C.
    The normal carry remains the full cross-release alignment operation.
    """
    boot = []
    for name, a, n in levels.read_boot_functions():
        if not levels.function_residue(name, n):
            a, n = levels.function_extent(name, a, n)
            boot.append((name, a, n))
    rows = correct_level_entries(levels.read_catalogue())
    # Validate both catalogues completely before writing either output.
    write_catalogues(boot, rows)
    print(f"entry repairs: {len(boot)} boot functions, {len(rows)} level rows; identities retained")


def main() -> None:
    version = levels.version_argument()
    levels.select(version)
    if version == "us":
        sys.exit("USA v1.01 is the catalogue the others are carried from: --version pal or us2")
    if "--entries" in sys.argv:
        refresh_entries()
        return
    if "--demote" in sys.argv:
        demote(version)
        return
    tag = levels.VERSIONS[version]["tag"]
    levels.select("us")
    us_boot = levels.read_boot_functions()
    us_rows = levels.read_catalogue()
    jobs = [("boot", version, sorted((a, n, name) for name, a, n in us_boot))]
    for number in sorted(levels.NAMES):
        ext = sorted((a, size, name) for name, _, size, _, places in us_rows for lv, a in places if lv == number)
        jobs.append((levels.level_dir(number), version, ext))
    with ProcessPoolExecutor() as pool:
        aligned = dict(pool.map(align_program, jobs))
    kept_out = not_carried(version)
    for p, ext in aligned.items():
        aligned[p] = [(e[0], e[1], None, "changed", e[4], e[5]) if e[3] == "same" and e[2] in kept_out else e
                      for e in ext]
    calls(aligned, version)
    joins(aligned, version)
    levels.select(version)

    # The boot: the catalogue's filters, then the names.
    boot_rows, last_end, last_body = [], None, b""
    for a, n, us_name, how, was, _ in sorted(aligned["boot"]):
        body = levels.boot_bytes(a, n)
        if levels.is_padding(body):
            continue
        if len(levels.words(body)) == 1 and last_end == a and levels.is_epilogue_residue(body, last_body):
            continue
        boot_rows.append((us_name or f"func_{tag}_{a:08X}", a, n, how, was))
        last_end, last_body = a + n, body
    boot_names = {r[0] for r in boot_rows}
    boot_by_fp = {}
    for name, a, n, _, _ in boot_rows:
        boot_by_fp.setdefault((levels.fingerprint(levels.boot_bytes(a, n), a), n), []).append(name)

    # The levels: identical code is one function, the k-th copy in each level one.
    found, us_of = {}, {}
    for number in sorted(levels.NAMES):
        base, data = levels.level_text(levels.DUMP / levels.level_dir(number))
        last_end, last_body = None, b""
        for a, n, us_name, how, was, _ in sorted(aligned[levels.level_dir(number)]):
            body = data[a - base:a - base + n]
            if not levels.trim(body) or levels.is_padding(body):
                continue
            if len(levels.words(body)) == 1 and last_end == a and levels.is_epilogue_residue(body, last_body):
                continue
            entry = found.setdefault((levels.fingerprint(body, a), n), {"size": n, "places": []})
            entry["places"].append((number, a))
            us_of[(number, a)] = (us_name, how, was)
            last_end, last_body = a + n, body
    rows = []
    for (fp, size), e in found.items():
        per_level = {}
        for number, a in sorted(e["places"]):
            per_level.setdefault(number, []).append(a)
        copies = max(len(v) for v in per_level.values())
        for k in range(copies):
            places = [(number, v[k]) for number, v in sorted(per_level.items()) if len(v) > k]
            rows.append({"fp": fp, "size": size, "places": places, "copies": copies})
    # v1.01 names: a row takes the name its places were found as; a name two rows claim goes
    # to the one with more places.
    claims = {}
    for r in rows:
        names = {}
        for p in r["places"]:
            name = us_of[p][0]
            if name:
                names[name] = names.get(name, 0) + 1
        r["us"] = max(names, key=lambda k: (names[k], k)) if names else None
        if r["us"]:
            claims.setdefault(r["us"], []).append(r)
    for name, rs in claims.items():
        rs.sort(key=lambda r: (-len(r["places"]), r["places"][0]))
        for r in rs[1:]:
            r["us"] = None
    out = []
    for r in rows:
        number, a = r["places"][0]
        boot = boot_by_fp.get((r["fp"], r["size"]), ())
        if r["us"]:
            name = r["us"]
        elif r["copies"] == 1 and len(boot) == 1:
            name = boot[0]
        else:
            name = f"func_{tag}_L{number:02d}_{a:08X}"
        if name in boot_names:
            kind = "boot"
        else:
            kind = "level" if len({p[0] for p in r["places"]}) == 1 else "shared"
        out.append((name, kind, r["size"], r["fp"], r["places"]))
    out.sort(key=lambda r: r[4][0])
    if len({r[0] for r in out}) != len(out):
        sys.exit("two level functions would have one name")

    write_catalogues([(n, a, s) for n, a, s, _, _ in sorted(boot_rows, key=lambda r: r[1])], out)

    # What each v1.01 function became, for docs/VERSIONS.md and tools/progress.py's notes.
    report = {"boot": {}, "levels": {}}
    for name, a, n, how, was in boot_rows:
        report["boot"][name] = {"address": a, "size": n, "how": how, "was": was}
    for name, kind, size, fp, places in out:
        hows = sorted({us_of[p][1] for p in places})
        was = sorted({us_of[p][2] for p in places if us_of[p][2]})
        report["levels"][name] = {"size": size, "how": hows, "was": was}
    carried = levels.build_dir() / "carry.json"
    carried.parent.mkdir(parents=True, exist_ok=True)
    carried.write_text(json.dumps(report, indent=0) + "\n")

    count = lambda rs, how: sum(1 for r in rs if r[3] == how)
    nbytes = lambda rs, how: sum(r[2] for r in rs if r[3] == how)
    print(f"{version} boot: {len(boot_rows)} functions; " + ", ".join(
        f"{count(boot_rows, h)} {h} ({nbytes(boot_rows, h)} bytes)" for h in ("same", "changed", "cut")))
    us_names = {r[0] for r in us_rows} | {r[0] for r in us_boot}
    kept = sum(1 for r in out if r[0] in us_names)
    print(f"{version} levels: {sum(len(r[4]) for r in out)} placements; {len(out)} distinct "
          f"({kept} with a v1.01 name): " + ", ".join(
              f"{sum(1 for r in out if r[1] == k)} {k}" for k in ("boot", "shared", "level")))

    write_sources(version, tag, boot_rows, out)


MARKER = re.compile(r'^(?:INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT)\("[^"]*",\s*(func_\w+)\);', re.M)
DEFINITION = re.compile(r"^(?:[A-Za-z_][^;=#]*?\b)?(func_\w+)\s*\(", re.M)


def source_runs(tag: str, boot_rows: list, rows: list, have: set[str], core: tuple[int, int]) -> list[tuple[str, str, list[str]]]:
    """The files src/<version>/ needs for the release's own functions that have no marker
    yet: (directory, file stem, the functions in the file), in the layout src/ has them
    (the boot's core.text in core/, its .text in game/, level code in levels/shared/ and
    levels/NN_name/). HAVE are the functions src/<version>/ already has."""
    mine = lambda name: name.startswith(f"func_{tag}_")
    runs = []                   # (directory, file stem, [names], fresh)
    previous = None
    for name, a in sorted(((r[0], r[1]) for r in boot_rows), key=lambda r: r[1]):
        directory = "core" if core[0] <= a < core[1] else "game"
        fresh = mine(name) and name not in have
        if fresh and not (previous and runs and runs[-1][3] and runs[-1][0] == directory):
            runs.append((directory, f"{a:08X}", [name], True))
        elif fresh:
            runs[-1][2].append(name)
        previous = fresh
    by_level = {}
    for name, kind, size, fp, places in rows:
        if kind != "boot":
            by_level.setdefault(places[0][0], []).append((places[0][1], name, kind))
    for number in sorted(by_level):
        previous = None
        for a, name, kind in sorted(by_level[number]):
            directory = "levels/shared" if kind == "shared" else f"levels/{levels.level_dir(number)}"
            fresh = mine(name) and name not in have
            if fresh and previous == directory and runs and runs[-1][3]:
                runs[-1][2].append(name)
            elif fresh:
                runs.append((directory, f"L{number:02d}_{a:08X}", [name], True))
            previous = directory if fresh else None
    return [(directory, stem, names) for directory, stem, names, _ in runs]


def write_sources(version: str, tag: str, boot_rows: list, rows: list) -> None:
    """src/<version>/: an INCLUDE_ASM marker for every function of the release that has no
    v1.01 name, in files of consecutive such functions as src/ has them (the boot's core.text
    in core/, its .text in game/, level code in levels/shared/ and levels/NN_name/). Files
    already there are kept; new functions get new files; a function of src/<version>/ the
    catalogues no longer have stops the tool."""
    root = ROOT / "src" / version
    have = set()
    for path in root.rglob("*.c"):
        text = path.read_text()
        have |= set(MARKER.findall(text)) | {m for m in DEFINITION.findall(text) if m.startswith(f"func_{tag}_")}
    mine = lambda name: name.startswith(f"func_{tag}_")
    known = {r[0] for r in boot_rows} | {r[0] for r in rows}
    stale = sorted(n for n in have if mine(n) and n not in known)
    if stale:
        sys.exit(f"src/{version}/ has {len(stale)} functions the catalogues no longer have, e.g. {stale[:5]}")
    sections = boot_sections(levels.BOOT)
    core = next(a for name, a, d in sections if name == "core.text"), \
        next(a + len(d) for name, a, d in sections if name == "core.text")
    runs = source_runs(tag, boot_rows, rows, have, core)
    for directory, stem, _ in runs:                # nothing is written if one file would go
        path = root / directory / f"{stem}.c"
        if path.exists():
            sys.exit(f"{path.relative_to(ROOT)} exists; move its functions before regenerating")
    written = 0
    for directory, stem, names in runs:
        path = root / directory / f"{stem}.c"
        path.parent.mkdir(parents=True, exist_ok=True)
        area = directory.split("/")[0]
        path.write_text('#include "include_asm.h"\n\n' + "\n".join(
            f'INCLUDE_ASM("asm/{version}/{area}", {name});\n' for name in names), newline="\n")
        written += len(names)
    print(f"src/{version}/: {written} new markers in {len(runs)} files")


if __name__ == "__main__":
    main()
