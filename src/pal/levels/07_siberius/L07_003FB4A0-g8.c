#include "include_asm.h"

#include "common.h"
extern s32 func_002A9640(u8 *, s32, s32);
extern f32 func_PAL_002AA108(u8 *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern void func_002A7750(u8 *, u8, s32);
extern f32 D_L07_001B0FD0 __attribute__((sda));
typedef struct { u8 pad[0x20]; f32 angle; u8 pad24[12]; u32 flags; } SpinnerState;

void func_PAL_L07_003FB4A0(u8 *a0)
{
    SpinnerState *s1 = *(SpinnerState **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 0) {
        f32 scale;
        s1->flags = 0;
        scale = D_L07_001B0FD0;
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * scale;
        func_002A7750(a0, 1, -1);
        *(u32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    {
        s32 id = func_002A9640(a0, 0x10000, 0);
        f32 angle = func_PAL_002AA108(a0, id);
        func_002AA2E8(&s1->angle, 0.0f, angle);
    }
    if (s1->angle <= 0.0f)
        func_002A7750(a0, 3, -1);
    *(u8 *)(a0 + 0xA8) = 0xFF;
}
