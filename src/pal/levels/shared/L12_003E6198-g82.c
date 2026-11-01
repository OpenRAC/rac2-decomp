#include "include_asm.h"

#include "common.h"
extern char *D_L12_001FEAC0[];
extern float D_L12_001B0B14 SDATA(D_L12_001B0B14);
extern float D_L12_001B0A54 SDATA(D_L12_001B0A54);
extern char D_L12_001B0B18[];
extern int func_PAL_L01_00323068(void *, void *);
extern float func_00283248(float, float);
extern void func_002AA800(void *, float, float, int);
extern float func_002A89A8(float, void *, int);
extern double func_001234F0(float);
extern void func_0026FEB8(const char *, ...);

void func_PAL_L12_003E63A0(char *object)
{
    char *state = *(char **)(object + 0x68);
    float oldHeight = *(float *)(object + 0x18);
    char *path = D_L12_001FEAC0[*(int *)(state + 0x158)];
    int flags;
    float ground;
    float probeRadius;
    float targetHeight;
    char *position;

    *(int *)(state + 0x218) = 0;
    flags = func_PAL_L01_00323068(object, path + ((*(int *)(state + 0x264) << 4) + 0x10));
    if (*(u8 *)(object + 0x95) == 6) {
        char *target = *(char **)(state + 0x270);
        float angle = func_00283248(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                   *(float *)(target + 0x14) - *(float *)(object + 0x14));
        func_002AA800(object + 0xF8, angle, 7.2000003f, 0);
    }
    probeRadius = 0.5f;
    position = object + 0x10;
    ground = func_002A89A8(probeRadius, position, 0);
    if (flags & 0x20) {
        if (*(int *)(state + 0x248) == 0 || *(float *)(object + 0x18) - ground > D_L12_001B0B14) {
            *(float *)(object + 0x18) = oldHeight;
        } else if (*(float *)(object + 0x18) < *(float *)(state + 0x2A8)) {
            *(float *)(object + 0x18) = *(float *)(state + 0x2A8);
        } else {
            char *sink = D_L12_001B0B18;
            float floor = func_002A89A8(probeRadius, position, 0);
            double heightDifference = func_001234F0(*(float *)(object + 0x18) - floor);
            func_0026FEB8(sink, heightDifference, *(short *)(object + 0xB2));
        }
    }
    targetHeight = *(float *)(path + (*(int *)(state + 0x264) << 4) + 0x18);
    if (*(float *)(object + 0x18) < targetHeight) {
        targetHeight -= *(float *)(object + 0x18);
        if (targetHeight > 0.8f) {
            *(float *)(object + 0x18) += D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(object + 0x18) < ground)
                *(float *)(object + 0x18) = ground;
        }
    }
    targetHeight = *(float *)(path + (*(int *)(state + 0x264) << 4) + 0x18);
    if (*(float *)(object + 0x18) > targetHeight) {
        targetHeight -= *(float *)(object + 0x18);
        if (targetHeight < -0.8f) {
            *(float *)(object + 0x18) -= D_L12_001B0A54 * 0.020000001f;
            if (*(float *)(object + 0x18) < ground)
                *(float *)(object + 0x18) = ground;
        }
    }
    if (flags & 0x80)
        *(int *)(state + 0x16C) = 0;
}
