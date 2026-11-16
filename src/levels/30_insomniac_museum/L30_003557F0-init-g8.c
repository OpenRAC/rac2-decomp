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
extern SourceEntry12 g_museum_source_entries[];
extern char g_museum_row_payload[];
extern InitEntry12 g_museum_menu_rows[];
/* Reloaded at each search step in retail. */
extern int * volatile g_museum_row_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l30_state;

/* Fills in the museum menu entries in order and selects the one that matches the current choice. */
int menu_build_museum_rows(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_museum_menu_rows[i].kind = 3;
        g_museum_menu_rows[i].payload = g_museum_row_payload;
        g_museum_menu_rows[i].id = g_museum_source_entries[g_menu_entry_ids[i]].id;
        g_museum_menu_rows[i].value = g_museum_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_museum_row_list;
    g_museum_menu_rows[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_museum_row_list[++i]) {
        if (g_menu_l30_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
