#!/usr/bin/env python3
"""Give mark_set_resources GCC 2.95's sticky `volatil`, by default (-fno-rac2-sticky-volatile-sets).

This is the mark_set_resources half of Mark Mitchell's 6 May 1999 change in GCC 2.95
(gcc/ChangeLog: "resource.c (mark_referenced_resources): Make volatil monotonically
increasing. (mark_set_resources): Likewise."); -frac2-sticky-volatile-refs applies the other
half. The EE tree's mark_set_resources assigns, at every MEM it sets,

    res->unch_memory = RTX_UNCHANGING_P (x);
    res->volatil = MEM_VOLATILE_P (x);

so when reorg collects what the insns between a call and a slot candidate set, an ordinary
store clears the flag that a volatile store nearer the call set, and fill_simple_delay_slots'
backward search takes an insn from before both. GCC 2.95 to 2.95.3 use `|=` for both fields
there (resource.c 713-714), and so does this cc1 now: the MEM case keeps a set flag.

The same upstream change also edits the ASM_OPERANDS case of mark_set_resources to `|=`. That
case does not exist in this tree: it, and the UNSPEC_VOLATILE, ASM_INPUT and TRAP_IF cases,
come from Mark Mitchell's change of 4 May 1999, which the EE tree lacks too. That hunk depends
on the 4 May change and is not applied.

Retail keeps the `jal` slot empty after a plain store and then a volatile store in
func_L00_002A3B88 and func_00131DE8, where the EE tree's rule fills it. The rule is the
default because retail's compiler shows it wherever it can be seen: with it, no matched
function of src/ changes. -fno-rac2-sticky-volatile-sets restores the EE tree's assignment
for a unit that needs it (none does). tests/test_sticky_volatile_sets.py covers the anchors,
the default, the explicit opt-out and controls. See docs/COMPILER-NOTES.md.

Usage: sticky_volatile_sets.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

# resource.c, mark_set_resources: the MEM case GCC 2.95 changed to `|=`.
SET_OLD = ("      if (in_dest)\n"
           "\t{\n"
           "\t  res->memory = 1;\n"
           "\t  res->unch_memory = RTX_UNCHANGING_P (x);\n"
           "\t  res->volatil = MEM_VOLATILE_P (x);\n"
           "\t}\n")
SET_NEW = ("      if (in_dest)\n"
           "\t{\n"
           "\t  res->memory = 1;\n"
           "\t  /* RAC2: both flags stay set, GCC 2.95's |= (Mark Mitchell 1999-05-06);\n"
           "\t     -fno-rac2-sticky-volatile-sets restores the EE tree's =.  */\n"
           "\t  res->unch_memory = (flag_rac2_sticky_volatile_sets ? res->unch_memory : 0)\n"
           "\t\t\t     | RTX_UNCHANGING_P (x);\n"
           "\t  res->volatil = (flag_rac2_sticky_volatile_sets ? res->volatil : 0)\n"
           "\t\t\t | MEM_VOLATILE_P (x);\n"
           "\t}\n")
DEFINITION_OLD = "int flag_rac2_no_static_chain_base = 0;\n"
DEFINITION_NEW = ("int flag_rac2_no_static_chain_base = 0;\n"
                  "\n"
                  "/* RAC2: on by default, mark_set_resources keeps volatil set.  */\n"
                  "int flag_rac2_sticky_volatile_sets = 1;\n")
OPTION_OLD = '   "Give the static chain and struct-value registers no alias base"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-sticky-volatile-sets", &flag_rac2_sticky_volatile_sets, 1,\n'
              '   "Keep a volatile store marked across later stores"},\n')
DECLARATION_OLD = "extern int flag_rac2_no_static_chain_base;\n"
DECLARATION_NEW = ("extern int flag_rac2_no_static_chain_base;\n"
                   "\n"
                   "/* RAC2: mark_set_resources keeps volatil set (default on).  */\n"
                   "extern int flag_rac2_sticky_volatile_sets;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    resource, top, flags = root / "resource.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (resource, top, flags)}
    if any("flag_rac2_sticky_volatile_sets" in text for text in sources.values()):
        raise ValueError("sticky-volatile-sets option already present")
    marked = replace_once(sources[resource], SET_OLD, SET_NEW, "MEM set")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((resource, marked), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
