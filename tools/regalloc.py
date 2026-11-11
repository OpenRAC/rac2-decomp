#!/usr/bin/env python3
"""Inspect GCC register allocation for current C without using the production cache.

  python3 tools/regalloc.py func_XXXXXXXX [--version pal] [--json]

The actual source unit and build.flags_for profile are compiled twice in a unique
build/regalloc/<function>/ directory: normally, then with diagnostic dump flags.
The complete objects must agree. Dumps and logs stay private in that directory;
this is allocator evidence, not a retail comparison or a matching-build verdict.

Parser/priority approach adapted from OpenRAC/rac1-decomp tools/regalloc.py
(GPL-3.0, origin/main revision 69c3e42d792adb90fabb90184a4fac915a48f5b2;
the reference file is unchanged since 948d2252ef6b7885418fa980db7ed9e4ec0fefa6),
itself adapted from rac3-uya-decomp. Distributed under this repository's GPL-3.0.
"""
import argparse
import hashlib
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
from fractions import Fraction
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import check
import levels

DUMP_FLAGS = ("-dl", "-dg", "-dL", "-dG", "-dS", "-dR")


def section(text: str, name: str) -> str:
    """Select exactly one function, never another function's allocator metadata."""
    match = re.search(rf"^;; Function {re.escape(name)}(?=\s|$).*?(?=^;; Function |\Z)",
                      text, re.M | re.S)
    return match[0] if match else ""


def priority(refs: int | None, live_length: int | None) -> Fraction | None:
    """An inferred score, not a dumped allocator priority; invalid inputs stay unknown."""
    if refs is None or live_length is None or refs <= 0 or live_length <= 0:
        return None
    return Fraction((refs.bit_length() - 1) * refs, live_length)


def parse_dumps(name: str, lreg: str, greg: str) -> dict:
    """Read real stats, queues, conflicts and dispositions from GCC 2.9x dumps."""
    local, global_ = section(lreg, name), section(greg, name)
    info = {}
    for match in re.finditer(r"^Register (\d+) used (\d+) times across (-?\d+) insns([^\n]*)",
                             local, re.M):
        pseudo, refs, live, rest = match.groups()
        calls = re.search(r"crosses (\d+) calls?\b", rest)
        info[int(pseudo)] = {"refs": int(refs), "live_length": int(live),
                             "stats_source": "lreg", "user_variable": "user var" in rest,
                             "calls_crossed": int(calls[1]) if calls else None}
    # -dG adds the real pre-allocation sorted candidates, beyond the global queue.
    passes = []
    for block in re.finditer(r"^Pass (\d+) registers to be allocated in sorted order:\s*\n"
                             r"((?:Register [^\n]*\n)*)", global_, re.M):
        entries = []
        for match in re.finditer(r"^Register (\d+), refs = (\d+), live_length = (-?\d+), size = (\d+)",
                                 block[2], re.M):
            pseudo, refs, live, size = map(int, match.groups())
            entries.append({"pseudo": pseudo, "refs": refs, "live_length": live, "size": size})
            if len(passes) == 0:
                row = info.setdefault(pseudo, {})
                row.update(refs=refs, live_length=live, size=size, stats_source="greg pass " + block[1])
        passes.append({"pass": int(block[1]), "sorted_candidates": entries})
    orders = [[int(n) for n in match[1].split()] for match in re.finditer(
        r"^;;\s*\d+ regs to allocate:[ \t]*([\d \t]*)$", global_, re.M)]
    conflicts = {int(m[1]): [int(n) for n in m[2].split()] for m in re.finditer(
        r"^;;\s*(\d+) conflicts:[ \t]*([\d \t]*)$", global_, re.M)}
    local_assignments = {int(a): int(b) for a, b in re.findall(
        r"^;; Register (\d+) in (\d+)\.", local, re.M)}
    dispositions = {}
    for match in re.finditer(r"^;; Register dispositions:\s*\n(.*?)(?=^;; Hard regs|^\(|\Z)",
                             global_, re.M | re.S):
        dispositions.update({int(a): int(b) for a, b in re.findall(r"(\d+) in (\d+)", match[1])})
    numbers = set(info) | set(local_assignments) | set(dispositions) | set(conflicts)
    numbers.update(n for order in orders for n in order)
    rows = []
    for pseudo in sorted(numbers):
        row = {"pseudo": pseudo, "refs": None, "live_length": None, "calls_crossed": None,
               "stats_source": None, "user_variable": None, **info.get(pseudo, {})}
        score = priority(row["refs"], row["live_length"])
        row.update(priority_inferred=({"numerator": score.numerator, "denominator": score.denominator}
                                      if score is not None else None),
                   hard_register=dispositions.get(pseudo, local_assignments.get(pseudo)),
                   assignment_source=("greg disposition" if pseudo in dispositions else
                                      "lreg local assignment" if pseudo in local_assignments else None),
                   conflicts=conflicts.get(pseudo))
        rows.append(row)
    unavailable = []
    if not local:
        unavailable.append("No lreg function section; call-crossing metadata is unavailable.")
    if not global_:
        unavailable.append("No greg function section; global allocation metadata is unavailable.")
    if not orders:
        unavailable.append("No global allocation queue was printed; allocation order is unavailable.")
    if not passes:
        unavailable.append("No verbose sorted candidate metadata was printed (-dG may be unsupported).")
    if not rows:
        unavailable.append("No pseudo-register metadata was printed for this function/profile.")
    return {"status": "ok" if rows else "unavailable", "pseudos": rows,
            "allocation_orders": orders, "candidate_passes": passes, "unavailable": unavailable,
            "interpretation": [
                "Refs, live lengths, call crossings, orders, assignments and conflicts are dumped fields.",
                "priority_inferred is floor_log2(refs)*refs/live_length, not a dumped allocator score.",
                "Missing fields are null, including a call-crossing count the compiler did not print.",
                "Conflict lists contain raw allocator register numbers, including hard regs and self.",
                "Dispositions follow reload; local assignments are identified separately."]}


def split_flags(flags: str) -> tuple[list[str], list[str]]:
    """Mirror compile_c's separate frontend/assembler handling, including SDK profiles."""
    return build.split_flags(flags)


def compile_script(source: Path, work: Path, flags: str, dumps: tuple[str, ...]) -> str:
    """The compile_c recipe in private scratch; never call compile_c or write its stamp."""
    compiler, assembler = split_flags(flags)
    root, tools = build.ROOT, build.COMPILER
    commands = ["set -e", "cd " + shlex.quote(str(work))]
    if flags.startswith("sdk"):
        sdk = build.SDK_COMPILER
        commands.append(shlex.join([str(sdk / "xgcc"), "-B" + str(sdk) + "/", "-S",
                                   *compiler, *dumps, "-I" + str(root / "include"),
                                   "-I" + str(sdk / "include"), "-I" + str(source.parent),
                                   "x.c", "-o", "x.s"]))
    else:
        commands.append(shlex.join([str(tools / "cpp"), "-I" + str(tools / "include"),
                                   "-I" + str(root / "include"), "-I" + str(source.parent),
                                   "x.c"]) + " > x.i")
        commands.append(shlex.join([str(tools / "cc1"), "-quiet", *compiler, *dumps,
                                   "x.i", "-o", "x.s"]))
    commands.append(shlex.join(["python3", str(build.SDATA_ALIASES), "x.s"]))
    commands.append(shlex.join([str(tools / "as"), *assembler, "-o", "x.o", "x.s"]))
    return "; ".join(commands)


def run_compile(source: Path, work: Path, flags: str, dumps: tuple[str, ...], tag: str) -> str:
    script = compile_script(source, work, flags, dumps)
    command = [*shlex.split(os.environ.get("RAC2_LINUX", "")), "bash", "-c", script]
    (work / (tag + ".command.txt")).write_text(shlex.join(command) + "\n")
    result = subprocess.run(command, capture_output=True, text=True, timeout=120)
    (work / (tag + ".log")).write_text(result.stdout + result.stderr)
    if dumps and re.search(r"(?:unrecogni[sz]ed|unknown|invalid).*?(?:option|debug)",
                           result.stderr, re.I):
        raise RuntimeError(f"compiler does not support the requested dump mode(s) "
                           f"{' '.join(dumps)}; see {work / (tag + '.log')}")
    if result.returncode:
        raise RuntimeError(f"{tag} compilation failed; see {work / (tag + '.log')}")
    return result.stderr


def diagnose(name: str) -> dict:
    tag_pattern = "|".join(re.escape(v["tag"]) for v in levels.VERSIONS.values() if v["tag"])
    if not re.fullmatch(rf"func_(?:(?:{tag_pattern})_)?(?:L\d\d_)?[0-9A-F]{{8}}", name):
        raise ValueError("expected a catalogue function name, e.g. func_002A77E0")
    programs = (["boot"] if any(n == name for n, _, _ in levels.read_boot_functions()) else [])
    for row in levels.read_catalogue():
        if row[0] == name:
            programs += [levels.level_dir(level) for level, _ in row[4]]
    if not programs:
        raise ValueError(f"{name} is in neither catalogue of {levels.VERSION}")
    source = check.source_of(name)
    if source is None:
        raise ValueError(f"no current C source defines {name}; allocator diagnostics are unavailable")
    flags = build.flags_for(source)
    parent = build.BUILD / "regalloc" / name
    parent.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix=levels.VERSION + "-", dir=parent)).resolve()
    shutil.copyfile(source, work / "x.c")
    source_hash = hashlib.sha256((work / "x.c").read_bytes()).hexdigest()
    run_compile(source, work, flags, (), "baseline")
    baseline = (work / "x.o").read_bytes()
    (work / "baseline.o").write_bytes(baseline)
    stderr = run_compile(source, work, flags, DUMP_FLAGS, "diagnostic")
    diagnostic = (work / "x.o").read_bytes()
    if baseline != diagnostic:
        raise RuntimeError(f"diagnostic unavailable: dump compilation changed object bytes; see {work}")
    dumps = {}
    for suffix in ("lreg", "greg", "loop", "gcse", "sched", "sched2"):
        paths = sorted(work.glob("x.*." + suffix))
        dumps[suffix] = "\n".join(p.read_text(errors="replace") for p in paths)
    result = parse_dumps(name, dumps["lreg"], dumps["greg"])
    result.update(function=name, version=levels.VERSION, programs=programs,
                  source=source.relative_to(build.ROOT).as_posix(), source_sha256=source_hash,
                  profile=flags, dump_flags=list(DUMP_FLAGS), work=str(work),
                  private_objects_equal=True, compiler_diagnostics=stderr,
                  object_sha256=hashlib.sha256(diagnostic).hexdigest(),
                  dump_files=sorted(p.name for p in work.glob("x.*") if p.suffix[1:] in dumps))
    (work / "diagnostic.json").write_text(json.dumps(result, indent=2) + "\n")
    return result


def hard_name(number: int | None) -> str:
    if number is None:
        return "?"
    gprs = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
            "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra").split()
    if 0 <= number < 32:
        return f"{number} (${gprs[number]})"
    if 32 <= number < 64:
        return f"{number} ($f{number - 32})"
    return str(number)


def display(result: dict) -> str:
    lines = [f"{result['function']}: {result['source']} ({result['version']})",
             "Profile: " + result["profile"], "Private dump/baseline objects: byte-identical",
             "Global allocation queues (actual dump order): " + str(result["allocation_orders"]),
             "Pseudo  refs  live  calls  inferred priority  hard register (dump disposition)"]
    for row in result["pseudos"]:
        score = row["priority_inferred"]
        value = str(Fraction(score["numerator"], score["denominator"])) if score else "?"
        show = lambda field: "?" if row[field] is None else str(row[field])
        lines.append(f"{row['pseudo']:6} {show('refs'):>5} {show('live_length'):>5} "
                     f"{show('calls_crossed'):>6} {value:>18}  {hard_name(row['hard_register'])}")
        if row["conflicts"] is not None:
            lines.append("       conflicts (raw): " + " ".join(map(str, row["conflicts"])))
    lines += result["interpretation"] + result["unavailable"]
    lines += ["Dumps/logs: " + result["work"], "Not a retail comparison or strict-build verdict."]
    return "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("function")
    parser.add_argument("--version", choices=levels.VERSIONS, default=os.environ.get("RAC2_VERSION", "us"))
    parser.add_argument("--json", action="store_true", help="print structured diagnostic fields")
    args = parser.parse_args(argv)
    levels.select(args.version)
    try:
        result = diagnose(args.function)
    except (ValueError, RuntimeError, OSError, subprocess.TimeoutExpired) as error:
        print(f"allocator diagnostic unavailable: {error}", file=sys.stderr)
        return 2
    print(json.dumps(result, indent=2) if args.json else display(result))
    return 0 if result["status"] == "ok" else 2


if __name__ == "__main__":
    sys.exit(main())
