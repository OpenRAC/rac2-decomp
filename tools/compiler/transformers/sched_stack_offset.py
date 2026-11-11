#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-stack-offset: break Haifa sched ties by higher stack displacement.

When Haifa scheduler schedules instructions that have equal priority, register pressure
weight, dependence class, and dependent count, it breaks ties using INSN_LUID (original
insn order). In func_L05_00444840, addiu $a1, $sp, 0x8 (&target_x) and addiu $a2, $sp, 0xC
(&target_y) tie in sched1 and sched2.

With -frac2-sched-stack-offset, rank_for_schedule tie-breaks equal-priority stack pointer
address computations by preferring the higher stack displacement.

Usage: sched_stack_offset.py <gcc/haifa-sched.c or gcc directory>
"""
import sys
from pathlib import Path

HELPER = """/* RAC2: Extract stack pointer offset from an addiu reg, $sp, offset insn.  */

static int
rac2_is_sp_addend (insn, poffset)
     rtx insn;
     HOST_WIDE_INT *poffset;
{
  rtx set = single_set (insn);
  rtx dest, src;

  if (!set)
    return 0;
  dest = SET_DEST (set);
  src = SET_SRC (set);
  if (GET_CODE (dest) != REG)
    return 0;
  if (GET_CODE (src) == PLUS
      && GET_CODE (XEXP (src, 0)) == REG
      && REGNO (XEXP (src, 0)) == STACK_POINTER_REGNUM
      && GET_CODE (XEXP (src, 1)) == CONST_INT)
    {
      *poffset = INTVAL (XEXP (src, 1));
      return 1;
    }
  return 0;
}

static int
rank_for_schedule (x, y)"""

RANK_OLD = """static int
rank_for_schedule (x, y)"""

TIE_OLD = """  /* RAC2: -frac2-sched-store-offset: prefer lower displacement for memory stores
     to the same base register.  */
  if (flag_rac2_sched_store_offset)
    {
      rtx base1, base2;
      HOST_WIDE_INT off1, off2;
      if (rac2_mem_store_base_and_offset (tmp, &base1, &off1)
	  && rac2_mem_store_base_and_offset (tmp2, &base2, &off2)
	  && REGNO (base1) == REGNO (base2)
	  && off1 != off2)
	return off1 > off2 ? 1 : -1;
    }"""

TIE_NEW = """  /* RAC2: -frac2-sched-store-offset: prefer lower displacement for memory stores
     to the same base register.  */
  if (flag_rac2_sched_store_offset)
    {
      rtx base1, base2;
      HOST_WIDE_INT off1, off2;
      if (rac2_mem_store_base_and_offset (tmp, &base1, &off1)
	  && rac2_mem_store_base_and_offset (tmp2, &base2, &off2)
	  && REGNO (base1) == REGNO (base2)
	  && off1 != off2)
	return off1 > off2 ? 1 : -1;
    }

  /* RAC2: -frac2-sched-stack-offset: prefer higher displacement for stack pointer
     address computations.  */
  if (flag_rac2_sched_stack_offset)
    {
      HOST_WIDE_INT off1, off2;
      if (rac2_is_sp_addend (tmp, &off1)
	  && rac2_is_sp_addend (tmp2, &off2)
	  && off1 != off2)
	return off2 > off1 ? 1 : -1;
    }"""

DEFINITION_OLD = "int flag_rac2_sched_store_offset = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_store_offset = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, tie-break stack address computations by higher displacement.  */\n"
                  "int flag_rac2_sched_stack_offset = 0;\n")

OPTION_OLD = '  {"rac2-sched-store-offset", &flag_rac2_sched_store_offset, 1,\n'
OPTION_NEW = ('  {"rac2-sched-stack-offset", &flag_rac2_sched_stack_offset, 1,\n'
              '   "Prefer higher displacement for tied stack pointer address computations"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_store_offset;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: tie-break stack address computations by higher displacement.  */\n"
                     "extern int flag_rac2_sched_stack_offset;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    if target.is_dir():
        sched, top, flags = target / "haifa-sched.c", target / "toplev.c", target / "flags.h"
    else:
        sched, top, flags = target, target.with_name("toplev.c"), target.with_name("flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (sched, top, flags)}
    if any("flag_rac2_sched_stack_offset" in text for text in sources.values()):
        raise ValueError("sched-stack-offset option already present")
    sched_src = replace_once(sources[sched], RANK_OLD, HELPER, "rank_for_schedule helper")
    sched_src = replace_once(sched_src, TIE_OLD, TIE_NEW, "rank_for_schedule tie breaker")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((sched, sched_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
