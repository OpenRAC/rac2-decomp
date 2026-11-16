#include "common.h"

/* func_PAL_002CC950: PAL copy of func_002CBAE0 (src/game/002C7748-g8.c).
 * Menu-source dispatcher. The C logic is identical to USA v1.01 and USA v2.00
 * (src/us2/game/002CCAA0-g8.c) with PAL symbol names. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_PAL_2CC950;
typedef struct { char pad[0x1C4]; int flags; } InputState_PAL_2CC950;
extern MenuState_PAL_2CC950 g_pause_menu_state;
extern InputState_PAL_2CC950 g_pause_pad_input;
extern char g_pause_page_main[];
extern char g_pause_page_sixth[];
extern char g_pause_page_fifth[];
extern char g_pause_page_fourth[];
extern char g_pause_page_third[];
extern char g_pause_page_options[];
extern volatile int g_pause_menu_busy_flag __attribute__((sda));
extern int (*g_pad_poll_funcs[])(int);
extern void func_PAL_0029D7D0(void);
extern int func_PAL_0029CC28(int);
extern int func_PAL_002D7B68(int);
extern int func_PAL_0029CC98(int);

int menu_update_page_input_pal(void)
{
    int result = 0;

    if (g_pause_menu_state.source == g_pause_page_main) {
        if (g_pause_pad_input.flags & 0x910) {
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
            result = 1;
        } else if (g_pad_poll_funcs[0](g_pause_pad_input.flags) >= 0) {
            result = 1;
        }
    } else if (g_pause_menu_state.source == g_pause_page_sixth) {
        func_PAL_0029D7D0();
    } else if (g_pause_menu_state.source == g_pause_page_fifth && !g_pause_menu_busy_flag) {
        func_PAL_0029CC28(0);
    } else if (g_pause_menu_state.source == g_pause_page_fourth && !g_pause_menu_busy_flag) {
        if (func_PAL_002D7B68(0))
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
        func_PAL_0029CC98(g_pause_pad_input.flags);
        result = g_pause_menu_state.destination != g_pause_page_fifth;
    } else if ((g_pause_menu_state.source == g_pause_page_third && !g_pause_menu_busy_flag)
               || (g_pause_menu_state.source == g_pause_page_options && !g_pause_menu_busy_flag)) {
        /* nothing: only the tests remain */
    }
    return result;
}
