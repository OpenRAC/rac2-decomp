#include "include_asm.h"
#include "common.h"

/* func_US2_L01_0041264C, the USA v2.00 copy of func_L01_004110E0: the same C with one more
 * test first in case 1. */

extern s32 D_L01_001A8F40 __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));

extern void func_002A7750(s8 *, s32, s32);
extern void func_L00_00326048(s8 *, s8 *, f32, s32, s32);

void func_US2_L01_0041264C(s8 *arg0) {
    s8 *s;
    u8 t;

    t = *(u8 *)(arg0 + 0x20);
    s = *(s8 **)(arg0 + 0x68);
    switch (t) {
    case 0:
        func_002A7750(arg0, 1, -1);
        return;
    case 1:
        if (D_001A79F0 == 0x33) {
            return;
        }
        if (s != 0) {
            if (D_L01_001A8F40 == 2) {
                func_L00_00326048(arg0, s + 0xC, 0.055268768f, (s32)0x80AABED2u, (s32)0x80466464u);
            } else {
                func_L00_00326048(arg0, s + 0xC, 0.037815473f, (s32)0x8096AAAAu, (s32)0x80466464u);
            }
        }
        break;
    }
}
