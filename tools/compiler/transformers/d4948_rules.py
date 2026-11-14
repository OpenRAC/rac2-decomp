#!/usr/bin/env python3
"""Add two opt-in switches for func_002D4948 (jump.c and Haifa sched1).

- -frac2-loop-exit-dup-first-pass (jump.c jump_optimize_1): duplicate_loop_exit_test runs only on
  the first iteration of jump_optimize_1's main loop, which the source comment already calls the
  only safe point ("immediately after regscan"). In func_002D4948 the preset search's exit code
  then still holds its label at jump1 and is peeled only by the pass after loop, giving retail's
  $a3 index copy, the store sunk to the end and the $t1/$t3 table pointers.
- -frac2-sched-defer-const-after-death (haifa-sched.c, sched1 only): a constant load is not
  issued in the slot directly after a same-cycle single-SET insn that uses a block-local pseudo
  with one set and one use; it waits one cycle, once per insn. This generalises
  -frac2-sched-defer-const from stores to any insn; in func_002D4948 the items load then follows
  addu 93 and takes $v1 as retail.

Forced on alone they change 173 and 637 functions: opt-in per-unit models under the owner's
standard of 12 November 2026. Default compilation is unchanged.

Usage: d4948_rules.py <gcc directory>
"""
import sys
from pathlib import Path

JUMP_OLD = """	  if (after_regscan && GET_CODE (insn) == NOTE
	      && NOTE_LINE_NUMBER (insn) == NOTE_INSN_LOOP_BEG
	      && (temp1 = next_nonnote_insn (insn)) != 0"""
JUMP_NEW = """	  if (after_regscan && GET_CODE (insn) == NOTE
	      && NOTE_LINE_NUMBER (insn) == NOTE_INSN_LOOP_BEG
	      && (first || ! flag_rac2_loop_exit_dup_first_pass)
	      && (temp1 = next_nonnote_insn (insn)) != 0"""

HELPER_OLD = "/* RAC2: nonzero if INSN is a register copy between two call argument registers.  */\n"
HELPER_NEW = """/* RAC2: -frac2-sched-defer-const-after-death state, reset per scheduled block.  */
static char *rac2_dd_deferred;
static int rac2_dd_size;
static rtx rac2_dd_prev;

/* RAC2: nonzero if X mentions a block-local pseudo with one set and one use.  */
static int
rac2_uses_single_use_pseudo (x)
     rtx x;
{
  char *fmt;
  int i, j;
  if (x == 0)
    return 0;
  if (GET_CODE (x) == REG)
    return (REGNO (x) >= FIRST_PSEUDO_REGISTER
	    && REG_N_SETS (REGNO (x)) == 1 && REG_N_REFS (REGNO (x)) == 2
	    && REG_BASIC_BLOCK (REGNO (x)) >= 0);
  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (rac2_uses_single_use_pseudo (XEXP (x, i)))
	    return 1;
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (rac2_uses_single_use_pseudo (XVECEXP (x, i, j)))
	    return 1;
    }
  return 0;
}

/* RAC2: nonzero if INSN is a single SET that ends such a pseudo.  */
static int
rac2_ends_single_use_pseudo_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  if (GET_CODE (insn) != INSN || GET_CODE (pat) != SET)
    return 0;
  if (rac2_uses_single_use_pseudo (SET_SRC (pat)))
    return 1;
  return (GET_CODE (SET_DEST (pat)) == MEM
	  && rac2_uses_single_use_pseudo (XEXP (SET_DEST (pat), 0)));
}

/* RAC2: nonzero if INSN sets a pseudo to a constant.  */
static int
rac2_dd_const_load_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  return (GET_CODE (insn) == INSN && GET_CODE (pat) == SET
	  && GET_CODE (SET_DEST (pat)) == REG
	  && REGNO (SET_DEST (pat)) >= FIRST_PSEUDO_REGISTER
	  && GET_CODE (SET_SRC (pat)) == CONST_INT);
}

""" + HELPER_OLD

INIT_OLD = "  /* loop until all the insns in BB are scheduled.  */\n"
INIT_NEW = """  if (flag_rac2_sched_defer_const_after_death)
    {
      if (rac2_dd_deferred)
	free (rac2_dd_deferred);
      rac2_dd_size = get_max_uid () + 1;
      rac2_dd_deferred = (char *) xcalloc (rac2_dd_size, 1);
    }

""" + INIT_OLD

RESET_OLD = "      rac2_clear_issued = 0;\n"
RESET_NEW = RESET_OLD + "      rac2_dd_prev = 0;\n"

TEST_OLD = "\t  /* RAC2: -frac2-sched2-barrier-hold: while a barrier's result is pending\n"
TEST_NEW = """\t  /* RAC2: -frac2-sched-defer-const-after-death: before reload, a constant
\t     load waits one cycle after a same-cycle insn that ends a block-local
\t     single-use pseudo.  */
\t  if (flag_rac2_sched_defer_const_after_death && rac2_dd_deferred
\t      && cost == 0 && !reload_completed
\t      && rac2_dd_prev != 0
\t      && rac2_ends_single_use_pseudo_p (rac2_dd_prev)
\t      && INSN_UID (insn) < rac2_dd_size
\t      && ! rac2_dd_deferred[INSN_UID (insn)]
\t      && rac2_dd_const_load_p (insn))
\t    {
\t      rac2_dd_deferred[INSN_UID (insn)] = 1;
\t      cost = 1;
\t    }

""" + TEST_OLD

PREV_OLD = "\t      rac2_cycle_prev = insn;\n"
PREV_NEW = PREV_OLD + "\t      rac2_dd_prev = insn;\n"

DEFINITION_OLD = "int flag_rac2_cse2_keep_const_vars = 0;\n"
DEFINITION_NEW = (DEFINITION_OLD
                  + "int flag_rac2_loop_exit_dup_first_pass = 0;\n"
                    "int flag_rac2_sched_defer_const_after_death = 0;\n")
OPTION_OLD = '  {"rac2-cse2-keep-const-vars", &flag_rac2_cse2_keep_const_vars, 1,\n'
OPTION_NEW = ('  {"rac2-loop-exit-dup-first-pass", &flag_rac2_loop_exit_dup_first_pass, 1,\n'
              '   "Duplicate loop exit tests only on jump\'s first pass"},\n'
              '  {"rac2-sched-defer-const-after-death", &flag_rac2_sched_defer_const_after_death, 1,\n'
              '   "Defer a constant load one cycle after an insn that ends a single-use pseudo"},\n'
              + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_cse2_keep_const_vars;\n"
DECLARATION_NEW = (DECLARATION_OLD + "extern int flag_rac2_loop_exit_dup_first_pass;\n"
                   "extern int flag_rac2_sched_defer_const_after_death;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = ["jump.c", "haifa-sched.c", "toplev.c", "flags.h"]
    s = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    if any("flag_rac2_loop_exit_dup_first_pass" in text for text in s.values()):
        raise ValueError("d4948 rules already present")
    s["jump.c"] = replace_once(s["jump.c"], JUMP_OLD, JUMP_NEW, "jump loop-exit test")
    h = s["haifa-sched.c"]
    for label, old, new in (("helpers", HELPER_OLD, HELPER_NEW), ("init", INIT_OLD, INIT_NEW),
                            ("reset", RESET_OLD, RESET_NEW), ("test", TEST_OLD, TEST_NEW),
                            ("prev", PREV_OLD, PREV_NEW)):
        h = replace_once(h, old, new, f"haifa {label}")
    s["haifa-sched.c"] = h
    s["toplev.c"] = replace_once(s["toplev.c"], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    s["toplev.c"] = replace_once(s["toplev.c"], OPTION_OLD, OPTION_NEW, "option table")
    s["flags.h"] = replace_once(s["flags.h"], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for name in names:
        (gcc / name).write_text(s[name], encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
