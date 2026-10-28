/* func_L09_003FB4D0 - 384 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L09_003FB4D0 (384 B, 1 place). draft.c = best (switch, separate loop
   var j for state 0, stores a0[0x20] before a0[0x30]).
   Needs `#include "common.h"` NOT required here. Names: D_L09_001B35E0
   int[16], D_L09_00255E90 {obj,other}[16], callee func_L08_002F2D10 for the
   2E2FD0 call.
   Same size, same instruction shape; ~35 masked diff lines, all register
   swaps:
    - state 1 loop: mine i=$s1, slot-ptr=$s2, n=$s6, arg=$s7; retail i=$s2,
   slot-ptr=$s1, n=$s7, arg=$s6
    - state 0 loop: mine slot-ptr $v1, count $a0; retail slot-ptr $a0, count
   $v1; and `beqz $v1` plus `lui $v0,0x25` in its delay slot (mine `beql`)
   Tried: loop var shared/separate, count-down loop, order of the 3 clears (6
   perms), declaration order, unsigned n, do-while, if/else instead of switch
   (worse, 84). */

typedef struct {
    int *obj;
    int other;
} Slot_L09_003FB4D0;

extern int D_L09_001B35E0[16];
extern Slot_L09_003FB4D0 D_L09_00255E90[16];
extern void func_L09_003FB860(int);
extern void func_L09_003FB9F8(int *, int);
extern void func_L09_003FBF98();
extern void func_L08_002F2D10(void *, void *);

void func_L09_003FB4D0(unsigned char *a0) {
    int i;
    int n;
    int j;

    switch (a0[0x20]) {
    case 0:
        for (j = 0; j < 16; j++) {
            D_L09_001B35E0[j] = 0;
            D_L09_00255E90[j].obj = 0;
            D_L09_00255E90[j].other = 0;
        }
        a0[0x20] = 1;
        a0[0x30] = 0xFF;
        break;
    case 1:
        n = 0;
        for (i = 0; i < 16; i++) {
            if (D_L09_001B35E0[i] == 1) {
                if (((signed char *)D_L09_00255E90[i].obj)[0x20] < 0) {
                    D_L09_00255E90[i].obj = 0;
                    D_L09_001B35E0[i] = 0;
                    D_L09_00255E90[i].other = 0;
                }
            } else if (D_L09_001B35E0[i] == 4) {
                func_L09_003FB860(i);
            } else if (D_L09_001B35E0[i] != 0) {
                func_L09_003FB9F8(D_L09_00255E90[i].obj, i);
                n++;
                D_L09_001B35E0[i] = 4;
            }
        }
        if (n != 0) {
            func_L08_002F2D10(func_L09_003FBF98, a0);
        }
        break;
    }
}
