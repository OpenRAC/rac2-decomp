#!/usr/bin/env python3
"""
Does C do what the retail function does? A check by behaviour, for the native port: the C
need not match a byte, only leave the same memory, result and kept registers as retail does
from real calls of the game (OpenRAC's docs/port/BACKFILL.md, "The gate").

  python3 tools/fcheck.py check NAME [CANDIDATE.c] [--ulps N] [--work DIR] [--retail]
  python3 tools/fcheck.py build NAME [CANDIDATE.c] --out DIR [--level N]
  python3 tools/fcheck.py capture LIST [--script menu|newgame|level00|all] [--frames N] [--force]
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
skipped. `--retail` is the harness's self-test: retail's own bytes of NAME, moved to 0x000A0000,
are the candidate (CANDIDATE, or src/'s C, gives only the return type); a DIFFERS on it is the
harness's or the states', never the C's.

Programs. A state is of the program the run had loaded where NAME was called: a level's run
(level00) takes a function with a place in that level's program there (config/levels/
functions.tsv: func_LNN_ names, and boot and shared functions with a NN: place), so its states
are of the level; every other state is of the boot (a boot run's, or a resident boot function's
in a level's run: the boot's memory below 0x1A7C80, which a level's program does not replace).
`check` builds NAME once for each program its states are of, against that program's addresses,
and the verdict is the worst: DIFFERS on any, else did not build, else SAME. In a level, retail
is the level's program (baserom/levels/NN_*/, its sections as tools/build.py's reference) above
0x1A7C80 and the boot's below.

Placement. Each relocation is resolved against retail's addresses in the program:
- a named symbol: the value NAME's own C needs to read as retail's bytes (tools/build.py's
  derivation, when NAME is matched); in a level, for a boot function's own copy there, what
  its boot address is in the copy (the copy is the same code: its references pair in order
  with the boot's, copy_pairs; the level may use its own variant of a callback where the
  catalogue also places a copy of the boot's); the program's function table (a level's: its
  places, and the resident boot functions below 0x1A7C80); the values the program's build
  derived (build/boot/placed.json, build/NN_*/placed.json from `tools/build.py level NN`); in a
  level the boot build's values that hold there (below 0x1A7C80, or moved as below); those
  other matched functions of the unit need; or the address its name states where the program
  has it (in a level: D_LNN_ of that level and boot addresses below 0x1A7C80; a boot address
  above it is moved to where the level's copies of boot code have it, copy_map: a boot
  function's to its place in the level, else to what the copies call there, data to the
  paired address, or inside a structure the distance pairs on both sides agree on);
- another function's section of the unit: that function's retail address; a static helper
  with none is placed after NAME;
- a writable section of the unit (.data, .sdata, .bss, .sbss): where retail has it, as this
  function's own C (else the unit's other matched functions) places it: one unit's data is
  shared by its functions, and retail's copy is the live one. A unit with no such placement
  gets its section in the kernel area, which the note says;
- a read-only section (.rodata: strings, constants, switch jump tables): copied after NAME
  with its own relocations resolved, so a jump table's entries go to the placed code;
- a variable the candidate defines in a writable section under a name with a retail address
  (D_XXXXXXXX, an sda one among them, even when the reference names the section, as a static's
  or an initialised small-data global's does): that address. An sda alias D_XXXXXXXX_sda or
  D_XXXXXXXX__gp is D_XXXXXXXX;
- a name none of these places (a near miss's ref_LNN_XXXXXXXX_kk, the kk-th external of a
  function): the value retail's bytes give it under the candidate's relocations, its
  instructions aligned to retail's by kind (the note names each value so read);
- a $gp-relative reference (-G8 units, R_MIPS_GPREL16/LITERAL): the target must be within
  $gp's 64 KB window (retail's $gp, 0x1AEFF0). A read-only constant is used where retail has
  the same bytes there (the unit's own placement, else core.lit / .lit, in a level its lit at
  0x1A7C80); anything else out of range stops the build ("LINK ...").

`capture` plays the US v1.01 disc (baserom/SCUS_972.68.iso) headless in the interpreter
(`openrac-boot --capture`, no window) and writes call states of the listed functions (names,
one a line, optionally followed by the states wanted per phase) into build/fcheck/states/
<script>/ ($RAC2_FCHECK_STATES overrides the root). menu: the boot and title, the main menu's
pages (Load, Options, New Game's no-card question); newgame: New Game up to the first level's
load, never past it; level00: New Game into level 00 (Aranos, the tutorial), played to frame
7000 (running, jumping, the wrench, the pause menu, weapons, the map: SCRIPTS). Each run is cut
into phases and takes the calls numbered 1 and 2 of each phase (`--capture-phases`,
`--capture-spread`), so a function called every frame has states from each part of the run.
A capture line holds the first bytes of the function and their CRC-32: a call is taken only
while that code is at the address (in level00, a level function's place holds the boot's code
until the level is loaded). A function a run never calls gets a NAME.none marker there. Level
states are about 16 MB each (the boot's about 5): list what is needed. `--script all` runs
every script. Levels other than 00 are not captured yet (each needs its script: the way there,
and its play) and their functions not checked.

Needs: OpenRAC's interpreter built (cmake -S tools/interpreter -B build/interpreter in
OpenRAC; $OPENRAC_ROOT, default ~/Projects/RAC/OpenRAC; level00 needs its --stick), the
compiler (docs/BUILDING.md; $RAC2_LINUX runs it, e.g. "docker exec rac2-gate"),
build/boot/placed.json from `tools/build.py boot` (and build/00_aranos_tutorial/placed.json from
`tools/build.py level 00` for level 00), and the disc image. Test-only: nothing here is linked or shipped.
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

# Pad bits: Select 1, L3 2, Start 8, Up 10, Right 20, Down 40, Left 80, L2 100, R2 200, L1 400,
# R1 800, Triangle 1000, Circle 2000, Cross 4000, Square 8000.
# Past the splash, the movies and the title to the main menu (New Game selected).
TO_MENU = ["300:4000:10", "500:8:10", "700:4000:10", "900:8:10"]


def play(start: int, end: int) -> tuple[list[str], list[str]]:
    """Presses and left-stick holds (openrac-boot's --press, --stick) that play a level from
    START to END: cycles of running forward (the stick up for 200 fields) with a jump, a swing
    of the wrench (Square) and a second jump, then turning right, left or back for 60 fields
    with another swing."""
    presses, sticks = [], []
    f, k = start, 0
    while f < end:
        sticks.append(f"{f}:80:00:200")
        presses += [f"{f + 60}:4000:8", f"{f + 120}:8000:8", f"{f + 170}:4000:8"]
        sticks.append(f"{f + 200}:{['ff:80', '00:80', '80:ff'][k % 3]}:60")
        presses.append(f"{f + 230}:8000:8")
        f, k = f + 300, k + 1
    return ([x for x in presses if int(x.split(":")[0]) < end],
            [x for x in sticks if int(x.split(":")[0]) < end])


L00_PLAY = play(2600, 7000)
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
    # New Game into level 00 (Aranos, the tutorial), loaded by about frame 1600 and run from
    # about 1700: Cross every 150 fields through the intro, then played (play()) to 7000, with
    # the pause menu (Start, Down, Triangle back) at 3500, R1 held at 4400 and 5000, Triangle
    # (quick select) at 5300, the map (Select) at 5600, Circle, L1, R2 and L2 held from 5800,
    # and the pause menu's pages again from 6300. Phases: the level's start, play, the pause
    # menu and weapons, the map and the rest. Its states are of level 00's program: a function
    # with a place there is taken at that place (the CRC guard keeps the boot's code at the
    # address, before the load, out), a resident boot function at its boot address.
    "level00": {"level": 0, "frames": 7000, "phases": [1500, 2600, 3500, 5500],
                "presses": TO_MENU + ["950:4000:10", "1000:4000:10"]
                + [f"{f}:4000:10" for f in range(1150, 2600, 150)] + L00_PLAY[0]
                + ["3500:8:8", "3600:40:8", "3700:1000:8", "3800:1000:8", "4400:800:60", "5000:800:60",
                   "5300:1000:8", "5360:1000:8", "5600:1:8", "5700:1:8", "5800:2000:30", "5900:400:60",
                   "6000:200:60", "6100:100:60", "6300:8:8", "6350:40:8", "6400:4000:8", "6500:1000:8",
                   "6550:40:8", "6600:40:8", "6650:4000:8", "6750:1000:8", "6800:1000:8"],
                "sticks": L00_PLAY[1]},
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


@lru_cache(maxsize=None)
def catalogue() -> dict[str, dict[int, int]]:
    """Catalogued level function name -> {level: address} (config/levels/functions.tsv; one
    place per level at most), and its size under the key -1."""
    out: dict[str, dict[int, int]] = {}
    for name, _, size, _, places in levels.read_catalogue():
        out[name] = {**dict(places), -1: size}
    return out


class Program:
    """The program a function is checked in: the boot (LEVEL None), or level LEVEL's, which
    replaces the boot's memory from levels.LEVEL_BASE (0x1A7C80; its .lit, data, bss and text)
    and keeps the boot's below it resident (the boot's functions and data there are live)."""

    def __init__(self, level: int | None = None):
        self.level = level
        self.key = "boot" if level is None else levels.level_dir(level)
        self.label = "boot" if level is None else f"level {level:02d}"

    def __eq__(self, other) -> bool:
        return isinstance(other, Program) and other.level == self.level

    def __hash__(self) -> int:
        return hash(self.level)

    def functions(self) -> dict[str, tuple[int, int]]:
        """Function name -> (address, size) as this program has them: a level's places in it
        (config/levels/functions.tsv), and the boot's resident functions (below LEVEL_BASE)."""
        if self.level is None:
            return boot_functions()
        return level_functions(self.level)

    def own(self, name: str) -> bool:
        """NAME is in this program's own code (the boot's, or a place in the level's program)."""
        if self.level is None:
            return name in boot_functions()
        return self.level in catalogue().get(name, {})

    def retail(self, address: int, size: int) -> bytes:
        if self.level is None or address < levels.LEVEL_BASE:
            return retail_bytes(address, size)
        return self.placement().retail(address, size)

    def placement(self):
        return program_placement(self.level)

    def placed(self) -> dict:
        return program_placed(self.key)

    def expected(self, n: str) -> int | None:
        """The address a name states, where this program has it there."""
        if self.level is None:
            return build.address_in_name(n)
        return self.placement().expected(n)

    def lit_sections(self) -> list[tuple[int, int]]:
        """(address, size) of the read-only literal pools in $gp's window: the boot's core.lit and
        .lit; a level's own lit, and what of the boot's lies below LEVEL_BASE."""
        boot = [(s["address"], s["size"]) for s in program_placement(None).image["sections"]
                if s["name"] in ("core.lit", ".lit")]
        if self.level is None:
            return boot
        mine = [(s["address"], s["size"]) for s in self.placement().image["sections"]
                if s["name"] in ("lit", ".lit")]
        return mine + [(a, min(n, levels.LEVEL_BASE - a)) for a, n in boot if a < levels.LEVEL_BASE]


BOOT_PROGRAM = Program()


@lru_cache(maxsize=None)
def level_functions(level: int) -> dict[str, tuple[int, int]]:
    out = {n: (a, s) for n, (a, s) in boot_functions().items() if a < levels.LEVEL_BASE}
    for name, places in catalogue().items():
        if level in places:
            out[name] = (places[level], places[-1])
    return out


@lru_cache(maxsize=None)
def program_placement(level: int | None):
    if level is None:
        return build.Placement("boot", elf.read(levels.BOOT))
    return build.Placement(levels.level_dir(level), elf.read(build.level_reference(level)))


@lru_cache(maxsize=None)
def copy_map(level: int, kind: str = "data") -> dict[int, int]:
    """Boot address (at or above LEVEL_BASE) -> where level LEVEL's program has it, read from the
    boot functions the level holds a copy of (catalogue rows of kind boot): the copy is the same
    code, so its references (retail_references), taken in order, pair one for one with the
    boot's. KIND "data" maps the addresses its loads, stores and address constants form, "call"
    its jump targets (a boot function the level has a variant of under another name). An address
    two copies place differently is left out."""
    prog = Program(level)
    seen: dict[int, set[int]] = {}
    for name, places in catalogue().items():
        if level not in places or name not in boot_functions():
            continue
        a, size = boot_functions()[name]
        if a < levels.LEVEL_BASE:
            continue
        for (k, b), l in copy_pairs(name, level):
            if k == kind:
                seen.setdefault(b, set()).add(l)
    return {b: next(iter(v)) for b, v in seen.items() if len(v) == 1}


@lru_cache(maxsize=None)
def copy_pairs(name: str, level: int) -> list[tuple[tuple[str, int], int]]:
    """((kind, boot address), level address) for each reference of boot function NAME's code
    that its copy in level LEVEL makes to another address at or above LEVEL_BASE: the two are
    the same code, so their references (retail_references) pair in order. Empty when NAME has no
    copy there or the two do not pair."""
    places = catalogue().get(name, {})
    if level not in places or name not in boot_functions():
        return []
    a, size = boot_functions()[name]
    if a < levels.LEVEL_BASE:
        return []
    n = min(size, places[-1])
    mine = retail_references(retail_bytes(a, n), a)
    theirs = retail_references(Program(level).retail(places[level], n), places[level])
    if len(mine) != len(theirs) or any(x[0] != y[0] for x, y in zip(mine, theirs)):
        return []
    return [((k, b), l) for (k, b), (_, l) in zip(mine, theirs) if b >= levels.LEVEL_BASE and b != l]


def level_address(level: int, address: int) -> int | None:
    """Where level LEVEL has the boot's data at ADDRESS (at or above LEVEL_BASE): copy_map's
    value, or (an address the copies reach only with an offset, inside a structure) the one
    distance every pair within 0x80 of it agrees on, when there are pairs on both sides of it
    (small variables are not always in the boot's order in a level)."""
    m = copy_map(level)
    if address in m:
        return m[address]
    near = {b: l - b for b, l in m.items() if abs(b - address) <= 0x80}
    if not any(b < address for b in near) or not any(b > address for b in near):
        return None
    deltas = set(near.values())
    return address + next(iter(deltas)) if len(deltas) == 1 else None


@lru_cache(maxsize=None)
def program_placed(key: str) -> dict:
    if key == "boot":
        return placed()
    p = ROOT / "build" / key / "placed.json"
    return json.loads(p.read_text()) if p.is_file() else {"functions": {}, "values": {}}


STUB = r'^(?:INCLUDE_ASM|ASM_FUNC)\("[^"]*",\s*{name}\);[ \t]*$'
DEFINITION = re.compile(r"^(?:[A-Za-z_][^;=#]*?\b)?([A-Za-z_]\w*)\s*\(")


@lru_cache(maxsize=None)
def sources() -> dict[str, tuple[Path, str]]:
    """Boot or catalogued level function name -> (its unit in src/, "c" or "asm")."""
    names = set(boot_functions()) | set(catalogue())
    out: dict[str, tuple[Path, str]] = {}
    dirs = [ROOT / "src" / d for d in ("core", "game", "levels/shared")]
    dirs += sorted(d for d in (ROOT / "src/levels").iterdir() if d.is_dir() and d.name[:2].isdigit())
    for d in dirs:
        for path in sorted(d.rglob("*.c")):
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


def derived_values(obj: dict, name: str, prog: Program = BOOT_PROGRAM) -> dict[str, int] | None:
    """The symbol values (and "§section" placements) NAME's section in OBJ needs to read as the
    retail bytes at NAME's address in PROG (tools/build.py's derivation), or None when it does not."""
    sym = next((s for s in obj["symbols"] if s["name"] == name and s["type"] == STT_FUNC and 0 < s["section"] < 0xFF00), None)
    if sym is None or not prog.own(name):
        return None
    address = prog.functions()[name][0]
    values, why = prog.placement().derive(obj, sym["section"], address - sym["value"])
    return None if why else values


def placement():
    return program_placement(None)


def unit_values(unit: Path, name: str, prog: Program = BOOT_PROGRAM) -> tuple[dict[str, int], dict[str, int]]:
    """From the unit's matched build (build/obj/): what NAME's own C needs (empty when NAME is
    not matched C), and the agreed values the unit's other functions placed in PROG need."""
    try:
        obj = elf.read_object(build.compile_c(unit))
    except SystemExit:
        return {}, {}
    own = derived_values(obj, name, prog) or {}
    others: dict[str, set[int]] = {}
    done = set(prog.placed().get("functions", {}))
    for s in obj["symbols"]:
        if s["type"] == STT_FUNC and s["name"] != name and s["name"] in done and 0 < s["section"] < 0xFF00:
            for k, v in (derived_values(obj, s["name"], prog) or {}).items():
                others.setdefault(k, set()).add(v)
    return own, {k: next(iter(v)) for k, v in others.items() if len(v) == 1}


def sda_alias(name: str) -> str | None:
    """The variable an sda alias names: D_XXXXXXXX_sda (a second, $gp-relative declaration of
    D_XXXXXXXX), or SDATA()'s assembler name D_XXXXXXXX__gp; None for another name."""
    m = re.fullmatch(r"(\w+?)(?:_sda|__gp)", name)
    return m.group(1) if m else None


# Opcodes whose 16-bit immediate is an address's low half on a base register: addiu, the
# loads and stores (lq/sq, ldl/ldr, lwc1/swc1, ld/sd and the rest).
ADDRESS_OPS = {0x09, 0x1A, 0x1B, 0x1E, 0x1F, *range(0x20, 0x30), 0x31, 0x35, 0x37, 0x39, 0x3D, 0x3F}
LOADS = {0x1A, 0x1B, 0x1E, *range(0x20, 0x28), 0x37}


def retail_references(ref: bytes, address: int) -> list[tuple[str, int]]:
    """The addresses retail's code at ADDRESS forms, in order: ("call", target) for a jal or j,
    ("data", address) for a %lo-style use of a lui's register or a $gp-based access."""
    sext = build.sext
    hi: dict[int, int] = {}
    out = []
    for at in range(0, len(ref) - 3, 4):
        w = struct.unpack_from("<I", ref, at)[0]
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        if op in (2, 3):
            out.append(("call", ((address + at + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)))
            if op == 3:
                hi.pop(31, None)
            continue
        if op == 0x0F:
            hi[rt] = (w & 0xFFFF) << 16
            continue
        if op in ADDRESS_OPS and (rs in hi or rs == 28):
            out.append(("data", ((GP if rs == 28 else hi[rs]) + sext(w & 0xFFFF)) & 0xFFFFFFFF))
        # What the instruction writes no longer holds a lui's value.
        if op in (0, 0x1C):
            hi.pop(rd, None)
        elif op in LOADS or 0x08 <= op <= 0x0E or (op == 0x11 and rs in (0, 2)):
            hi.pop(rt, None)
    return out


def signature(w: int) -> tuple[int, int]:
    """An instruction's kind, without its registers and immediate: the opcode, and the function
    field of SPECIAL/MMI ones, the rt field of REGIMM's."""
    op = w >> 26
    return op, (w & 0x3F if op in (0, 0x1C) else (w >> 16) & 0x1F if op == 1 else 0)


def aligned_by_position(obj: dict, index: int, start: int, end: int, address: int, ref: bytes) -> dict[str, int]:
    """aligned_values' first pass: the candidate's instructions aligned to retail's by kind (the
    longest common runs); a relocated one whose retail counterpart is the same instruction (a
    jump, a lui with the %lo instruction based on the register it loaded, a $gp-based access)
    gives its symbol a value, kept when every such use agrees."""
    import difflib
    data = bytes(obj["sections"][index]["data"])
    word = lambda blob, at: struct.unpack_from("<I", blob, at)[0]
    mine = [word(data, a) for a in range(start, end - 3, 4)]
    theirs = [word(ref, a) for a in range(0, len(ref) - 3, 4)]
    m = difflib.SequenceMatcher(None, [signature(w) for w in mine], [signature(w) for w in theirs], autojunk=False)
    at_retail: dict[int, int] = {}
    for a, b, n in m.get_matching_blocks():
        for k in range(n):
            at_retail[start + 4 * (a + k)] = 4 * (b + k)
    rel = obj["relocations"].get(index, [])
    sext = build.sext
    seen: dict[str, set[int]] = {}
    for k, (at, kind, s) in enumerate(rel):
        sy = obj["symbols"][s]
        n = sy["name"]
        if not n or sy["type"] == STT_SECTION or at not in at_retail:
            continue
        w, r = word(data, at), word(ref, at_retail[at])
        if kind == elf.R_MIPS_26:
            v = ((address & 0xF0000000) | ((r & 0x3FFFFFF) << 2)) - ((w & 0x3FFFFFF) << 2)
        elif kind == elf.R_MIPS_HI16:
            lo = next((o for o, t, ss in rel[k + 1:] if t == elf.R_MIPS_LO16 and ss == s), None)
            if lo is None or lo not in at_retail or r >> 26 != 0x0F:
                continue
            rl = word(ref, at_retail[lo])
            if (rl >> 21) & 31 != (r >> 16) & 31:
                continue
            v = (((r & 0xFFFF) << 16) + sext(rl & 0xFFFF)
                 - (((w & 0xFFFF) << 16) + sext(word(data, lo) & 0xFFFF)))
        elif kind == elf.R_MIPS_GPREL16:
            if (r >> 21) & 31 != 28:
                continue
            v = GP + sext(r & 0xFFFF) - sext(w & 0xFFFF)
        else:
            continue
        seen.setdefault(n, set()).add(v & 0xFFFFFFFF)
    return {n: next(iter(v)) for n, v in seen.items() if len(v) == 1}


def aligned_values(obj: dict, name: str, known=lambda n: None, prog: Program = BOOT_PROGRAM) -> dict[str, int]:
    """Values of the symbols NAME's candidate section refers to that nothing else places (a near
    miss's `ref_LNN_XXXXXXXX_kk`, the kk-th external of a function: a value of each program, which
    no matched function of the boot may give), read from retail's bytes as tools/build.py reads
    them under the relocations, for a candidate that is not byte-identical: its references, in
    order, are aligned to the addresses retail's code forms (retail_references), the symbols KNOWN
    or the first pass (aligned_by_position) gives a value anchoring the alignment, and a symbol
    takes the value every use aligned to retail agrees on."""
    sym = next((s for s in obj["symbols"] if s["name"] == name and s["type"] == STT_FUNC and 0 < s["section"] < 0xFF00), None)
    if sym is None or name not in prog.functions():
        return {}
    address, size = prog.functions()[name]
    index = sym["section"]
    data = bytes(obj["sections"][index]["data"])
    rel = obj["relocations"].get(index, [])
    word = lambda at: struct.unpack_from("<I", data, at)[0]
    sext = build.sext
    # The candidate's references in address order: (kind, symbol name or None, addend).
    pairs = {}
    for k, (at, kind, s) in enumerate(rel):
        if kind == elf.R_MIPS_HI16:
            lo = next((o for o, t, ss in rel[k + 1:] if t == elf.R_MIPS_LO16 and ss == s), None)
            if lo is not None:
                pairs.setdefault(lo, ((word(at) & 0xFFFF) << 16) + sext(word(lo) & 0xFFFF))
    mine = []
    for at, kind, s in sorted(rel):
        sy = obj["symbols"][s]
        n = sy["name"] if sy["type"] != STT_SECTION else None
        if kind == elf.R_MIPS_26:
            mine.append(("call", n, (word(at) & 0x3FFFFFF) << 2))
        elif kind == elf.R_MIPS_LO16:
            mine.append(("data", n, pairs.get(at, sext(word(at) & 0xFFFF))))
        elif kind == elf.R_MIPS_GPREL16 and n and sy["section"] == 0:
            mine.append(("data", n, sext(word(at) & 0xFFFF)))
        elif kind in (elf.R_MIPS_GPREL16, 8):
            mine.append(("data", None, 0))
    ref = prog.retail(address, size)
    end = min(len(data), sym["value"] + sym["size"]) if sym.get("size") else len(data)
    first = aligned_by_position(obj, index, sym["value"], end, address, ref)
    theirs = retail_references(ref, address)
    value = {}
    for kind, n, addend in mine:
        if n and n not in value:
            v = known(n)
            v = first.get(n) if v is None else v
            value[n] = None if v is None else v & 0xFFFFFFFF

    def score(a, b) -> int:
        (ka, n, addend), (kb, r) = a, b
        if ka != kb:
            return -1
        if n is None or value.get(n) is None:
            return 1                       # free: a section's or an unknown symbol's use
        return 3 if (value[n] + addend) & 0xFFFFFFFF == r else -1

    # The best alignment (most agreeing anchors), by dynamic programming.
    M, N = len(mine), len(theirs)
    best = [[0] * (N + 1) for _ in range(M + 1)]
    for i in range(M - 1, -1, -1):
        for j in range(N - 1, -1, -1):
            s = score(mine[i], theirs[j])
            best[i][j] = max(best[i + 1][j], best[i][j + 1], best[i + 1][j + 1] + s if s > 0 else 0)
    seen: dict[str, set[int]] = {}
    i = j = 0
    while i < M and j < N:
        s = score(mine[i], theirs[j])
        if s > 0 and best[i][j] == best[i + 1][j + 1] + s:
            kind, n, addend = mine[i]
            if n and value.get(n) is None:
                seen.setdefault(n, set()).add((theirs[j][1] - addend) & 0xFFFFFFFF)
            i, j = i + 1, j + 1
        elif best[i][j] == best[i + 1][j]:
            i += 1
        else:
            j += 1
    out = {n: v for n, v in first.items() if known(n) is None}
    out.update({n: next(iter(v)) for n, v in seen.items() if len(v) == 1})
    return out


# --- Placing ---------------------------------------------------------------------------------

def gp_literal(data: bytes, prog: Program = BOOT_PROGRAM) -> int | None:
    """An address in $gp's window where PROG's read-only literal pools (the boot's core.lit and
    .lit, a level's lit) hold DATA, aligned to its size."""
    for address, size in prog.lit_sections():
        lo, hi = max(address, GP - 0x8000), min(address + size, GP + 0x8000)
        blob = prog.retail(address, size)
        step = min(len(data), 8) or 4
        for a in range(lo + (-lo) % step, hi - len(data) + 1, step):
            if blob[a - address:a - address + len(data)] == data:
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
        # The gp the assembler assumed (.reginfo's last word): a $gp-relative reference to a local
        # symbol holds its offset less it (S + A + GP0 - GP, as the linker reads it).
        reginfo = next((s for s in obj["sections"] if s["name"] == ".reginfo" and len(s["data"]) >= 24), None)
        self.gp0 = struct.unpack_from("<i", bytes(reginfo["data"]), 20)[0] if reginfo else 0
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

    def target(self, sym: dict, addend: int) -> int:
        """Where a reference to SYM plus ADDEND goes. Into a writable section of the candidate, a
        variable it defines there with a retail address (a D_ name, an sda one among them) is
        at that address, whatever the section's own placement: the reference may name the
        section (a static, or an initialised small-data global) and not the variable."""
        index = sym["section"]
        if sym["type"] == STT_SECTION and 0 < index < 0xFF00:
            sec = self.obj["sections"][index]
            if sec.get("flags", 0) & SHF_WRITE or sec["type"] == elf.SHT_NOBITS:
                for s in self.obj["symbols"]:
                    if (s["section"] == index and s["type"] != STT_SECTION and s["name"]
                            and s["value"] <= addend < s["value"] + max(s.get("size", 0), 1)):
                        v = self.named(s["name"])
                        if v is not None:
                            return v + addend - s["value"]
        return self.value(sym) + addend

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
        if n.startswith("ref_"):
            raise Link(f"LINK {n} has no retail address: no matched function gives it, and its uses do not "
                       "line up with retail's (name it D_XXXXXXXX)")
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
        # Each %hi pairs with the next %lo of its symbol in the object's order, as the linker
        # does; that %lo's full addend (for a reference into a section) is the pair's.
        ahl_of_lo: dict[int, int] = {}
        for k, (at, kind, s) in enumerate(rel):
            if kind == elf.R_MIPS_HI16:
                lo = next((o for o, t, ss in rel[k + 1:] if t == elf.R_MIPS_LO16 and ss == s), None)
                if lo is not None:
                    ahl_of_lo.setdefault(lo, ((word(at) & 0xFFFF) << 16) + sext(word(lo) & 0xFFFF))
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
            if kind == elf.R_MIPS_32:
                put(at, self.target(sym, w))
            elif kind == elf.R_MIPS_26:
                target = self.target(sym, (w & 0x3FFFFFF) << 2)
                if (target ^ (self.base + off + at)) & 0xF0000000:
                    raise Link("LINK a jump out of its 256 MB region")
                put(at, (w & 0xFC000000) | ((target >> 2) & 0x3FFFFFF))
            elif kind == elf.R_MIPS_HI16:
                # Paired in the object's order with the next %lo of the same symbol, as the linker does.
                lo = next((o for o, t, ss in rel[k + 1:] if t == elf.R_MIPS_LO16 and ss == s), None)
                if lo is None:
                    raise Link(f"LINK a %hi at +{at:#x} without its %lo")
                ahl = ((w & 0xFFFF) << 16) + sext(word(lo) & 0xFFFF)
                put(at, (w & 0xFFFF0000) | (((self.target(sym, ahl) + 0x8000) >> 16) & 0xFFFF))
            elif kind == elf.R_MIPS_LO16:
                lo = sext(w & 0xFFFF)
                ahl = ahl_of_lo.get(at, lo)
                put(at, (w & 0xFFFF0000) | ((self.target(sym, ahl) - ahl + lo) & 0xFFFF))
            else:
                raise Link(f"LINK relocation type {kind} not handled")

    def gp_target(self, sym: dict, addend: int, ins: int) -> int:
        """Where a $gp-relative reference goes. A read-only section of the candidate (a literal)
        is not reachable from where it is copied: the same bytes in retail's window are used."""
        index = sym["section"]
        sec = self.obj["sections"][index] if 0 < index < 0xFF00 else None
        if sym["type"] == STT_SECTION or (sym.get("bind", 1) == 0 and sec is not None):
            addend += self.gp0
        if (sym["type"] == STT_SECTION and sec is not None and not sec["name"].startswith(".text")
                and not sec.get("flags", 0) & SHF_WRITE and sec["type"] != elf.SHT_NOBITS):
            width = WIDTH.get(ins >> 26, 4)
            data = bytes(sec["data"][addend:addend + width])
            a = self.literal(data, sec["name"], addend)
            if a is None:
                raise Link(f"LINK the constant {data.hex()} in {sec['name']} (read $gp-relative) is nowhere in retail's $gp window")
            return a
        return self.target(sym, addend)

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


class Resolver:
    """Retail values of the symbols NAME's candidate (object OBJ) refers to, in program PROG, for
    Placer: OWN and OTHERS are unit_values'. A named symbol, in order: what NAME's own matched C
    needs; in a level, for a boot function's own copy there, what each boot address its code
    refers to is in the copy (copy_pairs: the level's own variant of a callback, say, where the
    catalogue also places a copy of the boot's); a function of PROG (its place there; in a level,
    a resident boot function's boot address); the values PROG's build derived (build/<program>/placed.json); in a level, the boot
    build's values that hold there (below LEVEL_BASE, or a boot function's address above it, which
    is that function's copy in the level); the unit's other placed functions'; the address the
    name states where PROG has it there (build.Placement.expected: in a level, D_LNN_ of that
    level, and boot addresses below LEVEL_BASE only); an sda alias's variable; in a level, a boot
    address above LEVEL_BASE where the level's copies of boot code have it (copy_map: data, or
    for a boot function the level has no copy of, the function its copies call there); else
    retail's bytes by alignment (aligned_values)."""

    def __init__(self, prog: Program, name: str, obj: dict, own: dict[str, int], others: dict[str, int]):
        self.prog, self.name, self.obj, self.own, self.others = prog, name, obj, own, others
        self.table = prog.functions()
        self.derived = {k: int(v, 16) for k, v in prog.placed().get("values", {}).items()}
        self.boot_derived: dict[str, int] = {}
        self.by_address = by_address = {a: n for n, (a, _) in boot_functions().items()}
        # A boot function's own copy in the level: what each boot address it refers to is in
        # the copy (the level's own variant of a callback, say, where the catalogue also places
        # a copy of the boot's), the first word on a name's value there.
        self.local: dict[int, int] = {}
        if prog.level is not None:
            seen: dict[int, set[int]] = {}
            for (_, b), l in copy_pairs(name, prog.level):
                seen.setdefault(b, set()).add(l)
            self.local = {b: next(iter(v)) for b, v in seen.items() if len(v) == 1}
        if prog.level is not None:
            for k, v in placed().get("values", {}).items():
                v = int(v, 16)
                if v < levels.LEVEL_BASE:
                    self.boot_derived[k] = v
                elif by_address.get(v) in self.table and self.table[by_address[v]][0] != v:
                    self.boot_derived[k] = self.table[by_address[v]][0]
                elif v not in by_address and level_address(prog.level, v) is not None:
                    self.boot_derived[k] = level_address(prog.level, v)
                elif v in by_address and v in copy_map(prog.level, "call"):
                    self.boot_derived[k] = copy_map(prog.level, "call")[v]
        self.aligned: dict[str, int] | None = None
        self.from_bytes: list[str] = []

    def boot_value(self, n: str) -> int | None:
        """NAME's value in the boot: its function's address, the boot build's value, or the address
        its name states."""
        if n in boot_functions():
            return boot_functions()[n][0]
        v = placed().get("values", {}).get(n)
        return int(v, 16) if v is not None else build.address_in_name(n)

    def named(self, n: str) -> int | None:
        if n in self.own:
            return self.own[n] & 0xFFFFFFFF
        if self.local:
            b = self.boot_value(n)
            if b is not None and b in self.local:
                return self.local[b]
        if n in self.table:
            return self.table[n][0]
        if n in self.derived:
            return self.derived[n]
        if n in self.boot_derived:
            return self.boot_derived[n]
        if n in self.others:
            return self.others[n] & 0xFFFFFFFF
        v = self.prog.expected(n)
        if v is not None:
            return v
        if sda_alias(n):
            v = self.named(sda_alias(n))
            if v is not None:
                return v
        # A boot address the level replaces: where the level's copies of boot code have it.
        a = build.address_in_name(n)
        if self.prog.level is not None and a is not None and a >= levels.LEVEL_BASE and not n.startswith(("func_L", "D_L", "f_L")):
            if a in self.by_address:
                # A boot function: its place in the level (under the boot table's name for the
                # address, which may differ from the name's), else what the level's copies call
                # in its place.
                f = self.by_address[a]
                v = self.table[f][0] if f in self.table else copy_map(self.prog.level, "call").get(a)
            else:
                v = level_address(self.prog.level, a)
            if v is not None:
                return v
        # Else (a near miss's ref_ name): the value retail's own bytes give it.
        if self.aligned is None:
            self.aligned = {}          # (no recursion through named while aligning)
            self.aligned = aligned_values(self.obj, self.name, self.named, self.prog)
        if n in self.aligned:
            if n not in self.from_bytes:
                self.from_bytes.append(n)
            return self.aligned[n]
        return None

    def function(self, n: str) -> int | None:
        return self.named(n)

    def writable(self, sec: str) -> int | None:
        for d in (self.own, self.others):
            if "§" + sec in d:
                return d["§" + sec] & 0xFFFFFFFF
        return None

    def literal(self, data: bytes, sec: str, offset: int) -> int | None:
        for d in (self.own, self.others):
            b = d.get("§" + sec)
            if b is not None and GP - 0x8000 <= b + offset < GP + 0x8000 and self.prog.retail(b + offset, len(data)) == data:
                return b + offset
        return gp_literal(data, self.prog)


# --- Building a candidate ----------------------------------------------------------------------

def build_candidate(name: str, candidate: Path | None, out: Path, includes: list[Path] | None = None,
                    prog: Program = BOOT_PROGRAM, base: int = BASE) -> dict:
    """Compile and place NAME (src/'s C, or CANDIDATE in its unit) for its place in PROG, writing
    OUT/code.bin and OUT/placed.json; returns the placed.json dict. Raises Link."""
    src = sources().get(name)
    if src is None:
        raise Link(f"LINK {name} is not a boot or catalogued level function in src/ "
                   "(config/boot/functions.tsv, config/levels/functions.tsv)")
    if not prog.own(name):
        raise Link(f"LINK {name} has no place in the {prog.label} program")
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
    own, others = unit_values(unit, name, prog)
    r = Resolver(prog, name, obj, own, others)
    table = r.table
    p = Placer(obj, name, r.named, r.function, r.writable, r.literal, base,
               LIMIT if base == BASE else base + 0x100000)
    p.relocate()
    if r.from_bytes:
        p.notes.append("read from retail's bytes by alignment: " + ", ".join(
            f"{n}={r.aligned[n]:#010x}" for n in r.from_bytes))
    segs = p.segments()
    files = []
    for i, (a, data) in enumerate(segs):
        f = out / f"code{i}.bin"
        f.write_bytes(data)
        files.append([f.name, a])
    info = {"entry": p.entry, "segments": files, "unit": str(unit.relative_to(ROOT)), "mode": mode,
            "flags": build.flags_for(unit), "returns": returns(name, cand_text), "notes": p.notes,
            "own_values": bool(own), "program": prog.key, "address": table[name][0]}
    (out / "placed.json").write_text(json.dumps(info, indent=1))
    return info


def build_retail(name: str, candidate: Path | None, out: Path, prog: Program = BOOT_PROGRAM) -> dict:
    """The harness's self-test candidate: retail's own bytes of NAME in PROG, moved to BASE (its
    branches are relative; its jumps and addresses still go to retail's, so it does what retail
    does). A DIFFERS on it is the harness's or the states', never C's. The return type is read
    from CANDIDATE, else src/'s C (void when NAME is assembly there)."""
    if name not in prog.functions():
        raise Link(f"LINK {name} has no place in the {prog.label} program")
    a, size = prog.functions()[name]
    out.mkdir(parents=True, exist_ok=True)
    (out / "code0.bin").write_bytes(prog.retail(a, size))
    src = sources().get(name)
    text = candidate.read_text(errors="replace") if candidate else src[0].read_text(errors="replace") if src else ""
    info = {"entry": BASE, "segments": [["code0.bin", BASE]], "unit": None, "mode": "retail's own bytes",
            "flags": None, "returns": returns(name, text), "notes": [], "own_values": False,
            "program": prog.key, "address": a}
    (out / "placed.json").write_text(json.dumps(info, indent=1))
    return info


# --- Capturing ----------------------------------------------------------------------------------

def states_of(name: str, root: Path | None = None) -> list[Path]:
    root = root or states_root()
    return sorted(root.glob(f"*/{name}.*.snap"))


def script_program(script: str) -> Program:
    """The program a capture run's level part runs: a script's "level", else the boot."""
    s = SCRIPTS.get(script, {})
    return Program(s["level"]) if "level" in s else BOOT_PROGRAM


def state_program(name: str, state: Path) -> Program:
    """The program NAME's code in STATE belongs to: the level of the run that took it (its
    directory, a script's name) when NAME has a place in that level's program, else the boot
    (a boot function, resident below LEVEL_BASE or called before the level loaded)."""
    prog = script_program(state.parent.name)
    return prog if prog.level is not None and prog.own(name) else BOOT_PROGRAM


def capture_line(name: str, prog: Program = BOOT_PROGRAM, wanted: int = STATES_PER_PHASE) -> str | None:
    """openrac-boot's capture list line for a function of PROG: address, bytes compared, their
    CRC-32 (another program's code at the address then is not taken: before a level is loaded,
    or a level's over the boot's), name, states per phase. In a level's run a function with a
    place in the level is taken there, a resident boot function at its boot address."""
    if name not in prog.functions():
        return None
    a, size = prog.functions()[name]
    k = max(4, min(size, 256))
    return f"{a:08x} {k} {zlib.crc32(prog.retail(a, k)):08x} {name} {wanted}"


def capture(names: list[str], script: str, frames: int | None = None, force: bool = False,
            root: Path | None = None, wanted: dict[str, int] | None = None) -> tuple[int, int]:
    """One headless run of SCRIPT taking states of NAMES (those it has not run for yet), WANTED
    states per phase of a name that has an entry there (else the script's). Returns (functions
    called, functions asked)."""
    s = SCRIPTS[script]
    out = (root or states_root()) / script
    out.mkdir(parents=True, exist_ok=True)
    todo = [n for n in dict.fromkeys(names) if force or not (list(out.glob(f"{n}.*.snap")) or (out / f"{n}.none").exists())]
    prog = script_program(script)
    per = s.get("per_phase", STATES_PER_PHASE)
    lines = [l for l in (capture_line(n, prog, (wanted or {}).get(n, per)) for n in todo) if l]
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
    for p in s.get("sticks", []):
        cmd += ["--stick", p]
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
          includes: list[Path] | None = None, retail: bool = False) -> int:
    """NAME's candidate against each of its states, built once for each program the states are
    of (state_program): the boot's runs place it at its boot address's terms, a level's run at its
    place in the level. The verdict: DIFFERS when any program's states differ; else did not
    build when any program's build failed; else SAME when any compared; else every state skipped."""
    states = states_of(name)
    if not states:
        marked = list(states_root().glob(f"*/{name}.none"))
        print(f"{name}: NOT CALLED in the capture runs ({', '.join(sorted(p.parent.name for p in marked)) or 'none run yet'}); "
              "cannot check by behaviour")
        return 3
    work = work or WORK / "work" / name
    groups: dict[Program, list[Path]] = {}
    for s in states:
        groups.setdefault(state_program(name, s), []).append(s)
    order = sorted(groups, key=lambda g: -1 if g.level is None else g.level)
    codes, compared = [], 0
    for k, prog in enumerate(order):
        where = work if k == 0 else work / prog.key
        label = "" if len(order) == 1 and prog.level is None else f" ({prog.label})"
        try:
            info = (build_retail(name, candidate, where, prog) if retail
                    else build_candidate(name, candidate, where, includes, prog))
        except Link as e:
            print(str(e) + label)
            codes.append(2)
            continue
        # The capture run's hooks and disc: a hooked function's service answers in both runs.
        cmd = [str(FCHECK), "--hooks", str(HOOKS), "--disc", str(DISC), "--limit", str(RETAIL_LIMIT),
               "--entry", f"{info['entry']:x}", "--returns", info["returns"]]
        if ulps:
            cmd += ["--ulps", str(ulps)]
        for f, a in info["segments"]:
            cmd += ["--code", f"{where / f}@{a:x}"]
        cmd += [str(s) for s in groups[prog]]
        r = subprocess.run(cmd, capture_output=True, text=True)
        text = r.stdout.replace(str(states_root()) + "/", "")
        if info["notes"] or info["mode"] != "src":
            print(f"{name}: compiled {info['mode']}{label}" + "".join("; " + n for n in info["notes"]))
        print(text.strip() or r.stderr.strip())
        if r.returncode == 0:
            m = re.search(r"compared (\d+) of", r.stdout)
            compared += int(m.group(1)) if m else 0
        codes.append(r.returncode)
    if 1 in codes or any(c not in (0, 2, 4) for c in codes):
        return next(c for c in codes if c not in (0, 2, 4))
    if 2 in codes:
        return 2
    if 0 in codes:
        print(f"{name}: SAME on {compared} real calls")
        return 0
    print(f"{name}: NOTHING COMPARED (every state skipped)")
    return 4


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
    p.add_argument("--retail", action="store_true",
                   help="the harness's self-test: retail's own bytes as the candidate (CANDIDATE only gives the return type)")
    p = sub.add_parser("build")
    p.add_argument("name")
    p.add_argument("candidate", nargs="?", type=Path)
    p.add_argument("--out", type=Path, required=True)
    p.add_argument("--level", type=int, help="place NAME at its place in level N's program (default: the boot's)")
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
                     [d.resolve() for d in a.include], a.retail)
    if a.cmd == "build":
        try:
            prog = BOOT_PROGRAM if a.level is None else Program(a.level)
            print(json.dumps(build_candidate(a.name, a.candidate.resolve() if a.candidate else None, a.out.resolve(),
                                             prog=prog)))
        except Link as e:
            print(str(e))
            return 2
        return 0
    if a.cmd == "capture":
        rows = [l.split() for l in a.list.read_text().splitlines() if l.strip() and not l.startswith("#")]
        names = [r[0] for r in rows]
        wanted = {r[0]: int(r[1]) for r in rows if len(r) > 1 and r[1].isdigit()}
        for s in (SCRIPTS if a.script == "all" else [a.script]):
            got, asked = capture(names, s, a.frames, a.force, wanted=wanted)
            print(f"{s}: {got} of {asked} functions called")
        return 0
    if a.cmd == "source":
        if a.name not in sources():
            print(json.dumps({"name": a.name}))
            return 2
        unit, kind = sources()[a.name]
        span = find_definition(unit.read_text(errors="replace"), a.name) if kind == "c" else None
        levels_placed = sorted(int(k[:2]) for k in (p.parent.name for p in (ROOT / "build").glob("[0-9][0-9]_*/placed.json"))
                               if a.name in program_placed(k).get("functions", {}))
        print(json.dumps({"name": a.name, "unit": str(unit), "kind": kind, "span": span,
                          "placed": a.name in placed().get("functions", {}), "levels_placed": levels_placed}))
        return 0
    if a.cmd == "scripts":
        print(json.dumps(SCRIPTS, indent=1))
        return 0
    return 2


if __name__ == "__main__":
    sys.exit(main())
