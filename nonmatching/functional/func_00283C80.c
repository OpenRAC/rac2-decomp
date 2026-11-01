/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_00283C80 -- the angular distance between two angles, 56 bytes in
   retail.

   Retail: |a0 - a1|, and 2*pi - that when it is not below pi.

   Measured with tools/check.py in src/game/0027F128.c (the -O2 -G0 profile):
   "func_00283C80: 0 of 28 places match", 64 bytes against retail's 56.

   What differs, after this wave's measurements:

   - the shape is now right: writing the two returns separately gives
     retail's `c.olt.s` and its `bc1t` over the doubling arm, and the
     difference stays in `$f0` (the return register) as in retail.
   - retail doubles pi at run time (`add.s $f1,$f14,$f14`), this cc1 folds
     `pi + pi` into the constant 0x40C90FDB (three instructions) even when pi
     is a named local (`p = p + p`), so the doubling has no C spelling found
     here.  The only way this cc1 emits a run-time doubling is when pi is a
     value it cannot see the value of - a parameter - and then the constant
     cannot be materialised either.
   - retail keeps pi in `$f14`, this cc1 in `$f1`.
   - the SDK compiler profile (build/compiler/sdk, "sdk -O2 -G0
     -ffunction-sections -fno-builtin") emits the same words as the game's
     compiler for this body.

   31 October 2026 (Opus 5.5): recompiled, 64/56 bytes, 0/28.  Same catalogue identity
   (1ad1112489d5e314, 56 bytes) as RAC1 func_001FA850 (FastDiffRots), listed in RAC1's
   config/handwritten_asm.txt.  Retail also has a `nop` after `mtc1 $at,$f14` where
   the next instruction does not read $f14 (this compiler emits none there) and leaves
   `jr $ra` unfilled after `sub.s` (this compiler fills it).  Reported as HANDWRITTEN.
 */
typedef float f32;

f32 func_00283C80(f32 a0, f32 a1) {
    f32 d = a0 - a1;
    f32 p = 3.1415927f;

    d = __builtin_fabsf(d);
    if (d < p) {
        return d;
    }
    p = p + p;
    d = p - d;
    return d;
}
