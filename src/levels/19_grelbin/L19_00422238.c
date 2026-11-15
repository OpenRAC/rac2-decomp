#include "common.h"

extern float func_002A7878(float, float);
extern u8 D_L19_001A8F20[] MACRO_ADDR;
extern void func_L19_00422178(void *, void *);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern void func_002C7BB8(void *, void *, int, int, int, int, int, float, float, float, int);

void func_L19_00422238(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);
    int color, alpha, life, type;
    float scale, size;

    while (*(float *)(state + 0x24) > 1.0f) {
        *(float *)(state + 0x24) -= 1.0f;
        qcopy(vel, D_L19_001A8F20);
        func_L19_00422178(obj, pos);
        if (*(u8 *)(obj + 0x20) == 3 && func_002A7820(0, 1))
            pos[2] = *(float *)(state + 4);
        else
            vel[2] = *(float *)(state + 0xC) * 0.5f;
        pos[2] += 6.0f;
        color = FastTweenColor(*(int *)(state + 0x38), *(int *)(state + 0x34),
                              func_002A7878(0.0f, 1.0f));
        alpha = color >> 24;
        life = func_002A7820(*(int *)(state + 0x40) / 2, *(int *)(state + 0x40));
        color &= 0xFFFFFF;
        type = func_002A7820(0, *(int *)(state + 0x3C));
        scale = func_002A7878(0.5f, 1.0f) * *(float *)(state + 0x30);
        size = func_002A7878(0.7f, 1.0f);
        func_002C7BB8(pos, vel, life, color, type, alpha, 0, scale,
                      *(float *)(state + 0x30) * size, 0.0033333334f,
                      *(int *)(state + 0x2C));
    }
}
