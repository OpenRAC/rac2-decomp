#!/usr/bin/env python3
"""Toolchain-free repository checks (no game data needed).

  python3 tests/check_repository.py

1. config/levels/functions.tsv and config/boot/functions.tsv parse: right column count,
   unique names, kinds in {boot, shared, level}, places NN:XXXXXXXX of a known level; so do
   the other releases' (config/pal/, config/us2/: docs/VERSIONS.md).
2. Every function of the two catalogues appears in src/**/*.c exactly once, as its C or as an
   INCLUDE_ASM marker (rac1-decomp's layout), and nothing else does. A release's own functions
   (func_PAL_..., func_US2_...) are in its src/<version>/ and only there; every other function
   of its catalogues is v1.01's, with the one definition src/ has for every release.
3. Nothing of the removed system comes back: no gzipped or generated data, no generated sources
   or fragments, no per-level copies, no per-batch or campaign documents, no file over 2.5 MB.

4. nonmatching/functional.tsv (C for the native port only, never counted) lists only functions
   that are still INCLUDE_ASM in src/, once each, with a file under nonmatching/functional/.

Exits nonzero, listing every problem, on failure.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import levels  # noqa: E402

KINDS = {"boot", "shared", "level"}
PLACE = re.compile(r"^(\d\d):([0-9A-F]{8})$")
NAME = r"(?:func_(?:(?:PAL|US2)_)?(?:L[0-9]{2}_)?[0-9A-F]{8}|sceIpuRestartDMA|_sysbitFlush)"
TAGS = {v["tag"]: k for k, v in levels.VERSIONS.items() if v["tag"]}      # PAL -> pal
DEFINITION = re.compile(rf"^(?:[A-Za-z_][^;=#]*?\b)?({NAME})\s*\(")    # the type may be on the line before


def check_catalogues(errors: list, config: str = "config") -> set:
    names = set()
    boot_file = ROOT / config / "boot/functions.tsv"
    level_file = ROOT / config / "levels/functions.tsv"
    seen = {}
    for n, line in enumerate(boot_file.read_text().splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        where = f"{boot_file.relative_to(ROOT)}:{n}"
        cols = line.split("\t")
        if len(cols) != 3:
            errors.append(f"{where}: {len(cols)} columns, expected 3")
            continue
        name, address, size = cols
        if not re.fullmatch(r"[0-9A-F]{8}", address) or not size.isdigit():
            errors.append(f"{where}: bad address or size in {line!r}")
        if name in seen:
            errors.append(f"{where}: duplicate name {name} (first at line {seen[name]})")
        seen.setdefault(name, n)
        names.add(name)
    seen = {}
    for n, line in enumerate(level_file.read_text().splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        where = f"{level_file.relative_to(ROOT)}:{n}"
        cols = line.split("\t")
        if len(cols) != 6:
            errors.append(f"{where}: {len(cols)} columns, expected 6")
            continue
        name, kind, size, fp, count, places = cols
        if kind not in KINDS:
            errors.append(f"{where}: kind {kind!r} not in {sorted(KINDS)}")
        if not size.isdigit() or not count.isdigit():
            errors.append(f"{where}: size or level count is not a number")
        if not re.fullmatch(r"[0-9a-f]{16}", fp):
            errors.append(f"{where}: bad fingerprint {fp!r}")
        if name in seen:
            errors.append(f"{where}: duplicate name {name} (first at line {seen[name]})")
        seen.setdefault(name, n)
        numbers = set()
        for p in places.split(","):
            m = PLACE.match(p)
            if not m:
                errors.append(f"{where}: place {p!r} is not NN:XXXXXXXX")
            elif int(m.group(1)) not in levels.NAMES:
                errors.append(f"{where}: place {p!r} is in unknown level {int(m.group(1))}")
            else:
                numbers.add(int(m.group(1)))
        if count.isdigit() and int(count) != len(numbers):
            errors.append(f"{where}: levels column {count}, places span {len(numbers)}")
        names.add(name)
    return names


def release_of(name: str) -> str:
    m = re.match(r"func_([A-Z0-9]+)_", name)
    return TAGS.get(m.group(1), "us") if m else "us"


def check_sources(known: dict, errors: list) -> set:
    """KNOWN: version -> the names of its catalogues. Returns the names still INCLUDE_ASM."""
    defined = {}
    still_asm = set()
    for path in sorted((ROOT / "src").rglob("*.c")):
        text = path.read_text(encoding="utf-8", errors="replace")
        relative = path.relative_to(ROOT).as_posix()
        for n, line in enumerate(text.splitlines(), 1):
            m = DEFINITION.match(line)
            if m and not line.rstrip().endswith(";") and not line.startswith(("extern", "typedef")):
                defined.setdefault(m.group(1), []).append(f"{relative}:{n}")
        for m in re.finditer(rf'^(?:INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT)\("[^"]*",\s*({NAME})\);', text, re.M):
            n = text[:m.start()].count("\n") + 1
            defined.setdefault(m.group(1), []).append(f"{relative}:{n} (asm)")
            if m.group(0).startswith("INCLUDE_ASM"):
                still_asm.add(m.group(1))
    for name, where in sorted(defined.items()):
        if len(where) > 1:
            errors.append(f"{name} appears {len(where)} times: {', '.join(where)}")
        release = release_of(name)
        top = where[0].split("/")[1]
        if release != "us" and top != release:
            errors.append(f"{name} ({where[0]}) is {release}'s own function: it belongs in src/{release}/")
        if release == "us" and top in TAGS.values():
            errors.append(f"{name} ({where[0]}) is v1.01's: one definition in src/ serves every release")
        if name not in known.get(release, ()):
            errors.append(f"{name} ({where[0]}) is in no catalogue of {release}")
    for version, names in known.items():
        for name in sorted(names - set(defined)):
            errors.append(f"{name} is in a catalogue of {version} but in no file of src/")
    c = sum(1 for w in defined.values() if not w[0].endswith("(asm)"))
    print(f"{len(defined)} functions in src/: {c} in C, {len(defined) - c} as INCLUDE_ASM")
    return still_asm


def check_functional(still_asm: set, errors: list) -> None:
    """nonmatching/functional.tsv: name<TAB>file lines. Functional C does what the retail function
    does without matching its bytes; it is kept out of src/ and out of every count, so a listed
    function must still be INCLUDE_ASM in src/ (a match replaces the row), and its file must exist
    under nonmatching/functional/."""
    table = ROOT / "nonmatching/functional.tsv"
    if not table.is_file():
        errors.append("nonmatching/functional.tsv is missing (the slot for functional C)")
        return
    seen = {}
    for n, line in enumerate(table.read_text().splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        where = f"nonmatching/functional.tsv:{n}"
        cols = line.split("\t")
        if len(cols) != 2:
            errors.append(f"{where}: {len(cols)} columns, expected name<TAB>file")
            continue
        name, rel = cols[0].strip(), cols[1].strip()
        if not re.fullmatch(NAME, name):
            errors.append(f"{where}: {name!r} is not a function name")
        if name in seen:
            errors.append(f"{where}: duplicate {name} (first at line {seen[name]})")
        seen.setdefault(name, n)
        if name not in still_asm:
            errors.append(f"{where}: {name} is not INCLUDE_ASM in src/ (matched or unknown): remove the row")
        if not rel.startswith("nonmatching/functional/") or not (ROOT / rel).is_file():
            errors.append(f"{where}: {rel!r} is not a file under nonmatching/functional/")
    print(f"{len(seen)} functions in nonmatching/functional.tsv")


# What the repository must not grow again (AGENTS.md, "Do not bring back what was removed").
FORBIDDEN_DIRS = ("candidates/", "scripts/", "trials/", "progress/levels/", "config/function-catalog/",
                  "config/level-native/", "config/function-evidence/")
FORBIDDEN_DOC = re.compile(r"(?i)(-C-LOT|-NATIVE-LOT|EVIDENCE|REGISTER|CAMPAIGN|RESERVATION|QUEUE|RECEIPT)")
MAX_BYTES = 2_500_000


def check_empty_barriers(text: str, path: str, errors: list) -> None:
    """Reject empty source loops used only to steer scheduling; ignore prose/literals."""
    code = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
                  ' ', text, flags=re.S)
    if re.search(r'\bdo\s*\{[\s;]*\}\s*while\s*\(\s*0[uUlL]*\s*\)', code):
        errors.append(f"{path}: empty do/while(0) source barrier; retain meaningful C (AGENTS.md)")


def check_hygiene(errors: list) -> None:
    import subprocess
    files = subprocess.run(["git", "ls-files"], cwd=ROOT, capture_output=True, text=True).stdout.split()
    if not files:          # not a git checkout: look at the tree
        files = [p.relative_to(ROOT).as_posix() for p in ROOT.rglob("*") if p.is_file() and ".git/" not in p.as_posix()]
    for f in files:
        path = ROOT / f
        if not path.exists():        # deleted in the working tree, not yet committed
            continue
        if f.startswith("scratch/") or any(part.startswith("_scratch") for part in Path(f).parts):
            errors.append(f"{f}: temporary experiments stay local; retain named C attempts in nonmatching/")
        if f.endswith((".gz", ".cfrag", ".iso", ".elf", ".bin", ".o")):
            errors.append(f"{f}: no {Path(f).suffix} files in the repository (generated or game data)")
        if f.startswith(FORBIDDEN_DIRS):
            errors.append(f"{f}: this directory belongs to the removed system (AGENTS.md)")
        if f.startswith("docs/") and FORBIDDEN_DOC.search(f):
            errors.append(f"{f}: no per-batch, evidence or campaign documents (AGENTS.md)")
        reports = {v["report"] for v in levels.VERSIONS.values()}
        if f.startswith("progress/") and f not in reports:
            errors.append(f"{f}: progress/ holds only the releases' report.json, written by tools/progress.py")
        if path.is_file() and path.stat().st_size > MAX_BYTES and f != "assets/rac2-logo.png":
            errors.append(f"{f}: {path.stat().st_size} bytes; generated data stays out of git")
        if f.startswith("src/") and f.endswith((".c", ".h")):
            text = path.read_text(errors="replace")
            if f.endswith(".c"):
                check_empty_barriers(text, f, errors)
            if re.search(r"\bLVL_\d+_[A-Z]", text):
                errors.append(f"{f}: per-level copies (LVL_ names); one definition per function (AGENTS.md)")


def main() -> int:
    errors: list = []
    check_hygiene(errors)
    known = {}
    for version, v in levels.VERSIONS.items():
        if (ROOT / v["config"] / "boot/functions.tsv").is_file():
            known[version] = check_catalogues(errors, v["config"])
            print(f"{version}: {len(known[version])} catalogue names")
    check_functional(check_sources(known, errors), errors)
    if errors:
        print(f"\n{len(errors)} problem(s):", file=sys.stderr)
        for e in errors[:200]:
            print("  " + e, file=sys.stderr)
        return 1
    print("repository checks passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
