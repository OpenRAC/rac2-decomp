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
extern EffectTuning D_L00_00253770[];
extern unsigned char *D_L00_001B0A20 __attribute__((sda));
extern char D_L00_001B0A28[8] __attribute__((sda));
extern char D_L00_001B0A38[8] __attribute__((sda));
extern char D_L00_001B0A40[8] __attribute__((sda));
extern char *D_L00_001B2BC8;
extern char *D_L00_001B2BCC;
extern char *D_L00_001B2BD0;
extern short D_L00_001B2BD4;
extern int D_L00_001B2BD8;
extern float D_L00_001B2BDC;
extern unsigned char *health_drain_slots_create(int unused);

/* Empties the effect slots, calls func_L00_003F8DC8 and installs the two banks of per-kind tuning,
   the kinds grouped alike in both banks. entry's initializer is overwritten before it is read. */
void InitHealthDrainSlots(void)
{
    int i;
    EffectTuning *entry = D_L00_00253770;
    EffectTuning *table;

    for (i = 0; i < 30; i++)
        g_health_l00_drain_slots[i].object = 0;
    D_L00_001B0A20 = 0;
    health_drain_slots_create(0);
    D_L00_001B2BD4 = 3;
    D_L00_001B2BD8 = 30;
    D_L00_001B2BDC = 0.96f;
    D_L00_001B2BC8 = D_L00_001B0A28;
    D_L00_001B2BCC = D_L00_001B0A38;
    D_L00_001B2BD0 = D_L00_001B0A40;
    entry = D_L00_00253770;
    for (i = 0; i < 119; i++) {
        entry->weight = 0.0f;
        entry->count = 0;
        entry[119].weight = 0.0f;
        entry[119].count = 0;
        entry++;
    }
    table = D_L00_00253770;
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
