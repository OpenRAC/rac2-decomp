#include "names.h"
/* func_L04_00378838, in levels 4 and 10, is a copy of func_L00_00354DF8 (L00_002FC7A8-g8.c)
 * with the levels' own tables, named here by level 4's addresses. Its catalogue entry starts
 * at 0x00378848 in level 4 and 0x00369160 in level 10, after the previous body's 16-byte tail
 * (FUNCTION_ENTRY_OFFSETS); the words at 04:0029FE90 and 10:0029F960 point there.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l04_source_entries[];
extern char g_menu_l04_entry_callback[];
extern InitEntry12 g_menu_l04_entry_list[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_entry_id_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l04_state;

/* Fills the menu entry list from the level tables and selects the entry that is current. */
int menu_l04_build_entry_list(char *menu) {
    int i, entry;
    int *id_list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l04_entry_list[i].kind = 3;
        g_menu_l04_entry_list[i].callback = g_menu_l04_entry_callback;
        g_menu_l04_entry_list[i].id = g_menu_l04_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l04_entry_list[i].value = g_menu_l04_source_entries[g_menu_entry_ids[i]].value;
    }
    id_list = g_menu_entry_id_list;
    g_menu_l04_entry_list[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, entry = id_list[0]; entry; entry = g_menu_entry_id_list[++i]) {
        if (g_menu_l04_state.selected == entry) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}
