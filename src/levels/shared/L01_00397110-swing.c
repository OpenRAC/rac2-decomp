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
/* Picks a new random wind direction and a delay before the next change, and how many particles to spawn. */
void part_pick_random_wind_and_count(int weather_type)
{
    float wind_speed, change_delay_min, min_count, max_count;

    if (weather_type == 0) {
        wind_speed = 5.0f;
        change_delay_min = 2.0f;
        max_count = 8.0f;
        min_count = 4.0f;
    } else {
        wind_speed = 2.5f;
        change_delay_min = 20.0f;
        max_count = 3.0f;
        min_count = 2.0f;
    }

    if (g_wind_min_count >= 0.0f)
        min_count = g_wind_min_count;
    if (g_wind_max_count >= 0.0f)
        max_count = g_wind_max_count;

    {
        float k = wind_speed * 0.01666666753590107f;
        float v[4];

        g_wind_x = func_00310580(-k, k);
        g_wind_y[0] = func_00310580(-k, k);
        g_wind_change_delay = func_00310580(change_delay_min, 10.0f);
        v[0] = k;
        v[1] = k;
        g_wind_particle_count = (int)((func_002E35D0((char *)&swing_vector) /
                            func_002E35A0(v)) *
                               (max_count - min_count) +
                           min_count);
    }
}
