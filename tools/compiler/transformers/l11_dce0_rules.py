#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-fp-const-temp-first and -frac2-ga-addr-equiv-no-new-save.

-frac2-sched-fp-const-temp-first (haifa-sched.c): before reload, on a full tie between two
floating-point constant loads into pseudos live beyond their block, the load into a compiler
temporary goes before the load into a user variable (a sibling of -frac2-sched-frame-temp-first).
Forced on for every USA v1.01 C unit it changes 43 functions.

-frac2-ga-addr-equiv-no-new-save (global.c): a call-crossing user variable set once to a constant
address (REG_EQUIV of a SYMBOL_REF, LABEL_REF or CONST) does not take the only register left that
nothing has used so far (one that would need a new callee save); left without a register, reload
rematerialises the address at each use. Forced on for every USA v1.01 C unit it changes 16
functions.

Together they match func_PAL_L11_0045DCE0, the PAL copy of func_L11_004580E8: opt-in per-unit
models under the owner's standard of 12 November 2026 (owner ruling, 14 November 2026). Default
compilation is unchanged.

Usage: l11_dce0_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'flags.h': [('extern int flag_rac2_sched_call_last;\n'
              'extern int flag_rac2_sched_argreg_wait;\n'
              'extern int flag_rac2_sched_frame_temp_first;\n'
              'extern int flag_rac2_sched_call_with_arg_copy;\n'
              '/* RAC2: opt-in reload round-robin rules.  */\n'
              'extern int flag_rac2_reload_lone_class_no_rotate;\n',
              'extern int flag_rac2_sched_call_last;\n'
              'extern int flag_rac2_sched_argreg_wait;\n'
              'extern int flag_rac2_sched_frame_temp_first;\n'
              'extern int flag_rac2_sched_fp_const_temp_first;\n'
              'extern int flag_rac2_ga_addr_equiv_no_new_save;\n'
              'extern int flag_rac2_sched_call_with_arg_copy;\n'
              '/* RAC2: opt-in reload round-robin rules.  */\n'
              'extern int flag_rac2_reload_lone_class_no_rotate;\n')],
 'global.c': [('/* RAC2: -frac2-ga-divisor-first: nonzero for an allocno that holds a\n'
               '   constant used as a divisor.  */\n'
               'static char *rac2_divisor_allocno;\n'
               '/* RAC2: -frac2-ga-hoisted-var-first: nonzero for an allocno that is a\n'
               '   floating-point user variable set by an insn moved out of a loop\n'
               '   (rac2_hoisted, loop.c).  */\n',
               '/* RAC2: -frac2-ga-divisor-first: nonzero for an allocno that holds a\n'
               '   constant used as a divisor.  */\n'
               'static char *rac2_divisor_allocno;\n'
               '\n'
               '/* RAC2: -frac2-ga-addr-equiv-no-new-save: allocnos set once to a constant\n'
               '   address (a REG_EQUIV of a SYMBOL_REF, LABEL_REF or CONST).  */\n'
               'static char *rac2_addr_equiv_allocno;\n'
               '/* RAC2: -frac2-ga-hoisted-var-first: nonzero for an allocno that is a\n'
               '   floating-point user variable set by an insn moved out of a loop\n'
               '   (rac2_hoisted, loop.c).  */\n'),
              ('\t      rac2_divisor_allocno[r] = 0;\n'
               '\t}\n'
               '\n'
               '      qsort (allocno_order, max_allocno, sizeof (int), allocno_compare);\n'
               ' \n'
               '      if (file)\n',
               '\t      rac2_divisor_allocno[r] = 0;\n'
               '\t}\n'
               '\n'
               '      rac2_addr_equiv_allocno = 0;\n'
               '      if (flag_rac2_ga_addr_equiv_no_new_save)\n'
               '\t{\n'
               '\t  rtx insn, set, note;\n'
               '\t  int r;\n'
               '\n'
               '\t  rac2_addr_equiv_allocno = (char *) obstack_alloc (&global_obstack,\n'
               '\t\t\t\t\t\t\t    max_allocno);\n'
               '\t  bzero (rac2_addr_equiv_allocno, max_allocno);\n'
               '\t  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))\n'
               '\t    if (GET_CODE (insn) == INSN\n'
               '\t\t&& (set = single_set (insn)) != 0\n'
               '\t\t&& GET_CODE (SET_DEST (set)) == REG\n'
               '\t\t&& (r = REGNO (SET_DEST (set))) >= FIRST_PSEUDO_REGISTER\n'
               '\t\t&& reg_allocno[r] >= 0\n'
               '\t\t&& REG_N_SETS (r) == 1\n'
               '\t\t&& (note = find_reg_note (insn, REG_EQUIV, NULL_RTX)) != 0\n'
               '\t\t&& (GET_CODE (XEXP (note, 0)) == SYMBOL_REF\n'
               '\t\t    || GET_CODE (XEXP (note, 0)) == LABEL_REF\n'
               '\t\t    || GET_CODE (XEXP (note, 0)) == CONST))\n'
               '\t      rac2_addr_equiv_allocno[reg_allocno[r]] = 1;\n'
               '\t}\n'
               '\n'
               '      qsort (allocno_order, max_allocno, sizeof (int), allocno_compare);\n'
               ' \n'
               '      if (file)\n'),
              ('\n'
               '  IOR_HARD_REG_SET (used1, hard_reg_conflicts[allocno]);\n'
               '\n'
               '#ifdef CLASS_CANNOT_CHANGE_SIZE\n'
               '  if (REG_CHANGES_SIZE (allocno_reg[allocno]))\n'
               '    IOR_HARD_REG_SET (used1,\n',
               '\n'
               '  IOR_HARD_REG_SET (used1, hard_reg_conflicts[allocno]);\n'
               '\n'
               '  /* RAC2: -frac2-ga-addr-equiv-no-new-save: a call-crossing user variable\n'
               '     set once to a constant address does not take the only register left\n'
               '     that nothing has used so far (one that would need a new callee save);\n'
               '     left without a register, reload rematerializes the address at each\n'
               '     use.  */\n'
               '  if (rac2_addr_equiv_allocno && rac2_addr_equiv_allocno[allocno]\n'
               '      && allocno_calls_crossed[allocno] != 0 && ! accept_call_clobbered\n'
               '      && REG_USERVAR_P (regno_reg_rtx[pseudo]))\n'
               '    {\n'
               '      int k, nnew = 0;\n'
               '      for (k = 0; k < FIRST_PSEUDO_REGISTER; k++)\n'
               '\tif (! TEST_HARD_REG_BIT (used1, k)\n'
               '\t    && ! TEST_HARD_REG_BIT (regs_used_so_far, k)\n'
               '\t    && HARD_REGNO_MODE_OK (k, mode))\n'
               '\t  nnew++;\n'
               '      if (nnew == 1)\n'
               '\tIOR_COMPL_HARD_REG_SET (used1, regs_used_so_far);\n'
               '    }\n'
               '\n'
               '#ifdef CLASS_CANNOT_CHANGE_SIZE\n'
               '  if (REG_CHANGES_SIZE (allocno_reg[allocno]))\n'
               '    IOR_HARD_REG_SET (used1,\n')],
 'haifa-sched.c': [('\treturn REG_USERVAR_P (SET_DEST (s1)) ? 1 : -1;\n'
                    '    }\n'
                    '\n'
                    '  /* RAC2: -frac2-sched-stack-offset: prefer higher displacement for stack '
                    'pointer\n'
                    '     address computations.  */\n'
                    '  if (flag_rac2_sched_stack_offset)\n',
                    '\treturn REG_USERVAR_P (SET_DEST (s1)) ? 1 : -1;\n'
                    '    }\n'
                    '\n'
                    '  /* RAC2: -frac2-sched-fp-const-temp-first: before reload, on a full tie\n'
                    '     between two floating-point constant loads into pseudos live beyond\n'
                    '     their block, the load into a compiler temporary goes before the load\n'
                    '     into a user variable.  */\n'
                    '  if (flag_rac2_sched_fp_const_temp_first && !reload_completed)\n'
                    '    {\n'
                    '      rtx s1 = single_set (tmp), s2 = single_set (tmp2);\n'
                    '      if (s1 && s2\n'
                    '\t  && GET_CODE (SET_DEST (s1)) == REG && GET_CODE (SET_DEST (s2)) == REG\n'
                    '\t  && REGNO (SET_DEST (s1)) >= FIRST_PSEUDO_REGISTER\n'
                    '\t  && REGNO (SET_DEST (s2)) >= FIRST_PSEUDO_REGISTER\n'
                    '\t  && GET_MODE_CLASS (GET_MODE (SET_DEST (s1))) == MODE_FLOAT\n'
                    '\t  && GET_MODE_CLASS (GET_MODE (SET_DEST (s2))) == MODE_FLOAT\n'
                    '\t  && GET_CODE (SET_SRC (s1)) == CONST_DOUBLE\n'
                    '\t  && GET_CODE (SET_SRC (s2)) == CONST_DOUBLE\n'
                    '\t  && REG_BASIC_BLOCK (REGNO (SET_DEST (s1))) == REG_BLOCK_GLOBAL\n'
                    '\t  && REG_BASIC_BLOCK (REGNO (SET_DEST (s2))) == REG_BLOCK_GLOBAL\n'
                    '\t  && (REG_USERVAR_P (SET_DEST (s1)) != 0) != (REG_USERVAR_P (SET_DEST (s2)) '
                    '!= 0))\n'
                    '\treturn REG_USERVAR_P (SET_DEST (s1)) ? 1 : -1;\n'
                    '    }\n'
                    '\n'
                    '  /* RAC2: -frac2-sched-stack-offset: prefer higher displacement for stack '
                    'pointer\n'
                    '     address computations.  */\n'
                    '  if (flag_rac2_sched_stack_offset)\n')],
 'toplev.c': [('int flag_rac2_sched_call_last = 0;\n'
               'int flag_rac2_sched_argreg_wait = 0;\n'
               'int flag_rac2_sched_frame_temp_first = 0;\n'
               'int flag_rac2_sched_call_with_arg_copy = 0;\n'
               'extern void rac2_forget_hoisted PROTO((void));\n',
               'int flag_rac2_sched_call_last = 0;\n'
               'int flag_rac2_sched_argreg_wait = 0;\n'
               'int flag_rac2_sched_frame_temp_first = 0;\n'
               'int flag_rac2_sched_fp_const_temp_first = 0;\n'
               'int flag_rac2_ga_addr_equiv_no_new_save = 0;\n'
               'int flag_rac2_sched_call_with_arg_copy = 0;\n'
               'extern void rac2_forget_hoisted PROTO((void));\n'),
              ('   "Before reload, an argument register set that depends on a call waits two '
               'cycles"},\n'
               '  {"rac2-sched-frame-temp-first", &flag_rac2_sched_frame_temp_first, 1,\n'
               '   "On a full sched1 tie of two frame addresses, the temporary before the user '
               'variable"},\n'
               '  {"rac2-sched-call-with-arg-copy", &flag_rac2_sched_call_with_arg_copy, 1,\n'
               '   "Before reload, a value call made ready by a delayed argument copy issues in '
               'its cycle"},\n'
               '  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n',
               '   "Before reload, an argument register set that depends on a call waits two '
               'cycles"},\n'
               '  {"rac2-sched-frame-temp-first", &flag_rac2_sched_frame_temp_first, 1,\n'
               '   "On a full sched1 tie of two frame addresses, the temporary before the user '
               'variable"},\n'
               '  {"rac2-sched-fp-const-temp-first", &flag_rac2_sched_fp_const_temp_first, 1,\n'
               '   "On a full sched1 tie of two block-crossing float constant loads, the temporary '
               'before the user variable"},\n'
               '  {"rac2-ga-addr-equiv-no-new-save", &flag_rac2_ga_addr_equiv_no_new_save, 1,\n'
               '   "A call-crossing user variable equal to a constant address does not take the '
               'last register needing a new save"},\n'
               '  {"rac2-sched-call-with-arg-copy", &flag_rac2_sched_call_with_arg_copy, 1,\n'
               '   "Before reload, a value call made ready by a delayed argument copy issues in '
               'its cycle"},\n'
               '  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_ga_addr_equiv_no_new_save" in text for text in sources.values()):
        raise ValueError("l11_dce0 options already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
