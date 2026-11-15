#include "common.h"
extern void vec_transform_or_copy(char *, char *);
extern void FastVecScale(char *, char *, float);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern float math_random_float_range(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastDecTimer(char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern void part_kill(char *);
extern int g_game_time __attribute__((sda));
extern char g_active_camera[];
extern char g_hero_position[];
extern float fast_vec_dist(char *, char *);
extern void FastVecSub(char *, char *, char *);
/* Updates a floating particle: it slows down, sinks, gets pushed away by the hero and fades out. It is removed when its life runs out. */
void part_update_floating_dust(char *particle)
{
    char *motion, *position = particle + 16, *hero, *hero_base;
    float push[4], hero_pos[4];
    float a, b;
    motion = particle + 32;
    vec_transform_or_copy(position, position);
    FastVecScale(motion, motion, 0.9f);
    *(float *)(motion + 8) -= *(float *)(motion + 12);
    FastVecAdd(position, position, motion);
    hero = g_hero_position;
    if (fast_vec_dist(position, hero) < 1.05f) {
      hero_base = hero - 128;
      if (*(float *)(hero_base + 0x170) != 0) {
        qcopy(hero_pos, hero);
        FastVecSub((char *)push, position, (char *)hero_pos);
        a = math_random_float_range(0.1f, 2.0f);
        vec_scale_to_length((char *)push, (char *)push, *(float *)(hero_base + 0x170) * 0.2f + a * 0.016666667f * 0.15f);
        *(unsigned char *)(particle + 8) += (int)(*(short *)(motion + 22) * *(float *)(hero_base + 0x170) * 0.5f);
        FastVecAdd(position, position, (char *)push);
    }
    }
    if (g_game_time % 10 == 0) {
        *(float *)(motion + 28) = FastAddRotations(*(float *)(motion + 28), 1.0f);
        a = math_fast_sin_or_cos_b(*(float *)(motion + 28));
        vec_scale_to_length((char *)push, g_active_camera, a * 0.0075f);
        FastVecAdd(motion, motion, (char *)push);
    }
    if (*(short *)(motion + 20) >= 160) {
        if (*(short *)(particle + 10) < *(short *)(motion + 20)) {
            a = IntToFloat(*(short *)(particle + 10)); b = IntToFloat(*(short *)(motion + 20));
            *(int *)(particle + 4) = (FloatToInt((a /= b) * 128.0f) << 24) | 0x353535;
        } else *(int *)(particle + 4) = 0x9F353535;
    } else {
        if (*(short *)(particle + 10) < *(short *)(motion + 20)) {
            a = IntToFloat(*(short *)(particle + 10)); b = IntToFloat(*(short *)(motion + 20));
            *(int *)(particle + 4) = (FloatToInt((a /= b) * 64.0f) << 24) | 0x909090;
        } else *(int *)(particle + 4) = 0x40909090;
    }
    *(unsigned char *)(particle + 8) += *(unsigned char *)(motion + 22);
    if (FastDecTimer(particle + 10)) part_kill(particle);
}
