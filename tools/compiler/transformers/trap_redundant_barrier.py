#!/usr/bin/env python3
"""reorg's redundant-insn search stops at a division guard or volatile asm, as retail's compiler does.

When `fill_slots_from_thread` (reorg.c) takes an insn from a branch's target for the delay
slot, it first asks `redundant_insn` whether an identical insn earlier on the branch's path
already computed the value; if so it skips the insn (the branch then jumps past it) instead of
copying it into the slot. The search walks backward from the branch and in this tree passes the
divide-by-zero guard of an integer division (a `trap_if` insn, `beql $rN,$0,1f; break 7`). Retail
never treats a load as redundant across such a guard: it copies the target's load into the slot.
This is that behaviour, unconditionally; it is not an option. It is the same rule as
trap_delay_barrier.py, for reorg's other backward search.

Retail witness. func_L00_002C2DE8 (708 bytes, 27 places) tests a frame counter twice,
`clock % 3` and then `clock % 5`. The branch over the first block (taken when the remainder is
nonzero) still holds the counter in $a0, loaded just above the `% 3` guard; retail fills the
branch's slot with the target's reload `lw $a0,clock($gp)` and branches to the `li $v0,5` after
it, where this tree drops the reload as redundant, steals the `li` and branches one word further
(3 words at every place). func_L18_002C4000 (496 bytes, 3 places) shows the same rule for a
register restore: its last `beqz`, after a `% 6` test, goes to the epilogue's `ld $s0` in retail;
this tree took the restore already in an earlier `bne` slot as redundant and branched one word
further (1 word).

Census of the 28 retail programs (branches whose target starts just after a load of the value
already held in the same register, i.e. where reorg skipped a redundant reload): 331 such skips
with no division guard between the earlier load and the branch, none with a guard between. The
converse, a branch slot holding a reload of the value its register already holds with a guard
between and no intervening store, occurs only in func_L00_002C2DE8 (27 placements). Of every
matched function in tools/build.py all, none compiled differently.

A volatile asm stops the search the same way. func_0030E8A8 (1,052 bytes, 28 places) ends one
arm with a `bc1f` to the epilogue past `ld $s0`, whose slot holds that restore, then a qcopy and
a `b` to the epilogue. Retail's `b` lands on the `ld $s0`; this tree took the slot's restore as
redundant across the qcopy and branched one word further. Census of the 28 programs (a branch
slot holding a $sp restore, then lq/sq, then a `b` to that restore or the word after it): 30 land
on the restore, none past it. No unit of src/ compiles differently.

The first backward scan of redundant_insn now ends, finding nothing, at a TRAP_IF insn or a
volatile asm.
tests/test_trap_redundant_barrier.py covers the transformer and the compiler output; see
docs/COMPILER-NOTES.md.

Usage: trap_redundant_barrier.py <gcc/reorg.c>
"""
import sys
from pathlib import Path

SCAN_OLD = ("  /* Scan backwards looking for a match.  */\n"
            "  for (trial = PREV_INSN (target); trial; trial = PREV_INSN (trial))\n"
            "    {\n"
            "      if (GET_CODE (trial) == CODE_LABEL)\n"
            "\treturn 0;\n"
            "\n"
            "      if (GET_RTX_CLASS (GET_CODE (trial)) != 'i')\n"
            "\tcontinue;\n"
            "\n"
            "      pat = PATTERN (trial);\n"
            "      if (GET_CODE (pat) == USE || GET_CODE (pat) == CLOBBER)\n"
            "\tcontinue;\n"
            "\n"
            "      if (GET_CODE (pat) == SEQUENCE)\n")
GUARD = ("      /* RAC2: retail's compiler does not look for a match across a\n"
         "\t division guard (trap_if) or a volatile asm.  */\n"
         "      if (GET_CODE (trial) == INSN\n"
         "\t  && (GET_CODE (pat) == TRAP_IF\n"
         "\t      || (GET_CODE (pat) != SEQUENCE && volatile_insn_p (pat))))\n"
         "\treturn 0;\n"
         "\n")
SCAN_NEW = SCAN_OLD.replace("      if (GET_CODE (pat) == SEQUENCE)\n",
                            GUARD + "      if (GET_CODE (pat) == SEQUENCE)\n")


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    if source.count(SCAN_OLD) != 1:
        raise ValueError("redundant_insn: expected one insertion point, "
                         f"found {source.count(SCAN_OLD)}")
    path.write_text(source.replace(SCAN_OLD, SCAN_NEW), encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
