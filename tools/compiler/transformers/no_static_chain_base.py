#!/usr/bin/env python3
"""Add the opt-in -frac2-no-static-chain-base: GCC 2.95.3's hard-register alias seeds.

init_alias_analysis (alias.c) gives a few hard registers a base address before it walks the
insns: the argument registers, the stack, frame and argument pointers and, in this tree as in
GCC 2.95, the static chain register and the incoming struct-value register when they are
registers. On MIPS the static chain is $v0 (STATIC_CHAIN_REGNUM, mips.h); STRUCT_VALUE is 0, so
there is no struct-value register. record_set keeps a seeded register's base only while every
set of it is relative to itself, so the first `$v0 = lo_sum ($a1, sym)` after reload makes the
base of $v0 unknown, and the scheduler's write_dependence_p then lets every store through $v0
conflict with the prologue's stack saves. An unseeded register, $v1 for one, takes the base of
its first set instead (find_base_value), so its stores do not conflict with stack slots.
func_002BA0E0's retail code has its callee saves next to its first stores through $v0, which
this tree's sched2 cannot do.

GCC dropped both seeds: Richard Henderson's change of 22 August 2000 (gcc-3.0/gcc/ChangeLog.4:
"alias.c (init_alias_analysis): Do not register struct_value_incoming_rtx or static_chain_rtx
as pointing to stack memory."), which reverses Jeffrey Law's 1997 addition (ChangeLog.0) and is
also in gcc-2.95.3's alias.c. Checked against gcc-core-2.95.tar.gz (ftp.gnu.org, SHA-256
70250b26e923bcd2...) and gcc-core-2.95.3.tar.gz (56811ee60990b466...): the two releases' alias.c
differ only in the copyright line and these nine lines (2.95 lines 1458-1466).

Neither version is safe in a GNU C nested function, where $v0 arrives holding the parent's
frame address. Take a nested body `x = a*b*c*a; *p = 5;` (x is the parent's, reached through
the chain) called with p == &x, so the x store must come first:
- with the 2.95 seed (the default) $v0 is a stack reference (a Pmode ADDRESS), which
  base_alias_check says cannot alias an argument, so sched2 issues the *p store first. This is
  the bug GCC fixed;
- without the seed, as in 2.95.3, $v0 takes the base of its first set, and record_set is
  flow-insensitive. If the nested function sets $v0 again later (`return local;` gives
  `$v0 = $sp + 16`), every use of the incoming chain gets that stack base, and the two stores
  swap again (the same code is in 2.95.3).
So for nested functions this option goes one step past 2.95.3: when
current_function_needs_context is set, it also marks the chain register as seen (reg_seen),
so no set gives it a base, and stores through the chain conflict with every other store. In a
function without a static chain it changes nothing beyond 2.95.3: $v0 has no seed and takes the
base of its first set.

With this option both seeds are left out, as in 2.95.3, and a nested function's chain gets no
base; it keys on no function, only on the option. It is off by default, enabled per unit in
config/cflags.txt, and -fno-rac2-no-static-chain-base disables it again.
tests/test_no_static_chain_base.py covers the anchors, the default/disabled equality, the late
saves, both nested-function store orders and controls. See docs/COMPILER-NOTES.md.

Usage: no_static_chain_base.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

# alias.c, init_alias_analysis: the two seeds GCC 2.95.3 no longer has.
SEEDS_OLD = ("      if (struct_value_incoming_rtx\n"
             "\t  && GET_CODE (struct_value_incoming_rtx) == REG)\n"
             "\tnew_reg_base_value[REGNO (struct_value_incoming_rtx)]\n"
             "\t  = gen_rtx_ADDRESS (Pmode, struct_value_incoming_rtx);\n"
             "\n"
             "      if (static_chain_rtx\n"
             "\t  && GET_CODE (static_chain_rtx) == REG)\n"
             "\tnew_reg_base_value[REGNO (static_chain_rtx)]\n"
             "\t  = gen_rtx_ADDRESS (Pmode, static_chain_rtx);\n")
SEEDS_NEW = ("      /* RAC2: -frac2-no-static-chain-base leaves both seeds out, as GCC\n"
             "\t 2.95.3 does (rth, 2000-08-22).  */\n"
             "      if (! flag_rac2_no_static_chain_base\n"
             "\t  && struct_value_incoming_rtx\n"
             "\t  && GET_CODE (struct_value_incoming_rtx) == REG)\n"
             "\tnew_reg_base_value[REGNO (struct_value_incoming_rtx)]\n"
             "\t  = gen_rtx_ADDRESS (Pmode, struct_value_incoming_rtx);\n"
             "\n"
             "      if (! flag_rac2_no_static_chain_base\n"
             "\t  && static_chain_rtx\n"
             "\t  && GET_CODE (static_chain_rtx) == REG)\n"
             "\tnew_reg_base_value[REGNO (static_chain_rtx)]\n"
             "\t  = gen_rtx_ADDRESS (Pmode, static_chain_rtx);\n"
             "      /* RAC2: in a nested function the chain register holds the\n"
             "\t parent's frame address on entry.  Mark it seen, so that no later\n"
             "\t set of it gives it a base: record_set is flow-insensitive and\n"
             "\t would give every use of the incoming chain that set's base.  */\n"
             "      else if (flag_rac2_no_static_chain_base\n"
             "\t       && current_function_needs_context\n"
             "\t       && static_chain_rtx\n"
             "\t       && GET_CODE (static_chain_rtx) == REG)\n"
             "\treg_seen[REGNO (static_chain_rtx)] = 1;\n")
DEFINITION_OLD = "int flag_rac2_wide_saves_below = 0;\n"
DEFINITION_NEW = ("int flag_rac2_wide_saves_below = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, GCC 2.95.3's alias seeds: no static-chain base.  */\n"
                  "int flag_rac2_no_static_chain_base = 0;\n")
OPTION_OLD = '   "Give a GPR saved in TImode a 16-byte slot below the 8-byte ones"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-no-static-chain-base", &flag_rac2_no_static_chain_base, 1,\n'
              '   "Give the static chain and struct-value registers no alias base"},\n')
DECLARATION_OLD = "extern int flag_rac2_wide_saves_below;\n"
DECLARATION_NEW = ("extern int flag_rac2_wide_saves_below;\n"
                   "\n"
                   "/* RAC2: alias.c seeds no base for the static chain or struct-value\n"
                   "   register, as GCC 2.95.3.  */\n"
                   "extern int flag_rac2_no_static_chain_base;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    alias, top, flags = root / "alias.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (alias, top, flags)}
    if any("flag_rac2_no_static_chain_base" in text for text in sources.values()):
        raise ValueError("no-static-chain-base option already present")
    seeds = replace_once(sources[alias], SEEDS_OLD, SEEDS_NEW, "init_alias_analysis seeds")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((alias, seeds), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
