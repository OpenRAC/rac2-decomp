#!/usr/bin/env python3
"""Add the opt-in -frac2-sched-call-addr-float: a call's address MEM does not depend on FP stores.

In Haifa's dependence analysis (sched_analyze_2), the MEM inside a CALL names the function
being called. With the switch, a pending floating-point store (a MODE_FLOAT memory write)
is not made a true dependence of that MEM, so the store is not ordered before the call by
it (other dependences, such as the call's clobber of memory, are unchanged).

In func_L11_004580E8 case 5, store 819 took priority 4 from a true link to call 844's
(mem:SI (symbol_ref)) and won the sched1 tie on weight; retail issues it after both `li`s.

Forced on for every USA v1.01 C unit it changes 136 functions: an opt-in per-unit model, landed
under the owner's standard of 12 November 2026. Default compilation is unchanged.

Usage: sched_call_addr_float.py <gcc directory>
"""
import sys
from pathlib import Path

CASE_OLD = "#endif\n\n    case REG:\n      {\n\trtx u;"
CASE_NEW = """#endif

    case CALL:
      /* RAC2: -frac2-sched-call-addr-float: the MEM of a CALL names the
	 function; remember it so a pending floating-point store is not
	 made a true dependence of it.  */
      if (flag_rac2_sched_call_addr_float && GET_CODE (XEXP (x, 0)) == MEM)
	rac2_call_mem = XEXP (x, 0);
      break;

    case REG:
      {
	rtx u;"""

PENDING_OLD = """	    if (!find_insn_list (XEXP (pending, 0), LOG_LINKS (insn)))
	      if (true_dependence (XEXP (pending_mem, 0), VOIDmode,
		  x, rtx_varies_p))
		add_dependence (insn, XEXP (pending, 0), 0);"""
PENDING_NEW = """	    if (!find_insn_list (XEXP (pending, 0), LOG_LINKS (insn)))
	      if (! (flag_rac2_sched_call_addr_float && x == rac2_call_mem
		     && GET_MODE_CLASS (GET_MODE (XEXP (pending_mem, 0)))
			== MODE_FLOAT)
		  && true_dependence (XEXP (pending_mem, 0), VOIDmode,
				      x, rtx_varies_p))
		add_dependence (insn, XEXP (pending, 0), 0);"""

DECL_OLD = "static void\nsched_analyze_2 (x, insn)"
DECL_NEW = "/* RAC2: the function MEM of the CALL being analyzed (-frac2-sched-call-addr-float).  */\nstatic rtx rac2_call_mem;\n\n" + DECL_OLD

DEFINITION_OLD = "int flag_rac2_sched_clear_holds_store = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_clear_holds_store = 0;\n\n"
                  "/* RAC2: opt-in, a call's address MEM ignores pending FP stores.  */\n"
                  "int flag_rac2_sched_call_addr_float = 0;\n")
OPTION_OLD = '  {"rac2-sched-clear-holds-store", &flag_rac2_sched_clear_holds_store, 1,\n'
OPTION_NEW = ('  {"rac2-sched-call-addr-float", &flag_rac2_sched_call_addr_float, 1,\n'
              '   "Do not make a call address depend on pending floating-point stores"},\n' + OPTION_OLD)
DECLARATION_OLD = "extern int flag_rac2_sched_clear_holds_store;\n"
DECLARATION_NEW = (DECLARATION_OLD + "/* RAC2: a call's address MEM ignores pending FP stores.  */\n"
                   "extern int flag_rac2_sched_call_addr_float;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    haifa, top, flags = gcc / "haifa-sched.c", gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (haifa, top, flags)}
    if any("flag_rac2_sched_call_addr_float" in text for text in sources.values()):
        raise ValueError("sched-call-addr-float option already present")
    src = replace_once(sources[haifa], DECL_OLD, DECL_NEW, "haifa declaration")
    src = replace_once(src, CASE_OLD, CASE_NEW, "haifa CALL case")
    src = replace_once(src, PENDING_OLD, PENDING_NEW, "haifa pending writes")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW, "option declaration")
    for path, contents in ((haifa, src), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
