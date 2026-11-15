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
/* Creates a drifting particle with a random size and starting speed. */
char *func_002C7748(char *pos, char *velocity, int life)
{
    char *state;
    char *particle = AllocParticle(0x60);
    float scale;
    if (particle) {
        state = particle + 32;
        scale = 2.0f;
        particle[9] = FloatToInt(scale) + 64;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = D_001F26C0[0][0];
        *(float *)(particle + 12) = RandomFloatRange(D_001AA3CC, D_001AA3D0) * 105000.0f;
        particle[8] = RandomIntBelow(255);
        *(short *)(particle + 10) = life;
        *(int *)(particle + 4) = 0x40808080;
        qcopy(particle + 16, pos);
        qcopy(state, velocity);
        *(int *)(state + 12) = 0;
        *(float *)(state + 24) = *(float *)(particle + 12) * 2;
        {
            int random = RandomIntRange(0, 3);
            float min = D_001AA3D4;
            float max = min + scale;
            *(int *)(state + 20) = random;
            *(int *)(state + 16) = life / 2;
            *(float *)(state + 28) = RandomFloatRange(min, max) * 0.00027777778450399637f;
        }
    }
    return particle;
}
