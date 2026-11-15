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
void func_002C5120(char *particle)
{
    char *state = particle + 32;
    Vec16_C5120 velocity;
    float delta[4], side[4];
    float *velocityOut;
    float progress;
    int alpha;

    particle[8] += (unsigned char)state[10];
    if (*(short *)(state + 8) - *(short *)(particle + 10) < 6) {
        progress = (float)(*(short *)(state + 8) - *(short *)(particle + 10)) * 0.2f;
        *(float *)(particle + 12) = *(float *)(state + 4) +
            ((*(float *)state + *(float *)(state + 4)) * 0.5f - *(float *)(state + 4)) * progress;
        {
            int c2 = (unsigned char)state[11] >> 1;
            int c = (unsigned char)state[11];
            alpha = FloatToInt((float)c + (float)(c2 - c) * progress);
        }
    } else {
        progress = IntToFloat(*(short *)(state + 8) - 6);
        progress = (float)*(short *)(particle + 10) / progress;
        *(float *)(particle + 12) = *(float *)state +
            ((*(float *)state + *(float *)(state + 4)) * 0.5f - *(float *)state) * progress;
        alpha = FloatToInt((float)((unsigned char)state[11] >> 1) * progress);
    }
    *(int *)(particle + 4) = (alpha << 24) | (*(int *)(particle + 4) & 0xffffff);
    particle_copy_xyz(velocity.f, (float *)(state + 12));
    FastVecAdd(particle + 16, particle + 16, (char *)&velocity);
    TransformVectorOrCopy(particle + 16, particle + 16);
    if (*(char **)(state + 24) != 0) {
        FastVecSub(delta, *(char **)(state + 24) + 16, particle + 16);
        if (delta[0] <= 2.0f && delta[1] <= 2.0f) {
            FastVecCross(side, delta, D_0018A0E0);
            vec_scale_to_length(side, side, D_001AA3C0);
            FastVecAdd(particle + 16, particle + 16, side);
            if (delta[0] <= 0.5f && delta[1] <= 0.5f)
                vec_scale_to_length(velocity.f, delta, 0.03f);
            else
                vec_scale_to_length(velocity.f, delta, FastVecLength(velocity.f));
            velocity.f[2] += 0.02f;
            velocityOut = (float *)(state + 12);
            velocityOut[0] = velocity.f[0];
            velocityOut[1] = velocity.f[1];
            velocityOut[2] = velocity.f[2];
        }
    }
    if (FastDecTimer((short *)(particle + 10)))
        KillParticle(particle);
}
