#include "names.h"
/* func_PAL_L01_00416484, the PAL copy of func_L01_004110E0: the same C, where both float
 * arguments are scaled by 6/5 and case 1 first leaves when D_001A79F0 (the current area) is 0x33. */
#include "common.h"

extern s32 g_current_map_index MACRO_ADDR;
extern s32 g_hero_l01_control_mode __attribute__((sda));

extern void moby_set_state(s8 *, s32, s32);
extern void math_store_angle_update_result(s8 *, s8 *, s32, s32, f32);

void func_PAL_L01_00416484(s8 *arg0) {
    s8 *s;
    u8 t;

    t = *(u8 *)(arg0 + 0x20);
    s = *(s8 **)(arg0 + 0x68);
    switch (t) {
    case 0:
        moby_set_state(arg0, 1, -1);
        return;
    case 1:
        if (g_current_map_index == 0x33) {
            break;
        }
        if (s != 0) {
            if (g_hero_l01_control_mode == 2) {
                math_store_angle_update_result(arg0, s + 0xC, 0x80AABED2, 0x80466464, 0.06632252f);
            } else {
                math_store_angle_update_result(arg0, s + 0xC, 0x8096AAAA, 0x80466464, 0.04537857f);
            }
        }
        break;
    }
}
