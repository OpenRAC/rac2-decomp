#include "common.h"

extern unsigned char *g_region_group_table[] __attribute__((sda));
/* Only the two entry words and the byte count are needed by the reset. */
typedef struct {
    int firstEntry;
    unsigned char count;
    unsigned char pad[3];
    int secondEntry;
} RegionMembers;
extern RegionMembers **g_region_members_table[] __attribute__((sda));
extern unsigned char *g_moby_array_base[] __attribute__((sda));
extern short g_decoy_moby_index_list[] __attribute__((sda));
extern short g_dark_sheep_moby_index_list[] __attribute__((sda));
extern unsigned char *g_region_object_table[];
extern int g_dynamic_region_count[] __attribute__((sda));
extern unsigned char g_hero_state[];
extern int FastDecTimer(short *);
extern int coll_point_inside_region(void *, int);
extern void AppendIndexedObjectRecord(unsigned char *, int, int);

/* Rebuild each live region's resident/object membership lists for this frame. */
void RebuildRegionObjectMembership(void) {
    int region, index;
    unsigned char *object;
    /* Match the integer table-address arithmetic in func_L00_003296C0. */
    for (region = 0; region < *(int *)g_region_group_table[0]; ++region) {
        RegionMembers **members = (RegionMembers **)(region * 4 + (unsigned int)g_region_members_table[0]);
        (*members)->firstEntry = 0;
        (*members)->secondEntry = 0;
        (*members)->count = 0;
        if (FastDecTimer((short *)(region * 0x30 + (unsigned int)g_region_group_table[0] + 0x3A))) continue;
        if (coll_point_inside_region(g_hero_state + 0x80, region))
            AppendIndexedObjectRecord(*(unsigned char **)(g_hero_state + 0x2290), region, 1);
        for (index = 1; index <= g_decoy_moby_index_list[0]; ++index) {
            object = g_moby_array_base[0] + (g_decoy_moby_index_list[index] << 8);
            if (object && *(short *)(object + 0xAA) == MOBY_CLASS_DECOY &&
                object[0x20] != 0xFE && object[0x20] != 0xFD && object[0x20] == 3) {
                if (coll_point_inside_region(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 2);
            }
        }
        {
            int dynamicIndex;
            for (dynamicIndex = 0; dynamicIndex < g_dynamic_region_count[0]; ++dynamicIndex) {
                if (coll_point_inside_region(g_region_object_table[dynamicIndex] + 0x10, region))
                    AppendIndexedObjectRecord(g_region_object_table[dynamicIndex], region, 3);
            }
        }
        for (index = 1; index <= g_dark_sheep_moby_index_list[0]; ++index) {
            object = g_moby_array_base[0] + (g_dark_sheep_moby_index_list[index] << 8);
            if (object && *(short *)(object + 0xAA) == MOBY_CLASS_DARK_SHEEP &&
                object[0x20] != 0xFE && object[0x20] != 0xFD) {
                if (coll_point_inside_region(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 4);
            }
        }
    }
    g_dynamic_region_count[0] = 0;
}
