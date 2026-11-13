#!/usr/bin/env python3
"""Add the opt-in -frac2-keep-user-copies: keep a register copy into a user variable.

In func_PAL_L09_0040FD68 and func_PAL_L00_003B9E80, retail allocates the frame counter at
+0x96 as if a copy of it were kept up to local-alloc and tied to it: the counter's quantity
then has five references and takes the first free register ($v0 and $v1), and the copy costs
no instruction (mips_move_1word prints nothing for a move between equal registers). An
instrumented local-alloc (RAC2_LALLOC_DBG) shows the same assignment whenever one extra insn
tied to the counter is present; without one, `counter + 1` (and in L00 the divisor 6) take
those registers first. In this tree the copy never reaches local-alloc: cse makes the
source the canonical register of the pair, so the copy's uses are rewritten to the source
and flow deletes it, and combine folds a single-use copy into its user (floatsisf2, slt).

With -frac2-keep-user-copies:
  - cse's make_regs_eqv makes a pseudo that is a user variable the canonical register when it
    joins an equivalence class of pseudos, so later references keep the variable;
  - combine's can_combine_p does not fold a pseudo-to-pseudo copy into a user variable.
The source writes the copy as a named local (`t = counter;` after the counter's store), and
both functions then match. Default compilation is unchanged.

Usage: keep_user_copies.py <gcc directory>
"""
import sys
from pathlib import Path

CSE_OLD = """      && ((new < FIRST_PSEUDO_REGISTER && FIXED_REGNO_P (new))
	  || (new >= FIRST_PSEUDO_REGISTER
	      && (firstr < FIRST_PSEUDO_REGISTER"""

CSE_NEW = """      && ((new < FIRST_PSEUDO_REGISTER && FIXED_REGNO_P (new))
	  /* RAC2: -frac2-keep-user-copies: a user variable copied from a pseudo
	     becomes the canonical register, so its copy is kept.  */
	  || (flag_rac2_keep_user_copies
	      && new >= FIRST_PSEUDO_REGISTER
	      && firstr >= FIRST_PSEUDO_REGISTER
	      && REG_USERVAR_P (regno_reg_rtx[new]))
	  || (new >= FIRST_PSEUDO_REGISTER
	      && (firstr < FIRST_PSEUDO_REGISTER"""

COMBINE_OLD = """  /* Don't eliminate a store in the stack pointer.  */
  if (dest == stack_pointer_rtx"""

COMBINE_NEW = """  /* RAC2: -frac2-keep-user-copies: don't fold a pseudo-to-pseudo copy into
     a user variable.  */
  if (flag_rac2_keep_user_copies
      && GET_CODE (src) == REG && GET_CODE (dest) == REG
      && REGNO (src) >= FIRST_PSEUDO_REGISTER
      && REGNO (dest) >= FIRST_PSEUDO_REGISTER
      && REG_USERVAR_P (dest))
    return 0;

  /* Don't eliminate a store in the stack pointer.  */
  if (dest == stack_pointer_rtx"""

DEFINITION_OLD = "int flag_rac2_sched_arg_copy = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_arg_copy = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, keep register copies into user variables.  */\n"
                  "int flag_rac2_keep_user_copies = 0;\n")

OPTION_OLD = '  {"rac2-sched-arg-copy", &flag_rac2_sched_arg_copy, 1,\n'
OPTION_NEW = ('  {"rac2-keep-user-copies", &flag_rac2_keep_user_copies, 1,\n'
              '   "Keep register copies into user variables through cse and combine"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_arg_copy;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: keep register copies into user variables.  */\n"
                     "extern int flag_rac2_keep_user_copies;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(target: Path) -> None:
    cse, combine, top, flags = (target / "cse.c", target / "combine.c",
                                target / "toplev.c", target / "flags.h")
    sources = {path: path.read_text(encoding="latin-1") for path in (cse, combine, top, flags)}
    if any("flag_rac2_keep_user_copies" in text for text in sources.values()):
        raise ValueError("keep-user-copies option already present")
    edits = {
        cse: replace_once(sources[cse], CSE_OLD, CSE_NEW, "cse canonical register"),
        combine: replace_once(sources[combine], COMBINE_OLD, COMBINE_NEW, "combine copy"),
        top: replace_once(replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW,
                                       "option definition"),
                          OPTION_OLD, OPTION_NEW, "option table"),
        flags: replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                            "option declaration"),
    }
    for path, contents in edits.items():
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
