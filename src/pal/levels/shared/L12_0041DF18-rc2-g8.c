#include "common.h"

/* func_PAL_L12_0041DF18, the PAL copy of func_L01_004110E0 in levels 12, 14, 17 and 19: the same C,
 * where both float arguments are scaled by 6/5 and case 1 first leaves when D_001A79F0 is 0x33.
 * func_PAL_L07_0040E120 is the same function for levels 7, 8, 9 and 26. */

extern s32 D_001A79F0 MACRO_ADDR;
extern s32 D_L01_001A8F40 __attribute__((sda));

extern void func_002A7750(s8 *, s32, s32);
extern void func_L00_00326048(s8 *, s8 *, f32, s32, s32);

void func_PAL_L12_0041DF18(s8 *arg0) {
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
            break;
        }
        if (s != 0) {
            if (D_L01_001A8F40 == 2) {
                func_L00_00326048(arg0, s + 0xC, 0.06632252f, 0x80AABED2, 0x80466464);
            } else {
                func_L00_00326048(arg0, s + 0xC, 0.04537857f, 0x8096AAAA, 0x80466464);
            }
        }
        break;
    }
}
