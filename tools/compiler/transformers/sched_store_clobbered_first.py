#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-store-clobbered-first: after reload, call-clobbered sources store first.

When Haifa sched2 reaches the final LUID tie-break between two SImode stores of hard registers
to memory, the store whose source register is call-clobbered goes first, the store of a
call-saved register after it.

In func_0034B2C8 two PRE copies are spilled before a call: `sw $v1,0x30($sp)` and
`sw $s5,0x48($sp)`. Stock order follows PRE's expression index (the $s5 store first); retail
stores $v1 first and lets reorg put the $s5 store in the call's delay slot.

Forced on for every USA v1.01 C unit it changes 91 functions: an opt-in per-unit model, landed
under the owner's standard of 12 November 2026 (any generally worded opt-in rule that makes a
function match). Default compilation is unchanged.

Usage: sched_store_clobbered_first.py <gcc directory>
"""
import sys
from pathlib import Path

TIE_OLD = """  /* If insns are equally good, sort by INSN_LUID (original insn order),
"""
TIE_NEW = """  /* RAC2: -frac2-sched-store-clobbered-first: on a full sched2 tie between
     two SImode stores of hard registers, the call-clobbered source first.  */
  if (flag_rac2_sched_store_clobbered_first && reload_completed)
    {
      rtx s1 = single_set (tmp), s2 = single_set (tmp2);
      if (s1 && s2
	  && GET_CODE (SET_DEST (s1)) == MEM && GET_CODE (SET_DEST (s2)) == MEM
	  && GET_MODE (SET_DEST (s1)) == SImode && GET_MODE (SET_DEST (s2)) == SImode
	  && GET_CODE (SET_SRC (s1)) == REG && GET_CODE (SET_SRC (s2)) == REG
	  && REGNO (SET_SRC (s1)) < FIRST_PSEUDO_REGISTER
	  && REGNO (SET_SRC (s2)) < FIRST_PSEUDO_REGISTER
	  && call_used_regs[REGNO (SET_SRC (s1))] != call_used_regs[REGNO (SET_SRC (s2))])
	return call_used_regs[REGNO (SET_SRC (s1))] ? -1 : 1;
    }

""" + TIE_OLD

DEFINITION_OLD = "int flag_rac2_sched_global_yield = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_global_yield = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, sched2 ties store call-clobbered sources first.  */\n"
                  "int flag_rac2_sched_store_clobbered_first = 0;\n")

OPTION_OLD = '  {"rac2-sched-global-yield", &flag_rac2_sched_global_yield, 1,\n'
OPTION_NEW = ('  {"rac2-sched-store-clobbered-first", &flag_rac2_sched_store_clobbered_first, 1,\n'
              '   "On a full sched2 tie, store a call-clobbered register before a call-saved one"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_global_yield;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: sched2 ties store call-clobbered sources first.  */\n"
                     "extern int flag_rac2_sched_store_clobbered_first;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_store_clobbered_first" in text for text in sources.values()):
        raise ValueError("sched-store-clobbered-first option already present")
    src = replace_once(sources[haifa], TIE_OLD, TIE_NEW, "haifa tie-break")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
