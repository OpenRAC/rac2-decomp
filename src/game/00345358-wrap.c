#include "names.h"
/* Menu selection stepping: up or down moves through the entries, wrapping at both ends and
   skipping empty ones. Its own unit: the low wrap goes through a pointer, so its branch only
   becomes a conditional move after the loop pass, which leaves retail's -1 inside the loop. That
   needs the jump pass after gcse gone (-frac2-gcse-unsplit-edges). The padding nop at the loop
   head follows from it. */
typedef unsigned char u8;
extern int func_002E5E58(int, int, void *);

typedef struct {
    u8 pad00[0x50];
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

/* Moves the menu selection up or down, wrapping around and skipping empty entries. */
int func_00347F80(SelectionMenu *object, int flags)
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
        PlaySoundFromGlobalBank(3, 0, 0);
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
