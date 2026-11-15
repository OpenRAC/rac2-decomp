/* func_L00_002D1DA0 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

typedef struct {
    short key;
    unsigned char a;
    unsigned char b;
} Elem;

extern Elem D_L00_001A7D60 __attribute__((sda));
extern Elem D_L00_001A7D48 __attribute__((sda));
extern Elem D_L00_001A7D78 __attribute__((sda));

extern int func_L00_002A4EF0(int);
extern int func_L00_002ADEA0(int);
extern int func_002A7820(int, int);

/* Looks up the animation pair for a sequence in the table for the current mode and picks one match at random. Returns 1 when one was found. */
int func_L00_002D1DA0(int seq, int *outA, int *outB)
{
    int matches[20];
    Elem *table;
    int count = 0;
    int idx;
    int key;

    key = ReturnArgument_L00(seq);
    if (hero_slot_item_id(3) == 2) {
        table = &D_L00_001A7D60;
    } else if (hero_slot_item_id(3) == 3) {
        table = &D_L00_001A7D48;
    } else if ((hero_slot_item_id(3) ^ 4) != 0) {
        table = 0;
    } else {
        table = &D_L00_001A7D78;
    }
    if (table != 0) {
        for (idx = 0; table[idx].key != -1; idx++) {
            if (key == table[idx].key) {
                matches[count] = idx;
                count++;
            }
        }
    }
    idx = count - 1;
    if (count != 0) {
        int pick = RandomIntRange(0, idx);
        *outA = table[matches[pick]].a;
        *outB = table[matches[pick]].b;
        return 1;
    }
    *outA = 1;
    return 0;
}
