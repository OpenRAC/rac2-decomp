#!/usr/bin/env python3
"""Add the opt-in -frac2-no-null-pointer-checks: no Cygnus null-pointer-check pass.

rest_of_compilation (toplev.c) runs delete_null_pointer_checks (gcse.c) at -O2 after the first
jump pass and again after the jump pass that follows cse, both in a "CYGNUS LOCAL law" block
beside cygnus_merge_blocks, which -frac2-keep-block-order already leaves out. GCC 2.95 has
neither call. The pass starts with find_basic_blocks, and count_basic_blocks puts a
`(use (const_int 0))` after every call that ends a block, so a call followed by a label right
after the first jump pass keeps that no-op even when cse later deletes the label. Once the
blocks merge, sched1 is free to move the no-op, which has no dependences, between earlier
instructions, and local-alloc counts it as an instruction: two address pseudos that would be
born and die back to back no longer share a register.

func_L20_002CD928 (Yeedil) case 0x7C is the witness: its spawn block ends with a call before
the re-test of the new pointer, and cse threads the null branch past that re-test. Retail's
code is what the compiler gives without the early no-op: the re-test in the call's block
($v1, as $v0 is the call's) and the second copy's destination in $a1. With the pass in, the
no-op lands between the two copies (the destination comes out in $a0) or, when the label
survives, the re-test is a block of its own (in $v0). The twins func_L23_002C38B0 and
func_L13_002C5760 have the same block. That retail's compiler lacked the pass is an inference
from that code, not a dated GCC fix.

The option is off by default, enabled per compilation unit in config/cflags.txt (with
-frac2-keep-block-order, whose pass also counts blocks before cse), and
-fno-rac2-no-null-pointer-checks disables it again. Without it the source is unchanged in
effect. tests/test_no_null_pointer_checks.py covers the anchors, the default/disabled
equality and an authored check the pass deletes. See docs/build/compiler-notes.md.

Usage: no_null_pointer_checks.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

FIRST_OLD = ("  if (optimize > 1)\n"
             "    {\n"
             "      TIMEVAR (jump_time, delete_null_pointer_checks (get_insns ()));\n")
FIRST_NEW = ("  if (optimize > 1)\n"
             "    {\n"
             "      /* RAC2: -frac2-no-null-pointer-checks leaves out this Cygnus pass,\n"
             "         which GCC 2.95 does not have.  */\n"
             "      if (! flag_rac2_no_null_pointer_checks)\n"
             "        TIMEVAR (jump_time, delete_null_pointer_checks (get_insns ()));\n")
SECOND_OLD = ("\t  if (optimize > 1)\n"
              "\t    {\n"
              "\t      TIMEVAR (jump_time, delete_null_pointer_checks (get_insns ()));\n")
SECOND_NEW = ("\t  if (optimize > 1)\n"
              "\t    {\n"
              "\t      if (! flag_rac2_no_null_pointer_checks)\n"
              "\t\tTIMEVAR (jump_time, delete_null_pointer_checks (get_insns ()));\n")
DEFINITION_OLD = "int flag_thread_jumps;\n"
DEFINITION_NEW = ("int flag_thread_jumps;\n"
                  "\n"
                  "/* RAC2: opt-in, no Cygnus null-pointer-check pass (GCC 2.95).  */\n"
                  "int flag_rac2_no_null_pointer_checks = 0;\n")
OPTION_OLD = '  {"thread-jumps", &flag_thread_jumps, 1,\n'
OPTION_NEW = ('  {"rac2-no-null-pointer-checks", &flag_rac2_no_null_pointer_checks, 1,\n'
              '   "Do not run the null-pointer-check pass, as GCC 2.95"},\n'
              '  {"thread-jumps", &flag_thread_jumps, 1,\n')
DECLARATION_OLD = "extern int flag_expensive_optimizations;\n"
DECLARATION_NEW = ("extern int flag_expensive_optimizations;\n"
                   "\n"
                   "/* RAC2: no Cygnus null-pointer-check pass.  */\n"
                   "extern int flag_rac2_no_null_pointer_checks;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    top, flags = root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (top, flags)}
    if any("flag_rac2_no_null_pointer_checks" in text for text in sources.values()):
        raise ValueError("no-null-pointer-checks option already present")
    driver = replace_once(sources[top], FIRST_OLD, FIRST_NEW, "first null-pointer pass")
    driver = replace_once(driver, SECOND_OLD, SECOND_NEW, "second null-pointer pass")
    driver = replace_once(driver, DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
