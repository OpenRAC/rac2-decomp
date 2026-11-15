/* Carried from rac3-decomp (src/levels/shared/L01_0042DB28.c, func_L01_0042E1D8): the
   same instructions with rac2's offsets. Returns func_00295680(1) when it is non-zero;
   otherwise picks the first of slots 1-4 whose flags lack 0x1000 and whose word is set
   (5 when none is), hands it to func_00295788(0, slot) and returns it. */

#include "common.h"

typedef struct {
    u8 pad[0x288];
    s32 b[5];
    s32 a[5];
} SlotBlock;

extern SlotBlock D_001C4FA0;
extern s32 func_00295680(s32);
extern void func_00295788(s32, s32);

/* Finds a free entry (of 5) and copies entry 0 into it; returns its index. */
s32 func_002956E8(void) {
    s32 i = func_00295680(1);

    if (i != 0) {
        return i;
    }
    for (i = 1; i < 5; i++) {
        if (!(D_001C4FA0.a[i] & 0x1000) && D_001C4FA0.b[i] != 0) {
            break;
        }
    }
    func_00295788(0, i);
    return i;
}
