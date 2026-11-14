#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-clear-holds-store: a quadword clear holds the store slot for its cycle.

Before reload, once Haifa issues a quadword clear (a TImode store of const 0, the
rac2_const0_ti_store_p form) in a cycle, no further insn that stores to memory issues in that
same cycle: it gets cost 1 and stays on the ready list. Loads, ALU and FP insns may still take
the second issue slot.

In func_L04_0040DCA8 (block 2, t26) stock sched1 pairs clear 321 with store 344, so five stores
land in t26-t30 before h is ready; with the rule the clear pairs with a copy, and the h stores
issue ahead of c1.w as retail.

Forced on for every USA v1.01 C unit it changes 5 functions: an opt-in per-unit model, landed
under the owner's standard of 12 November 2026. Default compilation is unchanged.

Usage: sched_clear_holds_store.py <gcc directory>
"""
import sys
from pathlib import Path

DECL_OLD = "  int can_issue_more;\n"
DECL_NEW = "  int can_issue_more;\n  int rac2_clear_issued = 0;\n"

RESET_OLD = "      rac2_cycle_prev = 0;\n"
RESET_NEW = "      rac2_cycle_prev = 0;\n      rac2_clear_issued = 0;\n"

HOLD_OLD = "\t  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);\n\n"
HOLD_NEW = HOLD_OLD + """\t  /* RAC2: -frac2-sched-clear-holds-store: before reload a quadword clear
\t     holds the store slot for its cycle.  */
\t  if (flag_rac2_sched_clear_holds_store && cost == 0 && rac2_clear_issued
\t      && ! reload_completed
\t      && GET_CODE (PATTERN (insn)) == SET
\t      && GET_CODE (SET_DEST (PATTERN (insn))) == MEM)
\t    cost = 1;

"""

ISSUED_OLD = "\t      sched_n_insns++;\n"
ISSUED_NEW = ISSUED_OLD + """\t      if (flag_rac2_sched_clear_holds_store && ! reload_completed
\t\t  && rac2_const0_ti_store_p (PATTERN (insn)))
\t\trac2_clear_issued = 1;
"""

DEFINITION_OLD = "int flag_rac2_sched_store_clobbered_first = 0;\n"
DEFINITION_NEW = (DEFINITION_OLD + "\n/* RAC2: opt-in, a quadword clear holds the store slot of its cycle.  */\n"
                  "int flag_rac2_sched_clear_holds_store = 0;\n")
OPTION_OLD = '  {"rac2-sched-store-clobbered-first", &flag_rac2_sched_store_clobbered_first, 1,\n'
OPTION_NEW = ('  {"rac2-sched-clear-holds-store", &flag_rac2_sched_clear_holds_store, 1,\n'
              '   "No store issues after a quadword clear in the same sched1 cycle"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_sched_store_clobbered_first;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: a quadword clear holds the store slot of its cycle.  */\n"
                   "extern int flag_rac2_sched_clear_holds_store;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_clear_holds_store" in text for text in sources.values()):
        raise ValueError("sched-clear-holds-store option already present")
    src = replace_once(sources[haifa], DECL_OLD, DECL_NEW, "haifa declaration")
    src = replace_once(src, RESET_OLD, RESET_NEW, "haifa cycle reset")
    src = replace_once(src, HOLD_OLD, HOLD_NEW, "haifa hold test")
    src = replace_once(src, ISSUED_OLD, ISSUED_NEW, "haifa issued insn")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
