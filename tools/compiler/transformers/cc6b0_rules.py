#!/usr/bin/env python3
"""Add four opt-in life-analysis, register-allocation and scheduling rules, first needed by
func_002CC6B0.

-frac2-flow2-trap-mem: after reload, a trap insn (TRAP_IF) ends dead-store tracking in life
analysis, so a store before the trap is not deleted as overwritten by a store after it.
-frac2-la-multi-death-locals: local-alloc also allocates a block-local user variable that dies
more than once (stock local-alloc takes only pseudos with exactly one death).
-frac2-sched-const-first: before reload, on equal priority, the load of a constant into a pseudo
goes ahead of an arithmetic set of a pseudo (ahead of the register-weight test).
-frac2-sched-temp-store-after-args: before reload, on equal priority, a store of a compiler
temporary goes after a set of a call argument register.

Forced on for every USA v1.01 C unit they change 0, 154, 965 and 1109 functions. Opt-in
per-unit models under the owner's standard of 12 November 2026. Default compilation is
unchanged.

Usage: cc6b0_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'flags.h': [('extern int flag_rac2_unsized_sda_no_cond_slot;\nextern int flag_rac2_regmove_cmove_copy;\n/* RAC2: opt-in reload round-robin rules.  */\nextern int flag_rac2_reload_lone_class_no_rotate;\n', 'extern int flag_rac2_unsized_sda_no_cond_slot;\nextern int flag_rac2_regmove_cmove_copy;\n/* RAC2: opt-in rules of func_002CC6B0.  */\nextern int flag_rac2_flow2_trap_mem;\nextern int flag_rac2_la_multi_death_locals;\nextern int flag_rac2_sched_const_first;\nextern int flag_rac2_sched_temp_store_after_args;\n/* RAC2: opt-in reload round-robin rules.  */\nextern int flag_rac2_reload_lone_class_no_rotate;\n')], 'flow.c': [('\t  SET_REGNO_REG_SET (live, i);\n      break;\n\n    default:\n      break;\n    }\n', '\t  SET_REGNO_REG_SET (live, i);\n      break;\n\n    case TRAP_IF:\n      /* RAC2: -frac2-flow2-trap-mem: after reload a trap ends dead-store\n\t tracking.  */\n      if (flag_rac2_flow2_trap_mem && reload_completed)\n\tmem_set_list = NULL_RTX;\n      break;\n\n    default:\n      break;\n    }\n')], 'haifa-sched.c': [('}\n\nstatic int\nrank_for_schedule (x, y)\n', '}\n\n/* RAC2: a two-operand arithmetic set of a pseudo.  */\nstatic int\nrac2_arith_p (insn)\n     rtx insn;\n{\n  rtx set = single_set (insn);\n  enum rtx_code c;\n  if (! set || GET_CODE (SET_DEST (set)) != REG\n      || REGNO (SET_DEST (set)) < FIRST_PSEUDO_REGISTER)\n    return 0;\n  c = GET_CODE (SET_SRC (set));\n  return (c == PLUS || c == MINUS || c == AND || c == IOR || c == XOR\n\t  || c == ASHIFT || c == ASHIFTRT || c == LSHIFTRT);\n}\n\n/* RAC2: a store of a pseudo that is not a user variable.  */\nstatic int\nrac2_temp_store_p (insn)\n     rtx insn;\n{\n  rtx set = single_set (insn);\n  rtx src;\n  if (! set || GET_CODE (SET_DEST (set)) != MEM)\n    return 0;\n  src = SET_SRC (set);\n  if (GET_CODE (src) == SUBREG)\n    src = SUBREG_REG (src);\n  return (GET_CODE (src) == REG && REGNO (src) >= FIRST_PSEUDO_REGISTER\n\t  && ! REG_USERVAR_P (src));\n}\n\n/* RAC2: a set of a hard register that can carry a call argument.  */\nstatic int\nrac2_arg_set_p (insn)\n     rtx insn;\n{\n  rtx set = single_set (insn);\n  return (set && GET_CODE (SET_DEST (set)) == REG\n\t  && REGNO (SET_DEST (set)) < FIRST_PSEUDO_REGISTER\n\t  && FUNCTION_ARG_REGNO_P (REGNO (SET_DEST (set))));\n}\n\nstatic int\nrank_for_schedule (x, y)\n'), ('      && rac2_held[INSN_UID (tmp)] != rac2_held[INSN_UID (tmp2)])\n    return rac2_held[INSN_UID (tmp2)] - rac2_held[INSN_UID (tmp)];\n\n  /* prefer an insn with smaller contribution to registers-pressure */\n', '      && rac2_held[INSN_UID (tmp)] != rac2_held[INSN_UID (tmp2)])\n    return rac2_held[INSN_UID (tmp2)] - rac2_held[INSN_UID (tmp)];\n\n  /* RAC2: -frac2-sched-const-first: before reload, on equal priority, the\n     load of a constant into a pseudo goes ahead of an arithmetic set of a\n     pseudo (ahead of the weight test).  */\n  if (flag_rac2_sched_const_first && !reload_completed)\n    {\n      int c1 = rac2_const_load_p (tmp), c2 = rac2_const_load_p (tmp2);\n      if (c1 && ! c2 && rac2_arith_p (tmp2))\n\treturn -1;\n      if (c2 && ! c1 && rac2_arith_p (tmp))\n\treturn 1;\n    }\n\n  /* RAC2: -frac2-sched-temp-store-after-args: before reload, on equal\n     priority, a store of a compiler temporary goes after a set of a call\n     argument register.  */\n  if (flag_rac2_sched_temp_store_after_args && !reload_completed)\n    {\n      int s1 = rac2_temp_store_p (tmp), s2 = rac2_temp_store_p (tmp2);\n      int a1 = rac2_arg_set_p (tmp), a2 = rac2_arg_set_p (tmp2);\n      if (s1 && a2)\n\treturn 1;\n      if (s2 && a1)\n\treturn -1;\n    }\n\n  /* prefer an insn with smaller contribution to registers-pressure */\n')], 'local-alloc.c': [('  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)\n    {\n      if (REG_BASIC_BLOCK (i) >= 0 && REG_N_DEATHS (i) == 1\n\t  && (reg_alternate_class (i) == NO_REGS\n\t      || ! CLASS_LIKELY_SPILLED_P (reg_preferred_class (i))))\n', '  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)\n    {\n      if (REG_BASIC_BLOCK (i) >= 0\n\t  && (REG_N_DEATHS (i) == 1\n\t      /* RAC2: -frac2-la-multi-death-locals: a block-local user\n\t\t variable that dies more than once is allocated here too.  */\n\t      || (flag_rac2_la_multi_death_locals && REG_N_DEATHS (i) > 1\n\t\t  && REG_USERVAR_P (regno_reg_rtx[i])))\n\t  && (reg_alternate_class (i) == NO_REGS\n\t      || ! CLASS_LIKELY_SPILLED_P (reg_preferred_class (i))))\n')], 'toplev.c': [('int flag_rac2_regmove_cmove_copy = 0;\n\n/* RAC2: opt-in reload round-robin rules.  */\nint flag_rac2_reload_lone_class_no_rotate = 0;\n', 'int flag_rac2_regmove_cmove_copy = 0;\n\n/* RAC2: opt-in rules of func_002CC6B0.  */\nint flag_rac2_flow2_trap_mem = 0;\nint flag_rac2_la_multi_death_locals = 0;\nint flag_rac2_sched_const_first = 0;\nint flag_rac2_sched_temp_store_after_args = 0;\n\n/* RAC2: opt-in reload round-robin rules.  */\nint flag_rac2_reload_lone_class_no_rotate = 0;\n'), ('  {"rac2-regmove-cmove-copy", &flag_rac2_regmove_cmove_copy, 1,\n   "Copy a live register arm of a conditional move into its destination in regmove"},\n  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n   "Allocate local registers to floating-point user variables last"},\n', '  {"rac2-regmove-cmove-copy", &flag_rac2_regmove_cmove_copy, 1,\n   "Copy a live register arm of a conditional move into its destination in regmove"},\n  {"rac2-flow2-trap-mem", &flag_rac2_flow2_trap_mem, 1,\n   "After reload, a trap insn ends dead-store tracking in life analysis"},\n  {"rac2-la-multi-death-locals", &flag_rac2_la_multi_death_locals, 1,\n   "local-alloc also allocates a block-local user variable that dies more than once"},\n  {"rac2-sched-const-first", &flag_rac2_sched_const_first, 1,\n   "Before reload, on a priority tie a constant load into a pseudo goes first"},\n  {"rac2-sched-temp-store-after-args", &flag_rac2_sched_temp_store_after_args, 1,\n   "Before reload, on a priority tie a store of a temporary goes after call argument register sets"},\n  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n   "Allocate local registers to floating-point user variables last"},\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_sched_temp_store_after_args" in text for text in sources.values()):
        raise ValueError("cc6b0 rules already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
