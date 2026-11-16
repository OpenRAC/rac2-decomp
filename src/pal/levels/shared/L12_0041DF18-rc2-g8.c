#include "common.h"

/* func_PAL_L12_0041DF18, the PAL copy of func_L01_004110E0 in levels 12, 14, 17 and 19: the same C,
 * where both float arguments are scaled by 6/5 and case 1 first leaves when D_001A79F0 is 0x33.
 * func_PAL_L07_0040E120 is the same function for levels 7, 8, 9 and 26. */

extern s32 g_current_map_index MACRO_ADDR;
extern s32 g_hero_l01_control_mode __attribute__((sda));

extern void moby_set_state(s8 *, s32, s32);
extern void math_store_angle_update_result(s8 *, s8 *, f32, s32, s32);

/* Updates a TV screens moby: starts it, then keeps its screen effect running (PAL: 50 Hz rates). */
void tv_l12_l01_screens_update_pal(s8 *moby) {
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
            break;
        }
        if (vars != 0) {
            if (g_hero_l01_control_mode == 2) {
                math_store_angle_update_result(moby, vars + 0xC, 0.06632252f, 0x80AABED2, 0x80466464);
            } else {
                math_store_angle_update_result(moby, vars + 0xC, 0.04537857f, 0x8096AAAA, 0x80466464);
            }
        }
        break;
    }
}
