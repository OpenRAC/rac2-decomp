#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { int unused, timer, remaining, cooldown; int index[4]; char *child[4]; } SwitchState;
extern char *D_L00_001B1E9C;
extern int D_L00_001AF020 __attribute__((sda)), D_L00_001AF024 __attribute__((sda));
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
        state->timer = D_L00_001AF020;
        state->remaining = 3;
        state->child[0] = D_L00_001B1E9C + state->index[0] * 0x100;
        state->child[1] = D_L00_001B1E9C + state->index[1] * 0x100;
        state->child[2] = D_L00_001B1E9C + state->index[2] * 0x100;
        state->child[3] = D_L00_001B1E9C + state->index[3] * 0x100;
        break;
    case 1:
        contact = part_find_owned_effect_slot(actor, 0x10000, 0);
        math_fast_float_d(&state->cooldown);
        if (contact && state->cooldown == 0) {
            *(unsigned char *)(actor + 0xA8) = 0xFF;
            state->cooldown = D_L00_001AF024;
            if (--state->remaining <= 0) { moby_mark_spawned(actor); return; }
        }
        if (*(unsigned char *)(state->child[0] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[1] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[2] + 0x20) == 0x50 ||
            *(unsigned char *)(state->child[3] + 0x20) == 0x50) {
            if (math_fast_float_d(&state->timer)) {
                state->timer = D_L00_001AF020;
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
