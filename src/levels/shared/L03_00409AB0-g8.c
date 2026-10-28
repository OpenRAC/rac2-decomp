#include "common.h"

extern void func_002A7750(u8 *, s32, s32);
extern f32 func_002AA548(void *, void *, f32, f32, f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern s32 func_00282948(void *);
extern f32 D_L03_001B1650 __attribute__((sda));
extern f32 D_L03_001B1654 __attribute__((sda));
extern f32 D_L03_001B1658 __attribute__((sda));

void func_L03_00409AB0(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        qcopy(vars, object + 0x10);
        func_002A7750(object, 1, -1);
        *(s32 *)(object + 0x98) = 0;
        *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
        break;
    case 2:
        func_002AA548(object + 0x18, vars + 0x10, *(f32 *)(vars + 8), 0.0f,
                     D_L03_001B1654 * 0.00027777778450399637f,
                     D_L03_001B1658 * 0.01666666753590107f);
        if (*(f32 *)(object + 0x18) <= *(f32 *)(vars + 8)) {
            *(f32 *)(vars + 0x10) = 0.0f;
            if (func_00282948(vars + 0x14) != 0)
                func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        func_002AA2E8((f32 *)(vars + 0x10),
                     D_L03_001B1658 * 0.01666666753590107f,
                     D_L03_001B1650 * 0.00027777778450399637f);
        *(f32 *)(object + 0x18) += *(f32 *)(vars + 0x10);
        if (object[0x31] == 0) {
            *(s32 *)(object + 0x98) = 0;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
            func_002A7750(object, 1, -1);
        }
        break;
    }
}
