/* func_PAL_L00_003CF868, the PAL copy of func_L00_003CB980: the same C, where the lifetime 160
 * becomes 133, the timer 20 becomes 17 and the direction scale 1.0f becomes 1.2f, so the effect
 * call's 1.0f arguments are now their own constant. Separate -G8 unit: the pool counters are
 * read through $gp, and the position copies are 16-byte (TImode) assignments. Saving the position
 * through the volatile qcopy keeps the 1.2f in a saved register: it has one use, and combine
 * would otherwise carry the constant across the plain assignment to that call.
 */
#include "common.h"

typedef int L00PoolQuad __attribute__((mode(TI)));

/* Measured partial layouts (moby fields named after rac1-decomp's Moby); original types and
   game roles are unknown. */
typedef struct {
    unsigned int word_00;
    unsigned int word_04;
    unsigned int word_08;
    unsigned int word_0C;
} L00PoolSlot;

typedef struct {
    char pad_00[0x10];
    float position[4];
    unsigned char state;
    char pad_21[0xF];
    unsigned char update_dist;
    char pad_31;
    short draw_dist;
    char pad_34[0x34];
    char *pvars;
    char pad_6C[0x3E];
    short field_AA;
} L00PoolMoby;

typedef struct {
    float direction[4];
    int lifetime;
    int slot;
    float scale;
    int field_1C;
    char pad_20[0x10];
    int timer;
    int field_34;
    int field_38;
    int value;
    int owner_field_AA;
    int effect_slot;
} L00PoolState;

typedef struct {
    char pad_00[0x10];
    void *owner;
    char pad_14[0x1C];
} L00PoolParticle;

typedef struct {
    char pad_00[0x8C];
    int field_8C;
    char pad_90[0x10];
} L00PoolTrail;

extern L00PoolSlot D_L00_002472C0[];
extern unsigned int D_L00_001B0138 __attribute__((sda));
extern int D_L00_001B013C __attribute__((sda));
extern L00PoolParticle *D_L00_001B2AD4 MACRO_ADDR;
extern L00PoolTrail *D_L00_001B2AD8 MACRO_ADDR;
extern char D_00189EA0[];
extern int func_L00_003CBBD0(void);
extern L00PoolMoby *func_0029EFD0(int);
extern int func_002FED90(void *, float, float, float, void *);
extern void func_00282F20(void *, void *, float);
extern char *func_L00_00329FF0(char *);
extern void func_L00_003CB538(void *);

/* Unless func_L00_003CBBD0 reports the table full, creates a 0xA9B moby at position, takes the
   first free of the five D_L00_002472C0 slots for it and counts it in D_L00_001B0138. Its
   effect slot is allocated with the moby moved to D_00189EA0 for the call. The first call
   also carves the 64 particle records (D_L00_001B2AD4) and 12 trail records (D_L00_001B2AD8)
   out of the owner's pvars + 8 buffer and clears them; each call then seeds 20 particles
   through func_L00_003CB538. */
L00PoolMoby *func_PAL_L00_003CF868(L00PoolMoby *owner, int value, void *position, void *direction)
{
    char saved[16] __attribute__((aligned(16)));
    L00PoolMoby *object;
    L00PoolState *state;
    char *p;
    float scale;
    int i;

    if (func_L00_003CBBD0())
        return 0;

    for (i = 0; i < 5 && D_L00_002472C0[i].word_00 != 0; i++)
        ;
    object = func_0029EFD0(0xA9B);
    if (object != 0) {
        object->update_dist = object->draw_dist = 255;
        state = (L00PoolState *)object->pvars;
        object->state = 0;
        *(L00PoolQuad *)object->position = *(L00PoolQuad *)position;
        scale = 1.2f;

        qcopy(saved, object->position);
        *(L00PoolQuad *)object->position = *(L00PoolQuad *)D_00189EA0;
        state->effect_slot = func_002FED90(object, 1.0f, 1.0f, 1.0f, 0);
        *(L00PoolQuad *)object->position = *(L00PoolQuad *)saved;
        func_00282F20(state, direction, scale);
        state->lifetime = 133;
        state->timer = 17;
        state->slot = i;
        D_L00_002472C0[i].word_00 = (unsigned int)object;
        D_L00_001B0138++;

        state->scale = 2.5f;
        state->value = value;
        state->field_1C = 0;
        state->field_34 = 0;
        state->field_38 = 0;
        state->owner_field_AA = owner->field_AA;

        p = owner->pvars;
        if (!D_L00_001B013C) {
            D_L00_001B2AD4 = *(L00PoolParticle **)(p + 8);
            p = func_L00_00329FF0((char *)D_L00_001B2AD4 + 0xC00);
            D_L00_001B2AD8 = (L00PoolTrail *)p;
            func_L00_00329FF0(p + 0x780);
            D_L00_001B013C = 1;
            for (i = 63; i >= 0; i--)
                D_L00_001B2AD4[i].owner = 0;
            for (i = 0; i < 12; i++)
                D_L00_001B2AD8[i].field_8C = 0;
        }

        for (i = 0; i < 20; i++)
            func_L00_003CB538(object);
    }
    return object;
}
