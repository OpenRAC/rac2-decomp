#include "names.h"
/* func_L05_00367340 is the level 5 copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x00367350, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 05:0029D4F0 points there.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l05_source_entries[];
extern char g_menu_l05_item_callback[];
extern InitEntry12 g_menu_l05_item_list_2[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_l05_item_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l05_state;

/* Fills the level's menu list from the global item list and sets the highlighted row to the currently selected item. */
int menu_fill_item_list(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l05_item_list_2[i].kind = 3;
        g_menu_l05_item_list_2[i].callback = g_menu_l05_item_callback;
        g_menu_l05_item_list_2[i].id = g_menu_l05_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l05_item_list_2[i].value = g_menu_l05_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_menu_l05_item_list;
    g_menu_l05_item_list_2[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_menu_l05_item_list[++i]) {
        if (g_menu_l05_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
