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
extern int D_001ABA60 __attribute__((sda));
extern MenuPanel D_0025CAA0[];
extern int D_0025CB50[];
extern MenuText D_001ABD6A[] MACRO_ADDR;

/* Handles left and right on the six-page viewer and updates the page text and its scroll timer. */
int page_viewer_handle_input_short(void)
{
    int result = 0;
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old_cursor = D_001ABA60;

    if (flags & 0x10) {
        int value;
        int return_code;
        D_001ABA60 = 0;
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
        D_001ABA60 = 0;
        result = 1;
    } else if (flags & 0x8000) {
        if (old_cursor > 0)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (--D_001ABA60 < 0)
            D_001ABA60 = 0;
    } else if (flags & 0x2000) {
        if (old_cursor < 5)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (++D_001ABA60 > 5)
            D_001ABA60 = 5;
    }
    if (old_cursor != D_001ABA60)
        D_0025CAA0[0].timer = -300;
    D_0025CB50[0] = D_001ABA60;
    D_0025CAA0[0].text = D_001ABD6A[D_001ABA60].text;
    return result;
}
