#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-defer-const: a constant load waits after a dying store.

In Haifa sched1 (before reload), a constant load (the set of a pseudo to a CONST_INT) is not
issued in the slot directly after a store, in the same cycle, when that store is the single use
of a pseudo with one set (the store ends the pseudo's life). The constant load waits one cycle,
once per insn. local-alloc pads a quantity's life by one insn at each end, so a birth issued
beside such a death conflicts with the register that has just died.

In func_00285030 (block 3, cycle 6) the store of t[1] = 0xE kills r171 and the lone constant
r181 = 0x8000 takes the free slot beside it; retail's allocation follows when that constant
issues in cycle 7, so r181 and r171 share $6 and r172/r173 tie as retail.

Forced on for every USA v1.01 C unit it changes 163 functions: an opt-in per-unit model,
landed under the owner's standard of 12 November 2026 (any generally worded opt-in rule that
makes a function match). Default compilation is unchanged.

Usage: sched_defer_const.py <gcc directory>
"""
import sys
from pathlib import Path

HELPER_OLD = "/* RAC2: nonzero if INSN is a register copy between two call argument registers.  */\n"
HELPER_NEW = """/* RAC2: -frac2-sched-defer-const state, reset per scheduled block.  */
static char *rac2_deferred;
static int rac2_deferred_size;
static rtx rac2_cycle_prev;

/* RAC2: nonzero if INSN stores a pseudo that has one set and one use.  */
static int
rac2_single_use_store_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  rtx src;
  if (GET_CODE (insn) != INSN || GET_CODE (pat) != SET
      || GET_CODE (SET_DEST (pat)) != MEM)
    return 0;
  src = SET_SRC (pat);
  return (GET_CODE (src) == REG && REGNO (src) >= FIRST_PSEUDO_REGISTER
	  && REG_N_SETS (REGNO (src)) == 1 && REG_N_REFS (REGNO (src)) == 2);
}

/* RAC2: nonzero if INSN sets a pseudo to a constant.  */
static int
rac2_const_load_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  return (GET_CODE (insn) == INSN && GET_CODE (pat) == SET
	  && GET_CODE (SET_DEST (pat)) == REG
	  && REGNO (SET_DEST (pat)) >= FIRST_PSEUDO_REGISTER
	  && GET_CODE (SET_SRC (pat)) == CONST_INT);
}

""" + HELPER_OLD

INIT_OLD = "  /* loop until all the insns in BB are scheduled.  */\n"
INIT_NEW = """  if (flag_rac2_sched_defer_const)
    {
      if (rac2_deferred)
	free (rac2_deferred);
      rac2_deferred_size = get_max_uid () + 1;
      rac2_deferred = (char *) xcalloc (rac2_deferred_size, 1);
    }

""" + INIT_OLD

ISSUE_OLD = """      can_issue_more = issue_rate;
      for (i = n_ready - 1; i >= 0 && can_issue_more; i--)
	{
	  rtx insn = ready[i];
	  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);

"""
ISSUE_NEW = """      can_issue_more = issue_rate;
      rac2_cycle_prev = 0;
      for (i = n_ready - 1; i >= 0 && can_issue_more; i--)
	{
	  rtx insn = ready[i];
	  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);

	  /* RAC2: -frac2-sched-defer-const: before reload, a constant load is
	     not issued right after a same-cycle store that ends a single-use
	     pseudo; it waits one cycle, once.  */
	  if (flag_rac2_sched_defer_const && cost == 0 && !reload_completed
	      && rac2_cycle_prev != 0
	      && rac2_single_use_store_p (rac2_cycle_prev)
	      && INSN_UID (insn) < rac2_deferred_size
	      && ! rac2_deferred[INSN_UID (insn)]
	      && rac2_const_load_p (insn))
	    {
	      rac2_deferred[INSN_UID (insn)] = 1;
	      cost = 1;
	    }

"""

ISSUED_OLD = """	  else if (cost == 0)
	    {
	      /* an interblock motion? */
"""
ISSUED_NEW = """	  else if (cost == 0)
	    {
	      rac2_cycle_prev = insn;
	      /* an interblock motion? */
"""

DEFINITION_OLD = "int flag_rac2_fix_scratch_reuse = 0;\n"
DEFINITION_NEW = ("int flag_rac2_fix_scratch_reuse = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, sched1 defers a constant load after a dying store.  */\n"
                  "int flag_rac2_sched_defer_const = 0;\n")

OPTION_OLD = '  {"rac2-fix-scratch-reuse", &flag_rac2_fix_scratch_reuse, 1,\n'
OPTION_NEW = ('  {"rac2-sched-defer-const", &flag_rac2_sched_defer_const, 1,\n'
              '   "Defer a constant load one cycle after a store that ends a single-use pseudo"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_fix_scratch_reuse;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: sched1 defers a constant load after a dying store.  */\n"
                     "extern int flag_rac2_sched_defer_const;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_defer_const" in text for text in sources.values()):
        raise ValueError("sched-defer-const option already present")
    src = replace_once(sources[haifa], HELPER_OLD, HELPER_NEW, "haifa helpers")
    src = replace_once(src, INIT_OLD, INIT_NEW, "haifa block init")
    src = replace_once(src, ISSUE_OLD, ISSUE_NEW, "haifa issue test")
    src = replace_once(src, ISSUED_OLD, ISSUED_NEW, "haifa issued insn")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
