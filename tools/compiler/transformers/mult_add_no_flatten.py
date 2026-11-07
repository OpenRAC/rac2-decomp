#!/usr/bin/env python3
"""Add the opt-in -frac2-mult-add-no-flatten: loop's b*m+a expansion keeps its tree shape.

expand_mult_add (expmed.c) builds the tree `b*m + a` for loop.c's emit_iv_add_mult (a reduced
giv's initial value) and folds it. In this Cygnus-based 2.9-ee tree, fold (fold-const.c) runs
the CYGNUS LOCAL reduce_expression_tree_depth on every PLUS when optimizing with
-fschedule-insns, so `x*16 + (i*400 + (D + -16))` becomes `(x*16 + i*400) + (D + -16)`.
func_L20_0039F968 (996 bytes) shows the retail compiler kept the nested form: its history
copy computes `D-16; i*400 + (D-16); x*16 + that`. FSF GCC 2.95.2 (no CYGNUS LOCAL code)
gives that shape from the same giv; this repo's cc1 gives the flattened one.

With this option the fold calls inside expand_mult_add run with flag_schedule_insns clear, so
reduce_expression_tree_depth is skipped there and nowhere else. Forced on in every game unit,
no matched unit changes; only func_L20_0039F968's unit (and two nonmatching notes) change.

The option is off by default, enabled per unit in config/cflags.txt, and
-fno-rac2-mult-add-no-flatten disables it again. tests/test_mult_add_no_flatten.py covers
the anchors, the default/disabled equality and the kept grouping. See docs/COMPILER-NOTES.md.

Usage: mult_add_no_flatten.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

EXPAND_OLD = ("  tree type = type_for_mode (mode, unsignedp);\n"
              "  tree add_type = (GET_MODE (add) == VOIDmode\n"
              "\t\t   ? type : type_for_mode (GET_MODE (add), unsignedp));\n"
              "  tree result =  fold (build (PLUS_EXPR, type,\n"
              "\t\t\t      fold (build (MULT_EXPR, type,\n"
              "\t\t\t\t\t   make_tree (type, x),\n"
              "\t\t\t\t\t   make_tree (type, mult))),\n"
              "\t\t\t      make_tree (add_type, add)));\n"
              "\n"
              "  return expand_expr (result, target, VOIDmode, 0);\n")
EXPAND_NEW = ("  tree type = type_for_mode (mode, unsignedp);\n"
              "  tree add_type = (GET_MODE (add) == VOIDmode\n"
              "\t\t   ? type : type_for_mode (GET_MODE (add), unsignedp));\n"
              "  tree result;\n"
              "  /* RAC2: -frac2-mult-add-no-flatten folds this tree without the\n"
              "     CYGNUS LOCAL reduce_expression_tree_depth (fold-const.c), which\n"
              "     only runs while flag_schedule_insns is set.  */\n"
              "  int rac2_saved_schedule_insns = flag_schedule_insns;\n"
              "\n"
              "  if (flag_rac2_mult_add_no_flatten)\n"
              "    flag_schedule_insns = 0;\n"
              "  result =  fold (build (PLUS_EXPR, type,\n"
              "\t\t\t      fold (build (MULT_EXPR, type,\n"
              "\t\t\t\t\t   make_tree (type, x),\n"
              "\t\t\t\t\t   make_tree (type, mult))),\n"
              "\t\t\t      make_tree (add_type, add)));\n"
              "  flag_schedule_insns = rac2_saved_schedule_insns;\n"
              "\n"
              "  return expand_expr (result, target, VOIDmode, 0);\n")
DEFINITION_OLD = "int flag_rac2_wide_saves_below = 0;\n"
DEFINITION_NEW = ("int flag_rac2_wide_saves_below = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, expand_mult_add folds without tree flattening.  */\n"
                  "int flag_rac2_mult_add_no_flatten = 0;\n")
OPTION_OLD = '   "Give a GPR saved in TImode a 16-byte slot below the 8-byte ones"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-mult-add-no-flatten", &flag_rac2_mult_add_no_flatten, 1,\n'
              '   "Keep the tree shape of loop giv initial values (no tree flattening)"},\n')
DECLARATION_OLD = "extern int flag_rac2_wide_saves_below;\n"
DECLARATION_NEW = ("extern int flag_rac2_wide_saves_below;\n"
                   "\n"
                   "/* RAC2: expand_mult_add folds without tree flattening.  */\n"
                   "extern int flag_rac2_mult_add_no_flatten;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    expmed, top, flags = root / "expmed.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (expmed, top, flags)}
    if any("flag_rac2_mult_add_no_flatten" in text for text in sources.values()):
        raise ValueError("mult-add-no-flatten option already present")
    expand = replace_once(sources[expmed], EXPAND_OLD, EXPAND_NEW, "expand_mult_add body")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((expmed, expand), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
