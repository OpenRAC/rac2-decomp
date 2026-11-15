#include "common.h"

/* func_002C5120 needs -G8 (the side pull is a $gp float) and -g (the line
   label before the division gives retail's two padding nops). */

/* Copy the xyz components and clear the fourth word. Adapted from RAC1. */
static __inline__ void particle_copy_xyz(float *dst, float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    *(int *)&dst[3] = 0;
}

typedef struct {
    float f[4];
} Vec16_C5120;

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00300190(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern char D_0018A0E0[];
extern float D_001AA3C0 __attribute__((sda));

/* Move a particle while tweening its size and alpha (as func_002C23B8). When
   its offset to the owner at q+24 is at most 2 on x and y, it is moved along
   the cross product of that offset with D_0018A0E0, and its velocity is set
   along the offset (length 0.03 when within 0.5, else its current speed) and
   raised by 0.02 on z. */
void func_002C5120(char *p)
{
    char *q = p + 32;
    Vec16_C5120 v;
    float delta[4], side[4];
    float *vel;
    float t;
    int alpha;

    p[8] += (unsigned char)q[10];
    if (*(short *)(q + 8) - *(short *)(p + 10) < 6) {
        t = (float)(*(short *)(q + 8) - *(short *)(p + 10)) * 0.2f;
        *(float *)(p + 12) = *(float *)(q + 4) +
            ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)(q + 4)) * t;
        {
            int c2 = (unsigned char)q[11] >> 1;
            int c = (unsigned char)q[11];
            alpha = FloatToInt((float)c + (float)(c2 - c) * t);
        }
    } else {
        t = IntToFloat(*(short *)(q + 8) - 6);
        t = (float)*(short *)(p + 10) / t;
        *(float *)(p + 12) = *(float *)q +
            ((*(float *)q + *(float *)(q + 4)) * 0.5f - *(float *)q) * t;
        alpha = FloatToInt((float)((unsigned char)q[11] >> 1) * t);
    }
    *(int *)(p + 4) = (alpha << 24) | (*(int *)(p + 4) & 0xffffff);
    particle_copy_xyz(v.f, (float *)(q + 12));
    FastVecAdd(p + 16, p + 16, (char *)&v);
    func_00300190(p + 16, p + 16);
    if (*(char **)(q + 24) != 0) {
        FastVecSub(delta, *(char **)(q + 24) + 16, p + 16);
        if (delta[0] <= 2.0f && delta[1] <= 2.0f) {
            FastVecCross(side, delta, D_0018A0E0);
            vec_scale_to_length(side, side, D_001AA3C0);
            FastVecAdd(p + 16, p + 16, side);
            if (delta[0] <= 0.5f && delta[1] <= 0.5f)
                vec_scale_to_length(v.f, delta, 0.03f);
            else
                vec_scale_to_length(v.f, delta, FastVecLength(v.f));
            v.f[2] += 0.02f;
            vel = (float *)(q + 12);
            vel[0] = v.f[0];
            vel[1] = v.f[1];
            vel[2] = v.f[2];
        }
    }
    if (FastDecTimer((short *)(p + 10)))
        func_002B9180(p);
}
