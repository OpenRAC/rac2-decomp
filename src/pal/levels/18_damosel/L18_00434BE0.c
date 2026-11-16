#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 g_beam_target_vec[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern void extermibot_init_parts(u8 *moby);
extern void extermibot_update_hits(u8 *moby);
extern void extermibot_update_states(u8 *moby);
extern void extermibot_aim_torso(u8 *moby);
extern void extermibot_update_parts(u8 *moby);
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern u8 g_data_block_base[];

/* Runs the boss each frame: sets it up in state 0, does nothing in state 1, and otherwise runs its four sub-updates. (PAL version) */
void extermibot_update_subsystems_pal(u8 *moby) {
    u8 mode = *(u8 *)(moby + 0x20);
    if (mode == 0) {
        extermibot_init_parts(moby);
        return;
    }
    if (mode == 1) return;
    extermibot_update_hits(moby);
    extermibot_update_states(moby);
    extermibot_aim_torso(moby);
    extermibot_update_parts(moby);
}





