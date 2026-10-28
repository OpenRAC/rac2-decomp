#include "common.h"
/* EE argument-bank order: owner/index/point/force in a0..a3, range/height in f12/f13. */
extern int func_002B3BA8(void *, int, float, float, void *, int);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_002A7878(float, float), func_00282EB0(const void *, const void *);
extern void func_002ACB48(float *, float), func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void *func_L11_004417E8(void *);
extern unsigned char D_00189EA0[] NOT_SDA;
extern float D_L11_001B0590[] SDATA(D_L11_001B0590);
extern float D_L11_001B0558[] SDATA(D_L11_001B0558);

int func_L11_003F3258(char *object, float *from, float *to)
{
    char *state = *(char **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float radial[4] __attribute__((aligned(16)));
    float radius, factor, height;
    int result;
    *(int *)(state + 0x258) = func_002B3BA8(object, *(int *)(state + 0x25c), 200.0f, 200.0f, from, 0);
    if (*(int *)(state + 0x258) == 1) qcopy(to, state + 0x80);
    else qcopy(to, D_00189EA0);
    factor = 0.2f;
    /* The subtraction writes all 16 bytes, preserving the initialized input W. */
    func_00282CF0(delta, to, from);
    result = 0;
    radius = D_L11_001B0590[0] + func_002A7878(-D_L11_001B0590[1], D_L11_001B0590[1]);
    if (radius * radius < func_00282EB0(from, to)) {
        func_002ACB48(delta, D_L11_001B0590[2]);
        func_00282F20(delta, delta, radius);
        func_00282CC0(to, from, delta);
    } else {
        result = 1;
        factor = 0.5f;
    }
    height = to[2];
    func_00282CF0(radial, to, func_L11_004417E8(*(void **)(object + 0xb8)));
    radial[2] = 0.0f;
    func_00282F20(radial, radial, D_L11_001B0558[0] - factor);
    func_00282CC0(to, func_L11_004417E8(*(void **)(object + 0xb8)), radial);
    to[2] = height;
    return result;
}
