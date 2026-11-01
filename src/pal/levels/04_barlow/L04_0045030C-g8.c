#include "include_asm.h"

#include "common.h"
typedef int BarlowEffectQuad __attribute__((mode(TI)));
typedef union { BarlowEffectQuad q; float f[4]; } BarlowEffectVector;
extern void func_00282D30(void *, void *, float);
extern char *func_L00_0033E220(void *, void *, unsigned int, int, int, int, int, int, float, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, unsigned char, void *);
extern void func_PAL_L03_002EE460(void *, void *, void *, void *, void *, int, unsigned char);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(void *);
extern float D_L04_001B1830[] SDATA(D_L04_001B1830);
extern float D_L04_001B1828[] SDATA(D_L04_001B1828);
extern float D_L04_001B1820[] SDATA(D_L04_001B1820);
extern int D_L04_001B1850 SDATA(D_L04_001B1850);

void func_PAL_L04_00451600(unsigned char *object)
{
    BarlowEffectVector velocity, lower, upper, min_offset, max_offset;
    char *state = *(char **)(object + 0x68);
    velocity.q = 0;
    velocity.f[0] = -21.5f;
    switch (object[0x20]) {
    case 0:
        func_00282D30(&velocity, &velocity, *(float *)(object + 0x2c));
        *(char **)(state + 4) = func_L00_0033E220(&velocity, object, 0x40208080, -1, 1, -1, 0, -1,
                                                *(float *)(object + 0x2c) * 5250000.0f, *(float *)(object + 0x2c) * 15.0f);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002A9640(object, 0x4010000, 0) && !*(int *)state) func_002A7750(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(object, D_L04_001B1830, D_L04_001B1828, D_L04_001B1820, 65535, 0, D_L04_001B1850, 8, 65535, 255, 0);
        min_offset.q = 0;
        max_offset.q = 0;
        lower.q = 0;
        upper.q = 0;
        upper.f[0] = lower.f[0] = -15.0f;
        min_offset.f[0] = -10.0f;
        min_offset.f[2] = min_offset.f[1] = -4.0f;
        max_offset.f[0] = -3.0f;
        max_offset.f[1] = 5.0f;
        max_offset.f[2] = 4.0f;
        func_PAL_L03_002EE460(object, &lower, &upper, &min_offset, &max_offset, 45, 0);
        func_L00_00324F18(object, &velocity, -21.5f, 0.0f, 0.0f);
        func_PAL_L00_003FB330(object + 0x10, 0, 25, 20, 20, 20, 45, 1,
                     *(float *)(object + 0x2c) * 5.0f, 20.0f, 1, 1, 0, 0);
        func_0029F338(object);
        break;
    }
}
