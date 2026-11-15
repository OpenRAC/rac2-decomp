#include "common.h"

extern unsigned char *D_L00_001B2514 __attribute__((sda));
extern unsigned char *D_L00_001B2518 __attribute__((sda));
extern unsigned char *D_L00_001B23F8 __attribute__((sda));
extern unsigned char *D_L00_001B23FC __attribute__((sda));
extern unsigned char *D_L00_001B1E9C __attribute__((sda));
extern unsigned char *D_L00_001B1EA0 __attribute__((sda));
extern int level_find_first_accepted_entry(void *);

/* Shows or hides each object in three lists depending on whether it matches the selected item. */
void level_update_object_visibility(int selected)
{
    unsigned char *entry;
    for (entry = D_L00_001B2514; entry != D_L00_001B2518; entry += 0x20) {
        if (level_find_first_accepted_entry(entry) != selected)
            entry[0x1E] |= 4;
        else
            entry[0x1E] &= 0xFB;
    }
    for (entry = D_L00_001B23F8; entry != D_L00_001B23FC; entry += 0x20) {
        if (level_find_first_accepted_entry(entry) != selected)
            entry[0x16] |= 1;
        else
            entry[0x16] &= 0xFE;
    }
    for (entry = D_L00_001B1E9C; entry != D_L00_001B1EA0; entry += 0x100) {
        if (*(s16 *)(entry + 0xAA) != 0) {
            if (level_find_first_accepted_entry(entry + 0x10) != selected)
                *(u16 *)(entry + 0x34) |= 0x80;
            else
                *(u16 *)(entry + 0x34) &= 0xFF7F;
        }
    }
}
