#!/usr/bin/env python3
"""Add the opt-in -frac2-caller-reg-order: allocate argument registers ($a3) before $v1.

When allocating caller-saved registers for call-crossing values in global.c /
local-alloc.c, GCC walks reg_alloc_order. Stock MIPS GCC sets reg_alloc_order to
the identity order (0..FIRST_PSEUDO_REGISTER-1), placing $v1 (regno 3) before
$a3 (regno 7). In functions where an object pointer lives across a 3-argument call
such as MobySetState(object, 1, -1), $a0, $a1 and $a2 are occupied, leaving $a3
available as an argument scratch register. Retail's compiler allocated $a3 before
$v1 (witness: func_L22_003D0840).

With -frac2-caller-reg-order, mips_order_regs_for_local_alloc swaps the order of
$v1 and $a3 in reg_alloc_order. Default compilation is unchanged.

Usage: caller_reg_order.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

MIPS_OLD = ("  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)\n"
            "    reg_alloc_order[i] = i;\n")
MIPS_NEW = ("  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)\n"
            "    reg_alloc_order[i] = i;\n"
            "\n"
            "  /* RAC2: -frac2-caller-reg-order prefers argument registers ($a3)\n"
            "     before $v1 in caller-saved allocation order.  */\n"
            "  if (flag_rac2_caller_reg_order)\n"
            "    {\n"
            "      reg_alloc_order[3] = 7;\n"
            "      reg_alloc_order[7] = 3;\n"
            "    }\n")

DEFINITION_OLD = "int flag_rac2_sticky_volatile_sets = 1;\n"
DEFINITION_NEW = ("int flag_rac2_sticky_volatile_sets = 1;\n"
                  "\n"
                  "/* RAC2: opt-in, prefer argument registers ($a3) before $v1.  */\n"
                  "int flag_rac2_caller_reg_order = 0;\n")

OPTION_OLD = '   "Keep a volatile store marked across later stores"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-caller-reg-order", &flag_rac2_caller_reg_order, 1,\n'
              '   "Prefer argument registers before return scratch in register allocation"},\n')

DECLARATION_OLD = "extern int flag_rac2_sticky_volatile_sets;\n"
DECLARATION_NEW = ("extern int flag_rac2_sticky_volatile_sets;\n"
                   "\n"
                   "/* RAC2: prefer argument registers before $v1 in reg allocation.  */\n"
                   "extern int flag_rac2_caller_reg_order;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    mips, top, flags = root / "config/mips/mips.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (mips, top, flags)}
    if any("flag_rac2_caller_reg_order" in text for text in sources.values()):
        raise ValueError("caller-reg-order option already present")
    mips_src = replace_once(sources[mips], MIPS_OLD, MIPS_NEW, "mips_order_regs_for_local_alloc")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((mips, mips_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
