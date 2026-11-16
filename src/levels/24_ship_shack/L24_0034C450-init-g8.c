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
extern SourceEntry12 g_menu_l24_source_entries[];
extern char g_menu_entry_payload[];
extern InitEntry12 g_menu_l24_init_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_owner_entry_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l24_state;

/* Fills the menu rows from the level list and selects the entry that matches the current owner. */
int menu_build_owner_rows(char *menu) {
    int i, current_entry;
    int *owner_list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l24_init_entries[i].kind = 3;
        g_menu_l24_init_entries[i].payload = g_menu_entry_payload;
        g_menu_l24_init_entries[i].id = g_menu_l24_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l24_init_entries[i].value = g_menu_l24_source_entries[g_menu_entry_ids[i]].value;
    }
    owner_list = g_owner_entry_list;
    g_menu_l24_init_entries[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, current_entry = owner_list[0]; current_entry; current_entry = g_owner_entry_list[++i]) {
        if (g_menu_l24_state.selected == current_entry) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}
