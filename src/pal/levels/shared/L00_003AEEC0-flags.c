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
extern int func_PAL_0032F0B8(int, int, int);
extern void moby_queue_knockback_for_nodes(void *, void *, int *, int, int, int, int, int, float, float, float);
extern unsigned char g_item_slot_to_record[];
extern Entry262570b g_weapon_l00_table[];
extern int g_area_hit_targets[];
typedef struct {
    float head[4];
    float vec[4];
    int arg;
} Trail_3AC8E8;

void func_PAL_L00_003B00B8(char *a0, void *a1, int a2)
{
    Trail_3AC8E8 s;
    Entry262570b *e;
    float scale;
    int count;
    int i;

    s.arg = a2;
    FastVecScale(s.head, a1, -3.0f);
    e = &g_weapon_l00_table[g_item_slot_to_record[0x1B]];
    scale = e->scale;
    count = coll_process_hit(e->flag != 0 ? 3.0f : 4.0f, (int)(a0 + 0x10), 0x10, (int)a0, 0);
    for (i = 0; i < count; i++) {
        if ((g_weapon_l00_table + g_item_slot_to_record[0x1B])->flag != 0)
            func_PAL_0032F0B8(g_area_hit_targets[i], 0x45, *(int *)(a0 + 0xB8));
        else
            func_PAL_0032F0B8(g_area_hit_targets[i], 0x1B, *(int *)(a0 + 0xB8));
    }
    *(TI128 *)s.vec = *(TI128 *)(a0 + 0x10);
    moby_queue_knockback_for_nodes(a0, s.vec, g_area_hit_targets, count, s.arg, 0x810000, 3, 1, scale, 1.0f, 1.0f);
}
