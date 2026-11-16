#include "include_asm.h"
#include "names.h"

extern int g_game_mode;

/* Returns 1 when the game mode is 98, 99 or 100, else 0. */
int game_mode_is_98_to_100_us2(void) {
    int value = g_game_mode;
    int result = 0;

    if (value <= 100) {
        result = value >= 98;
    }
    return result;
}
