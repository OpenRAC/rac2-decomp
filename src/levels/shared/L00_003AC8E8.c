#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[4];
    unsigned char flag;
    unsigned char pad1[0x74 - 5];
    float scale;
    unsigned char pad2[0xE0 - 0x78];
} Entry262570b;

extern void FastVecScale(void *, void *, float);
extern int coll_process_hit(float, int, int, int, int);
extern void StartAttachedEffect(int, int, int);
extern void moby_queue_knockback_for_nodes(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char g_item_slot_to_record[];
extern Entry262570b g_weapon_l00_table[];
extern int g_area_hit_targets[];

typedef struct {
    float head[4];
    float vec[4];
    int arg;
} Trail_3AC8E8;

/* Makes the blast of a homing shot: hurts everything close by and shows the explosion. */
void homing_shot_spawn_explosion(char *moby, void *normal, int hitTarget)
{
    Trail_3AC8E8 blast;
    Entry262570b *entry;
    float scale;
    int count;
    int i;

    blast.arg = hitTarget;
    FastVecScale(blast.head, normal, -3.0f);
    entry = &g_weapon_l00_table[g_item_slot_to_record[0x1B]];
    scale = entry->scale;
    count = coll_process_hit(entry->flag != 0 ? 3.0f : 4.0f, (int)(moby + 0x10), 0x10, (int)moby, 0);
    for (i = 0; i < count; i++) {
        if ((g_weapon_l00_table + g_item_slot_to_record[0x1B])->flag != 0)
            StartAttachedEffect(g_area_hit_targets[i], 0x45, *(int *)(moby + 0xB8));
        else
            StartAttachedEffect(g_area_hit_targets[i], 0x1B, *(int *)(moby + 0xB8));
    }
    *(TI128 *)blast.vec = *(TI128 *)(moby + 0x10);
    moby_queue_knockback_for_nodes(moby, blast.vec, g_area_hit_targets, count, blast.arg, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}
