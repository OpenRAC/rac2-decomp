#!/usr/bin/env python3
"""Move, not copy, the selected variant in md_convert_frag in gas/config/tc-mips.c.

A relaxable macro stores its $gp form and, behind it, its absolute form; md_convert_frag
slides the chosen absolute form down over the $gp one with memcpy. The two ranges overlap
whenever the absolute form is longer than the $gp form is far away (8 bytes against 12 for a
load or store with a base register, `lbu $2,sym+1($18)`), which is undefined: a host memcpy
that copies backwards leaves the second instruction's word in the first slot, so the `lui` is
lost. Whether that happens depends on the host C library and on how the assembler was built;
an assembler built on 3 November 2026 gave the `lui`, the ones built from 8 November did not,
and func_00117278 (strtol, an -O0 unit, the only C that uses the base-register form) stopped
matching. memmove gives the 1999 hosts' forward copy on every host
(docs/build/compiler-notes.md, "Overlapping variants in md_convert_frag")."""
import sys
from pathlib import Path

path = Path(sys.argv[1])
source = path.read_text(encoding="utf-8")
old = "\tmemcpy (fixptr - old, fixptr, new);\n"
new = "\tmemmove (fixptr - old, fixptr, new);\n"
assert source.count(old) == 1, ("the variant copy in md_convert_frag", source.count(old))
path.write_text(source.replace(old, new), encoding="utf-8", newline="")
