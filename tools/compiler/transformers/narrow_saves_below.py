#!/usr/bin/env python3
"""Add the opt-in -frac2-narrow-saves-below: full-width GPR saves above narrower ones.

With -mastra-quad-saves every GPR save slot is a TImode slot and save_restore_insns (mips.c)
walks the saved registers from $31 down, so $ra always takes the top slot and each lower
register the next slot below. The stock EE attribute `register_precision` narrows one
register's save mode (mips_reg_mode[]) but not its place: a register narrowed to DImode
still sits in the slot its number gives it.

Retail has exactly two quad-slot frames that mix widths, both variadic level functions:
func_L01_00324550 (`sq $s0,0x210` above `sd $ra,0x200`) and func_L08_00389B68 (`sq $s0,0x10`
above `sd $ra,0x0`), each restoring `lq $s0` before `ld $ra`. Every retail frame whose saves
all have one width (func_00115C90, func_00115FC0 and the other -mastra-quad-saves units)
keeps $ra on top. With this option the save loop runs twice over the same descending
register order: first the registers saved at the slot's full width, then the narrower ones,
so a narrower save takes a lower slot. A frame whose saves all have the slot's width is
emitted exactly as before, and without -mastra-quad-saves the option has no effect.

The option is off by default, enabled per unit in config/cflags.txt (with -mastra-quad-saves),
and -fno-rac2-narrow-saves-below disables it again. tests/test_narrow_saves_below.py covers
the anchors, the default/disabled equality, an authored mixed-width frame and a control.
See docs/build/compiler-notes.md.

Usage: narrow_saves_below.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

LOOP_OLD = ("                for (regno = mips_astra_quad_saves ? GP_REG_LAST : GP_REG_FIRST;\n"
            "          \t   mips_astra_quad_saves ? regno >= GP_REG_FIRST : regno <= GP_REG_LAST;\n"
            "          \t   mips_astra_quad_saves ? regno-- : regno++)\n"
            "          \tif (BITSET_P (mask, regno - GP_REG_FIRST))\n")
LOOP_NEW = ("                /* RAC2: -frac2-narrow-saves-below (with -mastra-quad-saves) takes the\n"
            "                   registers saved at the slot's full width first, then the narrower\n"
            "                   ones, so a register_precision-narrowed save sits below.  */\n"
            "                for (rac2_width_pass = 0;\n"
            "                     rac2_width_pass < (rac2_by_width ? 2 : 1);\n"
            "                     rac2_width_pass++)\n"
            "                for (regno = mips_astra_quad_saves ? GP_REG_LAST : GP_REG_FIRST;\n"
            "          \t   mips_astra_quad_saves ? regno >= GP_REG_FIRST : regno <= GP_REG_LAST;\n"
            "          \t   mips_astra_quad_saves ? regno-- : regno++)\n"
            "          \tif (BITSET_P (mask, regno - GP_REG_FIRST)\n"
            "          \t    && (! rac2_by_width\n"
            "          \t\t|| ((GET_MODE_SIZE (mips_reg_mode[regno])\n"
            "          \t\t     < GET_MODE_SIZE (mips_reg_mode[0])) == rac2_width_pass)))\n")
SCOPE_OLD = ("    int rac2_save_pass;\n"
             "    base_reg_rtx = 0;\n")
SCOPE_NEW = ("    int rac2_save_pass;\n"
             "    int rac2_width_pass;\n"
             "    int rac2_by_width = flag_rac2_narrow_saves_below && mips_astra_quad_saves != 0;\n"
             "    base_reg_rtx = 0;\n")
DEFINITION_OLD = "int flag_rac2_no_null_pointer_checks = 0;\n"
DEFINITION_NEW = ("int flag_rac2_no_null_pointer_checks = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, quad-slot GPR saves narrower than the slot go below.  */\n"
                  "int flag_rac2_narrow_saves_below = 0;\n")
OPTION_OLD = ('   "Do not run the null-pointer-check pass, as GCC 2.95"},\n'
              '  {"thread-jumps", &flag_thread_jumps, 1,\n')
OPTION_NEW = ('   "Do not run the null-pointer-check pass, as GCC 2.95"},\n'
              '  {"rac2-narrow-saves-below", &flag_rac2_narrow_saves_below, 1,\n'
              '   "Put quad-slot GPR saves narrower than the slot below the full-width ones"},\n'
              '  {"thread-jumps", &flag_thread_jumps, 1,\n')
DECLARATION_OLD = "extern int flag_rac2_no_null_pointer_checks;\n"
DECLARATION_NEW = ("extern int flag_rac2_no_null_pointer_checks;\n"
                   "\n"
                   "/* RAC2: quad-slot GPR saves narrower than the slot go below.  */\n"
                   "extern int flag_rac2_narrow_saves_below;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    mips, top, flags = root / "config/mips/mips.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (mips, top, flags)}
    if any("flag_rac2_narrow_saves_below" in text for text in sources.values()):
        raise ValueError("narrow-saves-below option already present")
    saves = replace_once(sources[mips], LOOP_OLD, LOOP_NEW, "GP save loop")
    saves = replace_once(saves, SCOPE_OLD, SCOPE_NEW, "save pass scope")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((mips, saves), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
