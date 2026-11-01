#include "include_asm.h"

#include "common.h"

s32 func_PAL_00343638(s32 arg0) {
    s32 temp_v1;
    s32 var_a0;
    s32 var_v0;
    s32 tmp0;

    temp_v1 = (*(s32 *)((s8 *)(arg0) + (0x31C)));
    if (temp_v1 == 0) {
        goto block_2;
    }
    goto block_5;
block_2:
    var_v0 = (*(s32 *)((s8 *)(arg0) + (0x1B8)));
    var_a0 = (*(s32 *)((s8 *)(arg0) + (0x310)));
block_4:
    return var_a0 + (var_v0 * 0x14);
block_5:
    if (temp_v1 != 1) {
        tmp0 = arg0 + (temp_v1 * 4);
        return (*(s32 *)((s8 *)(arg0) + (0x318))) + ((*(s32 *)((s8 *)(tmp0) + (0x1B8))) * 0x14);
    }
    var_a0 = (*(s32 *)((s8 *)(arg0) + (0x314)));
    return var_a0 + (((*(s32 *)((s8 *)(arg0) + (0x1BC)))) * 0x14);
block_7:
    return (*(s32 *)((s8 *)(arg0) + (0x318))) + ((*(s32 *)((s8 *)((arg0 + (temp_v1 * 4))) + (0x1B8))) * 0x14);
}
