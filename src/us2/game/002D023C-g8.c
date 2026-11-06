/* func_US2_002D023C, the v2.00 relative of func_002CF2B8: the same C, built with -G8, where the
 * x and y become v2.00 data (0x1C7 and 0x100), the callee func_0027F980 and the text id 0x2BE5. */
#include "common.h"

extern void func_0027C540(int);
extern void func_US2_0029D368(void);
extern s32 func_00288FB8(s32);
extern void func_0027F980(int, int, u64, u8 *, int);
extern void func_0027C660(void);
extern int D_US2_001ABA28 __attribute__((sda));
extern int D_US2_001ABA2C;

int func_US2_002D023C(void)
{
    func_0027C540(0);
    func_US2_0029D368();
    func_0027F980(D_US2_001ABA28, D_US2_001ABA2C, 0x80F0F0F0ULL, (u8 *)func_00288FB8(0x2BE5), -1);
    func_0027C660();
    return 0;
}
