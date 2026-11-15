#include "common.h"

/* Kept in its own -G8 unit: func_L00_003C3A70 reads and writes small data through $gp. */

typedef int UiQuadword __attribute__((mode(TI)));

extern char *D_L00_001AFF98 __attribute__((sda));
extern unsigned char D_L00_001DB2BC[];
extern char *D_L00_001D9F00[];
extern UiQuadword g_hero_position[];
extern int D_L00_001B2940[] MACRO_ADDR;
extern int D_L00_001B2950[] MACRO_ADDR;
extern short D_L00_001B2990[] MACRO_ADDR;
extern UiQuadword D_L00_001B2900 MACRO_ADDR, D_L00_001B2910 MACRO_ADDR, D_L00_001B2920 MACRO_ADDR,
    D_L00_001B2930 MACRO_ADDR;
extern float D_L00_001AFF4C __attribute__((sda));
extern float D_L00_001B29D4 __attribute__((sda));
extern char D_L00_0023FB80[];
extern int weapon_spend_ammo(int, int);
extern int AllocateSoundVoice(void *, int, int, void *, int);
extern unsigned char *CreateMoby(int);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void fade_set_level(int);
extern float fade_get_value(void);
extern int PlayMobySound(int, int, void *);

/* State block of the created object; only the fields used here. */
typedef struct {
    float f00;
    char pad04[0xC - 0x4];
    int f0C;
    int f10;
    int countdown;
    short entries[4];
    int words[4];
} OwnerState;

/* The created object; field roles are inferred from this body. */
typedef struct {
    char pad00[0x10];
    UiQuadword position;
    unsigned char status;
    char pad21[0x30 - 0x21];
    unsigned char group;
    char pad31[3];
    unsigned short flags;
    char pad36[0x68 - 0x36];
    OwnerState *state;
    char pad6C[0xC0 - 0x6C];
    float forward[4], side[4], up[4], angles[4];
} Owner3A;

/* Creates the single object of this kind (0x1192 when mode is set, 0xA5C otherwise) unless one
   exists or the gate refuses, builds its basis from its angles, stores the scaled basis
   vectors and their combinations in the shared tables, clears the per-slot tables and resets
   the object's state block. Returns the object, or 0 when nothing was created. */
unsigned char *CreateTrailOwnerMoby(int mode)
{
    Owner3A *owner;
    OwnerState *state;
    float *up;
    float *side;
    UiQuadword *position;
    short *entries;
    int *words;

    if (D_L00_001AFF98 != 0) {
        AllocateSoundVoice(*(char **)(D_L00_001D9F00[D_L00_001DB2BC[0]] + 0x28) + 0x80,
                      0, 0, g_hero_position, 0x400);
        return 0;
    }
    if (weapon_spend_ammo(45, 1) == 0) {
        AllocateSoundVoice(*(char **)(D_L00_001D9F00[D_L00_001DB2BC[0]] + 0x28),
                      0, 0, g_hero_position, 0x400);
        return 0;
    }

    owner = (Owner3A *)CreateMoby(mode ? 0x1192 /* Tesla Barrier */ : 0xA5C /* Shield Charger */);
    if (owner != 0) {
        state = owner->state;
        D_L00_001AFF98 = (char *)owner;
        owner->flags |= 0x41;
        owner->group = 0xFF;
        owner->status = 1;
        euler_rotation_basis(owner->forward, owner->angles);
        up = owner->up;
        position = &owner->position;
        side = owner->side;

        {
            int n;

            for (n = 3; n >= 0; n--)
                D_L00_001B2940[n] = 0;
        }
        vec_scale_to_length(D_L00_0023FB80, owner->forward, D_L00_001AFF4C);
        qcopy(&D_L00_001B2900, up);
        vec_scale_to_length(D_L00_0023FB80 + 0x140, side, D_L00_001AFF4C);
        qcopy(&D_L00_001B2910, owner->forward);
        vec_scale_to_length(D_L00_0023FB80 + 0x280, up, D_L00_001AFF4C);
        qcopy(&D_L00_001B2920, side);
        FastVecAdd(D_L00_0023FB80 + 0x3C0, owner->forward, up);
        entries = state->entries;
        vec_scale_to_length(D_L00_0023FB80 + 0x3C0, D_L00_0023FB80 + 0x3C0, D_L00_001AFF4C);
        words = state->words;
        FastVecCross(&D_L00_001B2930, D_L00_0023FB80 + 0x3C0, side);

        {
            int n;

            for (n = 7; n >= 0; n--)
                D_L00_001B2950[n] = 0;
        }
        {
            int n;

            for (n = 4; n >= 0; n--)
                D_L00_001B2990[n] = 0;
        }
        D_L00_001B29D4 = 1.0f;

        fade_set_level(mode);
        state->f00 = fade_get_value();
        qcopy(position, g_hero_position);
        state->f0C = -1;
        state->f10 = 0;
        state->countdown = 30;
        {
            int n;

            for (n = 3; n >= 0; n--)
                entries[n] = 0;
        }
        {
            int n;

            for (n = 3; n >= 0; n--)
                words[n] = 0;
        }
        PlayMobySound(1, 0, owner);
    }
    return (unsigned char *)owner;
}
