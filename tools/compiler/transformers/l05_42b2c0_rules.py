#!/usr/bin/env python3
"""Add eight opt-in loop, cse and scheduling switches, first needed by
func_L05_0042B2C0.

-frac2-loop-no-equal-copy-subst: loop does not fold a pseudo copy that carries a REG_EQUAL
note (a GCSE reaching-register copy) into its single use.
-frac2-loop-move-high-copy: loop motion moves a pseudo copy of a symbol's high part as the
copy, not rebuilt from its REG_EQUAL note.
-frac2-rerun-loop-move-consts: the second pass of -frerun-loop-opt always moves an invariant
insn whose value is a symbolic constant out of a loop.
-frac2-rerun-loop-no-reverse: the second pass of -frerun-loop-opt does not reverse a loop.
-frac2-loop-ivs-in-order: strength reduction visits the induction variable classes in the
order their bivs were found (stock visits them last found first).
-frac2-cse2-loop-end-forgets-arith: after loop, at a loop end, cse forgets the value of each
pseudo set inside that loop from a sum or product.
-frac2-sched-phony-loop-notes: before scheduling, the loop notes of a do { } while (0)
group are deleted, so the group is no scheduling barrier.
-frac2-sched1-order: before reload, the scheduler issues the insns named by
`#pragma rac2_sched1_order UID...' in the listed order, one per cycle, where the
dependences allow. The list belongs to the next function compiled and is dropped after
its first scheduling pass. This is an instruction-order hint, not a model of the retail
compiler: by owner ruling of 14 November 2026 it is the fakematch mechanism of
func_L05_0042B2C0 only.

Opt-in per-unit switches under the owner's standard of 12 November 2026. Default
compilation is unchanged.

Usage: l05_42b2c0_rules.py <gcc directory>
"""
import sys
from pathlib import Path

FLAGS = [
    ("loop_no_equal_copy_subst", "loop-no-equal-copy-subst",
     "Loop does not fold a pseudo copy carrying a REG_EQUAL note into its single use"),
    ("loop_move_high_copy", "loop-move-high-copy",
     "Loop motion moves a pseudo copy of a symbol's high part as a copy"),
    ("rerun_loop_move_consts", "rerun-loop-move-consts",
     "The rerun loop pass always moves invariant symbolic constants out of a loop"),
    ("rerun_loop_no_reverse", "rerun-loop-no-reverse",
     "The rerun loop pass does not reverse a loop"),
    ("loop_ivs_in_order", "loop-ivs-in-order",
     "Strength-reduce induction variable classes in the order their bivs were found"),
    ("cse2_loop_end_forgets_arith", "cse2-loop-end-forgets-arith",
     "After loop, at a loop end, forget pseudos set inside the loop from a sum or product"),
    ("sched_phony_loop_notes", "sched-phony-loop-notes",
     "Delete the loop notes of a do { } while (0) group before scheduling"),
    ("sched1_order", "sched1-order",
     "Before reload, schedule the insns named by #pragma rac2_sched1_order in that order"),
]

HEAD = "/* RAC2: opt-in rules of func_L05_0042B2C0.  */\n"
DECLS = HEAD + "".join(f"extern int flag_rac2_{n};\n" for n, _, _ in FLAGS)
DEFS = "\n" + HEAD + "".join(f"int flag_rac2_{n} = 0;\n" for n, _, _ in FLAGS)
OPTS = "".join(f'  {{"rac2-{o}", &flag_rac2_{n}, 1,\n   "{d}"}},\n' for n, o, d in FLAGS)

L17_DECL = "extern int flag_rac2_sched2_qi_store_offset;\n"
L17_DEF = "int flag_rac2_sched2_qi_store_offset = 0;\n"
L17_OPT = ('  {"rac2-sched2-qi-store-offset", &flag_rac2_sched2_qi_store_offset, 1,\n'
           '   "After reload, tied byte stores to one base go by lower displacement"},\n')

ORDER_SUPPORT = """\
/* RAC2: -frac2-sched1-order.  rac2_order_key[UID] is the 1-based place of
   insn UID in the list given by #pragma rac2_sched1_order, or 0.  The
   list belongs to the next function scheduled and is dropped after its
   first scheduling pass.  */
static int *rac2_order_key;
static int rac2_order_size;
static int rac2_order_n;

void
rac2_sched1_order_add (uid)
     int uid;
{
  if (uid < 0)
    return;
  if (uid >= rac2_order_size)
    {
      int n = (uid + 1) * 2;
      int *t = (int *) xcalloc (n, sizeof (int));
      if (rac2_order_key)
	{
	  bcopy ((char *) rac2_order_key, (char *) t,
		 rac2_order_size * sizeof (int));
	  free (rac2_order_key);
	}
      rac2_order_key = t;
      rac2_order_size = n;
    }
  rac2_order_key[uid] = ++rac2_order_n;
}

/* RAC2: the -frac2-sched1-order place of INSN, or 0.  */
static int
rac2_order_of (insn)
     rtx insn;
{
  int uid = INSN_UID (insn);
  if (!flag_rac2_sched1_order || reload_completed || uid >= rac2_order_size)
    return 0;
  return rac2_order_key[uid];
}

"""

PHONY_SUPPORT = """\
/* RAC2: the loop notes of phony loops (do { } while (0)) found by the
   last loop pass, for -frac2-sched-phony-loop-notes.  */
#define RAC2_MAX_PHONY 64
static rtx rac2_phony[RAC2_MAX_PHONY][2];
static int rac2_n_phony;

/* RAC2: -frac2-sched-phony-loop-notes: before scheduling, delete the
   loop notes of the phony loops the last loop pass found, so that a
   do { } while (0) group is no scheduling barrier.  */
void
rac2_delete_phony_loop_notes ()
{
  int i, j;
  for (i = 0; i < rac2_n_phony; i++)
    for (j = 0; j < 2; j++)
      {
	rtx note = rac2_phony[i][j];
	if (GET_CODE (note) == NOTE
	    && (NOTE_LINE_NUMBER (note) == NOTE_INSN_LOOP_BEG
		|| NOTE_LINE_NUMBER (note) == NOTE_INSN_LOOP_END))
	  {
	    NOTE_LINE_NUMBER (note) = NOTE_INSN_DELETED;
	    NOTE_SOURCE_FILE (note) = 0;
	  }
      }
  rac2_n_phony = 0;
}

/* RAC2: nonzero during the second loop pass of -frerun-loop-opt.  */
static int rac2_loop_rerun_pass;

"""

HUNKS = {
    "flags.h": [(L17_DECL, L17_DECL + DECLS)],
    "toplev.c": [
        (L17_DEF, L17_DEF + DEFS),
        (L17_OPT, L17_OPT + OPTS),
        ("  /* Print function header into sched dump now\n"
         "     because doing the sched analysis makes some of the dump.  */\n",
         "  /* RAC2: -frac2-sched-phony-loop-notes.  */\n"
         "  if (optimize > 0 && flag_rac2_sched_phony_loop_notes)\n"
         "    {\n"
         "      extern void rac2_delete_phony_loop_notes PROTO((void));\n"
         "      rac2_delete_phony_loop_notes ();\n"
         "    }\n"
         "\n"
         "  /* Print function header into sched dump now\n"
         "     because doing the sched analysis makes some of the dump.  */\n"),
    ],
    "c-lex.c": [
        ("\t      if (c == '\\n')\n"
         "\t\treturn c;\n"
         "\n"
         "#if defined HANDLE_PRAGMA || defined HANDLE_GENERIC_PRAGMAS\n"
         "\t      UNGETC (c);\n"
         "\t      token = yylex ();\n",
         "\t      if (c == '\\n')\n"
         "\t\treturn c;\n"
         "\n"
         "#if !defined HANDLE_PRAGMA && !defined HANDLE_GENERIC_PRAGMAS\n"
         "\t      /* RAC2: #pragma rac2_sched1_order UID... names insns for\n"
         "\t\t -frac2-sched1-order; a unit may use several such lines.  */\n"
         "\t      {\n"
         "\t\tstatic char rac2_name[] = \"rac2_sched1_order\";\n"
         "\t\textern void rac2_sched1_order_add PROTO((int));\n"
         "\t\tint k = 0;\n"
         "\n"
         "\t\twhile (rac2_name[k] && c == rac2_name[k])\n"
         "\t\t  c = GETC (), k++;\n"
         "\t\tif (rac2_name[k] == 0 && (c == ' ' || c == '\\t'))\n"
         "\t\t  for (;;)\n"
         "\t\t    {\n"
         "\t\t      int n = 0, any = 0;\n"
         "\n"
         "\t\t      while (c == ' ' || c == '\\t')\n"
         "\t\t\tc = GETC ();\n"
         "\t\t      while (c >= '0' && c <= '9')\n"
         "\t\t\tn = n * 10 + (c - '0'), any = 1, c = GETC ();\n"
         "\t\t      if (!any)\n"
         "\t\t\tbreak;\n"
         "\t\t      rac2_sched1_order_add (n);\n"
         "\t\t    }\n"
         "\t\tUNGETC (c);\n"
         "\t\tgoto skipline;\n"
         "\t      }\n"
         "#endif\n"
         "\n"
         "#if defined HANDLE_PRAGMA || defined HANDLE_GENERIC_PRAGMAS\n"
         "\t      UNGETC (c);\n"
         "\t      token = yylex ();\n"),
    ],
    "cse.c": [
        ("      /* See if this is a branch that is part of the path.  If so, and it is\n"
         "\t to be taken, do so.  */\n",
         "      /* RAC2: -frac2-cse2-loop-end-forgets-arith: after loop, at a\n"
         "\t LOOP_END note, each pseudo set inside that loop from a PLUS or MULT\n"
         "\t loses its recorded value (invalidate, as for a clobber).  */\n"
         "      if (code == NOTE && NOTE_LINE_NUMBER (insn) == NOTE_INSN_LOOP_END\n"
         "\t  && rac2_cse_after_loop && flag_rac2_cse2_loop_end_forgets_arith)\n"
         "\t{\n"
         "\t  rtx p, s;\n"
         "\t  int depth = 0;\n"
         "\n"
         "\t  for (p = PREV_INSN (insn); p; p = PREV_INSN (p))\n"
         "\t    {\n"
         "\t      if (GET_CODE (p) == NOTE\n"
         "\t\t  && NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_END)\n"
         "\t\tdepth++;\n"
         "\t      else if (GET_CODE (p) == NOTE\n"
         "\t\t       && NOTE_LINE_NUMBER (p) == NOTE_INSN_LOOP_BEG)\n"
         "\t\t{\n"
         "\t\t  if (depth == 0)\n"
         "\t\t    break;\n"
         "\t\t  depth--;\n"
         "\t\t}\n"
         "\t      else if (GET_RTX_CLASS (GET_CODE (p)) == 'i'\n"
         "\t\t       && (s = single_set (p)) != 0\n"
         "\t\t       && GET_CODE (SET_DEST (s)) == REG\n"
         "\t\t       && REGNO (SET_DEST (s)) >= FIRST_PSEUDO_REGISTER\n"
         "\t\t       && (GET_CODE (SET_SRC (s)) == PLUS\n"
         "\t\t\t   || GET_CODE (SET_SRC (s)) == MULT))\n"
         "\t\tinvalidate (SET_DEST (s), VOIDmode);\n"
         "\t    }\n"
         "\t}\n"
         "\n"
         "      /* See if this is a branch that is part of the path.  If so, and it is\n"
         "\t to be taken, do so.  */\n"),
    ],
    "loop.c": [
        ("void\n"
         "loop_optimize (f, dumpfile, unroll_p, bct_p)\n",
         PHONY_SUPPORT +
         "void\n"
         "loop_optimize (f, dumpfile, unroll_p, bct_p)\n"),
        ("  loop_dump_stream = dumpfile;\n"
         "\n"
         "  init_recog_no_volatile ();\n",
         "  loop_dump_stream = dumpfile;\n"
         "  rac2_loop_rerun_pass = flag_rerun_loop_opt && bct_p;\n"
         "  rac2_n_phony = 0;\n"
         "\n"
         "  init_recog_no_volatile ();\n"),
        ("\tfprintf (loop_dump_stream, \"\\nLoop from %d to %d is phony.\\n\\n\",\n"
         "\t\t INSN_UID (loop_start), INSN_UID (end));\n"
         "      return;\n",
         "\tfprintf (loop_dump_stream, \"\\nLoop from %d to %d is phony.\\n\\n\",\n"
         "\t\t INSN_UID (loop_start), INSN_UID (end));\n"
         "      if (bct_p && rac2_n_phony < RAC2_MAX_PHONY\n"
         "\t  && GET_CODE (loop_start) == NOTE && GET_CODE (end) == NOTE\n"
         "\t  && NOTE_LINE_NUMBER (loop_start) == NOTE_INSN_LOOP_BEG\n"
         "\t  && NOTE_LINE_NUMBER (end) == NOTE_INSN_LOOP_END)\n"
         "\t{\n"
         "\t  rac2_phony[rac2_n_phony][0] = loop_start;\n"
         "\t  rac2_phony[rac2_n_phony][1] = end;\n"
         "\t  rac2_n_phony++;\n"
         "\t}\n"
         "      return;\n"),
        ("\t      if (temp && CONSTANT_P (XEXP (temp, 0)))\n"
         "\t\tsrc = XEXP (temp, 0), move_insn = 1;\n",
         "\t      if (temp && CONSTANT_P (XEXP (temp, 0))\n"
         "\t\t  /* RAC2: a copy of another pseudo whose REG_EQUAL value is\n"
         "\t\t     a HIGH is moved as the copy, not rebuilt from the note.  */\n"
         "\t\t  && ! (flag_rac2_loop_move_high_copy\n"
         "\t\t\t&& GET_CODE (src) == REG\n"
         "\t\t\t&& REGNO (src) >= FIRST_PSEUDO_REGISTER\n"
         "\t\t\t&& GET_CODE (XEXP (temp, 0)) == HIGH))\n"
         "\t\tsrc = XEXP (temp, 0), move_insn = 1;\n"),
        ("\t      if (loop_has_call\n"
         "\t\t  && VARRAY_RTX (reg_single_usage, regno) != 0\n",
         "\t      if (loop_has_call\n"
         "\t\t  /* RAC2: a copy of another pseudo that carries a REG_EQUAL\n"
         "\t\t     note (a GCSE reaching-register copy) is not folded into\n"
         "\t\t     its single use.  */\n"
         "\t\t  && ! (flag_rac2_loop_no_equal_copy_subst\n"
         "\t\t\t&& GET_CODE (SET_SRC (set)) == REG\n"
         "\t\t\t&& REGNO (SET_SRC (set)) >= FIRST_PSEUDO_REGISTER\n"
         "\t\t\t&& find_reg_note (p, REG_EQUAL, NULL_RTX))\n"
         "\t\t  && VARRAY_RTX (reg_single_usage, regno) != 0\n"),
        ("\t      || (m->forces && m->forces->done\n"
         "\t\t  && VARRAY_INT (n_times_set, m->forces->regno) == 1))\n",
         "\t      || (m->forces && m->forces->done\n"
         "\t\t  && VARRAY_INT (n_times_set, m->forces->regno) == 1)\n"
         "\t      /* RAC2: -frac2-rerun-loop-move-consts: in the second pass of\n"
         "\t\t -frerun-loop-opt, an invariant insn whose value is a\n"
         "\t\t symbolic constant is always moved out of the loop.  */\n"
         "\t      || (flag_rac2_rerun_loop_move_consts && rac2_loop_rerun_pass\n"
         "\t\t  && m->move_insn && GET_CODE (m->set_src) == CONST))\n"),
        ("  reg_map = (rtx *) alloca (reg_map_size * sizeof (rtx));\n"
         "  bzero ((char *) reg_map, reg_map_size * sizeof (rtx));\n"
         "\n"
         "  /* Examine each iv class for feasibility of strength reduction/induction\n",
         "  reg_map = (rtx *) alloca (reg_map_size * sizeof (rtx));\n"
         "  bzero ((char *) reg_map, reg_map_size * sizeof (rtx));\n"
         "\n"
         "  /* RAC2: -frac2-loop-ivs-in-order: strength-reduce the induction variable\n"
         "     classes in the order their bivs were found in the loop (record_biv\n"
         "     prepends each new class).  */\n"
         "  if (flag_rac2_loop_ivs_in_order)\n"
         "    {\n"
         "      struct iv_class *prev = 0, *nx;\n"
         "      for (bl = loop_iv_list; bl; bl = nx)\n"
         "\t{\n"
         "\t  nx = bl->next;\n"
         "\t  bl->next = prev;\n"
         "\t  prev = bl;\n"
         "\t}\n"
         "      loop_iv_list = prev;\n"
         "    }\n"
         "\n"
         "  /* Examine each iv class for feasibility of strength reduction/induction\n"),
        ("\t    fprintf (loop_dump_stream, \"Can reverse loop\\n\");\n",
         "\t    fprintf (loop_dump_stream, \"Can reverse loop\\n\");\n"
         "\n"
         "\t  /* RAC2: -frac2-rerun-loop-no-reverse: the second (rerun) loop\n"
         "\t     pass does not reverse a loop.  */\n"
         "\t  if (flag_rac2_rerun_loop_no_reverse && rac2_loop_rerun_pass)\n"
         "\t    return 0;\n"),
    ],
    "haifa-sched.c": [
        ("HAIFA_INLINE static int\n"
         "insn_cost (insn, link, used)\n"
         "     rtx insn, link, used;\n"
         "{\n"
         "  register int cost = INSN_COST (insn);\n",
         ORDER_SUPPORT +
         "HAIFA_INLINE static int\n"
         "insn_cost (insn, link, used)\n"
         "     rtx insn, link, used;\n"
         "{\n"
         "  register int cost = INSN_COST (insn);\n"
         "\n"
         "  /* RAC2: -frac2-sched1-order: a dependence between two listed insns\n"
         "     costs one cycle.  */\n"
         "  if (used && rac2_order_of (insn) && rac2_order_of (used))\n"
         "    return 1;\n"),
        ("  int val, priority_val, spec_val, prob_val, weight_val;\n"
         "  extern char *mips_astra_keep_frame_order;\n",
         "  int val, priority_val, spec_val, prob_val, weight_val;\n"
         "  extern char *mips_astra_keep_frame_order;\n"
         "\n"
         "  /* RAC2: -frac2-sched1-order: two listed insns go in list order.  */\n"
         "  if (rac2_order_of (tmp) && rac2_order_of (tmp2))\n"
         "    return rac2_order_of (tmp) - rac2_order_of (tmp2);\n"),
        ("      can_issue_more = issue_rate;\n",
         "      can_issue_more = issue_rate;\n"
         "      /* RAC2: -frac2-sched1-order: listed insns issue one per cycle.  */\n"
         "      if (n_ready > 0 && rac2_order_of (ready[n_ready - 1]))\n"
         "\tcan_issue_more = 1;\n"),
        ("\t  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);\n",
         "\t  int cost = actual_hazard (insn_unit (insn), insn, clock_var, 0);\n"
         "\n"
         "\t  /* RAC2: -frac2-sched1-order: a listed insn never waits for a\n"
         "\t     function unit.  */\n"
         "\t  if (rac2_order_of (insn))\n"
         "\t    cost = 0;\n"),
        ("  if (out_edges)\n"
         "    {\n"
         "      free (out_edges);\n"
         "      out_edges = NULL;\n"
         "    }\n",
         "  if (out_edges)\n"
         "    {\n"
         "      free (out_edges);\n"
         "      out_edges = NULL;\n"
         "    }\n"
         "\n"
         "  /* RAC2: -frac2-sched1-order: the list served this function's first\n"
         "     pass; the next function starts with none.  */\n"
         "  if (!reload_completed && rac2_order_n)\n"
         "    {\n"
         "      bzero ((char *) rac2_order_key, rac2_order_size * sizeof (int));\n"
         "      rac2_order_n = 0;\n"
         "    }\n"),
    ],
}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_sched1_order" in text for text in sources.values()):
        raise ValueError("L05_0042B2C0 rules already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
