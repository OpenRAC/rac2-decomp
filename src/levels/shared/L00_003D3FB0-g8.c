#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float v[4]; } Vector;
extern char D_00189E20[] __attribute__((nosda));
extern float func_00283CE0(int value);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern void func_00282F20(void *out, void *vector, float scale);
extern void func_00282CC0(void *out, void *left, void *right);

/* Moves position along three axes of the active camera, scaled by a sine and two cosines of the angle derived from the object's field at +0x38. */
void func_L00_003D3FB0(void *unused, char *position)
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
    base = gHeroState;
    axis_a = *(char **)(base + 0x2290) + 0xd0;
    wave = FastSinOrCosA(angle);
    vec_scale_to_length(&temporary, axis_a, wave * scale);
    FastVecAdd(position, &temporary, base + 0x80);
    axis_b = *(char **)(base + 0x2290) + 0xe0;
    wave = FastSinOrCosB(angle);
    vec_scale_to_length(&temporary, axis_b, wave * scale + 2.2f);
    FastVecAdd(position, position, &temporary);
    axis_c = *(char **)(base + 0x2290) + 0xc0;
    wave = FastSinOrCosB(angle);
    vec_scale_to_length(&temporary, axis_c, wave + wave);
    FastVecAdd(position, position, &temporary);
}
