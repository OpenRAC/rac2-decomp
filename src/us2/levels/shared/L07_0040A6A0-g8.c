#include "common.h"

/* func_US2_L07_0040A6A0, the USA v2.00 copy of func_L07_00409300: the same C with one more
 * test first in case 1. */

extern s32 ref_L07_00409300_00 __attribute__((sda));
extern s32 D_001A79F0;

extern void ref_L07_00409300_01(s8 *, s32, s32);
extern void ref_L07_00409300_02(s8 *, s8 *, s32, s32, f32);

void func_US2_L07_0040A6A0(s8 *arg0) {
    s8 *s;
    u8 t;

    t = *(u8 *)(arg0 + 0x20);
    s = *(s8 **)(arg0 + 0x68);
    switch (t) {
    case 0:
        ref_L07_00409300_01(arg0, 1, -1);
        return;
    case 1:
        if (D_001A79F0 == 0x33) {
            return;
        }
        if (s != 0) {
            if (ref_L07_00409300_00 == 2) {
                ref_L07_00409300_02(arg0, s + 0xC, 0x80AABED2, 0x80466464, 0.05526876822113991f);
            } else {
                ref_L07_00409300_02(arg0, s + 0xC, 0x8096AAAA, 0x80466464, 0.03781547397375107f);
            }
        }
        break;
    }
}
