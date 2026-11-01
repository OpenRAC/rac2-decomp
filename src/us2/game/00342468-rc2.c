#include "include_asm.h"

#include "common.h"
extern s8 D_00265290[];

s32 func_US2_00342468(s32 arg0) {
    s32 temp_a1;
    s32 var_a2;
    s32 tmp0;

    temp_a1 = (*(s32 *)((s8 *)(arg0) + (0x31C)));
    tmp0 = arg0 + (temp_a1 * 4);
    var_a2 = *(s32 *)(((s32)D_00265290) + (s32) (((*(s32 *)((s8 *)(tmp0) + (0x1B8))) * 4) + (temp_a1 << 5)));
    if ((temp_a1 == 2) && (*(u8 *)0x1A7A12 == 0)) {
        var_a2 = ((*(s32 *)((s8 *)(arg0) + (0x1C0))) >= 3) ? 0 : var_a2;
    }
    return var_a2;
}
