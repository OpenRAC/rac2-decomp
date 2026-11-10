#!/usr/bin/env python3
"""Every `li.d` into a GPR inline by default; `--r5900-pool-li-d` restores the pooled form.

cc1 writes a DFmode constant bound for a general register (a double argument of a variadic
call such as `printf(fmt, 0.1f)` under -msingle-float, where the double travels in one
64-bit GPR) as the macro `li.d $r,<value>` (mips_move_2words). This tree's gas
(gas/config/tc-mips.c, the 'F' operand of M_LI_D) builds it inline only when each 32-bit half
has a zero 16-bit chunk; any other value goes to .lit8 and is loaded with `lui $at` plus
`ld $r,%lo(...)($at)`.

The game's own code never pools one: (double)0.1f, 0x3FB99999A0000000, whose high half has no
zero chunk, is built in $a1 as `ori 0xFEE6; dsll 17; ori 0xCCCD; dsll 29`, load_register's
shifted dli form of the whole 64-bit value, in func_002ADB78 (boot) and its 27 level copies
(func_L00_00321878). The double constants of func_002D36A0 and its level copies
((double)1e-4f, 0x3F1A36E2E0000000) and of func_00284268 have the same form, and no compiled
game code in the boot or the levels loads a .lit8 value (every `lui $at`/`ld` pair reads the
scratchpad in hand-written blocks). The SDK's objects do pool: func_0011C090 (libc's
exponent formatter, matched with the SDK profile) loads 0.1 and 10.0 from .lit8, and match
only that way.

So the game code's form is the default: a 64-bit ISA takes the whole value into imm_expr for
every `li.d` into a GPR, and M_LI_D builds it with load_register; the FPR forms ('L') and
32-bit ISAs are unchanged. `--r5900-pool-li-d` restores the archive's pooling, and
tools/build.py passes it to every unit of the SDK profile (`sdk` flags in config/cflags.txt),
so the SDK's objects assemble as before. `--r5900-inline-li-d` states the default explicitly.
It is the li.d counterpart of patch 0027's inline `li.s`.
tests/test_inline_li_d.py checks the transformer and the assembler output; see
docs/build/compiler-notes.md.

Usage: inline_li_d.py <gas/config/tc-mips.c> (after swap_branch_slots.py)
"""
import sys
from pathlib import Path

EDITS = [
    ("static int r5900_swap_branch_slots = 0;\n",
     "static int r5900_swap_branch_slots = 0;\n"
     "\n"
     "/* RAC2: the game code's form, the default: every li.d into a 64-bit GPR\n"
     "   is built inline, never pooled in .lit8.  --r5900-pool-li-d (the SDK\n"
     "   profile) clears it.  */\n"
     "static int r5900_inline_li_d = 1;\n"),
    ("\t\telse if (length > 4\n"
     "\t\t\t && ((temp[0] == 0 && temp[1] == 0)\n"
     "\t\t\t     || (temp[2] == 0 && temp[3] == 0))\n"
     "\t\t\t && ((temp[4] == 0 && temp[5] == 0)\n"
     "\t\t\t     || (temp[6] == 0 && temp[7] == 0)))\n",
     "\t\telse if (length > 4\n"
     "\t\t\t && ((r5900_inline_li_d && *args == 'F' && mips_opts.isa >= 3)\n"
     "\t\t\t     || (((temp[0] == 0 && temp[1] == 0)\n"
     "\t\t\t\t  || (temp[2] == 0 && temp[3] == 0))\n"
     "\t\t\t\t && ((temp[4] == 0 && temp[5] == 0)\n"
     "\t\t\t\t     || (temp[6] == 0 && temp[7] == 0)))))\n"),
    ("  {\"r5900-swap-branch-slots\", no_argument, NULL, OPTION_R5900_SWAP_BRANCH_SLOTS},\n",
     "  {\"r5900-swap-branch-slots\", no_argument, NULL, OPTION_R5900_SWAP_BRANCH_SLOTS},\n"
     "\n"
     "#define OPTION_R5900_INLINE_LI_D (OPTION_MD_BASE + 41)\n"
     "  {\"r5900-inline-li-d\", no_argument, NULL, OPTION_R5900_INLINE_LI_D},\n"
     "#define OPTION_R5900_POOL_LI_D (OPTION_MD_BASE + 42)\n"
     "  {\"r5900-pool-li-d\", no_argument, NULL, OPTION_R5900_POOL_LI_D},\n"),
    ("    case OPTION_R5900_SWAP_BRANCH_SLOTS:\n",
     "    case OPTION_R5900_INLINE_LI_D:\n"
     "      r5900_inline_li_d = 1;\n"
     "      break;\n"
     "\n"
     "    case OPTION_R5900_POOL_LI_D:\n"
     "      r5900_inline_li_d = 0;\n"
     "      break;\n"
     "\n"
     "    case OPTION_R5900_SWAP_BRANCH_SLOTS:\n"),
    ("--r5900-swap-branch-slots  fill reorder-mode delay slots from the previous insn\\n\\\n",
     "--r5900-swap-branch-slots  fill reorder-mode delay slots from the previous insn\\n\\\n"
     "--r5900-inline-li-d  build every li.d into a 64-bit GPR inline (default)\\n\\\n"
     "--r5900-pool-li-d  pool li.d values without zero chunks in .lit8 (SDK)\\n\\\n"),
]


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    for old, _ in EDITS:
        if source.count(old) != 1:
            raise ValueError(f"tc-mips.c: expected one insertion point for {old.strip()[:60]!r}, "
                             f"found {source.count(old)}")
    for old, new in EDITS:
        source = source.replace(old, new)
    path.write_text(source, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
