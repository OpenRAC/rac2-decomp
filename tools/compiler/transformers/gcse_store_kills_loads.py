#!/usr/bin/env python3
"""gcse lets every memory store kill every load, as GCC 2.95.3's gcse does.

This tree's gcse (gcse.c, Cygnus) keeps a list of the stores in each block (modify_mem_list)
and asks alias analysis, through mems_conflict_for_gcse_p and true_dependence, whether a store
kills a load. GCC 2.95.3's gcse only records that a block stores to memory (mem_set_in_block,
mem_first_set, mem_last_set): any store kills every load. With alias analysis, a load of a
global scalar survives stores to a different global, so gcse reuses it across them; retail
reloads it, so the real EE compiler had 2.95's model. This is that model, unconditionally; it
is not an option.

Retail witnesses. func_L19_002C44F8 (15,824 bytes, Grelbin's hero state entry): each of its
inlined statistics updates

    if (stats->count < 0xFFFF) stats->count++;
    if (D_001A7390 > stats->maximum) stats->maximum = D_001A7390;
    stats->levels = (stats->levels | (1u << D_001A79F0)) | 0x80000000u;

loads D_001A7390 and D_001A79F0 again after every store to the record (lui/lw at each use,
even across consecutive records and after the stores to the hero), where alias analysis copies
the first load into a register and reuses it (a `move` in the branch slot and a longer live
range for the copy). Under 2.95's model the function goes from 3,879 to 3,901 of 3,956 opcodes
in place (3,560 to 3,662 with registers) and every statistics block takes retail's shape.

The same holds inside one record, where alias analysis tells the offsets of one base apart:
func_L00_002CB3A8 (26,432 bytes, 11 places, the hero state decider) reloads the state word
0x2294 after the byte store to 0x1239 on the store's path only (PRE's insertion for a load
the store kills), 0x31C after the 0x1E0/0x1D0 stores, 0x34E after 0x1EE and 0x1B4 after
0xC20; no access spelling (struct fields, char-array index, pointer casts, local pointers)
gets that from alias analysis, and under 2.95's model all four come out as in retail (26,404
to 26,428 bytes). func_L19_002CAAB0 (19,192 bytes), a member of that family, reaches all
4,798 instructions with registers. -dG dumps and an instrumented cc1 show the surviving loads
are gcse's availability decisions, not cse's or reload's.

Of every matched function in tools/build.py all, exactly one compiled differently under this
model: func_L00_00310048 (27 places), whose C had been shaped around alias analysis (a nested
loop that reread its bound). Written as the plain loop
`for (p = start; p < end; p += 256)` it matches all 27 places under 2.95's model.

mems_conflict_for_gcse_p is the one place where gcse decides whether a memory store kills a
load (load_killed_in_block_p for availability and anticipation, compute_transp and the
store-motion walk all call it), so it now reports a conflict for every memory destination,
which is what mem_set_in_block amounts to. Calls already kill every load.
tests/test_gcse_store_kills_loads.py covers the transformer and the compiler output; see
docs/build/compiler-notes.md.

Usage: gcse_store_kills_loads.py <gcc/gcse.c>
"""
import sys
from pathlib import Path

KILL_OLD = ("  if (GET_CODE (dest) != MEM)\n"
            "    return;\n"
            "\n"
            "  /* If we are setting a MEM in our list of specially recognized MEMs, ")
KILL_NEW = ("  if (GET_CODE (dest) != MEM)\n"
            "    return;\n"
            "\n"
            "  /* RAC2: GCC 2.95.3's gcse only records that a block stores to memory\n"
            "     (mem_set_in_block), and such a store kills every load; this Cygnus\n"
            "     tree asked alias analysis instead.  Retail has 2.95's model.  */\n"
            "  gcse_mems_conflict_p = 1;\n"
            "  return;\n"
            "\n"
            "  /* If we are setting a MEM in our list of specially recognized MEMs, ")


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    if source.count(KILL_OLD) != 1:
        raise ValueError("mems_conflict_for_gcse_p: expected one insertion point, "
                         f"found {source.count(KILL_OLD)}")
    path.write_text(source.replace(KILL_OLD, KILL_NEW), encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
