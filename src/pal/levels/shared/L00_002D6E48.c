#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_002D6E48, PAL's own: whether the global state is 98, 99 or 100. */
extern int g_game_mode;

int level_is_mode_98_to_100_pal(void) {
    int state = g_game_mode;
    int result = 0;

    if (state < 101) {
        result = state >= 98;
    }
    return result;
}
