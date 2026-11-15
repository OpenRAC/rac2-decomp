#include "common.h"

extern float func_002A7878(float, float);
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void func_L19_00422178(void *, void *);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern void func_002C7BB8(void *, void *, int, int, int, int, int, float, float, float, int);

/* Makes puffs of dust around the object as its dust counter fills up. */
void func_L19_00422238(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    int color, alpha, life, type;
    float scale, size;

    while (*(float *)(vars + 0x24) > 1.0f) {
        *(float *)(vars + 0x24) -= 1.0f;
        qcopy(vel, D_L19_001A8F20);
        PickRandomPointAroundMoby(moby, pos);
        if (*(u8 *)(moby + 0x20) == 3 && RandomIntRange(0, 1))
            pos[2] = *(float *)(vars + 4);
        else
            vel[2] = *(float *)(vars + 0xC) * 0.5f;
        pos[2] += 6.0f;
        color = FastTweenColor(*(int *)(vars + 0x38), *(int *)(vars + 0x34),
                              RandomFloatRange(0.0f, 1.0f));
        alpha = color >> 24;
        life = RandomIntRange(*(int *)(vars + 0x40) / 2, *(int *)(vars + 0x40));
        color &= 0xFFFFFF;
        type = RandomIntRange(0, *(int *)(vars + 0x3C));
        scale = RandomFloatRange(0.5f, 1.0f) * *(float *)(vars + 0x30);
        size = RandomFloatRange(0.7f, 1.0f);
        SpawnSizeChangingParticle(pos, vel, life, color, type, alpha, 0, scale,
                      *(float *)(vars + 0x30) * size, 0.0033333334f,
                      *(int *)(vars + 0x2C));
    }
}
