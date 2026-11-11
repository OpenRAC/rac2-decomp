#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-arg-copy: deprioritize call argument register copies in Haifa sched2.

When Haifa sched2 schedules instructions that have equal priority, dependence class,
and dependent count, it breaks ties using INSN_LUID (sched1 emission order). In
func_L02_003C43F0, the fourth sprite draw sets argument registers for func_00300A00:
ori $a1, $a1, 0xC070 (arg 2), mov.s $f15, $f14 (arg 6 from arg 5), and mov.s $f16, $f21
(arg 7). Because s dies on arg 6 in sched1, arg 6 received an earlier sched1 LUID than
the color ori. Consequently, Haifa sched2 issued the arg copy at cycle 3, leaving the
ori for cycle 4 and placing the ori in the jal delay slot instead of the arg copy.

With -frac2-sched-arg-copy, rank_for_schedule tie-breaks equal-priority instructions
after reload by preferring instructions that are not register copies between call argument
registers, delaying the argument copy to the final cycle before the call where reorg places
it in the delay slot.

Usage: sched_arg_copy.py <gcc/haifa-sched.c or gcc directory>
"""
import sys
from pathlib import Path

HELPER = """/* RAC2: nonzero if INSN is a register copy between two call argument registers.  */

static int
rac2_is_arg_copy (insn)
     rtx insn;
{
  rtx set = single_set (insn);
  if (set)
    {
      rtx d = SET_DEST (set);
      rtx s = SET_SRC (set);
      if (GET_CODE (d) == REG && GET_CODE (s) == REG)
	{
	  int rd = REGNO (d);
	  int rs = REGNO (s);
	  int d_arg = (rd >= 4 && rd <= 7) || (rd >= 44 && rd <= 51);
	  int s_arg = (rs >= 4 && rs <= 7) || (rs >= 44 && rs <= 51);
	  return (d_arg && s_arg);
	}
    }
  return 0;
}

static int
rank_for_schedule (x, y)"""

RANK_OLD = """static int
rank_for_schedule (x, y)"""

TIE_OLD = """  /* RAC2: -frac2-sched-stack-offset: prefer higher displacement for stack pointer
     address computations.  */
  if (flag_rac2_sched_stack_offset)
    {
      HOST_WIDE_INT off1, off2;
      if (rac2_is_sp_addend (tmp, &off1)
	  && rac2_is_sp_addend (tmp2, &off2)
	  && off1 != off2)
	return off2 > off1 ? 1 : -1;
    }"""

TIE_NEW = """  /* RAC2: -frac2-sched-stack-offset: prefer higher displacement for stack pointer
     address computations.  */
  if (flag_rac2_sched_stack_offset)
    {
      HOST_WIDE_INT off1, off2;
      if (rac2_is_sp_addend (tmp, &off1)
	  && rac2_is_sp_addend (tmp2, &off2)
	  && off1 != off2)
	return off2 > off1 ? 1 : -1;
    }

  /* RAC2: -frac2-sched-arg-copy: prefer non-argument-copy instructions over
     copies between call argument registers during Haifa sched2 tie-breaking.  */
  if (flag_rac2_sched_arg_copy && reload_completed)
    {
      int a1 = rac2_is_arg_copy (tmp);
      int a2 = rac2_is_arg_copy (tmp2);
      if (a1 != a2)
	return a1 ? 1 : -1;
    }"""

DEFINITION_OLD = "int flag_rac2_allocno_live_length = 0;\n"
DEFINITION_NEW = ("int flag_rac2_allocno_live_length = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, deprioritize call argument copies in Haifa sched2.  */\n"
                  "int flag_rac2_sched_arg_copy = 0;\n")

OPTION_OLD = '  {"rac2-allocno-live-length", &flag_rac2_allocno_live_length, 1,\n'
OPTION_NEW = ('  {"rac2-sched-arg-copy", &flag_rac2_sched_arg_copy, 1,\n'
              '   "Deprioritize call argument register copies during Haifa sched2"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_allocno_live_length;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: deprioritize call argument copies in Haifa sched2.  */\n"
                     "extern int flag_rac2_sched_arg_copy;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    if target.is_dir():
        haifa, top, flags = target / "haifa-sched.c", target / "toplev.c", target / "flags.h"
    else:
        haifa, top, flags = target, target.with_name("toplev.c"), target.with_name("flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_arg_copy" in text for text in sources.values()):
        raise ValueError("sched-arg-copy option already present")
    haifa_src = replace_once(sources[haifa], RANK_OLD, HELPER, "haifa helper")
    haifa_src = replace_once(haifa_src, TIE_OLD, TIE_NEW, "haifa tie-break")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((haifa, haifa_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
