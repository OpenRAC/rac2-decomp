#include "include_asm.h"
#include "names.h"
extern int g_enemy_effect_param __attribute__((sda));
extern void moby_play_anim_and_link(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void func_367150(int);

void enemy_reset_calm_pal(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int none = -1;

    *(short *)(state + 0x178) = 0;
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) &= 0xFFBE;
    *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x1000;
    *(int *)(*(char **)(state + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(state + 0x2A0) + 0x24) + 0x10);
    *(short *)(state + 0x2B0) = 0;
    *(int *)(state + 0x25C) = 0;
    *(short *)(state + 0x26) = 2;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    moby_play_anim_and_link(arg0, 1, 0, 0, 3, 1.0f);
    {
        unsigned short d = g_enemy_effect_param;
        float f = (float)g_enemy_effect_param;

        *(short *)(state + 0x24) = d;
        *(float *)(state + 0x20) = f;
        *(short *)(state + 0x2A4) = 0;
        *(float *)(state + 0x19C) = 150.0f / f;
        *(float *)(state + 0x198) = 40.0f / f;
    }
    if (*(int *)(state + 0x3B4) != none) {
        func_367150(*(int *)(state + 0x3B4));
        *(int *)(state + 0x3B4) = none;
    }
}
