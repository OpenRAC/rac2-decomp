#include "common.h"

/* A unit of its own (with the old unit's flags) so that the call to func_L02_003FD770 goes through its symbol: PAL has has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

extern char D_L02_001B11D0[8] __attribute__((sda));
extern char D_L02_001B11E0[8] __attribute__((sda));
extern float func_00282E48(void *, void *);
extern char D_L02_001BA500[];
extern int D_L02_001B32E8;
extern void func_002A7750(char *, int, int);
extern void func_L02_003FD770(char *);

/* Raises the flag at 0x1B32E8. When the point at D_L02_001BA500 is within 0.0001 of the one at
   D_L02_001B11D0 the actor changes state by its kind (4 to 7, 5 to 6) and the two widgets are
   updated; otherwise func_L02_003FD770 runs unless the object's state half-word is 5. */
void func_L02_003FD7C8(char *a0) {
    D_L02_001B32E8 = 1;
    if (fast_vec_dist(D_L02_001BA500, D_L02_001B11D0) < 0.0001f) {
        if (*(unsigned char *)(a0 + 0x20) == 4)
            func_002A7750(a0, 7, -1);
        else if (*(unsigned char *)(a0 + 0x20) == 5)
            func_002A7750(a0, 6, -1);
        SetCamera5Mode(1, 0);
        func_00335370(D_L02_001B11D0);
        func_003353C8(D_L02_001B11E0);
    } else if (*(short *)(*(char **)(D_L02_001BA500 + 0x50) + 0x86) != 5) {
        func_L02_003FD770(a0);
    }
}
