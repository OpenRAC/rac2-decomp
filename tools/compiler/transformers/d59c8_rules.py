#!/usr/bin/env python3
"""Add two opt-in sched2 switches for func_002859C8.

- -frac2-sched2-fp-load-holds-store (haifa-sched.c schedule_block, after reload): when a ready
  store gets hazard cost 1 in a cycle where an FP load has issued and no store has, no insn of
  lower priority than that store issues in that cycle (cases 9/10 leave the ALU slot empty).
- -frac2-sched2-stack-store-first (rank_for_schedule, after the dependent count, after reload):
  a store of a register to a stack-pointer address goes before a register copy into a call
  argument register (case 11).

Forced on they change 474 and 198 functions: opt-in per-unit models under the owner's standard
of 12 November 2026. Default compilation is unchanged.

Usage: d59c8_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'haifa-sched.c': [('\n/* Data structures for the computation of data dependences in a regions.  We', '/* RAC2 prototypes (env-gated here; to become -frac2-sched2-fp-load-holds-store\n   and -frac2-sched2-stack-store-first).  */\n\n/* Data structures for the computation of data dependences in a regions.  We'), ('  val = depend_count2 - depend_count1;\n  if (val)\n    return val;\n  \n  /* RAC2: -frac2-sched-store-offset: prefer lower displacement for memory stores\n     to the same base register.  */\n', '  val = depend_count2 - depend_count1;\n  if (val)\n    return val;\n\n  /* RAC2: -frac2-sched2-stack-store-first: after reload, on a tie this far,\n     a store of a register to a stack-pointer address goes before a\n     register copy into a call argument register.  */\n  if (flag_rac2_sched2_stack_store_first && reload_completed\n      && GET_CODE (PATTERN (tmp)) == SET && GET_CODE (PATTERN (tmp2)) == SET)\n    {\n      rtx p1 = PATTERN (tmp), p2 = PATTERN (tmp2);\n      int s1 = (GET_CODE (SET_DEST (p1)) == MEM && GET_CODE (SET_SRC (p1)) == REG\n\t\t&& reg_mentioned_p (stack_pointer_rtx, XEXP (SET_DEST (p1), 0)));\n      int s2 = (GET_CODE (SET_DEST (p2)) == MEM && GET_CODE (SET_SRC (p2)) == REG\n\t\t&& reg_mentioned_p (stack_pointer_rtx, XEXP (SET_DEST (p2), 0)));\n      int c1 = (GET_CODE (SET_DEST (p1)) == REG && GET_CODE (SET_SRC (p1)) == REG\n\t\t&& FUNCTION_ARG_REGNO_P (REGNO (SET_DEST (p1))));\n      int c2 = (GET_CODE (SET_DEST (p2)) == REG && GET_CODE (SET_SRC (p2)) == REG\n\t\t&& FUNCTION_ARG_REGNO_P (REGNO (SET_DEST (p2))));\n\n      if (s1 && c2)\n\treturn -1;\n      if (s2 && c1)\n\treturn 1;\n    }\n  \n  /* RAC2: -frac2-sched-store-offset: prefer lower displacement for memory stores\n     to the same base register.  */\n'), ('\n  /* flow block of this bb */', '  int rac2_hold_priority = 0, rac2_store_issued = 0, rac2_fp_load_issued = 0;\n\n  /* flow block of this bb */'), ('      for (i = n_ready - 1; i >= 0 && can_issue_more; i--)\n\t{\n\t  rtx insn = ready[i];\n\t  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);\n', '      rac2_hold_priority = 0;\n      rac2_store_issued = 0;\n      rac2_fp_load_issued = 0;\n      for (i = n_ready - 1; i >= 0 && can_issue_more; i--)\n\t{\n\t  rtx insn = ready[i];\n\t  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);\n\n\t  /* RAC2: -frac2-sched2-fp-load-holds-store: after reload, when a\n\t     ready store cannot issue in a cycle whose memory slot went to a\n\t     floating-point load (from memory or of a constant), no insn of\n\t     lower priority than that store issues in the cycle.  */\n\t  if (flag_rac2_sched2_fp_load_holds_store && reload_completed)\n\t    {\n\t      rtx pat = PATTERN (insn);\n\n\t      if (INSN_PRIORITY (insn) < rac2_hold_priority)\n\t\tcontinue;\n\t      if (GET_CODE (pat) == SET && GET_CODE (SET_DEST (pat)) == MEM)\n\t\t{\n\t\t  if (cost == 1 && rac2_fp_load_issued && ! rac2_store_issued)\n\t\t    {\n\t\t      rac2_hold_priority = INSN_PRIORITY (insn);\n\t\t      continue;\n\t\t    }\n\t\t  if (cost == 0)\n\t\t    rac2_store_issued = 1;\n\t\t}\n\t      else if (cost == 0 && GET_CODE (pat) == SET\n\t\t       && GET_CODE (SET_DEST (pat)) == REG\n\t\t       && GET_MODE_CLASS (GET_MODE (SET_DEST (pat))) == MODE_FLOAT\n\t\t       && (GET_CODE (SET_SRC (pat)) == MEM\n\t\t\t   || GET_CODE (SET_SRC (pat)) == CONST_DOUBLE))\n\t\trac2_fp_load_issued = 1;\n\t    }\n')]}

DEFINITION_OLD = "int flag_rac2_sched_defer_const_after_death = 0;\n"
DEFINITION_NEW = DEFINITION_OLD + 'int flag_rac2_sched2_fp_load_holds_store = 0;\nint flag_rac2_sched2_stack_store_first = 0;\n'
OPTION_OLD = '  {"rac2-sched-defer-const-after-death", &flag_rac2_sched_defer_const_after_death, 1,\n'
OPTION_NEW = '  {"rac2-sched2-fp-load-holds-store", &flag_rac2_sched2_fp_load_holds_store, 1,\n   "After an FP load, a blocked store holds lower-priority insns for the cycle"},\n  {"rac2-sched2-stack-store-first", &flag_rac2_sched2_stack_store_first, 1,\n   "On a sched2 tie, a stack store goes before an argument-register copy"},\n' + OPTION_OLD
DECLARATION_OLD = "extern int flag_rac2_sched_defer_const_after_death;\n"
DECLARATION_NEW = DECLARATION_OLD + 'extern int flag_rac2_sched2_fp_load_holds_store;\nextern int flag_rac2_sched2_stack_store_first;\n'


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = list(HUNKS) + ["toplev.c", "flags.h"]
    s = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    if any("flag_rac2_sched2_fp_load_holds_store" in text for text in s.values()):
        raise ValueError("d59c8_rules options already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            s[name] = replace_once(s[name], old, new, f"{name} hunk {k}")
    s["toplev.c"] = replace_once(s["toplev.c"], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    s["toplev.c"] = replace_once(s["toplev.c"], OPTION_OLD, OPTION_NEW, "option table")
    s["flags.h"] = replace_once(s["flags.h"], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for name in names:
        (gcc / name).write_text(s[name], encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
