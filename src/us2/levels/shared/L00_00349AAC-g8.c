/* func_US2_L00_00349AAC, the level copy of func_US2_002D023C (the v2.00 relative of
 * func_002CF2B8): the same C, where func_US2_0029D368 becomes the level's func_US2_L00_0030E850. */
#include "common.h"

extern void func_0027C540(int);
extern void func_US2_L00_0030E850(void);
extern s32 func_00288FB8(s32);
extern void func_0027F980(int, int, u64, u8 *, int);
extern void func_0027C660(void);
extern int D_US2_001ABA28 __attribute__((sda));
extern int D_US2_001ABA2C;

int func_US2_L00_00349AAC(void)
{
    func_0027C540(0);
    func_US2_L00_0030E850();
    func_0027F980(D_US2_001ABA28, D_US2_001ABA2C, 0x80F0F0F0ULL, (u8 *)func_00288FB8(0x2BE5), -1);
    func_0027C660();
    return 0;
}
