/* 0 of 27 places match - last line: 00_aranos_tutorial: 100 bytes, expected 108
   The body is recovered and every instruction is retail's; the eight missing
   bytes are the two NOPs the patched assembler puts in front of a `div.s`
   (see docs/build/compiler-notes.md, the division-erratum section):

     retail  jal func_00283CE0 ; nop ; mtc1 $s0,$f12 ; nop ;
             cvt.s.w $f12,$f12 ; nop ; nop ; div.s $f12,$f0,$f12
     this    jal func_00283CE0 ; nop ; mtc1 $s0,$f12 ; nop ;
             cvt.s.w $f12,$f12 ; div.s $f12,$f0,$f12

   The assembler only pads a division that is fewer than two slots after the
   most recent code label, so the source has to make the `div.s` the first
   instruction of a basic block. Nothing measured so far does that: the
   division sits in the middle of the block that follows the `beql` in every
   spelling tried (~30: the quotient in a local or not, the divisor in a local
   or not, the call in a local or not, an if/else, a goto, a label block, the
   float quotient as `float` or `f32`).

   What else the source has to be, all of it measured here:

     - the third argument is `s32` (the `sb` of the low byte at +5 would
       otherwise gain an `andi`);
     - the "value" path assigns to the argument and returns it
       (`value = (...); return value;`), so that both paths end in the same
       `daddu $v0,$a0,$zero` and the two tails merge: the candidate gives
       `sll $a0,$v0,4` + `daddu $v0,$a0,$zero` and the `beql`'s delay slot
       holds the `ld $s0,0($sp)`, exactly as retail does;
     - the return type is 32 bits (a 64-bit one makes the compiler strength
       reduce `(x + 1) << 4` into `x << 4 + 16` and lose the `addiu`).

   The candidate below is the closest one measured: 100 of the retail's 108
   bytes, every instruction identical apart from the two missing NOPs.  The
   spelling `if (value % divisor)` (no comparison) gives 112 bytes instead:
   the branch polarity changes the whole tail. */

typedef int s32;
typedef float f32;

extern f32 func_00283CE0(void);
extern int func_00283CF0(f32);

s32 func_L00_00329FF0(s32 value) {
    s32 divisor = 16;

    if (value % divisor != 0)
        value = (func_00283CF0(func_00283CE0() / (f32)divisor) + 1) << 4;
    return value;
}
