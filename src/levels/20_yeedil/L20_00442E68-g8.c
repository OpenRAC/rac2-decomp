#include "common.h"

/* Own -G8 unit: func_L20_00442E68 reads D_L20_001B2FB8 through $gp, and the -G8 sibling
   L20_0043ECB0-g8.c is built with -mno-split-addresses, which this function does not want. */

extern u16 *D_L20_001FBB20[];
extern char *D_L20_001B2F9C[] __attribute__((sda));
extern int D_L20_001B2FB8 __attribute__((sda));

extern void func_L02_003A6F78(char *);

/* Runs func_L02_003A6F78 on every entity of the object's group (state word 0x218, the id
   list D_L20_001FBB20[group], ids masked with 0x7FFF, 0x100-byte records at D_L20_001B2F9C),
   after setting each entity's halfword at +0x36 to 0x7F80.  The loop is the usual group
   walk with its doubled p test (see func_L02_003FD070 in L02_003F5430.c): the second test
   leaves the exit test at the bottom of the loop, which gives retail's `b test` entry.
   The entity bank is an `sda` array of unknown size, which gives retail's absolute
   lui/lw load in this -G8 unit. */
void func_L20_00442E68(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;

    for (p = D_L20_001FBB20[*(s32 *)(state + 0x218)];
         (*(s32 *)(state + 0x218) & 0xFF) != 0xFF && *(s32 *)(state + 0x218) <= D_L20_001B2FB8 &&
         p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L20_001FBB20[*(s32 *)(state + 0x218)]);
         p++) {
        e = D_L20_001B2F9C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        *(u16 *)(e + 0x36) = 0x7F80;
        func_L02_003A6F78(e);
    }
}
