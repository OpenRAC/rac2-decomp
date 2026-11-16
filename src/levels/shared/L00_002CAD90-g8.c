#include "common.h"

typedef struct {
    short key;
    unsigned char a;
    unsigned char b;
} TableEntry;

extern TableEntry g_linked_anim_pair_table_b[] SDATA(D_L00_001A7D60);
extern TableEntry g_linked_anim_pair_table_a[] SDATA(D_L00_001A7D48);
extern TableEntry g_linked_anim_pair_table_c[] SDATA(D_L00_001A7D78);

extern int hero_slot_item_id(int);

/* picks the table for the item in hero slot 3 and, for the entry whose byte a equals id, writes its key to out and returns 1; otherwise writes 0 and returns 0 */
int FindSlotTableKey(int id, int *out)
{
    TableEntry *table = 0;
    int index;

    if (hero_slot_item_id(3) == 2)
        table = g_linked_anim_pair_table_b;
    else if (hero_slot_item_id(3) == 3)
        table = g_linked_anim_pair_table_a;
    else if ((hero_slot_item_id(3) ^ 4) != 0)
        table = 0;
    else
        table = g_linked_anim_pair_table_c;

    if (table) {
        for (index = 0; table[index].key != -1; index++) {
            if (id == table[index].a) {
                *out = table[index].key;
                return 1;
            }
        }
    }
    *out = 0;
    return 0;
}
