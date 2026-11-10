#include "include_asm.h"

/* Built with -frac2-hazard-labels (config/cflags.txt). The first clamp's bc1tl reaches the
   join label forward, between the reload of 1.0f (lui $at ; mtc1 $at,$f0) and the sub.s
   that reads it. Retail keeps the label on the hazard nop the assembler inserts there; GNU
   as without the switch moves it behind the nop, and the bc1tl lands one word late
   (docs/build/compiler-notes.md, labels in front of the hazard nop). */

typedef unsigned char u8;

extern float D_L02_001B2FE0 __attribute__((sda));

/* Clamps the state's float at 0x3C to 0..1 and stores its complement. */
void func_L02_00411530(u8 *a0)
{
    float *s = *(float **)(a0 + 0x68);
    float x = s[0x3C / 4];

    if (x > 1.0f)
        x = 1.0f;
    else if (x < 0.0f)
        x = 0.0f;
    D_L02_001B2FE0 = 1.0f - x;
}
