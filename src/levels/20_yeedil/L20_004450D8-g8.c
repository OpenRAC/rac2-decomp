#include "common.h"

/* -G8: the group-index bound D_L20_001B2FB8 is read through $gp. */

extern int D_L20_001B2FB8 __attribute__((sda));
extern char *D_L20_001B2F9C;
extern unsigned short *D_L20_001FBB20[];

/* For each entity of the object's group that has class 0xD0F and whose state has bit 0 set and
   word 0x420 equal to 1, sets the state byte to 2 and clears bit 1 of the entity's flags. */
void func_L20_004450D8(unsigned char *arg0) {
    unsigned short *q;
    char *e;

    if (arg0[0x21] == 0xFF)
        return;
    q = D_L20_001FBB20[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L20_001B2FB8 && q != 0 &&
           ((q != 0 && (short)q[-1] >= 0) || q == D_L20_001FBB20[arg0[0x21]])) {
        char *o;

        e = D_L20_001B2F9C + ((*q & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(short *)(e + 0xAA) == 0xD0F) {
            o = *(char **)(e + 0x68);
            if (o != 0 && (o[0x302] & 1) && *(int *)(o + 0x420) == 1) {
                o[0x302] = 2;
                *(unsigned short *)(e + 0x34) &= 0xFFFD;
            }
        }
        q++;
    }
}
