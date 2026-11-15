#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern char g_hero_state[] __attribute__((nosda));
extern float IntToFloat(int value);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern void vec_scale_to_length(void *out, void *vector, float scale);
extern void FastVecAdd(void *out, void *left, void *right);

/* Moves position along three axes of the active camera, scaled by a sine and two cosines of the angle derived from the object's field at +0x38. */
void part_place_near_camera(void *unused, char *position)
{
    Vector temporary;
    float scale = 1.2f;
    float angle = IntToFloat(*(int *)(position + 0x38));
    char *base;
    char *axis_a, *axis_b, *axis_c;
    float wave;

    wave = IntToFloat(3);
    wave = 3.1415927f / wave;
    angle *= wave;
    base = g_hero_state;
    axis_a = *(char **)(base + 0x2290) + 0xd0;
    wave = math_fast_sin_or_cos_a(angle);
    vec_scale_to_length(&temporary, axis_a, wave * scale);
    FastVecAdd(position, &temporary, base + 0x80);
    axis_b = *(char **)(base + 0x2290) + 0xe0;
    wave = math_fast_sin_or_cos_b(angle);
    vec_scale_to_length(&temporary, axis_b, wave * scale + 2.2f);
    FastVecAdd(position, position, &temporary);
    axis_c = *(char **)(base + 0x2290) + 0xc0;
    wave = math_fast_sin_or_cos_b(angle);
    vec_scale_to_length(&temporary, axis_c, wave + wave);
    FastVecAdd(position, position, &temporary);
}
