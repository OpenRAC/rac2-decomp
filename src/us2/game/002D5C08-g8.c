/* func_US2_002D5C08, the USA v2.00 copy of func_002D4FF0: the same C, without the store of -0x2BC
 * at 0x3C. */
#include "common.h"

extern s32 D_001ABAA0 __attribute__((sda));
extern s32 D_001AAA38 __attribute__((sda));
extern s8 D_0025B9C0[];
extern s8 D_0025BA80[];

s32 func_US2_002D5C08(s32 arg0) {
    s32 temp_a1;
    s32 idx;

    temp_a1 = *(s32 *)D_0025B9C0;
    if (D_001ABAA0 != temp_a1) {
        D_001ABAA0 = temp_a1;
    }
    idx = temp_a1 * 4;
    (*(s32 *)((s8 *)(arg0) + (0x34))) = *(s32 *)((s8 *)&D_001AAA38 + idx);
    *(s32 *)D_0025BA80 = temp_a1 + 1;
    return 0;
}
