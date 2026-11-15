#include "names.h"
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
extern void func_00282CF0(char *, char *, char *);

extern u8 D_L17_001B0CBB;
extern u8 *D_L17_001AFB5C;
extern f32 D_L17_001B0CD8 __attribute__((sda));
extern f32 D_L17_001B0CDC __attribute__((sda));
extern f32 D_L17_001B0CE0 __attribute__((sda));
extern int D_L17_001B0CE4 __attribute__((sda));
extern f32 D_L17_001B0CE8 __attribute__((sda));
extern void func_002A7470(void *, int, int, int);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);

/* Pulls the creature toward a nearby object while it shrinks and turns. Returns 1 when it
   is done and can be removed. */
int func_L17_003E48E0(u8 *object) {
    float delta[4];
    u8 *data = *(u8 **)(object + 0x68);
    float heading, length, step, ratio, angle, minimum, scale, decay;
    u8 *target;
    int result;
    if (object[0x43] != D_L17_001B0CBB)
        StartAnimationBlended(object, D_L17_001B0CBB, 0, 10);
    if (D_L17_001AFB5C) {
        heading = FastMatrixHelperA(*(float *)(object + 0x10) - *(float *)(D_L17_001AFB5C + 0x10),
                               *(float *)(object + 0x14) - *(float *)(D_L17_001AFB5C + 0x14));
        angle = FastAddRotations(*(float *)(object + 0xF8),
            fast_subtract_rotations(heading, *(float *)(object + 0xF8)) * 0.1f);
        target = D_L17_001AFB5C + 0x10;
        *(float *)(object + 0xF8) = angle;
        FastVecSub((char *)delta, (char *)target, (char *)object + 0x10);
        delta[2] -= *(float *)(data + 0x330);
        length = FastVecLength(delta);
        if (length != 0.0f) {
            float fraction;
            step = D_L17_001B0CD8 * 0.01666666753590107f;
            if (length < step)
                step = length;
            fraction = step / length;
            FastVecScale(delta, delta, fraction);
            FastVecAdd(object + 0x10, object + 0x10, delta);
            delta[0] = FastSinOrCosA(FastAddRotations(heading, 1.5707964897155762f)) * 0.01666666753590107f * D_L17_001B0CDC;
            delta[1] = FastSinOrCosB(FastAddRotations(heading, 1.5707964897155762f)) * 0.01666666753590107f * D_L17_001B0CDC;
            delta[2] = 0.0f;
            FastVecAdd(object + 0x10, object + 0x10, delta);
        }
        decay = IntToFloat(D_L17_001B0CE4);
        minimum = D_L17_001B0CE8;
        *(float *)(object + 0x2C) -= *(float *)(data + 0x340) / decay;
        if (*(float *)(object + 0x2C) < minimum)
            *(float *)(object + 0x2C) = minimum;
        ratio = *(float *)(object + 0x2C) / *(float *)(data + 0x340);
        if (ratio > 1.0f)
            ratio = 1.0f;
        scale = D_L17_001B0CE0 + (*(float *)(data + 0x30) - D_L17_001B0CE0) * ratio;
        {
            u8 *hero = D_L17_001AFB5C;
            *(float *)(data + 0x330) = scale;
            if (!hero || hero[0x20] == 0x5A || (s8)hero[0x20] < 0)
                result = 1;
            else
                result = 0;
            goto done;
        }
    }
    result = 1;
done:
    return result;
}
