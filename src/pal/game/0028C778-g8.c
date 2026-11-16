#include "include_asm.h"
#include "names.h"

extern int g_radial_slot_counts_data[2] __attribute__((sda));
extern int g_radial_menu_page_index __attribute__((sda));
extern int g_radial_slot_count[] __attribute__((sda));

/* Resets the round weapon-select menu: eight slots, first page, and the panel size (PAL: 25 instead of 30). */
void weapon_wheel_init_pal(void *menu)
{
    g_radial_slot_count[0] = 8;
    g_radial_slot_count[1] = (int)g_radial_slot_counts_data;
    *(short *)((char *)menu + 0x48) = 0;
    *(short *)((char *)menu + 0x4A) = 0;
    *(int *)((char *)menu + 0x58) = 0xD2;
    *(int *)((char *)menu + 0x5C) = 0xC8;
    *(int *)((char *)menu + 0x74) = -2;
    *(int *)((char *)menu + 0x78) = 0x19;
    g_radial_menu_page_index = 0;
}
