#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int state_get_stored_pointer_value(void);
extern void level_append_object(void *, void *, int, int);
extern void moby_reset_action_state(void *);
extern void func_PAL_L15_0043B0D8(char *);
extern void func_PAL_L15_0043A270(void *, int);
extern void func_PAL_L15_0043BB70(void);
extern void gorn_ship_spawn_damage_effects(void *);
extern void func_PAL_L05_0042A240(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);
extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern s32 FloatToInt(f32 a);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int PlayMobySound(int, int, void *);
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);

void func_PAL_L15_00439D60(unsigned char *object) {
    float point[4] __attribute__((aligned(16)));
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float ratio;
    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        if (!state_get_stored_pointer_value()) return;
        func_PAL_L15_0043B0D8((char *)object);
        if (*(int *)(state + 0x264))
            level_append_object(object, func_PAL_L15_0043BB70, 0, 0);
        qcopy(state + 0x430, object + 0x10);
        break;
    case 1:
        func_PAL_L15_0043A270(object, 0);
        break;
    case 2:
        func_PAL_L15_0043A270(object, 1);
        if (math_fast_float_d(state + 0x274)) {
            object[0x20] = 3;
            *(int *)(state + 0x274) = 150;
        }
        break;
    case 3:
        func_PAL_L15_0043A270(object, 1);
        ratio = IntToFloat(*(int *)(state + 0x274)) / IntToFloat(150);
        object[0x23] = FloatToInt((1.0f - ratio) * 95.0f) + 32;
        if (math_fast_float_d(state + 0x274)) {
            *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
            object[0x20] = 4;
            *(int *)(state + 0x274) = 500;
            object[0x23] = 128;
            *(unsigned short *)(object + 0x34) &= 0xFFF7;
        }
        break;
    case 4:
        func_PAL_L15_0043A270(object, 0);
        if (math_fast_float_d(state + 0x274)) {
            *(int *)(object + 0x98) = 0;
            object[0x20] = 5;
            *(int *)(state + 0x274) = 150;
            *(unsigned short *)(object + 0x34) |= 8;
        }
        break;
    case 5:
        func_PAL_L15_0043A270(object, 1);
        ratio = IntToFloat(*(int *)(state + 0x274)) / IntToFloat(150);
        object[0x23] = FloatToInt(ratio * 95.0f) + 32;
        if (math_fast_float_d(state + 0x274)) {
            *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
            object[0x20] = 2;
            *(int *)(state + 0x274) = 400;
            object[0x23] = 32;
        }
        break;
    case 6:
        point[0] = *(float *)(object + 0x10) + math_random_float_range(-3.0f, 3.0f);
        point[1] = *(float *)(object + 0x14) + math_random_float_range(-3.0f, 3.0f);
        point[2] = *(float *)(object + 0x18) + math_random_float_range(-3.0f, 3.0f);
        if (*(int *)(state + 0x278) == 0) {
            func_PAL_L05_0042A240(point, 1, 24, 24, 24, 24, 24, 0, 3.0f, 1, 1, 1);
            *(int *)(state + 0x278) = 1;
        }
        if (math_random_int_below(12) == 0 && *(float *)(object + 0x18) > 350.0f)
            func_PAL_L05_0042A240(point, 0, 4, 4, 4, 4, 4, 0, 1.5f, 0, 0, 0);
        *(float *)(object + 0x18) -= *(float *)(state + 0x27C);
        *(float *)(state + 0x27C) += 0.00080000004f;
        *(float *)(state + 0x404) = FastAddRotations(*(float *)(state + 0x404), 0.0017453296f);
        euler_rotation_basis(object + 0xC0, state + 0x400);
        gorn_ship_spawn_damage_effects(object);
        if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
            *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
            *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
            moby_reset_action_state(object);
        break;
    case 7:
        FastVecAdd(object + 0x10, state + 0x410, object + 0x10);
        *(float *)(state + 0x418) -= 0.0044f;
        *(float *)(state + 0x404) = FastAddRotations(*(float *)(state + 0x404), 0.031415932f);
        euler_rotation_basis(object + 0xC0, state + 0x400);
        if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
            *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
            *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    math_fast_float_d(state + 0x450);
}
