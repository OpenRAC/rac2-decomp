#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

typedef struct {
    u8 prefix[0x40];
    s32 mode;
    u8 between[0x14];
    s32 state;
} StateTransitionView;

extern StateTransitionView g_menu_transition_state;

/* Owner-reviewed Qwen backlog: observed operations, not recovered original object boundaries. */

/* func_00285840: owner ABI/declaration review retained. */
/* extern declaration for global variable referenced in func_00285840 */
extern unsigned int g_menu_saved_state;

/* Change resident state word from1 to2 only when the mode word equals7 */
/* Moves the menu state from 1 to 2, but only while the menu mode is 7. */
void menu_advance_state_in_mode_seven(void) {
    if (g_menu_transition_state.mode == 7 && g_menu_transition_state.state == 1) {
        g_menu_transition_state.state = 2;
    }
}

/* Returns true while the saved menu state is 7. */
int menu_is_state_seven(void)
{
    return g_menu_saved_state == 7;
}
