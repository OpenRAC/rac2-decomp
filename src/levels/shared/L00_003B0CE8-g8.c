/* func_L00_003B0CE8 (184 bytes, 27 levels): frees slot idx and, in every used slot from
   the cursor up to the first free one, replaces references to it with that slot's own
   number; rebuilds the list when the freed slot was the cursor. */
#include "common.h"

typedef struct { u8 pad0[0xC]; int used; u8 pad10[4]; u8 id[8]; } Slot;
extern Slot D_L00_0023BB78[];
extern u8 D_L00_001AF810 __attribute__((sda));
extern u8 D_L00_001AF811 __attribute__((sda));

extern void func_L00_003B0A28();

void func_L00_003B0CE8(int idx)
{
    u8 c = idx;
    u8 cur;
    int i;

    D_L00_0023BB78[c].used = 0;
    for (cur = D_L00_001AF811; cur != D_L00_001AF810; cur++) {
        if (D_L00_0023BB78[cur].used != 0) {
            for (i = 0; i < 8; i++) {
                if (D_L00_0023BB78[cur].id[i] == c)
                    D_L00_0023BB78[cur].id[i] = cur;
            }
        }
    }
    if (c == D_L00_001AF811)
        AdvanceNodeRingCursor();
}
