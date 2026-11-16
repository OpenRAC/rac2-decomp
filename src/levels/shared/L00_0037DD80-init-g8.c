#include "names.h"
extern unsigned int D_L00_001B26B4_1;
extern int g_fade_level[] __attribute__((sda));

extern int g_active_tether_object __attribute__((sda));
extern unsigned char g_object_table_area[];
extern int g_owner_key_table[][4];
extern int g_object_slot_records[][8];
extern int g_object_l00_slot_table[];
extern int g_moby_pool_entries[];
extern void *g_object_table_ptrs[] __attribute__((sda));
extern void effect_clear_slot_tables(void);
extern void trail_effect_clear_pointer(void);
extern void part_clear_spark_records(void);
extern void effect_clear_four_word_table(void);
extern void blast_clear_saved_pointer(void);
extern void synthenoid_clear_slots(void);
extern void effect_clear_flag(void);
extern void lightning_burst_clear_active_flag(void);
extern void state_reset_records(void);
extern void state_reset_words(void);
extern void InitHealthDrainSlots(void);
extern void shot_init_tables(void);
extern void CollectClass135FObjects(void);
extern void *moby_place_fixed_id_object(void *);

/* Clears the level's object tables, runs each part's setup function and creates the first object. */
void level_init_object_tables(void)
{
    unsigned char *tablePtr;
    int i;
    int empty;
    union { int q __attribute__((mode(TI))); float f[4]; } v;
    unsigned char *newObject;
    g_active_tether_object = 0;
    tablePtr = g_object_table_area;
    do {
        tablePtr[1] = 0;
        *(int *)(tablePtr + 0x40) = 0;
        tablePtr += 0x50;
    } while ((int)tablePtr < (int)(g_object_table_area + 0x1400));
    for (i = 31; i >= 0; i--) g_owner_key_table[i][1] = 0;
    for (i = 127; i >= 0; i--) g_object_slot_records[i][7] = 0;
    empty = -1;
    for (i = 63; i >= 0; i--) g_object_l00_slot_table[i] = empty;
    g_object_l00_slot_table[64] = 0;
    g_moby_pool_entries[256] = 0;
    effect_clear_slot_tables();
    trail_effect_clear_pointer();
    part_clear_spark_records();
    effect_clear_four_word_table();
    blast_clear_saved_pointer();
    synthenoid_clear_slots();
    effect_clear_flag();
    lightning_burst_clear_active_flag();
    state_reset_records();
    state_reset_words();
    InitHealthDrainSlots();
    shot_init_tables();
    v.q = 0;
    v.f[0] = 5.0f;
    v.f[3] = 1.0f;
    v.f[1] = 5.0f;
    v.f[2] = 5.0f;
    newObject = moby_place_fixed_id_object(&v);
    g_object_table_ptrs[0] = newObject;
    *(int *)(newObject + 0x98) = 0;
    *(unsigned short *)(newObject + 0x34) |= 2;
    g_fade_level[0] = 0;
    D_L00_001B26B4_1 = 0;
    CollectClass135FObjects();
}
