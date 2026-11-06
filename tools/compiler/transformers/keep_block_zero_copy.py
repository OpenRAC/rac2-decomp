#!/usr/bin/env python3
"""Add the opt-in -frac2-keep-block-zero-copy: cse keeps a copy of a register zeroed in its block.

Stock cse_insn (cse.c) puts a register copy `(set (reg B) (reg A))` in the equivalence class
of A, and when A is known to hold CONST_INT 0 the constant wins: MIPS CONST_COSTS gives every
CONST_INT cost 0 and a pseudo costs 1, so the copy becomes `B = 0` (`move B,$0`).
func_002F7320 (132 bytes, 28 places) shows the retail compiler kept such a copy: its entry is
`daddu $t1,$zero,$zero ... daddu $a3,$t1,$zero` for `int result = 0; int i = result;`. The
live copy gives result=0 a dependent, so sched1 puts it before the argument copies and the
allocation becomes retail's (a0 value, a3 i, t0 base, t1 result).

With this option cse keeps the register source of a pseudo-to-pseudo copy whose known value is
CONST_INT 0 when that register is set earlier in the same basic block (no label, jump or call
between the two); the REG_EQUAL note cse adds still tells loop.c the copy is 0. A zero learnt
in an earlier block on the cse path is folded as before: forced on in every game unit, the
same-block limit leaves func_00349680 (jump1's duplicated loop-exit copy `lo = hi`, retail
`move $18,$0`) unchanged, and only func_002F7320's unit changes.

The option is off by default, enabled per unit in config/cflags.txt, and
-fno-rac2-keep-block-zero-copy disables it again. tests/test_keep_block_zero_copy.py covers
the anchors, the default/disabled equality, the kept copy and a cross-block control.
See docs/COMPILER-NOTES.md.

Usage: keep_block_zero_copy.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

CHOICE_OLD = ("      /* If this was an indirect jump insn, a known label will really be\n"
              "\t cheaper even though it looks more expensive.  */\n")
CHOICE_NEW = ("      /* RAC2: -frac2-keep-block-zero-copy keeps a pseudo-to-pseudo copy whose\n"
              "\t value is known to be 0 when its source is set earlier in this block.  */\n"
              "      if (flag_rac2_keep_block_zero_copy\n"
              "\t  && sets[i].src && GET_CODE (sets[i].src) == REG\n"
              "\t  && REGNO (sets[i].src) >= FIRST_PSEUDO_REGISTER\n"
              "\t  && GET_CODE (dest) == REG && REGNO (dest) >= FIRST_PSEUDO_REGISTER\n"
              "\t  && src_const == const0_rtx\n"
              "\t  && rac2_set_in_block_p (insn, sets[i].src))\n"
              "\tsrc = sets[i].src, src_cost = -1;\n"
              "\n" + CHOICE_OLD)
HELPER_OLD = "\nstatic void\ncse_insn (insn, libcall_insn)"
HELPER_NEW = ("\n/* RAC2: nonzero if REG is set by an insn between the start of INSN's basic\n"
              "   block (a label, jump or call) and INSN.  */\n"
              "static int\n"
              "rac2_set_in_block_p (insn, reg)\n"
              "     rtx insn, reg;\n"
              "{\n"
              "  rtx p;\n"
              "\n"
              "  for (p = PREV_INSN (insn); p; p = PREV_INSN (p))\n"
              "    {\n"
              "      if (GET_CODE (p) == CODE_LABEL || GET_CODE (p) == JUMP_INSN\n"
              "\t  || GET_CODE (p) == CALL_INSN)\n"
              "\treturn 0;\n"
              "      if (GET_CODE (p) == INSN && reg_set_p (reg, p))\n"
              "\treturn 1;\n"
              "    }\n"
              "  return 0;\n"
              "}\n" + HELPER_OLD)
DEFINITION_OLD = "int flag_rac2_narrow_saves_below = 0;\n"
DEFINITION_NEW = ("int flag_rac2_narrow_saves_below = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, cse keeps a copy of a register zeroed in its block.  */\n"
                  "int flag_rac2_keep_block_zero_copy = 0;\n")
OPTION_OLD = '   "Put quad-slot GPR saves narrower than the slot below the full-width ones"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-keep-block-zero-copy", &flag_rac2_keep_block_zero_copy, 1,\n'
              '   "Keep a copy of a register set to zero earlier in the same block"},\n')
DECLARATION_OLD = "extern int flag_rac2_narrow_saves_below;\n"
DECLARATION_NEW = ("extern int flag_rac2_narrow_saves_below;\n"
                   "\n"
                   "/* RAC2: cse keeps a copy of a register zeroed in its block.  */\n"
                   "extern int flag_rac2_keep_block_zero_copy;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    cse, top, flags = root / "cse.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="utf-8") for path in (cse, top, flags)}
    if any("flag_rac2_keep_block_zero_copy" in text for text in sources.values()):
        raise ValueError("keep-block-zero-copy option already present")
    folded = replace_once(sources[cse], CHOICE_OLD, CHOICE_NEW, "cse source choice")
    folded = replace_once(folded, HELPER_OLD, HELPER_NEW, "cse_insn definition")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((cse, folded), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
