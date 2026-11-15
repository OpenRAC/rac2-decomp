#include "include_asm.h"


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

void func_PAL_002C8D68(char *p)
{
    char *d, *position = p + 16, *hero, *base;
    float v[4], origin[4];
    float a, b;
    d = p + 32;
    vec_transform_or_copy(position, position);
    FastVecScale(d, d, 0.9f);
    *(float *)(d + 8) -= *(float *)(d + 12);
    FastVecAdd(position, position, d);
    hero = g_hero_position;
    if (fast_vec_dist(position, hero) < 1.05f) {
      base = hero - 128;
      if (*(float *)(base + 0x170) != 0) {
        qcopy(origin, hero);
        FastVecSub((char *)v, position, (char *)origin);
        a = math_random_float_range(0.1f, 2.0f);
        vec_scale_to_length((char *)v, (char *)v, *(float *)(base + 0x170) * 0.2f + a * 0.020000001f * 0.15f);
        *(unsigned char *)(p + 8) += (int)(*(short *)(d + 22) * *(float *)(base + 0x170) * 0.5f);
        FastVecAdd(position, position, (char *)v);
    }
    }
    if (g_game_time % 10 == 0) {
        *(float *)(d + 28) = FastAddRotations(*(float *)(d + 28), 1.0f);
        a = math_fast_sin_or_cos_b(*(float *)(d + 28));
        vec_scale_to_length((char *)v, g_active_camera, a * 0.0075f);
        FastVecAdd(d, d, (char *)v);
    }
    if (*(short *)(d + 20) >= 160) {
        if (*(short *)(p + 10) < *(short *)(d + 20)) {
            a = IntToFloat(*(short *)(p + 10)); b = IntToFloat(*(short *)(d + 20));
            *(int *)(p + 4) = (FloatToInt((a /= b) * 128.0f) << 24) | 0x353535;
        } else *(int *)(p + 4) = 0x9F353535;
    } else {
        if (*(short *)(p + 10) < *(short *)(d + 20)) {
            a = IntToFloat(*(short *)(p + 10)); b = IntToFloat(*(short *)(d + 20));
            *(int *)(p + 4) = (FloatToInt((a /= b) * 64.0f) << 24) | 0x909090;
        } else *(int *)(p + 4) = 0x40909090;
    }
    *(unsigned char *)(p + 8) += *(unsigned char *)(d + 22);
    if (FastDecTimer(p + 10)) part_kill(p);
}


