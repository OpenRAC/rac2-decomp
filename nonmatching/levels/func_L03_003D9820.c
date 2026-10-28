/* Nonmatching reconstruction. Profile: -O2 -G8 -ffunction-sections -g.
 * 224 bytes, 0/2 US and US2; PAL ABSENT. Only the adjacent global lwc1 and class-pointer lw at +0xA4/+0xA8 are reversed. Local scale and multiplication order tie; -g does not fix it. Reopen with measured load scheduling or alias evidence.
 * No strict linked validation or matching credit.
 */
#include "common.h"

extern u8 *func_0029EFD0(s32);
extern void func_002B37E8(u8 *, u8 *);
extern f32 func_00283248(f32, f32);
extern f32 func_00282E20(void *);
extern f32 D_L03_001B08D8 __attribute__((sda));

u8 *func_L03_003D9820(u8 *owner, void *position, f32 *velocity, s32 value)
{
    u8 *object = func_0029EFD0(0xA72);
    u8 *vars;
    f32 scale;
    if (object != 0) {
        vars = *(u8 **)(object + 0x68);
        func_002B37E8(object, owner);
        qcopy(object + 0x10, position);
        *(f32 *)(object + 0xF8) = func_00283248(velocity[0], velocity[1]);
        *(f32 *)(object + 0xF4) = -func_00283248(func_00282E20(velocity), velocity[2]);
        qcopy(vars, velocity);
        *(s32 *)(vars + 0x18) = value;
        *(short *)(vars + 0x10) = 0x5A;
        *(u8 **)(vars + 0x14) = owner;
        *(short *)(vars + 0x12) = 0;
        scale = D_L03_001B08D8;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * scale;
    }
    return object;
}
