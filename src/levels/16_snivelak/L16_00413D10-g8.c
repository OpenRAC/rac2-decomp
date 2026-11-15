#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *CreateMoby(s32);
extern void euler_rotation_basis(void *, void *);
extern float math_random_float_range(float, float);
extern u8 *part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, float, float, float, s32);
extern float D_L16_001B1998 __attribute__((sda));
extern s32 D_L16_001B1908 __attribute__((sda));
extern s32 D_L16_001B190C __attribute__((sda));
extern u8 D_L16_001A8F20[] __attribute__((sda));

/* Spawns the 0xF7A object at the position with the velocity, hands it to its owner, and
   starts two particle bursts on it. */
u8 *snivelak_spawn_spark_projectile(u8 *owner, TI128 *velocity, TI128 *position, float speed)
{
    u8 *obj;
    u8 *state;
    u8 *pos;
    float scale;
    obj = CreateMoby(0xF7A);
    if (obj) {
        obj[0x30] = 255;
        *(u16 *)(obj + 0x32) = 255;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(s64 *)(obj + 0x38) = *(s64 *)(owner + 0x38);
        pos = obj + 0x10;
        qcopy(pos, position);
        *(u16 *)(obj + 0x34) |= 0x41;
        state = *(u8 **)(obj + 0x68);
        qcopy(state, velocity);
        *(float *)(state + 0x14) = speed;
        *(float *)(state + 0x20) = 0.15f;
        *(u8 **)(state + 0x10) = owner;
        *(u16 *)(obj + 0x34) |= 0x208;
        qcopy(obj + 0xF0, owner + 0xF0);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        obj[0x23] = 128;
        *(float *)(obj + 0x2C) = D_L16_001B1998;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(state + 0x24) = 0;
        scale = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(pos, 15, D_L16_001B1908, 0, 10, D_L16_001A8F20, scale * 0.3f, scale, 0.0f, 0);
        part_spawn_ground_effect(pos, 15, D_L16_001B190C, 1, -10, D_L16_001A8F20, scale * 0.04f, scale * 0.4f, 0.0f, 0);
    }
    return obj;
}
