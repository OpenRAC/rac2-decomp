#include "include_asm.h"
#include "names.h"

extern int math_fast_float_d(void *);

extern int FastDecTimer(void *);

extern float IntToFloat(int);

extern int FloatToInt(float value);

extern void FastVecAdd(void *dst, void *left, void *right);

extern void vec_transform_or_copy(void *dst, void *src);

extern void part_kill(void *object);

/* vcopy: copies an xyz vector and clears the w word (RAC1's vcopy_273090). */
static __inline__ void vcopy_L00_0033EE38(float *d, float *s)
{
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    *(int *)&d[3] = 0;
}

/* Particle update (the RAC1 update_moving_size_alpha_tween_particle family): ramps the size at
   +0x0C and the alpha byte of +0x04 over the particle's life, moves it by its velocity and
   kills it when it leaves the 2..1021 world box or its timer runs out. The division sits on
   its own source line: this -g unit's line label gives the two nops retail has before div.s. */
void UpdateMovingSizeAlphaTweenParticle(char *m)
{
    char *v = m + 0x20;
    float f4;
    float a[4] __attribute__((aligned(16)));
    int al;

    m[8] += v[0xA];
    if (math_fast_float_d(m + 0x38)) {
        if (*(short *)(v + 8) - *(short *)(m + 0xA) < *(short *)(v + 0x1E)) {
            int c;
            int c2;
            f4 = (float)(*(short *)(v + 8) - *(short *)(m + 0xA)) * 0.2f;
            *(float *)(m + 0xC) = *(float *)(v + 4) + ((*(float *)(m + 0x20) + *(float *)(v + 4)) * 0.5f - *(float *)(v + 4)) * f4;
            c2 = (unsigned char)v[0xB] >> 1;
            c = (unsigned char)v[0xB];
            al = FloatToInt((float)c + (float)(c2 - c) * f4);
        } else {
            f4 = IntToFloat(*(short *)(v + 8) - 6);
            f4 = (float)*(short *)(m + 0xA) / f4;
            *(float *)(m + 0xC) = *(float *)(m + 0x20) + ((*(float *)(m + 0x20) + *(float *)(v + 4)) * 0.5f - *(float *)(m + 0x20)) * f4;
            al = FloatToInt((float)((unsigned char)v[0xB] >> 1) * f4);
        }
        *(int *)(m + 4) = (al << 24) | (*(int *)(m + 4) & 0xFFFFFF);
        vcopy_L00_0033EE38(a, (float *)(v + 0xC));
        FastVecAdd(m + 0x10, m + 0x10, a);
        if (*(float *)(m + 0x10) < 2.0f || *(float *)(m + 0x10) > 1021.0f ||
            *(float *)(m + 0x14) < 2.0f || *(float *)(m + 0x14) > 1021.0f ||
            *(float *)(m + 0x18) < 2.0f || *(float *)(m + 0x18) > 1021.0f ||
            FastDecTimer(m + 0xA)) {
            part_kill(m);
            return;
        }
    }
    if (*(float *)(m + 0x1C) != 0.0f) {
        if (*(float *)(m + 0x1C) == 2.0f)
            vec_transform_or_copy(m + 0x10, m + 0x10);
        *(float *)(m + 0x1C) = 2.0f;
    }
}
