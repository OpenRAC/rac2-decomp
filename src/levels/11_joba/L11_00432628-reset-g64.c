/* A unit of its own for -G64 -Wa,-G64 (config/cflags.txt): retail reads the twelve-float
   default table through $gp, which its 48-byte extent puts above the -G8 threshold. */
#include "common.h"

/* The class record an object points at (field 0x24). */
struct RotorClass {
    /* 0x00 */ char pad00[0x10];
    /* 0x10 */ int f10;
};

/* The rotor's state (the object's field 0x68). Only the fields this reset uses are named. */
struct RotorState {
    /* 0x000 */ char pad00[0x20];
    /* 0x020 */ float f20;
    /* 0x024 */ s16 f24;
    /* 0x026 */ char pad26[8];
    /* 0x02E */ u8 f2E;
    /* 0x02F */ char pad2F[0x41];
    /* 0x070 */ s16 colorPending;
    /* 0x072 */ s16 colorApplied;
    /* 0x074 */ u8 color[3];
    /* 0x077 */ char pad77[0x279];
    /* 0x2F0 */ float weights[12];
    /* 0x320 */ char pad320[0x10];
    /* 0x330 */ int records[10];
    /* 0x358 */ int linked;
    /* 0x35C */ char pad35C[0x18];
    /* 0x374 */ s16 f374;
    /* 0x376 */ char pad376[2];
    /* 0x378 */ s16 f378;
    /* 0x37A */ char pad37A[6];
    /* 0x380 */ u8 armed[10];
};

/* A rotor moby; each 256-byte record of the level's table has the same layout. */
struct RotorObject {
    /* 0x00 */ char pad00[0x24];
    /* 0x24 */ struct RotorClass *cls;
    /* 0x28 */ char pad28[9];
    /* 0x31 */ u8 f31;
    /* 0x32 */ char pad32[2];
    /* 0x34 */ u16 flags;
    /* 0x36 */ char pad36[0xD];
    /* 0x43 */ u8 f43;
    /* 0x44 */ char pad44[0x24];
    /* 0x68 */ struct RotorState *state;
    /* 0x6C */ char pad6C[0x13];
    /* 0x7F */ u8 f7F;
    /* 0x80 */ char pad80[0x18];
    /* 0x98 */ int f98;
};

extern char *g_moby_l11_table;
extern float g_rotor_reset_weights[12] __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void chain_creature_set_segments_anim(void *, int, int, int);
extern void chain_creature_set_linked_anim(void *, int, int, int);
extern void get_moby_color(void *, int *, int *, int *);
extern void set_moby_color(void *, int, int, int);
extern void rotor_reaim_random_spin(void *);

/* The record of the level's 256-byte table that the state lists at `i`, and the one it links to. */
#define LISTED_RECORD(obj, i) \
    ((struct RotorObject *)(D_L11_001B359C + ((obj)->state->records[i] << 8)))
#define LINKED_RECORD(obj) \
    ((struct RotorObject *)(((obj)->state->linked << 8) + (int)D_L11_001B359C))

/* Resets the ten rotors: re-arms the object and the ten records its state lists (each re-aimed
   and given the object's colour), reloads the twelve default weights, refreshes the linked
   record and restores a pending colour. */
void rotor_reset_group(struct RotorObject *obj)
{
    struct RotorState *state = obj->state;
    int red, green, blue;
    int i;

    state->f2E = 1;
    state->f20 = state->f24;
    obj->f31 = 1;
    obj->flags &= 0xFFFE;
    obj->f98 = obj->cls->f10;
    obj->flags = (obj->flags | 0x1000) & 0xFFB9;
    obj->f7F = 0;
    state->f378 = 10;
    moby_set_state(obj, 2, 0);
    if (obj->f43)
        anim_start_blended(obj, 0, 0, 0);
    chain_creature_set_segments_anim(obj, 1, 0, 0);
    chain_creature_set_linked_anim(obj, 1, 0, 0);
    state->f374 = -1;
    get_moby_color(obj, &red, &green, &blue);

    for (i = 0; i < 10; i++) {
        state->armed[i] = 0;
        rotor_reaim_random_spin(LISTED_RECORD(obj, i));
        set_moby_color(LISTED_RECORD(obj, i), red, green, blue);
    }

    for (i = 0; i < 12; i++)
        state->weights[i] = g_rotor_reset_weights[i];

    LINKED_RECORD(obj)->flags &= 0xFFFD;
    LINKED_RECORD(obj)->flags &= 0xFFFB;
    LINKED_RECORD(obj)->flags &= 0xFFBF;
    LINKED_RECORD(obj)->flags |= 0x1000;
    LINKED_RECORD(obj)->flags &= 0xFFFE;
    LINKED_RECORD(obj)->f31 = 1;
    LINKED_RECORD(obj)->f98 = LINKED_RECORD(obj)->cls->f10;

    if (state->colorPending) {
        state->colorPending = 0;
        set_moby_color(obj, state->color[0], state->color[1], state->color[2]);
        state->colorApplied = 1;
    }
}
