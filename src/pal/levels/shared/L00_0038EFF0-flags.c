#include "include_asm.h"

extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern int func_00282978(short *);
extern void func_0029F338(void *);

void func_PAL_L00_00390440(char *object)
{
    char *data = *(char **)(object + 0x68);
    float step = 0.062831864f;
    float numerator = func_00283CE0(*(int *)(data + 0x14) - *(short *)(data + 0x1C));
    float denominator = func_00283CE0(*(int *)(data + 0x14));
    *(float *)(object + 0x2C) = numerator * *(float *)(data + 0x18) / denominator;
    *(float *)(object + 0xF0) = func_00283B98(*(float *)(object + 0xF0), step);
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), step);
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), step);
    if (func_00282978((short *)(data + 0x1C))) func_0029F338(object);
    else {
        int half = *(int *)(data + 0x14) / 2;
        if (*(short *)(data + 0x1C) < half)
            object[0x23] = (*(short *)(data + 0x1C) * *(short *)(data + 0x1E)) / half;
    }
}
