#!/usr/bin/env python3
"""Return types agree between a function's definition and every declaration of it.

  python3 tests/check_return_types.py            # all of src/, every release folder
  python3 tests/check_return_types.py --list     # also print every function's classes

Each file in src/ links (and matches retail) on its own, so a caller may declare a function with a
return type other than the one its definition has and still produce the right bytes. The program
as a whole is then undefined C, and a tool that links all the C together (OpenRAC's hostgen)
reads the value from the wrong register: `float snd_compute_voice_volume_from_distance` was
declared `int` by its callers and every 3D sound went silent in the port.

Every .c file under src/ is parsed by clang (`-fsyntax-only -Xclang -ast-dump=json`, MIPS target,
the build's include paths). Every function declaration (file scope, block scope, prototypes in
headers, and C89 implicit declarations at a call) and every definition is reduced to its return
type class, as the EE ABI returns it:

  void, int32 (char/short/int/enum, in $v0), int64 (long, long long: EE GCC's long is 64-bit,
  in $v0), int128 (mode TI), float (in $f0), double (software floating point, 64 bits in $v0),
  pointer (in $v0), aggregate.

Functions are grouped by linker name (after include/names.h's macros) across all release folders:
src/ holds v1.01's names, which the other releases share, and their own names carry a tag. A
`<prefix>_FUN_XXXXXXXX` alias is the function at that address (tools/build.py resolves it so), and
so is a numbered alias `func_XXXXXXXX_N`.
The check fails when the classes of a group differ: definitions against declarations, or, for a
function with no C definition (assembly), declarations against each other.

Known exceptions go in config/return_type_exceptions.tsv: `name<TAB>classes<TAB>reason`, one row
per function. The row tolerates declarations (never the definition) of the listed classes
(comma-separated, e.g. `void`); everything else of the function must still agree. A row that no
longer matches a conflict is itself an error.
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EXCEPTIONS = ROOT / "config/return_type_exceptions.tsv"
CLANG_FLAGS = ["--target=mipsel-unknown-linux-gnu", "-fsyntax-only", "-std=gnu89", "-w",
               "-ferror-limit=0", "-Wno-error", "-Xclang", "-ast-dump=json"]

INT32 = {"char", "short", "int", "_Bool", "signed", "unsigned"}
QUALIFIERS = {"const", "volatile", "signed", "unsigned", "register", "static", "extern",
              "inline", "__inline", "__inline__", "restrict", "__restrict", "__restrict__"}


def clang() -> str:
    for name in (os.environ.get("CLANG"), "clang", "clang-18", "clang-19", "clang-20"):
        if name and shutil.which(name):
            return name
    sys.exit("check_return_types: clang not found (set $CLANG)")


def return_part(function_type: str) -> str:
    """'float (char *, char *)' -> 'float'; 'void (*(int))(void)' -> 'void (*)(void)'-like."""
    t = function_type.strip()
    while True:                              # trailing attributes: noreturn, format, ...
        m = re.search(r"\s*__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)\s*$", t)
        if not m:
            break
        t = t[:m.start()].rstrip()
    # strip the outermost parameter list: the last top-level '(...)' group
    depth = 0
    for i in range(len(t) - 1, -1, -1):
        c = t[i]
        if c == ")":
            depth += 1
        elif c == "(":
            depth -= 1
            if depth == 0:
                head = t[:i].rstrip()
                if head.endswith("(*") or head.endswith("*)") or "(*" in head:
                    return head + "*)"          # returns a pointer to function or array
                return head
    return t


def classify(type_text: str, typedefs: dict, depth: int = 0) -> str:
    t = type_text.strip()
    if "*" in t or "(" in t or "[" in t:
        return "pointer"
    t = re.sub(r"__attribute__\s*\(\(.*\)\)", "", t).strip()
    words = [w for w in t.split() if w not in QUALIFIERS]
    if not words:
        return "int32"                       # plain 'unsigned' / 'signed'
    if words[0] in ("struct", "union"):
        return "aggregate"
    if words[0] == "enum":
        return "int32"
    if words == ["void"]:
        return "void"
    if words[-1] == "float":
        return "float"
    if words[-1] == "double":
        return "double"                      # software double: 64 bits in $v0
    if "long" in words:
        return "int64"
    if "__int128" in words or "__int128_t" in words or "__uint128_t" in words:
        return "int128"
    if all(w in INT32 for w in words):
        return "int32"
    if len(words) == 1 and words[0] in typedefs and depth < 20:
        return classify(typedefs[words[0]], typedefs, depth + 1)
    return "unknown:" + " ".join(words)


def scan(path: str) -> dict:
    """Parse one file; return its function declarations and the parse errors."""
    source = ROOT / path
    command = [clang(), *CLANG_FLAGS, f"-I{ROOT / 'include'}", f"-I{source.parent}", str(source)]
    done = subprocess.run(command, capture_output=True, text=True, cwd=ROOT)
    errors = [line for line in done.stderr.splitlines() if " error: " in line]
    try:
        tree = json.loads(done.stdout)
    except json.JSONDecodeError:
        return {"path": path, "decls": [], "errors": errors or ["clang produced no AST"]}
    typedefs = {}
    decls = []

    last = {"file": path, "line": 0, "col": 0, "tokLen": 0}

    def walk(node):
        loc = node.get("loc", {})
        expansion = loc.get("expansionLoc", loc)
        if "file" in expansion:
            last["file"] = expansion["file"]
        if "line" in expansion:
            last["line"] = expansion["line"]
        if "col" in expansion:
            last["col"] = expansion["col"]
            last["tokLen"] = expansion.get("tokLen", 0)
        kind = node.get("kind")
        if kind == "TypedefDecl" and "name" in node:
            ty = node.get("type", {})
            typedefs[node["name"]] = ty.get("desugaredQualType", ty.get("qualType", ""))
        elif kind == "FunctionDecl" and "name" in node:
            ty = node.get("type", {})
            text = ty.get("qualType", "")
            ret = return_part(text)
            defined = any(c.get("kind") == "CompoundStmt" for c in node.get("inner", []))
            decls.append({
                "name": node["name"], "ret": ret, "defined": defined,
                "implicit": bool(node.get("isImplicit")),
                "file": relative(last["file"]), "line": last["line"],
                "col": last["col"], "len": last["tokLen"],
            })
        for child in node.get("inner", []) or []:
            walk(child)

    walk(tree)
    for d in decls:
        d["class"] = classify(d["ret"], typedefs)
        if d["class"].startswith("unknown:") and d["ret"] in typedefs:
            d["class"] = classify(typedefs[d["ret"]], typedefs)
    return {"path": path, "decls": decls, "errors": errors}


def relative(name: str) -> str:
    try:
        return str(Path(name).resolve().relative_to(ROOT))
    except ValueError:
        return name


ALIAS = re.compile(r"(?:^|_)FUN_([0-9A-F]{8})$")
NUMBERED = re.compile(r"(func_(?:[A-Z0-9]+_)?(?:L\d\d_)?[0-9A-F]{8})_\d+")    # func_00283B98_10


def canonical(names: set) -> dict:
    """Map each name to its group key: `<prefix>_FUN_XXXXXXXX` joins func_XXXXXXXX (or the one
    func_LNN_XXXXXXXX of that address)."""
    by_address = defaultdict(set)
    for n in names:
        m = re.fullmatch(r"func_(?:L\d\d_)?([0-9A-F]{8})", n)
        if m:
            by_address[m.group(1)].add(n)
    out = {}
    for n in names:
        numbered = NUMBERED.fullmatch(n)
        if numbered:
            out[n] = numbered.group(1)
            continue
        m = ALIAS.search(n)
        if m and not n.startswith("func_"):
            address = m.group(1)
            if f"func_{address}" in names:
                out[n] = f"func_{address}"
                continue
            if len(by_address[address]) == 1:
                out[n] = next(iter(by_address[address]))
                continue
            out[n] = f"func_{address}"
        else:
            out[n] = n
    return out


def load_exceptions() -> dict:
    rows = {}
    if not EXCEPTIONS.exists():
        return rows
    for n, line in enumerate(EXCEPTIONS.read_text().splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        cols = line.split("\t")
        if len(cols) != 3 or not cols[2].strip() or not cols[1].strip():
            sys.exit(f"{EXCEPTIONS.relative_to(ROOT)}:{n}: expected `name<TAB>classes<TAB>reason`")
        if cols[0] in rows:
            sys.exit(f"{EXCEPTIONS.relative_to(ROOT)}:{n}: {cols[0]} listed twice")
        rows[cols[0]] = {c.strip() for c in cols[1].split(",")}
    return rows


def excepted(decls: list, tolerated: set) -> bool:
    """The conflict disappears once declarations of the tolerated classes are set aside."""
    rest = [d for d in decls if d["defined"] or d["class"] not in tolerated]
    used = {d["class"] for d in decls if not d["defined"] and d["class"] in tolerated}
    return len({d["class"] for d in rest}) <= 1 and bool(used)


def sources() -> list:
    return sorted(str(p.relative_to(ROOT)) for p in (ROOT / "src").rglob("*.c"))


def collect(paths: list, jobs: int) -> list:
    with ProcessPoolExecutor(max_workers=jobs) as pool:
        return list(pool.map(scan, paths, chunksize=16))


def conflicts(results: list) -> dict:
    """Group key -> list of (class, kind, file:line, spelled return type) when classes differ."""
    names = {d["name"] for r in results for d in r["decls"]}
    key = canonical(names)
    groups = defaultdict(dict)                 # key -> {(file, line, name): decl}
    for r in results:
        for d in r["decls"]:
            groups[key[d["name"]]][(d["file"], d["line"], d["name"], d["defined"])] = d
    bad = {}
    for k, decls in groups.items():
        decls = list(decls.values())
        defs = [d for d in decls if d["defined"]]
        reference = {d["class"] for d in defs} if defs else {d["class"] for d in decls}
        classes = {d["class"] for d in decls}
        if len(classes) > 1 or len(reference) > 1:
            bad[k] = sorted(decls, key=lambda d: (not d["defined"], d["file"], d["line"]))
    return bad


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("paths", nargs="*", help="files to parse (default: every .c under src/)")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    ap.add_argument("--json", help="write every conflict as JSON to this file")
    args = ap.parse_args()
    paths = args.paths or sources()
    results = collect(paths, args.jobs)
    failed = [r for r in results if r["errors"] and not r["decls"]]
    bad = conflicts(results)
    exceptions = load_exceptions()
    problems = []
    for r in failed:
        problems.append(f"{r['path']}: clang could not parse it: {r['errors'][:1]}")
    excused = set()
    for k, decls in sorted(bad.items()):
        if k in exceptions and excepted(decls, exceptions[k]):
            excused.add(k)
            continue
        lines = [f"{k}: return type classes differ:"]
        for d in decls:
            what = "definition" if d["defined"] else ("implicit declaration" if d["implicit"] else "declaration")
            lines.append(f"    {d['class']:9} {what:20} {d['file']}:{d['line']}  ({d['name']}: {d['ret']})")
        problems.append("\n".join(lines))
    for k in sorted(set(exceptions) - set(bad)):
        problems.append(f"{EXCEPTIONS.relative_to(ROOT)}: {k} has no conflict any more; remove its row")
    if args.json:
        Path(args.json).write_text(json.dumps(bad, indent=1))
    for p in problems:
        print(p)
    count = sum(len(r["decls"]) for r in results)
    print(f"check_return_types: {len(paths)} files, {count} function declarations, "
          f"{len(bad)} conflicts ({len(excused)} excepted)"
          + (": FAIL" if problems else ": OK"))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
