/* 4 November 2026: meaningful product and return one-pass groups remain
 * 12/16 bytes, 0/1 USA placements at G8; they do not restore the missing nop. The equivalent
 * eight-function boot/level family remains unresolved.
 */
/* func_002828B8 - 16 bytes, 1 place (the boot), retail at 0x002828b8:
   lwc1 $f0,-0x76E0($gp) ; nop ; jr $ra ; mul.s $f0,$f0,$f12.  The gp
   relative float constant (D_001A7910) and the multiplication are right,
   but this cc1 moves the `jr $ra` into the delay slot of the `lwc1`, so
   the candidate is 12 bytes.  Measured: -fno-schedule-insns does not change
   it (the move is the assembler's, not the scheduler's), and neither the
   local-variable spellings nor a second use of the constant.  The body
   needs the -G8 profile, so it belongs in 0027F128-g8.c.
   Same wall for func_002828F0 (offset -0x76DC), func_00282928 (-0x76D8)
   and func_00282938 (-0x76D4). An isolated 29 October
   -fno-schedule-insns2 unit remains 12 bytes and 0/1; it retains the same
   lwc1/jr/mul.s sequence and does not restore the hazard nop or GP offset. */
typedef float f32;

extern float D_001A7910 __attribute__((sda));

f32 func_002828B8(f32 a0) { return D_001A7910 * a0; }
