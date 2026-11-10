#!/usr/bin/env python3
"""Add the opt-in -frac2-wide-saves-below: a GPR saved in TImode gets a 16-byte slot.

Without -mastra-quad-saves every GPR save slot is GET_MODE_SIZE (mips_reg_mode[0]) = 8 bytes
wide, but save_restore_insns (mips.c) saves a register in the widest mode the function writes
it in (mips_check_reg_mode), so a callee-saved register holding a TImode value is saved with
`sq` into an 8-byte slot. `sq` ignores the low four address bits, so that save overwrites a
neighbouring one. compute_frame_size never sees the modes: only the prologue scans them.

Retail has one such frame among 7,980 framed functions: func_L02_00411D18, whose $s2 holds a
TImode value, saves `sq $s2,0x620` below `sd $s0,0x630`, `sd $s1,0x638` and $s3..$ra at
0x640..0x670, restores them in register order, and has a 0x690-byte frame. With this option,
in a unit without -mastra-quad-saves, a saved GPR whose save is wider than a slot takes a
16-byte slot at the bottom of the GPR save area, the others keep 8-byte slots above it in
register order, and compute_frame_size adds the 8 bytes per such register. The layout of one
wide register is measured; the order of two or more is not, so they simply ascend.

The frame size fixes the arg-pointer offsets during reload, before the prologue exists, so the
mask cannot wait for the prologue's scan. While reload runs it is taken from the insns, whose
pseudos alter_reg has renumbered to their hard registers (or, if not yet, through
reg_renumber), together with the modes mips_reg_mode and register_precision already give; the
mask of the last such call (verify_initial_elim_offsets aborts if reload_as_needed moved it)
is kept for the rest of the function. A save the prologue then finds wider than its slot is a
hard error, never an overlapping store. mips_reg_mode stays widened for the rest of the unit,
as without the option, so a function that needs this belongs in a unit of its own.

The option is off by default, enabled per unit in config/cflags.txt, has no effect with
-mastra-quad-saves (every slot is already 16 bytes), and -fno-rac2-wide-saves-below disables it
again. tests/test_wide_saves_below.py covers the anchors, the default/disabled equality, wide
frames with and without stack arguments, and controls. See docs/build/compiler-notes.md.

Usage: wide_saves_below.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

HELPERS_OLD = ("HOST_WIDE_INT\n"
               "compute_frame_size (size)\n"
               "     HOST_WIDE_INT size;\t/* # of var. bytes allocated */\n"
               "{\n")
HELPERS_NEW = ("/* RAC2: -frac2-wide-saves-below.  Without -mastra-quad-saves a GPR save\n"
               "   slot is GET_MODE_SIZE (mips_reg_mode[0]) bytes, but a register the\n"
               "   function writes in TImode is saved in TImode.  With the option such a\n"
               "   register takes a 16-byte slot at the bottom of the GPR save area.  The\n"
               "   mask is taken while reload runs, since the frame size fixes the\n"
               "   arg-pointer offsets then, and kept for the rest of the function.  */\n"
               "\n"
               "static long rac2_wide_store_mask;\n"
               "static long rac2_wide_kept_mask;\n"
               "static tree rac2_wide_kept_decl;\n"
               "\n"
               "static int\n"
               "rac2_wide_saves_p ()\n"
               "{\n"
               "  return (flag_rac2_wide_saves_below && TARGET_MIPS5900 && TARGET_64BIT\n"
               "\t  && ! mips_astra_quad_saves && ! TARGET_MIPS16 && ! mips_entry);\n"
               "}\n"
               "\n"
               "/* note_stores callback: a GPR set in a mode wider than a save slot.  A\n"
               "   pseudo that alter_reg has not renumbered yet stands for its hard reg.  */\n"
               "\n"
               "static void\n"
               "rac2_note_wide_store (x, set)\n"
               "     rtx x;\n"
               "     rtx set;\n"
               "{\n"
               "  int regno;\n"
               "\n"
               "  if (GET_CODE (x) != REG)\n"
               "    return;\n"
               "  regno = REGNO (x);\n"
               "  if (regno >= FIRST_PSEUDO_REGISTER)\n"
               "    regno = reg_renumber != 0 ? reg_renumber[regno] : -1;\n"
               "  if (regno >= GP_REG_FIRST && regno <= GP_REG_LAST\n"
               "      && GET_MODE_SIZE (GET_MODE (x)) > GET_MODE_SIZE (mips_reg_mode[0]))\n"
               "    rac2_wide_store_mask |= 1L << (regno - GP_REG_FIRST);\n"
               "}\n"
               "\n"
               "/* The registers of MASK whose saves get a 16-byte slot: those the prologue\n"
               "   will save wider than mips_reg_mode[0], as save_restore_insns works the\n"
               "   modes out (stores, the unit's mips_reg_mode, register_precision).  */\n"
               "\n"
               "static long\n"
               "rac2_wide_saves (mask)\n"
               "     long mask;\n"
               "{\n"
               "  rtx insn;\n"
               "  tree attr;\n"
               "  int regno;\n"
               "  long wide;\n"
               "\n"
               "  if (reload_completed && rac2_wide_kept_decl == current_function_decl)\n"
               "    return rac2_wide_kept_mask & mask;\n"
               "  rac2_wide_store_mask = 0;\n"
               "  push_topmost_sequence ();\n"
               "  for (insn = get_insns (); insn != NULL_RTX; insn = NEXT_INSN (insn))\n"
               "    if (GET_RTX_CLASS (GET_CODE (insn)) == 'i')\n"
               "      note_stores (PATTERN (insn), rac2_note_wide_store);\n"
               "  pop_topmost_sequence ();\n"
               "  wide = rac2_wide_store_mask;\n"
               "  for (regno = GP_REG_FIRST; regno <= GP_REG_LAST; regno++)\n"
               "    if (GET_MODE_SIZE (mips_reg_mode[regno]) > GET_MODE_SIZE (mips_reg_mode[0]))\n"
               "      wide |= 1L << (regno - GP_REG_FIRST);\n"
               "  for (attr = lookup_attribute (\"register_precision\",\n"
               "\t\t\t       DECL_MACHINE_ATTRIBUTES (current_function_decl));\n"
               "       attr; attr = TREE_CHAIN (attr))\n"
               "    {\n"
               "      char *reg_expr = IDENTIFIER_POINTER (TREE_VALUE (TREE_VALUE (attr)));\n"
               "      tree reg_length = TREE_VALUE (TREE_CHAIN (TREE_VALUE (attr)));\n"
               "      int j = decode_reg_name (reg_expr);\n"
               "\n"
               "      if (j > 0 && j <= GP_REG_LAST)\n"
               "\t{\n"
               "\t  if (TREE_INT_CST_LOW (reg_length) == 128)\n"
               "\t    wide |= 1L << (j - GP_REG_FIRST);\n"
               "\t  else\n"
               "\t    wide &= ~(1L << (j - GP_REG_FIRST));\n"
               "\t}\n"
               "    }\n"
               "  if (! reload_completed)\n"
               "    {\n"
               "      rac2_wide_kept_mask = wide;\n"
               "      rac2_wide_kept_decl = current_function_decl;\n"
               "    }\n"
               "  return wide & mask;\n"
               "}\n"
               "\n" + HELPERS_OLD)
SIZE_OLD = ("  gp_reg_rounded = MIPS_STACK_ALIGN (gp_reg_size);\n"
            "  total_size += gp_reg_rounded + MIPS_STACK_ALIGN (fp_reg_size);\n")
SIZE_NEW = ("  /* RAC2: -frac2-wide-saves-below: a 16-byte slot for each wide save.  */\n"
            "  if (rac2_wide_saves_p ())\n"
            "    {\n"
            "      long rac2_wide = rac2_wide_saves (mask);\n"
            "\n"
            "      for (; rac2_wide; rac2_wide &= rac2_wide - 1)\n"
            "\tgp_reg_size += GET_MODE_SIZE (TImode) - GET_MODE_SIZE (mips_reg_mode[0]);\n"
            "    }\n"
            "\n" + SIZE_OLD)
SCOPE_OLD = ("    int rac2_by_width = flag_rac2_narrow_saves_below && mips_astra_quad_saves != 0;\n"
             "    base_reg_rtx = 0;\n")
SCOPE_NEW = ("    int rac2_by_width = flag_rac2_narrow_saves_below && mips_astra_quad_saves != 0;\n"
             "    int rac2_wide_on = rac2_wide_saves_p ();\n"
             "    long rac2_wide = 0;\n"
             "    HOST_WIDE_INT rac2_wide_offset = 0, rac2_narrow_offset = 0;\n"
             "    base_reg_rtx = 0;\n")
START_OLD = ("                /* RAC2: -frac2-narrow-saves-below (with -mastra-quad-saves) takes the\n")
START_NEW = ("                /* RAC2: -frac2-wide-saves-below: the wide saves take 16-byte slots\n"
             "                   up from the bottom of the GPR area (end_offset), the others\n"
             "                   8-byte slots above them, both in register order.  */\n"
             "                if (rac2_wide_on)\n"
             "                  {\n"
             "                    long rac2_w;\n"
             "\n"
             "                    rac2_wide = rac2_wide_saves (mask);\n"
             "                    rac2_wide_offset = rac2_narrow_offset = end_offset;\n"
             "                    for (rac2_w = rac2_wide; rac2_w; rac2_w &= rac2_w - 1)\n"
             "                      rac2_narrow_offset += GET_MODE_SIZE (TImode);\n"
             "                  }\n" + START_OLD)
SLOT_OLD = ("          \t\t     < GET_MODE_SIZE (mips_reg_mode[0])) == rac2_width_pass)))\n"
            "          \t  {\n")
SLOT_NEW = (SLOT_OLD +
            "          \t    if (rac2_wide_on)\n"
            "          \t      {\n"
            "          \t\tint rac2_in_wide = BITSET_P (rac2_wide, regno - GP_REG_FIRST);\n"
            "\n"
            "          \t\tif (store_p\n"
            "          \t\t    && (GET_MODE_SIZE (mips_reg_mode[regno])\n"
            "          \t\t\t> (rac2_in_wide ? GET_MODE_SIZE (TImode)\n"
            "          \t\t\t   : GET_MODE_SIZE (mips_reg_mode[0]))))\n"
            "          \t\t  error (\"-frac2-wide-saves-below: %s is saved wider than the slot reload gave it\",\n"
            "          \t\t\t reg_names[regno]);\n"
            "          \t\tif (rac2_in_wide)\n"
            "          \t\t  gp_offset = rac2_wide_offset,\n"
            "          \t\t  rac2_wide_offset += GET_MODE_SIZE (TImode);\n"
            "          \t\telse\n"
            "          \t\t  gp_offset = rac2_narrow_offset,\n"
            "          \t\t  rac2_narrow_offset += GET_MODE_SIZE (mips_reg_mode[0]);\n"
            "          \t      }\n")
DEFINITION_OLD = "int flag_rac2_sticky_volatile_refs = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sticky_volatile_refs = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, a GPR saved in TImode gets a 16-byte slot at the bottom.  */\n"
                  "int flag_rac2_wide_saves_below = 0;\n")
OPTION_OLD = '   "Keep a volatile reference marked across later memory references"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-wide-saves-below", &flag_rac2_wide_saves_below, 1,\n'
              '   "Give a GPR saved in TImode a 16-byte slot below the 8-byte ones"},\n')
DECLARATION_OLD = "extern int flag_rac2_sticky_volatile_refs;\n"
DECLARATION_NEW = ("extern int flag_rac2_sticky_volatile_refs;\n"
                   "\n"
                   "/* RAC2: a GPR saved in TImode gets a 16-byte slot at the bottom.  */\n"
                   "extern int flag_rac2_wide_saves_below;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    mips, top, flags = root / "config/mips/mips.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (mips, top, flags)}
    if any("flag_rac2_wide_saves_below" in text for text in sources.values()):
        raise ValueError("wide-saves-below option already present")
    saves = replace_once(sources[mips], HELPERS_OLD, HELPERS_NEW, "frame-size helpers")
    saves = replace_once(saves, SIZE_OLD, SIZE_NEW, "GP save area size")
    saves = replace_once(saves, SCOPE_OLD, SCOPE_NEW, "save pass scope")
    saves = replace_once(saves, START_OLD, START_NEW, "GP slot bases")
    saves = replace_once(saves, SLOT_OLD, SLOT_NEW, "GP slot per register")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((mips, saves), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
