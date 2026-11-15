#include "include_asm.h"
/* Returns the index of the selector entry whose key matches, or -1. */
typedef struct { int unk00; int key; int unk08; int unk0C; } SelectorEntry;

typedef struct { char pad00[0x2C]; int count; } SelectorCount;

extern SelectorCount ref_00288F48_00;
extern SelectorEntry *ref_00288F48_01 __attribute__((sda));

/* Returns the index of the entry with the given key in the help table, or -1 if there is none. */
int func_00288F48(int key)
{
    int found = -1;
    int i;

    for (i = 0; i < ref_00288F48_00.count; i++) {
        if (ref_00288F48_01[i].key == key) {
            found = i;
            break;
        }
    }
    return found;
}
