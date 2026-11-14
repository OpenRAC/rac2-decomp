#!/usr/bin/env python3
"""Add the opt-in -frac2-fix-scratch-reuse: consecutive float-to-int truncations share a scratch.

fix_truncsfsi2 clobbers an integer SCRATCH that the R5900 template never emits (it prints
`cvt.w.s` and a move from the FP scratch only). reload still gives that scratch a general
register, and the register it picks decides which later moves sched2 may hoist above the
truncation. In func_002FA270 two truncations follow each other in one block (insns 676 and
698); retail's register choice is the one obtained when the second truncation's scratch is
the first one's again, while order_regs_for_reload's stock order gives the first free GPR.

With -frac2-fix-scratch-reuse, order_regs_for_reload moves the general register the previous
reloaded insn of the same block used for its spills to the front of potential_reload_regs,
when that insn and this one are both such truncations. Only the immediately preceding insn
that needed reloads counts. Floating-point scratches, other integer scratches (block moves)
and ordinary reloads are unchanged; so is default compilation.

Forced on for every USA v1.01 C unit it changes no function's bytes (it renames the unemitted
scratch of 5 insns in 4 functions). Letting it skip intervening insns that needed no register
would change func_0028F410; extending it to any integer scratch changes 17 functions, to any
GPR reload 39. A per-unit model (owner ruling, 12 November 2026).

Usage: fix_scratch_reuse.py <gcc directory>
"""
import sys
from pathlib import Path

HELPER_OLD = """/* Choose the order to consider regs for use as reload registers
   based on how much trouble would be caused by spilling one.
   Store them in order of decreasing preference in potential_reload_regs.  */
"""

HELPER_NEW = """/* RAC2: nonzero if INSN is a float-to-integer truncation that clobbers an
   integer SCRATCH (-frac2-fix-scratch-reuse; on the R5900 fix_truncsfsi2
   never emits that scratch).  */

static int
rac2_fix_scratch_p (insn)
     rtx insn;
{
  rtx pat = PATTERN (insn);
  int k;

  if (GET_CODE (pat) != PARALLEL || GET_CODE (XVECEXP (pat, 0, 0)) != SET
      || GET_CODE (SET_SRC (XVECEXP (pat, 0, 0))) != FIX)
    return 0;
  for (k = 1; k < XVECLEN (pat, 0); k++)
    {
      rtx e = XVECEXP (pat, 0, k);
      if (GET_CODE (e) == CLOBBER && GET_CODE (XEXP (e, 0)) == SCRATCH
	  && GET_MODE_CLASS (GET_MODE (XEXP (e, 0))) == MODE_INT)
	return 1;
    }
  return 0;
}

""" + HELPER_OLD

ORDER_OLD = """#endif

  qsort (hard_reg_n_uses, FIRST_PSEUDO_REGISTER,
	 sizeof hard_reg_n_uses[0], hard_reg_use_compare);
"""

ORDER_NEW = """#endif

  /* RAC2: -frac2-fix-scratch-reuse: when this insn and the previous reloaded
     insn of the block are both such truncations, name the general register
     the previous one used again if it is still free.  */
  if (flag_rac2_fix_scratch_reuse && rac2_fix_scratch_p (chain->insn))
    {
      struct insn_chain *pc;

      for (pc = chain->prev; pc && pc->block == chain->block; pc = pc->prev)
	if (pc->need_reload)
	  break;
      if (pc && pc->block == chain->block && rac2_fix_scratch_p (pc->insn))
	for (i = 0; i < o; i++)
	  {
	    int regno = potential_reload_regs[i];

	    if (GP_REG_P (regno)
		&& TEST_HARD_REG_BIT (pc->used_spill_regs, regno))
	      {
		for (; i > 0; i--)
		  potential_reload_regs[i] = potential_reload_regs[i - 1];
		potential_reload_regs[0] = regno;
		break;
	      }
	  }
    }

  qsort (hard_reg_n_uses, FIRST_PSEUDO_REGISTER,
	 sizeof hard_reg_n_uses[0], hard_reg_use_compare);
"""

DEFINITION_OLD = "int flag_rac2_la_funcref_weight = 0;\n"
DEFINITION_NEW = ("int flag_rac2_la_funcref_weight = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, consecutive truncations reuse one integer scratch.  */\n"
                  "int flag_rac2_fix_scratch_reuse = 0;\n")

OPTION_OLD = '  {"rac2-la-funcref-weight", &flag_rac2_la_funcref_weight, 1,\n'
OPTION_NEW = ('  {"rac2-fix-scratch-reuse", &flag_rac2_fix_scratch_reuse, 1,\n'
              '   "Reuse the previous truncation\'s integer scratch in reload"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_la_funcref_weight;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: consecutive truncations reuse one integer scratch.  */\n"
                     "extern int flag_rac2_fix_scratch_reuse;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    reload1, top, flags = gcc / "reload1.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (reload1, top, flags)}
    if any("flag_rac2_fix_scratch_reuse" in text for text in sources.values()):
        raise ValueError("fix-scratch-reuse option already present")
    reload_src = replace_once(sources[reload1], HELPER_OLD, HELPER_NEW, "reload1 helper")
    reload_src = replace_once(reload_src, ORDER_OLD, ORDER_NEW, "reload1 order")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((reload1, reload_src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
