#include "names.h"
/* Initialization-table relative of func_L00_00354DF8. The measured entry
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l01_source_entries[];
extern char g_menu_l01_item_callback[];
extern InitEntry12 g_menu_l01_init_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_map_id_table __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l01_state;

/* Fills a menu list from a table of item ids and marks which entry is currently selected. */
int menu_build_item_list(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l01_init_entries[i].kind = 3;
        g_menu_l01_init_entries[i].callback = g_menu_l01_item_callback;
        g_menu_l01_init_entries[i].id = g_menu_l01_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l01_init_entries[i].value = g_menu_l01_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_map_id_table;
    g_menu_l01_init_entries[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_map_id_table[++i]) {
        if (g_menu_l01_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
