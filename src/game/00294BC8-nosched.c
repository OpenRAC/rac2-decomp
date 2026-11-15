#include "names.h"
/* Functions of 00294BC8.c that retail built without the first scheduling pass.

   Without it the two halves of the table's address stay ahead of the masked
   index when local-alloc ranks its quantities, so the index gets $v0 and the
   address $v1. */

extern char D_0014B540_1[];

typedef struct {
    int unk0;
    int unk4;
} TableSlot;

typedef struct {
    char reserved[0x14F0];
    TableSlot set[28];
    TableSlot clear[28];
} TableBlock;

/* Whether the 28-entry slot table selected by flag 0x100 has a positive value at the low byte's index. */
int map_is_entry_available(int map_id)
{
    if ((map_id & 0x100) == 0) {
        map_id = ((TableBlock *)D_0014B540_1)->clear[map_id & 0xFF].unk4;
        return map_id > 0;
    }
    map_id = ((TableBlock *)D_0014B540_1)->set[map_id & 0xFF].unk4;
    return map_id > 0;
}
