#include "include_asm.h"

extern float D_L02_001B1030 __attribute__((sda));
extern int D_L02_001AD410;

void func_PAL_L02_003F9D50(void) {
    int v0 = D_L02_001AD410;
    float *p = (float *)((char *)v0 + 0x74);
    float f;

    f = p[0] + D_L02_001B1030 * 0.020000001f;
    p[0] = f;
    if (f > 1.0f)
        p[0] = f - 1.0f;
}
