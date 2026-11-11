#!/usr/bin/env python3
"""Add the opt-in -frac2-delay-no-split-hi: keep split high-part address loads (lui %hi) out of thread delay slots.

When reorg.c:fill_slots_from_thread searches a fall-through or target thread to fill
the delay slot of a conditional branch, it pulls an instruction into a non-annulled slot
if the instruction does not trap and does not set any resource needed at the opposite
thread. If the opposite thread does not read a register before an epilogue or overwrite,
stock GCC may pull the high part of an address calculation (`lui %hi(sym)`, RTL code HIGH)
into the delay slot, leaving the low part (`addiu %lo(sym)`) behind in the branch body.
If the branch is taken, the register is left holding an incomplete half-address.

In retail's compiler, high-part address loads (`(high:SI ...)`) are not pulled into
conditional delay slots from threads (witness: func_002BB100).

With -frac2-delay-no-split-hi, fill_slots_from_thread rejects instructions with HIGH
sources for non-annulled delay slots of conditional branches.

Usage: delay_no_split_hi.py <gcc/reorg.c or gcc directory>
"""
import sys
from pathlib import Path

PREDICATE_OLD = """static rtx
fill_slots_from_thread (insn, condition, thread, opposite_thread, likely,"""

PREDICATE_NEW = """/* RAC2: nonzero if INSN sets a register to the high part of an address (lui %hi).  */

static int
rac2_high_part_p (insn)
     rtx insn;
{
  rtx set = single_set (insn);
  return (set != 0 && GET_CODE (SET_SRC (set)) == HIGH);
}

static rtx
fill_slots_from_thread (insn, condition, thread, opposite_thread, likely,"""

CHECK_OLD = """	  /* There are two ways we can win:  If TRIAL doesn't set anything
	     needed at the opposite thread and can't trap, or if it can
	     go into an annulled delay slot.  */
	  if (!must_annul
	      && (condition == const_true_rtx
	          || (! insn_sets_resource_p (trial, &opposite_needed, 1)
		      && ! may_trap_p (pat))))"""

CHECK_NEW = """	  /* There are two ways we can win:  If TRIAL doesn't set anything
	     needed at the opposite thread and can't trap, or if it can
	     go into an annulled delay slot.  */
	  if (!must_annul
	      && (condition == const_true_rtx
	          || (! insn_sets_resource_p (trial, &opposite_needed, 1)
		      && ! may_trap_p (pat)
		      && ! (flag_rac2_delay_no_split_hi
			    && rac2_high_part_p (trial)))))"""

DEFINITION_OLD = "int flag_rac2_caller_reg_order = 0;\n"
DEFINITION_NEW = ("int flag_rac2_caller_reg_order = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, keep split high-part loads out of thread delay slots.  */\n"
                  "int flag_rac2_delay_no_split_hi = 0;\n")

OPTION_OLD = '  {"rac2-caller-reg-order", &flag_rac2_caller_reg_order, 1,\n'
OPTION_NEW = ('  {"rac2-delay-no-split-hi", &flag_rac2_delay_no_split_hi, 1,\n'
              '   "Keep split high-part address loads out of conditional delay slots"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_caller_reg_order;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: keep split high-part loads out of conditional delay slots.  */\n"
                     "extern int flag_rac2_delay_no_split_hi;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    if target.is_dir():
        reorg, top, flags = target / "reorg.c", target / "toplev.c", target / "flags.h"
    else:
        reorg, top, flags = target, target.with_name("toplev.c"), target.with_name("flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (reorg, top, flags)}
    if any("flag_rac2_delay_no_split_hi" in text for text in sources.values()):
        raise ValueError("delay-no-split-hi option already present")
    reorg_src = replace_once(sources[reorg], PREDICATE_OLD, PREDICATE_NEW, "reorg predicate")
    reorg_src = replace_once(reorg_src, CHECK_OLD, CHECK_NEW, "fill_slots_from_thread check")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((reorg, reorg_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
