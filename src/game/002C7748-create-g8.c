#include "common.h"
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern unsigned char *D_001F26C0[];
extern float D_001AA3CC __attribute__((sda));
extern float D_001AA3D0 __attribute__((sda));
extern float D_001AA3D4 __attribute__((sda));
char *func_002C7748(char *pos, char *velocity, int life)
{
    char *state;
    char *p = func_002B9030(0x60);
    float scale;
    if (p) {
        state = p + 32;
        scale = 2.0f;
        p[9] = FloatToInt(scale) + 64;
        p[3] = 0x44;
        p[1] = 0;
        p[2] = D_001F26C0[0][0];
        *(float *)(p + 12) = func_002A7878(D_001AA3CC, D_001AA3D0) * 105000.0f;
        p[8] = func_002A77E0(255);
        *(short *)(p + 10) = life;
        *(int *)(p + 4) = 0x40808080;
        qcopy(p + 16, pos);
        qcopy(state, velocity);
        *(int *)(state + 12) = 0;
        *(float *)(state + 24) = *(float *)(p + 12) * 2;
        {
            int random = func_002A7820(0, 3);
            float min = D_001AA3D4;
            float max = min + scale;
            *(int *)(state + 20) = random;
            *(int *)(state + 16) = life / 2;
            *(float *)(state + 28) = func_002A7878(min, max) * 0.00027777778450399637f;
        }
    }
    return p;
}
