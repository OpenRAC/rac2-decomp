#include "names.h"
/* func_PAL_L01_00416484, the PAL copy of func_L01_004110E0: the same C, where both float
 * arguments are scaled by 6/5 and case 1 first leaves when D_001A79F0 (the current area) is 0x33. */
#include "common.h"

extern s32 g_current_map_index MACRO_ADDR;
extern s32 g_hero_l01_control_mode __attribute__((sda));

extern void moby_set_state(s8 *, s32, s32);
extern void math_store_angle_update_result(s8 *, s8 *, s32, s32, f32);

/* Updates a TV Screens moby: starts it, then keeps its screen effect running (PAL: 6/5 scaled rates). */
void tv_l01_l01_screens_update_pal(s8 *moby) {
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
                math_store_angle_update_result(moby, vars + 0xC, 0x80AABED2, 0x80466464, 0.06632252f);
            } else {
                math_store_angle_update_result(moby, vars + 0xC, 0x8096AAAA, 0x80466464, 0.04537857f);
            }
        }
        break;
    }
}
