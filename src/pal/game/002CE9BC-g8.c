#include "common.h"

extern void func_0027C540(int);
extern void func_PAL_0029CE58(void);
extern s32 func_00288FB8(s32);
extern void func_0027F980(int, int, u64, u8 *, int);
extern void func_0027C660(void);
/* PAL's stored panel text position (455, 293). */
extern int D_PAL_001ABA48 __attribute__((sda));
extern int D_PAL_001ABA4C[] __attribute__((sda));

/* func_PAL_002CE9BC, the PAL copy of func_002CDA20: the same centered panel text
   draw, where the fixed x and scaled y become PAL's stored position and text
   0x2D4F becomes 0xB60. */
int func_PAL_002CE9BC(void)
{
    func_0027C540(0);
    func_PAL_0029CE58();
    func_0027F980(D_PAL_001ABA48, D_PAL_001ABA4C[0], 0x80F0F0F0ULL, (u8 *)func_00288FB8(0xB60), -1);
    func_0027C660();
    return 0;
}
