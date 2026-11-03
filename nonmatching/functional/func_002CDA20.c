/* functional: high. Same calls with the same arguments in the same order and the same result as retail; the near miss's matching-only do/while(0) wrapper and float local are gone. y is (D_001B23A4 * 293.0f) + 0.5f truncated toward zero (trunc.w.s), as the (int) cast does. The style is retail's 64-bit register holding 0x80F0F0F0 zero-extended (dli/dsll/ori), so it is unsigned long, as the landed func_002CF2B8/func_002D53F0 declare it; the text is a game address as host/font.c takes it. */

#include "common.h"

extern void func_0027C540(int);
extern void func_0029C4C0(void);
extern void func_0027C660(void);
extern int func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, unsigned int, int);

extern float D_001B23A4 NOT_SDA;

/* Draws a fixed text prompt (text id 0x2D4F) at x 0x1A5, y = 293 * D_001B23A4 + 0.5, colour 0x80F0F0F0, between the
   text-batch begin/end calls (func_0029C4C0 sets up the text state first). Returns 0. */
int func_002CDA20(void)
{
    int y;

    func_0027C540(0);
    func_0029C4C0();
    y = (int)(D_001B23A4 * 293.0f + 0.5f);
    func_0027FAA8(0x1A5, y, 0x80F0F0F0UL, (unsigned int)func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
