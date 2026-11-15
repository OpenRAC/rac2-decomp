#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern short D_L05_00221D50;
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int func_00282948(char *);
extern float func_00283B98(float, float);
extern void func_L04_0040DCA8(char *, int, int, int, float, float, float, float);

/* Draws glowing sprites at the back of the object. Their colour changes while a timer runs. */
void func_L05_00418E90(char *object)
{
    char *vars = *(char **)(object + 0x68);
    TI128 offset;
    char *source;
    int colorA;
    int colorB;

    *(float *)(vars + 0x60) = FastAddRotations(*(float *)(vars + 0x60), 0.01f);
    *(float *)(vars + 0x64) = FastAddRotations(*(float *)(vars + 0x64), -0.007f);
    *(float *)(vars + 0x68) = FastAddRotations(*(float *)(vars + 0x68), 0.007f);
    *(float *)(vars + 0x6C) = FastAddRotations(*(float *)(vars + 0x6C), *(float *)(vars + 0x38) * 0.02f);
    source = object + 0xE0;
    qcopy(&offset, source);
    colorA = 0;
    vec_scale_to_length((char *)&offset, (char *)&offset, 0.05f);
    colorB = 0;
    FastVecAdd((char *)&offset, object + 0x10, (char *)&offset);
    if (D_L05_00221D50 != 0) {
        *(int *)(vars + 0xA0) = 7;
    } else {
        colorA = 0x0FC85A5A;
        colorB = 0x28FF3232;
    }
    if (FastFloatHelperD(vars + 0xA0) == 0) {
        int step = *(int *)(vars + 0xA0) * 5;
        int lowBits = (0x6E - step) | 0x1E000000;

        colorA = ((step + 0x6E) << 16) | lowBits;
        colorB = ((step + 0x96) << 16) | lowBits;
    }
    DrawBillboardSprite_L04((char *)&offset, *(int *)(vars + 0x58), colorA, 1, 0.27f, 0.35f, *(float *)(vars + 0x60), 0.0f);
    DrawBillboardSprite_L04((char *)&offset, *(int *)(vars + 0x58), colorA, 1, 0.27f, 0.35f, *(float *)(vars + 0x64), 0.0f);
    DrawBillboardSprite_L04((char *)&offset, 0x36, colorB, 1, 0.22f, 0.35f, *(float *)(vars + 0x68), 0.0f);
}
