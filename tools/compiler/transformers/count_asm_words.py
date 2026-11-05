"""Count asm statements, grouped copies and inserted padding by their words.

The retail assembler lengthens a short loop by counting machine words. The
post-delay-slot padding pass counts insns, so a two-instruction `qcopy` asm
or the grouped `rac2_qcopy` pattern (lq/sq) was counted as one word and its
loop received one NOP too many. Both report their word count through the
length attribute (asm_insn_count for an asm; "length" 2 for rac2_qcopy).
Padding inserted before an already-visited branch must also advance the
counter, so another back edge to the same label sees those real words.
An unannounced external SI load/address expands to two words in reorder
mode. Count that bounded case here, without changing scheduler lengths.
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

declaration_old = ("  if (TARGET_GP_OPT)\n"
                   "    {\n"
                   "      tree name_tree = get_identifier (name);\n"
                   "      TREE_ASM_WRITTEN (name_tree) = 1;\n"
                   "    }")
declaration_new = ("  /* Track definitions at -G0 too; this does not emit metadata. */\n"
                   "  {\n"
                   "    tree name_tree = get_identifier (name);\n"
                   "    TREE_ASM_WRITTEN (name_tree) = 1;\n"
                   "  }")

symbolic_helper = r'''
/* Ordinary external SI macros whose metadata is not yet in the assembly
   expand to lui plus the access/address operation. The scheduler's length
   can still be one because SYMBOL_REF_FLAG describes small-data eligibility,
   not whether its declaration was emitted. Keep that scheduler model intact. */
static int
mips_rac2_unannounced_symbolic_move_p (insn)
     rtx insn;
{
  rtx pat, value;
  const char *raw, *printed;
  char *alternate;
  size_t length;

  if (! TARGET_MIPS5900 || ! TARGET_GAS || Pmode != SImode
      || TARGET_MIPS16 || flag_pic || TARGET_ABICALLS
      || TARGET_EMBEDDED_PIC || HALF_PIC_P ()
      || TARGET_R5900_GAS_EXTERN_BUFFER)
    return 0;
  pat = PATTERN (insn);
  if (GET_CODE (pat) != SET || GET_CODE (SET_DEST (pat)) != REG
      || GET_MODE (SET_DEST (pat)) != SImode)
    return 0;
  value = SET_SRC (pat);
  if (GET_CODE (value) == MEM)
    {
      if (GET_MODE (value) != SImode)
        return 0;
      value = XEXP (value, 0);
    }
  if (GET_CODE (value) == CONST)
    value = XEXP (value, 0);
  if (GET_CODE (value) == PLUS
      && GET_CODE (XEXP (value, 1)) == CONST_INT)
    value = XEXP (value, 0);
  if (GET_CODE (value) != SYMBOL_REF || ! SYMBOL_REF_USED (value))
    return 0;

  raw = XSTR (value, 0);
  if (TREE_ASM_WRITTEN (get_identifier (raw)))
    return 0;
  printed = raw[0] == '*' ? raw + 1 : raw;
  length = strlen (printed);
  /* SDATA aliases receive their metadata in the existing pre-assembly pass,
     including incomplete C arrays which emit no .extern of their own. */
  if (length >= 4 && strcmp (printed + length - 4, "__gp") == 0)
    return 0;
  if (raw[0] == '*')
    {
      if (TREE_ASM_WRITTEN (get_identifier (printed)))
        return 0;
    }
  else
    {
      alternate = (char *) alloca (length + 2);
      alternate[0] = '*';
      strcpy (alternate + 1, printed);
      if (TREE_ASM_WRITTEN (get_identifier (alternate)))
        return 0;
    }
  return 1;
}

'''


def patch(source: str) -> str:
    assert "mips_rac2_unannounced_symbolic_move_p" not in source, "Already patched symbolic counter"
    object_start = source.index("mips_declare_object (stream, name, init_string, final_string, size)\n")
    object_end = source.index("\n}\n", object_start) + 3
    object_body = source[object_start:object_end]
    assert object_body.count(declaration_old) == 1, "Unexpected object-definition marker"
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
    counter = "? get_attr_length (insn) : 1;"
    assert fragment.count(counter) == 1, "Unexpected ordinary instruction counter"
    fragment = fragment.replace(counter, "? get_attr_length (insn)\n"
                               "\t       : (mips_rac2_unannounced_symbolic_move_p (insn) ? 2 : 1);")
    source = source[:start] + symbolic_helper + fragment + source[end:]
    return source.replace(object_body, object_body.replace(declaration_old, declaration_new), 1)


if __name__ == "__main__":
    path = Path(sys.argv[1])
    path.write_text(patch(path.read_text(encoding="utf-8")), encoding="utf-8", newline="")
    print("Asm, qcopy and inserted NOPs use their word count in post-DBR padding")
