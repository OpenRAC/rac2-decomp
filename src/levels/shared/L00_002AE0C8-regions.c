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
extern unsigned char D_00189E20[];
extern int func_00282978(short *);
extern int func_L00_00329520(void *, int);
extern void func_L00_003296C0(unsigned char *, int, int);

/* Rebuild each live region's resident/object membership lists for this frame. */
void func_L00_002AE0C8(void) {
    int region, index;
    unsigned char *object;
    /* Match the integer table-address arithmetic in AppendIndexedObjectRecord. */
    for (region = 0; region < *(int *)D_L00_001B1B00[0]; ++region) {
        RegionMembers **members = (RegionMembers **)(region * 4 + (unsigned int)D_L00_001B1AFC[0]);
        (*members)->firstEntry = 0;
        (*members)->secondEntry = 0;
        (*members)->count = 0;
        if (FastDecTimer((short *)(region * 0x30 + (unsigned int)D_L00_001B1B00[0] + 0x3A))) continue;
        if (func_L00_00329520(D_00189E20 + 0x80, region))
            AppendIndexedObjectRecord(*(unsigned char **)(D_00189E20 + 0x2290), region, 1);
        for (index = 1; index <= D_L00_001B1FF0[0]; ++index) {
            object = D_L00_001B1E9C[0] + (D_L00_001B1FF0[index] << 8);
            if (object && *(short *)(object + 0xAA) == 0xCB &&
                object[0x20] != 0xFE && object[0x20] != 0xFD && object[0x20] == 3) {
                if (func_L00_00329520(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 2);
            }
        }
        {
            int dynamicIndex;
            for (dynamicIndex = 0; dynamicIndex < D_L00_001A9024[0]; ++dynamicIndex) {
                if (func_L00_00329520(D_L00_001C57E8[dynamicIndex] + 0x10, region))
                    AppendIndexedObjectRecord(D_L00_001C57E8[dynamicIndex], region, 3);
            }
        }
        for (index = 1; index <= D_L00_001B2030[0]; ++index) {
            object = D_L00_001B1E9C[0] + (D_L00_001B2030[index] << 8);
            if (object && *(short *)(object + 0xAA) == 0xEB0 &&
                object[0x20] != 0xFE && object[0x20] != 0xFD) {
                if (func_L00_00329520(object + 0x10, region))
                    AppendIndexedObjectRecord(object, region, 4);
            }
        }
    }
    D_L00_001A9024[0] = 0;
}
