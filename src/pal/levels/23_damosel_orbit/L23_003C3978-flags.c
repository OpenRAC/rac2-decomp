#include "include_asm.h"
#include "names.h"
extern int g_enemy_effect_param __attribute__((sda));
extern void moby_play_anim_and_link(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);
extern void func_367150(int);

/* Calms the enemy down: clears its attack flags, resets the linked part and its animation and stops its looping sound. (PAL) */
void enemy_reset_calm_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int none = -1;

    *(short *)(vars + 0x178) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000;
    *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
    *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) &= 0xFFBE;
    *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x1000;
    *(int *)(*(char **)(vars + 0x2A0) + 0x98) = *(int *)(*(char **)(*(char **)(vars + 0x2A0) + 0x24) + 0x10);
    *(short *)(vars + 0x2B0) = 0;
    *(int *)(vars + 0x25C) = 0;
    *(short *)(vars + 0x26) = 2;
    *(float *)(vars + 0x20) = (float)*(short *)(vars + 0x24);
    moby_play_anim_and_link(moby, 1, 0, 0, 3, 1.0f);
    {
        unsigned short param_int = g_enemy_effect_param;
        float param_float = (float)g_enemy_effect_param;

        *(short *)(vars + 0x24) = param_int;
        *(float *)(vars + 0x20) = param_float;
        *(short *)(vars + 0x2A4) = 0;
        *(float *)(vars + 0x19C) = 150.0f / param_float;
        *(float *)(vars + 0x198) = 40.0f / param_float;
    }
    if (*(int *)(vars + 0x3B4) != none) {
        func_367150(*(int *)(vars + 0x3B4));
        *(int *)(vars + 0x3B4) = none;
    }
}
