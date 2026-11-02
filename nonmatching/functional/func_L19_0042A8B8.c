/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Batch 3 (2026-10-28) handoff notes:
draft.c: new file src/levels/19_grelbin/L19_0042A8B8.c with cflags line `-O2 -G0 -ffunction-sections -mno-split-addresses`; marker removed from L19_0042A860.c. 228/228 B, 9 masked lines (no name fixes done: func_0029F978 etc. still need canonical names).
Left: retail forms the list address in v1 (lui/addiu v1,-0x28C0), loads the count at 0x44(v1) for the guard, and only then copies it (daddu s2,v1,zero) into the saved reg used by the loop; ours keeps it in s2 from the start (and orders addiu s3,0xE3E / daddu s0 differently).
Tried: guard through the symbol (folds +0x44 into the symbol: 14 lines), separate list/block locals, count pointer, struct-typed global with for loop (10 lines, folds sym+0x44 as well), loop-condition via symbol, <1 vs <=0.
*/

#include "common.h"

extern s32 D_L19_001A8F00;
extern u8 D_001A7A40;
extern u8 D_L19_001B22E1;
extern u8 D_L19_001B22E0[];
extern f32 D_L19_001B2300;
extern f32 D_L19_001B2304;
extern f32 D_L19_001B2308;
extern u8 D_L19_001BD740[];
extern void func_0029F978(u8 *, u32, u8 *);

void func_L19_0042A8B8(void)
{
    u8 *block;
    u8 **entry;
    int i;
    if (D_L19_001A8F00 != 2) return;
    if (!D_001A7A40) return;
    block = D_L19_001BD740;
    if (*(s16 *)(block+0x44) <= 0) return;
    entry = (u8 **)(block+0x18c);
    i=0;
    do {
        u8 *object = *entry;
        if (*(s16 *)(object + 0xaa) == 0xe3e && !D_L19_001B22E1) {
        func_0029F978(object, 0, D_L19_001B22E0);
        D_L19_001B2300 = 1.9f;
        D_L19_001B2304 = 1.9f;
        D_L19_001B2308 = 1.9f;
        }
        i++;
        entry++;
    } while (i < *(s16 *)(block+0x44));
}
