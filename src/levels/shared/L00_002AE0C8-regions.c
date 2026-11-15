#include "common.h"

extern unsigned char *D_L00_001B1B00[] __attribute__((sda));
/* Only the two entry words and the byte count are needed by the reset. */
typedef struct {
    int firstEntry;
    unsigned char count;
    unsigned char pad[3];
    int secondEntry;
} RegionMembers;
extern RegionMembers **D_L00_001B1AFC[] __attribute__((sda));
extern unsigned char *D_L00_001B1E9C[] __attribute__((sda));
extern short D_L00_001B1FF0[] __attribute__((sda));
extern short D_L00_001B2030[] __attribute__((sda));
extern unsigned char *D_L00_001C57E8[];
extern int D_L00_001A9024[] __attribute__((sda));
extern unsigned char g_hero_state[];
extern int FastDecTimer(short *);
extern int coll_point_inside_region(void *, int);
extern void AppendIndexedObjectRecord(unsigned char *, int, int);

/* Rebuild each live region's resident/object membership lists for this frame. */
void RebuildRegionObjectMembership(void) {
    int region, index;
    unsigned char *object;
    /* Match the integer table-address arithmetic in func_L00_003296C0. */
    for (region = 0; region < *(int *)D_L00_001B1B00[0]; ++region) {
        RegionMembers **members = (RegionMembers **)(region * 4 + (unsigned int)D_L00_001B1AFC[0]);
        (*members)->firstEntry = 0;
        (*members)->secondEntry = 0;
        (*members)->count = 0;
        if (FastDecTimer((short *)(region * 0x30 + (unsigned int)D_L00_001B1B00[0] + 0x3A))) continue;
        if (coll_point_inside_region(g_hero_state + 0x80, region))
            AppendIndexedObjectRecord(*(unsigned char **)(g_hero_state + 0x2290), region, 1);
        for (index = 1; index <= D_L00_001B1FF0[0]; ++index) {
            object = D_L00_001B1E9C[0] + (D_L00_001B1FF0[index] << 8);
            if (object && *(short *)(object + 0xAA) == 0xCB /* Decoy */ &&
                object[0x20] != 0xFE && object[0x20] != 0xFD && object[0x20] == 3) {
                if (coll_point_inside_region(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 2);
            }
        }
        {
            int dynamicIndex;
            for (dynamicIndex = 0; dynamicIndex < D_L00_001A9024[0]; ++dynamicIndex) {
                if (coll_point_inside_region(D_L00_001C57E8[dynamicIndex] + 0x10, region))
                    AppendIndexedObjectRecord(D_L00_001C57E8[dynamicIndex], region, 3);
            }
        }
        for (index = 1; index <= D_L00_001B2030[0]; ++index) {
            object = D_L00_001B1E9C[0] + (D_L00_001B2030[index] << 8);
            if (object && *(short *)(object + 0xAA) == 0xEB0 /* Dark Sheep */ &&
                object[0x20] != 0xFE && object[0x20] != 0xFD) {
                if (coll_point_inside_region(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 4);
            }
        }
    }
    D_L00_001A9024[0] = 0;
}
