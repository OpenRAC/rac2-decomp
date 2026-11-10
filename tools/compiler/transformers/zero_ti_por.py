#!/usr/bin/env python3
"""Add the opt-in -frac2-zero-ti-por: a plain C clear of 0($sp) keeps its materialised zero.

rac2_fold_zero_ti_store (fold_zero_ti_store.py, run before sched2 when optimizing) rewrites a
TImode zero store whose address is a bare register, `por $rd,$0,$0` ... `sq $rd,0(base)`, into
`sq $0,0(base)` when the zero register dies at the store and its `por` is close above it. That
models retail's clear, `sq $zero,0(reg)`: 396 such stores in 263 functions of retail's game
code (one place per catalogue row, the boot's from 0x26EA00), most likely an inline-asm macro.
Retail also stores a `por`-materialised zero at displacement 0: 183 stores in 153 functions.
Those are plain C zero stores, which the original compiler never folded, and every one of them
is to 0($sp), a local: none goes through another register. The address alone cannot tell the
two forms apart, since 82 of the 396 `sq $zero` stores (58 functions) are to 0($sp) too, so a
compilation unit says which its stack clears are: with this option rac2_fold_zero_ti_store
leaves a store addressed by $sp alone, which keeps its `por` and register-source `sq`, and
still folds a store through any other register (a pointer, or a global's address), which
retail always clears with `sq $zero`. Of the 153 functions, 131 hold no `sq $zero` clear, 21
also clear through another register (16 of them only a global, which plain C still reaches with
this), and one also clears 0($sp) with `sq $zero`, which no per-unit rule expresses. Nothing else
changes: sched1, reload and sched2 run as before, and -frac2-zero-ti-barrier keeps its
pre-reload selector (after reload it finds no `sq $0` at 0($sp)).

The option is off by default, enabled per compilation unit in config/cflags.txt, and
-fno-rac2-zero-ti-por disables it again. Without it every unit of src/ compiles to the same
objects; forced on everywhere it changes only the four units whose functions retail clears
0($sp) with `sq $zero`. Five functions are the measured witnesses, each a unit of its own.
tests/test_zero_ti_por.py covers the anchors, the default/disabled equality and authored zero
stores through $sp, a pointer, a global and in a loop, at zero and nonzero displacements, a
mixed function, shared and live zeros and the function-value case. See docs/build/compiler-notes.md.

Usage: zero_ti_por.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

PASS_OLD = ("      if (GET_CODE (XEXP (SET_DEST (set), 0)) != REG)\n"
            "        continue;\n"
            "\n"
            "      reg = SET_SRC (set);\n")
PASS_NEW = ("      if (GET_CODE (XEXP (SET_DEST (set), 0)) != REG)\n"
            "        continue;\n"
            "\n"
            "      /* RAC2: -frac2-zero-ti-por keeps the materialised zero of a store to\n"
            "         0($sp), as retail's plain C clears of a local have it (`por $rd,$0,$0'\n"
            "         ... `sq $rd,0($sp)'); a store through any other register still folds.  */\n"
            "      if (flag_rac2_zero_ti_por\n"
            "          && REGNO (XEXP (SET_DEST (set), 0)) == STACK_POINTER_REGNUM)\n"
            "        continue;\n"
            "\n"
            "      reg = SET_SRC (set);\n")
DEFINITION_OLD = "int flag_rac2_zero_ti_barrier = 0;\n"
DEFINITION_NEW = ("int flag_rac2_zero_ti_barrier = 0;\n"
                  "/* Opt-in: keep the materialised zero of a plain C quadword clear of 0($sp). */\n"
                  "int flag_rac2_zero_ti_por = 0;\n")
OPTION_OLD = ('   "Model the RAC2 quadword-clear scheduling barrier"},\n'
              '  {"schedule-insns", &flag_schedule_insns, 1,\n')
OPTION_NEW = ('   "Model the RAC2 quadword-clear scheduling barrier"},\n'
              '  {"rac2-zero-ti-por", &flag_rac2_zero_ti_por, 1,\n'
              '   "Keep the materialised zero of a quadword zero store to 0($sp)"},\n'
              '  {"schedule-insns", &flag_schedule_insns, 1,\n')
DECLARATION_OLD = "extern int flag_rac2_zero_ti_barrier;\n"
DECLARATION_NEW = ("extern int flag_rac2_zero_ti_barrier;\n"
                   "extern int flag_rac2_zero_ti_por;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    mips, top, flags = root / "config/mips/mips.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (mips, top, flags)}
    if any("flag_rac2_zero_ti_por" in text for text in sources.values()):
        raise ValueError("zero-ti-por option already present")
    fold = replace_once(sources[mips], PASS_OLD, PASS_NEW, "rac2_fold_zero_ti_store")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((mips, fold), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
