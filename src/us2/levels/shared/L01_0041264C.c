#include "include_asm.h"
#include "common.h"

/* func_US2_L01_0041264C, the USA v2.00 copy of func_L01_004110E0: the same C with one more
 * test first in case 1. */

extern s32 g_hero_l01_control_mode __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));

extern void moby_set_state(s8 *, s32, s32);
extern void math_store_angle_update_result(s8 *, s8 *, f32, s32, s32);

void func_US2_L01_0041264C(s8 *arg0) {
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
            return;
        }
        if (s != 0) {
            if (g_hero_l01_control_mode == 2) {
                math_store_angle_update_result(arg0, s + 0xC, 0.055268768f, (s32)0x80AABED2u, (s32)0x80466464u);
            } else {
                math_store_angle_update_result(arg0, s + 0xC, 0.037815473f, (s32)0x8096AAAAu, (s32)0x80466464u);
            }
        }
        break;
    }
}
