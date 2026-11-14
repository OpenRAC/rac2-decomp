#!/usr/bin/env python3
"""Add the opt-in -frac2-sched2-barrier-hold: sched2 holds lower-priority insns behind a barrier.

After reload, while the result of a scheduling barrier (an insn carrying saved loop notes, i.e.
a REG_DEAD note on a CONST_INT) is still pending (clock < its issue cycle + insn_cost), Haifa
issues only insns of the highest ready priority; an insn held back this way then ranks ahead of
insns of equal priority once the hold ends (checked in rank_for_schedule right after priority).

In func_L03_003C7018 (sched2 block 3) the loop-note barrier is a cvt.s.w with latency 3; stock
pairs `lwc1 $f14` with `ori $a1,0xC070` while it is pending, retail issues the load alone and
the ori one cycle later, ahead of `mov.s` (draw 1, without a barrier, already matches).

Forced on for every USA v1.01 C unit it changes no function: an opt-in per-unit model, landed
under the owner's standard of 12 November 2026. Default compilation is unchanged.

Usage: sched2_barrier_hold.py <gcc directory>
"""
import sys
from pathlib import Path

EDITS = [
    ("static rtx last_scheduled_insn;\n",
     "static rtx last_scheduled_insn;\n"
     "/* RAC2: -frac2-sched2-barrier-hold state.  */\n"
     "static int rac2_barrier_until, rac2_top_priority;\n"
     "static char *rac2_held;\n"),
    ("  if (priority_val)\n    return priority_val;\n\n  /* prefer an insn with smaller contribution to registers-pressure */\n",
     "  if (priority_val)\n    return priority_val;\n\n"
     "  /* RAC2: -frac2-sched2-barrier-hold: an insn held behind a barrier goes\n"
     "     ahead of insns of equal priority once the hold is released.  */\n"
     "  if (flag_rac2_sched2_barrier_hold && reload_completed && rac2_held\n"
     "      && rac2_held[INSN_UID (tmp)] != rac2_held[INSN_UID (tmp2)])\n"
     "    return rac2_held[INSN_UID (tmp2)] - rac2_held[INSN_UID (tmp)];\n\n"
     "  /* prefer an insn with smaller contribution to registers-pressure */\n"),
    ("  /* no insns scheduled in this block yet */\n  last_scheduled_insn = 0;\n",
     "  /* no insns scheduled in this block yet */\n  last_scheduled_insn = 0;\n  rac2_barrier_until = 0;\n"),
    ("      rac2_clear_issued = 0;\n",
     "      rac2_clear_issued = 0;\n"
     "      rac2_top_priority = n_ready ? INSN_PRIORITY (ready[n_ready - 1]) : 0;\n"),
    ("\t  if (cost > 1)\n\t    {\n\t      queue_insn (insn, cost);\n",
     "\t  /* RAC2: -frac2-sched2-barrier-hold: while a barrier's result is pending\n"
     "\t     after reload, only insns of the highest ready priority issue.  */\n"
     "\t  if (flag_rac2_sched2_barrier_hold && reload_completed\n"
     "\t      && clock_var < rac2_barrier_until\n"
     "\t      && INSN_PRIORITY (insn) < rac2_top_priority)\n"
     "\t    {\n"
     "\t      rac2_held[INSN_UID (insn)] = 1;\n"
     "\t      continue;\n"
     "\t    }\n\n"
     "\t  if (cost > 1)\n\t    {\n\t      queue_insn (insn, cost);\n"),
    ("\t      last_scheduled_insn = insn;\n\t      last = move_insn (insn, last);\n",
     "\t      if (flag_rac2_sched2_barrier_hold && reload_completed)\n"
     "\t\t{\n"
     "\t\t  rtx note;\n"
     "\t\t  for (note = REG_NOTES (insn); note; note = XEXP (note, 1))\n"
     "\t\t    if (REG_NOTE_KIND (note) == REG_DEAD\n"
     "\t\t\t&& GET_CODE (XEXP (note, 0)) == CONST_INT)\n"
     "\t\t      {\n"
     "\t\t\trac2_barrier_until = clock_var + insn_cost (insn, 0, 0);\n"
     "\t\t\tbreak;\n"
     "\t\t      }\n"
     "\t\t}\n"
     "\t      last_scheduled_insn = insn;\n\t      last = move_insn (insn, last);\n"),
    ("  insn_tick = (int *) xmalloc (max_uid * sizeof (int));\n",
     "  insn_tick = (int *) xmalloc (max_uid * sizeof (int));\n"
     "  rac2_held = (char *) xmalloc (max_uid);\n"
     "  bzero (rac2_held, max_uid);\n"),
    ("  free (insn_tick);\n",
     "  free (insn_tick);\n  free (rac2_held);\n  rac2_held = 0;\n"),
]

DEFINITION_OLD = "int flag_rac2_reload_reuse_pseudo_reg = 0;\n"
DEFINITION_NEW = (DEFINITION_OLD + "\n/* RAC2: opt-in, sched2 holds lower-priority insns behind a pending barrier.  */\n"
                  "int flag_rac2_sched2_barrier_hold = 0;\n")
OPTION_OLD = '  {"rac2-reload-lone-class-no-rotate", &flag_rac2_reload_lone_class_no_rotate, 1,\n'
OPTION_NEW = ('  {"rac2-sched2-barrier-hold", &flag_rac2_sched2_barrier_hold, 1,\n'
              '   "In sched2, issue only top-priority insns while a barrier result is pending"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_reload_reuse_pseudo_reg;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: sched2 holds lower-priority insns behind a pending barrier.  */\n"
                   "extern int flag_rac2_sched2_barrier_hold;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched2_barrier_hold" in text for text in sources.values()):
        raise ValueError("sched2-barrier-hold option already present")
    src = sources[haifa]
    for k, (old, new) in enumerate(EDITS):
        src = replace_once(src, old, new, f"haifa edit {k}")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
