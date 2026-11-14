#!/usr/bin/env python3
"""Add the opt-in -frac2-la-unweighted-refs (local-alloc.c).

local-alloc ranks a block's quantities by their reference counts divided by the block's loop
depth (rounded, at least 1), i.e. without the loop-depth weight flow gives references inside
do { } while (0) groups; qty_n_refs itself is unchanged. Forced on for every USA v1.01 C unit it
changes 229 functions. First needed by func_PAL_002CD520 (owner rulings of 14 November 2026:
opt-in rules and, for that function, fakematch order hints). Default compilation is unchanged.

Usage: cd520_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'flags.h': [('extern int flag_rac2_combine_keep_dead_sets;\n',
              'extern int flag_rac2_combine_keep_dead_sets;\n'
              '/* RAC2: -frac2-la-unweighted-refs.  */\n'
              'extern int flag_rac2_la_unweighted_refs;\n')],
 'local-alloc.c': [('/* RAC2: -frac2-la-const-longer-first: nonzero for a quantity of the\n'
                    '   current block set from an integer constant.  */\n'
                    'static char *rac2_qconst;\n'
                    'static int qty_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\n'
                    'static int combine_regs\t\tPROTO((rtx, rtx, int, int, rtx, int));\n'
                    'static int reg_meets_class_p\tPROTO((int, enum reg_class));\n',
                    '/* RAC2: -frac2-la-const-longer-first: nonzero for a quantity of the\n'
                    '   current block set from an integer constant.  */\n'
                    'static char *rac2_qconst;\n'
                    '\n'
                    '/* RAC2: -frac2-la-unweighted-refs: the loop depth flow weighted the\n'
                    '   references of the block being allocated with, or 1.  */\n'
                    'static int rac2_block_depth = 1;\n'
                    'static int qty_compare_1\tPROTO((const GENERIC_PTR, const GENERIC_PTR));\n'
                    'static int combine_regs\t\tPROTO((rtx, rtx, int, int, rtx, int));\n'
                    'static int reg_meets_class_p\tPROTO((int, enum reg_class));\n'),
                   ('\t}\n'
                    '    }\n'
                    '\n'
                    '  qty_order = (int *) alloca (next_qty * sizeof (int));\n'
                    '  for (i = 0; i < next_qty; i++)\n'
                    '    qty_order[i] = i;\n',
                    '\t}\n'
                    '    }\n'
                    '\n'
                    '  rac2_block_depth = 1;\n'
                    '  if (flag_rac2_la_unweighted_refs && BASIC_BLOCK (b)->loop_depth > 1)\n'
                    '    rac2_block_depth = BASIC_BLOCK (b)->loop_depth;\n'
                    '\n'
                    '  qty_order = (int *) alloca (next_qty * sizeof (int));\n'
                    '  for (i = 0; i < next_qty; i++)\n'
                    '    qty_order[i] = i;\n'),
                   ("   Multiplying this by 10000 can't overflow.\n"
                    '   QTY_CMP_PRI is also used by qty_sugg_compare.  */\n'
                    '\n'
                    '#define QTY_CMP_PRI(q)\t\t\\\n'
                    '  ((int) (((double) (floor_log2 (qty_n_refs[q]) * qty_n_refs[q] * '
                    'qty_size[q]) \\\n'
                    '\t  / (qty_death[q] - qty_birth[q])) * 10000))\n'
                    '\n'
                    '/* RAC2: -frac2-la-float-vars-last: nonzero if quantity Q is a '
                    'floating-point\n',
                    "   Multiplying this by 10000 can't overflow.\n"
                    '   QTY_CMP_PRI is also used by qty_sugg_compare.  */\n'
                    '\n'
                    '/* RAC2: -frac2-la-unweighted-refs: every reference of a block-local\n'
                    "   quantity has the block's loop-depth weight; rank by the plain count.  */\n"
                    '#define RAC2_QTY_REFS(q) \\\n'
                    '  (rac2_block_depth > 1 \\\n'
                    '   ? MAX (1, (qty_n_refs[q] + rac2_block_depth / 2) / rac2_block_depth) \\\n'
                    '   : qty_n_refs[q])\n'
                    '\n'
                    '#define QTY_CMP_PRI(q)\t\t\\\n'
                    '  ((int) (((double) (floor_log2 (RAC2_QTY_REFS (q)) * RAC2_QTY_REFS (q) * '
                    'qty_size[q]) \\\n'
                    '\t  / (qty_death[q] - qty_birth[q])) * 10000))\n'
                    '\n'
                    '/* RAC2: -frac2-la-float-vars-last: nonzero if quantity Q is a '
                    'floating-point\n')],
 'toplev.c': [('int flag_rac2_combine_keep_dead_sets = 0;\n',
               'int flag_rac2_combine_keep_dead_sets = 0;\n'
               'int flag_rac2_la_unweighted_refs = 0;\n'),
              ('  {"rac2-combine-keep-dead-sets", &flag_rac2_combine_keep_dead_sets, 1,\n'
               '   "combine marks a set left without uses REG_UNUSED instead of deleting it"},\n',
               '  {"rac2-combine-keep-dead-sets", &flag_rac2_combine_keep_dead_sets, 1,\n'
               '   "combine marks a set left without uses REG_UNUSED instead of deleting it"},\n'
               '  {"rac2-la-unweighted-refs", &flag_rac2_la_unweighted_refs, 1,\n'
               '   "local-alloc ranks a block\'s quantities by reference counts without loop-depth '
               'weight"},\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_la_unweighted_refs" in text for text in sources.values()):
        raise ValueError("cd520 option already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
