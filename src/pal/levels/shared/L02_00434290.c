#include "include_asm.h"

typedef unsigned char u8;
extern void func_0031E6A0(void *, int, int);
extern int func_0031E770(int);
extern void func_0031E3C0(void *, int, int, int);

/* Restarts the record's resident effect once it has settled, picking the
   variant by the resident query and the record's own byte 0x43. */
void func_PAL_L02_00434290(u8 *a0) {
    u8 *s0 = a0;

    if (*(u8 *)(s0 + 0x20) != 0)
        return;
    func_0031E6A0(s0, 1, -1);
    if (func_0031E770(2) != 0) {
        if (*(u8 *)(s0 + 0x43) != 0)
            func_0031E3C0(s0, 0, 0, 0x8);
    } else {
        if (*(u8 *)(s0 + 0x43) != 1)
            func_0031E3C0(s0, 1, 0, 0x8);
    }
}

