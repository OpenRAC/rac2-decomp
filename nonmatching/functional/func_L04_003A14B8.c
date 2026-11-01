/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high: 132/132 bytes, 0/5 places, default -O2 -G0
   -ffunction-sections. An integer index alongside the countdown restores retail's
   induction-pointer copy and loop-alignment nop (previous draft: 124/132 bytes).
   Allocation still differs: state/induction pointer is a2 instead of v1,
   countdown is v1 instead of a0, and the mask is a0 instead of a1. Initial
   andi also uses a1 instead of t1; base/offset arithmetic scheduling differs.
   Factoring the offset and using an s32 pointer for state both tie this form.
   No extra declarations needed; useful next step is an allocator explanation
   for the state-to-induction-pointer register preference. */

#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

/* tags the masked words of the sub-array the state block points at */
void func_L04_003A14B8(u8 *object, u32 value) {
    u32 tag = (value & 0x3F) << 24;
    u8 *state = *(u8 **)(object + 0x98);
    u32 *p = (u32 *)(state + *(s32 *)(state + 0x4) + 0x10 +
                     (*(s32 *)(state + 0xC) / 8) * 8);
    s32 count = *(s32 *)(state + 0x8) / 4;

    if (count > 0) {
        int i = 0;
        do {
            p[i] = (p[i] & 0xC0FFFFFF) | tag;
            i++;
            count--;
        } while (count != 0);
    }
}
