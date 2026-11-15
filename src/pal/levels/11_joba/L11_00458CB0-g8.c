#include "include_asm.h"

#include "common.h"
extern float math_random_float_range(float a, float b);
extern void vec_scale_to_length(char *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern char g_sound_state[];
extern char D_L11_001BA8C0[];
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void get_moby_color(void *, void *, void *, void *);
extern void moby_update_ground_check(void *);
extern float func_PAL_002AA108(void *, void *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern float fast_vec_dist(void *, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void func_PAL_002AC290(void *, void *);
extern void vec_random_direction(void *, float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern float FastAddRotations(float, float);
extern float func_L00_002EE290(void *);
extern void drone_update_lock_on(char *);
extern void func_PAL_L11_0045A9A8(char *);
extern u8 *arena_get_center_point(u8 *);
extern int arena_is_point_in_inner_zone(u8 *, u8 *);

/* The launcher's state handler: re-arms the shot, aims the head at the level's
   target and hands the launch to the level's helpers. */
void func_PAL_L11_0045A0D8(char *p)
{
    char *q = *(char **)(p + 0x68);
    float vec0[4];
    float vec1[4];
    float vec2[4];
    float d;
    float dot;
    float len;
    int idx;
    char *ptr;
    char *entry;
    u8 *r;

    if (*(u8 *)(p + 0x20) == 0) {
        *(int *)(q + 0x18) = (int)(q + 0x60);
        *(float *)(p + 0x2C) *= 0.75f;
        *(int *)(q + 0x1DC) = -1;
        *(u8 *)(q + 0x48) = FloatToInt(15.0f);
        *(u8 *)(q + 0x4A) = FloatToInt(12.0f);
        *(float *)(q + 0x1D0) =
            math_random_float_range(-*(float *)(q + 0x1D0), *(float *)(q + 0x1D0)) *
            0.01745329424738884f;
        *(u8 *)(p + 0x30) = 0x80;
        *(int *)(q + 0x1D4) = 1;
        *(float *)(q + 0x1D8) *= 0.020000001f;
        moby_set_controller_speed_limits(p, 0.040000003f, 2.0000002f,
                      0.0016755164f, 0.12566373f);
        *(int *)(q + 0x98) |= 4;
        *(float *)(q + 0x60) = 0.75f;
        *(float *)(q + 0x68) = 0.75f;
        *(int *)(q + 0x64) = 0;
        *(float *)(q + 0x6C) = 0.5f;
        *(float *)(q + 0x70) = 1.134464144706726f;
        *(float *)(q + 0x90) = 0.523598849773407f;
        *(float *)(q + 0x8C) = 0.004f;
        get_moby_color(p, q + 0x1F0, q + 0x1F4, q + 0x1F8);
        *(u8 *)(q + 0x28) = 3;
        *(int *)(q + 0x30) = 0;
        *(short *)(q + 0x1EC) = 0;
        func_PAL_L11_0045A9A8(p);
    }
    if (*(short *)(q + 0x1FC) == 0 && *(u8 *)(p + 0x20) != 0xE &&
        D_L11_001A8FF4 == 0) {
        *(u16 *)(p + 0x34) |= 0x400;
        if (*(u8 *)(p + 0x31) != 0) {
            if (fast_vec_dist(p + 0x10, D_L11_001BA8C0) < 24.0f) {
                moby_update_ground_check(p);
                *(u8 *)(p + 0x6F) = 0x16;
            }
        }
    } else {
        *(u16 *)(p + 0x34) &= 0xFBFF;
    }
    if (*(u8 *)(p + 0x95) >= 2) {
        if (snd_is_voice_playing_for_owner(p, *(int *)(q + 0x1DC)) == 0)
            *(int *)(q + 0x1DC) = PlayMobySound(1, 4, p);
    } else {
        if (snd_is_voice_playing_for_owner(p, *(int *)(q + 0x1DC))) {
            idx = *(int *)(q + 0x1DC);
            if (idx != -1) {
                entry = g_sound_state + idx * 0x70;
                if (*(char **)(entry + 0x88) == p && *(u8 *)(entry + 0x74) != 0)
                    snd_stop_voice(idx);
            }
            *(int *)(q + 0x1DC) = -1;
        }
    }
    if (*(short *)(q + 0x1FC) != 0)
        *(int *)(q + 0x98) &= ~0x10;
    else
        *(int *)(q + 0x98) |= 0x10;
    ptr = (char *)part_find_owned_effect_slot(p, 0x10000, 0);
    if (ptr != 0) {
        r = *(u8 **)(ptr + 0x20);
        if (r != 0) {
            if (*(short *)(r + 0xAA) == 0xA03)
                *(int *)(ptr + 0x2C) = 0;
            else if (*(u8 *)(p + 0x31) == 0 && *(short *)(r + 0xAA) == 0xB89)
                *(int *)(ptr + 0x2C) = 0;
        }
    }
    d = func_PAL_002AA108(p, ptr);
    *(u8 *)(p + 0xA8) = 0xFF;
    *(float *)(q + 0x20) -= d;
    if (d != 0.0f) {
        if (*(u8 *)(p + 0x20) != 3 && *(u8 *)(p + 0x20) != 0xE) {
            vec_scale_to_length((char *)vec0, ptr + 0x10, 1.2f);
            vec_random_direction(vec1, -0.2f, 0.2f);
            FastVecAdd(vec0, vec0, vec1);
            if (*(short *)(q + 0x1FC) == 0) {
                vec0[2] = math_random_float_range(0.0f, 0.0f) * 0.00040000002f;
                vec0[3] = 5627.9248046875f;
            } else {
                FastVecSub(vec2, arena_get_center_point(*(u8 **)(p + 0xB8)),
                              p + 0x10);
                vec2[2] = 0.0f;
                vec_scale_to_length((char *)vec2, vec2, 1.0f);
                dot = FastVecDot(vec0, vec2);
                if (dot < 0.0f) {
                    vec_scale_to_length((char *)vec2, vec2, dot);
                    len = FastVecLength(vec0);
                    FastVecSub(vec0, vec0, vec2);
                    vec_scale_to_length((char *)vec0, vec0, len);
                }
            }
            FastVecAdd(q + 0x100, q + 0x100, vec0);
            vec_random_direction(vec1, 0.0025132746f, 0.010053098f);
            *(float *)(q + 0x1B0) = FastAddRotations(*(float *)(q + 0x1B0), vec1[0]);
            *(float *)(q + 0x1B4) = FastAddRotations(*(float *)(q + 0x1B4), vec1[1]);
            *(float *)(q + 0x1B8) = FastAddRotations(*(float *)(q + 0x1B8), vec1[2]);
            func_PAL_002AC290(p, q + 0x50);
            moby_set_state(p, 0xD, 4);
        }
    }
    if (*(short *)(q + 0x1FC) != 0) {
        matrix_from_basis_rows(q + 0x170, p + 0xC0);
        cam_compute_view_direction(p + 0x10, q + 0x1A0, 0);
        if (arena_is_point_in_inner_zone(*(u8 **)(p + 0xB8), (u8 *)(p + 0x10)) == 0) {
            *(int *)(q + 0x20) = 0;
            moby_set_state(p, 0xE, 4);
        }
        if (*(u8 *)(p + 0x20) != 0xE) {
            len = *(float *)(p + 0x18);
            r = arena_get_center_point(*(u8 **)(p + 0xB8));
            FastVecSub(vec0, p + 0x10, r);
            vec0[2] = 0.0f;
            if (func_L00_002EE290(vec0) > 225.0f) {
                vec_scale_to_length((char *)vec0, vec0, 15.0f);
                r = arena_get_center_point(*(u8 **)(p + 0xB8));
                FastVecAdd(p + 0x10, vec0, r);
                *(float *)(p + 0x18) = len;
            }
        }
    }
    if (*(u8 *)(p + 0x20) >= 2 && *(u8 *)(q + 0x2E) == 2)
        func_PAL_L11_0045A9A8(p);
    drone_update_lock_on(p);
}
