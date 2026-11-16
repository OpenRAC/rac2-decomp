#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int snd_play_from_global_bank(int, int, void *);
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

/* Moves the list menu's selection one entry up or down on the d-pad, wrapping at both ends and skipping empty
   entries; returns 1 when the select button is pressed on a filled entry. */
int list_menu_update_selection_us2(SelectionMenu *object, int flags)
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
        snd_play_from_global_bank(3, 0, 0);
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
