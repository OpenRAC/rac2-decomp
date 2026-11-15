#include "include_asm.h"

/* This unit is built with -G8: these bodies reach a global through $gp. */

extern char D_L03_00282D40[];

extern int D_L03_001B2850 __attribute__((sda));

extern int D_001A72E0;

extern int D_L03_001AD390;

extern void func_35E6B8(void);

extern void func_35E450(void);

extern void func_35E728(void);

extern void func_37CA78(unsigned int, unsigned long);

/* Sets up the Endako sky effect each frame and slowly scrolls a texture offset that wraps around at 1.0. */
void func_L03_002FDB10(void) {
    float *scroll;

    func_35E6B8();
    D_L03_001B2850 = (int)D_L03_00282D40;
    func_35E450();
    func_35E728();
    func_37CA78(0x47, 0x5360B);
    func_37CA78(0x4E, 0x1000000 | (D_001A72E0 >> 13));
    scroll = (float *)(D_L03_001AD390 + 0x74);
    *scroll += 0.011100001f;
    if (*scroll > 1.0f)
        *scroll -= 1.0f;
}
