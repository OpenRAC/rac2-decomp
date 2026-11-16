#include "names.h"
/* func_L14_0035F510 is the level 14 copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x0035F520, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 14:0028D180 points there.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l14_source_entries[];
extern char g_menu_l14_entry_callback[];
extern InitEntry12 g_menu_selection_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_selection_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l14_state;

/* Fills the menu entry list from the table of unlocked ids, then finds which entry is currently selected and stores its index. */
int menu_fill_selection_entries(char *menu) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_selection_entries[i].kind = 3;
        g_menu_selection_entries[i].callback = g_menu_l14_entry_callback;
        g_menu_selection_entries[i].id = g_menu_l14_source_entries[g_menu_entry_ids[i]].id;
        g_menu_selection_entries[i].value = g_menu_l14_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_menu_selection_list;
    g_menu_selection_entries[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_menu_selection_list[++i]) {
        if (g_menu_l14_state.selected == entry) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}
