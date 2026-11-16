/* func_002D2018 in its own unit, a sibling of func_002D01D0: the cursor goes through $gp, so the
   file is compiled at -G32 (config/cflags.txt). The text table's address is built by one lui/addiu
   pair in one register, the assembler's la macro, so it is declared MACRO_ADDR. */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { char reserved00[0x34]; int text; int f38; int timer; } MenuPanel;
typedef struct { short text; short pad; } MenuText;

extern SelectionCallback g_pause_menu_state;
extern CallbackMenuState g_pad_state;
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern int g_page_viewer_short_cursor __attribute__((sda));
extern MenuPanel g_page_viewer_panel[];
extern int g_page_viewer_short_index[];
extern MenuText g_page_viewer_menu_text_table[] MACRO_ADDR;

/* Handles left and right on the six-page viewer and updates the page text and its scroll timer. */
int page_viewer_handle_input_short(void)
{
    int result = 0;
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old_cursor = g_page_viewer_short_cursor;

    if (flags & 0x10) {
        int value;
        int return_code;
        g_page_viewer_short_cursor = 0;
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
        g_page_viewer_short_cursor = 0;
        result = 1;
    } else if (flags & 0x8000) {
        if (old_cursor > 0)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (--g_page_viewer_short_cursor < 0)
            g_page_viewer_short_cursor = 0;
    } else if (flags & 0x2000) {
        if (old_cursor < 5)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (++g_page_viewer_short_cursor > 5)
            g_page_viewer_short_cursor = 5;
    }
    if (old_cursor != g_page_viewer_short_cursor)
        g_page_viewer_panel[0].timer = -300;
    g_page_viewer_short_index[0] = g_page_viewer_short_cursor;
    g_page_viewer_panel[0].text = g_page_viewer_menu_text_table[g_page_viewer_short_cursor].text;
    return result;
}
