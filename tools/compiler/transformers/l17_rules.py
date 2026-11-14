#!/usr/bin/env python3
"""Add nine opt-in expansion, combine and scheduling rules, first needed by
func_L17_003E8A58.

-frac2-register-scope: a variable declared `register' stays live through the end of its
scope when optimizing too (stock GCC does this only with -fno-optimize's obey_regdecls).
-frac2-keep-user-copies-strict: combine substitutes nothing into a pseudo-to-pseudo copy
into a user variable (-frac2-keep-user-copies only keeps the copy itself from being
folded forward).
-frac2-sched-flush-30: the scheduler flushes its pending memory lists once they exceed 30
entries (stock 32).
-frac2-sched1-priority-only: before reload, ties after priority skip the register-weight and
dependent-count keys.
-frac2-sched-uservar-const-no-boost: a constant loaded into a user variable is not promoted
to the top ready priority as a register birth.
-frac2-sched-uservar-copy-priority: before reload, a register copy into a user variable counts
4 extra cycles on the critical path of its true dependences.
-frac2-sched2-fp-symbol-load-latency-3: after reload, a floating-point load from a symbol's
address has a result latency of 3.
-frac2-sched2-fp-const-first-consumer: after reload, on a full tie between two constant loads
into floating-point registers, the one whose earliest true dependent in the block comes
first goes first.
-frac2-sched2-qi-store-offset: after reload, on a full tie between two byte stores to the
same base register, the lower displacement goes first.

Opt-in per-unit models under the owner's standard of 12 November 2026. Default
compilation is unchanged.

Usage: l17_rules.py <gcc directory>
"""
import sys
from pathlib import Path

FLAGS = [
    ("register_scope", "register-scope",
     "Keep a register variable live through the end of its scope when optimizing"),
    ("keep_user_copies_strict", "keep-user-copies-strict",
     "combine substitutes nothing into a register copy into a user variable"),
    ("sched_flush_30", "sched-flush-30",
     "Flush the scheduler's pending memory lists beyond 30 entries"),
    ("sched1_priority_only", "sched1-priority-only",
     "Before reload, skip the register-weight and dependent-count tie keys"),
    ("sched_uservar_const_no_boost", "sched-uservar-const-no-boost",
     "Do not promote a constant load into a user variable as a register birth"),
    ("sched_uservar_copy_priority", "sched-uservar-copy-priority",
     "Before reload, a register copy into a user variable counts 4 extra cycles"),
    ("sched2_fp_symbol_load_latency_3", "sched2-fp-symbol-load-latency-3",
     "After reload, a floating-point load from a symbol has a latency of 3"),
    ("sched2_fp_const_first_consumer", "sched2-fp-const-first-consumer",
     "After reload, tied FP constant loads go in the order of their first consumers"),
    ("sched2_qi_store_offset", "sched2-qi-store-offset",
     "After reload, tied byte stores to one base go by lower displacement"),
]

HEAD = "/* RAC2: opt-in rules of func_L17_003E8A58.  */\n"
DECLS = HEAD + "".join(f"extern int flag_rac2_{n};\n" for n, _, _ in FLAGS)
DEFS = "\n" + HEAD + "".join(f"int flag_rac2_{n} = 0;\n" for n, _, _ in FLAGS)
OPTS = "".join(f'  {{"rac2-{o}", &flag_rac2_{n}, 1,\n   "{d}"}},\n' for n, o, d in FLAGS)

KUC_DECL = "extern int flag_rac2_keep_user_copies;\n"
KUC_DEF = "int flag_rac2_keep_user_copies = 0;\n"
KUC_OPT = ('  {"rac2-keep-user-copies", &flag_rac2_keep_user_copies, 1,\n'
           '   "Keep register copies into user variables through cse and combine"},\n')

USERVAR_COPY = """\
/* RAC2: a register copy from a pseudo into a pseudo that is a user
   variable.  */
static int
rac2_uservar_copy_p (insn)
     rtx insn;
{
  rtx set = single_set (insn);
  return (set && GET_CODE (SET_DEST (set)) == REG
	  && GET_CODE (SET_SRC (set)) == REG
	  && REGNO (SET_DEST (set)) >= FIRST_PSEUDO_REGISTER
	  && REGNO (SET_SRC (set)) >= FIRST_PSEUDO_REGISTER
	  && REG_USERVAR_P (SET_DEST (set)));
}

/* RAC2: the LUID of INSN's earliest true dependent in its own block.  */
static int
rac2_first_consumer_luid (insn)
     rtx insn;
{
  rtx link;
  int luid = 0x7fffffff;
  for (link = INSN_DEPEND (insn); link; link = XEXP (link, 1))
    if (REG_NOTE_KIND (link) == 0
	&& INSN_BLOCK (XEXP (link, 0)) == INSN_BLOCK (insn)
	&& INSN_LUID (XEXP (link, 0)) < luid)
      luid = INSN_LUID (XEXP (link, 0));
  return luid;
}

/* RAC2: a QImode store to (plus REG CONST_INT); sets *BASE and *OFF.  */
static int
rac2_qi_store_p (insn, base, off)
     rtx insn;
     int *base;
     HOST_WIDE_INT *off;
{
  rtx set = single_set (insn);
  rtx addr;
  if (! set || GET_CODE (SET_DEST (set)) != MEM
      || GET_MODE (SET_DEST (set)) != QImode)
    return 0;
  addr = XEXP (SET_DEST (set), 0);
  if (GET_CODE (addr) != PLUS || GET_CODE (XEXP (addr, 0)) != REG
      || GET_CODE (XEXP (addr, 1)) != CONST_INT)
    return 0;
  *base = REGNO (XEXP (addr, 0));
  *off = INTVAL (XEXP (addr, 1));
  return 1;
}

"""

HUNKS = {
    "flags.h": [(KUC_DECL, KUC_DECL + DECLS)],
    "toplev.c": [(KUC_DEF, KUC_DEF + DEFS), (KUC_OPT, KUC_OPT + OPTS)],
    "stmt.c": [(
        "\tif (TREE_CODE (decl) == VAR_DECL && rtl != 0)\n"
        "\t  use_variable (rtl);\n"
        "      }\n",
        "\tif (TREE_CODE (decl) == VAR_DECL && rtl != 0)\n"
        "\t  use_variable (rtl);\n"
        "      }\n"
        "  /* RAC2: -frac2-register-scope: a variable declared `register' stays\n"
        "     live through the end of its scope when optimizing too.  */\n"
        "  else if (flag_rac2_register_scope)\n"
        "    for (decl = vars; decl; decl = TREE_CHAIN (decl))\n"
        "      {\n"
        "\trtx rtl = DECL_RTL (decl);\n"
        "\tif (TREE_CODE (decl) == VAR_DECL && DECL_REGISTER (decl)\n"
        "\t    && rtl != 0 && GET_CODE (rtl) == REG)\n"
        "\t  use_variable (rtl);\n"
        "      }\n")],
    "combine.c": [(
        "  combine_attempts++;\n",
        "  /* RAC2: -frac2-keep-user-copies-strict: nothing is substituted into a\n"
        "     pseudo-to-pseudo copy into a user variable.  */\n"
        "  if (flag_rac2_keep_user_copies_strict\n"
        "      && GET_CODE (PATTERN (i3)) == SET\n"
        "      && GET_CODE (SET_DEST (PATTERN (i3))) == REG\n"
        "      && GET_CODE (SET_SRC (PATTERN (i3))) == REG\n"
        "      && REGNO (SET_DEST (PATTERN (i3))) >= FIRST_PSEUDO_REGISTER\n"
        "      && REGNO (SET_SRC (PATTERN (i3))) >= FIRST_PSEUDO_REGISTER\n"
        "      && REG_USERVAR_P (SET_DEST (PATTERN (i3))))\n"
        "    return 0;\n"
        "\n"
        "  combine_attempts++;\n")],
    "haifa-sched.c": [
        ("  if (link == 0 && used == 0)\n"
         "    return cost;\n",
         "  if (link == 0 && used == 0)\n"
         "    return cost;\n"
         "\n"
         "  /* RAC2: -frac2-sched2-fp-symbol-load-latency-3: after reload, a\n"
         "     floating-point load from a symbol's address has a result latency\n"
         "     of 3.  */\n"
         "  if (flag_rac2_sched2_fp_symbol_load_latency_3 && reload_completed\n"
         "      && REG_NOTE_KIND (link) == 0)\n"
         "    {\n"
         "      rtx set = single_set (insn);\n"
         "      if (set && GET_CODE (SET_DEST (set)) == REG\n"
         "\t  && GET_CODE (SET_SRC (set)) == MEM\n"
         "\t  && FP_REG_P (REGNO (SET_DEST (set))) && cost < 3\n"
         "\t  && GET_CODE (XEXP (SET_SRC (set), 0)) == SYMBOL_REF)\n"
         "\treturn 3;\n"
         "    }\n"),
        ("\t    next_priority = insn_cost (insn, link, next) + priority (next);\n",
         "\t    next_priority = insn_cost (insn, link, next) + priority (next);\n"
         "\t    /* RAC2: -frac2-sched-uservar-copy-priority: before reload, a\n"
         "\t       register copy into a user variable counts 4 extra cycles.  */\n"
         "\t    if (flag_rac2_sched_uservar_copy_priority && ! reload_completed\n"
         "\t\t&& REG_NOTE_KIND (link) == 0 && rac2_uservar_copy_p (insn))\n"
         "\t      next_priority += 4;\n"),
        ("      if (pending_lists_length > 32)\n",
         "      /* RAC2: -frac2-sched-flush-30 flushes beyond 30 entries.  */\n"
         "      if (pending_lists_length > (flag_rac2_sched_flush_30 ? 30 : 32))\n"),
        ("  if (!reload_completed &&\n"
         "      (weight_val = INSN_REG_WEIGHT (tmp) - INSN_REG_WEIGHT (tmp2)))\n",
         "  /* RAC2: -frac2-sched1-priority-only skips this key before reload.  */\n"
         "  if (!reload_completed && !flag_rac2_sched1_priority_only &&\n"
         "      (weight_val = INSN_REG_WEIGHT (tmp) - INSN_REG_WEIGHT (tmp2)))\n"),
        ("  val = depend_count2 - depend_count1;\n"
         "  if (val)\n",
         "  val = depend_count2 - depend_count1;\n"
         "  /* RAC2: -frac2-sched1-priority-only skips this key before reload.  */\n"
         "  if (val && (reload_completed || !flag_rac2_sched1_priority_only))\n"),
        ("  /* If insns are equally good, sort by INSN_LUID (original insn order),\n",
         "  /* RAC2: -frac2-sched2-qi-store-offset: on a full sched2 tie between two\n"
         "     byte stores to the same base register, the lower displacement\n"
         "     first.  */\n"
         "  if (flag_rac2_sched2_qi_store_offset && reload_completed)\n"
         "    {\n"
         "      int b1, b2;\n"
         "      HOST_WIDE_INT o1, o2;\n"
         "      if (rac2_qi_store_p (tmp, &b1, &o1) && rac2_qi_store_p (tmp2, &b2, &o2)\n"
         "\t  && b1 == b2 && o1 != o2)\n"
         "\treturn o1 < o2 ? -1 : 1;\n"
         "    }\n"
         "\n"
         "  /* RAC2: -frac2-sched2-fp-const-first-consumer: on a full sched2 tie\n"
         "     between two constant loads into floating-point registers, the one\n"
         "     whose earliest true dependent in the block comes first.  */\n"
         "  if (flag_rac2_sched2_fp_const_first_consumer && reload_completed)\n"
         "    {\n"
         "      rtx s1 = single_set (tmp), s2 = single_set (tmp2);\n"
         "      if (s1 && s2\n"
         "\t  && GET_CODE (SET_DEST (s1)) == REG && GET_CODE (SET_DEST (s2)) == REG\n"
         "\t  && CONSTANT_P (SET_SRC (s1)) && CONSTANT_P (SET_SRC (s2))\n"
         "\t  && FP_REG_P (REGNO (SET_DEST (s1))) && FP_REG_P (REGNO (SET_DEST (s2))))\n"
         "\t{\n"
         "\t  int c1 = rac2_first_consumer_luid (tmp);\n"
         "\t  int c2 = rac2_first_consumer_luid (tmp2);\n"
         "\t  if (c1 != c2)\n"
         "\t    return c1 < c2 ? -1 : 1;\n"
         "\t}\n"
         "    }\n"
         "\n"
         "  /* If insns are equally good, sort by INSN_LUID (original insn order),\n"),
        ("\tcase 0:\n"
         "\t  if (birthing_insn_p (PATTERN (prev)))\n",
         "\tcase 0:\n"
         "\t  /* RAC2: -frac2-sched-uservar-const-no-boost: a constant loaded\n"
         "\t     into a user variable is not promoted as a register birth.  */\n"
         "\t  if (flag_rac2_sched_uservar_const_no_boost\n"
         "\t      && GET_CODE (PATTERN (prev)) == SET\n"
         "\t      && GET_CODE (SET_DEST (PATTERN (prev))) == REG\n"
         "\t      && REG_USERVAR_P (SET_DEST (PATTERN (prev)))\n"
         "\t      && CONSTANT_P (SET_SRC (PATTERN (prev))))\n"
         "\t    break;\n"
         "\t  if (birthing_insn_p (PATTERN (prev)))\n"),
        ("/* Compute the priority number for INSN.  */\n",
         USERVAR_COPY + "/* Compute the priority number for INSN.  */\n"),
    ],
}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_sched2_qi_store_offset" in text for text in sources.values()):
        raise ValueError("L17 rules already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
