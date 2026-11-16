#include "common.h"

/* One of the 30 slots of the level's attached-effect table, as in L00_003F87B0.c, and one entry of
   the per-kind tuning table that follows it: two banks of 119 kinds. */
typedef struct { int timer, first, second; float phase, damage; char *object; int owner, hold; } Slot;
typedef struct {
    float weight;
    int count;
    char remainder[8];
} EffectTuning;

extern Slot g_health_l00_drain_slots[30];
extern EffectTuning g_effect_tuning_table[];
extern unsigned char *g_health_drain_moby __attribute__((sda));
extern char g_effect_data_block_a[8] __attribute__((sda));
extern char g_effect_data_block_b[8] __attribute__((sda));
extern char g_effect_data_block_c[8] __attribute__((sda));
extern char *g_reset_ptr_a;
extern char *g_reset_ptr_b;
extern char *g_reset_ptr_c;
extern short g_reset_short_param;
extern int g_reset_int_param;
extern float g_reset_decay_factor;
extern unsigned char *health_drain_slots_create(int unused);

/* Empties the effect slots, calls func_L00_003F8DC8 and installs the two banks of per-kind tuning,
   the kinds grouped alike in both banks. entry's initializer is overwritten before it is read. */
void InitHealthDrainSlots(void)
{
    int i;
    EffectTuning *entry = g_effect_tuning_table;
    EffectTuning *table;

    for (i = 0; i < 30; i++)
        g_health_l00_drain_slots[i].object = 0;
    g_health_drain_moby = 0;
    health_drain_slots_create(0);
    g_reset_short_param = 3;
    g_reset_int_param = 30;
    g_reset_decay_factor = 0.96f;
    g_reset_ptr_a = g_effect_data_block_a;
    g_reset_ptr_b = g_effect_data_block_b;
    g_reset_ptr_c = g_effect_data_block_c;
    entry = g_effect_tuning_table;
    for (i = 0; i < 119; i++) {
        entry->weight = 0.0f;
        entry->count = 0;
        entry[119].weight = 0.0f;
        entry[119].count = 0;
        entry++;
    }
    table = g_effect_tuning_table;
    table[0x2A].weight = 1.0f; table[0x2A].count = 5;
    table[0x47].weight = 1.0f; table[0x47].count = 5;
    table[0x16].weight = 1.0f; table[0x16].count = 3;
    table[0x41].weight = 1.0f; table[0x41].count = 3;
    table[0x1A].weight = 1.0f; table[0x1A].count = 3;
    table[0x44].weight = 1.0f; table[0x44].count = 3;
    table[0x1D].weight = 2.0f; table[0x1D].count = 4;
    table[0x3F].weight = 2.0f; table[0x3F].count = 4;
    table[0x25].weight = 2.0f; table[0x25].count = 4;
    table[0x4C].weight = 2.0f; table[0x4C].count = 4;
    table[0x1B].weight = 2.0f; table[0x1B].count = 4;
    table[0x45].weight = 2.0f; table[0x45].count = 4;
    table[0x1C].weight = 2.0f; table[0x1C].count = 4;
    table[0x3E].weight = 2.0f; table[0x3E].count = 4;
    table[0x20].weight = 2.0f; table[0x20].count = 4;
    table[0x4E].weight = 2.0f; table[0x4E].count = 4;
    table[0x19].weight = 2.0f; table[0x19].count = 4;
    table[0x46].weight = 2.0f; table[0x46].count = 4;
    table[0x2A + 119].weight = 9.0f; table[0x2A + 119].count = 8;
    table[0x47 + 119].weight = 9.0f; table[0x47 + 119].count = 8;
    table[0x16 + 119].weight = 3.0f; table[0x16 + 119].count = 4;
    table[0x41 + 119].weight = 3.0f; table[0x41 + 119].count = 4;
    table[0x1A + 119].weight = 3.0f; table[0x1A + 119].count = 4;
    table[0x44 + 119].weight = 3.0f; table[0x44 + 119].count = 4;
    table[0x1D + 119].weight = 3.0f; table[0x1D + 119].count = 6;
    table[0x3F + 119].weight = 3.0f; table[0x3F + 119].count = 6;
    table[0x25 + 119].weight = 3.0f; table[0x25 + 119].count = 6;
    table[0x4C + 119].weight = 3.0f; table[0x4C + 119].count = 6;
    table[0x1B + 119].weight = 2.0f; table[0x1B + 119].count = 5;
    table[0x45 + 119].weight = 2.0f; table[0x45 + 119].count = 5;
    table[0x1C + 119].weight = 5.0f; table[0x1C + 119].count = 4;
    table[0x3E + 119].weight = 5.0f; table[0x3E + 119].count = 4;
    table[0x20 + 119].weight = 5.0f; table[0x20 + 119].count = 4;
    table[0x4E + 119].weight = 5.0f; table[0x4E + 119].count = 4;
    table[0x19 + 119].weight = 3.0f; table[0x19 + 119].count = 4;
    table[0x46 + 119].weight = 3.0f; table[0x46 + 119].count = 4;
}
