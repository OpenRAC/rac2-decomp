#!/usr/bin/env python3
"""Reload never inherits into a register that is not a spill register of the insn.

The archive's reload1.c (2.9-ee-991111b) starts reload_reg_free_for_value_p with

    if (TEST_HARD_REG_BIT (reload_reg_used, regno))
      return 0;

and choose_reload_regs puts every register outside the insn's spill set into reload_reg_used
(IOR_COMPL_HARD_REG_SET (reload_reg_used, chain->used_spill_regs)). A hard register that a
pseudo holds in the insn, such as the output of `slt` given $v0 by local-alloc, is therefore
never taken over as an inherited reload register. Patch 0047 (the GCC 2.95.2 reload1.c) drops
the test, so the tree inherited the value of a spilled pseudo left in $v0 by the previous
insn's output reload and wrote `slt $v0,$v0,128` where retail reloads: `lw $v1,slot($sp)`,
`slt $v0,$v1,128`. This puts the test back; nothing else of 0047 changes.

Retail witnesses: func_L00_003C5B88 and its 22 copies (the count reload after `n++`, and the
round-robin register choice of the index reloads after it) become exact with it. Every matched
function of all 28 programs compiles to the same bytes with and without it.
The exclusion must use the initial non-spill set. mark_reload_reg_in_use also adds
RELOAD_OTHER allocations to reload_reg_used; testing that mutable set rejects a
reload's own register before the existing lifetime loop can exclude reloadnum.
Snapshot the non-spill set once per instruction. Leave the lifetime/conflict
checks for every other reload unchanged.

tests/test_reload_reg_used_guard.py covers the anchors and reload controls.

Usage: reload_reg_used_guard.py <gcc/reload1.c>
"""
import sys
from pathlib import Path

OLD = ("  int time1;\n"
       "  int i;\n"
       "  int copy = 0;\n"
       "\n"
       "  if (out == const0_rtx)\n"
       "    {\n"
       "      copy = 1;\n")
NEW = ("  int time1;\n"
       "  int i;\n"
       "  int copy = 0;\n"
       "\n"
    "  /* RAC2: retain the archive's non-spill exclusion without rejecting\n"
    "     this reload's own RELOAD_OTHER allocation. The loop below checks\n"
    "     conflicts with other reloads and deliberately skips reloadnum.\n"
    "     See reload_reg_used_guard.py.  */\n"
    "  if (TEST_HARD_REG_BIT (rac2_reload_unavailable, regno))\n"
       "    return 0;\n"
       "\n"
       "  if (out == const0_rtx)\n"
       "    {\n"
       "      copy = 1;\n")

DECLARATION_OLD = "static HARD_REG_SET reload_reg_used;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* Instruction-local non-spill set, before any reload allocation. */\n"
                     "static HARD_REG_SET rac2_reload_unavailable;\n")
INITIAL_OLD = "  IOR_COMPL_HARD_REG_SET (reload_reg_used, chain->used_spill_regs);\n"
INITIAL_NEW = (INITIAL_OLD
               + "  COPY_HARD_REG_SET (rac2_reload_unavailable, reload_reg_used);\n")


def patch(text: str) -> str:
    if "reload_reg_used_guard.py" in text:
        raise ValueError("reload_reg_free_for_value_p already patched")
    replacements = ((OLD, NEW), (DECLARATION_OLD, DECLARATION_NEW), (INITIAL_OLD, INITIAL_NEW))
    for before, _ in replacements:
        if text.count(before) != 1:
            raise ValueError(f"reload_reg_free_for_value_p: expected one anchor, found {text.count(before)}")
    for before, after in replacements:
        text = text.replace(before, after)
    return text


def main() -> None:
    path = Path(sys.argv[1])
    path.write_text(patch(path.read_text(encoding="utf-8")), encoding="utf-8", newline="")
    print("reload_reg_free_for_value_p: preserve non-spill exclusion and ignore self-conflicts")


if __name__ == "__main__":
    main()
