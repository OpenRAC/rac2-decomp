#include "include_asm.h"
#include "common.h"
extern float D_L23_001B38E8[] __attribute__((sda));
extern int D_L23_001B3900[] __attribute__((sda));
extern int D_L23_001B3918[] __attribute__((sda));
extern float D_L23_001B19FC __attribute__((sda));
extern char D_L23_001BA640[];
extern float func_00282E48(void *, void *);
extern int func_00282978(void *);
extern void func_0029F338(void *);
extern void func_L00_002E6DB8(void *, void *);
extern void func_L05_00428518(void *);

void func_L23_004265D0(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (!*(unsigned char *)(object + 0x20)) {
        D_L23_001B38E8[*(int *)(state + 0x3C)] = 0.01f;
        D_L23_001B3900[*(int *)(state + 0x3C)] = 0xFF;
        *(unsigned char *)(object + 0x20) = 1;
        if (fast_vec_dist(object + 0x10, D_L23_001BA640) > 200.0f)
            *(float *)(state + 0x40) = 4.0f;
        else if (fast_vec_dist(object + 0x10, D_L23_001BA640) > 100.0f)
            *(float *)(state + 0x40) = 2.0f;
        else if (fast_vec_dist(object + 0x10, D_L23_001BA640) > 25.0f)
            *(float *)(state + 0x40) = 1.0f;
        else if (fast_vec_dist(object + 0x10, D_L23_001BA640) > 0.0f)
            *(float *)(state + 0x40) = 0.5f;
    }
    if (!FastDecTimer(state)) {
        FastDecTimer(state + 4);
        func_L00_002E6DB8(DrawExpandingBillboardEffect, object);
    } else {
        D_L23_001B3918[*(int *)(state + 0x3C)] = 0;
        D_L23_001B19FC -= 1.0f;
        func_0029F338(object);
    }
}

