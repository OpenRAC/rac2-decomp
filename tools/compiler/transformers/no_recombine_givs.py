#!/usr/bin/env python3
"""strength_reduce does not recombine givs, as in the gcc-2.95 release branch.

`recombine_givs` (loop.c) runs after `combine_givs` has decided which reduced giv each
address giv is expressed from. Its first loop walks the givs in insn order and moves every
combined giv onto the most recently set DEST_REG giv it can be expressed from ("This tends
to shorten giv lifetimes"); its second loop derives DEST_REG givs from earlier ones. For the
gcc-2.95 release the FSF disabled the call in strength_reduce with `#if 0` ("There are still
some problems with giv recombination", gcc-patches, June 1999), while the development tree
this Cygnus snapshot comes from kept it. Retail's compiler behaves like the release branch:
its address givs stay on the giv combine_givs chose. This is that behaviour,
unconditionally; it is not an option.

Retail witness. func_00298F00 (7,840 bytes, boot + 27 levels, the memory-card state
machine) reads a directory entry's slot digit as `lbu 0x24(entry)` in its directory loop,
where this tree recombines the read with the name + 5 pointer reduced for the call just
before it (`lbu -1(name + 5)`) and swaps the two pointers' registers: six instructions, at
every place. With the call removed it matches at all 28 places. Of every matched function in
tools/build.py all, none compiled differently; of the near-miss drafts in nonmatching/ that
compile, 9 of 922 change, none of them close to a match.

The call to recombine_givs in strength_reduce is removed (the function itself stays, unused,
as in the release branch). tests/test_no_recombine_givs.py covers the transformer and the
compiler output; see docs/build/compiler-notes.md.

Usage: no_recombine_givs.py <gcc/loop.c>
"""
import sys
from pathlib import Path

CALL_OLD = "      recombine_givs (bl, loop_start, loop_end, unroll_p);\n"
CALL_NEW = ("      /* RAC2: no giv recombination, as in the gcc-2.95 release branch\n"
            "\t and retail's compiler.  */\n")


def patch(path: Path) -> None:
    source = path.read_text(encoding="utf-8")
    if source.count(CALL_OLD) != 1:
        raise ValueError("strength_reduce: expected one recombine_givs call, "
                         f"found {source.count(CALL_OLD)}")
    path.write_text(source.replace(CALL_OLD, CALL_NEW), encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
