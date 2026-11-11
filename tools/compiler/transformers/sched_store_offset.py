#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-store-offset: break Haifa sched2 ties by store displacement.

When Haifa sched2 schedules instructions that have equal priority, register pressure
weight, dependence class, and dependent count, it breaks ties using INSN_LUID (sched1
emission order). In func_00342BE8, clip.x1 (sw $v0, 0x24($sp)) and clip.y1
(sw $a0, 0x2C($sp)) tie in sched2. Because load latency on screenWidthGP delayed
clip.x1 in sched1, clip.y1 received an earlier sched1 LUID, causing sched2 to invert
the stores (+0x230/+0x234).

With -frac2-sched-store-offset, rank_for_schedule tie-breaks equal-priority stores to
the same base register by preferring the lower memory displacement (ascending write order).

Usage: sched_store_offset.py <gcc/haifa-sched.c or gcc directory>
"""
import sys
from pathlib import Path

HELPER = """/* RAC2: Extract base register and offset from an SImode GPR memory store insn.  */

static int
rac2_mem_store_base_and_offset (insn, pbase, poffset)
     rtx insn;
     rtx *pbase;
     HOST_WIDE_INT *poffset;
{
  rtx set = single_set (insn);
  rtx dest, src, addr;

  if (!set)
    return 0;
  dest = SET_DEST (set);
  src = SET_SRC (set);
  if (GET_CODE (dest) != MEM || GET_MODE (dest) != SImode)
    return 0;
  if (GET_CODE (src) != REG || REGNO (src) == 0 || REGNO (src) >= 32)
    return 0;
  addr = XEXP (dest, 0);
  if (GET_CODE (addr) == REG)
    {
      *pbase = addr;
      *poffset = 0;
      return 1;
    }
  if (GET_CODE (addr) == PLUS
      && GET_CODE (XEXP (addr, 0)) == REG
      && GET_CODE (XEXP (addr, 1)) == CONST_INT)
    {
      *pbase = XEXP (addr, 0);
      *poffset = INTVAL (XEXP (addr, 1));
      return 1;
    }
  return 0;
}

static int
rank_for_schedule (x, y)"""

RANK_OLD = """static int
rank_for_schedule (x, y)"""

TIE_OLD = """  val = depend_count2 - depend_count1;
  if (val)
    return val;
  
  /* If insns are equally good, sort by INSN_LUID (original insn order),
     so that we make the sort stable.  This minimizes instruction movement,
     thus minimizing sched's effect on debugging and cross-jumping.  */
  return INSN_LUID (tmp) - INSN_LUID (tmp2);"""

TIE_NEW = """  val = depend_count2 - depend_count1;
  if (val)
    return val;
  
  /* RAC2: -frac2-sched-store-offset: prefer lower displacement for memory stores
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

  /* If insns are equally good, sort by INSN_LUID (original insn order),
     so that we make the sort stable.  This minimizes instruction movement,
     thus minimizing sched's effect on debugging and cross-jumping.  */
  return INSN_LUID (tmp) - INSN_LUID (tmp2);"""

DEFINITION_OLD = "int flag_rac2_gcse_hash_111 = 0;\n"
DEFINITION_NEW = ("int flag_rac2_gcse_hash_111 = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, tie-break memory stores by lower displacement.  */\n"
                  "int flag_rac2_sched_store_offset = 0;\n")

OPTION_OLD = '  {"rac2-gcse-hash-111", &flag_rac2_gcse_hash_111, 1,\n'
OPTION_NEW = ('  {"rac2-sched-store-offset", &flag_rac2_sched_store_offset, 1,\n'
              '   "Prefer lower displacement for tied memory stores to same base"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_gcse_hash_111;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: tie-break memory stores by lower displacement.  */\n"
                     "extern int flag_rac2_sched_store_offset;\n")


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
    if any("flag_rac2_sched_store_offset" in text for text in sources.values()):
        raise ValueError("sched-store-offset option already present")
    sched_src = replace_once(sources[sched], RANK_OLD, HELPER, "rank_for_schedule helper")
    sched_src = replace_once(sched_src, TIE_OLD, TIE_NEW, "rank_for_schedule tie breaker")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((sched, sched_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
