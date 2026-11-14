#!/usr/bin/env python3
"""Add two opt-in switches for func_0028D1E8.

- -frac2-cse2-keep-const-vars (cse.c insert_regs): in the cse pass rerun after loop optimization,
  a user variable set to a constant does not join the quantity of another register holding
  that constant (retail keeps separate 0x8710 copies in $s1/$s2 and still knows `one` = 1.0).
- -frac2-sched-barrier-anti (haifa-sched.c sched_analyze_2): an insn reading a register that the
  scheduling-barrier insn (made a barrier by a loop/EH/setjmp note) does not really set depends
  on it as an anti-dependence, without the barrier insn's result latency.

Forced on alone they change 26 and 0 functions: opt-in per-unit models under the owner's
standard of 12 November 2026. Default compilation is unchanged.

Usage: d1e8_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'cse.c': [["   Nonzero value means that elements of reg_qty have changed\n   so X's hash code may be different.  */\n\nstatic int\ninsert_regs (x, classp, modified)\n     rtx x;\n", "   Nonzero value means that elements of reg_qty have changed\n   so X's hash code may be different.  */\n\n/* RAC2: nonzero while cse runs after loop optimization.  */\nstatic int rac2_cse_after_loop;\n\nstatic int\ninsert_regs (x, classp, modified)\n     rtx x;\n"], ['\t\t classp != 0;\n\t\t classp = classp->next_same_value)\n\t      if (GET_CODE (classp->exp) == REG\n\t\t  && GET_MODE (classp->exp) == GET_MODE (x))\n\t\t{\n\t\t  make_regs_eqv (regno, REGNO (classp->exp));\n\t\t  return 1;\n', '\t\t classp != 0;\n\t\t classp = classp->next_same_value)\n\t      if (GET_CODE (classp->exp) == REG\n\t\t  && GET_MODE (classp->exp) == GET_MODE (x)\n\t\t  /* RAC2: in the cse pass rerun after loop optimization, a\n\t\t     user variable set to a constant does not join the\n\t\t     quantity of another register holding that constant.  */\n\t\t  && ! (flag_rac2_cse2_keep_const_vars\n\t\t\t&& rac2_cse_after_loop\n\t\t\t&& regno >= FIRST_PSEUDO_REGISTER\n\t\t\t&& REG_USERVAR_P (x)\n\t\t\t&& classp->first_same_value->is_const))\n\t\t{\n\t\t  make_regs_eqv (regno, REGNO (classp->exp));\n\t\t  return 1;\n'], ['  register rtx insn = f;\n  register int i;\n\n  cse_jumps_altered = 0;\n  recorded_label_ref = 0;\n  constant_pool_entries_cost = 0;\n', '  register rtx insn = f;\n  register int i;\n\n  rac2_cse_after_loop = after_loop;\n  cse_jumps_altered = 0;\n  recorded_label_ref = 0;\n  constant_pool_entries_cost = 0;\n']], 'haifa-sched.c': [['static void\nsched_analyze_2 (x, insn)', "/* RAC2: the insn made a scheduling barrier by a loop, EH or setjmp note.\n   It becomes the last setter of every register only to keep later insns\n   after it; a later insn reading a register the barrier insn does not\n   really set depends on it for order only (an anti-dependence, without the\n   barrier insn's result latency).  */\nstatic rtx rac2_barrier_insn;\n#define RAC2_BARRIER_DEP_KIND(SETTER, REG) \\\n  (flag_rac2_sched_barrier_anti && (SETTER) == rac2_barrier_insn \\\n   && ! reg_set_p ((REG), (SETTER)) ? REG_DEP_ANTI : 0)\n\nstatic void\nsched_analyze_2 (x, insn)"], ['\t\t  = alloc_INSN_LIST (insn, reg_last_uses[regno + i]);\n\n\t\tfor (u = reg_last_sets[regno + i]; u; u = XEXP (u, 1))\n\t\t  add_dependence (insn, XEXP (u, 0), 0);\n\n\t\t/* ??? This should never happen.  */\n\t\tfor (u = reg_last_clobbers[regno + i]; u; u = XEXP (u, 1))\n', '\t\t  = alloc_INSN_LIST (insn, reg_last_uses[regno + i]);\n\n\t\tfor (u = reg_last_sets[regno + i]; u; u = XEXP (u, 1))\n\t\t  add_dependence (insn, XEXP (u, 0),\n\t\t\t\t  RAC2_BARRIER_DEP_KIND (XEXP (u, 0), x));\n\n\t\t/* ??? This should never happen.  */\n\t\tfor (u = reg_last_clobbers[regno + i]; u; u = XEXP (u, 1))\n'], ['\t    reg_last_uses[regno] = alloc_INSN_LIST (insn, reg_last_uses[regno]);\n\n\t    for (u = reg_last_sets[regno]; u; u = XEXP (u, 1))\n\t      add_dependence (insn, XEXP (u, 0), 0);\n\n\t    /* ??? This should never happen.  */\n\t    for (u = reg_last_clobbers[regno]; u; u = XEXP (u, 1))\n', '\t    reg_last_uses[regno] = alloc_INSN_LIST (insn, reg_last_uses[regno]);\n\n\t    for (u = reg_last_sets[regno]; u; u = XEXP (u, 1))\n\t      add_dependence (insn, XEXP (u, 0),\n\t\t\t      RAC2_BARRIER_DEP_KIND (XEXP (u, 0), x));\n\n\t    /* ??? This should never happen.  */\n\t    for (u = reg_last_clobbers[regno]; u; u = XEXP (u, 1))\n'], ['\t\tadd_dependence (insn, XEXP (u, 0), 0);\n\t    }\n\t  reg_pending_sets_all = 1;\n\n\t  flush_pending_lists (insn, 0);\n\t}\n', '\t\tadd_dependence (insn, XEXP (u, 0), 0);\n\t    }\n\t  reg_pending_sets_all = 1;\n\t  rac2_barrier_insn = insn;\n\n\t  flush_pending_lists (insn, 0);\n\t}\n'], ['  register rtx u;\n  rtx loop_notes = 0;\n\n  for (insn = head;; insn = NEXT_INSN (insn))\n    {\n      if (GET_CODE (insn) == INSN || GET_CODE (insn) == JUMP_INSN)\n', '  register rtx u;\n  rtx loop_notes = 0;\n\n  rac2_barrier_insn = 0;\n  for (insn = head;; insn = NEXT_INSN (insn))\n    {\n      if (GET_CODE (insn) == INSN || GET_CODE (insn) == JUMP_INSN)\n']]}

DEFINITION_OLD = "int flag_rac2_sched_stackaddr = 0;\n"
DEFINITION_NEW = DEFINITION_OLD + "\n/* RAC2: opt-in rules (see this transformer).  */\nint flag_rac2_cse2_keep_const_vars = 0;\nint flag_rac2_sched_barrier_anti = 0;\n"
OPTION_ANCHOR = "&flag_rac2_sched_stackaddr, 1,\n"
DECLARATION_OLD = "extern int flag_rac2_sched_stackaddr;\n"
DECLARATION_NEW = DECLARATION_OLD + "extern int flag_rac2_cse2_keep_const_vars;\nextern int flag_rac2_sched_barrier_anti;\n"


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = list(HUNKS) + ["toplev.c", "flags.h"]
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    top = replace_once(sources["toplev.c"], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    i = top.index(OPTION_ANCHOR)
    start = top.rindex("\n", 0, i) + 1
    top = top[:start] + "  {\"rac2-cse2-keep-const-vars\", &flag_rac2_cse2_keep_const_vars, 1,\n   \"In cse after loop, constant user variables keep their own quantity\"},\n  {\"rac2-sched-barrier-anti\", &flag_rac2_sched_barrier_anti, 1,\n   \"A read of a register a barrier insn does not set is only an anti-dependence\"},\n" + top[start:]
    sources["toplev.c"] = top
    sources["flags.h"] = replace_once(sources["flags.h"], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for name in names:
        (gcc / name).write_text(sources[name], encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
