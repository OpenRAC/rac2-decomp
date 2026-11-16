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
extern SourceEntry12 g_level_menu_sources[];
extern char g_level_menu_payload[];
extern InitEntry12 g_level_menu_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_level_list_table __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l13_state;

/* Fills in the level menu list from the unlocked levels and selects the current one. */
int menu_build_level_list(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_level_menu_entries[i].kind = 3;
        g_level_menu_entries[i].payload = g_level_menu_payload;
        g_level_menu_entries[i].id = g_level_menu_sources[g_menu_entry_ids[i]].id;
        g_level_menu_entries[i].value = g_level_menu_sources[g_menu_entry_ids[i]].value;
    }
    list = g_level_list_table;
    g_level_menu_entries[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_level_list_table[++i]) {
        if (g_menu_l13_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
