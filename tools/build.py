#!/usr/bin/env python3
"""
Build the game's programs and compare them with the retail ones.

  python3 tools/build.py boot             # the boot executable
  python3 tools/build.py level 04         # one level's program
  python3 tools/build.py levels           # all 27
  python3 tools/build.py all              # the boot and all 27
  python3 tools/build.py all --jobs 12    # that many programs at once (default: half the cores, at most 8)
  python3 tools/build.py all --strict     # release check: also reject any C falling back to assembly
  python3 tools/build.py all --version pal  # another release (pal, us2): build/<version>/, docs/build/versions.md

Each program is disassembled with splat into build/<program>/asm/, converted for SN
ProDG 2.0's assembler (tools/expand_asm.py) and assembled with it; the C in src/ is
compiled with the game's compiler (tools/compiler/) and every C function takes the
place of its assembly; then SN's linker links the program, and every loaded byte,
the segments and the entry point are compared with the retail program's. A program
that differs stops the build.

Inputs: baserom/ (tools/levels.py dump), toolchain/sn-prodg-2.0/ee/bin/{Ps2EeAs,ld}.exe
and build/compiler/tools/{cpp,cc1,as} (docs/build/building.md). The Windows tools run through
$RAC2_WINE (default `wine`; `{cwd}` is replaced by the directory they run in), the
32-bit Linux compiler through $RAC2_LINUX (default: directly).

One wineserver serves a whole Wine prefix and runs single-threaded, so `all` and `levels`
give each program running at once a prefix of its own, build/wine/<slot> (made once by
wineboot, then reused): a 32-job build runs 32 wineservers instead of queueing behind one.
A WINEPREFIX already set, or RAC2_ONE_PREFIX=1, keeps every program on that one prefix.
"""
import ast
import hashlib
import json
import os
import queue
import re
import shlex
import shutil
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf  # noqa: E402
import levels  # noqa: E402

BUILD = ROOT / "build"


def out_dir() -> Path:
    """build/ for v1.01, build/<version>/ for another release (C objects stay in build/obj/)."""
    return BUILD if levels.VERSION == "us" else BUILD / levels.VERSION
SN = ROOT / "toolchain/sn-prodg-2.0/ee/bin"
JOBS = os.cpu_count() or 4


def run(arguments: list[str], cwd: Path, log: Path) -> None:
    if arguments[0].lower().endswith(".exe"):
        arguments = shlex.split(os.environ.get("RAC2_WINE", "wine").replace("{cwd}", str(cwd))) + arguments
    with log.open("wb") as out:
        result = subprocess.run(arguments, cwd=cwd, stdout=out, stderr=subprocess.STDOUT, timeout=900)
    if result.returncode:
        sys.exit(f"{arguments[0]} failed; see {log}")


# --- splat and the linker script ------------------------------------------------------

def safe_name(name: str) -> str:
    return name.lstrip(".").replace(".", "_").replace("-", "_")


def splat_config(reference: Path, directory: Path, name: str) -> dict:
    """config/splat.yaml for REFERENCE: one segment per loaded section, the text as assembly
    and the rest as data. Returns the object names splat's linker script uses for each
    section, by file offset, and the ones the build gives them."""
    image = elf.read(reference)
    loads = [s for s in image["segments"] if s["type"] == elf.PT_LOAD]
    sections = sorted((s for s in image["sections"] if s["size"] and s["address"] and s["type"] != elf.SHT_NOBITS
                       and any(l["offset"] <= s["offset"] and s["offset"] + s["size"] <= l["offset"] + l["filesz"]
                               and s["address"] == l["address"] + s["offset"] - l["offset"] for l in loads)),
                      key=lambda s: s["offset"])
    (directory / "assets").mkdir(parents=True)
    shutil.copy2(reference, directory / "assets" / f"{name}.elf")
    (directory / "config").mkdir()
    options = {"platform": "ps2", "base_path": "..", "basename": name,
               "target_path": f"assets/{name}.elf", "asm_path": "asm", "src_path": "src",
               "build_path": "build", "create_asm_dependencies": True,
               "ld_script_path": "config/rac2.ld", "symbol_addrs_path": "config/symbol_addrs.txt",
               "undefined_funcs_auto_path": "config/undefined_funcs_auto.txt",
               "undefined_syms_auto_path": "config/undefined_syms_auto.txt",
               "find_file_boundaries": False, "disassemble_all": True}
    segments, renamed = [], {}
    for s in sections:
        code = s["name"] in (".text", "core.text")
        seg = f"{safe_name(s['name'])}_{s['offset']:X}"
        segment = {"name": seg, "type": "code" if code else "data", "start": s["offset"],
                   "vram": s["address"], "align": 16, "subsegments": [[s["offset"], "asm" if code else "data"]]}
        bss = [o for o in image["sections"] if o["type"] == elf.SHT_NOBITS and o["address"] == s["address"] + s["size"]]
        if bss:
            segment["bss_size"] = sum(o["size"] for o in bss)
        segments.append(segment)
        if code:
            renamed[f"build/asm/{s['offset']:X}.s.o"] = f"build/asm/{seg}.s.o"
        else:
            renamed[f"build/asm/data/{s['offset']:X}.data.s.o"] = f"build/asm/data/{seg}.data.s.o"
    for l in loads:
        end = l["offset"] + l["filesz"]
        if end < max(o["offset"] + o["filesz"] for o in loads) and not any(s["offset"] == end for s in sections):
            segments.append({"name": f"unloaded_gap_{end:X}", "type": "bin", "start": end})
    segments.sort(key=lambda s: s["start"])
    segments.append([max(l["offset"] + l["filesz"] for l in loads)])
    document = {"name": name, "sha1": hashlib.sha1(reference.read_bytes()).hexdigest(),
                "options": options, "segments": segments}
    (directory / "config/splat.yaml").write_text(json.dumps(document, indent=2) + "\n")
    (directory / "config/symbol_addrs.txt").write_text("")
    return renamed


def data_tails(reference: Path) -> dict[str, bytes]:
    """The last bytes of a load segment that ends off a word boundary, by section: splat's
    data files stop at the last whole word."""
    image = elf.read(reference)
    tails = {}
    for l in (s for s in image["segments"] if s["type"] == elf.PT_LOAD):
        end = l["offset"] + l["filesz"]
        if end % 4:
            s = next(s for s in image["sections"] if s["type"] != elf.SHT_NOBITS and s["offset"] + s["size"] == end)
            tails[f"{safe_name(s['name'])}_{s['offset']:X}"] = image["data"][end - end % 4:end]
    return tails


def adapt_linker(directory: Path, renamed: dict) -> None:
    """splat's linker script in the dialect of SN's 1990s GNU ld, one PT_LOAD per segment."""
    path = directory / "config/rac2.ld"
    text = path.read_text()
    text = re.sub(r"^\s*(unloaded_gap_\w+)_ROM_START = .*?\n\s*\1_VRAM_END = \.;\n", "\n", text,
                  flags=re.MULTILINE | re.DOTALL)
    text = re.sub(r"ALIGN\(\s*\.\s*,\s*(\d+)\s*\)", r"ALIGN(\1)", text)
    text = re.sub(r"ALIGN\(\s*([^,()]+?)\s*,\s*(\d+)\s*\)", r"((\1 + \2 - 1) & ~(\2 - 1))", text)
    text = re.sub(r"\n[ \t]*\. = ALIGN\(\d+\);(?=\n[ \t]*\w+_END = \.;)", "", text)
    text = re.sub(r"HIDDEN\(\s*(\w+)\s*=\s*([^)]+)\);", r"\1 = \2;", text)
    text = re.sub(r"\s*SUBALIGN\(\s*\d+\s*\)", "", text)
    addresses = dict(re.findall(r"^\s*(\.\S+)\s+(0x[0-9A-Fa-f]+)\s*:", text, re.MULTILINE))
    text = re.sub(r"=\s*ADDR\(\s*(\.\S+)\s*\)\s*;", lambda m: f"= {addresses.get(m.group(1), '0')};", text)
    for old, new in renamed.items():
        if (directory / new.replace("build/asm/", "asm_pp/").removesuffix(".o")).is_file():
            text = text.replace(old, new)
    reference = next((directory / "assets").glob("*.elf"))
    for name, tail in data_tails(reference).items():
        marker = f"{name}_DATA_END = .;"
        text = text.replace(marker, "\n        ".join(f"BYTE(0x{b:02X});" for b in tail) + "\n        " + marker)
    loads = [s for s in elf.read(reference)["segments"] if s["type"] == elf.PT_LOAD]
    header = "PHDRS\n{\n" + "".join(f"  load{i} PT_LOAD FLAGS({l['flags']});\n" for i, l in enumerate(loads)) + "}\n"

    def segment(m: re.Match) -> str:
        address = int(m.group(2), 16)
        i = next(i for i, l in enumerate(loads) if l["address"] <= address < l["address"] + l["memsz"])
        return m.group(1) + f" :load{i}" + m.group(3)
    text = re.sub(r"(\.[^\s]+\s+(0x[0-9A-Fa-f]+)\s*:[^{]*\{.*?\n\s*})([^\n]*)", segment, text, flags=re.DOTALL)
    path.write_text("INCLUDE config/undefined_symbols.ld\n" + header + text)


def asm_names(text: str) -> str:
    """splat's names in the assembly with their own prefixes, f_ and d_, so that no assembly
    symbol has the name of a C one (C names its functions func_ and its data D_). In another
    release splat's names are that release's addresses, which C names (v1.01's) can share
    with other values, so its shorter D_XXXXXX names are renamed too."""
    digits = "{8}" if levels.VERSION == "us" else "{6,8}"
    return re.sub(rf"\b(func|D)_([0-9A-F]{digits})\b", lambda m: ("f_" if m.group(1) == "func" else "d_") + m.group(2), text)


def undefined_symbols(directory: Path, extra: dict[str, int] | None = None,
                      aliases: dict[str, str] | None = None) -> None:
    """config/undefined_symbols.ld: splat's undefined symbols, every D_XXXXXXXX the assembly
    uses without defining at its address, and EXTRA."""
    values = {}
    for name in ("undefined_syms_auto.txt", "undefined_funcs_auto.txt"):
        path = directory / "config" / name
        if path.is_file():
            for line in path.read_text().splitlines():
                line = line.split("//")[0].strip()
                if "=" in line:
                    symbol, value = line.rstrip(";").split("=", 1)
                    values[asm_names(symbol.strip())] = value.strip()
    used, defined = set(), set()
    for source in (directory / "asm_pp").rglob("*.s"):
        text = source.read_text()
        used.update(re.findall(r"\b[df]_[0-9A-F]{6,8}\b", text))
        defined.update(re.findall(r"^\s*(\w+):", text, re.MULTILINE))
    for symbol in used - defined:
        values[symbol] = "0x" + symbol[2:]
    for symbol, value in (extra or {}).items():
        values[symbol] = f"{value:#x}"
    for symbol, expression in (aliases or {}).items():
        values[symbol] = expression
    (directory / "config/undefined_symbols.ld").write_text(
        "".join(f"{s} = {v};\n" for s, v in sorted(values.items())))


# --- C ----------------------------------------------------------------------------------

COMPILER = ROOT / "build/compiler/tools"
DEFAULT_FLAGS = "-O2 -G0 -ffunction-sections"
# The boot's and every level's $gp, and where a level's program replaces the boot's memory:
# levels.GP and levels.LEVEL_BASE, the selected release's.
INSTRUCTION = re.compile(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/")
TEXT_HEADER = '.set noat\n.set noreorder\n.section .text, "ax"\n'


SDK_COMPILER = ROOT / "build/compiler/sdk"
SDATA_ALIASES = Path(__file__).with_name("sdata_aliases.py")


def flags_for(source: Path) -> str:
    """config/cflags.txt: `glob<TAB>flags` lines, the first that matches; else the default,
    with -G8 for a file named *-g8.c. Flags starting with "sdk" select the SDK compiler."""
    import fnmatch
    relative = source.relative_to(ROOT).as_posix()
    path = ROOT / "config/cflags.txt"
    if path.is_file():
        for line in path.read_text().splitlines():
            if line.strip() and not line.startswith("#"):
                pattern, flags = line.split("\t", 1)
                if fnmatch.fnmatch(relative, pattern):
                    return flags
    return DEFAULT_FLAGS.replace("-G0", "-G8") if source.stem.endswith("-g8") else DEFAULT_FLAGS


@lru_cache(maxsize=4096)
def file_digest(path: Path, stat_key: tuple[int, ...]) -> str:
    """Hash once per file version; ctime/inode also detect replacements preserving mtime."""
    return hashlib.sha256(path.read_bytes()).hexdigest()


def compile_key(source: Path, flags: str) -> str:
    """Private object-cache key for the inputs used by the selected compiler chain."""
    compiler = SDK_COMPILER if flags.startswith("sdk") else COMPILER
    programs = ("xgcc", "cpp", "cc1") if flags.startswith("sdk") else ("cpp", "cc1")
    inputs = {source, Path(__file__), COMPILER / "as", SDATA_ALIASES}
    inputs.update(compiler / name for name in programs)
    for directory in (ROOT / "include", compiler / "include", source.parent):
        inputs.update(directory.rglob("*.h"))
    digests = []
    for path in sorted(inputs):
        stat = path.stat()  # A missing tool must not silently reuse an old object.
        version = (stat.st_mtime_ns, stat.st_ctime_ns, stat.st_size, stat.st_ino)
        digests.append((str(path), file_digest(path, version)))
    return json.dumps([flags, os.environ.get("RAC2_LINUX", ""), digests])


def split_flags(flags: str) -> tuple[list[str], list[str]]:
    """A unit's flags as (compiler arguments, assembler arguments).

    Both frontends stop at assembly, so standard -Wa, options are forwarded here. SDK units
    (flags starting with "sdk") also get --r5900-pool-li-d: the SDK's objects pool li.d
    constants in .lit8, while the game code builds them inline, the assembler's default
    (docs/build/compiler-notes.md, "Double constants in general registers")."""
    compiler_args, assembler_args = [], []
    sdk = flags.startswith("sdk")
    if sdk:
        assembler_args.append("--r5900-pool-li-d")
    for arg in shlex.split(flags[3:] if sdk else flags):
        if arg == "-Wa" or arg.startswith("-Wa,"):
            forwarded = arg[4:].split(",")
            if not all(forwarded):
                raise ValueError("-Wa, requires nonempty comma-separated assembler arguments")
            assembler_args.extend(forwarded)
        else:
            compiler_args.append(arg)
    return compiler_args, assembler_args


def compile_c(source: Path) -> Path:
    """build/obj/<source>.o, reused only with the same source, headers and toolchain."""
    out = BUILD / "obj" / (source.relative_to(ROOT).as_posix() + ".o")
    flags = flags_for(source)
    try:
        compiler_args, assembler_args = split_flags(flags)
    except ValueError as error:
        sys.exit(f"{source.relative_to(ROOT)} has invalid compiler flags: {error}")
    compiler_flags = shlex.join(compiler_args)
    assemble = shlex.join([str(COMPILER / "as"), *assembler_args, "-o", "x.o", "x.s"])
    metadata = f"python3 '{SDATA_ALIASES}' x.s; "
    stamp = out.with_suffix(".inputs")
    key = compile_key(source, flags)
    if out.is_file() and stamp.is_file() and stamp.read_text() == key:
        return out
    out.parent.mkdir(parents=True, exist_ok=True)
    runner = shlex.split(os.environ.get("RAC2_LINUX", ""))
    if flags.startswith("sdk"):
        # the SDK compiler's driver (integrated cpp), then the game compiler's assembler
        script = (f"set -e; t=$(mktemp -d); cd $t; cp '{source}' x.c; "
                  f"'{SDK_COMPILER}/xgcc' -B'{SDK_COMPILER}/' -S {compiler_flags} -I'{ROOT}/include' -I'{SDK_COMPILER}/include' "
                  f"-I'{source.parent}' x.c -o x.s; {metadata}{assemble}; cp x.o '{out}'.$$; mv '{out}'.$$ '{out}'; rm -rf $t")
    else:
        script = (f"set -e; t=$(mktemp -d); cd $t; cp '{source}' x.c; "
                  f"'{COMPILER}/cpp' -I'{COMPILER}/include' -I'{ROOT}/include' -I'{source.parent}' x.c > x.i; "
                  f"'{COMPILER}/cc1' -quiet {compiler_flags} x.i -o x.s; {metadata}{assemble}; "
                  f"cp x.o '{out}'.$$; mv '{out}'.$$ '{out}'; rm -rf $t")
    result = subprocess.run([*runner, "bash", "-c", script], capture_output=True, text=True)
    if result.returncode:
        sys.exit(f"{source.relative_to(ROOT)} does not compile:\n{result.stderr[-3000:]}")
    fresh = stamp.with_suffix(f".inputs.{os.getpid()}.tmp")
    fresh.write_text(key)
    os.replace(fresh, stamp)
    return out


def program_functions(name: str) -> dict[str, list[tuple[int, int]]]:
    """function name -> [(address, size)] of its places in program NAME."""
    out = {}
    if name == "boot":
        for fname, address, size in levels.read_boot_functions():
            out.setdefault(fname, []).append((address, size))
        return out
    number = int(name[:2])
    for fname, _, size, _, places in levels.read_catalogue():
        for level, address in places:
            if level == number:
                out.setdefault(fname, []).append((address, size))
    return out


def sources_for(name: str) -> list[Path]:
    """The C a program links: the boot's (src/core/, src/game/) and the levels' shared C, since
    each program holds copies of functions of the others, and a level's own. Another release
    links the same C (the functions its catalogue names), and its own from src/<version>/."""
    found = []
    roots = [ROOT / "src"] + ([ROOT / "src" / levels.VERSION] if levels.VERSION != "us" else [])
    for root in roots:
        for d in ("core", "game", "levels/shared"):
            found += sorted((root / d).rglob("*.c"))
        if name != "boot":
            found += sorted((root / "levels" / name).rglob("*.c"))
    return found


def sext(x: int) -> int:
    return x - 0x10000 if x & 0x8000 else x


def address_in_name(symbol: str) -> int | None:
    """The address a name states: func_XXXXXXXX, D_XXXXXXXX, or one of them at its end."""
    m = re.search(r"(?:^|_)(?:func|FUN|D)_([0-9A-F]{8})$", symbol)
    return int(m.group(1), 16) if m else None


class Placement:
    """The C functions a program takes, where, and the symbol values their relocations need."""

    def __init__(self, name: str, image: dict):
        self.name, self.image = name, image
        self.functions = program_functions(name)
        self.placed = {}          # C symbol -> (address, size, object path, section name)
        self.differ = []          # (C symbol, reason)
        self.values = {}          # symbol -> value
        self.objects = []
        self.tables = {}          # (object path, section name) -> (address, size)
        self.scalar_pools = set() # the relocation-free subset of tables

    def retail(self, address: int, size: int) -> bytes:
        for seg in self.image["segments"]:
            if (seg["type"] == elf.PT_LOAD and seg["address"] <= address
                    and address + size <= seg["address"] + seg["filesz"]):
                at = seg["offset"] + address - seg["address"]
                return self.image["data"][at:at + size]
        return b""

    def expected(self, symbol: str) -> int | None:
        """The value a symbol must have here: a function of this program its place, else the
        address its name states."""
        if symbol in self.functions and len(self.functions[symbol]) == 1:
            return self.functions[symbol][0][0]
        if levels.VERSION != "us":
            return None          # names state v1.01's addresses: another release's are read
        if re.fullmatch(r"func_L\d\d_([0-9A-F]{8})", symbol) or symbol.startswith("r1_"):
            return None          # r1_: a name carried from rac1, its rac2 value read from the bytes
        m = re.fullmatch(r"(?:D|f)_L(\d\d)_([0-9A-F]{8})", symbol)
        if m:        # data or code of level NN: there at its address, elsewhere where it reads
            return int(m.group(2), 16) if self.name[:2] == m.group(1) else None
        address = address_in_name(symbol)
        if address is not None and self.name != "boot" and address >= levels.LEVEL_BASE:
            # a boot address in the memory a level replaces: the level has its own copy there
            return None
        return address

    def derive(self, obj: dict, index: int, address: int) -> tuple[dict, str | None]:
        """The symbol values that make section INDEX, placed at ADDRESS, read as the retail
        bytes there; or why it cannot."""
        sec = obj["sections"][index]
        data, ref = sec["data"], self.retail(address, len(sec["data"]))
        if len(ref) != len(data):
            return {}, "outside the program"
        in_order = obj["relocations"].get(index, [])
        relocs = sorted(in_order)
        touched = {o for o, _, _ in relocs}
        # The assembler lists each %hi just before the %lo it pairs with (mips_frob_file),
        # which can lie at a lower address: a %hi in a loop's last delay slot pairs with the
        # %lo at the loop's top. Pair them in the object's order, as the linker does.
        pair = {}
        for k, (at, kind, sym) in enumerate(in_order):
            if kind == elf.R_MIPS_HI16:
                pair[at] = next((o for o, t, s in in_order[k + 1:]
                                 if t == elf.R_MIPS_LO16 and s == sym), None)
        for at in range(0, len(data), 4):
            if at not in touched and data[at:at + 4] != ref[at:at + 4]:
                return {}, f"instruction at +{at:#x} differs"
        values = {}

        def agree(symbol: str, value: int) -> str | None:
            value &= 0xFFFFFFFF
            if values.setdefault(symbol, value) != value:
                return f"{symbol} needs two values"
            return None

        def name_of(sym: int) -> str:
            """A symbol's name; a section symbol (a call or address within the same object)
            becomes "§" and the section's name, whose start the linker places."""
            s = obj["symbols"][sym]
            return s["name"] if s["type"] != 3 else "§" + obj["sections"][s["section"]]["name"]
        word = lambda b, at: struct.unpack_from("<I", b, at)[0]
        i = 0
        while i < len(relocs):
            at, kind, sym = relocs[i]
            symbol = name_of(sym)
            mine, theirs = word(data, at), word(ref, at)
            if kind == elf.R_MIPS_26:
                if (mine ^ theirs) & 0xFC000000:
                    return {}, f"jump at +{at:#x} differs"
                err = agree(symbol, ((address & 0xF0000000) | ((theirs & 0x3FFFFFF) << 2))
                            - ((mine & 0x3FFFFFF) << 2))
            elif kind == elf.R_MIPS_HI16:
                # value = retail address - addend, both from the %hi and its paired %lo
                lo_at = pair.get(at)
                if lo_at is None:
                    return {}, f"%hi at +{at:#x} has no %lo"
                if (mine ^ theirs) & 0xFFFF0000:
                    return {}, f"%hi at +{at:#x} differs"
                target = ((theirs & 0xFFFF) << 16) + sext(word(ref, lo_at) & 0xFFFF)
                addend = ((mine & 0xFFFF) << 16) + sext(word(data, lo_at) & 0xFFFF)
                err = agree(symbol, target - addend)
            elif kind == elf.R_MIPS_LO16:
                err = None            # checked below, once every %hi has given its value
            elif kind == elf.R_MIPS_GPREL16:
                if (mine ^ theirs) & 0xFFFF0000:
                    return {}, f"gp access at +{at:#x} differs"
                err = agree(symbol, levels.GP + sext(theirs & 0xFFFF) - sext(mine & 0xFFFF))
            elif kind == elf.R_MIPS_32:
                err = agree(symbol, theirs - mine)
            else:
                return {}, f"relocation type {kind}"
            if err:
                return {}, err
            i += 1
        for at, kind, sym in relocs:
            if kind != elf.R_MIPS_LO16:
                continue
            symbol = name_of(sym)
            mine, theirs = word(data, at), word(ref, at)
            if symbol not in values:
                return {}, f"%lo at +{at:#x} without a %hi"
            if (mine ^ theirs) & 0xFFFF0000 or (values[symbol] + sext(mine & 0xFFFF) - theirs) & 0xFFFF:
                return {}, f"%lo at +{at:#x} differs"
        for symbol, value in values.items():
            if symbol.startswith("§"):
                continue
            want = self.expected(symbol)
            if want is not None and want != value:
                return {}, f"{symbol} would be at {value:#010x}"
        return values, None

    def place(self) -> None:
        taken, needs, objects = set(), {}, {}
        for source in sources_for(self.name):
            path = compile_c(source)
            obj = elf.read_object(path)
            objects[path] = obj
            for sym in obj["symbols"]:
                if sym["type"] != 2 or sym["name"] not in self.functions:
                    continue
                index = sym["section"]
                section = obj["sections"][index]["name"]
                # its own section, or a unit's .text that holds just it (no -ffunction-sections)
                alone = section == ".text" and sym["value"] == 0 and sym["size"] == obj["sections"][index]["size"]
                if section != ".text." + sym["name"] and not alone:
                    self.differ.append((sym["name"], f"in section {section}"))
                    continue
                for address, size in self.functions[sym["name"]]:
                    if address in taken:
                        continue
                    have = obj["sections"][index]["size"]
                    if have != size:
                        # zero padding after the function, in the C or in the program
                        lo, hi = min(have, size), max(have, size)
                        if any(obj["sections"][index]["data"][lo:]) or any(self.retail(address + lo, hi - lo)):
                            self.differ.append((sym["name"], f"{have} bytes, expected {size}"))
                            break
                        size = have
                    values, why = self.derive(obj, index, address)
                    clash = next((s for s, v in values.items() if not s.startswith("§")
                                  and self.values.get(s, v) != v), None)
                    if why or clash:
                        self.differ.append((sym["name"], why or f"{clash} needs two values"))
                        break
                    self.values.update({k: v for k, v in values.items() if not k.startswith("§")})
                    needs[sym["name"]] = {k[1:]: v for k, v in values.items() if k.startswith("§")}
                    self.placed[sym["name"]] = (address, size, path, section)
                    taken.add(address)
                    break
        # A call within one object goes to the section's placement: it must be the right one.
        changed = True
        while changed:
            changed = False
            where = {(o, sec): a for a, _, o, sec in self.placed.values()}
            tables, scalar_pools, bindings = {}, set(), {}
            for name, need in needs.items():
                if name in self.placed:
                    for sec, address in need.items():
                        bindings.setdefault((self.placed[name][2], sec), set()).add(address)
            for name, need in needs.items():
                if name not in self.placed:
                    continue
                path = self.placed[name][2]
                obj = objects[path]
                for sec, address in need.items():
                    if sec not in (".rodata", ".rdata"):
                        continue
                    if len(bindings[path, sec]) != 1:
                        continue
                    index = next(i for i, s in enumerate(obj["sections"]) if s["name"] == sec)
                    if self.jump_table(obj, index, address, path, where):
                        tables[path, sec] = (address, obj["sections"][index]["size"])
                    elif self.scalar_pool(obj, index, address):
                        tables[path, sec] = (address, obj["sections"][index]["size"])
                        scalar_pools.add((path, sec))
            # No two compiler input sections may claim the same retail bytes.
            conflicts = {key for key, (a, n) in tables.items()
                         if any(key != other and a < b + m and b < a + n
                                for other, (b, m) in tables.items())
                         or any(a < b + m and b < a + n for b, m, _, _ in self.placed.values())}
            for key in conflicts:
                del tables[key]
            where.update({key: a for key, (a, _) in tables.items()})
            for name, need in needs.items():
                if name in self.placed and any(where.get((self.placed[name][2], sec)) != a for sec, a in need.items()):
                    bad = next(sec for sec, a in need.items() if where.get((self.placed[name][2], sec)) != a)
                    self.differ.append((name, f"needs {bad} at its place, which is not C"))
                    del self.placed[name]
                    changed = True
        self.tables = {key: value for key, value in tables.items()
                       if any(o == key[0] and needs[sym].get(key[1]) == value[0]
                              for sym, (_, _, o, _) in self.placed.items())}
        self.scalar_pools = scalar_pools & self.tables.keys()
        self.objects = sorted({o for _, _, o, _ in self.placed.values()})

    def scalar_pool(self, obj: dict, index: int, address: int) -> bool:
        """Place one whole, relocation-free read-only input section without rewriting it.

        Its address comes from the calling text's relocations, not a value search or
        a configured address. Check the entire pool, including padding and unused
        constants, against exactly one initialized retail data section/load segment.
        Relocated pointers, mixed branch tables and writable pools stay unsupported.
        """
        sec = obj["sections"][index]
        size, alignment = sec["size"], sec.get("align", 1)
        if (sec["name"] not in (".rodata", ".rdata") or sec["type"] != elf.SHT_PROGBITS
                or sec.get("flags", 0) != 2 or size <= 0 or len(sec["data"]) != size
                or alignment <= 0 or alignment & (alignment - 1) or address % alignment
                or obj["relocations"].get(index)
                or any(s["section"] == index and s["type"] == 2 for s in obj["symbols"])):
            return False
        owners = [s for s in self.image["sections"] if s["type"] == elf.SHT_PROGBITS
                  and s.get("flags", 0) & 2 and not s.get("flags", 0) & 4
                  and s["name"] not in (".text", "core.text")
                  and s["address"] <= address and address + size <= s["address"] + s["size"]]
        loads = [s for s in self.image["segments"] if s["type"] == elf.PT_LOAD
                 and s["address"] <= address and address + size <= s["address"] + s["filesz"]]
        return len(owners) == len(loads) == 1 and self.retail(address, size) == sec["data"]

    def jump_table(self, obj: dict, index: int, address: int, path: Path, where: dict) -> bool:
        """Qualify a complete compiler-owned table, including every case destination.

        Like RAC1's section-placement method, retain the original compiler section;
        neither instructions nor table entries are rewritten. Mixed constant pools,
        partial tables and targets outside placed C text remain unsupported.
        """
        sec = obj["sections"][index]
        size, alignment = sec["size"], sec.get("align", 4)
        if (sec["type"] != elf.SHT_PROGBITS or sec.get("flags", 2) != 2 or not size or size % 4
                or len(sec["data"]) != size
                or alignment < 4 or alignment & (alignment - 1) or address % alignment):
            return False
        owners = [s for s in self.image["sections"] if s["type"] == elf.SHT_PROGBITS
                  and s["name"] not in (".text", "core.text")
                  and s["address"] <= address and address + size <= s["address"] + s["size"]]
        if len(owners) != 1:
            return False
        relocs = sorted(obj["relocations"].get(index, []))
        # Every word is a case entry, except the zero words the compiler's `.align 4`
        # puts between two tables of one function: each gap is shorter than 16 bytes
        # and ends at a 16-byte boundary where the next table starts.
        offsets = [r[0] for r in relocs]
        covered = set(offsets)
        if not offsets or offsets[0] != 0 or len(covered) != len(offsets) or any(o % 4 for o in offsets):
            return False
        for at in range(0, size, 4):
            if at in covered:
                continue
            gap_end = next((o for o in offsets if o > at), None)
            if gap_end is None or gap_end % 16 or gap_end - at >= 16 or sec["data"][at:at + 4] != bytes(4):
                return False
        values, why = self.derive(obj, index, address)
        if why:
            return False
        for at, kind, symbol in relocs:
            target = obj["symbols"][symbol]
            if kind != elf.R_MIPS_32 or target["type"] != 3:
                return False
            text = obj["sections"][target["section"]]
            base = where.get((path, text["name"]))
            offset = struct.unpack_from("<I", sec["data"], at)[0]
            if (base is None or not text["name"].startswith(".text") or offset % 4
                    or offset >= text["size"] or values.get("§" + text["name"]) != base):
                return False
        return True


def split_text(text: str, bodies: dict[int, tuple[str, int, str]]) -> tuple[list[tuple[str, str]], dict[str, str]]:
    """Cut one assembly file at the functions in BODIES (address -> (C symbol, size, object
    input)): [("asm", text) or ("c", input)], and the labels removed with a body, each as an
    expression of its C symbol."""
    lines = text.splitlines(keepends=True)
    pieces, labels, current, i = [], {}, [], 0
    while i < len(lines):
        m = re.fullmatch(r"\.globl (f_([0-9A-F]{8}))", lines[i].strip())
        if not m or int(m.group(2), 16) not in bodies:
            current.append(lines[i])
            i += 1
            continue
        address = int(m.group(2), 16)
        symbol, size, owner = bodies[address]
        seen, j, pending = 0, i, []
        while j < len(lines) and seen < size:
            ins = INSTRUCTION.search(lines[j])
            if ins:
                if int(ins.group(1), 16) != address + seen:
                    sys.exit(f"{symbol}: the assembly at {address:#x} is not contiguous")
                seen += 4
            else:
                lab = re.match(r"^\s*([A-Za-z_.$][\w.$]*):", lines[j])
                if lab:
                    pending.append((lab.group(1), seen))
                elif re.match(r"^\s*\.section", lines[j]):
                    sys.exit(f"{symbol}: a section change inside the body at {address:#x}")
            j += 1
        if seen != size:
            sys.exit(f"{symbol}: the assembly at {address:#x} is shorter than {size} bytes")
        for label, offset in pending:
            labels[label.lstrip(".")] = symbol if offset == 0 else f"{symbol} + {offset:#x}"
        if "".join(current).strip():
            pieces.append(("asm", "".join(current)))
        pieces.append(("c", owner))
        current, i = [], j
    if INSTRUCTION.search("".join(current)):
        pieces.append(("asm", "".join(current)))
    # A local label (.L) used in one piece and defined in another becomes a global XL_ name.
    asm = [k for k, p in enumerate(pieces) if p[0] == "asm"]
    defined = {}
    for k in asm:
        for m in re.finditer(r"(?m)^\s*\.?L([0-9A-Fa-f]+):", pieces[k][1]):
            defined.setdefault(m.group(1), k)
    crossing = {m.group(1) for k in asm for m in re.finditer(r"\.?L([0-9A-Fa-f]+)\b", pieces[k][1])
                if defined.get(m.group(1), k) != k}
    crossing |= {l[1:] for l in labels if l.startswith("L") and re.fullmatch(r"L[0-9A-Fa-f]+", l)}
    for k in asm:
        body = re.sub(r"\.?L([0-9A-Fa-f]+)\b", lambda m: "XL_" + m.group(1) if m.group(1) in crossing
                      else m.group(0), pieces[k][1])
        body = re.sub(r"(?m)^(\s*)XL_([0-9A-Fa-f]+):", lambda m: f"{m.group(1)}.globl XL_{m.group(2)}\n"
                      f"{m.group(1)}XL_{m.group(2)}:" if defined.get(m.group(2)) == k else m.group(0), body)
        pieces[k] = ("asm", body)
    labels = {("XL_" + l[1:] if l[1:] in crossing and l.startswith("L") else l): v for l, v in labels.items()}
    return pieces, labels


# --- programs ----------------------------------------------------------------------------

def level_reference(number: int) -> Path:
    """The level's program as an executable, from its sections in baserom/levels/."""
    d = levels.DUMP / levels.level_dir(number)
    m = json.loads((d / "manifest.json").read_text())
    path = out_dir() / "reference" / f"{levels.level_dir(number)}.elf"
    if path.is_file() and path.stat().st_mtime >= max(f.stat().st_mtime for f in d.iterdir()):
        return path           # current: tools/check.py runs side by side must not rewrite it
    sections = [{"name": "." + s["name"] if s["name"] in ("text", "data", "bss") else s["name"],
                 "address": s["address"], "type": s["type"],
                 "data": (d / f"{s['name']}.bin").read_bytes() if s["type"] != elf.SHT_NOBITS else b"\0" * s["size"]}
                for s in m["sections"]]
    path.parent.mkdir(parents=True, exist_ok=True)
    fresh = path.with_suffix(f".{os.getpid()}.tmp")
    elf.write_exec(fresh, m["entry"], sections)
    os.replace(fresh, path)   # whole or not at all, for a reader in another process
    return path


def scalar_string_width(lines: list[str], index: int, address: int) -> int | None:
    """Size of an annotated asciz record, including explicitly proved zero padding.

    Splat prints the exact bytes on the next comment line. Accept a bounded
    ASCII/C-escape spelling only when it agrees with those bytes. Extra zeros
    require a following explicit alignment; a label before that padding would
    have a different address, so leave such a record unsupported.
    """
    quoted = r'"(?:[\x20-\x21\x23-\x5B\x5D-\x7E]|\\(?:[\\\"abfnrtv]|[0-3][0-7]{2}))*"'
    literal = re.fullmatch(r"\s*/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s*\*/\s*"
                           r"\.asciz\s+(" + quoted + r")\s*", lines[index])
    if literal is None or index + 1 >= len(lines):
        return None
    annotation = re.fullmatch(r"\s*/\*\s*([0-9A-Fa-f]+)\s*\*/\s*", lines[index + 1])
    if annotation is None or len(annotation[1]) % 2:
        return None
    try:
        payload = ast.literal_eval(literal[1]).encode("latin1") + b"\0"
    except (SyntaxError, ValueError, UnicodeError):
        return None
    encoded = bytes.fromhex(annotation[1])
    if not encoded.startswith(payload) or any(encoded[len(payload):]):
        return None
    if len(encoded) == len(payload):
        return len(encoded)
    cursor, end = address + len(payload), address + len(encoded)
    for following in lines[index + 2:]:
        alignment = re.fullmatch(r"\s*\.align\s+([1-4])\s*", following)
        if alignment:
            boundary = 1 << int(alignment[1])
            cursor = (cursor + boundary - 1) & -boundary
            if cursor == end:
                return len(encoded)
            if cursor > end:
                return None
        elif (following.strip()
              and not re.fullmatch(r"\s*/\*.*?\*/\s*", following)
              and not re.fullmatch(r"\s*\.globl\s+[A-Za-z_.$][\w.$]*\s*", following)):
            return None
    return None


def split_table_data(text: str, tables: dict[int, tuple[int, str]], *, scalar: bool = False
                     ) -> tuple[list[tuple[str, str]], dict[str, str]]:
    """Replace measured whole-word data spans with compiler section inputs.

    Keep all surrounding assembly and retain names defined inside a replaced span
    at their measured addresses. Branch tables require one .word per annotated
    record. Relocation-free scalar pools also accept numeric .byte/.short records
    and asciz records whose literal bytes and explicit padding are proved.
    Records must be contiguous and fully contained; no padding is inferred.
    """
    lines = text.splitlines(keepends=True)
    pieces, aliases, current, pending = [], {}, [], []
    active, seen, consumed = None, set(), set()
    string_annotations = set()
    spans = sorted((a, a + n) for a, (n, _) in tables.items())
    if any(end <= a or (not scalar and (a % 4 or end % 4)) for a, end in spans):
        sys.exit("invalid compiler jump table span")
    if any(end > following for (_, end), (following, _) in zip(spans, spans[1:])):
        sys.exit("overlapping compiler jump tables")
    for line_index, line in enumerate(lines):
        if line_index in string_annotations:
            continue
        ins = (re.search(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})(?:\s+[0-9A-Fa-f]+)?\s*\*/", line)
               if scalar else INSTRUCTION.search(line))
        if not ins:
            pending.append(line)
            continue
        address = int(ins.group(1), 16)
        if active is not None and address == active[0] + active[1]:
            active = None
        if address in tables:
            if active:
                sys.exit("overlapping compiler jump tables")
            size, owner = tables[address]
            active = (address, size, owner)
            seen.add(address)
            # Strings and alignment before a table belong to the preceding piece.
            # Only its immediately preceding labels/comments move with the table.
            cut = len(pending)
            while cut and (not pending[cut - 1].strip()
                           or re.fullmatch(r"\s*/\*.*?\*/\s*", pending[cut - 1])
                           or re.fullmatch(r"\s*\.globl\s+[A-Za-z_.$][\w.$]*\s*", pending[cut - 1])
                           or re.fullmatch(r"\s*[A-Za-z_.$][\w.$]*:\s*", pending[cut - 1])):
                cut -= 1
            current.extend(pending[:cut])
            pending = pending[cut:]
            if "".join(current).strip():
                pieces.append(("asm", "".join(current)))
            current = []
            pieces.append(("c", owner))
        if active:
            start, size, _ = active
            width = 4
            if scalar:
                directive = re.search(r"\*/\s*\.(byte|short|half|word)\s+([^;#\n]+)\s*$", line.rstrip())
                if directive:
                    fields = [field.strip() for field in directive[2].split(",")]
                    if any(not re.fullmatch(r"-?(?:0[xX][0-9A-Fa-f]+|[0-9]+)", f) for f in fields):
                        sys.exit("compiler scalar pool span is not fixed-size numeric data")
                    width = {"byte": 1, "short": 2, "half": 2, "word": 4}[directive[1]] * len(fields)
                else:
                    width = scalar_string_width(lines, line_index, address)
                    if width is None:
                        sys.exit(f"compiler scalar pool record at {address:#x} is not proved literal data")
                    string_annotations.add(line_index + 1)
            if address != start + sum(1 for a in consumed if start <= a < start + size):
                sys.exit("noncontiguous compiler jump table span")
            if address + width > start + size:
                sys.exit("compiler data record crosses its input-section boundary")
            if not scalar and not re.search(r"\*/\s*\.(?:word|float)\s+[^,;\n]+$", line.rstrip()):
                sys.exit("compiler jump table span is not whole-word data")
            for previous in pending:
                label = re.fullmatch(r"\s*([A-Za-z_.$][\w.$]*):\s*", previous)
                if label:
                    aliases[label.group(1)] = f"{address:#x}"
                elif scalar and (alignment := re.fullmatch(r"\s*\.align\s+([1-4])\s*", previous)):
                    if address % (1 << int(alignment[1])):
                        sys.exit("unproved alignment inside compiler scalar pool")
                elif (previous.strip()
                      and not re.fullmatch(r"\s*\.globl\s+[A-Za-z_.$][\w.$]*\s*", previous)
                      and not re.fullmatch(r"\s*/\*.*?\*/\s*", previous)):
                    sys.exit("unsupported directive inside compiler jump table")
            consumed.update(range(address, address + width))
            if address + width == start + size:
                active = None
        else:
            current.extend(pending)
            current.append(line)
        pending = []
    current.extend(pending)
    if "".join(current).strip():
        pieces.append(("asm", "".join(current)))
    if seen != tables.keys() or any(sum(1 for a in consumed if start <= a < start + n) != n
                                    for start, (n, _) in tables.items()):
        sys.exit("incomplete compiler jump table span")
    return pieces, aliases


def build_program(name: str, reference: Path, strict: bool = False) -> tuple[int, int]:
    """Build program NAME; returns (C functions placed, their bytes)."""
    directory = out_dir() / name
    if directory.exists():
        shutil.rmtree(directory)
    renamed = splat_config(reference, directory, "program")
    image = elf.read(reference)
    placement = Placement(name, image)
    # splat starts a function at every place of a catalogued one, named f_XXXXXXXX so that no
    # assembly label has the name of a C function
    (directory / "config/symbol_addrs.txt").write_text("".join(
        f"f_{a:08X} = 0x{a:08X}; // type:func size:0x{n:X}\n"
        for a, n in sorted({p for places in placement.functions.values() for p in places})))
    run([sys.executable, "-m", "splat", "split", "config/splat.yaml"], directory, directory / "split.log")
    run([sys.executable, str(ROOT / "tools/expand_asm.py"), "--src", "asm", "--dst", "asm_pp"],
        directory, directory / "expand.log")
    adapt_linker(directory, renamed)
    skipped = {old.removeprefix("build/asm/").removesuffix(".o") for old, new in renamed.items()
               if (directory / new.replace("build/asm/", "asm_pp/").removesuffix(".o")).is_file()}
    sources = [s for s in sorted((directory / "asm_pp").rglob("*.s"))
               if s.relative_to(directory / "asm_pp").as_posix() not in skipped]
    for source in sources:
        source.write_text(asm_names(source.read_text()))

    placement.place()
    extra, script = dict(placement.values), (directory / "config/rac2.ld").read_text()
    aliases = {}
    if placement.placed:
        bodies = {a: (sym, n, f"{Path(os.path.relpath(o, directory)).as_posix()}({sec})")
                  for sym, (a, n, o, sec) in placement.placed.items()}
        kept = []
        for source in sources:
            text = source.read_text()
            inside = {int(x, 16) for x in re.findall(r"^\.globl f_([0-9A-F]{8})$", text, re.MULTILINE)}
            mine = {a: v for a, v in bodies.items() if a in inside}
            if not mine:
                kept.append(source)
                continue
            old = "build/asm/" + source.relative_to(directory / "asm_pp").as_posix() + ".o(.text);"
            if script.count(old) != 1:
                sys.exit(f"{name}: cannot find {old} in the linker script")
            pieces, labels = split_text(text, mine)
            aliases.update(labels)
            inputs = []
            for k, (kind, body) in enumerate(pieces):
                if kind == "c":
                    inputs.append(body)
                    continue
                piece = directory / "asm_pp/pieces" / f"{source.stem}_{k}.s"
                piece.parent.mkdir(exist_ok=True)
                piece.write_text(body if body.lstrip().startswith(".set") else TEXT_HEADER + body)
                kept.append(piece)
                inputs.append("build/asm/" + piece.relative_to(directory / "asm_pp").as_posix() + ".o(.text);")
            script = script.replace(old, "\n        ".join(inputs))
            script = re.sub(re.escape(old[:-len("(.text);")]) + r"\(\.(?:data|rodata|bss)\);", "", script)
        sources = kept
        # Interleave original compiler data sections with the surrounding retail data.
        # Separate passes preserve the branch-table directive checks while allowing
        # relocation-free byte/halfword scalar pools in the same retail assembly file.
        for scalar in (False, True):
            tables = {a: (n, f"{Path(os.path.relpath(o, directory)).as_posix()}({sec});")
                      for (o, sec), (a, n) in placement.tables.items()
                      if ((o, sec) in placement.scalar_pools) == scalar}
            kept = []
            for source in sources:
                text = source.read_text()
                annotations = (re.compile(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})(?:\s+[0-9A-Fa-f]+)?\s*\*/")
                               if scalar else INSTRUCTION)
                addresses = {int(m.group(1), 16) for m in annotations.finditer(text)}
                mine = {a: value for a, value in tables.items() if a in addresses}
                if not mine:
                    kept.append(source)
                    continue
                section = re.search(r'\.section\s+(\.\w+)', text)
                if section is None or section.group(1) == ".text":
                    sys.exit("compiler data is not in a data assembly input")
                old = ("build/asm/" + source.relative_to(directory / "asm_pp").as_posix()
                       + f".o({section.group(1)});")
                if script.count(old) != 1:
                    sys.exit(f"{name}: cannot find data input {old}")
                pieces, labels = split_table_data(text, mine, scalar=scalar)
                aliases.update(labels)
                inputs = []
                for k, (kind, body) in enumerate(pieces):
                    if kind == "c":
                        inputs.append(body)
                    else:
                        piece = directory / "asm_pp/pieces" / f"{source.stem}_data_{k}.s"
                        piece.parent.mkdir(exist_ok=True)
                        piece.write_text(f'.section {section.group(1)}, "wa"\n' + body)
                        kept.append(piece)
                        inputs.append("build/asm/" + piece.relative_to(directory / "asm_pp").as_posix()
                                      + f".o({section.group(1)});")
                script = script.replace(old, "\n        ".join(inputs))
                for a in mine:
                    del tables[a]
            if tables:
                sys.exit(f"{name}: compiler data missing from assembly data")
            sources = kept
        discard = "".join(f"        {Path(os.path.relpath(o, directory)).as_posix()}(*)\n" for o in placement.objects)
        end = script.rindex("}")
        script = script[:end] + "    /DISCARD/ :\n    {\n" + discard + "    }\n" + script[end:]
        (directory / "config/rac2.ld").write_text(script)
        for sym, (a, n, o, sec) in placement.placed.items():
            aliases[f"f_{a:08X}"] = sym
        extra["_gp"] = levels.GP

    def assemble(source: Path) -> Path:
        out = directory / "build/asm" / (source.relative_to(directory / "asm_pp").as_posix() + ".o")
        out.parent.mkdir(parents=True, exist_ok=True)
        run([str(SN / "Ps2EeAs.exe"), "-o", str(out), str(source)], directory, out.with_suffix(".log"))
        return out
    with ThreadPoolExecutor(JOBS) as pool:
        objects = list(pool.map(assemble, sources))
    undefined_symbols(directory, extra, aliases)
    out = directory / "build/program.elf"
    # No object goes on the command line: the script names every one it places, which loads
    # it, and a Windows program takes 32,767 characters, fewer than a thousand C functions need.
    run([str(SN / "ld.exe"), "-T", "config/rac2.ld", "-e", hex(image["entry"]),
         "-Map", "build/program.map", "-o", "build/program.elf"],
        directory, directory / "link.log")
    same, why = elf.compare_loads(reference, out)
    c_bytes = sum(v[1] for v in placement.placed.values())
    label = name if levels.VERSION == "us" else f"{levels.VERSION} {name}"
    print(f"{label}: {'OK' if same else 'DIFFERS'}: {why}; {len(placement.placed)} C functions ({c_bytes} bytes)"
          + (f", {len(placement.differ)} do not match" if placement.differ else ""))
    for sym, why_not in placement.differ:
        print(f"  {sym}: {why_not}")
    if not same:
        sys.exit(1)
    (directory / "placed.json").write_text(json.dumps(
        {"program": name, "functions": {sym: [a, n] for sym, (a, n, _, _) in sorted(placement.placed.items())},
         "differ": dict(placement.differ),
         "values": {k: f"{v:#010x}" for k, v in sorted(placement.values.items())}}, indent=1) + "\n")
    if strict and placement.differ:
        sys.exit(f"{name}: strict check failed: {len(placement.differ)} C functions fell back to assembly")
    return len(placement.placed), c_bytes


def wine_prefixes(jobs: int) -> "queue.Queue[Path] | None":
    """A Wine prefix per program running at once (module docstring), ready to use: None when
    the build keeps one prefix (WINEPREFIX set, RAC2_ONE_PREFIX=1, or one job)."""
    if jobs < 2 or os.environ.get("WINEPREFIX") or os.environ.get("RAC2_ONE_PREFIX") == "1":
        return None
    slots = [BUILD / "wine" / str(n) for n in range(jobs)]
    wine = shlex.split(os.environ.get("RAC2_WINE", "wine").replace("{cwd}", str(ROOT)))

    def ready(slot: Path) -> None:
        # A prefix wineboot finished has its system.reg; a half-made one is made again.
        if (slot / "system.reg").is_file():
            return
        shutil.rmtree(slot, ignore_errors=True)
        slot.mkdir(parents=True)
        env = {**os.environ, "WINEPREFIX": str(slot), "WINEDEBUG": "-all"}
        subprocess.run([*wine, "wineboot", "-i"], env=env, stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL, timeout=600)

    with ThreadPoolExecutor(jobs) as pool:
        list(pool.map(ready, slots))
    free: "queue.Queue[Path]" = queue.Queue()
    for slot in slots:
        free.put(slot)
    return free


def main() -> None:
    version = levels.version_argument()
    strict = "--strict" in sys.argv[1:]
    args = [arg for arg in sys.argv[1:] if arg != "--strict"]
    if args == ["boot"]:
        build_program("boot", levels.BOOT, strict=strict)
    elif len(args) == 2 and args[0] == "level":
        number = int(args[1])
        build_program(levels.level_dir(number), level_reference(number), strict=strict)
    elif args[:1] in (["levels"], ["all"]) and (len(args) == 1 or len(args) == 3 and args[1] == "--jobs"):
        # The programs are independent: several at once, each in a process of its own.
        jobs = int(args[2]) if len(args) == 3 else max(1, min(8, JOBS // 2))
        programs = ([["boot"]] if args[0] == "all" else []) + [["level", str(n)] for n in sorted(levels.NAMES)]

        prefixes = wine_prefixes(jobs)

        def one(program: list[str]) -> tuple[int, str]:
            env = None
            if prefixes:
                slot = prefixes.get()
                env = {**os.environ, "WINEPREFIX": str(slot)}
            try:
                done = subprocess.run([sys.executable, __file__, *program, "--version", version,
                                       *(["--strict"] if strict else [])],
                                      capture_output=True, text=True, env=env)
            finally:
                if prefixes:
                    prefixes.put(slot)
            return done.returncode, (done.stdout + done.stderr).rstrip()

        failed = 0
        with ThreadPoolExecutor(jobs) as pool:
            for code, text in pool.map(one, programs):       # printed in program order
                print(text, flush=True)
                failed += bool(code)
        if failed:
            sys.exit(f"{failed} of {len(programs)} programs failed")
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
