#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

/* This unit is built with -ffast-math because the retail clamps the morph progress with the
   R5900's min.s and max.s (0x46020829 and 0x46020828). The approved cc1 only folds a float
   min/max into those instructions under -ffast-math: gcc/config/mips guards the fold with
   flag_fast_math, and the EE target's float format is IEEE. Measured with the approved
   compiler, -funsafe-math-optimizations, -fno-math-errno, -fassociative-math and
   -fno-signed-zeros all still emit c.lt.s. The retail's ordinary 32-bit stores in the parent
   unit are folded, so the flag is specific to the 128-bit and float-clamp shapes. */

extern float math_eval_cubic_hermite(float, float, float, float, float);

extern s32 FastTweenColor(s32, s32, f32);

typedef struct { float x, y, z, w; } MorphVec;

typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float f10;
    int i14;
    float f18;
    int i1C;
    int *p20;
    float *dst[2];
    unsigned char pad2C[0x10];
    MorphVec from[2];
    unsigned char pad5C[0x10];
    MorphVec to[2];
    s32 p8C;
    s32 p90;
} MorphObject;

/* Advances the morph progress by the step, clamps it to its range, lerps the two
   position pairs into the destination vectors and updates the second morph. */
void anim_step_morph(u8 *anim)
{
    MorphObject *morph = (MorphObject *)anim;
    float blend, inverse;
    int i;

    if (morph->i1C != 0) {
        if (morph->i14 == 1) {
            float next = morph->f10 + morph->f18;
            morph->f10 = next;
            morph->i1C = (next <= 1.0f) ? 1 : 0;
            morph->f10 = (next <= 1.0f) ? next : 1.0f;
        } else {
            float next = morph->f10 - morph->f18;
            morph->f10 = next;
            morph->i1C = (next >= 0.0f) ? 1 : 0;
            morph->f10 = (next >= 0.0f) ? next : 0.0f;
        }
        blend = math_eval_cubic_hermite(morph->f10, 0.0f, morph->f0, morph->f4, 1.0f);
        for (i = 0; i < 2; i++) {
            if (morph->dst[i] != 0) {
                inverse = 1.0f - blend;
                morph->dst[i][0] = inverse * morph->from[i].x + blend * morph->to[i].x;
                morph->dst[i][1] = inverse * morph->from[i].y + blend * morph->to[i].y;
                morph->dst[i][2] = inverse * morph->from[i].z + blend * morph->to[i].z;
                morph->dst[i][3] = inverse * morph->from[i].w + blend * morph->to[i].w;
            }
        }
        if (morph->p20 != 0) {
            morph->p20[0] = FastTweenColor(morph->p8C, morph->p90, math_eval_cubic_hermite(morph->f10, 0.0f, morph->f8, morph->fC, 1.0f));
        }
    }
}
