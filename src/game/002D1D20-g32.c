#include "names.h"
/* func_002D1D20 in its own unit, a sibling of func_002D2018: the cursor goes through $gp, so the
   file is compiled at -G32 (config/cflags.txt). The text table's address is built by one lui/addiu
   pair in one register, the assembler's la macro, so it is declared MACRO_ADDR. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int g_page_viewer_long_cursor __attribute__((sda));
extern int g_page_viewer_long_index[];
extern int g_page_viewer_long_item[];
extern short g_page_viewer_icon_table[] MACRO_ADDR;

/* Handles left and right on the 18-page viewer and shows the page for the current index. */
int page_viewer_handle_input_long(void)
{
    int result = 0;
    int flags = g_pad_state.flags;

    if (flags & 0x10) {
        int value;
        int return_code;
        g_page_viewer_long_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            return_code = -1;
            goto finish;
        }
        return_code = 0;
finish:
        return return_code;
    }
    if (flags & 0x900) {
        g_page_viewer_long_cursor = 0;
        result = 1;
    } else if (flags & 0x8000) {
        if (g_page_viewer_long_cursor > 0)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (--g_page_viewer_long_cursor < 0)
            g_page_viewer_long_cursor = 0;
    } else if (flags & 0x2000) {
        if (g_page_viewer_long_cursor < 17)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (++g_page_viewer_long_cursor > 17)
            g_page_viewer_long_cursor = 17;
    }
    g_page_viewer_long_index[0] = g_page_viewer_long_cursor;
    g_page_viewer_long_item[0] = g_page_viewer_icon_table[g_page_viewer_long_cursor];
    return result;
}
