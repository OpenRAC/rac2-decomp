#include "common.h"

/* Kept in its own -G8 unit: func_L00_003C3A70 reads and writes small data through $gp. */

typedef int UiQuadword __attribute__((mode(TI)));

extern char *g_trail_owner __attribute__((sda));
extern unsigned char g_voice_bank_index[];
extern char *g_sound_bank_table[];
extern UiQuadword g_hero_position[];
extern int g_trail_point_counts[] MACRO_ADDR;
extern int g_tesla_barrier_effects[] MACRO_ADDR;
extern short g_tesla_ribbon_ids[] MACRO_ADDR;
extern UiQuadword g_trail_up_vectors MACRO_ADDR, g_trail_forward_vectors MACRO_ADDR, g_trail_side_vectors MACRO_ADDR,
    D_L00_001B2930 MACRO_ADDR;
extern float g_trail_effect_length __attribute__((sda));
extern float g_electric_ribbon_alpha_scale __attribute__((sda));
extern char g_effect_trail_histories[];
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

    if (g_trail_owner != 0) {
        AllocateSoundVoice(*(char **)(g_sound_bank_table[g_voice_bank_index[0]] + 0x28) + 0x80,
                      0, 0, g_hero_position, 0x400);
        return 0;
    }
    if (weapon_spend_ammo(45, 1) == 0) {
        AllocateSoundVoice(*(char **)(g_sound_bank_table[g_voice_bank_index[0]] + 0x28),
                      0, 0, g_hero_position, 0x400);
        return 0;
    }

    owner = (Owner3A *)CreateMoby(mode ? MOBY_CLASS_TESLA_BARRIER : MOBY_CLASS_SHIELD_CHARGER);
    if (owner != 0) {
        state = owner->state;
        g_trail_owner = (char *)owner;
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
                g_trail_point_counts[n] = 0;
        }
        vec_scale_to_length(g_effect_trail_histories, owner->forward, g_trail_effect_length);
        qcopy(&g_trail_up_vectors, up);
        vec_scale_to_length(g_effect_trail_histories + 0x140, side, g_trail_effect_length);
        qcopy(&g_trail_forward_vectors, owner->forward);
        vec_scale_to_length(g_effect_trail_histories + 0x280, up, g_trail_effect_length);
        qcopy(&g_trail_side_vectors, side);
        FastVecAdd(g_effect_trail_histories + 0x3C0, owner->forward, up);
        entries = state->entries;
        vec_scale_to_length(g_effect_trail_histories + 0x3C0, g_effect_trail_histories + 0x3C0, g_trail_effect_length);
        words = state->words;
        FastVecCross(&g_trail_cross_vector, g_effect_trail_histories + 0x3C0, side);

        {
            int n;

            for (n = 7; n >= 0; n--)
                g_tesla_barrier_effects[n] = 0;
        }
        {
            int n;

            for (n = 4; n >= 0; n--)
                g_tesla_ribbon_ids[n] = 0;
        }
        g_electric_ribbon_alpha_scale = 1.0f;

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
