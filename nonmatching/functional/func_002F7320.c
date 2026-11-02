/* functional: high. Written from the assembly: a lookup in a table of 56 rows of a key and three values. Row key 0 ends the
 * table. Whether VALUE is the row's value number INDEX. Past 56 rows without the key, retail reads row 56, as this does. */
#include "common.h"

typedef struct {
    int key;
    int value[3];
} Row;

extern Row D_00264E80[];

int func_002F7320(int value, int key, int index)
{
    Row *row;
    int i;

    for (i = 0; i < 56; i++) {
        if (D_00264E80[i].key == 0) {
            return 0;
        }
        if (D_00264E80[i].key == key) {
            break;
        }
    }
    row = &D_00264E80[i];
    if (row->key == 0) {
        return 0;
    }
    return row->value[index] == value;
}
