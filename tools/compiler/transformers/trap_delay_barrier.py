#!/usr/bin/env python3
"""reorg's backward delay-slot search stops at a division guard, as retail's compiler does.

`fill_simple_delay_slots` (reorg.c) fills the delay slot of a call, or of any insn whose slot
was not filled from its own block, by scanning backward from it for an independent insn; the
scan stops only at a label, a jump or an insn that already holds a slot (`stop_search_p`). On
the R5900 an integer division is preceded by its divide-by-zero guard, a `trap_if` insn whose
template is `beql $rN,$0,1f; break 7`, and this tree lets the scan pass it: an argument setup
placed before the guard is moved into the call's slot. Retail never does that, so the real EE
compiler ended the search at the guard. This is that behaviour, unconditionally; it is not an
option.

Retail witnesses. func_L00_002CB3A8 (26,432 bytes, 11 places, the hero state decider), whose
case 0x40 calls func_L00_002D2168 twice, each after `(n * k / m + c) % n`: retail sets the
first argument `li $a0,2` (and `li $a0,3`) in the delay slot of the preceding `beq` (stolen
from the call's block by fill_eager_delay_slots) and leaves the `jal` slot empty; this tree
puts the `li` into the `jal` slot first (fill_simple runs before fill_eager), so the `beq`
takes an insn from its target and the `jal` slot is filled (12 instructions differ). With the
guard as a barrier the call finds nothing it may take below the guard (`mfhi` and the
divisions are not eligible) and both blocks come out as in retail. func_L12_002CF7B0 and
func_L11_002DE9E0, members of that family, match with it.

A census of the 28 retail programs finds 68 calls whose slot is a `nop` although an
independent argument setup (`li`/`move`/`addiu` into $a0-$t3, its register untouched up to the
call) stands before a division guard in the same block, which this tree's search would have
moved into the slot (e.g. L00 0x002A4448 `li $a0,0x755D`, 0x00354924 `li $a0,0x2E0C`, the
same code in every level). Of every matched function in tools/build.py all, none compiled
differently with the barrier.

The backward scan of fill_simple_delay_slots now stops at a TRAP_IF insn, as it stops at a
jump. tests/test_trap_delay_barrier.py covers the transformer and the compiler output; see
docs/build/compiler-notes.md.

Usage: trap_delay_barrier.py <gcc/reorg.c>
"""
import sys
from pathlib import Path

SCAN_OLD = ("\t  for (trial = prev_nonnote_insn (insn); ! stop_search_p (trial, 1);\n"
            "\t       trial = next_trial)\n"
            "\t    {\n"
            "\t      next_trial = prev_nonnote_insn (trial);\n"
            "\n"
            "\t      /* This must be an INSN or CALL_INSN.  */\n")
SCAN_NEW = ("\t  for (trial = prev_nonnote_insn (insn); ! stop_search_p (trial, 1);\n"
            "\t       trial = next_trial)\n"
            "\t    {\n"
            "\t      next_trial = prev_nonnote_insn (trial);\n"
            "\n"
            "\t      /* RAC2: retail's compiler ends the backward search at a\n"
            "\t\t division guard (trap_if), as at a jump.  */\n"
            "\t      if (GET_CODE (trial) == INSN\n"
            "\t\t  && GET_CODE (PATTERN (trial)) == TRAP_IF)\n"
            "\t\tbreak;\n"
            "\n"
            "\t      /* This must be an INSN or CALL_INSN.  */\n")


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    if source.count(SCAN_OLD) != 1:
        raise ValueError("fill_simple_delay_slots: expected one insertion point, "
                         f"found {source.count(SCAN_OLD)}")
    path.write_text(source.replace(SCAN_OLD, SCAN_NEW), encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
