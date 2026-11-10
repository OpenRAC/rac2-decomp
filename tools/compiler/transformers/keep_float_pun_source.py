#!/usr/bin/env python3
"""Add the opt-in -frac2-keep-float-pun-source: an int stored into a float keeps its GPR.

`f32 f; *(s32 *)&f = K;` reaches cse2 as (set (reg:SI g) K) and, from purge_addressof and
store_bit_field, (set (subreg:SI (reg:SF f) 0) (reg:SI g)). This tree then loses g whatever the
source says: cse2 writes K into the SUBREG store, and if g survives that, combine's
combinable_i3pat moves the SUBREG to the source (expand_field_assignment) and folds K through
gen_lowpart_common into a CONST_DOUBLE. An f read more than once then gets one of two codes,
neither of them retail's: `(set f const_double)`, a `li.s` through $at at the block start; or
sched1 splits `(set (subreg:SI f) K)` into hi/ior, which makes f a GR_REGS pseudo in a saved
register with an mtc1 per read, or, if the reads win FP_REGS, drops the ior's output reload:
wrong code (`lui; mtc1`, no `ori`; tests/test_keep_float_pun_source.py,
test_default_loses_the_low_half). The EE 2.9 base and the SDK compiler do the same.

Retail has neither at the six such sites of func_0034B2C8 and func_00349D58: g stays a GPR pseudo
that crosses no call (so sched1 leaves its set after the previous call), f is a saved FPR, and
`mtc1 $v0,$f20` is a real move (`mov.s $f13,$f20` waits out its latency). The same bit patterns
read once are `li.s`: combine still folds those. So with this option:

- cse_insn leaves (set (subreg:SI (reg:SF f) 0) (reg:SI g)) alone: neither a constant nor an
  older register holding the same value replaces g;
- combinable_i3pat refuses that insn as I3, unless f has a single use (find_single_use), which
  is the case combine folds into the use.

No GCC release does this. gen_lowpart_common's SFmode case, fold_rtx's SUBREG case, combine's
SUBREG simplification and expand_field_assignment are the same in GCC 2.95, 2.95.1, 2.95.2,
2.95.3 and this tree, and no ChangeLog entry concerns it (nor, for the lost output reload, up
to 3.4.6). The rule is inferred from retail alone and was designed to give retail's form; where
that form comes from is unverified (docs/build/compiler-notes.md). It also prevents the wrong code above. It keys on the insn's shape, never on a function, is off by default,
is enabled per unit in config/cflags.txt, and -fno-rac2-keep-float-pun-source disables it again.

Usage: keep_float_pun_source.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

# cse.c, cse_insn: canonicalising the source would replace g by the oldest register in its class.
CANON_OLD = ("      rtx new = canon_reg (src, insn);\n"
             "      int insn_code;\n")
CANON_NEW = ("      /* RAC2: -frac2-keep-float-pun-source keeps this source register.  */\n"
             "      rtx new = RAC2_FLOAT_PUN_SET_P (sets[i].rtl) ? src : canon_reg (src, insn);\n"
             "      int insn_code;\n")
# cse.c, cse_insn: the loop that tries cheaper equivalents, constants among them.
TRIAL_OLD = ("          rtx trial, old_src;\n"
             "\n"
             "          /* Skip invalid entries.  */\n")
TRIAL_NEW = ("          rtx trial, old_src;\n"
             "\n"
             "\t  /* RAC2: -frac2-keep-float-pun-source: no replacement either.  */\n"
             "\t  if (RAC2_FLOAT_PUN_SET_P (sets[i].rtl))\n"
             "\t    break;\n"
             "\n"
             "          /* Skip invalid entries.  */\n")
# combine.c, combinable_i3pat: this is where (set (subreg f) g) would become (set f (subreg g)).
I3_OLD = ("  if (GET_CODE (x) == SET)\n"
          "    {\n"
          "      rtx set = expand_field_assignment (x);\n"
          "      rtx dest = SET_DEST (set);\n")
I3_NEW = ("  /* RAC2: -frac2-keep-float-pun-source: g stays unless f has one use,\n"
          "     which takes the folded value; find_single_use finds that insn even\n"
          "     where its result is 0, a bare (set y f).  */\n"
          "  if (GET_CODE (x) == SET && RAC2_FLOAT_PUN_SET_P (x))\n"
          "    {\n"
          "      rtx user = 0;\n"
          "\n"
          "      find_single_use (SUBREG_REG (SET_DEST (x)), i3, &user);\n"
          "      if (user == 0)\n"
          "\treturn 0;\n"
          "    }\n"
          "\n" + I3_OLD)
DEFINITION_OLD = "int flag_rac2_no_static_chain_base = 0;\n"
DEFINITION_NEW = ("int flag_rac2_no_static_chain_base = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, an int stored into a float keeps its register.  */\n"
                  "int flag_rac2_keep_float_pun_source = 0;\n")
OPTION_OLD = '   "Give the static chain and struct-value registers no alias base"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-keep-float-pun-source", &flag_rac2_keep_float_pun_source, 1,\n'
              '   "Keep the register an int stored into a float comes from"},\n')
DECLARATION_OLD = "extern int flag_rac2_no_static_chain_base;\n"
DECLARATION_NEW = ("extern int flag_rac2_no_static_chain_base;\n"
                   "\n"
                   "/* RAC2: cse and combine keep the source register of\n"
                   "   (set (subreg:SI (reg:SF f) 0) (reg:SI g)).  */\n"
                   "extern int flag_rac2_keep_float_pun_source;\n"
                   "#define RAC2_FLOAT_PUN_SET_P(SET)\t\t\t\t\t\\\n"
                   "  (flag_rac2_keep_float_pun_source\t\t\t\t\t\\\n"
                   "   && GET_CODE (SET_DEST (SET)) == SUBREG\t\t\t\t\\\n"
                   "   && GET_MODE (SET_DEST (SET)) == SImode\t\t\t\t\\\n"
                   "   && GET_CODE (SUBREG_REG (SET_DEST (SET))) == REG\t\t\t\\\n"
                   "   && REGNO (SUBREG_REG (SET_DEST (SET))) >= FIRST_PSEUDO_REGISTER\t\\\n"
                   "   && GET_MODE (SUBREG_REG (SET_DEST (SET))) == SFmode\t\t\t\\\n"
                   "   && GET_CODE (SET_SRC (SET)) == REG)\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    cse, combine, top, flags = (root / name for name in ("cse.c", "combine.c", "toplev.c", "flags.h"))
    sources = {path: path.read_text(encoding="latin-1") for path in (cse, combine, top, flags)}
    if any("flag_rac2_keep_float_pun_source" in text or "RAC2_FLOAT_PUN_SET_P" in text
           for text in sources.values()):
        raise ValueError("keep-float-pun-source option already present")
    cse_new = replace_once(sources[cse], CANON_OLD, CANON_NEW, "cse_insn canon_reg")
    cse_new = replace_once(cse_new, TRIAL_OLD, TRIAL_NEW, "cse_insn trial loop")
    combine_new = replace_once(sources[combine], I3_OLD, I3_NEW, "combinable_i3pat")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((cse, cse_new), (combine, combine_new), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
