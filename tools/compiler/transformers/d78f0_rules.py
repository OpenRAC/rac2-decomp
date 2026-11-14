#!/usr/bin/env python3
"""Add three opt-in switches for func_003478F0.

- -frac2-pseudo-base (emit-rtl.c init_emit): pseudo numbering starts 128 above the last virtual
  register (128 numbers reserved and never referenced), parameters included; this shifts PRE's
  bucket walk and so the spill-slot order.
- -frac2-gcse-hash-171 (gcse.c alloc_expr_hash_table): the PRE expression table has 171 buckets,
  a sibling of -frac2-gcse-hash-111.
- -frac2-sched-elapsed-latency (haifa-sched.c rank_for_schedule, before reload): the class test
  against the last scheduled insn subtracts the cycles elapsed since it issued, so a dependence
  whose latency has elapsed counts as independent.

Forced on they change 107, 133 and 4 functions: opt-in per-unit models under the owner's standard
of 12 November 2026. Default compilation is unchanged.

Usage: d78f0_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'haifa-sched.c': [('\n/* Data structures for the computation of data dependences in a regions.  We', '\n/* RAC2: cycle in which last_scheduled_insn was issued (for\n   -frac2-sched-elapsed-latency); clock_var is the cycle being filled.  */\nstatic int rac2_last_scheduled_clock;\nstatic int clock_var;\n\n/* Data structures for the computation of data dependences in a regions.  We'), ('         2) Anti/Output dependent on last scheduled insn.\n         3) Independent of last scheduled insn, or has latency of one.\n         Choose the insn from the highest numbered class if different.  */\n      link = find_insn_list (tmp, INSN_DEPEND (last_scheduled_insn));\n      if (link == 0 || insn_cost (last_scheduled_insn, link, tmp) == 1)\n\ttmp_class = 3;\n      else if (REG_NOTE_KIND (link) == 0)\t/* Data dependence.  */\n\ttmp_class = 1;\n', '         2) Anti/Output dependent on last scheduled insn.\n         3) Independent of last scheduled insn, or has latency of one.\n         Choose the insn from the highest numbered class if different.  */\n      /* RAC2: -frac2-sched-elapsed-latency.  Before reload, the cycles that\n\t have passed since the last scheduled insn was issued count against\n\t the latency of a dependence on it: once the latency has elapsed the\n\t dependent insn no longer stalls and is class 3 like an independent\n\t one.  */\n      int elapsed = 0;\n\n      if (flag_rac2_sched_elapsed_latency && !reload_completed)\n\telapsed = clock_var - rac2_last_scheduled_clock;\n\n      link = find_insn_list (tmp, INSN_DEPEND (last_scheduled_insn));\n      if (link == 0\n\t  || insn_cost (last_scheduled_insn, link, tmp) <= 1 + elapsed)\n\ttmp_class = 3;\n      else if (REG_NOTE_KIND (link) == 0)\t/* Data dependence.  */\n\ttmp_class = 1;\n'), ('\ttmp_class = 2;\n\n      link = find_insn_list (tmp2, INSN_DEPEND (last_scheduled_insn));\n      if (link == 0 || insn_cost (last_scheduled_insn, link, tmp2) == 1)\n\ttmp2_class = 3;\n      else if (REG_NOTE_KIND (link) == 0)\t/* Data dependence.  */\n\ttmp2_class = 1;\n', '\ttmp_class = 2;\n\n      link = find_insn_list (tmp2, INSN_DEPEND (last_scheduled_insn));\n      if (link == 0\n\t  || insn_cost (last_scheduled_insn, link, tmp2) <= 1 + elapsed)\n\ttmp2_class = 3;\n      else if (REG_NOTE_KIND (link) == 0)\t/* Data dependence.  */\n\ttmp2_class = 1;\n'), ('\t      last = move_insn (insn, last);', '\t      rac2_last_scheduled_clock = clock_var;\n\t      last = move_insn (insn, last);')], 'gcse.c': [('  /* RAC2: -frac2-gcse-hash-111 forces PRE expression hash table to 111 buckets.  */\n  if (flag_rac2_gcse_hash_111)\n    expr_hash_table_size = 111;\n  n = expr_hash_table_size * sizeof (struct expr *);\n  expr_hash_table = (struct expr **) gmalloc (n);\n}\n', '  /* RAC2: -frac2-gcse-hash-111 forces PRE expression hash table to 111 buckets.  */\n  if (flag_rac2_gcse_hash_111)\n    expr_hash_table_size = 111;\n  /* RAC2: -frac2-gcse-hash-171 forces PRE expression hash table to 171 buckets.  */\n  if (flag_rac2_gcse_hash_171)\n    expr_hash_table_size = 171;\n  n = expr_hash_table_size * sizeof (struct expr *);\n  expr_hash_table = (struct expr **) gmalloc (n);\n}\n')], 'emit-rtl.c': [('  REGNO_POINTER_ALIGN (VIRTUAL_CFA_REGNUM) = UNITS_PER_WORD;\n#endif\n\n#ifdef INIT_EXPANDERS\n  INIT_EXPANDERS;\n#endif\n', '  REGNO_POINTER_ALIGN (VIRTUAL_CFA_REGNUM) = UNITS_PER_WORD;\n#endif\n\n  /* RAC2: -frac2-pseudo-base starts pseudo-register numbering 128 above the\n     last virtual register: the first 128 numbers are reserved (allocated,\n     never referenced), so every pseudo of the function, the incoming\n     parameters included, is numbered 128 higher.  */\n  if (flag_rac2_pseudo_base)\n    {\n      int n = 128;\n      while (n-- > 0)\n\tgen_reg_rtx (SImode);\n    }\n\n#ifdef INIT_EXPANDERS\n  INIT_EXPANDERS;\n#endif\n')]}

DEFINITION_OLD = "int flag_rac2_sched_defer_const_after_death = 0;\n"
DEFINITION_NEW = DEFINITION_OLD + 'int flag_rac2_pseudo_base = 0;\nint flag_rac2_gcse_hash_171 = 0;\nint flag_rac2_sched_elapsed_latency = 0;\n'
OPTION_OLD = '  {"rac2-sched-defer-const-after-death", &flag_rac2_sched_defer_const_after_death, 1,\n'
OPTION_NEW = '  {"rac2-pseudo-base", &flag_rac2_pseudo_base, 1,\n   "Start pseudo register numbering 128 higher"},\n  {"rac2-gcse-hash-171", &flag_rac2_gcse_hash_171, 1,\n   "Use 171 buckets for gcse\'s expression table"},\n  {"rac2-sched-elapsed-latency", &flag_rac2_sched_elapsed_latency, 1,\n   "Count an elapsed dependence latency as independent in sched1"},\n' + OPTION_OLD
DECLARATION_OLD = "extern int flag_rac2_sched_defer_const_after_death;\n"
DECLARATION_NEW = DECLARATION_OLD + 'extern int flag_rac2_pseudo_base;\nextern int flag_rac2_gcse_hash_171;\nextern int flag_rac2_sched_elapsed_latency;\n'


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = list(HUNKS) + ["toplev.c", "flags.h"]
    s = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    if any("flag_rac2_pseudo_base" in text for text in s.values()):
        raise ValueError("d78f0_rules options already present")
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
