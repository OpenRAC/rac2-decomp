#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *D_0018C0B0;
extern f32 D_L08_001BE0B0;
extern u64 func_0027C878(int);
extern u8 D_L08_00296CD0[];
extern u8 D_L08_001DB5E7;
extern s32 D_L08_001DAC40[];
extern s32 D_L08_001BFEF4;
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u32 D_L08_001FB660[];
extern f32 func_00283248(f32, f32);
extern f32 func_00282E20(void *);
extern u8 *D_0018C0B0;

s32 func_PAL_L08_0033B2D0(u8 *p, s32 a1, s32 a2, u8 *out, f32 f1, f32 f2) {
    u8 *q;
    if (p == 0)
        return -1;
    q = *(u8 **)(p + 0x24);
    if (q == 0)
        return -1;
    if (*(s32 *)(q + 0x28) == 0)
        return -1;
    *(u32 *)(out + 0x1C) = (u32)p;
    *(f32 *)(out + 0x14) = f2 * 0.020000001f;
    *(f32 *)(out + 0x10) = f1 * 0.020000001f;
    *(TI128 *)out = *(TI128 *)(p + 0x10);
    *(s32 *)(out + 0x18) = a2;
    *(s32 *)(out + 0x20) = a1;
    return 1;
}

