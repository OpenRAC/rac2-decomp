#!/usr/bin/env python3
"""Add the opt-in -frac2-la-float-vars-last: local-alloc serves floating-point user variables last.

local-alloc orders a block's quantities for hard-register allocation by QTY_CMP_PRI (references
over lifetime) in qty_compare / qty_compare_1. With the switch, a quantity of floating-point mode
whose first pseudo is a user variable (REG_USERVAR_P) is ordered after every other quantity
(compiler temporaries of any mode, integer user variables); within each group the usual priority
and quantity-number order is unchanged. The ordering used for quantities with suggested hard
registers (qty_sugg_compare*) is not changed.

In func_L11_004580E8 case 0 (stores in retail order, six named constants and an inline 0.1f),
the temporary holding 0.1 (priority 1111) is then allocated before gravity (1666) and limit
(1111) and takes $f0; gravity and limit follow in $f1 and $f2, as retail.

An opt-in per-unit model, landed under the owner's standard of 12 November 2026. Default
compilation is unchanged.

Usage: la_float_vars_last.py <gcc directory>
"""
import sys
from pathlib import Path

HELPER_OLD = """static int
qty_compare (q1, q2)
     int q1, q2;
{
  return QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);
}"""
HELPER_NEW = """/* RAC2: -frac2-la-float-vars-last: nonzero if quantity Q is a floating-point
   user variable rather than a compiler temporary or an integer.  */
#define RAC2_QTY_FLOAT_VAR(q) \\
  (GET_MODE_CLASS (qty_mode[q]) == MODE_FLOAT \\
   && REG_USERVAR_P (regno_reg_rtx[qty_first_reg[q]]) != 0)

static int
qty_compare (q1, q2)
     int q1, q2;
{
  /* RAC2: -frac2-la-float-vars-last: floating-point user variables last.  */
  if (flag_rac2_la_float_vars_last
      && RAC2_QTY_FLOAT_VAR (q1) != RAC2_QTY_FLOAT_VAR (q2))
    return RAC2_QTY_FLOAT_VAR (q1) - RAC2_QTY_FLOAT_VAR (q2);

  return QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);
}"""

TIE_OLD = """  register int tem = QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);

  if (tem != 0)
    return tem;
"""
TIE_NEW = """  register int tem = QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);

  /* RAC2: -frac2-la-float-vars-last: floating-point user variables last.  */
  if (flag_rac2_la_float_vars_last
      && RAC2_QTY_FLOAT_VAR (q1) != RAC2_QTY_FLOAT_VAR (q2))
    return RAC2_QTY_FLOAT_VAR (q1) - RAC2_QTY_FLOAT_VAR (q2);

  if (tem != 0)
    return tem;
"""

DEFINITION_OLD = "int flag_rac2_sched_call_addr_float = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_call_addr_float = 0;\n\n"
                  "/* RAC2: opt-in, local-alloc serves floating-point user variables last.  */\n"
                  "int flag_rac2_la_float_vars_last = 0;\n")
OPTION_OLD = '  {"rac2-sched-call-addr-float", &flag_rac2_sched_call_addr_float, 1,\n'
OPTION_NEW = ('  {"rac2-la-float-vars-last", &flag_rac2_la_float_vars_last, 1,\n'
              '   "Allocate local registers to floating-point user variables last"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_sched_call_addr_float;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: local-alloc serves floating-point user variables last.  */\n"
                   "extern int flag_rac2_la_float_vars_last;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    local, top, flags = gcc / "local-alloc.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (local, top, flags)}
    if any("flag_rac2_la_float_vars_last" in text for text in sources.values()):
        raise ValueError("la-float-vars-last option already present")
    src = replace_once(sources[local], HELPER_OLD, HELPER_NEW, "local-alloc qty_compare")
    src = replace_once(src, TIE_OLD, TIE_NEW, "local-alloc qty_compare_1")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((local, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
