#include "common.h"

typedef struct {
    unsigned short id, kind;
    void *descriptor;
    unsigned short value, reserved;
} MenuEntry;
typedef struct { unsigned short id, reserved, value; char rest[6]; } SourceEntry;
extern int g_menu_entry_ids[];
extern SourceEntry g_menu_source_entries[];
extern char g_level_page_root[];
extern MenuEntry g_menu_entry_table[];
/* Retail rereads the list pointer at each search step. */
extern int * volatile g_map_select_list __attribute__((sda));
extern struct { char unknown00[0x230]; int selected; } g_map_overlay_state;

/* Builds the menu entries from a table and puts the cursor on the entry matching the current selection. */
int menu_entries_init_from_table(char *object)
{
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_entry_table[i].kind = 3;
        g_menu_entry_table[i].descriptor = g_level_page_root;
        g_menu_entry_table[i].id = g_menu_source_entries[g_menu_entry_ids[i]].id;
        g_menu_entry_table[i].value = g_menu_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_map_select_list;
    g_menu_entry_table[i].id = 0;
    *(int *)(object + 0x40) = 0;
    *(unsigned int *)(object + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_map_select_list[++i]) {
        if (g_map_overlay_state.selected == entry) {
            *(int *)(object + 0x40) = i;
            break;
        }
    }
    return 0;
}
