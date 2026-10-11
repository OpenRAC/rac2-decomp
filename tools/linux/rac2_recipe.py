#!/usr/bin/env python3
"""Apply the RAC2 source adjustments to a Lombyte-patched GNU EE 2.9-ee-991111b tree.

Usage: rac2_recipe.py <patched-tree> <scripts/compiler dir>

Runs only published transformers, in the order of docs/COMPILER-NOTES.md, plus the one earlier
`tc-mips.c` helper step. Success means the four source hashes in the notes' checkpoint table.
"""
from __future__ import annotations

import subprocess
import sys
from pathlib import Path

tree, published = Path(sys.argv[1]), Path(sys.argv[2])
mips_c, mips_h = tree / "gcc/config/mips/mips.c", tree / "gcc/config/mips/mips.h"
tc_mips = tree / "gas/config/tc-mips.c"


def run(script: str, target: Path) -> None:
    subprocess.run([sys.executable, str(published / script), str(target)], check=True)


def edit(path: Path, old: str, new: str) -> None:
    text = path.read_text(encoding="utf-8")
    assert text.count(old) == 1, (path.name, old[:50])
    path.write_text(text.replace(old, new), encoding="utf-8", newline="")


# The frame-order option exists but is not yet enabled; disable_frame_order_default.py later replaces this line.
edit(mips_c, "char *mips_astra_keep_frame_order;\n", 'char *mips_astra_keep_frame_order = "1";\n')

run("neutralise_timode_anchor.py", mips_c)
run("enable_loop_padding.py", mips_h)
run("count_trap_length.py", mips_c)
run("ascending_save_order.py", mips_c)
run("reorder_save_blocks.py", mips_c)

# Earlier transfer-hazard helper that restrict_mtc1_exemption.py refines.
edit(tc_mips, "static int insn_uses_fpr_exact PARAMS ((struct mips_cl_insn *ip,\n\t\t\t\t\t      unsigned int reg));\n",
     "static int insn_uses_fpr_exact PARAMS ((struct mips_cl_insn *ip,\n\t\t\t\t\t      unsigned int reg));\n"
     "static int rac2_mtc1_nop_ok PARAMS ((void));\n")
for field in ("FT", "FS"):
    old = ("\t      if (mips_optimize == 0\n\t\t  || insn_uses_fpr_exact (ip,\n"
           f"\t\t\t\t\t   ((prev_insn.insn_opcode >> OP_SH_{field})\n"
           f"\t\t\t\t\t    & OP_MASK_{field})))\n\t\t++nops;\n")
    new = ("\t      if ((mips_optimize == 0\n\t\t  || insn_uses_fpr_exact (ip,\n"
           f"\t\t\t\t\t   ((prev_insn.insn_opcode >> OP_SH_{field})\n"
           f"\t\t\t\t\t    & OP_MASK_{field})))\n\t\t\t\t\t   && rac2_mtc1_nop_ok ())\n\t\t++nops;\n")
    edit(tc_mips, old, new)
edit(tc_mips, "      return 1;\n  return 0;\n}\n\nstatic void\nmacro_build (char *place,\n",
     "      return 1;\n  return 0;\n}\n\n/* RAC2 : earlier transfer-delay rule. */\nstatic int\nrac2_mtc1_nop_ok ()\n{\n"
     "  if (prev_insn.insn_mo == 0 || strcmp (prev_insn.insn_mo->name, \"mtc1\") != 0)\n    return 1;\n"
     "  if (prev_prev_insn.insn_mo == 0 || prev_prev_insn.insn_mo == &dummy_opcode)\n    return 0;\n  return 1;\n}\n\n"
     "static void\nmacro_build (char *place,\n")
run("restrict_mtc1_exemption.py", tc_mips)
run("pad_div_erratum_nops.py", tc_mips)
run("pad_div_erratum_branch.py", tc_mips)  # must follow pad_div_erratum_nops.py

run("fold_zero_ti_store.py", tree / "gcc")
run("fold_zero_ti_return_value.py", tree / "gcc")  # rewrites the guard fold_zero_ti_store.py inserts
run("neutralise_div_dslot.py", tree / "gcc")
run("disable_frame_order_default.py", mips_c)
print("RAC2 recipe applied")
