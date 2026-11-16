#include "include_asm.h"
#include "names.h"

extern int g_game_mode;

int func_US2_L00_002D6C98(void) {
    int value = g_game_mode;
    int result = 0;

    if (value <= 100) {
        result = value >= 98;
    }
    return result;
}
