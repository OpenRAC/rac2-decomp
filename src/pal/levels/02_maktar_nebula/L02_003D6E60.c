#include "include_asm.h"
#include "names.h"



extern void value_set_and_smooth(char *, char *, int, int, float);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern void SpawnJointParticleBursts(char *, int, int);
extern void chainblade_draw_glows(char *);
extern char *g_active_attacker_robot;

void func_PAL_L02_003D8738(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x95) == 2 ||
        *(unsigned char *)(arg0 + 0x20) == 0x12) {
        SpawnJointParticleBursts(arg0, 2, 0);
        SpawnJointParticleBursts(arg0, 3, 1);
    }
    gfx_add_draw_callback_third(chainblade_draw_glows, arg0);
    if (*(unsigned short *)(arg0 + 0x96) < 0xFFFF) {
        (*(unsigned short *)(arg0 + 0x96))++;
    }
    if (g_active_attacker_robot != 0 &&
        (g_active_attacker_robot == arg0 || *(short *)(g_active_attacker_robot + 0xAA) == 0x9F8)) {
        *(short *)(state + 0x32A) = -1;
    }
    *(unsigned short *)(state + 0x32A) = *(unsigned short *)(state + 0x32A) + 1;
    *(unsigned short *)(state + 0x32E) = *(unsigned short *)(state + 0x32E) + 1;
    value_set_and_smooth(arg0, state + 0x340, 6, 1, 2.5f);
}

