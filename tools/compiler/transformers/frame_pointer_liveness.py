#!/usr/bin/env python3
"""Add the opt-in -frac2-frame-pointer-liveness: GCC 2.95's frame-pointer liveness after reload.

The EE tree predates John Wehle's GCC change of 2 June 1999 (gcc-2.95/gcc/ChangeLog:
"flow.c (mark_regs_live_at_end, insn_dead_p, mark_set_1, mark_used_regs): Only give
FRAME_POINTER_REGNUM and HARD_FRAME_POINTER_REGNUM special treatment if reload hasn't run or
the frame pointer is needed. haifa-sched.c (attach_deaths): Likewise. sched.c (attach_deaths):
Likewise."). In this tree flow treats $fp (HARD_FRAME_POINTER_REGNUM, 30) as always live, even
in a function that keeps no frame pointer and gives $fp to an ordinary value: no REG_DEAD or
REG_UNUSED note for it, no set of it ever deleted, live at the function's end. reorg then sees
$fp live on every path and annuls a branch slot that loads it (func_L07_0040EC08,
func_L04_00414698: `bnel` where retail has `bne`).

With this option the six tests take GCC 2.95's form: the frame pointers (the soft one, $1 on
MIPS, and $fp) are special only when `! reload_completed || frame_pointer_needed`. Checked
against gcc-core-2.95.tar.gz (ftp.gnu.org, SHA-256 70250b26e923bcd2...): flow.c lines 2276
(mark_regs_live_at_end), 2965/2968 (insn_dead_p), 3278/3281 (mark_set_1), 3740/3746 and
3923/3926 (mark_used_regs, REG and SET cases), haifa-sched.c 4633/4636 (attach_deaths). With
RAC2_FRAME_POINTER_SPECIAL_P read as that condition, the five patched functions equal 2.95's
token for token, except for one extra pair of parentheses and an ASM_OPERANDS case GCC 2.95
also has in mark_used_regs, which belongs to another change and is not added. sched.c is not
patched: the r5900 configuration builds haifa-sched.c (configure.in, "Use haifa by default for
the r5900").

The option is off by default, enabled per unit in config/cflags.txt, and
-fno-rac2-frame-pointer-liveness disables it again. tests/test_frame_pointer_liveness.py covers
the anchors, the default/disabled equality, the un-annulled slot and controls.
See docs/COMPILER-NOTES.md.

Usage: frame_pointer_liveness.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

SPECIAL = "RAC2_FRAME_POINTER_SPECIAL_P"

# flow.c, mark_regs_live_at_end.
LIVE_AT_END_OLD = ("  SET_REGNO_REG_SET (set, FRAME_POINTER_REGNUM);\n"
                   "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
                   "  /* If they are different, also mark the hard frame pointer as live */\n"
                   "  SET_REGNO_REG_SET (set, HARD_FRAME_POINTER_REGNUM);\n"
                   "#endif      \n")
LIVE_AT_END_NEW = ("  /* RAC2: -frac2-frame-pointer-liveness, GCC 2.95's test.  */\n"
                   "  if (" + SPECIAL + ")\n"
                   "    {\n"
                   "      SET_REGNO_REG_SET (set, FRAME_POINTER_REGNUM);\n"
                   "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
                   "      /* If they are different, also mark the hard frame pointer as live */\n"
                   "      SET_REGNO_REG_SET (set, HARD_FRAME_POINTER_REGNUM);\n"
                   "#endif      \n"
                   "    }\n")
# flow.c, insn_dead_p.
DEAD_OLD = ("\t      /* Make sure insns to set frame pointer aren't deleted.  */\n"
            "\t      || regno == FRAME_POINTER_REGNUM\n"
            "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
            "\t      || regno == HARD_FRAME_POINTER_REGNUM\n"
            "#endif\n")
DEAD_NEW = ("\t      /* Make sure insns to set frame pointer aren't deleted.  */\n"
            "\t      || (regno == FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
            "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
            "\t      || (regno == HARD_FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
            "#endif\n")
# flow.c, mark_set_1.
SET_OLD = ("  if (GET_CODE (reg) == REG\n"
           "      && (regno = REGNO (reg), regno != FRAME_POINTER_REGNUM)\n"
           "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
           "      && regno != HARD_FRAME_POINTER_REGNUM\n"
           "#endif\n")
SET_NEW = ("  if (GET_CODE (reg) == REG\n"
           "      && (regno = REGNO (reg),\n"
           "\t  ! (regno == FRAME_POINTER_REGNUM && " + SPECIAL + "))\n"
           "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
           "      && ! (regno == HARD_FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
           "#endif\n")
# flow.c, mark_used_regs, case REG.
USE_OLD = ("\t    if (regno == STACK_POINTER_REGNUM\n"
           "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
           "\t\t|| regno == HARD_FRAME_POINTER_REGNUM\n"
           "#endif\n"
           "#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM\n"
           "\t\t|| (regno == ARG_POINTER_REGNUM && fixed_regs[regno])\n"
           "#endif\n"
           "\t\t|| regno == FRAME_POINTER_REGNUM)\n")
USE_NEW = ("\t    if (regno == STACK_POINTER_REGNUM\n"
           "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
           "\t\t|| (regno == HARD_FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
           "#endif\n"
           "#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM\n"
           "\t\t|| (regno == ARG_POINTER_REGNUM && fixed_regs[regno])\n"
           "#endif\n"
           "\t\t|| (regno == FRAME_POINTER_REGNUM && " + SPECIAL + "))\n")
# flow.c, mark_used_regs, case SET.
SET_USE_OLD = ("\t\t&& (regno = REGNO (testreg), regno != FRAME_POINTER_REGNUM)\n"
               "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
               "\t\t&& regno != HARD_FRAME_POINTER_REGNUM\n"
               "#endif\n")
SET_USE_NEW = ("\t\t&& (regno = REGNO (testreg),\n"
               "\t\t    ! (regno == FRAME_POINTER_REGNUM && " + SPECIAL + "))\n"
               "#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM\n"
               "\t\t&& ! (regno == HARD_FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
               "#endif\n")
# haifa-sched.c, attach_deaths.
DEATHS_OLD = ("\t    if (regno != FRAME_POINTER_REGNUM\n"
              "#if HARD_FRAME_POINTER_REGNUM != FRAME_POINTER_REGNUM\n"
              "\t\t&& ! (regno == HARD_FRAME_POINTER_REGNUM)\n"
              "#endif\n")
DEATHS_NEW = ("\t    if (! (regno == FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
              "#if HARD_FRAME_POINTER_REGNUM != FRAME_POINTER_REGNUM\n"
              "\t\t&& ! (regno == HARD_FRAME_POINTER_REGNUM && " + SPECIAL + ")\n"
              "#endif\n")
DEFINITION_OLD = "int flag_rac2_sticky_volatile_refs = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sticky_volatile_refs = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, GCC 2.95's frame-pointer liveness after reload.  */\n"
                  "int flag_rac2_frame_pointer_liveness = 0;\n")
OPTION_OLD = '   "Keep a volatile reference marked across later memory references"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-frame-pointer-liveness", &flag_rac2_frame_pointer_liveness, 1,\n'
              '   "Treat an unneeded frame pointer as an ordinary register after reload"},\n')
DECLARATION_OLD = "extern int flag_rac2_sticky_volatile_refs;\n"
DECLARATION_NEW = ("extern int flag_rac2_sticky_volatile_refs;\n"
                   "\n"
                   "/* RAC2: GCC 2.95's frame-pointer liveness after reload (flow.c,\n"
                   "   haifa-sched.c): the frame pointers are special only before reload or\n"
                   "   when the frame pointer is needed.  Always true without the option.  */\n"
                   "extern int flag_rac2_frame_pointer_liveness;\n"
                   "#define " + SPECIAL + " \\\n"
                   "  (! flag_rac2_frame_pointer_liveness || ! reload_completed \\\n"
                   "   || frame_pointer_needed)\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    flow, sched = root / "flow.c", root / "haifa-sched.c"
    top, flags = root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (flow, sched, top, flags)}
    if any("flag_rac2_frame_pointer_liveness" in text or SPECIAL in text
           for text in sources.values()):
        raise ValueError("frame-pointer-liveness option already present")
    life = replace_once(sources[flow], LIVE_AT_END_OLD, LIVE_AT_END_NEW, "mark_regs_live_at_end")
    life = replace_once(life, DEAD_OLD, DEAD_NEW, "insn_dead_p")
    life = replace_once(life, SET_OLD, SET_NEW, "mark_set_1")
    life = replace_once(life, USE_OLD, USE_NEW, "mark_used_regs REG")
    life = replace_once(life, SET_USE_OLD, SET_USE_NEW, "mark_used_regs SET")
    deaths = replace_once(sources[sched], DEATHS_OLD, DEATHS_NEW, "attach_deaths")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((flow, life), (sched, deaths), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
