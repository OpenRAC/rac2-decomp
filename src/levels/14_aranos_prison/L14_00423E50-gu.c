/* func_L14_00423E50: own unit for -frac2-gcse-unsplit-edges. With the critical edge left whole,
 * gcse PRE leaves the group-index reload in the bnel delay slot (table-entry path only), as
 * retail has it; with L14_003F4F98.c's plain flags the same C is 160 bytes.
 */
#include "common.h"

/* The entity bank: `sda` makes its load one macro instruction, which the assembler expands to
   retail's lui/lw pair on one register. */
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern unsigned short *D_L14_001FB060[];

/* 1 when an entity of the object's group (the 0x7FFF-masked id list D_L14_001FB060[group],
   last id flagged by bit 15) is active (state byte +0x20 not negative) and its class (+0xAA)
   is not 0xF91, else 0.  Only group 0xFF with no list returns 0 before the walk: retail
   walks the list of any other group without testing it for null. */
int func_L14_00423E50(unsigned char *a0)
{
    unsigned short *p;
    unsigned char *base;
    unsigned char *e;

    if (a0[0x21] == 0xFF && D_L14_001FB060[a0[0x21]] == 0)
        return 0;
    p = D_L14_001FB060[a0[0x21]];
    base = D_L14_001B259C;
    for (;;) {
        e = base + ((*p & 0x7FFF) << 8);
        if ((signed char)e[0x20] >= 0 && *(short *)(e + 0xAA) != 0xF91)
            return 1;
        if ((short)*p < 0)
            break;
        p++;
    }
    return 0;
}
