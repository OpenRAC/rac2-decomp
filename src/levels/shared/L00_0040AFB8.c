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
extern void moby_queue_knockback_for_nodes(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char g_item_slot_to_record[];
extern Entry262570b g_weapon_l00_table[];
extern int g_area_hit_targets[];

/* Draws a short beam effect from the object, sized by the current weapon. */
void shot_draw_impact_beam(char *obj, void *source, int flags)
{
    float headVec[4];
    float startPos[4];
    float scale;
    int pointCount;

    FastVecScale(headVec, source, -3.0f);
    scale = (g_weapon_l00_table + g_item_slot_to_record[0x2C])->scale;
    pointCount = coll_process_hit(g_weapon_l00_table[g_item_slot_to_record[0x1B]].flag != 0 ? 3.0f : 4.0f, (int)(obj + 0x10), 0x10, (int)obj, 0);
    *(TI128 *)startPos = *(TI128 *)(obj + 0x10);
    moby_queue_knockback_for_nodes(obj, startPos, g_area_hit_targets, pointCount, flags, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}
