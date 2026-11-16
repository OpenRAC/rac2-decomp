#include "names.h"
/* Own unit: the hero block is declared in .data here, which the neighbours in
   L19_002A88C8.c do not share. */
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; } Hero19;
extern char g_hero_state[] __attribute__((section(".data")));
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_item_l19_record_table[];
extern int hero_slot_item_id(int);

/* the hero's animation id for its current state: 13 in state 4, the 0xE0-byte table entry's
   value for the selected slot when enabled and idle, 81 in mode 1, else 0 */
/* Chooses which animation the hero should play right now. */
int hero_get_anim_id(int enabled)
{
    unsigned char *entry;

    if (((Hero19 *)g_hero_state)->b[0x22B4] == 4)
        return 13;
    if (enabled && ((Hero19 *)g_hero_state)->b[0x22BA] && ((Hero19 *)g_hero_state)->h[0x24EC / 2] == 0) {
        entry = g_item_l19_record_table + g_item_slot_to_record[hero_slot_item_id(0)] * 0xE0;
        return *(int *)(entry + 0x28);
    }
    if (((Hero19 *)g_hero_state)->i[0x24CC / 4] == 1)
        return 81;
    return 0;
}
