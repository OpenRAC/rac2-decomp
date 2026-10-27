#!/usr/bin/env python3
"""
Does C do what the retail function does? A check by behaviour, for the native port: the C
need not match a byte, only leave the same memory, result and kept registers as retail does
from real calls of the game (OpenRAC's docs/port/BACKFILL.md, "The gate").

  python3 tools/fcheck.py check NAME [CANDIDATE.c] [--ulps N] [--work DIR]
  python3 tools/fcheck.py build NAME [CANDIDATE.c] --out DIR
  python3 tools/fcheck.py capture LIST [--script menu|newgame|all] [--frames N] [--force]
  python3 tools/fcheck.py source NAME
  python3 tools/fcheck.py scripts

`check` compiles NAME's source unit in src/ with the unit's own flags (config/cflags.txt),
CANDIDATE.c (a function and what it needs, e.g. a draft from nonmatching/functional/) taking
the place of NAME's INCLUDE_ASM line or C definition; when that does not compile, the
candidate on its own with the unit's flags. Without CANDIDATE it takes src/'s C as it is.
It then places NAME's section at 0x000A0000 (the kernel's area, which the game does not use)
and runs OpenRAC's test-only `openrac-fcheck` on NAME's captured call states: from each,
retail runs in the interpreter, then the candidate, and memory (but the dead stack), the
scratchpad, the result by the return type, the kept registers and the order of device
accesses and system calls are compared (each run on a fresh machine with the capture run's
hooks table and disc, so a hooked library function answers as it did in the capture). Exit
status: 0 SAME, 1 differs, 2 the candidate did not build or place, 3 no states, 4 every state
skipped.

Placement. Each relocation is resolved against retail's addresses:
- a named symbol: the value NAME's own C needs to read as retail's bytes (tools/build.py's
  derivation, when NAME is matched), the boot's function table, the values the boot build
  derived (build/boot/placed.json), those other matched functions of the unit need, or the
  address its name states;
- another function's section of the unit: that function's retail address; a static helper
  with none is placed after NAME;
- a writable section of the unit (.data, .sdata, .bss, .sbss): where retail has it, as this
  function's own C (else the unit's other matched functions) places it: one unit's data is
  shared by its functions, and retail's copy is the live one. A unit with no such placement
  gets its section in the kernel area, which the note says;
- a read-only section (.rodata: strings, constants, switch jump tables): copied after NAME
  with its own relocations resolved, so a jump table's entries go to the placed code;
- a $gp-relative reference (-G8 units, R_MIPS_GPREL16/LITERAL): the target must be within
  $gp's 64 KB window (retail's $gp, 0x1AEFF0). A read-only constant is used where retail has
  the same bytes there (the unit's own placement, else core.lit / .lit); anything else out of
  range stops the build ("LINK ...").

`capture` plays the US v1.01 disc (baserom/SCUS_972.68.iso) headless in the interpreter
(`openrac-boot --capture`, no window) and writes call states of the listed functions (names,
one a line) into build/fcheck/states/<script>/ ($RAC2_FCHECK_STATES overrides the root): the
boot and title, the main menu's pages (Load, Options, New Game's no-card question) and New
Game up to the first level's load, never past it. Each run is cut into phases and takes the
calls numbered 1 and 2 of each phase (`--capture-phases`, `--capture-spread`), so a function
called every frame has states from each part of the run. A function a run never calls gets
a NAME.none marker there. Boot functions only for now: level programs (func_LNN_, and boot
functions in the memory a level replaces from 0x1A7C80, once it is loaded) are not captured.

Needs: OpenRAC's interpreter built (cmake -S tools/interpreter -B build/interpreter in
OpenRAC; $OPENRAC_ROOT, default ~/Projects/RAC/OpenRAC), the compiler (docs/BUILDING.md;
$RAC2_LINUX runs it, e.g. "docker exec rac2-gate"), build/boot/placed.json from
`tools/build.py boot`, and the disc image. Test-only: nothing here is linked or shipped.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import struct
import subprocess
import sys
import zlib
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import elf  # noqa: E402
import levels  # noqa: E402

OPENRAC = Path(os.environ.get("OPENRAC_ROOT", str(Path.home() / "Projects/RAC/OpenRAC")))
BOOT = OPENRAC / "build/interpreter/openrac-boot"
FCHECK = OPENRAC / "build/interpreter/openrac-fcheck"
HOOKS = OPENRAC / "tools/interpreter/games/SCUS_972.68.hooks"
DISC = ROOT / "baserom/SCUS_972.68.iso"
WORK = ROOT / "build/fcheck"
BASE = 0x000A0000          # where the candidate goes: the kernel's area, unused by the game
LIMIT = 0x000F0000
GP = levels.GP             # 0x1AEFF0, the boot's (and every level's) $gp
STATES_PER_PHASE = 2
# Instructions retail may take from a state (about eight frames of the EE): a call that takes
# more waits for an interrupt, a frame or the disc, which openrac-fcheck does not deliver, and
# the state is skipped.
RETAIL_LIMIT = 40_000_000

# Pad bits: Start 8, Up 10, Right 20, Down 40, Left 80, Triangle 1000, Cross 4000.
# Past the splash, the movies and the title to the main menu (New Game selected).
TO_MENU = ["300:4000:10", "500:8:10", "700:4000:10", "900:8:10"]
SCRIPTS = {
    # The main menu's pages: Load (no card: "Go back?"), Options (moved through, settings
    # changed), New Game's "No Memory Card ... Continue anyway?" question, each backed out of.
    "menu": {"frames": 2300, "phases": [0, 900, 1400],
             "presses": TO_MENU + ["1000:40:8", "1050:4000:8", "1150:20:8", "1200:1000:8",
                                   "1300:40:8", "1400:4000:8", "1450:20:8", "1500:40:8", "1550:20:8",
                                   "1600:40:8", "1650:80:8", "1700:10:8", "1800:1000:8", "1900:10:8",
                                   "1950:10:8", "2000:4000:8", "2100:20:8", "2150:80:8", "2200:1000:8"]},
    # New Game, Yes, and the first level's load, stopped before the level runs (its program
    # replaces the boot's memory from 0x1A7C80 at about frame 1650).
    "newgame": {"frames": 1650, "phases": [950, 1300],
                "presses": TO_MENU + ["950:4000:10", "1000:4000:10"]},
}
SHF_WRITE = 1
STT_FUNC, STT_SECTION = 2, 3
SHN_ABS = 0xFFF1


class Link(Exception):
    """The candidate cannot be placed (the message starts with LINK)."""


def states_root() -> Path:
    return Path(os.environ.get("RAC2_FCHECK_STATES") or WORK / "states")


# --- The boot's functions and their sources -------------------------------------------------

@lru_cache(maxsize=None)
def boot_functions() -> dict[str, tuple[int, int]]:
    return {n: (a, s) for n, a, s in levels.read_boot_functions()}


@lru_cache(maxsize=None)
def placed() -> dict:
    p = ROOT / "build/boot/placed.json"
    return json.loads(p.read_text()) if p.is_file() else {"functions": {}, "values": {}}


def retail_bytes(address: int, size: int) -> bytes:
    return levels.boot_bytes(address, size)


STUB = r'^(?:INCLUDE_ASM|ASM_FUNC)\("[^"]*",\s*{name}\);[ \t]*$'
DEFINITION = re.compile(r"^(?:[A-Za-z_][^;=#]*?\b)?([A-Za-z_]\w*)\s*\(")


@lru_cache(maxsize=None)
def sources() -> dict[str, tuple[Path, str]]:
    """Boot function name -> (its unit in src/, "c" or "asm")."""
    names = boot_functions()
    out: dict[str, tuple[Path, str]] = {}
    for d in ("core", "game", "levels/shared"):
        for path in sorted((ROOT / "src" / d).rglob("*.c")):
            text = path.read_text(errors="replace")
            for m in re.finditer(r'^(?:INCLUDE_ASM|ASM_FUNC|LINKER_REMNANT)\("[^"]*",\s*(\w+)\);', text, re.M):
                if m.group(1) in names:
                    out.setdefault(m.group(1), (path, "asm"))
            for line in text.splitlines():
                m = DEFINITION.match(line)
                if (m and m.group(1) in names and not line.rstrip().endswith(";")
                        and not line.startswith(("extern", "typedef"))):
                    out.setdefault(m.group(1), (path, "c"))
    return out


def find_definition(text: str, name: str) -> tuple[int, int] | None:
    """The span of NAME's C definition: from its header (and a type alone on the line before)
    through the brace that closes its body (and the rest of that line)."""
    lines = text.splitlines(keepends=True)
    at = 0
    for i, line in enumerate(lines):
        m = DEFINITION.match(line)
        if m and m.group(1) == name and not line.rstrip().endswith(";") and not line.startswith(("extern", "typedef")):
            start = at
            if i and re.fullmatch(r"[A-Za-z_][\w \t\*]*\n", lines[i - 1]) and not lines[i - 1].startswith(("#", "extern", "typedef")):
                start -= len(lines[i - 1])
            end = body_end(text, text.find("{", at))
            if end is None:
                return None
            nl = text.find("\n", end)
            return start, len(text) if nl < 0 else nl + 1
        at += len(line)
    return None


def body_end(text: str, k: int) -> int | None:
    """Just past the brace that closes the one at K (strings, characters and comments skipped)."""
    if k < 0:
        return None
    depth, n = 0, len(text)
    while k < n:
        c = text[k]
        if text.startswith("/*", k):
            k = text.find("*/", k + 2)
            if k < 0:
                return None
            k += 2
            continue
        if text.startswith("//", k):
            k = text.find("\n", k)
            if k < 0:
                return None
            continue
        if c in "\"'":
            k += 1
            while k < n and text[k] != c:
                k += 2 if text[k] == "\\" else 1
        elif c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return k + 1
        k += 1
    return None


def splice(text: str, name: str, candidate: str) -> str:
    """The unit's text with CANDIDATE in place of NAME's INCLUDE_ASM line or C definition."""
    m = re.search(STUB.format(name=re.escape(name)), text, re.M)
    if m:
        return text[:m.start()] + candidate.rstrip("\n") + "\n" + text[m.end():]
    span = find_definition(text, name)
    if span is None:
        raise Link(f"LINK {name}: neither an INCLUDE_ASM stub nor a C definition in its unit")
    return text[:span[0]] + candidate.rstrip("\n") + "\n" + text[span[1]:]


# --- Compiling -------------------------------------------------------------------------------

def compile_text(text: str, unit: Path, obj: Path, includes: list[Path] | None = None) -> tuple[bool, str]:
    """TEXT compiled as UNIT is (its flags, its directory on the include path) into OBJ, through
    $RAC2_LINUX as tools/build.py compiles. Returns (ok, the compiler's messages)."""
    obj.parent.mkdir(parents=True, exist_ok=True)
    copy = obj.with_suffix(".c")
    copy.write_text(text)
    flags = build.flags_for(unit)
    cargs, aargs = build.split_flags(flags)
    C, S = build.COMPILER, build.SDK_COMPILER
    inc = " ".join(f"-I'{d}'" for d in [unit.parent, *(includes or [])])
    assemble = shlex.join([str(C / "as"), *aargs, "-o", "x.o", "x.s"])
    if flags.startswith("sdk"):
        front = f"'{S}/xgcc' -B'{S}/' -S {shlex.join(cargs)} -I'{ROOT}/include' -I'{S}/include' {inc} x.c -o x.s"
    else:
        front = (f"'{C}/cpp' -I'{C}/include' -I'{ROOT}/include' {inc} x.c > x.i; "
                 f"'{C}/cc1' -quiet {shlex.join(cargs)} x.i -o x.s")
    script = (f"set -e; t=$(mktemp -d); trap 'rm -rf $t' EXIT; cd $t; cp '{copy}' x.c; {front}; "
              f"cp x.s '{obj.with_suffix('.s')}'; {assemble}; cp x.o '{obj}'")
    if obj.exists():
        obj.unlink()
    runner = shlex.split(os.environ.get("RAC2_LINUX", ""))
    r = subprocess.run([*runner, "bash", "-c", script], capture_output=True, text=True)
    return r.returncode == 0 and obj.is_file(), (r.stdout + r.stderr)[-4000:]


def derived_values(obj: dict, name: str) -> dict[str, int] | None:
    """The symbol values (and "§section" placements) NAME's section in OBJ needs to read as the
    retail bytes at NAME's address (tools/build.py's derivation), or None when it does not."""
    sym = next((s for s in obj["symbols"] if s["name"] == name and s["type"] == STT_FUNC and 0 < s["section"] < 0xFF00), None)
    if sym is None or name not in boot_functions():
        return None
    address = boot_functions()[name][0]
    values, why = placement().derive(obj, sym["section"], address - sym["value"])
    return None if why else values


@lru_cache(maxsize=None)
def placement():
    return build.Placement("boot", elf.read(levels.BOOT))


def unit_values(unit: Path, name: str) -> tuple[dict[str, int], dict[str, int]]:
    """From the unit's matched build (build/obj/): what NAME's own C needs (empty when NAME is
    not matched C), and the agreed values the unit's other placed functions need."""
    try:
        obj = elf.read_object(build.compile_c(unit))
    except SystemExit:
        return {}, {}
    own = derived_values(obj, name) or {}
    others: dict[str, set[int]] = {}
    done = set(placed().get("functions", {}))
    for s in obj["symbols"]:
        if s["type"] == STT_FUNC and s["name"] != name and s["name"] in done and 0 < s["section"] < 0xFF00:
            for k, v in (derived_values(obj, s["name"]) or {}).items():
                others.setdefault(k, set()).add(v)
    return own, {k: next(iter(v)) for k, v in others.items() if len(v) == 1}


# --- Placing ---------------------------------------------------------------------------------

def gp_literal(data: bytes) -> int | None:
    """An address in $gp's window where retail's read-only literal pools (core.lit, .lit) hold
    DATA, aligned to its size."""
    for sec in placement().image["sections"]:
        if sec["name"] not in ("core.lit", ".lit"):
            continue
        lo, hi = max(sec["address"], GP - 0x8000), min(sec["address"] + sec["size"], GP + 0x8000)
        blob = retail_bytes(sec["address"], sec["size"])
        step = min(len(data), 8) or 4
        for a in range(lo + (-lo) % step, hi - len(data) + 1, step):
            if blob[a - sec["address"]:a - sec["address"] + len(data)] == data:
                return a
    return None


# Bytes a gp-relative instruction reads: lb lh lw lbu lhu lwu ld lq lwc1 ldc1 (and stores).
WIDTH = {0x20: 1, 0x24: 1, 0x28: 1, 0x21: 2, 0x25: 2, 0x29: 2, 0x23: 4, 0x27: 4, 0x2B: 4, 0x31: 4,
         0x39: 4, 0x37: 8, 0x3F: 8, 0x35: 8, 0x3D: 8, 0x1E: 16, 0x1F: 16}


class Placer:
    """Places NAME's section of a compiled object at BASE, as the module docstring says.

    NAMED(symbol) -> retail value or None; FUNCTION(name) -> retail address or None;
    WRITABLE(section name) -> retail address of the unit's writable section or None;
    LITERAL(bytes, section name, offset) -> an address in $gp's window holding them, or None."""

    def __init__(self, obj: dict, name: str, named, function, writable, literal, base: int = BASE, limit: int = LIMIT):
        self.obj, self.name = obj, name
        self.named, self.function, self.writable, self.literal = named, function, writable, literal
        self.base, self.limit = base, limit
        self.where: dict[int, int] = {}       # section index -> address
        self.copied: list[int] = []           # sections laid out in the image, in order
        self.image = bytearray()
        self.notes: list[str] = []
        sym = next((s for s in obj["symbols"] if s["name"] == name and s["type"] == STT_FUNC
                    and 0 < s["section"] < 0xFF00), None)
        if sym is None:
            raise Link(f"LINK {name} is not defined by the candidate")
        self.own = sym["section"]
        self.copy(self.own)
        self.entry = self.where[self.own] + sym["value"]

    def copy(self, index: int) -> int:
        sec = self.obj["sections"][index]
        align = max(sec.get("align", 4) or 4, 4) if self.image else 1
        at = self.base + len(self.image)
        at += (-at) % align
        self.image += bytes(at - self.base - len(self.image))
        self.where[index] = at
        self.image += sec["data"] if sec["type"] != elf.SHT_NOBITS else bytes(sec["size"])
        self.copied.append(index)
        if self.base + len(self.image) > self.limit:
            raise Link(f"LINK the candidate's code and data do not fit below {self.limit:#010x}")
        return at

    def section(self, index: int) -> int:
        if index in self.where:
            return self.where[index]
        sec = self.obj["sections"][index]
        if sec["name"].startswith(".text"):
            f = next((s for s in self.obj["symbols"] if s["section"] == index and s["type"] == STT_FUNC
                      and s["value"] == 0), None)
            a = self.function(f["name"]) if f and f["name"] != self.name else None
            if a is not None:
                self.where[index] = a
                return a
            self.notes.append(f"helper {f['name'] if f else sec['name']} placed after the function")
            return self.copy(index)
        if sec.get("flags", 0) & SHF_WRITE or sec["type"] == elf.SHT_NOBITS:
            a = self.writable(sec["name"])
            if a is not None:
                self.where[index] = a
                return a
            self.notes.append(f"{sec['name']} has no retail placement: placed fresh in the kernel area")
        return self.copy(index)

    def value(self, sym: dict) -> int:
        if sym["type"] == STT_SECTION:
            return self.section(sym["section"])
        n = sym["name"]
        if n == self.name:
            return self.entry
        if n:
            v = self.named(n)
            if v is not None:
                return v
        if 0 < sym["section"] < 0xFF00:
            return self.section(sym["section"]) + sym["value"]
        if sym["section"] == SHN_ABS:
            return sym["value"]
        raise Link(f"LINK {n or '?'} has no retail address")

    def relocate(self) -> None:
        done = 0
        while done < len(self.copied):
            self.apply(self.copied[done])
            done += 1

    def apply(self, index: int) -> None:
        obj = self.obj
        off = self.where[index] - self.base
        orig = bytes(obj["sections"][index]["data"])
        rel = obj["relocations"].get(index, [])
        word = lambda at: struct.unpack_from("<I", orig, at)[0]
        put = lambda at, v: struct.pack_into("<I", self.image, off + at, v & 0xFFFFFFFF)
        sext = build.sext
        for k, (at, kind, s) in enumerate(rel):
            sym = obj["symbols"][s]
            w = word(at)
            if kind in (elf.R_MIPS_GPREL16, 8):          # R_MIPS_LITERAL: the same, for .lit4/.lit8
                target = self.gp_target(sym, sext(w & 0xFFFF), w)
                d = target - GP
                if not -0x8000 <= d < 0x8000:
                    raise Link(f"LINK $gp-relative access to {target:#010x} ({sym['name'] or obj['sections'][sym['section']]['name']}) "
                               "is outside $gp's window: give the data a retail D_ address")
                put(at, (w & 0xFFFF0000) | (d & 0xFFFF))
                continue
            v = self.value(sym)
            if kind == elf.R_MIPS_32:
                put(at, w + v)
            elif kind == elf.R_MIPS_26:
                target = v + ((w & 0x3FFFFFF) << 2)
                if (target ^ (self.base + off + at)) & 0xF0000000:
                    raise Link("LINK a jump out of its 256 MB region")
                put(at, (w & 0xFC000000) | ((target >> 2) & 0x3FFFFFF))
            elif kind == elf.R_MIPS_HI16:
                # Paired in the object's order with the next %lo of the same symbol, as the linker does.
                lo = next((o for o, t, ss in rel[k + 1:] if t == elf.R_MIPS_LO16 and ss == s), None)
                if lo is None:
                    raise Link(f"LINK a %hi at +{at:#x} without its %lo")
                ahl = ((w & 0xFFFF) << 16) + sext(word(lo) & 0xFFFF)
                put(at, (w & 0xFFFF0000) | (((v + ahl + 0x8000) >> 16) & 0xFFFF))
            elif kind == elf.R_MIPS_LO16:
                put(at, (w & 0xFFFF0000) | ((v + sext(w & 0xFFFF)) & 0xFFFF))
            else:
                raise Link(f"LINK relocation type {kind} not handled")

    def gp_target(self, sym: dict, addend: int, ins: int) -> int:
        """Where a $gp-relative reference goes. A read-only section of the candidate (a literal)
        is not reachable from where it is copied: the same bytes in retail's window are used."""
        index = sym["section"]
        sec = self.obj["sections"][index] if 0 < index < 0xFF00 else None
        if (sym["type"] == STT_SECTION and sec is not None and not sec["name"].startswith(".text")
                and not sec.get("flags", 0) & SHF_WRITE and sec["type"] != elf.SHT_NOBITS):
            width = WIDTH.get(ins >> 26, 4)
            data = bytes(sec["data"][addend:addend + width])
            a = self.literal(data, sec["name"], addend)
            if a is None:
                raise Link(f"LINK the constant {data.hex()} in {sec['name']} (read $gp-relative) is nowhere in retail's $gp window")
            return a
        return self.value(sym) + addend

    def segments(self) -> list[tuple[int, bytes]]:
        return [(self.base, bytes(self.image))]


def returns(name: str, text: str) -> str:
    """openrac-fcheck's --returns for NAME's definition in TEXT: void, int, long (64 bits and
    more: EE GCC's long and long long, double), or float."""
    lines = text.splitlines()
    head = None
    for i, line in enumerate(lines):
        m = DEFINITION.match(line)
        if m and m.group(1) == name and not line.rstrip().endswith(";") and not line.startswith(("extern", "typedef")):
            head = line[:line.index(name)]
            if not head.strip() and i:
                head = lines[i - 1]
            break
    if head is None:
        return "void"
    if "*" in head:
        return "int"
    words = [w for w in head.split() if w not in ("const", "volatile", "extern", "signed", "unsigned",
                                                   "register", "static", "inline", "__inline__")]
    w = " ".join(words)
    if w == "void":
        return "void"
    if w in ("float", "f32"):
        return "float"
    if w in ("long", "long long", "long int", "u64", "s64", "u128", "s128", "double", "f64", "u_long"):
        return "long"
    if w.startswith(("struct", "union")):
        return "void"
    return "int"


# --- Building a candidate ----------------------------------------------------------------------

def build_candidate(name: str, candidate: Path | None, out: Path, includes: list[Path] | None = None) -> dict:
    """Compile and place NAME (src/'s C, or CANDIDATE in its unit), writing OUT/code.bin and
    OUT/placed.json; returns the placed.json dict. Raises Link."""
    src = sources().get(name)
    if src is None:
        raise Link(f"LINK {name} is not a boot function in src/ (config/boot/functions.tsv)")
    unit, kind = src
    out.mkdir(parents=True, exist_ok=True)
    text = unit.read_text(errors="replace")
    mode = "src"
    if candidate is None:
        if kind != "c":
            raise Link(f"LINK {name} is still assembly in {unit.relative_to(ROOT)}: give a candidate")
        ok, log = compile_text(text, unit, out / "unit.o")
        cand_text = text
    else:
        cand_text = candidate.read_text(errors="replace")
        ok, log = compile_text(splice(text, name, cand_text), unit, out / "unit.o")
        mode = "in its unit"
        if not ok:
            ok2, log2 = compile_text(cand_text, unit, out / "alone.o", [candidate.parent, *(includes or [])])
            if ok2:
                ok, mode = True, "on its own (with the unit's flags)"
                (out / "unit.log").write_text(log)
                (out / "unit.o").unlink(missing_ok=True)
                os.replace(out / "alone.o", out / "unit.o")
            else:
                log += "\n--- on its own ---\n" + log2
    (out / "log.txt").write_text(log)
    if not ok:
        raise Link(f"COMPILE failed ({unit.relative_to(ROOT)}):\n" + "\n".join(log.strip().splitlines()[-12:]))
    obj = elf.read_object(out / "unit.o")
    own, others = unit_values(unit, name)
    table = boot_functions()
    derived = {k: int(v, 16) for k, v in placed().get("values", {}).items()}

    def named(n: str) -> int | None:
        for d in (own,):
            if n in d:
                return d[n] & 0xFFFFFFFF
        if n in table:
            return table[n][0]
        if n in derived:
            return derived[n]
        if n in others:
            return others[n] & 0xFFFFFFFF
        return build.address_in_name(n)

    def function(n: str) -> int | None:
        return table[n][0] if n in table else named(n)

    def writable(sec: str) -> int | None:
        for d in (own, others):
            if "§" + sec in d:
                return d["§" + sec] & 0xFFFFFFFF
        return None

    def literal(data: bytes, sec: str, offset: int) -> int | None:
        for d in (own, others):
            b = d.get("§" + sec)
            if b is not None and GP - 0x8000 <= b + offset < GP + 0x8000 and retail_bytes(b + offset, len(data)) == data:
                return b + offset
        return gp_literal(data)

    p = Placer(obj, name, named, function, writable, literal)
    p.relocate()
    segs = p.segments()
    files = []
    for i, (a, data) in enumerate(segs):
        f = out / f"code{i}.bin"
        f.write_bytes(data)
        files.append([f.name, a])
    info = {"entry": p.entry, "segments": files, "unit": str(unit.relative_to(ROOT)), "mode": mode,
            "flags": build.flags_for(unit), "returns": returns(name, cand_text), "notes": p.notes,
            "own_values": bool(own)}
    (out / "placed.json").write_text(json.dumps(info, indent=1))
    return info


# --- Capturing ----------------------------------------------------------------------------------

def states_of(name: str, root: Path | None = None) -> list[Path]:
    root = root or states_root()
    return sorted(root.glob(f"*/{name}.*.snap"))


def capture_line(name: str) -> str | None:
    """openrac-boot's capture list line for a boot function: address, bytes compared, their
    CRC-32 (a level's code at the address then is not taken), name, states per phase."""
    if name not in boot_functions():
        return None
    a, size = boot_functions()[name]
    k = max(4, min(size, 256))
    return f"{a:08x} {k} {zlib.crc32(retail_bytes(a, k)):08x} {name} {STATES_PER_PHASE}"


def capture(names: list[str], script: str, frames: int | None = None, force: bool = False,
            root: Path | None = None) -> tuple[int, int]:
    """One headless run of SCRIPT taking states of NAMES (those it has not run for yet).
    Returns (functions called, functions asked)."""
    s = SCRIPTS[script]
    out = (root or states_root()) / script
    out.mkdir(parents=True, exist_ok=True)
    todo = [n for n in dict.fromkeys(names) if force or not (list(out.glob(f"{n}.*.snap")) or (out / f"{n}.none").exists())]
    lines = [l for l in (capture_line(n) for n in todo) if l]
    if not lines:
        return 0, 0
    lst = out / "capture.list"
    lst.write_text("\n".join(lines) + "\n")
    calls = out / "calls.tsv.new"
    cmd = [str(BOOT), str(DISC), "--hooks", str(HOOKS), "--no-card", "--ntsc", "--gs-threads", "2",
           "--frames", str(frames or s["frames"]), "--report", "0",
           "--capture", str(lst), str(out), "--capture-phases", ",".join(map(str, s["phases"])),
           "--capture-spread", "--calls", str(calls)]
    for p in s["presses"]:
        cmd += ["--press", p]
    with open(out / "capture.log", "a") as log:
        log.write("$ " + shlex.join(cmd) + "\n")
        log.flush()
        subprocess.run(cmd, stdout=log, stderr=subprocess.STDOUT)
    got = 0
    counted = {}
    if calls.is_file():
        for line in calls.read_text().splitlines():
            c = line.split("\t")
            counted[c[0]] = int(c[1])
        with open(out / "calls.tsv", "a") as f:
            f.write(calls.read_text())
        calls.unlink()
    for line in lines:
        n = line.split()[3]
        if counted.get(n, 0) and list(out.glob(f"{n}.*.snap")):
            got += 1
        elif n in counted:
            (out / f"{n}.none").write_text(f"not called in the {script} run\n")
    return got, len(lines)


# --- Checking -------------------------------------------------------------------------------------

def check(name: str, candidate: Path | None, ulps: int = 0, work: Path | None = None,
          includes: list[Path] | None = None) -> int:
    states = states_of(name)
    if not states:
        marked = list(states_root().glob(f"*/{name}.none"))
        print(f"{name}: NOT CALLED in the capture runs ({', '.join(sorted(p.parent.name for p in marked)) or 'none run yet'}); "
              "cannot check by behaviour")
        return 3
    work = work or WORK / "work" / name
    try:
        info = build_candidate(name, candidate, work, includes)
    except Link as e:
        print(str(e))
        return 2
    # The capture run's hooks and disc: a hooked function's service answers in both runs.
    cmd = [str(FCHECK), "--hooks", str(HOOKS), "--disc", str(DISC), "--limit", str(RETAIL_LIMIT),
           "--entry", f"{info['entry']:x}", "--returns", info["returns"]]
    if ulps:
        cmd += ["--ulps", str(ulps)]
    for f, a in info["segments"]:
        cmd += ["--code", f"{work / f}@{a:x}"]
    cmd += [str(s) for s in states]
    r = subprocess.run(cmd, capture_output=True, text=True)
    text = r.stdout.replace(str(states_root()) + "/", "")
    if info["notes"] or info["mode"] != "src":
        print(f"{name}: compiled {info['mode']}" + "".join("; " + n for n in info["notes"]))
    print(text.strip() or r.stderr.strip())
    if r.returncode == 0:
        m = re.search(r"compared (\d+) of", r.stdout)
        print(f"{name}: SAME on {m.group(1) if m else '?'} real calls")
    elif r.returncode == 4:
        print(f"{name}: NOTHING COMPARED (every state skipped)")
    return r.returncode


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("check")
    p.add_argument("name")
    p.add_argument("candidate", nargs="?", type=Path)
    p.add_argument("--ulps", type=int, default=0)
    p.add_argument("--work", type=Path)
    p.add_argument("--include", type=Path, action="append", default=[],
                   help="another directory for the candidate's #include \"...\" (where its file came from)")
    p = sub.add_parser("build")
    p.add_argument("name")
    p.add_argument("candidate", nargs="?", type=Path)
    p.add_argument("--out", type=Path, required=True)
    p = sub.add_parser("capture")
    p.add_argument("list", type=Path)
    p.add_argument("--script", default="all", choices=["all", *SCRIPTS])
    p.add_argument("--frames", type=int)
    p.add_argument("--force", action="store_true")
    p = sub.add_parser("source", help="NAME's unit, whether it is C or assembly there, and its definition's span")
    p.add_argument("name")
    sub.add_parser("scripts")
    a = ap.parse_args()
    if a.cmd == "check":
        return check(a.name, a.candidate.resolve() if a.candidate else None, a.ulps, a.work,
                     [d.resolve() for d in a.include])
    if a.cmd == "build":
        try:
            print(json.dumps(build_candidate(a.name, a.candidate.resolve() if a.candidate else None, a.out.resolve())))
        except Link as e:
            print(str(e))
            return 2
        return 0
    if a.cmd == "capture":
        names = [l.split()[0] for l in a.list.read_text().splitlines() if l.strip() and not l.startswith("#")]
        for s in (SCRIPTS if a.script == "all" else [a.script]):
            got, asked = capture(names, s, a.frames, a.force)
            print(f"{s}: {got} of {asked} functions called")
        return 0
    if a.cmd == "source":
        if a.name not in sources():
            print(json.dumps({"name": a.name}))
            return 2
        unit, kind = sources()[a.name]
        span = find_definition(unit.read_text(errors="replace"), a.name) if kind == "c" else None
        print(json.dumps({"name": a.name, "unit": str(unit), "kind": kind, "span": span,
                          "placed": a.name in placed().get("functions", {})}))
        return 0
    if a.cmd == "scripts":
        print(json.dumps(SCRIPTS, indent=1))
        return 0
    return 2


if __name__ == "__main__":
    sys.exit(main())
