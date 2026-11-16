#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l00_source_entries[];
extern char g_menu_l00_entry_callback[];
extern InitEntry12 g_menu_l00_entry_table[];
extern int * volatile g_menu_l00_item_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_format_root;

/* Fills the menu entry table from the entry ids and selects the entry matching the current
   choice (USA v2.00). Always returns 0. */
int menu_l16_fill_entries_from_item_list_us2(char *moby) {
    int i, menu_entry;
    int *items;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l00_entry_table[i].kind = 3;
        g_menu_l00_entry_table[i].callback = g_menu_l00_entry_callback;
        g_menu_l00_entry_table[i].id = g_menu_l00_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l00_entry_table[i].value = g_menu_l00_source_entries[g_menu_entry_ids[i]].value;
    }
    items = g_menu_l00_item_list;
    g_menu_l00_entry_table[i].id = 0;
    *(int *)(moby + 0x40) = 0;
    *(unsigned int *)(moby + 0x30) |= 0x8000;
    for (i = 0, menu_entry = items[0]; menu_entry; menu_entry = g_menu_l00_item_list[++i]) {
        if (g_format_root.selected == menu_entry) {
            *(int *)(moby + 0x40) = i;
            break;
        }
    }
    return 0;
}
