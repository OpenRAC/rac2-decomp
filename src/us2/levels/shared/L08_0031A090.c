#include "include_asm.h"
#include "names.h"

typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x79F8]; Pair pair[4]; } State;
extern char *g_hud_l08_text_table[] __attribute__((sda));

/* Stores two values in entry `index` (0 to 3) of the level game-state pair table; returns 1 on success. */
int level_set_game_state_pair_us2(int first_value, int second_value, unsigned int index)
{
    if (g_hud_l08_text_table[0] != 0 && index < 4) {
        State *game_state = (State *)(g_hud_l08_text_table[0] + 0x38000);
        game_state->pair[index].a = first_value;
        game_state->pair[index].b = second_value;
        return 1;
    }
    return 0;
}

