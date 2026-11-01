#include "include_asm.h"

#include "common.h"
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002B38B8(u8 *);
extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);

void func_PAL_L03_003CE080(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * 0.2f;
        *(u32 *)(vars + 0x5C) |= 1;
        qcopy(vars + 0x90, object + 0x10);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B38B8(object) != 0)
            func_002A7750(object, 2, -1);
        break;
    case 2:
        *(f32 *)(object + 0x18) = *(f32 *)(vars + 0xA0) + *(f32 *)(vars + 0x98);
        if (func_002B38B8(object) == 0) {
            *(f32 *)(object + 0x18) = *(f32 *)(vars + 0xA0) + *(f32 *)(vars + 0x98);
            func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        func_002AA548(object + 0x18, vars + 0xA4, *(f32 *)(vars + 0x98) + 2.8f,
                     0.0006f, 0.0006f,
                     0.060000002f);
        if (*(f32 *)(vars + 0x98) + 2.8f <= *(f32 *)(object + 0x18))
            *(u16 *)(object + 0x34) |= 2;
        break;
    }
}

