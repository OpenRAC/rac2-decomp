#include "common.h"

extern u16 *D_L20_001FBB20[];
extern u8 *D_L20_001B2F9C[] __attribute__((sda));
extern int D_L20_001B2FB8 __attribute__((sda));

extern void func_002A6C58(void *, int, int);
extern void func_L18_003F74B8(u8 *, int);

/* For every entity of the object's group (the id list D_L20_001FBB20[self[0x21]], ids masked
   with 0x7FFF, 0x100-byte records at D_L20_001B2F9C) of class 0xB69 whose state byte is neither
   0xFE nor 0xFD, calls func_002A6C58(e, 0, 1) and func_L18_003F74B8(e, 0).
   Own -G8 unit: D_L20_001B2FB8 is read through $gp.  The list walk is the usual group macro;
   its doubled p test leaves the exit test at the bottom, so retail's `b test` entry and the
   %hi copy in its delay slot come out (see func_L02_003EB138).  The entity bank is an `sda`
   array of unknown size, which gives retail's absolute lui/lw load in this -G8 unit. */
void func_L20_00447640(u8 *self) {
    u16 *p;
    u8 *e;

    if (self[0x21] == 0xFF)
        return;
    for (p = D_L20_001FBB20[self[0x21]];
         self[0x21] != 0xFF && self[0x21] <= D_L20_001B2FB8 && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L20_001FBB20[self[0x21]]);
         p++) {
        e = D_L20_001B2F9C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xB69 && e[0x20] != 0xFE && e[0x20] != 0xFD) {
            func_002A6C58(e, 0, 1);
            func_L18_003F74B8(e, 0);
        }
    }
}
