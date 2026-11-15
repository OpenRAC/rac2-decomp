#include "common.h"

/* A unit of its own for -mno-split-addresses (config/cflags.txt): the level word at 0x001B20C4
   is then one assembler operand, which the assembler expands to the retail's absolute lui + load
   through the destination register, never in a delay slot. -G0 splits the address into a
   high-part register of its own; the flag would change the other bodies of the old unit. */

extern u8 *D_L12_001B20C4;
extern int math_fast_float_d(void *);
extern s32 math_random_int_range(s32, s32);
extern s32 PlayMobySound(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));

/* Starts the sub-object's timer when it has finished, then tells the engine to
   advance to mode 1.  The gp word at 0x30D0 needs its `sda` declaration (measured). */
void spark_timer_restart_sound(u8 *self) {
    u8 *vars = *(u8 **)(self + 0x68);

    if (math_fast_float_d(vars + 0x2C0) != 0) {
        *(s32 *)(vars + 0x2C0) = math_random_int_range(D_L12_001B20C0, (s32)D_L12_001B20C4);
        PlayMobySound(1, 0, self);
    }
}
