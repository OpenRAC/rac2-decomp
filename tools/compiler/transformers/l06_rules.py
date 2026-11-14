#!/usr/bin/env python3
"""Add four opt-in switches for func_L06_004587E8 (gcse PRE, cse, two sched2 tie-breaks).

- -frac2-pre-call-test (gcse.c insert_insn_end_bb): a block ending in a call, a copy of the hard
  return register and a conditional jump on that copy is treated as ending in the call, so PRE
  inserts before the call's first parameter load.
- -frac2-cse-noskip-store (cse.c cse_end_of_basic_block): cse does not branch around (skip) a
  block that contains a memory store.
- -frac2-sched-retstore (haifa-sched.c rank_for_schedule, before the dependent count): after
  reload, on equal priority and class, a memory store of an FP function-value register goes
  before a load of a call argument register.
- -frac2-sched-stackaddr (haifa-sched.c, final tie before LUID): on a full sched2 tie,
  `reg = $sp + offset` goes before `reg = const_int`.

In func_L06_004587E8 they place case 0's PRE copy before insn 90, order its swc1 stores, keep the
i<<1 copy, and put &axis before 0x180. Forced on alone they change 254, 737, 412 and 266
functions: opt-in per-unit models under the owner's standard of 12 November 2026. Default
compilation is unchanged.

Usage: l06_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'gcse.c': [('\n  pat = process_insert_insn (expr, bb);\n\n  /* If the last insn is a jump, insert EXPR in front [taking care to\n     handle cc0, etc. properly].  */\n', "\n  pat = process_insert_insn (expr, bb);\n\n  /* RAC2: RAC2_PRE_CALLTEST (-frac2-pre-before-call-test): a block ending\n     in a conditional jump on the value of a call (call; copy of its hard\n     return register; jump on that copy) is treated as ending in the call:\n     PRE puts the expression before the call's first parameter load, not\n     between the call and the test of its value.  */\n  if (pre && flag_rac2_pre_call_test && GET_CODE (insn) == JUMP_INSN\n      && condjump_p (insn) && ! simplejump_p (insn))\n    {\n      rtx copy = prev_nonnote_insn (insn);\n      rtx call = copy ? prev_nonnote_insn (copy) : NULL_RTX;\n      rtx cset = (copy && GET_CODE (copy) == INSN) ? single_set (copy) : NULL_RTX;\n\n      if (cset && call && GET_CODE (call) == CALL_INSN\n\t  && copy != BLOCK_HEAD (bb) && call != BLOCK_HEAD (bb)\n\t  && GET_CODE (SET_SRC (cset)) == REG\n\t  && REGNO (SET_SRC (cset)) < FIRST_PSEUDO_REGISTER\n\t  && GET_CODE (SET_DEST (cset)) == REG\n\t  && reg_mentioned_p (SET_DEST (cset), PATTERN (insn))\n\t  && reg_set_p (SET_SRC (cset), call))\n\tinsn = call;\n    }\n\n  /* If the last insn is a jump, insert EXPR in front [taking care to\n     handle cc0, etc. properly].  */\n")], 'cse.c': [('\t      for (tmp = NEXT_INSN (p); tmp && tmp != q; tmp = NEXT_INSN (tmp))\n\t\tif (GET_CODE (tmp) == CODE_LABEL)\n\t\t  break;\n\t      \n\t      if (tmp == q)\n\t\t{\n', '\t      for (tmp = NEXT_INSN (p); tmp && tmp != q; tmp = NEXT_INSN (tmp))\n\t\tif (GET_CODE (tmp) == CODE_LABEL)\n\t\t  break;\n\n\t      /* RAC2: RAC2_CSE_NOSKIP_STORE (-frac2-cse-no-skip-stores): cse\n\t\t does not branch around a block that stores to memory; the\n\t\t path ends at the jump.  */\n\t      if (tmp == q && flag_rac2_cse_noskip_store)\n\t\t{\n\t\t  rtx t2, set;\n\n\t\t  for (t2 = NEXT_INSN (p); t2; t2 = NEXT_INSN (t2))\n\t\t    {\n\t\t      if (GET_CODE (t2) == INSN\n\t\t\t  && (set = single_set (t2)) != 0\n\t\t\t  && GET_CODE (SET_DEST (set)) == MEM)\n\t\t\ttmp = 0;\n\t\t      if (t2 == q)\n\t\t\tbreak;\n\t\t    }\n\t\t}\n\t      \n\t      if (tmp == q)\n\t\t{\n')], 'haifa-sched.c': [('\treturn val;\n    }\n\n  /* Prefer the insn which has more later insns that depend on it. \n     This gives the scheduler more freedom when scheduling later\n     instructions at the expense of added register pressure.  */\n', "\treturn val;\n    }\n\n  /* RAC2: RAC2_SCHED_RETSTORE (-frac2-sched-fp-result-store-first): after\n     reload, on equal priority and class, the memory store of a\n     floating-point function-value register (the saving of a call's\n     result) goes before the load of a call argument register, ahead of\n     the dependent count.  */\n  if (flag_rac2_sched_retstore && reload_completed)\n    {\n      rtx s1 = single_set (tmp), s2 = single_set (tmp2);\n      int r1 = (s1 && GET_CODE (SET_DEST (s1)) == MEM\n\t\t&& GET_CODE (SET_SRC (s1)) == REG\n\t\t&& REGNO (SET_SRC (s1)) < FIRST_PSEUDO_REGISTER\n\t\t&& FP_REG_P (REGNO (SET_SRC (s1)))\n\t\t&& FUNCTION_VALUE_REGNO_P (REGNO (SET_SRC (s1))));\n      int r2 = (s2 && GET_CODE (SET_DEST (s2)) == MEM\n\t\t&& GET_CODE (SET_SRC (s2)) == REG\n\t\t&& REGNO (SET_SRC (s2)) < FIRST_PSEUDO_REGISTER\n\t\t&& FP_REG_P (REGNO (SET_SRC (s2)))\n\t\t&& FUNCTION_VALUE_REGNO_P (REGNO (SET_SRC (s2))));\n      int g1 = (s1 && GET_CODE (SET_DEST (s1)) == REG\n\t\t&& REGNO (SET_DEST (s1)) < FIRST_PSEUDO_REGISTER\n\t\t&& FUNCTION_ARG_REGNO_P (REGNO (SET_DEST (s1))));\n      int g2 = (s2 && GET_CODE (SET_DEST (s2)) == REG\n\t\t&& REGNO (SET_DEST (s2)) < FIRST_PSEUDO_REGISTER\n\t\t&& FUNCTION_ARG_REGNO_P (REGNO (SET_DEST (s2))));\n      if (r1 && g2)\n\treturn -1;\n      if (r2 && g1)\n\treturn 1;\n    }\n\n  /* Prefer the insn which has more later insns that depend on it. \n     This gives the scheduler more freedom when scheduling later\n     instructions at the expense of added register pressure.  */\n"), ('  /* If insns are equally good, sort by INSN_LUID (original insn order),\n', '  /* RAC2: RAC2_SCHED_STACKADDR (-frac2-sched-stack-addr-before-const): on\n     a full sched2 tie, a stack address computation (reg = $sp + offset)\n     goes before an integer constant load (reg = const_int).  */\n  if (flag_rac2_sched_stackaddr && reload_completed)\n    {\n      HOST_WIDE_INT off;\n      rtx s1 = single_set (tmp), s2 = single_set (tmp2);\n      int a1 = rac2_is_sp_addend (tmp, &off);\n      int a2 = rac2_is_sp_addend (tmp2, &off);\n      int c1 = (s1 && GET_CODE (SET_DEST (s1)) == REG\n\t\t&& GET_CODE (SET_SRC (s1)) == CONST_INT);\n      int c2 = (s2 && GET_CODE (SET_DEST (s2)) == REG\n\t\t&& GET_CODE (SET_SRC (s2)) == CONST_INT);\n      if (a1 && c2)\n\treturn -1;\n      if (a2 && c1)\n\treturn 1;\n    }\n\n  /* If insns are equally good, sort by INSN_LUID (original insn order),\n')]}

DEFINITION_OLD = "int flag_rac2_sched2_barrier_hold = 0;\n"
DEFINITION_NEW = (DEFINITION_OLD + "\n/* RAC2: opt-in rules for func_L06_004587E8.  */\n"
                  "int flag_rac2_pre_call_test = 0;\n"
                  "int flag_rac2_cse_noskip_store = 0;\n"
                  "int flag_rac2_sched_retstore = 0;\n"
                  "int flag_rac2_sched_stackaddr = 0;\n")
OPTION_OLD = '  {"rac2-sched2-barrier-hold", &flag_rac2_sched2_barrier_hold, 1,\n'
OPTION_NEW = ('  {"rac2-pre-call-test", &flag_rac2_pre_call_test, 1,\n'
              '   "PRE treats a call followed by a test of its result as the block end"},\n'
              '  {"rac2-cse-noskip-store", &flag_rac2_cse_noskip_store, 1,\n'
              '   "cse does not skip blocks that contain a memory store"},\n'
              '  {"rac2-sched-retstore", &flag_rac2_sched_retstore, 1,\n'
              '   "sched2 stores an FP return value before loading an argument register"},\n'
              '  {"rac2-sched-stackaddr", &flag_rac2_sched_stackaddr, 1,\n'
              '   "On a full sched2 tie, a stack address goes before a constant"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_sched2_barrier_hold;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: opt-in rules for func_L06_004587E8.  */\n"
                   "extern int flag_rac2_pre_call_test;\n"
                   "extern int flag_rac2_cse_noskip_store;\n"
                   "extern int flag_rac2_sched_retstore;\n"
                   "extern int flag_rac2_sched_stackaddr;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = list(HUNKS) + ["toplev.c", "flags.h"]
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    if any("flag_rac2_sched_stackaddr" in text for text in sources.values()):
        raise ValueError("l06 rules already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    sources["toplev.c"] = replace_once(sources["toplev.c"], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    sources["toplev.c"] = replace_once(sources["toplev.c"], OPTION_OLD, OPTION_NEW, "option table")
    sources["flags.h"] = replace_once(sources["flags.h"], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for name in names:
        (gcc / name).write_text(sources[name], encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
