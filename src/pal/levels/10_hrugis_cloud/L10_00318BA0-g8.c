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

/* Fills the menu entry table from the list of entry ids and selects the entry that matches the current value (PAL copy of menu_fill_entries_from_item_list). */
int menu_fill_entries_from_item_list_pal(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l00_entry_table[i].kind = 3;
        g_menu_l00_entry_table[i].callback = g_menu_l00_entry_callback;
        g_menu_l00_entry_table[i].id = g_menu_l00_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l00_entry_table[i].value = g_menu_l00_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_menu_l00_item_list;
    g_menu_l00_entry_table[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_menu_l00_item_list[++i]) {
        if (g_format_root.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
