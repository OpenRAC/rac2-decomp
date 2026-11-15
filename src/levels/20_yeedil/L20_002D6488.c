#include "include_asm.h"
#include "names.h"

/* Not attempted: nonmatching/levels/func_L20_002D7730.c holds a map of this
   body (19548 bytes, 4887 instructions, 278 blocks, 238 calls, no loop; the
   dispatch through the level's own jump table jtbl_002B2A40, the join points
   with their predecessor counts, the exits, the callees, the $gp accesses,
   and the -G8 unit it needs). */

extern unsigned char D_L20_0018C0D4;

extern void hero_l20_set_state(int a0, int a1);

/* Picks the variant of the shared loader the current game state selects. */
void hero_load_state_by_game_mode(int flag)
{
    int a1 = (flag != 0) ? 2 : 1;

    switch (D_L20_0018C0D4) {
    case 0:
        hero_l20_set_state(0, a1);
        break;
    case 1:
        hero_l20_set_state(0x3F, a1);
        break;
    case 4:
        hero_l20_set_state(0x8D, a1);
        break;
    }
}
