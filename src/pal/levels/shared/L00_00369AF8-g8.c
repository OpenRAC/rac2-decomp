#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_00369AF8, the PAL copy of func_L00_00367308: the same C, where word 31 becomes 6
 * and two copied timers take the 50 Hz scale. */

typedef struct { int words[34]; } ResetState;
typedef struct { int words[10]; } ResetRow;
typedef struct {
    char reserved00[0x50];
    int active;
    char reserved54[0x2C];
} ResetBlock;

extern ResetState g_menu_reset_state;
extern ResetRow g_menu_reset_rows[15];
extern ResetBlock g_menu_reset_blocks[128];
extern int g_menu_state_word_a __attribute__((sda));
extern int g_menu_state_word_b __attribute__((sda));

void func_PAL_L00_00369AF8(void) {
    int i;

    g_menu_reset_state.words[7] = 2;
    g_menu_reset_state.words[6] = 3;
    g_menu_reset_state.words[8] = 4;
    g_menu_reset_state.words[0] = -1;
    g_menu_reset_state.words[10] = 100;
    g_menu_reset_state.words[14] = -1;
    g_menu_reset_state.words[31] = 6;
    g_menu_reset_state.words[1] = 0;
    g_menu_reset_state.words[4] = 0;
    g_menu_reset_state.words[2] = 0;
    g_menu_reset_state.words[5] = 0;
    g_menu_reset_state.words[3] = 0;
    g_menu_reset_state.words[30] = 0;
    g_menu_reset_state.words[9] = 0;
    g_menu_reset_state.words[11] = 0;
    g_menu_reset_state.words[13] = 0;
    g_menu_reset_state.words[15] = 0;
    g_menu_reset_state.words[18] = 0;
    g_menu_reset_state.words[19] = 0;
    g_menu_reset_state.words[20] = 0;
    g_menu_reset_state.words[21] = 0;
    g_menu_reset_state.words[28] = 0;
    g_menu_reset_state.words[23] = 0;
    g_menu_reset_state.words[25] = 0;
    g_menu_reset_state.words[24] = 0;
    g_menu_reset_state.words[26] = 0;
    g_menu_reset_state.words[22] = 0;
    g_menu_reset_state.words[27] = 0;
    g_menu_reset_state.words[32] = 0;
    g_menu_reset_state.words[33] = 0;
    g_menu_state_word_a = 0;
    g_menu_state_word_b = 0;
    for (i = 0; i < 15; i++)
        g_menu_reset_rows[i].words[5] = g_menu_reset_rows[i].words[3];
    g_menu_reset_rows[7].words[5] = (g_menu_reset_rows[7].words[3] * 5 + 2) / 6;
    g_menu_reset_rows[13].words[5] = (g_menu_reset_rows[13].words[3] * 5 + 2) / 6;
    for (i = 127; i >= 0; i--)
        g_menu_reset_blocks[i].active = 0;
}
