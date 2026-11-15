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
/* Picks a new random wind direction and a delay before the next change, and how many particles to spawn. */
void part_pick_random_wind_and_count(int weatherType)
{
    float windSpeed, changeDelayMin, minCount, maxCount;

    if (weatherType == 0) {
        windSpeed = 5.0f;
        changeDelayMin = 2.0f;
        maxCount = 8.0f;
        minCount = 4.0f;
    } else {
        windSpeed = 2.5f;
        changeDelayMin = 20.0f;
        maxCount = 3.0f;
        minCount = 2.0f;
    }

    if (D_L01_001AF638 >= 0.0f)
        minCount = D_L01_001AF638;
    if (D_L01_001AF63C >= 0.0f)
        maxCount = D_L01_001AF63C;

    {
        float k = windSpeed * 0.01666666753590107f;
        float v[4];

        D_L01_001B2EF0 = func_00310580(-k, k);
        D_L01_001B2EF4[0] = func_00310580(-k, k);
        D_L01_001B2F00 = func_00310580(changeDelayMin, 10.0f);
        v[0] = k;
        v[1] = k;
        D_L01_001B2F04 = (int)((func_002E35D0((char *)&swing_vector) /
                            func_002E35A0(v)) *
                               (maxCount - minCount) +
                           minCount);
    }
}
