/* func_PAL_L18_003FF408, the PAL copy of func_L18_003FB308: the same C, where rename func_L18_003FB620 becomes func_PAL_L18_003FF768; scale D_L18_001B0580; scale D_L18_001B0580. */
#include "common.h"

extern int D_L18_001B0580 __attribute__((sda));
extern float D_L18_001B0584 __attribute__((sda));
extern int D_L18_001B0588 __attribute__((sda));
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A7750(u8 *, int, int);
extern int func_002B3868(u8 *);
extern void func_002E5DA0(int, int, u8 *, int);
extern void func_PAL_L18_003FF768(u8 *);

void func_PAL_L18_003FF408(u8 *a0) {
    u8 *s = *(u8 **)(a0 + 0x68);
    switch (a0[0x20]) {
    case 0:
        qcopy_nc(s, a0 + 0x10);
        func_00282F20(s + 0x10, a0 + 0xC0, D_L18_001B0584 / (((int)(D_L18_001B0580) * 5 + 2) / 6));
        func_002A7750(a0, 1, -1);
        *(int *)(s + 0x20) = 0;
        break;
    case 1: {
        if (*(int *)(s + 0x20) >= 2) {
            func_00282CF0(a0 + 0x10, a0 + 0x10, s + 0x10);
            func_00282CC0(D_L18_001B281C[0] + (*(int *)(s + 0x24) << 8) + 0x10,
                         D_L18_001B281C[0] + (*(int *)(s + 0x24) << 8) + 0x10,
                         s + 0x10);
            --*(int *)(s + 0x20);
        } else if (*(int *)(s + 0x20) > 0) {
            qcopy_nc(a0 + 0x10, s);
            qcopy_nc((u8 *)((*(int *)(s + 0x24) << 8) +
                           (int)D_L18_001B281C[0] + 0x10), s);
            --*(int *)(s + 0x20);
        }
        break;
    }
    case 2:
        if (func_002B3868(a0))
            func_002E5DA0(0, 0, a0, 0x1152);
        if (*(int *)(s + 0x20) < (((int)(D_L18_001B0580) * 5 + 2) / 6)) {
            func_00282CC0(a0 + 0x10, a0 + 0x10, s + 0x10);
            func_00282CF0(D_L18_001B281C[0] + (*(int *)(s + 0x24) << 8) + 0x10,
                         D_L18_001B281C[0] + (*(int *)(s + 0x24) << 8) + 0x10,
                         s + 0x10);
            ++*(int *)(s + 0x20);
        }
        if (*(int *)(s + 0x28))
            func_PAL_L18_003FF768(a0);
        if (D_L18_001B0588 < *(u16 *)(a0 + 0x96))
            func_002A7750(a0, 1, -1);
        break;
    }
    if (*(u16 *)(a0 + 0x96) <= 0xFFFEu)
        ++*(u16 *)(a0 + 0x96);
}
