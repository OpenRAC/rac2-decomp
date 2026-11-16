#include "include_asm.h"
#include "names.h"



extern void value_set_and_smooth(char *, char *, int, int, float);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern void SpawnJointParticleBursts(char *, int, int);
extern void chainblade_draw_glows(char *);
extern char *g_active_attacker_robot;

/* Per-frame upkeep for the Chainblade: jet puffs while flying, glow drawing, timers, and a timer reset when it is the target. */
void chainblade_update_effects_timers_pal(char *self) {
    char *state = *(char **)(self + 0x68);

    if (*(unsigned char *)(self + 0x95) == 2 ||
        *(unsigned char *)(self + 0x20) == 0x12) {
        SpawnJointParticleBursts(self, 2, 0);
        SpawnJointParticleBursts(self, 3, 1);
    }
    gfx_add_draw_callback_third(chainblade_draw_glows, self);
    if (*(unsigned short *)(self + 0x96) < 0xFFFF) {
        (*(unsigned short *)(self + 0x96))++;
    }
    if (g_active_attacker_robot != 0 &&
        (g_active_attacker_robot == self || *(short *)(g_active_attacker_robot + 0xAA) == 0x9F8)) {
        *(short *)(state + 0x32A) = -1;
    }
    *(unsigned short *)(state + 0x32A) = *(unsigned short *)(state + 0x32A) + 1;
    *(unsigned short *)(state + 0x32E) = *(unsigned short *)(state + 0x32E) + 1;
    value_set_and_smooth(self, state + 0x340, 6, 1, 2.5f);
}

