#include "names.h"
/* func_PAL_L01_0039C7E8, the PAL copy of func_L01_003993C8: the same C, where the rate constant
   becomes 0.020000001f and both swing bounds take the 50 Hz scale, the 10.0f bound through a local. */
#include "common.h"

/* Sets the random swing band and derives its duration from the resulting speed. */
extern float g_wind_min_count SDATA(D_L01_001AF638);

extern float g_wind_max_count SDATA(D_L01_001AF63C);

extern float g_wind_x SDATA(D_L01_001B2EF0);

extern float g_wind_change_delay SDATA(D_L01_001B2F00);

extern float g_wind_y[] NOT_SDA;

extern int g_wind_particle_count MACRO_ADDR;

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

    if (g_wind_min_count >= 0.0f)
        lo = g_wind_min_count;
    if (g_wind_max_count >= 0.0f)
        hi = g_wind_max_count;

    {
        float k = s * 0.020000001f;
        float v[4];

        g_wind_x = func_00310580(-k, k);
        g_wind_y[0] = func_00310580(-k, k);
        g_wind_change_delay = func_00310580((x * 5.0f + 2.0f) * 0.16666667f,
                                       (y * 5.0f + 2.0f) * 0.16666667f);
        v[0] = k;
        v[1] = k;
        g_wind_particle_count = (int)((func_002E35D0((char *)&swing_vector) /
                            func_002E35A0(v)) *
                               (hi - lo) +
                           lo);
    }
}
