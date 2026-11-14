#!/usr/bin/env python3
"""Add two opt-in switches for func_002B44C0.

- -frac2-gcse-hash-pseudo-spread (gcse.c hash_expr_1): a pseudo register hashes as
  regno + 16 * (regno - LAST_VIRTUAL_REGISTER); hard registers keep their number. Only PRE's
  bucket walk (reaching-register creation, hence spill-slot order) changes. Used with
  -frac2-gcse-hash-111; any step 15..22 fits, 16 is fixed here.
- -frac2-reorg-reverse-filled-branch (reorg.c relax_delay_slots, last pass only): a conditional
  branch with a filled, non-annulled delay slot, predicted not taken, followed by an unfilled
  unconditional jump, has its targets swapped (stock does this only for an unfilled branch).

Forced on they change 92 and 185 units: opt-in per-unit models under the owner's standard of
12 November 2026. Default compilation is unchanged.

Usage: b44c0_rules.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'gcse.c': [('\thash += ((unsigned) REG << 7) + regno;', '\t/* RAC2: -frac2-gcse-hash-pseudo-spread.  */\n\tif (flag_rac2_gcse_hash_pseudo_spread && regno > LAST_VIRTUAL_REGISTER)\n\t  regno += 16 * (regno - LAST_VIRTUAL_REGISTER);\n\thash += ((unsigned) REG << 7) + regno;')], 'reorg.c': [('      if (GET_CODE (insn) == JUMP_INSN\n\t  && (simplejump_p (insn) || GET_CODE (PATTERN (insn)) == RETURN)\n\t  && (other = prev_active_insn (insn)) != 0\n', '      /* RAC2: -frac2-reorg-reverse-filled-branch.  */\n      if (flag_rac2_reorg_reverse_filled_branch\n\t  && reorg_pass_number == MAX_REORG_PASSES - 1\n\t  && GET_CODE (insn) == JUMP_INSN\n\t  && simplejump_p (insn)\n\t  && (other = prev_active_insn (insn)) != 0\n\t  && GET_CODE (other) == INSN\n\t  && GET_CODE (PATTERN (other)) == SEQUENCE\n\t  && GET_CODE (XVECEXP (PATTERN (other), 0, 0)) == JUMP_INSN\n\t  && condjump_p (XVECEXP (PATTERN (other), 0, 0))\n\t  && ! INSN_ANNULLED_BRANCH_P (XVECEXP (PATTERN (other), 0, 0))\n\t  && JUMP_LABEL (XVECEXP (PATTERN (other), 0, 0)) != 0\n\t  && no_labels_between_p (other, insn)\n\t  && 0 >= mostly_true_jump (XVECEXP (PATTERN (other), 0, 0),\n\t\t\t\t    get_branch_condition\n\t\t\t\t    (XVECEXP (PATTERN (other), 0, 0),\n\t\t\t\t     JUMP_LABEL (XVECEXP (PATTERN (other),\n\t\t\t\t\t\t\t  0, 0)))))\n\t{\n\t  rtx oj = XVECEXP (PATTERN (other), 0, 0);\n\t  rtx other_target = JUMP_LABEL (oj);\n\t  int k;\n\n\t  target_label = JUMP_LABEL (insn);\n\t  ++LABEL_NUSES (other_target);\n\t  if (invert_jump (oj, target_label))\n\t    {\n\t      reorg_redirect_jump (insn, other_target);\n\t      for (k = 1; k < XVECLEN (PATTERN (other), 0); k++)\n\t\tINSN_FROM_TARGET_P (XVECEXP (PATTERN (other), 0, k))\n\t\t  = ! INSN_FROM_TARGET_P (XVECEXP (PATTERN (other), 0, k));\n\t    }\n\t  --LABEL_NUSES (other_target);\n\t}\n\n      if (GET_CODE (insn) == JUMP_INSN\n\t  && (simplejump_p (insn) || GET_CODE (PATTERN (insn)) == RETURN)\n\t  && (other = prev_active_insn (insn)) != 0\n')]}

DEFINITION_OLD = "int flag_rac2_sched_defer_const_after_death = 0;\n"
DEFINITION_NEW = DEFINITION_OLD + 'int flag_rac2_gcse_hash_pseudo_spread = 0;\nint flag_rac2_reorg_reverse_filled_branch = 0;\n'
OPTION_OLD = '  {"rac2-sched-defer-const-after-death", &flag_rac2_sched_defer_const_after_death, 1,\n'
OPTION_NEW = '  {"rac2-gcse-hash-pseudo-spread", &flag_rac2_gcse_hash_pseudo_spread, 1,\n   "Spread pseudo registers apart in gcse\'s expression hash"},\n  {"rac2-reorg-reverse-filled-branch", &flag_rac2_reorg_reverse_filled_branch, 1,\n   "Reverse a filled not-taken branch over an unfilled jump in the last reorg pass"},\n' + OPTION_OLD
DECLARATION_OLD = "extern int flag_rac2_sched_defer_const_after_death;\n"
DECLARATION_NEW = DECLARATION_OLD + 'extern int flag_rac2_gcse_hash_pseudo_spread;\nextern int flag_rac2_reorg_reverse_filled_branch;\n'


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    names = list(HUNKS) + ["toplev.c", "flags.h"]
    s = {name: (gcc / name).read_text(encoding="latin-1") for name in names}
    if any("flag_rac2_gcse_hash_pseudo_spread" in text for text in s.values()):
        raise ValueError("b44c0_rules options already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            s[name] = replace_once(s[name], old, new, f"{name} hunk {k}")
    s["toplev.c"] = replace_once(s["toplev.c"], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    s["toplev.c"] = replace_once(s["toplev.c"], OPTION_OLD, OPTION_NEW, "option table")
    s["flags.h"] = replace_once(s["flags.h"], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for name in names:
        (gcc / name).write_text(s[name], encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
