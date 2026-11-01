#include "include_asm.h"

#include "common.h"
extern float func_00282E20(char *);
extern float func_00283248(float, float);
extern void func_00282D30(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_001290E0(int *, int *);
extern unsigned char D_00189E20_1[];

void func_PAL_L00_002B4230(void)
{
    char *p = (char *)D_00189E20_1;
    float distance;
    float angle;
    float value;
    float vector[4] __attribute__((aligned(16)));

    if (*(short *)(p + 0x34E) == 0)
        return;
    if (!(*(float *)(p + 0x31C) < 0.15f))
        return;
    if (!(0.0f < *(float *)(p + 0x118)))
        return;
    if (*(unsigned char *)(p + 0x287) == 0)
        return;
    if (!(0.0f < *(float *)(p + 0x238)))
        return;
    distance = func_00282E20(p + 0x230);
    angle = func_00283248(*(float *)(p + 0x238), distance);
    if (!(angle >= 0.8726646900177002f))
        return;
    qcopy(vector, p + 0x230);
    vector[2] = 0.0f;
    func_001290E0((int *)vector, (int *)vector);
    value = -*(float *)(p + 0xF0) * vector[0] - *(float *)(p + 0xF4) * vector[1];
    if (value > 0.0f) {
        func_00282D30((char *)vector, (char *)vector, value);
        func_00282CC0(p + 0xF0, p + 0xF0, (char *)vector);
        *(float *)(p + 0xF8) -= 0.0432f;
    }
}


