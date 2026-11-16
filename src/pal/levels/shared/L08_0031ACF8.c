#include "include_asm.h"
#include "names.h"

typedef struct { int a; int b; } Pair;
typedef struct { char pad[0x7AA8]; Pair pair[4]; } State;
extern char *g_hud_l08_text_table[] __attribute__((sda));

int level_set_game_state_pair_pal(int a0, int a1, unsigned int index)
{
    if (g_hud_l08_text_table[0] != 0 && index < 4) {
        State *s = (State *)(g_hud_l08_text_table[0] + 0x38000);
        s->pair[index].a = a0;
        s->pair[index].b = a1;
        return 1;
    }
    return 0;
}

