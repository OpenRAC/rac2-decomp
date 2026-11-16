#include "names.h"
/* func_US2_002CCAA0: v2.00's copy of func_002CBAE0 (src/game/002C7748-g8.c), the
 * menu-source dispatcher. The code is v1.01's with every address moved; it is the
 * release's own function because three of its callees changed in v2.00.
 * D_001AB910 is declared volatile as in func_002CBAE0 and func_002CBC58: retail
 * rereads it for every test and keeps one load whose value it discards (the empty
 * D_0025A058/D_00259B48 arm). Without the qualifier the body is 328 bytes, not 376. */
typedef struct {
    int mode, pad4, value;
    int padC[2];
    char *source;
    char *destination;
    int state;
} MenuState_US2_2CCAA0;
typedef struct { char pad[0x1C4]; int flags; } InputState_US2_2CCAA0;
extern MenuState_US2_2CCAA0 g_pause_menu_state;
extern InputState_US2_2CCAA0 g_pad_state;
extern char g_menu_page_pause[];
extern char g_pause_page_d[];
extern char g_pause_page_c[];
extern char g_pause_page_b[];
extern char g_pause_page_a[];
extern char g_menu_page_source_alt[];
extern volatile int g_pause_menu_busy_flag __attribute__((sda));
extern int (*g_menu_page_input_handlers[])(int);
extern void func_0029CE38(void);
extern int mission_screen_place_parts_call_us2(int);
extern int DrawMapScreen_us2(int);
extern int list_screen_layout_call_us2(int);

/* Checks the current menu page and reacts to button presses on it. */
int menu_update_page_input_us2(void)
{
    int result = 0;

    if (g_pause_menu_state.source == g_menu_page_pause) {
        if (g_pad_state.flags & 0x910) {
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
            result = 1;
        } else if (g_menu_page_input_handlers[0](g_pad_state.flags) >= 0) {
            result = 1;
        }
    } else if (g_pause_menu_state.source == g_pause_page_d) {
        func_0029CE38();
    } else if (g_pause_menu_state.source == g_pause_page_c && !g_pause_menu_busy_flag) {
        mission_screen_place_parts_call_us2(0);
    } else if (g_pause_menu_state.source == g_pause_page_b && !g_pause_menu_busy_flag) {
        if (DrawMapScreen_us2(0))
            g_pause_menu_state.state = g_pause_menu_state.value == 4 ? 2 : 1;
        list_screen_layout_call_us2(g_pad_state.flags);
        result = g_pause_menu_state.destination != g_pause_page_c;
    } else if ((g_pause_menu_state.source == g_pause_page_a && !g_pause_menu_busy_flag)
               || (g_pause_menu_state.source == g_menu_page_source_alt && !g_pause_menu_busy_flag)) {
        /* nothing: only the tests remain */
    }
    return result;
}
