#!/usr/bin/env python3
"""The opt-in `--r5900-swap-branch-slots` assembler profile of the SDK objects.

When the compiler leaves a branch's or call's delay slot unfilled, it writes the branch in
`.set reorder` mode and the assembler may fill the slot itself by swapping the branch with
the instruction before it (`append_insn`, gas/config/tc-mips.c). In this tree that swap never
happens: the last of its guards reads `(prev_pinfo && INSN_SYNC)`, a logical `&&` where the
bit test `&` was meant, so any previous instruction with any pinfo bit (all of them) refuses
the swap and the assembler emits a `nop`. The game's C, assembled like that, matches retail.

Sony's SDK libraries in the boot were assembled by a GNU as that tests the bit. Running the
unmodified output of the SDK compiler through the original GNU 2.10-ee-001003-1 assembler, or
through the DTL-S13010 build of GNU as 2.9-ee-991111, gives retail's bytes for these boot
functions from four SDK libraries, which this tree leaves a `nop` longer:
func_001253A8 (libcdvd, a volatile `lw` into a `jal` slot), func_0012E378 and func_0012E608
(libipu, volatile IPU register stores into `jal` slots), func_001307B0 (libmpeg, a volatile
store into a `jal` slot), func_0012CDB0 (libmpeg, the `sw ...($at)` half of three IPU_CTRL
store macros into `jal` slots) and func_0011C000 (the C library's printf, the `dsra` half of a
`truncdisi2` sign extension into the return slot). The compiler cannot fill those slots
itself: reorg refuses a volatile memory reference (resource_conflicts_p) and a two-word
pattern (define_delay's length 1). 989snd, which rac1 shows was assembled with SN's ps2eeas,
keeps the `nop` (func_00133988, `mflo` before `j $31`), so this is a per-object profile.

With the option the guard tests `prev_pinfo & INSN_SYNC`, as GNU 2.10-ee does; every other
swap rule is unchanged. Without it the assembler is unchanged. Pass it per file with
`-Wa,--r5900-swap-branch-slots` in config/cflags.txt. tests/test_swap_branch_slots.py checks
the transformer and the assembler output; see docs/build/compiler-notes.md.

Usage: swap_branch_slots.py <gas/config/tc-mips.c>
"""
import sys
from pathlib import Path

EDITS = (
    ("static int r5900_sign_bit_signed = 1;\n",
     "static int r5900_sign_bit_signed = 1;\n"
     "\n"
     "/* RAC2: nonzero for the SDK objects' assembler profile.  The swap guard\n"
     "   below tests the sync bit, as GNU 2.10-ee does, instead of `&&'.  */\n"
     "static int r5900_swap_branch_slots = 0;\n"),
    ("\t      || (prev_pinfo && INSN_SYNC))\n",
     "\t      || (r5900_swap_branch_slots\n"
     "\t\t  ? (prev_pinfo & INSN_SYNC) != 0\n"
     "\t\t  : (prev_pinfo && INSN_SYNC)))\n"),
    ("  {\"r5900-sign-bit\", required_argument, NULL, OPTION_R5900_SIGN_BIT},\n",
     "  {\"r5900-sign-bit\", required_argument, NULL, OPTION_R5900_SIGN_BIT},\n"
     "\n"
     "#define OPTION_R5900_SWAP_BRANCH_SLOTS (OPTION_MD_BASE + 40)\n"
     "  {\"r5900-swap-branch-slots\", no_argument, NULL, OPTION_R5900_SWAP_BRANCH_SLOTS},\n"),
    ("    case OPTION_R5900_SIGN_BIT:\n",
     "    case OPTION_R5900_SWAP_BRANCH_SLOTS:\n"
     "      r5900_swap_branch_slots = 1;\n"
     "      break;\n"
     "\n"
     "    case OPTION_R5900_SIGN_BIT:\n"),
    ("--r5900-sign-bit=signed|unsigned  select the isolated sign-bit seed [signed]\\n\\\n",
     "--r5900-sign-bit=signed|unsigned  select the isolated sign-bit seed [signed]\\n\\\n"
     "--r5900-swap-branch-slots  fill reorder-mode delay slots from the previous insn\\n\\\n"),
)


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    for old, _ in EDITS:
        if source.count(old) != 1:
            raise ValueError(f"tc-mips.c: expected one insertion point for {old.strip()!r}, "
                             f"found {source.count(old)}")
    for old, new in EDITS:
        source = source.replace(old, new)
    path.write_text(source, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
