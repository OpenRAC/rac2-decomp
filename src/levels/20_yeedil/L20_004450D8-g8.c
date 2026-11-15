#include "common.h"

/* -G8: the group-index bound D_L20_001B2FB8 is read through $gp. */

extern int D_L20_001B2FB8 __attribute__((sda));
extern char *D_L20_001B2F9C;
extern unsigned short *D_L20_001FBB20[];

/* For each entity of the object's group that has class 0xD0F and whose state has bit 0 set and
   word 0x420 equal to 1, sets the state byte to 2 and clears bit 1 of the entity's flags. */
/* Wakes up the troopers of this group that were waiting, switching them to their next state. */
void func_L20_004450D8(unsigned char *moby) {
    unsigned short *q;
    char *member;

    if (moby[0x21] == 0xFF)
        return;
    q = D_L20_001FBB20[moby[0x21]];
    while (moby[0x21] != 0xFF && moby[0x21] <= D_L20_001B2FB8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == D_L20_001FBB20[moby[0x21]])) {
        char *trooperVars;

        member = D_L20_001B2F9C + ((*q & 0x7FFF) << 8);
        if (member == 0)
            break;
        if (*(short *)(member + 0xAA) == 0xD0F /* Megacorp Trooper Legs */) {
            trooperVars = *(char **)(member + 0x68);
            if (trooperVars != 0 && (trooperVars[0x302] & 1) && *(int *)(trooperVars + 0x420) == 1) {
                trooperVars[0x302] = 2;
                *(unsigned short *)(member + 0x34) &= 0xFFFD;
            }
        }
        q++;
    }
}
