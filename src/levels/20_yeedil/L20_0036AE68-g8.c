#include "names.h"
/* func_L20_0036AE68 is the level 20 copy of func_L00_00354DF8 (L00_002FC7A8-g8.c), with the
 * level's own tables. Its catalogue entry starts at 0x0036AE78, after the previous body's
 * 16-byte tail (FUNCTION_ENTRY_OFFSETS); the word at 20:00292390 points there.
 */
#include "include_asm.h"
#include "names.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int g_menu_entry_ids[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 g_menu_l20_source_entries[];
extern char g_menu_l20_entry_callback[];
extern InitEntry12 g_menu_l20_entry_list_2[];
/* Reloaded at each search step in retail. */
extern int * volatile g_menu_l20_entry_list __attribute__((sda));
extern struct { char pad[0x230]; int selected; } g_menu_l20_state;

/* Fills the menu entry list from a table of ids, then finds which entry is currently picked and stores its position in the menu. */
int menu_l20_build_entry_list(char *menu) {
    int i, item;
    int *item_list;
    for (i = 0; i < 28 && g_menu_entry_ids[i]; i++) {
        g_menu_l20_entry_list_2[i].kind = 3;
        g_menu_l20_entry_list_2[i].callback = g_menu_l20_entry_callback;
        g_menu_l20_entry_list_2[i].id = g_menu_l20_source_entries[g_menu_entry_ids[i]].id;
        g_menu_l20_entry_list_2[i].value = g_menu_l20_source_entries[g_menu_entry_ids[i]].value;
    }
    item_list = g_menu_l20_entry_list;
    g_menu_l20_entry_list_2[i].id = 0;
    *(int *)(menu + 0x40) = 0;
    *(unsigned int *)(menu + 0x30) |= 0x8000;
    for (i = 0, item = item_list[0]; item; item = g_menu_l20_entry_list[++i]) {
        if (g_menu_l20_state.selected == item) {
            *(int *)(menu + 0x40) = i;
            break;
        }
    }
    return 0;
}
