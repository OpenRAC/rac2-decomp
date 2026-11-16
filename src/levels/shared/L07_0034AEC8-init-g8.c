#include "names.h"
/* Build the menu rows in level order and select the current owner entry.
 * The +4 row field holds the level menu-data descriptor.
 * The list-pointer word is reloaded on every search step, as in retail.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *payload; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_level_select_source_entries[];
extern char g_level_select_payload[];
extern InitEntry12 g_level_select_init_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_level_l07_select_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l07_state;

/* Fills the level menu rows from the level order list and selects the row for the current level. */
int menu_l07_init_level_select_rows(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_level_select_init_entries[i].kind = 3;
        g_level_select_init_entries[i].payload = g_level_select_payload;
        g_level_select_init_entries[i].id = g_level_select_source_entries[g_menu_entry_ids[i]].id;
        g_level_select_init_entries[i].value = g_level_select_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_level_l07_select_list;
    g_level_select_init_entries[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_level_l07_select_list[++i]) {
        if (g_menu_l07_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
