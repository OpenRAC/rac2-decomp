#include "common.h"

/* func_US2_L07_0040A6A0, the USA v2.00 copy of func_L07_00409300: the same C with one more
 * test first in case 1. */

extern s32 ref_L07_00409300_00 __attribute__((sda));
extern s32 g_current_map_index;

extern void ref_L07_00409300_01(s8 *, s32, s32);
extern void ref_L07_00409300_02(s8 *, s8 *, s32, s32, f32);

/* Updates the TV screens moby: sets up in state 0, then scrolls the screens, speed depending on a mode value (v2.00). */
void tv_l07_screens_update_us2(s8 *moby) {
    s8 *state;
    u8 object_state;

    object_state = *(u8 *)(moby + 0x20);
    state = *(s8 **)(moby + 0x68);
    switch (object_state) {
    case 0:
        ref_L07_00409300_01(moby, 1, -1);
        return;
    case 1:
        if (g_current_map_index == 0x33) {
            return;
        }
        if (state != 0) {
            if (ref_L07_00409300_00 == 2) {
                ref_L07_00409300_02(moby, state + 0xC, 0x80AABED2, 0x80466464, 0.05526876822113991f);
            } else {
                ref_L07_00409300_02(moby, state + 0xC, 0x8096AAAA, 0x80466464, 0.03781547397375107f);
            }
        }
        break;
    }
}
