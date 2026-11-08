"""Restrict the existing transfer-delay exemption to measured operand roles."""
from pathlib import Path
import sys

path = Path(sys.argv[1])
source = path.read_text(encoding="utf-8")
declaration = "static int rac2_mtc1_nop_ok PARAMS ((void));"
assert source.count(declaration) == 1, "Expected the earlier no-argument helper"
assert source.count("rac2_mtc1_nop_ok ())") == 2, "Expected both transfer-hazard sites"
# gas empties both history slots in two ways. mips_no_prev_insn (md_begin, a section change,
# .align, data) forgets the history: it also clears prev_insn_valid. append_insn empties both
# slots after every unconditional branch (b, j, jal, jr) but then sets prev_insn_valid. The
# exemption applies only to a forgotten history (prev_insn_valid clear): a section start, and
# so, with -ffunction-sections (every game unit), in practice a function start. A function
# start inside a section, after `j $31`, keeps the nop. Known limits, which cc1 never emits:
# `b; .align 3; L: mtc1` and `b; .set noreorder; .set reorder; L: mtc1` forget the history and
# stay exempt (tests/fixtures/mtc1_exemption.s).
assert source.count("prev_insn_valid =") == 2, "Expected prev_insn_valid set in two places"
for anchor in ("static int prev_insn_valid;\n",
               "\t  if (pinfo & INSN_UNCOND_BRANCH_DELAY)\n\t    {\n"
               "\t      prev_prev_insn.insn_mo = &dummy_opcode;\n"
               "\t      prev_insn.insn_mo = &dummy_opcode;\n\t    }\n",
               "      prev_insn_valid = 1;\n    }\n  else if (place == NULL)\n",
               "  prev_insn_valid = 0;\n  prev_insn_is_delay_slot = 0;\n"):
    assert source.count(anchor) == 1, ("Expected one history anchor", anchor[:40])
source = source.replace(declaration, "static int rac2_mtc1_nop_ok PARAMS ((struct mips_cl_insn *ip));\n"
                        "/* RAC2: the history had been forgotten when prev_insn was appended. */\n"
                        "static int rac2_prev_after_clear;")
# Record, as each instruction enters the history, whether the history had been forgotten
# before it: both slots empty and prev_insn_valid clear, not merely both slots emptied by a
# branch delay slot or an unconditional branch.
CLEAR = ("! prev_insn_valid\n"
         "\t\t\t\t   && (prev_insn.insn_mo == 0 || prev_insn.insn_mo == &dummy_opcode)\n"
         "\t\t\t\t   && (prev_prev_insn.insn_mo == 0\n"
         "\t\t\t\t       || prev_prev_insn.insn_mo == &dummy_opcode);\n")
for old, indent in (("\t  /* Update the previous insn information.  */\n"
                     "\t  if (nops > 0)\n\t    prev_prev_insn.insn_mo = &dummy_opcode;\n", "\t  "),
                    ("      prev_prev_insn = prev_insn;\n      prev_insn = *ip;\n"
                     "      prev_insn_reloc_type = reloc_type;\n", "      ")):
    assert source.count(old) == 1, ("Expected one history update", old[:40])
    source = source.replace(old, indent + "rac2_prev_after_clear = " + CLEAR + old)
source = source.replace("rac2_mtc1_nop_ok ())", "rac2_mtc1_nop_ok (ip))")
start = source.index("\nstatic int\nrac2_mtc1_nop_ok ()")
comment = source.rfind("\n/*", 0, start)
assert comment >= 0 and source[comment:start].count("*/") == 1
end = source.index("\n}\n", start) + 3
replacement = '''
/* Private compatibility restricted to measured producer/consumer roles, and
   to an mtc1 appended to a forgotten history (prev_insn_valid clear).
   History cleared by a branch delay slot or emptied after an unconditional
   branch keeps the nop. No game policy. */
static int
rac2_mtc1_nop_ok (ip)
     struct mips_cl_insn *ip;
{
  unsigned int gpr, fpr;
  if (prev_insn.insn_mo == 0 || strcmp (prev_insn.insn_mo->name, "mtc1") != 0)
    return 1;
  if (! rac2_prev_after_clear)
    return 1;
  gpr = (prev_insn.insn_opcode >> OP_SH_RT) & OP_MASK_RT;
  fpr = (prev_insn.insn_opcode >> OP_SH_FS) & OP_MASK_FS;
  if (fpr != 0 || ip->insn_mo == 0)
    return 1;
  if (gpr == 4 && strcmp (ip->insn_mo->name, "cvt.s.w") == 0
      && ((ip->insn_opcode >> OP_SH_FS) & OP_MASK_FS) == 0
      && ((ip->insn_opcode >> OP_SH_FD) & OP_MASK_FD) == 0)
    return 0;
  if (gpr == 0 && strcmp (ip->insn_mo->name, "c.lt.s") == 0
      && ((ip->insn_opcode >> OP_SH_FS) & OP_MASK_FS) == 12
      && ((ip->insn_opcode >> OP_SH_FT) & OP_MASK_FT) == 0)
    return 0;
  return 1;
}
'''
path.write_text(source[:comment] + replacement + source[end:], encoding="utf-8", newline="")
print("Transfer-delay exemption restricted to the qualified operand patterns")
