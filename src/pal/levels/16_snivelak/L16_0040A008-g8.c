#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(s32);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282E20(void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, s32, s32, s32, s32, void *, float, float, float, s32);
extern float D_L16_001B1500 __attribute__((sda));
extern s32 D_L16_001B1460 __attribute__((sda));
extern s32 D_L16_001B1464 __attribute__((sda));
extern u8 D_L16_001A8F20[] __attribute__((sda));

/* Spawns the 0xEBD object at the position with the velocity, aims it along the velocity,
   hands it to its owner and starts two particle bursts on it. */
u8 *func_PAL_L16_0040A008(float speed, u8 *owner, float *velocity, TI128 *position)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    u8 *rotation;
    u8 *axis;
    float scale;
    float angle;
    obj = func_0029EFD0(0xEBD);
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
        *(u8 **)(state + 0x10) = owner;
        *(float *)(state + 0x14) = speed;
        *(float *)(state + 0x20) = 0.15f;
        *(u16 *)(obj + 0x34) |= 0x208;
        rotation = obj + 0xC0;
        axis = obj + 0xD0;
        *(float *)(obj + 0xF8) = func_00283B98(func_00283248(velocity[0], velocity[1]), 1.5707965f);
        *(float *)(obj + 0xF0) = -func_00283248(func_00282E20(velocity), velocity[2]);
        angle = func_002A7940();
        func_002ACEC0(obj + 0xE0, obj + 0xE0, axis, angle);
        func_002ACEC0(rotation, rotation, axis, angle);
        func_002833F0(rotation, obj + 0xF0);
        obj[0x23] = 128;
        *(float *)(obj + 0x2C) = D_L16_001B1500;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(state + 0x24) = 0;
        scale = func_002A7878(8.0f, 10.0f);
        func_002C2210(pos, 12, D_L16_001B1460, 0, 10, D_L16_001A8F20, scale * 0.3f, scale, 0.0f, 0);
        func_002C2210(pos, 12, D_L16_001B1464, 1, -10, D_L16_001A8F20, scale * 0.04f, scale * 0.4f, 0.0f, 0);
    }
    return obj;
}
