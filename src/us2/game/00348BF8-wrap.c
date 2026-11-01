#include "include_asm.h"

typedef unsigned char u8;
extern int func_002E5E58(int, int, void *);
typedef struct {
    u8 pad00[0x60];
    int selection;
    u8 pad54[8];
    void *entries[16];
    u8 pad9C[0x14];
    int count;
} SelectionMenu;
static inline void WrapLow(int *index, int last)
{
    if (*index < 0)
        *index = last;
}

int func_US2_00348CB8(SelectionMenu *object, int flags)
{
    int direction = 0;
    int last;
    int original;

    if (flags & 0x1000) {
        direction = -1;
    } else if (flags & 0x4000) {
        direction = 1;
    } else if (flags & 0x40) {
        if (object->entries[object->selection] != 0)
            return 1;
    }
    if (direction != 0) {
        original = object->selection;
        func_002E5E58(3, 0, 0);
        last = object->count - 1;
        do {
            int index = object->selection + direction;
            int wrapped;
            if (last < index)
                index = 0;
            wrapped = index;
            WrapLow(&wrapped, last);
            object->selection = wrapped;
        } while (object->entries[object->selection] == 0 && original != object->selection);
    }
    return 0;
}
