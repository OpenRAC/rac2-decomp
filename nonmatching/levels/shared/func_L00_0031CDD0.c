/* 0 of 27 places match - last line: 00_aranos_tutorial: 176 bytes, expected 184
   The whole body is recovered and every other word is byte-identical, registers
   included. The 8 missing bytes are the two `nop` retail carries between the second
   call's delay slot and its division:
     retail  jal func_00282E20 ; daddu $a0,$sp,$zero ; nop ; nop ; div.s $f4,$f0,$f20
     ours    jal func_00282E20 ; daddu $a0,$sp,$zero ; div.s $f4,$f0,$f20
   cc1's .s emits no marker at all there (`div.s` directly after the delay slot), so this
   is the division-padding hole described in docs/build/compiler-notes.md item (4): the retail
   two-`nop` runs at a division site that the SDK 3.01 assembler does not produce from
   that sequence, i.e. compiler-emitted and not recovered by this lot.
   Meaning of the body (for a future pass): buf = a - b (0x00282CF0), t = |buf|
   (0x00282E20) / arg4, `out` receives t, and the result is
   -((a[2]-b[2]) + arg5 * (t*t) * 0.5f) / t for t != 0, 0.0f otherwise. Four spellings
   measured (grouped/ungrouped t*t, V4 struct buffer, `if (out)`): all 176.

   Wave 8 (agent w8-08) reached the same 176 bytes with the same body (the call is
   func_2EE138(out, vec, mat) into the stack buffer, func_2EE268 for its length) and
   measured WHY the two nops cannot appear here. The SDK 3.01 division padding
   (tools/compiler/transformers/pad_div_erratum_nops.py and ..._branch.py) only fires
   when a CODE LABEL sits within two slots of the division, and the rule is dropped again
   when the previous instruction was emitted in a `.set noreorder` region. Here the
   `div.s` follows the `jal`'s delay slot, which is exactly such a noreorder region, so
   the padding is cleared: a label on the `div.s` alone changes nothing (measured: 176
   bytes with the label added by hand to the .s). The branch floor of
   pad_div_erratum_branch.py does not apply either - a `jal` is a jump and starts no
   padding distance. A division right after a call therefore cannot carry retail's two
   nops in this assembler; only a reorder-region instruction before the division (and a
   label at its foot) would. */

typedef float f32;

extern void func_00282CF0(f32 *, const f32 *, const f32 *);
extern f32 func_00282E20(const f32 *);

f32 func_L00_0031CDD0(const f32 *a, const f32 *b, f32 *out, f32 d, f32 e) {
    f32 buf[4];
    f32 t;

    func_00282CF0(buf, b, a);
    t = func_00282E20(buf) / d;
    if (out != 0)
        *out = t;
    if (t == 0.0f)
        return 0.0f;
    return -((a[2] - b[2]) + e * (t * t) * 0.5f) / t;
}
