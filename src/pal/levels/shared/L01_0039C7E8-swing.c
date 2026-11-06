/* func_PAL_L01_0039C7E8, the PAL copy of func_L01_003993C8: the same C, where the rate constant
   becomes 0.020000001f and both swing bounds take the 50 Hz scale, the 10.0f bound through a local. */
#include "common.h"

/* Sets the random swing band and derives its duration from the resulting speed. */
extern float D_L01_001AF638 SDATA(D_L01_001AF638);

extern float D_L01_001AF63C SDATA(D_L01_001AF63C);

extern float D_L01_001B2EF0 SDATA(D_L01_001B2EF0);

extern float D_L01_001B2F00 SDATA(D_L01_001B2F00);

extern float D_L01_001B2EF4[] NOT_SDA;

extern int D_L01_001B2F04 MACRO_ADDR;

extern float func_00310580(float, float);

extern float func_002E35D0(char *);

extern float func_002E35A0(float *);

extern float swing_vector __asm__("D_L01_001B2EF0") MACRO_ADDR;
void func_PAL_L01_0039C7E8(int a0)
{
    float s, x, y, lo, hi;

    if (a0 == 0) {
        s = 5.0f;
        y = 10.0f;
        x = 2.0f;
        hi = 8.0f;
        lo = 4.0f;
    } else {
        s = 2.5f;
        y = 10.0f;
        x = 20.0f;
        hi = 3.0f;
        lo = 2.0f;
    }

    if (D_L01_001AF638 >= 0.0f)
        lo = D_L01_001AF638;
    if (D_L01_001AF63C >= 0.0f)
        hi = D_L01_001AF63C;

    {
        float k = s * 0.020000001f;
        float v[4];

        D_L01_001B2EF0 = func_00310580(-k, k);
        D_L01_001B2EF4[0] = func_00310580(-k, k);
        D_L01_001B2F00 = func_00310580((x * 5.0f + 2.0f) * 0.16666667f,
                                       (y * 5.0f + 2.0f) * 0.16666667f);
        v[0] = k;
        v[1] = k;
        D_L01_001B2F04 = (int)((func_002E35D0((char *)&swing_vector) /
                            func_002E35A0(v)) *
                               (hi - lo) +
                           lo);
    }
}
