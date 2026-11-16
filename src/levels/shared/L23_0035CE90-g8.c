#include "names.h"
/* Initialization-table relative of func_L00_00354DF8. The measured current
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l23_source_entries[];
extern char g_menu_init_callback_data[];
extern InitEntry12 g_menu_l23_init_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_select_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l23_state;

/* Fills the menu entry table from the list of item ids, then finds which entry is currently selected and stores its index in the menu object. */
int menu_init_entry_table(char *obj) {
    int i, current;
    int *select_list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l23_init_entries[i].kind = 3;
        g_menu_l23_init_entries[i].callback = g_menu_init_callback_data;
        g_menu_l23_init_entries[i].id = g_menu_l23_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l23_init_entries[i].value = g_menu_l23_source_entries[g_menu_entry_ids[i]].value;
    }
    select_list = g_menu_select_list;
    g_menu_l23_init_entries[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, current = select_list[0]; current; current = g_menu_select_list[++i]) {
        if (g_menu_l23_state.selected == current) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
