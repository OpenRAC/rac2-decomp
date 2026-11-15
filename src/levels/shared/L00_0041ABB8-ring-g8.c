#include "common.h"

typedef int Quad __attribute__((mode(TI)));

extern char *g_lava_gun_ring_entries __attribute__((sda));
extern void table_clear_entry_flag(int);
extern int part_alloc_effect_slot(void *, void *, float, float, float);

extern void gfx_init_sprite_packet_large(char *packet);
extern float math_random_float_range(float low, float high);
extern int func_001163B0(void);

/* One 0x40-byte entry of the ring at D_L00_001B144C. */
typedef struct {
    Quad first, second;           /* 0x00 */
    char pad20[0x10];
    int value;                    /* 0x30 */
    int f34;                      /* 0x34 */
    int handle;                   /* 0x38 */
    char pad3C[4];
} RingEntry;

/* The ring bookkeeping at object +0x68. */
typedef struct {
    char pad0[0x3C];
    int head;                     /* 0x3C */
    int full;                     /* 0x40 */
    int count;                    /* 0x44 */
    int last;                     /* 0x48 */
} RingState;

typedef struct {
    char pad0[0x68];
    RingState *state;             /* 0x68 */
} RingOwner;

/* Append two vectors to the 35-entry ring and replace the entry's effect handle. */
void AppendVectorRingEntry(char *self, Quad *first, Quad *second, int value)
{
    RingState *state = ((RingOwner *)self)->state;
    RingEntry *slot = (RingEntry *)(state->head * 0x40 + g_lava_gun_ring_entries);

    qcopy(&slot->first, first);
    qcopy(&slot->second, second);
    if (slot->handle >= 0)
        table_clear_entry_flag(slot->handle);
    slot->handle = part_alloc_effect_slot(self, slot, 1.0f, 1.0f, 1.0f);
    slot->value = value;
    slot->f34 = 0;
    state->last = state->head;
    state->head += 1;
    if (state->head >= 35) {
        state->head = 0;
        state->full = 1;
    } else if (state->full != 1) {
        state->count += 1;
    }
}

/* A 0x90-byte packet: a 4x4 float matrix followed by packet fields. */
typedef struct {
    float m[4][4];
    char pad40[0x50];
} EffectPacket;

/* The slot seen from the start of part PART's 0x90-byte stride: its matrix sits at +0x60. */
typedef struct {
    char pad0[0x60];
    float m[4][4];                /* 0x60 */
} PartView;

/* One 0x530-byte effect slot. */
typedef struct {
    Quad first, second;           /* 0x00 */
    float point[2][4];            /* 0x20 */
    char pad40[0x20];
    EffectPacket matrix[2];       /* 0x60 */
    char pad180[0x120];
    EffectPacket packet[2];       /* 0x2A0 */
    char pad3C0[0x120];
    int phase[2];                 /* 0x4E0 */
    char pad4E8[8];
    float velocity[2];            /* 0x4F0 */
    char pad4F8[8];
    float scroll[2];              /* 0x500 */
    char pad508[8];
    int f510;                     /* 0x510 */
    int inUse;                    /* 0x514 */
    int f518, f51C;               /* 0x518 */
    char pad520[0x10];
} EffectSlot;

extern char *g_lava_gun_beam_slots __attribute__((sda));

/* Takes the first free one of the ten effect slots: resets its four packets, scales
   the first two at random, places two points around ORIGIN with random velocities,
   scrolls and phases, marks the slot in use and stores the two quadwords. */
void SpawnRandomTaperedQuadPair(void *unused, float *origin, Quad *first, Quad *second)
{
    EffectSlot *slot;
    PartView *view;
    float widthScale, heightScale, *scroll, *velocity;
    int index, part, *phase;
    Quad *point, *quads;

    for (index = 0; index < 10; index++) {
        slot = (EffectSlot *)(index * 0x530 + (int)g_lava_gun_beam_slots);
        if (slot->inUse != 0)
            continue;
        quads = (Quad *)slot;
        part = 0;
        phase = slot->phase;
        scroll = slot->scroll;
        velocity = slot->velocity;
        point = quads;
        for (; part < 2; part++) {
            view = (PartView *)((char *)slot + part * 0x90);
            gfx_init_sprite_packet_large((char *)&slot->packet[part]);
            gfx_init_sprite_packet_large((char *)&slot->matrix[part]);
            widthScale = math_random_float_range(0.3f, 0.5f);
            view->m[0][1] *= widthScale;
            view->m[1][1] *= widthScale;
            view->m[2][1] *= widthScale;
            view->m[3][1] *= widthScale;
            heightScale = math_random_float_range(0.9f, 1.0f);
            view->m[1][2] *= heightScale;
            view->m[3][2] *= heightScale;
            view->m[1][1] *= 0.4f;
            view->m[3][1] *= 0.4f;
            ((float *)(point + 2))[0] = origin[0] + math_random_float_range(-0.1f, 0.1f);
            ((float *)(point + 2))[1] = origin[1] + math_random_float_range(-0.1f, 0.1f);
            ((float *)(point + 2))[2] = origin[2];
            ((float *)(point + 2))[3] = 1.0f;
            *velocity = math_random_float_range(-0.02f, -0.01f);
            point++;
            velocity++;
            *scroll = math_random_float_range(-7.99f, 0.0f);
            scroll++;
            *phase = func_001163B0() % 2;
            phase++;
        }
        slot->f510 = 0;
        slot->inUse = 1;
        slot->f518 = 0;
        slot->f51C = 0;
        quads[1] = *second;
        quads[0] = *first;
        return;
    }
}
