/* func_PAL_L12_0040CBA0, the PAL copy of func_L12_00408050: the same C with the two 15-frame
   effect durations become 12. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(s32);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float, float);
extern u8 *func_002C2210(void *, s32, s32, s32, s32, void *, float, float, float, s32);
extern float D_L12_001B15B0 __attribute__((sda));
extern s32 D_L12_001B1520 __attribute__((sda));
extern s32 D_L12_001B1524 __attribute__((sda));
extern u8 D_L12_001A8F20[] MACRO_ADDR;

/* The func_L16_00413D10 spawner for the 0xEA5 object: places it at the position with the
   velocity, hands it to its owner, and starts two particle bursts on it. The burst table is a
   MACRO_ADDR object, so its lui/addiu pair is emitted again for each call. */
u8 *func_PAL_L12_0040CBA0(u8 *owner, TI128 *velocity, TI128 *position, float speed)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    float scale;
    obj = func_0029EFD0(0xEA5);
    if (obj) {
        obj[0x30] = 255;
        *(u16 *)(obj + 0x32) = 255;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(s64 *)(obj + 0x38) = *(s64 *)(owner + 0x38);
        pos = obj + 0x10;
        qcopy(pos, position);
        state = *(u8 **)(obj + 0x68);
        qcopy(state, velocity);
        *(float *)(state + 0x14) = speed;
        *(float *)(state + 0x20) = 0.15f;
        *(u8 **)(state + 0x10) = owner;
        *(u16 *)(obj + 0x34) |= 0x208;
        qcopy(obj + 0xF0, owner + 0xF0);
        func_002833F0(obj + 0xC0, obj + 0xF0);
        obj[0x23] = 128;
        *(float *)(obj + 0x2C) = D_L12_001B15B0;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(state + 0x24) = 0;
        scale = func_002A7878(8.0f, 10.0f);
        func_002C2210(pos, 12, D_L12_001B1520, 0, 10, D_L12_001A8F20, scale * 0.3f, scale, 0.0f, 0);
        func_002C2210(pos, 12, D_L12_001B1524, 1, -10, D_L12_001A8F20, scale * 0.04f, scale * 0.4f, 0.0f, 0);
    }
    return obj;
}
