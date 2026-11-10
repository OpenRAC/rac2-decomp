#!/usr/bin/env python3
"""Add the opt-in -frac2-sticky-volatile-refs: mark_referenced_resources keeps `volatil` set.

The EE tree's resource.c predates Mark Mitchell's 6 May 1999 change in GCC 2.95 ("resource.c
(mark_referenced_resources): Make volatil monotonically increasing. (mark_set_resources):
Likewise."). Its mark_referenced_resources assigns `res->volatil = MEM_VOLATILE_P (x)` at
every MEM and ASM_OPERANDS, so a later ordinary MEM clears the flag a volatile asm set, and
reorg's forward delay-slot search goes on past the asm. GCC 2.95 uses `|=`.

func_L00_002A9460 (412 bytes, 27 places) shows retail kept the flag: the search from its
first call passes a volatile qcopy asm and stops, so `addiu $s1,$s1,%lo(D_00189E20)` fills the
second call's slot instead. With this option the two mark_referenced_resources sites use `|=`.
The referenced half alone changes only func_L00_002A9460's unit of 8,511. The
mark_set_resources half of the same upstream change is the compiler's default
(sticky_volatile_sets.py, -fno-rac2-sticky-volatile-sets to opt out).

The option is off by default, enabled per unit in config/cflags.txt, and
-fno-rac2-sticky-volatile-refs disables it again. tests/test_sticky_volatile_refs.py covers
the anchors, the default/disabled equality, the moved delay slot and a control without an asm.
See docs/build/compiler-notes.md.

Usage: sticky_volatile_refs.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

MEM_OLD = ("\tres->memory = 1;\n"
           "      res->volatil = MEM_VOLATILE_P (x);\n"
           "\n"
           "      /* Mark registers used to access memory.  */\n")
MEM_NEW = ("\tres->memory = 1;\n"
           "      /* RAC2: -frac2-sticky-volatile-refs keeps volatil set (GCC 2.95's |=).  */\n"
           "      res->volatil = (flag_rac2_sticky_volatile_refs ? res->volatil : 0)\n"
           "\t\t     | MEM_VOLATILE_P (x);\n"
           "\n"
           "      /* Mark registers used to access memory.  */\n")
ASM_OLD = ("    case ASM_OPERANDS:\n"
           "      res->volatil = MEM_VOLATILE_P (x);\n"
           "\n"
           "      /* For all ASM_OPERANDS, we must traverse the vector of input operands.\n")
ASM_NEW = ("    case ASM_OPERANDS:\n"
           "      res->volatil = (flag_rac2_sticky_volatile_refs ? res->volatil : 0)\n"
           "\t\t     | MEM_VOLATILE_P (x);\n"
           "\n"
           "      /* For all ASM_OPERANDS, we must traverse the vector of input operands.\n")
DEFINITION_OLD = "int flag_rac2_keep_block_zero_copy = 0;\n"
DEFINITION_NEW = ("int flag_rac2_keep_block_zero_copy = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, mark_referenced_resources keeps volatil set.  */\n"
                  "int flag_rac2_sticky_volatile_refs = 0;\n")
OPTION_OLD = '   "Keep a copy of a register set to zero earlier in the same block"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-sticky-volatile-refs", &flag_rac2_sticky_volatile_refs, 1,\n'
              '   "Keep a volatile reference marked across later memory references"},\n')
DECLARATION_OLD = "extern int flag_rac2_keep_block_zero_copy;\n"
DECLARATION_NEW = ("extern int flag_rac2_keep_block_zero_copy;\n"
                   "\n"
                   "/* RAC2: mark_referenced_resources keeps volatil set.  */\n"
                   "extern int flag_rac2_sticky_volatile_refs;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    resource, top, flags = root / "resource.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (resource, top, flags)}
    if any("flag_rac2_sticky_volatile_refs" in text for text in sources.values()):
        raise ValueError("sticky-volatile-refs option already present")
    marked = replace_once(sources[resource], MEM_OLD, MEM_NEW, "MEM reference")
    marked = replace_once(marked, ASM_OLD, ASM_NEW, "ASM_OPERANDS reference")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((resource, marked), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
