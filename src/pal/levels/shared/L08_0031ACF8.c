#include "include_asm.h"
#include "names.h"

typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7AA8]; Pair pair[4]; } State;
extern char *g_hud_l08_text_table[] __attribute__((sda));

/* Stores a pair of values in one of four slots of the global game state, if it exists. Returns 1 on success. */
int level_set_game_state_pair_pal(int value_a, int value_b, unsigned int index)
{
    if (g_hud_l08_text_table[0] != 0 && index < 4) {
        State *game_state = (State *)(g_hud_l08_text_table[0] + 0x38000);
        game_state->pair[index].a = value_a;
        game_state->pair[index].b = value_b;
        return 1;
    }
    return 0;
}

