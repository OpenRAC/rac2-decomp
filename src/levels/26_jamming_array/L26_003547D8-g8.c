#include "names.h"
/* func_L26_003547D8 is level 26's copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x003547E8, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 26:00286D80 points there.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l26_source_entries[];
extern char g_menu_l26_entry_callback[];
extern InitEntry12 g_menu_l26_init_entries[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_l26_entry_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l26_state;

/* Fills the menu entry table from the list of unlocked items, then finds which one is currently
   selected and stores its position in the object. */
int menu_fill_entry_table(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l26_init_entries[i].kind = 3;
        g_menu_l26_init_entries[i].callback = g_menu_l26_entry_callback;
        g_menu_l26_init_entries[i].id = g_menu_l26_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l26_init_entries[i].value = g_menu_l26_source_entries[g_menu_entry_ids[i]].value;
    }
    list = g_menu_l26_entry_list;
    g_menu_l26_init_entries[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = g_menu_l26_entry_list[++i]) {
        if (g_menu_l26_state.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
