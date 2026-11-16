#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: the body reaches level globals through $gp. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int g_hero_vehicle_mode;

extern char *g_target_moby __attribute__((nosda));

extern float g_pop_target_param_a __attribute__((sda));

extern float g_pop_target_param_b __attribute__((sda));

/* Declared without sda: the load gcc copies into a delay slot is assembled through $gp,
   the reload after the 0xAC store stays absolute, as in retail. */
extern int g_frame_l20_counter;

extern void moby_reset_to_idle(char *);

extern void moby_vanish_with_effect(char *);

extern void path_follow_pop_on_touch(char *);

extern void pushable_moby_update(void *, void *, float, float, float, int);

extern float coll_probe_ground_height_below(char *, int, float);

extern float math_fabs(float);

extern int math_fast_float_d(int *);

/* The object's state block (only the fields this body touches). */
typedef struct {
    char pad0[0x20];
    float x20;
    u16 x24;
    char pad26[0x50 - 0x26];
    char x50[0x20];
    u32 x70;
    char pad74[0x84 - 0x74];
    float x84;
    float x88;
    char pad8C[0xA0 - 0x8C];
    int xA0;
    char padA4[0xA8 - 0xA4];
    int xA8;
    u32 xAC;
} State;

/* Update handler for moby class 4819: it sets itself up, waits quietly, and pops with an effect when the player targets it or comes close. */
void pop_target_update(char *moby) {
    State *state = *(State **)(moby + 0x68);
    int mode;

    if (g_hero_vehicle_mode == 2 && *(u8 *)(moby + 0x20) != 1) {
        moby_reset_to_idle(moby);
    }
    mode = *(u8 *)(moby + 0x20);
    switch (mode) {
    case 0:
        state->x20 = 1.0f;
        state->x24 = 1;
        state->x70 |= 6;
        state->x84 = g_pop_target_param_a;
        state->x88 = g_pop_target_param_b;
        moby_reset_to_idle(moby);
        return;
    case 1:
        return;
    case 2:
        pushable_moby_update(moby, state->x50, 0.0f, 0.5f, 0.6f, state->xA0);
        break;
    }
    if (g_target_moby == moby) {
        state->xAC = 1;
    }
    if (((g_frame_l20_counter & 0xF) == (((int)moby >> 8) & 0xF)
         && 5.0f < math_fabs(*(float *)(moby + 0x18)
                                 - coll_probe_ground_height_below(moby + 0x10, 0, 0.5f)))
        || (state->xAC != 0 && math_fast_float_d(&state->xA8) != 0)) {
        moby_vanish_with_effect(moby);
    } else {
        path_follow_pop_on_touch(moby);
    }
}
