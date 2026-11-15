#include "include_asm.h"
#include "names.h"

extern float IntToFloat(int);
extern float FastAddRotations(float, float);
extern int FastDecTimer(short *);
extern void moby_mark_spawned(void *);

void func_PAL_L00_00390440(char *object)
{
    char *data = *(char **)(object + 0x68);
    float step = 0.062831864f;
    float numerator = IntToFloat(*(int *)(data + 0x14) - *(short *)(data + 0x1C));
    float denominator = IntToFloat(*(int *)(data + 0x14));
    *(float *)(object + 0x2C) = numerator * *(float *)(data + 0x18) / denominator;
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), step);
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), step);
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), step);
    if (FastDecTimer((short *)(data + 0x1C))) moby_mark_spawned(object);
    else {
        int half = *(int *)(data + 0x14) / 2;
        if (*(short *)(data + 0x1C) < half)
            object[0x23] = (*(short *)(data + 0x1C) * *(short *)(data + 0x1E)) / half;
    }
}
