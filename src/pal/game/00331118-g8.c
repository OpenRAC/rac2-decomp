#include "include_asm.h"

extern float D_001B284C;
extern float ref_L00_0032FEA8_00 __attribute__((sda));
extern int D_001B2850;
extern float D_001B2854;
extern float D_001B09A0 __attribute__((sda));
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032FFD8(void *);
extern void func_PAL_00331CF0(void *);
extern void func_PAL_00332038(void *);

void func_PAL_00331A48(char *object)
{
    char *data = *(char **)(object + 0x68);
    float value;
    int flag;
    char buffer[16];

    if (D_001B284C != 0.0f && D_001B2850 != 0) {
        value = *(float *)(data + 0x58) + D_001B284C * (0.010000001f);
        *(float *)(data + 0x58) = value;
        if (func_00282C48(value) > D_001B09A0 * (0.020000001f))
            *(float *)(data + 0x58) = D_001B09A0 * ref_L00_0032FEA8_00 * (0.020000001f);
    } else {
        *(float *)(data + 0x58) = *(float *)(data + 0x58) * 0.85f;
    }

    flag = D_001B2850;
    value = *(float *)(data + 0x58) * 25.0f;
    *(float *)(object + 0x48) = value;
    if (flag == 0)
        *(float *)(object + 0x48) = value + (D_001B2854 + D_001B2854);

    func_00282F20(buffer, object + 0xC0, *(float *)(data + 0x58));
    func_00282CC0(object + 0x10, object + 0x10, buffer);
    func_0032FFD8(object);
    func_PAL_00331CF0(object);
    func_PAL_00332038(object);
}
