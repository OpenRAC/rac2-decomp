#!/usr/bin/env python3
"""Add the opt-in -frac2-reload-lone-class-no-rotate and -frac2-reload-reuse-pseudo-reg.

reload1.c's allocate_reload_reg takes spill registers round robin (last_spill_reg).
- -frac2-reload-lone-class-no-rotate: a reload whose class holds a single spill register has
  nothing to rotate, so it does not move the round robin.
- -frac2-reload-reuse-pseudo-reg: an input reload of a pseudo goes back to the spill register
  that last loaded that pseudo, when no insn has stored into that register since (calls and
  labels do not forget it), and does not move the round robin. A per-hard-register record is
  kept and cleared in forget_old_reloads_1.

In func_0028A670 both are needed: the draw-1 truncation's FP scratch ($f1, a one-register class)
no longer moves the pointer, and draw 2's 0x8710 reload returns to $a2, which loaded the same
pseudo in draw 1; the later scratch and loop-counter reloads then land as retail.

Forced on together for every USA v1.01 C unit they change 266 functions (142 and 185 alone):
opt-in per-unit models under the owner's standard of 12 November 2026. With neither flag the
record is still kept but never read, so default compilation is unchanged.

Usage: reload_rotation.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = [('   a round-robin fashion.  */\nstatic int last_spill_reg;\n\n/* Describes order of preference for putting regs into spill_regs.\n   Contains the numbers of all the hard regs, in order most preferred first.\n   This order is different for each function.\n', '   a round-robin fashion.  */\nstatic int last_spill_reg;\n\n/* RAC2: for each hard register, the pseudo whose value allocate_reload_reg\n   last chose it to load, or -1.  Forgotten when an insn stores into the\n   register, but not at calls or labels.  */\nstatic int rac2_spill_last_pseudo[FIRST_PSEUDO_REGISTER];\n\n/* Describes order of preference for putting regs into spill_regs.\n   Contains the numbers of all the hard regs, in order most preferred first.\n   This order is different for each function.\n'), ('  \n  /* Initialize to -1, which means take the first spill register.  */\n  last_spill_reg = -1;\n\n  spilled_pseudos = ALLOCA_REG_SET ();\n', '  \n  /* Initialize to -1, which means take the first spill register.  */\n  last_spill_reg = -1;\n  {\n    int c;\n    for (c = 0; c < FIRST_PSEUDO_REGISTER; c++)\n      rac2_spill_last_pseudo[c] = -1;\n  }\n\n  spilled_pseudos = ALLOCA_REG_SET ();\n'), ("      for (i = 0; i < nr; i++)\n\t/* But don't do this if the reg actually serves as an output\n\t   reload reg in the current instruction.  */\n\tif (n_reloads == 0\n\t    || ! TEST_HARD_REG_BIT (reg_is_output_reload, regno + i))\n\t  CLEAR_HARD_REG_BIT (reg_reloaded_valid, regno + i);\n    }\n\n  /* Since value of X has changed,\n", "      for (i = 0; i < nr; i++)\n\t/* But don't do this if the reg actually serves as an output\n\t   reload reg in the current instruction.  */\n\t{\n\t  rac2_spill_last_pseudo[regno + i] = -1;\n\t  if (n_reloads == 0\n\t      || ! TEST_HARD_REG_BIT (reg_is_output_reload, regno + i))\n\t    CLEAR_HARD_REG_BIT (reg_reloaded_valid, regno + i);\n\t}\n    }\n\n  /* Since value of X has changed,\n"), ("\n  int force_group = reload_nregs[r] > 1 && ! last_reload;\n\n  /* If we want a single register and haven't yet found one,\n     take any reg in the right class and not in use.\n     If we want a consecutive group, here is where we look for it.\n", "\n  int force_group = reload_nregs[r] > 1 && ! last_reload;\n\n  /* RAC2: nonzero if this reload leaves the round robin where it was.  */\n  int rac2_keep = 0;\n  /* RAC2: the pseudo this reload loads (an input reload only), or -1.  */\n  int rac2_pseudo = (reload_in[r] != 0 && reload_out[r] == 0\n\t\t     && reload_in_reg[r] != 0\n\t\t     && GET_CODE (reload_in_reg[r]) == REG\n\t\t     && REGNO (reload_in_reg[r]) >= FIRST_PSEUDO_REGISTER\n\t\t     && reload_nregs[r] == 1\n\t\t     ? (int) REGNO (reload_in_reg[r]) : -1);\n\n  /* RAC2 (-frac2-reload-lone-class-no-rotate): a reload whose class holds\n     a single spill register has nothing to rotate, so it does not move\n     the round robin.  */\n  if (flag_rac2_reload_lone_class_no_rotate)\n    {\n      int k, n = 0;\n\n      for (k = 0; k < n_spills; k++)\n\tif (TEST_HARD_REG_BIT (reg_class_contents[(int) reload_reg_class[r]],\n\t\t\t       spill_regs[k]))\n\t  n++;\n      if (n == 1)\n\trac2_keep = 1;\n    }\n\n  /* RAC2 (-frac2-reload-reuse-pseudo-reg): an input reload of a pseudo\n     goes back to the spill register that last loaded that pseudo, when\n     no insn has stored into that register since, and leaves the round\n     robin where it was.  */\n  if (flag_rac2_reload_reuse_pseudo_reg && rac2_pseudo >= 0)\n    for (i = 0; i < n_spills; i++)\n      {\n\tint regnum = spill_regs[i];\n\n\tif (rac2_spill_last_pseudo[regnum] == rac2_pseudo\n\t    && (reload_reg_free_p (regnum, reload_opnum[r],\n\t\t\t\t   reload_when_needed[r])\n\t\t|| (! TEST_HARD_REG_BIT (reload_reg_used, regnum)\n\t\t    && reload_reg_free_for_value_p (regnum, reload_opnum[r],\n\t\t\t\t\t\t    reload_when_needed[r],\n\t\t\t\t\t\t    reload_in[r],\n\t\t\t\t\t\t    reload_out[r], r, 1)))\n\t    && TEST_HARD_REG_BIT (reg_class_contents[(int) reload_reg_class[r]],\n\t\t\t\t  regnum)\n\t    && HARD_REGNO_MODE_OK (regnum, reload_mode[r])\n\t    && HARD_REGNO_NREGS (regnum, reload_mode[r]) == 1)\n\t  {\n\t    rac2_keep = 1;\n\t    count = 0;\n\t    goto rac2_found;\n\t  }\n      }\n\n  /* If we want a single register and haven't yet found one,\n     take any reg in the right class and not in use.\n     If we want a consecutive group, here is where we look for it.\n"), ('      goto failure;\n    }\n\n  /* I is the index in SPILL_REG_RTX of the reload register we are to\n     allocate.  Get an rtx for it and find its register number.  */\n', '      goto failure;\n    }\n\nrac2_found:\n  /* I is the index in SPILL_REG_RTX of the reload register we are to\n     allocate.  Get an rtx for it and find its register number.  */\n'), ('\t       && ! HARD_REGNO_MODE_OK (regno, GET_MODE (reload_out[r]))))\n\t  {\n\t    /* The reg is OK.  */\n\t    last_spill_reg = i;\n\n\t    /* Mark as in use for this insn the reload regs we use\n\t       for this.  */\n', '\t       && ! HARD_REGNO_MODE_OK (regno, GET_MODE (reload_out[r]))))\n\t  {\n\t    /* The reg is OK.  */\n\t    if (! rac2_keep)\n\t      last_spill_reg = i;\n\t    rac2_spill_last_pseudo[spill_regs[i]] = rac2_pseudo;\n\n\t    /* Mark as in use for this insn the reload regs we use\n\t       for this.  */\n')]

DEFINITION_OLD = "int flag_rac2_la_float_vars_last = 0;\n"
DEFINITION_NEW = (DEFINITION_OLD
                  + "\n/* RAC2: opt-in reload round-robin rules.  */\n"
                    "int flag_rac2_reload_lone_class_no_rotate = 0;\n"
                    "int flag_rac2_reload_reuse_pseudo_reg = 0;\n")
OPTION_OLD = '  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n'
OPTION_NEW = ('  {"rac2-reload-lone-class-no-rotate", &flag_rac2_reload_lone_class_no_rotate, 1,\n'
              '   "A reload whose class has one spill register leaves the round robin alone"},\n'
              '  {"rac2-reload-reuse-pseudo-reg", &flag_rac2_reload_reuse_pseudo_reg, 1,\n'
              '   "Reload a pseudo into the spill register that last loaded it"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_la_float_vars_last;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: opt-in reload round-robin rules.  */\n"
                   "extern int flag_rac2_reload_lone_class_no_rotate;\n"
                   "extern int flag_rac2_reload_reuse_pseudo_reg;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    reload1, top, flags = gcc / "reload1.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (reload1, top, flags)}
    if any("flag_rac2_reload_reuse_pseudo_reg" in text for text in sources.values()):
        raise ValueError("reload rotation options already present")
    src = sources[reload1]
    for k, (old, new) in enumerate(HUNKS):
        src = replace_once(src, old, new, f"reload1 hunk {k}")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((reload1, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
