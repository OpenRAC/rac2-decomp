#include "common.h"

extern void func_0027C540(int);
extern void func_0027C660(void);
extern s32 func_00288FB8(s32);
extern void func_PAL_0029CEC8(void);
extern int func_0027F980(int v, int p7, unsigned long long k, char *r, int m1);
extern int D_PAL_001ABA98 __attribute__((sda));
extern int D_PAL_001ABA9C[] __attribute__((sda));

/* func_PAL_002D022C, the PAL copy of func_002CF2B8: the same C, where the text
 * position comes from two PAL words in place of 0x1A5 and the scaled 256, and
 * the string id becomes 0xB60. */
int func_PAL_002D022C(void)
{
    func_0027C540(0);
    func_PAL_0029CEC8();
    func_0027F980(D_PAL_001ABA98, D_PAL_001ABA9C[0], 0x80F0F0F0ULL, (char *)func_00288FB8(0xb60), -1);
    func_0027C660();
    return 0;
}
