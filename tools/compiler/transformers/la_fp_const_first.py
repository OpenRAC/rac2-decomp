#!/usr/bin/env python3
"""Add the opt-in -frac2-la-fp-const-first: in a two-quantity FP block, the constant goes first.

In local-alloc's block_alloc, when a block has exactly two quantities, both floating point, and
the first born is set from a constant (a REG_EQUIV constant), that constant is allocated first
whatever the priorities. In func_002D3FA0's y3 block the 187.0 constant then takes $f0 and the
scale chain $f1, as retail (the three-quantity sibling blocks already sort that way).

Forced on for every USA v1.01 C unit it changes 110 functions: an opt-in per-unit model under the
owner's standard of 12 November 2026. Default compilation is unchanged.

Usage: la_fp_const_first.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'local-alloc.c': [('static int qty_sugg_compare    \tPROTO((int, int));\nstatic int qty_sugg_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\nstatic int qty_compare    \tPROTO((int, int));\nstatic int qty_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\nstatic int combine_regs\t\tPROTO((rtx, rtx, int, int, rtx, int));\nstatic int reg_meets_class_p\tPROTO((int, enum reg_class));\n', 'static int qty_sugg_compare    \tPROTO((int, int));\nstatic int qty_sugg_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\nstatic int qty_compare    \tPROTO((int, int));\nstatic int rac2_fp_const_pair\tPROTO((int));\nstatic int qty_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\nstatic int combine_regs\t\tPROTO((rtx, rtx, int, int, rtx, int));\nstatic int reg_meets_class_p\tPROTO((int, enum reg_class));\n'), ('      qsort (qty_order, next_qty, sizeof (int), qty_compare_1);\n    }\n\n  /* Now for each qty that is not a hardware register,\n     look for a hardware register to put it in.\n     First try the register class that is cheapest for this qty,\n', "      qsort (qty_order, next_qty, sizeof (int), qty_compare_1);\n    }\n\n  /* RAC2: -frac2-la-fp-const-first: when the block's only two quantities\n     are both floating point and the first born is a constant, the\n     constant gets its register first, whatever the priorities.  */\n  if (flag_rac2_la_fp_const_first && next_qty == 2 && rac2_fp_const_pair (b))\n    {\n      qty_order[0] = 0;\n      qty_order[1] = 1;\n    }\n\n  /* Now for each qty that is not a hardware register,\n     look for a hardware register to put it in.\n     First try the register class that is cheapest for this qty,\n"), ("      }\n}\n\x0c\n/* Compare two quantities' priority for getting real registers.\n   We give shorter-lived quantities higher priority.\n   Quantities with more references are also preferred, as are quantities that\n", "      }\n}\n\x0c\n/* RAC2: -frac2-la-fp-const-first: nonzero if both quantities of the\n   two-quantity block B are floating point and quantity 0 (the first born)\n   is set from a constant (its insn carries a constant REG_EQUIV note).  */\n\nstatic int\nrac2_fp_const_pair (b)\n     int b;\n{\n  rtx insn, set, note;\n\n  if (GET_MODE_CLASS (qty_mode[0]) != MODE_FLOAT\n      || GET_MODE_CLASS (qty_mode[1]) != MODE_FLOAT)\n    return 0;\n\n  for (insn = BLOCK_HEAD (b); ; insn = NEXT_INSN (insn))\n    {\n      if (GET_CODE (insn) == INSN && (set = single_set (insn)) != 0\n\t  && GET_CODE (SET_DEST (set)) == REG\n\t  && REGNO (SET_DEST (set)) == qty_first_reg[0]\n\t  && (note = find_reg_note (insn, REG_EQUIV, NULL_RTX)) != 0\n\t  && CONSTANT_P (XEXP (note, 0)))\n\treturn 1;\n      if (insn == BLOCK_END (b))\n\tbreak;\n    }\n  return 0;\n}\n\n/* Compare two quantities' priority for getting real registers.\n   We give shorter-lived quantities higher priority.\n   Quantities with more references are also preferred, as are quantities that\n")], 'flags.h': [('extern int flag_rac2_sched_call_addr_float;\n/* RAC2: local-alloc serves floating-point user variables last.  */\nextern int flag_rac2_la_float_vars_last;\n/* RAC2: opt-in reload round-robin rules.  */\nextern int flag_rac2_reload_lone_class_no_rotate;\nextern int flag_rac2_reload_reuse_pseudo_reg;\n', 'extern int flag_rac2_sched_call_addr_float;\n/* RAC2: local-alloc serves floating-point user variables last.  */\nextern int flag_rac2_la_float_vars_last;\nextern int flag_rac2_la_fp_const_first;\n/* RAC2: opt-in reload round-robin rules.  */\nextern int flag_rac2_reload_lone_class_no_rotate;\nextern int flag_rac2_reload_reuse_pseudo_reg;\n')], 'toplev.c': [('\n/* RAC2: opt-in, local-alloc serves floating-point user variables last.  */\nint flag_rac2_la_float_vars_last = 0;\n\n/* RAC2: opt-in reload round-robin rules.  */\nint flag_rac2_reload_lone_class_no_rotate = 0;\n', '\n/* RAC2: opt-in, local-alloc serves floating-point user variables last.  */\nint flag_rac2_la_float_vars_last = 0;\nint flag_rac2_la_fp_const_first = 0;\n\n/* RAC2: opt-in reload round-robin rules.  */\nint flag_rac2_reload_lone_class_no_rotate = 0;\n'), ('   "A reload whose class has one spill register leaves the round robin alone"},\n  {"rac2-reload-reuse-pseudo-reg", &flag_rac2_reload_reuse_pseudo_reg, 1,\n   "Reload a pseudo into the spill register that last loaded it"},\n  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n   "Allocate local registers to floating-point user variables last"},\n  {"rac2-sched-call-addr-float", &flag_rac2_sched_call_addr_float, 1,\n', '   "A reload whose class has one spill register leaves the round robin alone"},\n  {"rac2-reload-reuse-pseudo-reg", &flag_rac2_reload_reuse_pseudo_reg, 1,\n   "Reload a pseudo into the spill register that last loaded it"},\n  {"rac2-la-fp-const-first", &flag_rac2_la_fp_const_first, 1,\n   "In a block of two floating-point quantities, allocate a first-born constant first"},\n  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n   "Allocate local registers to floating-point user variables last"},\n  {"rac2-sched-call-addr-float", &flag_rac2_sched_call_addr_float, 1,\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_la_fp_const_first" in text for text in sources.values()):
        raise ValueError("la-fp-const-first option already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
