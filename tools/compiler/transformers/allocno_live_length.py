#!/usr/bin/env python3
"""Add the opt-in -frac2-allocno-live-length: prioritize allocnos by descending live length.

In GCC global-alloc, allocno_compare ranks allocnos by reference density:
floor_log2(refs) * refs / live_length. In func_L03_00421930, variable p has a shorter
live length (47) than table base (72) and stride (70), giving p higher density
and allocating it to $s1 before base ($s3). Retail allocated base to $s1 and p to $s3.

With -frac2-allocno-live-length, allocno_compare prioritizes allocnos with longer live
length before shorter ones (obj 94 > base 72 > stride 70 > p 47). Default compilation
is unchanged.

Usage: allocno_live_length.py <gcc directory or gcc/global.c>
"""
import sys
from pathlib import Path

COMPARE_OLD = """    /* Favor regs referenced in live ranges over other registers */
  pri1 = REG_N_RANGE_COPY_P (allocno_reg [v1]);
  pri2 = REG_N_RANGE_COPY_P (allocno_reg [v2]);
  if (pri2 - pri1)
    return pri2 - pri1;"""

COMPARE_NEW = """    /* Favor regs referenced in live ranges over other registers */
  pri1 = REG_N_RANGE_COPY_P (allocno_reg [v1]);
  pri2 = REG_N_RANGE_COPY_P (allocno_reg [v2]);
  if (pri2 - pri1)
    return pri2 - pri1;

  /* RAC2: -frac2-allocno-live-length: prioritize allocnos by descending live length.  */
  if (flag_rac2_allocno_live_length)
    {
      if (allocno_live_length[v2] - allocno_live_length[v1])
	return allocno_live_length[v2] - allocno_live_length[v1];
    }"""

DEFINITION_OLD = "int flag_rac2_sched_stack_offset = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_stack_offset = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, prioritize allocnos by descending live length.  */\n"
                  "int flag_rac2_allocno_live_length = 0;\n")

OPTION_OLD = '  {"rac2-sched-stack-offset", &flag_rac2_sched_stack_offset, 1,\n'
OPTION_NEW = ('  {"rac2-allocno-live-length", &flag_rac2_allocno_live_length, 1,\n'
              '   "Prioritize register allocnos by descending live length"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_stack_offset;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: prioritize allocnos by descending live length.  */\n"
                     "extern int flag_rac2_allocno_live_length;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    if target.is_dir():
        glob, top, flags = target / "global.c", target / "toplev.c", target / "flags.h"
    else:
        glob, top, flags = target, target.with_name("toplev.c"), target.with_name("flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (glob, top, flags)}
    if any("flag_rac2_allocno_live_length" in text for text in sources.values()):
        raise ValueError("allocno-live-length option already present")
    glob_src = replace_once(sources[glob], COMPARE_OLD, COMPARE_NEW, "allocno_compare live length")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((glob, glob_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
