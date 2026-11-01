/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_00283BE0 -- the difference of two angles, wrapped to [-pi, pi],
   72 bytes in retail.  It is func_00283B98 with a subtraction.

   Measured with tools/check.py in src/game/0027F128.c (the -O2 -G0 profile):
   "func_00283BE0: 0 of 28 places match", 92 bytes against retail's 72.

   A semantics-preserving early-subtract form, using `if (!(r < p))` before
   the lower-bound check, measures 96 bytes, 0/28. It moves the result into
   `$f0` immediately and materializes the constants in `$f14`/`$f15`, but
   keeps a longer branch layout than retail. The retained nested form remains
   the shorter 92-byte candidate; no match is established.

   29 October 2026 `-ffast-math` profile probe: still 92 bytes, 0/28. It
   changes comparisons to an annulled branch and recomputes constants on each
   path, adding return paths instead of recovering retail's shared constants
   and single epilogue. This profile is not closer.

   A 29 October NaN-preserving `goto done` form with the upper-bound test
   expressed as `!(r < p)` compiles to 96 bytes, 0/28. It preserves the
   comparison behavior of the nested form but cc1 keeps two separately
   materialized constants and lays out two branch paths before the shared
   return, so it is larger and farther from retail.

   The nested candidate's remaining differences are the float register
   allocation: retail keeps the difference in `$f0` and pi in `$f14`, while
   this cc1 keeps the difference in `$f12` and the constants in `$f1`/`$f0`.
*/
typedef float f32;

f32 func_00283BE0(f32 a0, f32 a1) {
    f32 r = a0 - a1;
    f32 p = 3.1415927f;
    f32 n = -3.1415927f;

    if (r < p) {
        if (r < n) {
            r = r + p;
            r = r + p;
        }
        return r;
    }
    r = r - p;
    r = r - p;
    return r;
}
