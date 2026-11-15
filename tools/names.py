#!/usr/bin/env python3
"""
Readable names for this build's symbols, and the header that lets C use
them while the linker symbol stays func_<ADDR> / func_LNN_<ADDR> / D_<ADDR>
(docs/contributing/names.md). Carried from rac1-decomp's tools/names.py,
without its RaC1-only import sources.

  python3 tools/names.py local       # config/names_local.tsv -> config/names.tsv
  python3 tools/names.py header      # config/names.tsv -> include/names.h, include/names/*.h
  python3 tools/names.py apply-defs  # definitions use the readable names
  python3 tools/names.py apply       # bodies, extern lines and prototypes use them
  python3 tools/names.py check       # names.h is current and collision-free
  python3 tools/names.py rename      # carry changed names into names.h and src/
  python3 tools/names.py SYMBOL|NAME [...]   # look one up

config/names.tsv is the committed table: one row per named symbol, with
its chosen name, tier, source, evidence and alternatives.

  recovered    an original identifier (research documents, the 8 August 2003
               prototype's symbols); never respelled
  descriptive  a later name with evidence: a RAC1 counterpart, or a name this
               project gives from reading the code (config/names_local.tsv)
  candidate    weaker: listed for workers, never put into names.h
"""
from __future__ import annotations
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import names_header  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
TABLE = ROOT / "config/names.tsv"
LOCAL = ROOT / "config/names_local.tsv"
HEADER = ROOT / "include/names.h"
TIERS = ("recovered", "descriptive", "candidate")
SYMBOL = re.compile(r"^(func_(?:L\d{2}_)?[0-9A-F]{8}|D_(?:L\d{2}_)?[0-9A-F]{8})$")
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
COLUMNS = ("symbol", "name", "tier", "source", "evidence", "alts")
LOCAL_SOURCE = "config/names_local.tsv"
TABLE_HEAD = ("# Readable names; see docs/contributing/names.md. tools/names.py local merges\n"
              "# config/names_local.tsv into it. Columns:\n"
              "# symbol\tname\ttier\tsource\tevidence\talternatives\n")


def warn(msg):
    print(f"warning: {msg}", file=sys.stderr)


# ---------------------------------------------------------------- the table

def read_local() -> list[tuple[str, str, str, bool]]:
    """(symbol, name, evidence, override) rows of config/names_local.tsv:
    names this project gives from reading the code."""
    out = []
    if not LOCAL.exists():
        return out
    for line in LOCAL.read_text().splitlines():
        if line.startswith("#") or not line.strip():
            continue
        sym, name, evidence, flag = (line.split("\t") + ["", "", "", ""])[:4]
        if not SYMBOL.match(sym) or not IDENT.match(name):
            sys.exit(f"{LOCAL.name}: bad row: {line!r}")
        out.append((sym, name, evidence, flag.strip() == "override"))
    return out


def merge_local(rows: list[dict]) -> list[dict]:
    """ROWS with config/names_local.tsv applied: a local name fills a symbol
    that has none or only a candidate (tier descriptive); `override` also
    replaces a recovered/descriptive name that is wrong. The old name goes
    to the alternatives. A name another symbol holds is refused."""
    by_sym = {r["symbol"]: r for r in rows}
    holder = {r["name"]: r["symbol"] for r in rows if r["tier"] != "candidate"}
    for sym, name, evidence, override in read_local():
        old = by_sym.get(sym)
        if old and old["source"] != LOCAL_SOURCE and old["tier"] != "candidate" and not override:
            continue
        if holder.get(name, sym) != sym:
            warn(f"{LOCAL.name}: {name} for {sym} is taken by {holder[name]}")
            continue
        new = {"symbol": sym, "name": name, "tier": "descriptive", "source": LOCAL_SOURCE,
               "evidence": evidence, "alts": ""}
        if old:
            alts = [a for a in old["alts"].split(",") if a] + [old["name"]]
            new["alts"] = ",".join(dict.fromkeys(a for a in alts if a != name))
            if holder.get(old["name"]) == sym:
                del holder[old["name"]]
            old.update(new)
        else:
            rows.append(new)
            by_sym[sym] = new
        holder[name] = sym
    return rows


def read_table() -> list[dict]:
    out = []
    if not TABLE.exists():
        return out
    for line in TABLE.read_text().splitlines():
        if line.startswith("#") or not line.strip():
            continue
        sym, name, tier, source, evidence, alts = (line.split("\t") + [""] * 6)[:6]
        out.append({"symbol": sym, "name": name, "tier": tier, "source": source,
                    "evidence": evidence, "alts": alts})
    return out


def write_table(rows) -> None:
    with open(TABLE, "w", newline="") as f:
        f.write(TABLE_HEAD)
        for r in rows:
            f.write("\t".join(r[c].replace("\t", " ") for c in COLUMNS) + "\n")


def local() -> None:
    """Apply config/names_local.tsv to config/names.tsv."""
    rows = merge_local(read_table())
    write_table(rows)
    c = Counter(r["tier"] for r in rows)
    print(f"wrote {TABLE.relative_to(ROOT)}: {len(rows)} symbols "
          f"({', '.join(f'{c[t]} {t}' for t in TIERS)})")


# ---------------------------------------------------------------- the header

def strip_c(text: str) -> str:
    """TEXT without comments, string and character literals."""
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'',
                  " ", text, flags=re.S)


def source_files():
    for d in ("src", "include", "nonmatching"):
        for p in sorted((ROOT / d).rglob("*")):
            if p.suffix in (".c", ".h") and not names_header.is_generated(p, HEADER):
                yield p


def identifiers_in_use() -> set[str]:
    words = set()
    for p in source_files():
        words |= set(re.findall(r"\b[A-Za-z_]\w*\b", strip_c(p.read_text(errors="replace"))))
    return words


def header_rows(rows=None):
    """Rows names.h defines, and rows left out because the name is already
    an identifier in src/, include/ or nonmatching/ (it would be silently renamed)."""
    rows = rows if rows is not None else read_table()
    # A name names.h already maps to the same symbol is in src/ because
    # `apply` put it there; only new names can clash with an identifier.
    current = dict(re.findall(r"(?m)^#define (\w+)\s+(\w+)$", names_header.read(HEADER)))
    in_use = identifiers_in_use() - {n for n, s in current.items()
                                     if any(r["name"] == n and r["symbol"] == s for r in rows)}
    keep, clash = [], []
    for r in rows:
        if r["tier"] == "candidate":
            continue
        (clash if r["name"] in in_use else keep).append(r)
    return keep, clash


def part_of(symbol: str) -> str:
    """Which file of include/names/ a symbol's name goes in."""
    m = re.match(r"(?:func|D)_L(\d\d)_", symbol)
    if not m:
        return "executable"
    return "shared_levels" if m.group(1) == "00" else f"level_{m.group(1)}"


def render_part(part, rows) -> str:
    width = max((len(r["name"]) for r in rows), default=0)
    lines = [f"/* Readable names: {part}. Generated by tools/names.py header; do not edit. */", ""]
    for tier in ("recovered", "descriptive"):
        group = sorted((r for r in rows if r["tier"] == tier), key=lambda r: r["symbol"])
        if group:
            lines.append(f"/* {tier} */")
            lines += [f"#define {r['name']:<{width}} {r['symbol']}" for r in group]
            lines.append("")
    return "\n".join(lines)


def render_header(parts) -> str:
    lines = [
        "/*",
        " * Readable names for this build's symbols. Generated by",
        " * tools/names.py header from config/names.tsv; do not edit.",
        " *",
        " * Each name is a macro for the address-named symbol the build and",
        " * every tool use (func_<ADDR>, func_LNN_<ADDR>, D_<ADDR>): code may",
        " * write either spelling and compiles to the same object. Definitions,",
        " * bodies, extern lines and prototypes use the readable name;",
        " * INCLUDE_ASM/ASM_FUNC lines, __asm__ labels and SDATA() keep the",
        " * address name (tools read source through tools/srcnames.py).",
        " * Names express observed behaviour unless their tier is recovered.",
        " * Tiers and sources: docs/contributing/names.md.",
        " */",
        "#ifndef NAMES_H",
        "#define NAMES_H",
        "",
    ]
    lines += [f'#include "names/{part}.h"' for part in sorted(parts)]
    lines += ["", "#endif /* NAMES_H */", ""]
    return "\n".join(lines)


def header() -> None:
    keep, clash = header_rows()
    parts = defaultdict(list)
    for row in keep:
        parts[part_of(row["symbol"])].append(row)
    folder = HEADER.parent / names_header.PARTS
    folder.mkdir(exist_ok=True)
    for stale in names_header.part_files(HEADER):
        if stale.stem not in parts:
            stale.unlink()
    for part, rows in parts.items():
        (folder / f"{part}.h").write_text(render_part(part, rows))
    HEADER.write_text(render_header(parts))
    print(f"wrote {HEADER.relative_to(ROOT)}: {len(keep)} names"
          + (f"; {len(clash)} left out, already an identifier in src/: "
             + ", ".join(sorted(r['name'] for r in clash)) if clash else ""))


def check() -> None:
    """names.h matches the table, and no name it defines is used as a
    different identifier anywhere in src/, include/ or nonmatching/."""
    keep, clash = header_rows()
    current = names_header.read(HEADER)
    defined = dict(re.findall(r"(?m)^#define (\w+)\s+(\w+)$", current))
    wanted = {r["name"]: r["symbol"] for r in keep}
    in_header = {n: s for n, s in defined.items() if n != "NAMES_H"}
    bad = False
    for n, s in in_header.items():
        if wanted.get(n) != s and not any(r["name"] == n for r in clash):
            print(f"names.h defines {n} as {s}, the table says {wanted.get(n)}")
            bad = True
    missing = sorted(set(wanted) - set(in_header))
    if missing:
        print(f"names.h lacks {len(missing)} names from the table (run: tools/names.py header)")
        bad = True
    names = Counter(r["name"] for r in read_table() if r["tier"] != "candidate")
    for n, k in names.items():
        if k > 1:
            print(f"config/names.tsv gives {n} to {k} symbols")
            bad = True
    if bad:
        sys.exit(1)
    print(f"include/names.h is current: {len(in_header)} names")


# ---------------------------------------------------------------- apply

DECL_LINE = re.compile(r"^\s*(extern\b|#|INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT|typedef\b)")
EXTERN_LINE = re.compile(r"^\s*extern\b")
PROTO_LINE = re.compile(r"^(?!\s*(#|INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT|typedef\b))"
                        r"[A-Za-z_][^=;{}\n]*\([^;{}\n]*\)\s*;\s*(/\*.*)?$")


def c_files():
    return sorted((ROOT / "src").rglob("*.c"))


def apply() -> None:
    """In every src/ C file, write a named symbol by its readable name
    inside function bodies, `extern` lines and prototypes. Definitions,
    preprocessor lines, comments, strings, __asm__ labels and SDATA()
    arguments (stringified into the label) keep the address name."""
    keep, _ = header_rows()
    name_of = {r["symbol"]: r["name"] for r in keep}
    if not name_of:
        return
    token = re.compile(r"\b(" + "|".join(re.escape(s) for s in sorted(name_of, key=len, reverse=True)) + r")\b")
    changed_files = changed = 0
    for p in c_files():
        text = p.read_text()
        out, n = rewrite_bodies(text, token, name_of)
        if n:
            out = ensure_names_include(out, set(name_of.values()))
            p.write_text(out)
            changed_files += 1
            changed += n
    print(f"{changed} uses renamed in {changed_files} files")


NAMES_INCLUDE = re.compile(r'^#include "(names|common|engine|flags|card|save|gadgets|weapons)\.h"', re.M)


def ensure_names_include(text: str, names: set[str]) -> str:
    """TEXT with `#include "names.h"` added near the top when it uses a
    readable name before any header that brings names.h in."""
    code = strip_c(text)
    first = next((m.start() for m in re.finditer(r"\b[A-Za-z_]\w*\b", code) if m.group(0) in names), None)
    if first is None:
        return text
    inc = NAMES_INCLUDE.search(text)
    if inc and inc.start() < first:
        return text
    m = re.search(r'^#include [<"].*$', text, re.M)
    if m and m.start() < first:
        return text[:m.end()] + '\n#include "names.h"' + text[m.end():]
    return '#include "names.h"\n' + text


def rewrite_bodies(text: str, token, name_of) -> tuple[str, int]:
    """Replace TOKEN matches outside comments/strings: inside brace depth
    >= 1 of top-level function bodies on lines that are not declarations
    or preprocessor lines, and on `extern` lines and prototypes."""
    out, n, i, depth = [], 0, 0, 0
    L = len(text)
    line_start = 0
    cached = (-1, "", False)

    def line_info(start):
        nonlocal cached
        if cached[0] != start:
            end = text.find("\n", start)
            cached = (start, text[start:end if end >= 0 else L], logical_line_is_preprocessor(text, start))
        return cached[1], cached[2]
    while i < L:
        c = text[i]
        if text.startswith("/*", i):
            j = text.find("*/", i + 2)
            j = L if j < 0 else j + 2
            out.append(text[i:j]); i = j; continue
        if text.startswith("//", i):
            j = text.find("\n", i)
            j = L if j < 0 else j
            out.append(text[i:j]); i = j; continue
        if c in "\"'":
            j = i + 1
            while j < L and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            out.append(text[i:j + 1]); i = j + 1; continue
        if c == "\n":
            line_start = i + 1
        line, in_pp = line_info(line_start)
        if c == "{" and not in_pp:
            depth += 1
        elif c == "}" and not in_pp:
            depth -= 1
        m = token.match(text, i) if (c == "f" or c == "D") else None
        if m and (i == 0 or not (text[i - 1].isalnum() or text[i - 1] == "_")):
            if not in_pp and "__asm__" not in line and not text.endswith("SDATA(", 0, i) and (
                    (depth >= 1 and not DECL_LINE.match(line)) or EXTERN_LINE.match(line) or PROTO_LINE.match(line)):
                out.append(name_of[m.group(1)]); n += 1
            else:
                out.append(m.group(1))
            i = m.end(); continue
        out.append(c); i += 1
    return "".join(out), n


def logical_line_is_preprocessor(text: str, line_start: int) -> bool:
    """Is the physical line starting at LINE_START part of a preprocessor
    directive (its first line starts with `#`, continued with backslashes)?"""
    start = line_start
    while start >= 2 and text[start - 2] == "\\" and text[start - 1] == "\n":
        start = text.rfind("\n", 0, start - 1) + 1
    return text[start:start + 200].lstrip(" \t").startswith("#")


DEF_LINE = re.compile(r"^(?!extern\b)([A-Za-z_][^;\n]*?\b)(func_(?:L\d\d_)?[0-9A-Fa-f]{8})(\s*\()")


def apply_defs() -> None:
    """In every src/ C file, write a named function's definition with its
    readable name: `void func_L19_0041B078(...) {` becomes `void yeti_update(...) {`.
    names.h makes it the same symbol. Lines with an __asm__ label and
    prototypes keep the address name. Tools that find definitions read
    source through tools/srcnames.py."""
    keep, _ = header_rows()
    name_of = {r["symbol"]: r["name"] for r in keep if r["symbol"].startswith("func_")}
    changed_files = changed = 0
    for p in c_files():
        text = p.read_text()
        lines = text.split("\n")
        n = 0
        for i, line in enumerate(lines):
            m = DEF_LINE.match(line)
            if not m or m.group(2) not in name_of or "__asm__" in line:
                continue
            rest = line[m.end():]
            if line.rstrip().endswith(";") or DECL_LINE.match(line):
                continue
            # a definition: its body opens on this line or the next non-blank one
            nxt = next((l for l in lines[i + 1:] if l.strip()), "")
            if "{" not in rest and not nxt.lstrip().startswith("{") and not rest.rstrip().endswith(","):
                if not re.search(r"\)\s*$", rest) or nxt.strip().endswith(";"):
                    continue
            lines[i] = m.group(1) + name_of[m.group(2)] + m.group(3) + rest
            n += 1
        if n:
            out = ensure_names_include("\n".join(lines), set(name_of.values()))
            p.write_text(out)
            changed_files += 1
            changed += n
    print(f"{changed} definitions renamed in {changed_files} files")


def rename() -> None:
    """Carry a changed table into names.h and the sources: every use of a name names.h gives
    a symbol that now has another name (or none) goes back to the address name in code and to
    the new spelling in comments; then `header`, `apply-defs` and `apply` write the new names."""
    old = {n: s for n, s in re.findall(r"(?m)^#define (\w+)\s+(\w+)$",
                                       names_header.read(HEADER)) if n != "NAMES_H"}
    rows = read_table()
    named = {r["symbol"]: r["name"] for r in rows if r["tier"] != "candidate"}
    gone = {n: s for n, s in old.items() if named.get(s) != n}
    if gone:
        token = re.compile(r"\b(" + "|".join(re.escape(n) for n in sorted(gone, key=len, reverse=True)) + r")\b")
        lit = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
        files = changed = 0
        for d in ("src", "include", "nonmatching"):
            for p in sorted((ROOT / d).rglob("*")):
                if p.suffix not in (".c", ".h") or names_header.is_generated(p, HEADER):
                    continue
                text = p.read_text()
                n = 0

                def code(seg):
                    nonlocal n
                    out, k = token.subn(lambda m: gone[m.group(1)], seg)
                    n += k
                    return out

                def comment(seg):
                    nonlocal n
                    out, k = token.subn(lambda m: named.get(gone[m.group(1)], gone[m.group(1)]), seg)
                    n += k
                    return out
                parts, last = [], 0
                for m in lit.finditer(text):
                    parts.append(code(text[last:m.start()]))
                    seg = m.group(0)
                    parts.append(comment(seg) if seg.startswith("/") else seg)
                    last = m.end()
                parts.append(code(text[last:]))
                out = "".join(parts)
                if out != text:
                    p.write_text(out)
                    files += 1
                    changed += n
        print(f"{len(gone)} names changed or dropped: {changed} uses rewritten in {files} files")
    header()
    apply_defs()
    apply()


def lookup(args) -> None:
    rows = read_table()
    for a in args:
        hits = [r for r in rows if a in (r["symbol"], r["name"]) or a in r["alts"].split(",")]
        if not hits:
            print(f"{a}: no name")
        for r in hits:
            print(f"{r['symbol']}  {r['name']}  [{r['tier']}] {r['source']}: {r['evidence']}"
                  + (f"  (also: {r['alts']})" if r["alts"] else ""))


def main() -> None:
    args = sys.argv[1:]
    if not args:
        sys.exit(__doc__)
    cmd = {"header": header, "apply": apply, "apply-defs": apply_defs, "local": local,
           "check": check, "rename": rename}.get(args[0])
    if cmd:
        cmd()
    else:
        lookup(args)


if __name__ == "__main__":
    main()
