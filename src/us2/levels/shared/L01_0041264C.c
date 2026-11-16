#include "include_asm.h"
#include "common.h"

/* func_US2_L01_0041264C, the USA v2.00 copy of func_L01_004110E0: the same C with one more
 * test first in case 1. */

extern s32 g_hero_l01_control_mode __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));

extern void moby_set_state(s8 *, s32, s32);
extern void math_store_angle_update_result(s8 *, s8 *, f32, s32, s32);

/* Updates a level 1 TV screen moby, turning it with the hero control mode (USA v2.00, skipped on map 0x33). */
void tv_l01_screens_update_us2(s8 *moby) {
    s8 *vars;
    u8 state;

    state = *(u8 *)(moby + 0x20);
    vars = *(s8 **)(moby + 0x68);
    switch (state) {
    case 0:
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if (g_current_map_index == 0x33) {
            return;
        }
        if (vars != 0) {
            if (g_hero_l01_control_mode == 2) {
                math_store_angle_update_result(moby, vars + 0xC, 0.055268768f, (s32)0x80AABED2u, (s32)0x80466464u);
            } else {
                math_store_angle_update_result(moby, vars + 0xC, 0.037815473f, (s32)0x8096AAAAu, (s32)0x80466464u);
            }
        }
        break;
    }
}
