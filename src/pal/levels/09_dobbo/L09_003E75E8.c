#include "include_asm.h"

#include "common.h"
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);

/* The record's state byte is a small switch, not an if/else chain: the retail
   compares it against 0 and 1 in turn and falls straight out for anything else.
   State 0 draws a random duration in 150..200 and marks the record active;
   state 1 converts the drawn duration to a signed angle and folds it into the
   record's angle through the resident step body. */
void func_PAL_L09_003E75E8(unsigned char *a0) {
    switch (a0[0x20]) {
    case 0:
        a0[0xBC] = func_002A7820(0x96, 0xC8);
        if (func_002A77E0(2) != 0) {
            a0[0x95] = 1;
        }
        a0[0x20] = 1;
        break;
    case 1:
        if (a0[0x95] != 0) {
            *(float *)(a0 + 0xF4) = func_00283B98(
                *(float *)(a0 + 0xF4), -((float)a0[0xBC] * 0.0003490659f));
        } else {
            *(float *)(a0 + 0xF4) = func_00283B98(
                *(float *)(a0 + 0xF4), (float)a0[0xBC] * 0.0003490659f);
        }
        break;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L09_003E76B0);
