#include "include_asm.h"



#include "common.h"
extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern int math_random_int_below(int);
extern u8 *g_hero_moby;
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 math_fast_float_d(s32);
extern int FastDecTimer();
extern void build_axis_rotation_quaternion(s32, s32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern void AttachManipulator(s32, s32, s32);
extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern u8 *g_hero_moby;

/* func_L22_0040C888 is in L22_0040C888-g8.c. */

/* func_L22_0040D638 lives in L22_00358778-state-g8.c. */

void func_PAL_L22_00412818(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    math_fast_float_d(s0 + 0x258);
    FastDecTimer(s0 + 0x25C);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    if (*(u8 *)(s0 + 0x211) == 0)
        AttachManipulator(s1, 7, s0 + 0x210);
    build_axis_rotation_quaternion(s0 + 0x220, 2, *(f32 *)(s0 + 0x26C));
    *(f32 *)(s0 + 0x26C) = fast_subtract_rotations(*(f32 *)(s0 + 0x26C), 0.49916422f);
}


extern void vec_scale_to_length(void *, void *, float);
extern s32 func_2F36F0(s32);
extern f32 func_2F4AD0(f32, f32);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void vec_scale_to_length(void *, void *, f32);

void func_PAL_L22_004128B8(u8 *a0, f32 *a1, f32 f12) {
    f32 vec1[4] __attribute__((aligned(16)));
    f32 vec2[4] __attribute__((aligned(16)));
    f32 scale = f12;

    if (D_L22_001AF314[0] != 0 && *(f32 *)(*(u8 **)(D_L22_001AF314[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    moby_transform_joint_to_world(a0, 2, vec1);
    if (scale == 0.0f) {
        scale = D_L22_001B2A98;
    }
    FastVecSub(vec2, a1, vec1);
    vec_scale_to_length(vec2, vec2, 0.8000001f);
    func_PAL_L22_00412B98(vec1, vec2, &scale);
    moby_transform_joint_to_world(a0, 3, vec1);
    FastVecSub(vec2, a1, vec1);
    vec_scale_to_length(vec2, vec2, 0.8000001f);
    func_PAL_L22_00412B98(vec1, vec2, &scale);
}


extern int moby_copy_vector_to_child();
extern void FastVecAdd(void *, void *, void *);
extern int moby_check_target_point_from_offset(s32, s32);
extern void arena_push_point_out(void *, f32);

void func_PAL_L22_004129D8(s32 a0, s32 a1, s32 a2, f32 f12) {
    u8 buf[0x10];
    u8 buf2[0x10];
    f32 v = f12;

    FastVecSub(buf, (void *)a1, (void *)(a0 + 0x10));
    v = v * 0.020000001f;
    vec_scale_to_length(buf, buf, v);
    if (a2 != 0) {
        FastVecAdd(buf2, (void *)(a0 + 0x10), buf);
        arena_push_point_out(buf2, 7.2f);
        FastVecSub(buf, buf2, (void *)(a0 + 0x10));
        vec_scale_to_length(buf, buf, v);
    }
    moby_check_target_point_from_offset(a0, a1);
    moby_copy_vector_to_child(a0, buf);
}

