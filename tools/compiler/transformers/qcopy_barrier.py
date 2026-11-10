#!/usr/bin/env python3
"""Add the opt-in -frac2-qcopy-barrier: the grouped quadword copy as a scheduling barrier.

Retail's grouped 16-byte copy, `lq $v0,0(rA)' ; `sq $v0,0(rB)' through register addresses,
is reproduced by -frac2-qcopy (qcopy_pattern.py), which deliberately adds no barrier, so
independent instructions move across the copy. In the original source the copy was most
likely an inline-asm macro, `asm volatile ("lq $2,0(%1) ; sq $2,0(%0)" ...)', which both
schedulers treat as a volatile asm (sched_analyze_2): the scheduler's register-use and
register-set lists are cleared, so nothing crosses it and the priorities change. A scratch
copy of the measured records with exactly that asm in place of the C assignment gives
retail's bytes; src/ allows no inline assembly.

This gives the rac2_qcopy insn, in gcc/haifa-sched.c's sched_analyze_insn (both
schedulers), the treatment -frac2-zero-ti-barrier (zero_ti_store_barrier.py) gives the
clear: a volatile asm's dependences, cost and unit. The insn is recognised by its shape,
a TImode SET from memory to memory beside a clobber of (reg:TI 2), which only the
rac2_qcopy pattern has. Instructions, operands, register allocation inputs and memory
flags are unchanged. The option only matters together with -frac2-qcopy, which is the
only source of that insn; it is off by default, enabled per compilation unit in
config/cflags.txt, and -fno-rac2-qcopy-barrier disables it again. Without it every unit
of src/ compiles to the same objects; forced on in the -frac2-qcopy units, it changes none
of them. Twelve functions (59 places) are the measured witnesses, each a unit of its own
with both switches. It is an inference from those records, not proof of the original
macro, and models only the schedulers' view of a volatile asm (jump2, for one, still
deletes a redundant move across the copy). tests/test_qcopy_barrier.py covers the
selector, the default/disabled equality and authored copies around calls, branches,
volatile accesses and neighbouring instructions. See docs/build/compiler-notes.md.

Usage: qcopy_barrier.py <gcc source directory>
"""
import sys
from pathlib import Path

HELPER_ANCHOR = "/* Analyze an INSN with pattern X to find all dependencies.  */\n"
HELPER = (
    "/* RAC2: retail's grouped quadword copy is scheduled as a volatile inline-asm macro,\n"
    "   `lq $2,0(%1); sq $2,0(%0)', would be: a barrier for both schedulers.  The C writes it\n"
    "   as a TImode assignment, which -frac2-qcopy expands to the rac2_qcopy insn: a TImode\n"
    "   SET from memory to memory beside a clobber of (reg:TI 2).  */\n"
    "\n"
    "static int\n"
    "rac2_qcopy_barrier_p (x)\n"
    "     rtx x;\n"
    "{\n"
    "  rtx set, clobber;\n"
    "\n"
    "  if (GET_CODE (x) != PARALLEL || XVECLEN (x, 0) != 2)\n"
    "    return 0;\n"
    "  set = XVECEXP (x, 0, 0);\n"
    "  clobber = XVECEXP (x, 0, 1);\n"
    "  return (GET_CODE (set) == SET\n"
    "\t  && GET_CODE (SET_DEST (set)) == MEM\n"
    "\t  && GET_MODE (SET_DEST (set)) == TImode\n"
    "\t  && GET_CODE (SET_SRC (set)) == MEM\n"
    "\t  && GET_MODE (SET_SRC (set)) == TImode\n"
    "\t  && GET_CODE (clobber) == CLOBBER\n"
    "\t  && GET_CODE (XEXP (clobber, 0)) == REG\n"
    "\t  && GET_MODE (XEXP (clobber, 0)) == TImode\n"
    "\t  && REGNO (XEXP (clobber, 0)) == 2);\n"
    "}\n"
    "\n")

CONDITION_OLD = "  if (flag_rac2_zero_ti_barrier && rac2_zero_ti_barrier_p (x, insn))\n"
CONDITION_NEW = ("  if ((flag_rac2_zero_ti_barrier && rac2_zero_ti_barrier_p (x, insn))\n"
                 "      || (flag_rac2_qcopy_barrier && rac2_qcopy_barrier_p (x)))\n")

TABLE_ANCHOR = '  {"rac2-zero-ti-barrier", &flag_rac2_zero_ti_barrier, 1,'
TABLE_ENTRY = ('  {"rac2-qcopy-barrier", &flag_rac2_qcopy_barrier, 1,\n'
               '   "Model the RAC2 quadword-copy scheduling barrier"},\n')


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    sched, top, flags = root / "haifa-sched.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (sched, top, flags)}
    if any("flag_rac2_qcopy_barrier" in text for text in sources.values()):
        raise ValueError("qcopy-barrier option already present")
    scheduler = replace_once(sources[sched], HELPER_ANCHOR, HELPER + HELPER_ANCHOR, "selector")
    scheduler = replace_once(scheduler, CONDITION_OLD, CONDITION_NEW, "barrier condition")
    driver = replace_once(sources[top], "int flag_rac2_qcopy = 0;\n",
                          "int flag_rac2_qcopy = 0;\n"
                          "/* Opt-in model of the game's inferred quadword-copy macro. */\n"
                          "int flag_rac2_qcopy_barrier = 0;\n", "option definition")
    driver = replace_once(driver, TABLE_ANCHOR, TABLE_ENTRY + TABLE_ANCHOR, "option table")
    declarations = replace_once(sources[flags], "extern int flag_rac2_qcopy;\n",
                                "extern int flag_rac2_qcopy;\n"
                                "extern int flag_rac2_qcopy_barrier;\n", "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((sched, scheduler), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
