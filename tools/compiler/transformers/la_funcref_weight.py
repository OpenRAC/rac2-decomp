#!/usr/bin/env python3
"""Add the opt-in -frac2-la-funcref-weight: weight function-address quantities in local-alloc.

local-alloc's block_alloc orders a block's quantities by QTY_CMP_PRI,
floor_log2(refs) * refs * size / (death - birth). In func_002CA070's case 8 five
block-local values are stored into the pause and cinema state: the constant 0x18, the
page and callback-table addresses, and two function addresses (the update and init
callbacks, the second of which is then called through its register). Stock priorities
put 0x18 first (init 5 refs, upd 4); retail's registers follow init > 0x18 > upd >
page > c, the order given when a quantity whose value is loaded from a function's
SYMBOL_REF (directly or through a LO_SUM) counts one more reference.

With -frac2-la-funcref-weight, block_alloc adds one to qty_n_refs for each quantity set
in the block from a function symbol, before the quantities are sorted. A symbol is a
function when its global binding is a FUNCTION_DECL (rac2_symbol_is_function, in the C
front end). Data symbols, constants and hard registers are unchanged.

Not retail's global rule: forced on for every USA v1.01 C unit it changes 17 of 4058
units. It is an opt-in model for the units that set it (owner ruling, 12 November 2026),
like -frac2-sched-arg-copy. Default compilation is unchanged.

Usage: la_funcref_weight.py <gcc directory>
"""
import sys
from pathlib import Path

ORDER_OLD = """  qty_order = (int *) alloca (next_qty * sizeof (int));
  for (i = 0; i < next_qty; i++)
    qty_order[i] = i;

#define EXCHANGE(I1, I2)  \\
"""

ORDER_NEW = """  /* RAC2: -frac2-la-funcref-weight: a quantity set in this block from a
     function's address counts one more reference.  */
  if (flag_rac2_la_funcref_weight)
    {
      rtx fi;
      for (fi = BLOCK_HEAD (b); ; fi = NEXT_INSN (fi))
	{
	  rtx fs;
	  if (GET_CODE (fi) == INSN && (fs = single_set (fi)) != 0
	      && GET_CODE (SET_DEST (fs)) == REG
	      && REGNO (SET_DEST (fs)) >= FIRST_PSEUDO_REGISTER
	      && reg_qty[REGNO (SET_DEST (fs))] >= 0)
	    {
	      rtx src = SET_SRC (fs);
	      if (GET_CODE (src) == LO_SUM)
		src = XEXP (src, 1);
	      if (GET_CODE (src) == SYMBOL_REF
		  && rac2_symbol_is_function (XSTR (src, 0)))
		qty_n_refs[reg_qty[REGNO (SET_DEST (fs))]]++;
	    }
	  if (fi == BLOCK_END (b))
	    break;
	}
    }

""" + ORDER_OLD

PROTO_OLD = '#include "recog.h"\n'
PROTO_NEW = ('#include "recog.h"\n'
             '\n'
             '/* RAC2: in the C front end (c-decl.c).  */\n'
             'extern int rac2_symbol_is_function PROTO((char *));\n')

HELPER = """
/* RAC2: nonzero if NAME is bound to a function declaration at file scope
   (-frac2-la-funcref-weight, local-alloc.c).  */

int
rac2_symbol_is_function (name)
     char *name;
{
  tree id = maybe_get_identifier (name);
  tree d;
  if (id == 0)
    return 0;
  d = IDENTIFIER_GLOBAL_VALUE (id);
  return d != 0 && TREE_CODE (d) == FUNCTION_DECL;
}
"""

DEFINITION_OLD = "int flag_rac2_sched_arg_copy = 0;\n"
DEFINITION_NEW = ("int flag_rac2_sched_arg_copy = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, function-address quantities weigh one more reference.  */\n"
                  "int flag_rac2_la_funcref_weight = 0;\n")

OPTION_OLD = '  {"rac2-sched-arg-copy", &flag_rac2_sched_arg_copy, 1,\n'
OPTION_NEW = ('  {"rac2-la-funcref-weight", &flag_rac2_la_funcref_weight, 1,\n'
              '   "Count one more reference for local quantities set from a function address"},\n'
              + OPTION_OLD)

DECLARATION_OLD = "extern int flag_rac2_sched_arg_copy;\n"
DECLARATION_NEW = (DECLARATION_OLD
                   + "/* RAC2: function-address quantities weigh one more reference.  */\n"
                     "extern int flag_rac2_la_funcref_weight;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    local, decl = gcc / "local-alloc.c", gcc / "c-decl.c"
    top, flags = gcc / "toplev.c", gcc / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (local, decl, top, flags)}
    if any("flag_rac2_la_funcref_weight" in text for text in sources.values()):
        raise ValueError("la-funcref-weight option already present")
    local_src = replace_once(sources[local], PROTO_OLD, PROTO_NEW, "local-alloc prototype")
    local_src = replace_once(local_src, ORDER_OLD, ORDER_NEW, "local-alloc qty weight")
    decl_src = sources[decl].rstrip("\n") + "\n" + HELPER
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    for path, contents in ((local, local_src), (decl, decl_src), (top, driver),
                           (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
