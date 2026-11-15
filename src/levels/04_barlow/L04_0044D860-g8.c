#include "names.h"
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
extern void func_00282CF0(char *, char *, char *);

extern u8 D_L04_001B1883;
extern u8 *D_L04_001AF90C;
extern f32 D_L04_001B188C __attribute__((sda));
extern f32 D_L04_001B1890 __attribute__((sda));
extern f32 D_L04_001B1894 __attribute__((sda));
extern int D_L04_001B1898 __attribute__((sda));
extern f32 D_L04_001B189C __attribute__((sda));
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

/* Pulls the object toward the hero while it shrinks. Returns 1 when the hero is gone or can no longer be followed. */
int func_L04_0044D860(u8 *object) {
    float delta[4];
    u8 *data = *(u8 **)(object + 0x68);
    float heading, length, step, ratio, angle, minimum, scale, decay;
    u8 *target;
    int result;
    if (object[0x43] != D_L04_001B1883)
        StartAnimationBlended(object, D_L04_001B1883, 0, 10);
    if (D_L04_001AF90C) {
        heading = FastMatrixHelperA(*(float *)(object + 0x10) - *(float *)(D_L04_001AF90C + 0x10),
                               *(float *)(object + 0x14) - *(float *)(D_L04_001AF90C + 0x14));
        angle = FastAddRotations(*(float *)(object + 0xF8),
            fast_subtract_rotations(heading, *(float *)(object + 0xF8)) * 0.1f);
        target = D_L04_001AF90C + 0x10;
        *(float *)(object + 0xF8) = angle;
        FastVecSub((char *)delta, (char *)target, (char *)object + 0x10);
        delta[2] -= *(float *)(data + 0x220);
        length = FastVecLength(delta);
        if (length != 0.0f) {
            float fraction;
            step = D_L04_001B188C * 0.01666666753590107f;
            if (length < step)
                step = length;
            fraction = step / length;
            FastVecScale(delta, delta, fraction);
            FastVecAdd(object + 0x10, object + 0x10, delta);
            delta[0] = FastSinOrCosA(FastAddRotations(heading, 1.5707964897155762f)) * 0.01666666753590107f * D_L04_001B1890;
            delta[1] = FastSinOrCosB(FastAddRotations(heading, 1.5707964897155762f)) * 0.01666666753590107f * D_L04_001B1890;
            delta[2] = 0.0f;
            FastVecAdd(object + 0x10, object + 0x10, delta);
        }
        decay = IntToFloat(D_L04_001B1898);
        minimum = D_L04_001B189C;
        *(float *)(object + 0x2C) -= *(float *)(data + 0x230) / decay;
        if (*(float *)(object + 0x2C) < minimum)
            *(float *)(object + 0x2C) = minimum;
        ratio = *(float *)(object + 0x2C) / *(float *)(data + 0x230);
        if (ratio > 1.0f)
            ratio = 1.0f;
        scale = D_L04_001B1894 + (*(float *)(data + 0x30) - D_L04_001B1894) * ratio;
        {
            u8 *hero = D_L04_001AF90C;
            *(float *)(data + 0x220) = scale;
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
