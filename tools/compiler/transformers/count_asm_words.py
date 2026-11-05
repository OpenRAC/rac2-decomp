"""Count asm statements, grouped copies and inserted padding by their words.

The retail assembler lengthens a short loop by counting machine words. The
post-delay-slot padding pass counts insns, so a two-instruction `qcopy` asm
or the grouped `rac2_qcopy` pattern (lq/sq) was counted as one word and its
loop received one NOP too many. Both report their word count through the
length attribute (asm_insn_count for an asm; "length" 2 for rac2_qcopy).
Padding inserted before an already-visited branch must also advance the
counter, so another back edge to the same label sees those real words.
"""
from pathlib import Path
import sys

old = "\t  n += pat == TRAP_IF ? get_attr_length (insn) : 1;"
new = ("\t  /* An asm statement and the grouped qcopy occupy their word count,\n"
       "\t     which is what the assembler counts. */\n"
       "\t  n += (pat == TRAP_IF || pat == ASM_INPUT\n"
       "\t\t|| asm_noperands (PATTERN (insn)) >= 0\n"
       "\t\t|| recog_memoized (insn) == CODE_FOR_rac2_qcopy)\n"
       "\t       ? get_attr_length (insn) : 1;")
# After count_block_move_length.py the counter is already a multi-line condition.
old_bm = "\t  n += (pat == TRAP_IF\n"
new_bm = ("\t  n += (pat == TRAP_IF || pat == ASM_INPUT\n"
          "\t\t|| asm_noperands (PATTERN (insn)) >= 0\n"
          "\t\t|| recog_memoized (insn) == CODE_FOR_rac2_qcopy\n")
padding_old = ("\t\t  for (; loop < 7; loop++)\n"
               "\t\t    emit_insn_before (gen_nop (), insn);")
padding_new = ("\t\t  for (; loop < 7; loop++)\n"
               "\t\t    {\n"
               "\t\t      emit_insn_before (gen_nop (), insn);\n"
               "\t\t      /* Inserted before INSN: the walk will not visit it. */\n"
               "\t\t      n++;\n"
               "\t\t    }")


def patch(source: str) -> str:
    start = source.index("void\nmips_r5900_pad_loops (first)")
    end = source.index("/* ASTRA P25:", start)
    fragment = source[start:end]
    # Filled and unfilled delay slots have distinct emission paths.
    assert fragment.count(padding_old) == 2, "Unexpected or already patched padding insertion"
    if fragment.count(old) == 1:
        fragment = fragment.replace(old, new)
    else:
        assert fragment.count(old_bm) == 1, "Unexpected or already patched loop counter"
        fragment = fragment.replace(old_bm, new_bm)
    fragment = fragment.replace(padding_old, padding_new)
    return source[:start] + fragment + source[end:]


if __name__ == "__main__":
    path = Path(sys.argv[1])
    path.write_text(patch(path.read_text(encoding="utf-8")), encoding="utf-8", newline="")
    print("Asm, qcopy and inserted NOPs use their word count in post-DBR padding")
