/* functional: high. Same calls with the same arguments in the same order and the same result as retail. Retail computes the value as (D_001B23A4 * 256.0f) + 0.5f truncated toward zero (trunc.w.s), which the (int) cast does. Retail passes the style as a 64-bit register holding 0x80F0F0F0 zero-extended (the callee stores all 64 bits into its packet; an int would sign-extend it, which the gate caught), so the style is unsigned long. The near-miss draft's ref_ name and level-copy callee were replaced with the boot names retail uses here (lui 0x1B / lwc1 9124 = D_001B23A4; jal 0x29C530 = func_0029C530). */

#include "common.h"

extern void func_0027C540(long);
extern void func_0029C530(void);
extern void func_0027C660(void);
extern int func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, unsigned int, int); /* text as host/font.c takes it (a game address); the style is retail's 64-bit register, as the landed func_002859C8/func_002D53F0 declare it */

extern float D_001B23A4 NOT_SDA;

/* Draws a fixed text prompt (text id 0x2D4F) at x 0x1A5, y = 256 * D_001B23A4 + 0.5, colour 0x80F0F0F0, between the
   text-batch begin/end calls. Returns 0. */
int func_002CF2B8(void)
{
    int y;

    func_0027C540(0);
    func_0029C530();
    y = (int)(D_001B23A4 * 256.0f + 0.5f);
    func_0027FAA8(0x1A5, y, 0x80F0F0F0UL, (unsigned int)func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
