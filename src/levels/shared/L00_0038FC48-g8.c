#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { int unused, timer, remaining, cooldown; int index[4]; char *child[4]; } SwitchState;
extern char *g_moby_array_base;
extern int g_switch_activator_timer __attribute__((sda)), g_switch_activator_cooldown __attribute__((sda));
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
/* Activates one waiting child at a time and expires after three trigger contacts. */
void switch_child_activator_update(char *actor) {
    SwitchState *state = *(SwitchState **)(actor + 0x68);
    char *contact, **slot, *child;
    int i;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        state->timer = g_switch_activator_timer;
        state->remaining = 3;
        state->child[0] = g_moby_array_base + state->index[0] * 0x100;
        state->child[1] = g_moby_array_base + state->index[1] * 0x100;
        state->child[2] = g_moby_array_base + state->index[2] * 0x100;
        state->child[3] = g_moby_array_base + state->index[3] * 0x100;
        break;
    case 1:
        contact = part_find_owned_effect_slot(actor, 0x10000, 0);
        math_fast_float_d(&state->cooldown);
        if (contact && state->cooldown == 0) {
            *(unsigned char *)(actor + 0xA8) = 0xFF;
            state->cooldown = g_switch_activator_cooldown;
            if (--state->remaining <= 0) { moby_mark_spawned(actor); return; }
        }
        if (*(unsigned char *)(state->child[0] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[1] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[2] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[3] + 0x20) == 0x50) {
            if (math_fast_float_d(&state->timer)) {
                state->timer = g_switch_activator_timer;
                slot = state->child;
                for (i = 0; i < 4; i++, slot++) {
                    if (*(unsigned char *)(state->child[i] + 0x20) == 0x50) {
                        *(unsigned char *)(state->child[i] + 0x20) = 0x51;
                        child = *slot;
                        *(Quad *)(child + 0x10) = *(Quad *)(actor + 0x10);
                        *(unsigned char *)(child + 0xA8) = 0xFF;
                        return;
                    }
                }
            }
        }
        break;
    }
}
