/* from src/levels/shared/L00_002E5918.c: retail, 16 bytes, 27 places:
   lwc1 $f0,-0x76E0($gp) ; nop ; jr $ra ; mul.s $f0,$f0,$f12.
   The candidate is 12 bytes with the same load and the same `mul.s` operand
   order: lwc1 ; jr $ra ; mul.s.  The one missing word is the `nop` between the
   load and the jump (the wall recorded in docs/build/compiler-notes.md).
   Measured this wave (wave 8 w06): -O0, -O1, -O2, -O3, -G0, -G8,
   -fno-schedule-insns, -fno-delayed-branch, -ffast-math, a volatile global
   and a double read of the global all give the compact three-instruction form
   (or a different order); nothing reaches 16 bytes.  Assembling the retail's
   exact four instructions with the game's `as` gives 12 bytes too, so the
   `nop` is not the assembler's FPR-hazard nop: the compiler has to emit it.
   Marked G8. */
extern float D_001A7910 __attribute__((sda));

float func_L00_002EDCB8(float a0) {
    return D_001A7910 * a0;
}
