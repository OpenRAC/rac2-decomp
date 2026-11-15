#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L23_001B1AD8 __attribute__((sda));
extern s32 D_L23_001B1A44 __attribute__((sda));
extern s32 D_L23_001B1A48 __attribute__((sda));
extern float D_L23_001B1A14 __attribute__((sda));
extern float D_L23_001B1A2C __attribute__((sda));
extern float D_L23_001B1A38 __attribute__((sda));
extern float D_L23_001B1A20 __attribute__((sda));
extern u8 D_L23_001A8F20[] MACRO_ADDR;
extern void *CreateMoby(s32);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float vec_length_xy(void *);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, float, float, float, s32);

u8 *func_PAL_L23_0042D620(u8 *parent, TI128 *a1, TI128 *a2, s32 b, float f) {
    u8 *obj = CreateMoby(0x1230);
    u8 *payload;
    float rotationRandom;
    float particleRandom;
    float v30, v34, v38, v3c;

    if (obj != 0) {
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0xBC] = b;
        obj[0x20] = 0;
        *(s64 *)(obj + 0x38) = *(s64 *)(parent + 0x38);
        qcopy(obj + 0x10, a2);
        payload = *(u8 **)(obj + 0x68);
        qcopy(payload, a1);
        *(u8 **)(payload + 0x10) = parent;
        *(float *)(payload + 0x14) = f;
        *(float *)(payload + 0x20) = 0.15f;
        *(u16 *)(obj + 0x34) |= 0x208;
        *(float *)(obj + 0xF8) = FastAddRotations(mat_fast_helper_a(((float *)a1)[0], ((float *)a1)[1]), 1.5707965f);
        *(float *)(obj + 0xF0) = -mat_fast_helper_a(vec_length_xy(a1), ((float *)a1)[2]);
        rotationRandom = math_random_angle();
        math_apply_axis_rotation_to_quat(obj + 0xE0, obj + 0xE0, obj + 0xD0, rotationRandom);
        math_apply_axis_rotation_to_quat(obj + 0xC0, obj + 0xC0, obj + 0xD0, rotationRandom);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        obj[0x23] = 0x80;
        *(float *)(obj + 0x2C) = D_L23_001B1AD8;
        *(u16 *)(obj + 0x34) |= 0x100;
        *(s32 *)(payload + 0x24) = 0;
        particleRandom = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(obj + 0x10, 0xC, D_L23_001B1A44, 0, 10, D_L23_001A8F20, particleRandom * 0.3f, particleRandom, 0.0f, 0);
        part_spawn_ground_effect(obj + 0x10, 0xC, D_L23_001B1A48, 1, -10, D_L23_001A8F20, particleRandom * 0.04f, particleRandom * 0.4f, 0.0f, 0);
        v30 = D_L23_001B1A14;
        v34 = D_L23_001B1A2C;
        v38 = D_L23_001B1A38;
        v3c = D_L23_001B1A20;
        *(float *)(payload + 0x30) = v30;
        *(float *)(payload + 0x34) = v34;
        *(float *)(payload + 0x38) = v38;
        *(float *)(payload + 0x3C) = v3c;
    }
    return obj;
}
