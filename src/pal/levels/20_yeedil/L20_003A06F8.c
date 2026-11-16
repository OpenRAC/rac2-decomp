#include "include_asm.h"

#include "common.h"
extern int g_frame_l20_counter __attribute__((sda));
extern int trooper_spawn_parts_pal(char *, int);
extern void SpawnHealthThresholdEffects_pal(char *);
extern void trooper_count_closer_mates(char *);
extern float fast_subtract_rotations(float, float);
extern float math_approach_target_with_direction_mode(char *, char *, float, float, float, float, int);
extern f32 func_00303270(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 FastVecLength(void *);
extern f32 vec_distance_xy(void *, void *);
extern s32 path_check_entry_for_moby(char *, s32);
extern f32 vec_distance_xy(void *, void *);

void trooper_update_body_pal(char *arg0) {
    char *s0 = arg0;
    char *s1;
    f32 c;
    f32 r;
    u32 v1;
    u16 v2;

    s1 = *(char **)(s0 + 0x68);
    trooper_spawn_parts_pal(s0, 0);
    SpawnHealthThresholdEffects_pal(s0);
    if ((g_frame_l20_counter & 7) == (((s32)s0 >> 8) & 7)) {
        trooper_count_closer_mates(s0);
    }
    c = 0.013962637f;
    r = fast_subtract_rotations(*(f32 *)(s1 + 0x284), *(f32 *)(s0 + 0xF8));
    {
        f32 c2 = c;
        math_approach_target_with_direction_mode(s1 + 0x288, s1 + 0x28C, r, c, c2, 0.69813186f, 0);
    }
    *(f32 *)(s1 + 0x284) = *(f32 *)(s0 + 0xF8);
    v2 = *(u16 *)(s0 + 0x96);
    if ((u32)v2 <= 0xFFFEu) {
        *(u16 *)(s0 + 0x96) = v2 + 1;
    }
}


