#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
extern char D_L00_00189F00[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern char D_002351A0[];
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00282948(int *);

void func_0032B7D0(char *owner)
{
    float delta[4];
    int i;
    char *records = D_002351A0;
    char *center = D_L00_00189F00;
    for (i = 0; i < 12; i++) {
        char *p = records + i * 0xB0;
        float ratio;
        if (*(char **)(p + 0x9C) != owner) continue;
        FastVecSub(delta, (float *)(p + 0x40), p + 0x20);
        *(EffectQuad *)(p + 0x20) = *(EffectQuad *)center;
        FastVecAdd(p + 0x40, p + 0x20, delta);
        if (*(int *)(p + 0xA0)) {
            *(float *)(p + 0x50) = FastAddRotations(*(float *)(p + 0x50), *(float *)(p + 0x5C) * 100.0f);
            *(float *)(p + 0x54) = FastAddRotations(*(float *)(p + 0x54), *(float *)(p + 0x60) * 100.0f);
            *(float *)(p + 0x58) = FastAddRotations(*(float *)(p + 0x58), *(float *)(p + 0x64) * 100.0f);
            *(float *)(p + 0x74) = FastAddRotations(*(float *)(p + 0x74), *(float *)(p + 0x80) * 100.0f);
            *(float *)(p + 0x78) = FastAddRotations(*(float *)(p + 0x78), *(float *)(p + 0x84) * 100.0f);
            *(float *)(p + 0x7C) = FastAddRotations(*(float *)(p + 0x7C), *(float *)(p + 0x88) * 100.0f);
        } else {
            *(float *)(p + 0x50) = FastAddRotations(*(float *)(p + 0x50), *(float *)(p + 0x5C) * 50.0f);
            *(float *)(p + 0x54) = FastAddRotations(*(float *)(p + 0x54), *(float *)(p + 0x60) * 50.0f);
            *(float *)(p + 0x58) = FastAddRotations(*(float *)(p + 0x58), *(float *)(p + 0x64) * 50.0f);
            *(float *)(p + 0x74) = FastAddRotations(*(float *)(p + 0x74), *(float *)(p + 0x80) * 50.0f);
            *(float *)(p + 0x78) = FastAddRotations(*(float *)(p + 0x78), *(float *)(p + 0x84) * 50.0f);
            *(float *)(p + 0x7C) = FastAddRotations(*(float *)(p + 0x7C), *(float *)(p + 0x88) * 50.0f);
        }
        *(float *)(p + 0) = func_00283180(*(float *)(p + 0x50)) * *(float *)(p + 0x68);
        *(float *)(p + 4) = func_00283198(*(float *)(p + 0x54)) * *(float *)(p + 0x6C);
        *(float *)(p + 8) = -func_00283198(*(float *)(p + 0x58)) * *(float *)(p + 0x70);
        *(float *)(p + 0x10) = func_00283180(*(float *)(p + 0x74)) * *(float *)(p + 0x8C);
        *(float *)(p + 0x14) = func_00283198(*(float *)(p + 0x78)) * *(float *)(p + 0x90);
        *(float *)(p + 0x18) = -func_00283198(*(float *)(p + 0x7C)) * *(float *)(p + 0x94);
        ratio = IntToFloat(*(int *)(p + 0xA0));
        ratio /= IntToFloat(*(int *)(p + 0xA4));
        lerp_vector(p + 0x30, p + 0x20, p + 0x40, 1.0f - ratio);
        if (func_00282948((int *)(p + 0xA0))) {
            if (*(int *)(p + 0xA8) == 0) *(int *)(p + 0xA8) = 1;
            if (func_00282948((int *)(p + 0x98))) *(int *)(p + 0x9C) = 0;
        }
    }
}
