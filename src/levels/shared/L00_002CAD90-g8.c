#include "common.h"

typedef struct {
    short key;
    unsigned char a;
    unsigned char b;
} TableEntry;

extern TableEntry D_L00_001A7D60[] SDATA(D_L00_001A7D60);
extern TableEntry D_L00_001A7D48[] SDATA(D_L00_001A7D48);
extern TableEntry D_L00_001A7D78[] SDATA(D_L00_001A7D78);

extern int func_L00_002ADEA0(int);

/* picks the table for the item in hero slot 3 and, for the entry whose byte a equals id, writes its key to out and returns 1; otherwise writes 0 and returns 0 */
int func_L00_002D1B70(int id, int *out)
{
    TableEntry *table = 0;
    int index;

    if (hero_slot_item_id(3) == 2)
        table = D_L00_001A7D60;
    else if (hero_slot_item_id(3) == 3)
        table = D_L00_001A7D48;
    else if ((hero_slot_item_id(3) ^ 4) != 0)
        table = 0;
    else
        table = D_L00_001A7D78;

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
