#include "common.h"

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_spinning_effect_record(void *, void *, int, float, float);
extern float D_L06_001B1AC0 __attribute__((sda));
extern float D_L06_001B1AC4 __attribute__((sda));
extern float D_L06_001B1AC8 __attribute__((sda));
extern float D_L06_001B1ACC __attribute__((sda));
extern float D_L06_001B1AD0 __attribute__((sda));
extern float D_L06_001B1AD4 __attribute__((sda));
extern float D_L06_001B1AD8 __attribute__((sda));
extern float D_L06_001B1ADC __attribute__((sda));
extern int D_L06_001B1AE0 __attribute__((sda));
extern int D_L06_001B1AE4 __attribute__((sda));
extern int D_L06_001B1AE8 __attribute__((sda));

extern u8 *D_L06_001B281C MACRO_ADDR;
extern char g_sound_state[];
extern void func_003514C8(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern float FastVecLength(void *);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void chained_segment_spawn(char *);
extern int snd_is_voice_playing_for_owner(char *, int);
extern void snd_stop_voice(int);

extern u8 *D_L06_001B290C MACRO_ADDR;
extern char D_L06_001B1990[];
extern char D_L06_001B19C8[];
extern char D_L06_001B1A00[];
extern char D_L06_001B1A30[];
extern u8 *g_path_list[];

extern void STUB_printf(char *, ...);
extern int func_001163B0(void);
extern void path_l06_compute_segment_lengths(char *a0);
extern int actor_classify_headroom(char *a0, char *a1);
extern void actor_start_size_anim(unsigned char *a0, u8 *a1);

/* Turns this part to follow the progress value of the object it is linked to, and plays a sound while it moves. */
void linked_rotation_follower_update(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *other;
    float tmp[4];
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(vars + 8) = *(float *)(moby + 0xF8);
        *(float *)(vars + 0x18) = *(float *)(moby + 0xF4);
        *(int *)(vars + 0x10) = 0;
        func_003514C8(moby, 0, tmp);
        FastVecSub(tmp, tmp, (float *)(moby + 0x10));
        {
            float length = FastVecLength(tmp);
            *(float *)(vars + 4) -= length;
            *(float *)(vars + 0x1C) = length;
        }
        if (*(float *)(vars + 0xC) == 0.0f) *(float *)(vars + 0xC) = 1.0f;
        chained_segment_spawn(moby);
        *(float *)(vars + 0x24) = 0;
        moby[0x20] = 1;
        break;
    case 1:
        if (*(int *)vars != -1) {
            other = D_L06_001B281C + *(int *)vars * 256;
            if (other) {
                char *link_vars = *(char **)(other + 0x68);
                if (math_fabs(*(float *)(vars + 0xC)) > 0.0f)
                    *(float *)(vars + 0x14) = *(float *)link_vars * (*(float *)(vars + 0xC) * 3.1415927f);
                else *(float *)(vars + 0x14) = 0;
                *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(vars + 8), *(float *)(vars + 0x14));
                if (*(float *)link_vars > 0.6f)
                    *(float *)(moby + 0xF4) = fast_subtract_rotations(*(float *)(vars + 0x18), (*(float *)link_vars - 0.6f) * 0.13089971244335175f);
                if (*(int *)(vars + 0x10) == 0) {
                    if (*(float *)link_vars != *(float *)(vars + 0x24) && *(float *)link_vars != 1.0f && *(float *)link_vars != 0.0f) {
                        if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x20)))
                            *(int *)(vars + 0x20) = func_003A0948(0, 4, moby);
                    } else if (snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x20))) {
                        if (*(int *)(vars + 0x20) != -1) {
                        char *sound = g_sound_state + *(int *)(vars + 0x20) * 0x70;
                        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74)) snd_stop_voice(*(int *)(vars + 0x20));
                        }
                        *(int *)(vars + 0x20) = -1;
                    }
                }
                *(float *)(vars + 0x24) = *(float *)link_vars;
            }
        }
        if (*(int *)(vars + 0x10)) func_003514C8((void *)*(int *)(vars + 0x10), 0, moby + 0x10);
        break;
    }
}

/* Resolves the table entries a spawn record names; returns 1 after reporting a missing one. */
int spawn_record_resolve_links(u8 *moby, u8 *vars)
{
    s32 path_idx_a, path_idx_b, anchor_idx, home_idx;
    u8 *path_a, *path_b;

    path_idx_a = *(s32 *)(vars + 0x100);
    if (path_idx_a == -1) {
        STUB_printf(D_L06_001B1990, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    path_a = g_path_list[path_idx_a];
    *(u8 **)(vars + 0x118) = path_a;
    path_l06_compute_segment_lengths((char *)path_a);
    path_idx_b = *(s32 *)(vars + 0x134);
    if (path_idx_b == -1) {
        STUB_printf(D_L06_001B19C8, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    path_b = g_path_list[path_idx_b];
    *(u8 **)(vars + 0x138) = path_b;
    path_l06_compute_segment_lengths((char *)path_b);
    anchor_idx = *(s32 *)(vars + 0x108);
    if (anchor_idx == -1) {
        STUB_printf(D_L06_001B1A00, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    *(u8 **)(vars + 0x11C) = D_L06_001B281C + (anchor_idx << 8) + 0x18;
    moby[0xBC] = actor_classify_headroom((char *)moby, (char *)vars);
    home_idx = *(s32 *)(vars + 0x104);
    if (home_idx == -1) {
        STUB_printf(D_L06_001B1A30, (moby - D_L06_001B281C) >> 8);
        return 1;
    }
    qcopy(vars + 0xE0, D_L06_001B290C + 0x30 + (home_idx << 7));
    qcopy(vars + 0xD0, moby + 0x10);
    actor_start_size_anim(moby, vars);
    *(s32 *)(vars + 0x124) = func_001163B0() % 120;
    if (func_001163B0() & 1)
        *(f32 *)(vars + 0x130) = 0.3490659f;
    else
        *(f32 *)(vars + 0x130) = -0.3490659f;
    *(s32 *)(vars + 0x13C) = 0;
    vars[0x29] = 1;
    return 0;
}

/* Spits out a few small particles in front of the object, along the direction it is facing. */
void part_emit_facing(char *moby) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, moby + 0x10);
    pos[2] += 3.3f + math_random_float_range(-0.05f, 0.05f);
    pos[0] += math_random_float_range(-0.1f, 0.1f);
    pos[1] += math_random_float_range(-0.1f, 0.1f);
    offset[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * 1.5f;
    offset[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * 1.5f;
    offset[2] = 0;
    FastVecAdd(pos, pos, offset);
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
    part_spawn_spinning_effect_record(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    part_spawn_spinning_effect_record(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    if (math_random_int_below(D_L06_001B1AE8) != 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
        part_spawn_spinning_effect_record(pos, velocity, D_L06_001B1AE0, 0.5f, 50.4f);
    }
    if (math_random_int_below(D_L06_001B1AE8) != 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(D_L06_001B1AD8 * 0.0166666675f, 0.0300000012f);
        part_spawn_spinning_effect_record(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
    if (math_random_int_below(D_L06_001B1AE8) == 1) {
    velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby + 0xF8)) * math_random_float_range(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = math_random_float_range(D_L06_001B1AD8 * 0.0166666675f, D_L06_001B1ADC * 0.0166666675f);
        part_spawn_spinning_effect_record(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
}
