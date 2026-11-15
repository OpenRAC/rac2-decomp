#include "include_asm.h"
#include "names.h"

/* func_PAL_00289730, the PAL copy of func_00288E18: the same C, with the tests of D_001A8BB0 and
 * D_001B1688 added before the stores. */
typedef struct { int active; char reserved04[0x20]; int key; int selection; char reserved2C[0x14]; int value40; int value44; } SelectorState;
typedef struct { char reserved00[0x24]; int key; char reserved28[0x40]; int active;
                short unk6C; char reserved6E[4]; unsigned short unk72; } SelectorOwner;
typedef struct { unsigned short key; char reserved02[10]; } SelectorRow;
extern SelectorState ref_L00_00288E18_00;
extern SelectorOwner g_music_state;
extern SelectorRow g_subtitle_history[];
extern int g_current_game_mode __attribute__((sda));
extern int g_game_time __attribute__((sda));
int func_PAL_00289730(int key, int selection)
{
    SelectorState *state = &ref_L00_00288E18_00;
    if (state->active == 0 && state->key == -1 && g_music_state.active == 0 &&
        g_music_state.key == -1 && g_subtitle_history[selection].key != 65535 &&
        g_current_game_mode != 6 && g_game_time >= 6) {
        state->key = key;
        state->selection = selection;
        state->value40 = 0;
        state->value44 = 0;
        return 1;
    }
    return 0;
}
