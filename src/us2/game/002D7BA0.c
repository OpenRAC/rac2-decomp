#include "include_asm.h"
#include "names.h"

extern int menu_update_entry_states(int *);
extern int menu_list_active_entries(unsigned int, unsigned int, unsigned int, int);
extern int g_selected_map_index;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 g_page_preview;
extern int g_level_page_entry_value[];

/* Sets up a preview of the selected entry by loading its two data words from the tables. */
int menu_preview_entry_init_us2(int *menu)
{
    menu_update_entry_states(menu);
    *(int *)((char *)menu + 0xA0) = menu_list_active_entries(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)menu + 0x30;
        int index = g_selected_map_index;

        if (*(int *)(base + (index << 2)) != -1) {
            g_page_preview.f3C = -0x240;
            g_page_preview.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)g_level_page_entry_value = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)menu + 0xA4) = 0;
    return 0;
}
