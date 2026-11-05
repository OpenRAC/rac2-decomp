"""Reproduce a measured SDK 3.01 division-padding subset in GNU `as`.

The SN ProDG 3.01 EE assembler (`Ps2EeAs`) warns about a
single-precision COP1 division opcode too near a possible branch destination.
Its own message is "DIV related opcode too near possible branch destination",
and for a division inside a delay slot it says "DIV related opcode used in
branch delay slot -- Automatic padding cannot take place".

Measured rule. The oracle is the authentic SDK 3.01 assembler, driven by a private
diagnostic harness that is deliberately kept outside this repository; the
harness reconstructs a witness around each sampled retail division site and
asks the SDK 3.01 assembler to regenerate the run length. The witnesses live with
that private harness, not here, and no binary, object or image from it is
published.

  (A) Padding.  When a division opcode is emitted fewer than two instructions
      after the most recent code label, even one never branched to,
      the assembler emits `2 - n` nops before it, where `n` counts the
      emitted four-byte slots since that label. The division therefore lands
      exactly two slots after the label.  `n` counts every instruction,
      including generated nops and same-fragment `.word` slots. No code label exists
      in the file => no padding (the division may be the first instruction).

  (B) The floor is a maximum, not a sum.  A coprocessor hazard that already
      asks for a nop before the division (a `mtc1` immediately before a
      division that reads the written FPR, or `sync.p` immediately before it)
      satisfies one of the two slots; it is not added.  Measured: a label one
      instruction back together with an adjacent `mtc1` yields one nop, and
      `sync.p` followed by `mtc1` followed by the division yields one nop,
      not two.

  (C) `sync.p` immediately before such a division also asks for one nop on
      its own.  It is the exact `sync.p` opcode, not the `INSN_SYNC` class:
      `sync` and `sync.l` share that flag and do not trigger.  The trigger
      pairs with the same division family and not with the integer opcodes.

The opcode family is measured, not assumed.  `div.s` (funct 0x03), `sqrt.s`
(0x04) and `rsqrt.s` (0x16) carry the padding.  `add.s`, `sub.s`, `mul.s`,
`neg.s`, `mov.s`, `madd.s`, `msub.s`, `adda.s`, `cvt.w.s` do not; the integer
HI/LO `div`/`divu` do not; and this SDK assembler does not accept the D forms
at all.  This is narrower than the family names sometimes quoted for the wall,
and it is what the oracle answers.

  (D)  A label that directly follows a noreorder group still counts.  GCC emits
      each call with its delay slot inside `.set noreorder`; a -g line label
      after it and a division at that label get the two nops in retail
      (jal, delay, nop, nop, div.s in func_L00_0040A4A8 and 23 other level-00
      sites).  gas's own reset for an unreordered previous instruction would
      cancel them, so the label floor is tested after that reset.

The delay-slot half is NOT fixed here. Retained compiler attempts place a
`div.s` in a following `jal` delay slot and remain mismatches. A division emitted
inside a noreorder region gets no new floor; SDK 3.01 pads ordinary noreorder
cases too, so that behavior remains unsupported. A division scheduled in a delay
slot still loses the padding. Cross-fragment alignment/relaxation and speculative
nop removal are not generally reproduced. This is a bounded improvement, not
whole-assembler equivalence. See docs/COMPILER-NOTES.md.

Usage: pad_div_erratum_nops.py <gas source directory or tc-mips.c>
"""
from pathlib import Path
import sys

STATE_ANCHOR = "static int insn_uses_fpr_exact PARAMS ((struct mips_cl_insn *ip,"
HELPER_ANCHOR = "\nstatic void\nmacro_build (char *place,"

HELPER = '''
/* RAC2: count emitted slots since the latest code label. A separate
   flag tracks whether a label has been seen.
    */
static int rac2_div_insns_since_label;
static int rac2_div_label_defined;
static symbolS *rac2_div_last_code_label;
static segT rac2_div_code_label_segment;

/* RAC2: the measured SDK 3.01 padding family contains only COP1 single-
   precision div.s (0x03), sqrt.s (0x04) and rsqrt.s (0x16). Other
   single-precision operations and integer HI/LO div/divu do not trigger
   this floor; the oracle rejects double-precision forms.
    */
static int
rac2_div_erratum_p (ip)
     struct mips_cl_insn *ip;
{
  if (ip == 0 || ip->insn_mo == 0)
    return 0;
  if ((ip->insn_opcode >> 26) != 0x11)              /* COP1 */
    return 0;
  if (((ip->insn_opcode >> 21) & 0x1F) != 0x10)     /* single precision */
    return 0;
  switch (ip->insn_opcode & 0x3F)
    {
    case 0x03:                                      /* div.s */
    case 0x04:                                      /* sqrt.s */
    case 0x16:                                      /* rsqrt.s */
      return 1;
    default:
      return 0;
    }
}
/* Count emitted bytes, not the unselected instructions stored in a relaxation
   fragment. Only cross fixed fragments and non-PIC alternatives whose symbol
   already has a size or section; forward symbols and alignment retain the
   existing conservative fallback. */
static int
rac2_div_code_distance ()
{
  if (rac2_div_last_code_label != 0
      && rac2_div_code_label_segment == now_seg)
    {
      fragS *frag = rac2_div_last_code_label->sy_frag;
      valueT start = S_GET_VALUE (rac2_div_last_code_label);
      valueT bytes = 0;
      for (; frag != 0; frag = frag->fr_next)
        {
          valueT size = frag == frag_now ? (valueT) frag_now_fix ()
                                        : (valueT) frag->fr_fix;
          if (size < start)
            break;
          bytes += size - start;
          start = 0;
          if (frag == frag_now)
            {
              if ((bytes & 3) == 0)
                return bytes >= 8 ? 2 : (int) (bytes / 4);
              break;
            }
          if (frag->fr_type == rs_machine_dependent
              && mips_pic == NO_PIC
              && ! RELAX_MIPS16_P (frag->fr_subtype))
            {
              symbolS *sym = frag->fr_symbol;
              if (sym == 0
                  || ((! S_IS_DEFINED (sym) || S_IS_COMMON (sym))
                      && S_GET_VALUE (sym) == 0
#ifndef NO_ECOFF_DEBUGGING
                      && sym->ecoff_extern_size == 0
#endif
                      ))
                break;
              if (nopic_need_relax (sym, 0))
                bytes += RELAX_NEW (frag->fr_subtype)
                         - RELAX_OLD (frag->fr_subtype);
            }
          else if (frag->fr_type != rs_fill || frag->fr_offset != 0)
            break;
          if (bytes >= 8)
            return 2;
        }
    }
  return rac2_div_insns_since_label;
}

'''

PAD_ANCHOR = """      /* If the previous instruction was in a noreorder section, then
         we don't want to insert the nop after all.  */
      /* Itbl support may require additional care here. */
      if (prev_insn_unreordered)
	nops = 0;
"""

PAD = """      /* RAC2: an immediately preceding sync.p also requires one nop before
   this COP1 family. Match the exact mnemonic: sync and sync.l share
   INSN_SYNC but do not trigger the measured rule. This is another
   minimum, not an addition.

    */
      if (! mips_opts.mips16
	  && rac2_div_erratum_p (ip)
	  && prev_insn.insn_mo != 0
	  && prev_insn.insn_mo != &dummy_opcode
	  && strcmp (prev_insn.insn_mo->name, "sync.p") == 0
	  && nops < 1)
	nops = 1;

"""

LABEL_PAD = """      /* RAC2: require two emitted slots between a code label and a division-
   family operation. This is a minimum, not an addition: an existing
   coprocessor hazard nop contributes to the floor. No observed code
   label means no label-driven padding. The test runs after the noreorder
   reset: a label that follows a compiler .set noreorder group (a call and
   its delay slot) still gets the floor, as retail shows (jal, delay, nop,
   nop, div.s after a -g line label in func_L00_0040A4A8 and 23 other
   level-00 sites). See docs/COMPILER-NOTES.md.
    */
      if (rac2_div_label_defined
	  && ! mips_opts.mips16
	  && rac2_div_erratum_p (ip)
	  && rac2_div_code_label_segment == now_seg
	  && rac2_div_code_distance () < 2)
	{
	  int rac2_need = 2 - rac2_div_code_distance ();
	  if (nops < rac2_need)
	    nops = rac2_need;

	  /* A division label denotes the inserted padding, as in the oracle. */
	  if (insn_labels != NULL && ! mips_opts.noreorder
	      && ! prev_insn_unreordered)
	    rac2_div_keep_labels = 1;
	}

"""

COUNT_ANCHOR = """  /* We just output an insn, so the next one doesn't have a label.  */
  mips_clear_insn_labels ();
"""

COUNT = """  /* RAC2: count this instruction; saturate at two slots. */
  if (rac2_div_insns_since_label < 2)
    ++rac2_div_insns_since_label;

  /* We just output an insn, so the next one doesn't have a label.  */
  mips_clear_insn_labels ();
"""

LABEL_ANCHOR = """  l->label = sym;
  l->next = insn_labels;
  insn_labels = l;
"""

LABEL = """  l->label = sym;
  l->next = insn_labels;
  insn_labels = l;

  /* RAC2: a code label starts a new padding distance, even when no branch
   targets it. */
  /* A data symbol is not a possible destination in this code stream. */
  if ((bfd_get_section_flags (stdoutput, now_seg) & SEC_CODE) != 0)
    {
      rac2_div_insns_since_label = 0;
      rac2_div_label_defined = 1;
      rac2_div_last_code_label = sym;
      rac2_div_code_label_segment = now_seg;
    }
"""


NOP_EMIT_ANCHOR = '#define emit_nop()\t\t\t\t\t\\\n  (mips_opts.mips16\t\t\t\t\t\\\n   ? md_number_to_chars (frag_more (2), 0x6500, 2)\t\\\n   : md_number_to_chars (frag_more (4), 0, 4))'
NOP_EMIT = '#define emit_nop()\t\t\t\t\t\\\n  (mips_opts.mips16\t\t\t\t\t\\\n   ? md_number_to_chars (frag_more (2), 0x6500, 2)\t\\\n   : md_number_to_chars (frag_more (4), 0, 4),\\\n   (rac2_div_insns_since_label < 2\\\n    ? ++rac2_div_insns_since_label : rac2_div_insns_since_label))'

def main() -> None:
    p = Path(sys.argv[1])
    if p.is_dir():
        p = p / "gas" / "config" / "tc-mips.c"
    source = p.read_text(encoding="utf-8")

    if "rac2_div_insns_since_label" in source:
        raise SystemExit(
            "already transformed: this transformer is not idempotent by design"
        )
    assert source.count(STATE_ANCHOR) == 1, "anchor: insn_uses_fpr_exact declaration"
    assert source.count(HELPER_ANCHOR) == 1, "anchor: macro_build definition"
    assert source.count(PAD_ANCHOR) == 1, "anchor: noreorder nop reset"
    assert source.count(COUNT_ANCHOR) == 1, "anchor: append_insn instruction tail"
    assert source.count(LABEL_ANCHOR) == 1, "anchor: mips_define_label body"

    end = source.index(";", source.index(STATE_ANCHOR)) + 1
    source = source[:end] + "\n" + HELPER + source[end:]
    source = source.replace(PAD_ANCHOR, PAD + PAD_ANCHOR + LABEL_PAD, 1)
    source = source.replace(COUNT_ANCHOR, COUNT, 1)
    source = source.replace(LABEL_ANCHOR, LABEL, 1)
    assert source.count(NOP_EMIT_ANCHOR) == 1, "anchor: emitted-nop macro"
    source = source.replace(NOP_EMIT_ANCHOR, NOP_EMIT, 1)
    assert source.count("  int nops = 0;\n") == 1, "anchor: append_insn local state"
    source = source.replace("  int nops = 0;\n", "  int nops = 0;\n  int rac2_div_keep_labels = 0;\n", 1)
    # Keep the existing label relocation policy for every non-erratum case.
    begin = source.index("append_insn (place, ip, address_expr, reloc_type, unmatched_hi)\n")
    end = source.index("static void\nmips_emit_delays", begin)
    part = source[begin:end]
    label_loop = "for (l = insn_labels; l != NULL; l = l->next)"
    assert part.count(label_loop) == 1, "anchor: append_insn label relocation"
    part = part.replace(label_loop, "for (l = rac2_div_keep_labels ? NULL : insn_labels; l != NULL; l = l->next)", 1)
    source = source[:begin] + part + source[end:]

    p.write_text(source, encoding="utf-8", newline="")
    print("Division-erratum padding installed in %s" % p)


if __name__ == "__main__":
    main()
