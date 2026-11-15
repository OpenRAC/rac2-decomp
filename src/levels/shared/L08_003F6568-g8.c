#include "common.h"
extern s32 D_L08_001B29DC[] MACRO_ADDR;
extern s32 func_002A8508(s32, s32);
extern s32 func_002A8600(s32 *, s32, s32, s32);

s32 func_L08_003F6568(s32 a0, u8 *a1)
{
    s32 total;
    s32 tmp;
    s32 sel = -1;
    total = func_002A8508(*(s32 *)(a1 + 0x134), -1);
    total += func_002A8508(*(s32 *)(a1 + 0x138), -1);
    *(u8 *)(a1 + 0x131) = total;
    tmp = 0;
    if (GetFirstMobyInGroup(&tmp, *(s32 *)(a1 + 0x134), 1, 1) == 0 || GetFirstMobyInGroup(&tmp, *(s32 *)(a1 + 0x138), 1, 1) == 0) {
        sel = (tmp - D_L08_001B29DC[0]) >> 8;
    }
    return sel;
}
