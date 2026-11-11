#!/usr/bin/env python3
"""Add the opt-in -frac2-gcse-hash-111: force PRE expression hash table to 111 buckets.

In GCC 2.95 gcse.c:alloc_expr_hash_table, the PRE hash table size is computed as
`expr_hash_table_size = n_insns / 2 | 1`. The hash table size directly dictates the
bucket assignment and spill-slot allocation order of PRE-hoisted loop invariants.
In func_L00_003E5BD8, max_cuid is 242 (table size 121), whereas retail's binary
matches an expression table size of 111 buckets (max_cuid ~222).

With -frac2-gcse-hash-111, alloc_expr_hash_table sets expr_hash_table_size = 111.

Usage: gcse_hash_111.py <gcc/gcse.c or gcc directory>
"""
import sys
from pathlib import Path

HASH_OLD = """  /* Attempt to maintain efficient use of hash table.
     Making it an odd number is simplest for now.
     ??? Later take some measurements.  */
  expr_hash_table_size |= 1;
  n = expr_hash_table_size * sizeof (struct expr *);"""

HASH_NEW = """  /* Attempt to maintain efficient use of hash table.
     Making it an odd number is simplest for now.
     ??? Later take some measurements.  */
  expr_hash_table_size |= 1;
  /* RAC2: -frac2-gcse-hash-111 forces PRE expression hash table to 111 buckets.  */
  if (flag_rac2_gcse_hash_111)
    expr_hash_table_size = 111;
  n = expr_hash_table_size * sizeof (struct expr *);"""

DEFINITION_OLD = "int flag_rac2_delay_no_split_hi = 0;\n"
DEFINITION_NEW = ("int flag_rac2_delay_no_split_hi = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, force GCSE expression hash table to 111 buckets.  */\n"
                  "int flag_rac2_gcse_hash_111 = 0;\n")

OPTION_OLD = '  {"rac2-delay-no-split-hi", &flag_rac2_delay_no_split_hi, 1,\n'
OPTION_NEW = ('  {"rac2-gcse-hash-111", &flag_rac2_gcse_hash_111, 1,\n'
              '   "Force GCSE expression hash table to 111 buckets"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_delay_no_split_hi;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: force GCSE expression hash table to 111 buckets.  */\n"
                     "extern int flag_rac2_gcse_hash_111;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    if target.is_dir():
        gcse, top, flags = target / "gcse.c", target / "toplev.c", target / "flags.h"
    else:
        gcse, top, flags = target, target.with_name("toplev.c"), target.with_name("flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (gcse, top, flags)}
    if any("flag_rac2_gcse_hash_111" in text for text in sources.values()):
        raise ValueError("gcse-hash-111 option already present")
    gcse_src = replace_once(sources[gcse], HASH_OLD, HASH_NEW, "alloc_expr_hash_table size")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((gcse, gcse_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
