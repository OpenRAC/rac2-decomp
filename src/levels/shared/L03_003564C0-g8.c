#include "names.h"
/* Initialization-table relative of func_L00_00354DF8. The measured entry
 * correction leaves the preceding function's tail in assembly. */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l03_source_entries[];
extern char g_menu_choice_callback[];
extern InitEntry12 g_menu_choice_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_choice_id_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_choice_menu_state;

/* Fills the menu choice table from the list of unlocked entries and puts the cursor on the one currently selected. */
int menu_fill_choice_table(char *menu) {
    int i, value;
    int *id_list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_choice_entries[i].kind = 3;
        g_menu_choice_entries[i].callback = g_menu_choice_callback;
        g_menu_choice_entries[i].id = g_menu_l03_source_entries[g_menu_entry_ids[i]].id;
        g_menu_choice_entries[i].value = g_menu_l03_source_entries[g_menu_entry_ids[i]].value;
    }
    id_list = g_choice_id_list;
    g_menu_choice_entries[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, value = id_list[0]; value; value = g_choice_id_list[++i]) {
        if (g_choice_menu_state.selected == value) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}
