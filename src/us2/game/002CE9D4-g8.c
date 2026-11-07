#include "common.h"

/* func_US2_002CE9D4, the USA v2.00 copy of func_002CDA20: the same draw sequence, where the text
 * (string 0x2BE5) goes through func_0027F980 at a stored position instead of a computed one. */

extern void func_0027C540(int);
extern void func_US2_0029D2F8(void);
extern int D_US2_001AB9E0 __attribute__((sda));
extern int D_US2_001AB9E4;
extern s32 func_00288FB8(s32);
extern void func_0027F980(int, int, u64, u8 *, int);
extern void func_0027C660(void);

int func_US2_002CE9D4(void)
{
    func_0027C540(0);
    func_US2_0029D2F8();
    func_0027F980(D_US2_001AB9E0, D_US2_001AB9E4, 0x80F0F0F0ULL, (u8 *)func_00288FB8(0x2BE5), -1);
    func_0027C660();
    return 0;
}
