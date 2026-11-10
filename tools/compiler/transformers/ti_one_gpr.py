#!/usr/bin/env python3
"""On the R5900 a TImode value takes one general register in reload's class arithmetic too.

The sce-991111b stack redefines HARD_REGNO_NREGS so that a TImode value occupies one general
register on the R5900 (its GPRs are 128 bits wide), but CLASS_MAX_NREGS still divides the mode
by UNITS_PER_WORD and answers 2 for every non-FP class. Reload sizes its spill needs and its
reload registers by CLASS_MAX_NREGS, so each TImode reload counts as a two-register group: a
`por $rX,$0,$0` zero for a quadword store makes reload spill a pair ($v0 and $v1) and round-robin
through {v0, v1, a0, ...} from last_spill_reg + 1 in allocate_reload_reg, which hands the zero
$v1 where retail has $a0. This answers 1 for TImode in a class made only of general registers
(GR_REGS and the MIPS16 subsets before it in enum reg_class), so the two macros agree, as the
real EE compiler's evidently did; FP_REGS and the hi/lo classes keep their counts.

Retail witnesses: func_L23_002C38B0's four quadword zeros are a0, v0, a0, v0 with this and v1,
a0, v1, a0 without it, and ten more unmatched functions clear with `por $a0,$0,$0`
(func_002ABBB8, func_L00_0038ADD0, ...). Every matched function of all 28 programs compiles to
the same bytes with and without it. tests/test_ti_one_gpr.py covers the anchor and the
register choice; see docs/build/compiler-notes.md.

Usage: ti_one_gpr.py <gcc/config/mips/mips.h>
"""
import sys
from pathlib import Path

OLD = ("#define CLASS_MAX_NREGS(CLASS, MODE)\t\t\t\t\t\\\n"
       "  ((CLASS) == FP_REGS\t\t\t\t\t\t\t\\\n"
       "   ? (TARGET_FLOAT64\t\t\t\t\t\t\t\\\n"
       "      ? CLASS_UNITS (MODE, 8)\t\t\t\t\t\t\\\n"
       "      : 2 * CLASS_UNITS (MODE, 8))\t\t\t\t\t\\\n"
       "   : CLASS_UNITS (MODE, UNITS_PER_WORD))\n")
NEW = ("/* RAC2: on the R5900 a TImode value takes one general register, as\n"
       "   HARD_REGNO_NREGS says; a two-register group would make reload spill\n"
       "   a pair for each quadword reload (ti_one_gpr.py).  */\n"
       "#define CLASS_MAX_NREGS(CLASS, MODE)\t\t\t\t\t\\\n"
       "  ((CLASS) == FP_REGS\t\t\t\t\t\t\t\\\n"
       "   ? (TARGET_FLOAT64\t\t\t\t\t\t\t\\\n"
       "      ? CLASS_UNITS (MODE, 8)\t\t\t\t\t\t\\\n"
       "      : 2 * CLASS_UNITS (MODE, 8))\t\t\t\t\t\\\n"
       "   : (TARGET_MIPS5900 && (MODE) == TImode\t\t\t\t\\\n"
       "      && (int) (CLASS) <= (int) GR_REGS)\t\t\t\t\\\n"
       "   ? 1\t\t\t\t\t\t\t\t\t\\\n"
       "   : CLASS_UNITS (MODE, UNITS_PER_WORD))\n")


def patch(text: str) -> str:
    if "ti_one_gpr.py" in text:
        raise ValueError("CLASS_MAX_NREGS already patched")
    if text.count(OLD) != 1:
        raise ValueError(f"CLASS_MAX_NREGS: expected one definition, found {text.count(OLD)}")
    return text.replace(OLD, NEW)


def main() -> None:
    path = Path(sys.argv[1])
    path.write_text(patch(path.read_text(encoding="utf-8")), encoding="utf-8", newline="")
    print("CLASS_MAX_NREGS: TImode takes one general register on the R5900")


if __name__ == "__main__":
    main()
