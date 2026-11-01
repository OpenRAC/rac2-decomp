#include "include_asm.h"

extern float D_L00_001B0464 __attribute__((sda));
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00326EC0(void *);
extern void func_PAL_003287E0(void *);
extern void func_PAL_00328B28(void *);

void func_PAL_00328538(char *object)
{
    float vector[4];
    char *data = *(char **)(object + 0x68);
    float speed = *(float *)(data + 0x30);
    if (speed != 0.0f && *(int *)(data + 0x34)) {
        float magnitude;
        float step;
        *(float *)(data + 0x18) += speed * (0.010000001f);
        magnitude = func_00282C48(*(float *)(data + 0x18));
        step = D_L00_001B0464;
        if (step * (0.020000001f) < magnitude)
            *(float *)(data + 0x18) = step * *(float *)(data + 0x30) * (0.020000001f);
    } else {
        *(float *)(data + 0x18) *= 0.85f;
    }
    *(float *)(object + 0x48) = *(float *)(data + 0x18) * 25.0f;
    if (*(int *)(data + 0x34) == 0)
        *(float *)(object + 0x48) += *(float *)(data + 0x38) * 2.0f;
    func_00282F20(vector, object + 0xC0, *(float *)(data + 0x18));
    func_00282CC0(object + 0x10, object + 0x10, vector);
    func_00326EC0(object);
    func_PAL_003287E0(object);
    func_PAL_00328B28(object);
}
