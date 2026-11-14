#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-keep-live-length and -frac2-combine-keep-dead-sets.

-frac2-sched-keep-live-length (haifa-sched.c): the first scheduling pass may lengthen a
register's recorded live length but never shortens it. Forced on for every USA v1.01 C unit it
changes 1315 functions.

-frac2-combine-keep-dead-sets (combine.c): when combine places a death note on a set left without
uses, it marks the set REG_UNUSED instead of deleting it; a later life analysis (flow2) removes
it. Forced on for every USA v1.01 C unit it changes 1 function.

Both are first needed by func_US2_002CD670 (owner rulings of 14 November 2026: opt-in rules and,
for that function, fakematch order hints). Default compilation is unchanged.

Usage: cd670_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'combine.c': [('\t\t\t effects, mark the user with an UNUSED note instead\n'
                '\t\t\t of deleting it.  */\n'
                '\n'
                '\t\t      if (set != 0 && ! side_effects_p (SET_SRC (set))\n'
                '\t\t\t  && rtx_equal_p (XEXP (note, 0), inner_dest)\n'
                '#ifdef HAVE_cc0\n'
                '\t\t\t  && (! reg_mentioned_p (cc0_rtx, SET_SRC (set))\n',
                '\t\t\t effects, mark the user with an UNUSED note instead\n'
                '\t\t\t of deleting it.  */\n'
                '\n'
                '\t\t      /* RAC2: -frac2-combine-keep-dead-sets: the set is not\n'
                '\t\t\t deleted here; it gets a REG_UNUSED note below and\n'
                '\t\t\t stays until a later life analysis removes it.  */\n'
                '\t\t      if (set != 0 && ! side_effects_p (SET_SRC (set))\n'
                '\t\t\t  && ! flag_rac2_combine_keep_dead_sets\n'
                '\t\t\t  && rtx_equal_p (XEXP (note, 0), inner_dest)\n'
                '#ifdef HAVE_cc0\n'
                '\t\t\t  && (! reg_mentioned_p (cc0_rtx, SET_SRC (set))\n')],
 'flags.h': [('extern int flag_rac2_output_dep_no_alias_sets;\n'
              'extern int flag_rac2_unsized_sda_no_cond_slot;\n'
              'extern int flag_rac2_regmove_cmove_copy;\n'
              '/* RAC2: opt-in rules of func_002CC6B0.  */\n'
              'extern int flag_rac2_flow2_trap_mem;\n'
              'extern int flag_rac2_la_multi_death_locals;\n',
              'extern int flag_rac2_output_dep_no_alias_sets;\n'
              'extern int flag_rac2_unsized_sda_no_cond_slot;\n'
              'extern int flag_rac2_regmove_cmove_copy;\n'
              '/* RAC2: opt-in rules of func_US2_002CD670.  */\n'
              'extern int flag_rac2_sched_keep_live_length;\n'
              'extern int flag_rac2_combine_keep_dead_sets;\n'
              '/* RAC2: opt-in rules of func_002CC6B0.  */\n'
              'extern int flag_rac2_flow2_trap_mem;\n'
              'extern int flag_rac2_la_multi_death_locals;\n')],
 'haifa-sched.c': [('\t  }\n'
                    "\t/* Negative values are special; don't overwrite the current\n"
                    '\t   reg_live_length value if it is negative.  */\n'
                    '\tif (REG_LIVE_LENGTH (regno) >= 0)\n'
                    '\t  REG_LIVE_LENGTH (regno) = sched_reg_live_length[regno];\n'
                    '\n'
                    '\tif (sched_reg_basic_block[regno] != REG_BLOCK_UNKNOWN\n',
                    '\t  }\n'
                    "\t/* Negative values are special; don't overwrite the current\n"
                    '\t   reg_live_length value if it is negative.  */\n'
                    '\t/* RAC2: -frac2-sched-keep-live-length: scheduling never shortens\n'
                    "\t   a register's recorded live length.  */\n"
                    '\tif (REG_LIVE_LENGTH (regno) >= 0\n'
                    '\t    && ! (flag_rac2_sched_keep_live_length\n'
                    '\t\t  && sched_reg_live_length[regno] < REG_LIVE_LENGTH (regno)))\n'
                    '\t  REG_LIVE_LENGTH (regno) = sched_reg_live_length[regno];\n'
                    '\n'
                    '\tif (sched_reg_basic_block[regno] != REG_BLOCK_UNKNOWN\n')],
 'toplev.c': [('int flag_rac2_unsized_sda_no_cond_slot = 0;\n'
               'int flag_rac2_regmove_cmove_copy = 0;\n'
               '\n'
               '/* RAC2: opt-in rules of func_002CC6B0.  */\n'
               'int flag_rac2_flow2_trap_mem = 0;\n'
               'int flag_rac2_la_multi_death_locals = 0;\n',
               'int flag_rac2_unsized_sda_no_cond_slot = 0;\n'
               'int flag_rac2_regmove_cmove_copy = 0;\n'
               '\n'
               '/* RAC2: opt-in rules of func_US2_002CD670.  */\n'
               'int flag_rac2_sched_keep_live_length = 0;\n'
               'int flag_rac2_combine_keep_dead_sets = 0;\n'
               '/* RAC2: opt-in rules of func_002CC6B0.  */\n'
               'int flag_rac2_flow2_trap_mem = 0;\n'
               'int flag_rac2_la_multi_death_locals = 0;\n'),
              ('   "Keep loads of sda variables of unknown size out of conditional branch delay '
               'slots"},\n'
               '  {"rac2-regmove-cmove-copy", &flag_rac2_regmove_cmove_copy, 1,\n'
               '   "Copy a live register arm of a conditional move into its destination in '
               'regmove"},\n'
               '  {"rac2-flow2-trap-mem", &flag_rac2_flow2_trap_mem, 1,\n'
               '   "After reload, a trap insn ends dead-store tracking in life analysis"},\n'
               '  {"rac2-la-multi-death-locals", &flag_rac2_la_multi_death_locals, 1,\n',
               '   "Keep loads of sda variables of unknown size out of conditional branch delay '
               'slots"},\n'
               '  {"rac2-regmove-cmove-copy", &flag_rac2_regmove_cmove_copy, 1,\n'
               '   "Copy a live register arm of a conditional move into its destination in '
               'regmove"},\n'
               '  {"rac2-sched-keep-live-length", &flag_rac2_sched_keep_live_length, 1,\n'
               '   "Scheduling never shortens a register\'s recorded live length"},\n'
               '  {"rac2-combine-keep-dead-sets", &flag_rac2_combine_keep_dead_sets, 1,\n'
               '   "combine marks a set left without uses REG_UNUSED instead of deleting it"},\n'
               '  {"rac2-flow2-trap-mem", &flag_rac2_flow2_trap_mem, 1,\n'
               '   "After reload, a trap insn ends dead-store tracking in life analysis"},\n'
               '  {"rac2-la-multi-death-locals", &flag_rac2_la_multi_death_locals, 1,\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_sched_keep_live_length" in text for text in sources.values()):
        raise ValueError("cd670 options already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
