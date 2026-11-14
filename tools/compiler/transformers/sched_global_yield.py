#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-global-yield: on a full sched1 tie, a hard-register set goes first.

When Haifa sched1 (before reload) reaches the final LUID tie-break between a single set of a
pseudo that is live in more than one basic block (REG_BASIC_BLOCK == REG_BLOCK_GLOBAL) and a
single set of a hard register, the hard-register set is scheduled first.

In func_L22_003A5018 (block 39, clock 1) the colour load into a cross-block pseudo and the
argument setup `a0 = text` tie on priority, weight, class and dependents; retail issues the
argument setup first and fills the call's delay slot with the load.

Forced on for every USA v1.01 C unit it changes 212 functions: an opt-in per-unit model,
landed under the owner's standard of 12 November 2026 (any generally worded opt-in rule that
makes a function match). Default compilation is unchanged.

Usage: sched_global_yield.py <gcc directory>
"""
import sys
from pathlib import Path

HELPER_OLD = "/* RAC2: nonzero if INSN is a register copy between two call argument registers.  */\n"
HELPER_NEW = """/* RAC2: nonzero if INSN is a single set of a pseudo live in more than one
   basic block (-frac2-sched-global-yield).  */
static int
rac2_sets_global_pseudo (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  return (GET_CODE (insn) == INSN && GET_CODE (pat) == SET
	  && GET_CODE (SET_DEST (pat)) == REG
	  && REGNO (SET_DEST (pat)) >= FIRST_PSEUDO_REGISTER
	  && REG_BASIC_BLOCK (REGNO (SET_DEST (pat))) == REG_BLOCK_GLOBAL);
}

/* RAC2: nonzero if INSN is a single set of a hard register.  */
static int
rac2_sets_hard_reg (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  return (GET_CODE (insn) == INSN && GET_CODE (pat) == SET
	  && GET_CODE (SET_DEST (pat)) == REG
	  && REGNO (SET_DEST (pat)) < FIRST_PSEUDO_REGISTER);
}

""" + HELPER_OLD

TIE_OLD = """  /* If insns are equally good, sort by INSN_LUID (original insn order),
"""
TIE_NEW = """  /* RAC2: -frac2-sched-global-yield: on a full sched1 tie, a set of a
     hard register goes before a set of a pseudo live beyond its block.  */
  if (flag_rac2_sched_global_yield && !reload_completed)
    {
      if (rac2_sets_global_pseudo (tmp) && rac2_sets_hard_reg (tmp2))
	return 1;
      if (rac2_sets_global_pseudo (tmp2) && rac2_sets_hard_reg (tmp))
	return -1;
    }

""" + TIE_OLD

DEFINITION_OLD = "int flag_rac2_sched_defer_const = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_defer_const = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, sched1 ties put a hard-register set first.  */\n"
                  "int flag_rac2_sched_global_yield = 0;\n")

OPTION_OLD = '  {"rac2-sched-defer-const", &flag_rac2_sched_defer_const, 1,\n'
OPTION_NEW = ('  {"rac2-sched-global-yield", &flag_rac2_sched_global_yield, 1,\n'
              '   "On a full sched1 tie, schedule a hard-register set before a cross-block pseudo set"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_defer_const;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: sched1 ties put a hard-register set first.  */\n"
                     "extern int flag_rac2_sched_global_yield;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_global_yield" in text for text in sources.values()):
        raise ValueError("sched-global-yield option already present")
    src = replace_once(sources[haifa], HELPER_OLD, HELPER_NEW, "haifa helpers")
    src = replace_once(src, TIE_OLD, TIE_NEW, "haifa tie-break")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
