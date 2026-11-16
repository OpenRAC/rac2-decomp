#include "names.h"
/* func_PAL_0032F0B8: start an attached effect on an object, in the first free slot of the level's
   effect table. Its own unit because the slot array has its real type here, where 00327038.c
   only has an opaque search view of it. D_001A7A80 is reached by an unsplit lui/addiu pair. */
#include "common.h"

/* Declarations */
extern s32 part_find_effect_slot_by_object(void *object);
/* func_PAL_0032F0B8's effect type rows, kind flags and per-bank effect parameters. */
typedef struct { int active; unsigned char type; char pad[0x47]; short kind; char tail[0x92]; } EffectType;
extern EffectType g_weapon_table[];
extern unsigned char g_movie_seen_flags[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
typedef struct { float scale; int ticks; char pad[8]; } EffectParams;
extern EffectParams g_effect_params_table[2][119];
extern float *moby_get_private_value_0(void *);
/* The matched slot consumer reads +0x0C as phase; creation clears its bits. */
typedef struct {
    int remaining, color, flags;
    union { float value; unsigned int bits; } phase;
    float rate;
    char *object;
    int tag, active;
} EffectSlot;
extern EffectSlot g_health_l00_drain_slots[];
extern void get_moby_color(void *, int *, int *, int *);

static __inline__ int EffectAlternate(int kind)
{
    EffectType *type = &g_weapon_table[g_item_slot_to_record[kind]];
    if (type->active) {
        if (type->type == 2) return 1;
        if (type->type == 1) {
            int selected = 0;
            switch (kind) {
            case 12: case 14: case 17: case 18: case 53: selected = 1; break;
            }
            if (selected) return 1;
        }
    }
    return 0;
}

static __inline__ int EffectThird(int kind)
{
    EffectType *type = &g_weapon_table[g_item_slot_to_record[kind]];
    int result = 0;
    if (type->active) result = type->type == 3;
    return result;
}

int StartAttachedEffect_pal(char *self, int index, int arg)
{
    int kind = g_weapon_table[index].kind;
    int result = 1, alternate;
    int i, r, g, b;
    char *p;
    float *health;
    if (!kind) kind = index;
    if (!(g_movie_seen_flags[kind] & 8)) return result;
    alternate = 0;
    if (EffectAlternate(kind) || EffectThird(kind)) alternate = 1;
    if (*(short *)(*(char **)(self + 0x24) + 0x46) != 5) return 1;
    if (!(*(unsigned short *)(self + 0x34) & 0x1000)) return 1;
    if (*(signed char *)(self + 0x20) < 0) return 1;
    if (!*(int *)(self + 0x98)) return 1;
    health = moby_get_private_value_0(self);
    if (!health || *health <= 0.0f) return 1;
    if (part_find_effect_slot_by_object(self) != -1) return 1;
    for (i = 0; i < 30; i++) {
        EffectSlot *slot;
        int found;
        unsigned int flags;
        if (g_health_l00_drain_slots[i].object)
            continue;
        slot = &g_health_l00_drain_slots[i];
        found = 0;
        slot->object = self;
        slot->remaining = g_effect_params_table[alternate][index].ticks * 50;
        slot->rate = g_effect_params_table[alternate][index].scale * 0.01666667f;
        flags = *(unsigned short *)(self + 0x34);
        if (flags & 0x20) {
            char *colour = *(char **)(*(char **)(self + 0x68) + 0x10);
            if (colour && *(short *)colour) {
                r = *(unsigned char *)(colour + 4);
                g = *(unsigned char *)(colour + 5);
                b = *(unsigned char *)(colour + 6);
                found = 1;
            }
        }
        if (!found) get_moby_color(slot->object, &r, &g, &b);
        slot->phase.bits = 0;
        slot->flags = 0x8000;
        slot->color = (b << 16) + (g << 8) + r;
        slot->tag = arg;
        slot->active = 1;
        result = 0;
        break;
    }
    return result;
}