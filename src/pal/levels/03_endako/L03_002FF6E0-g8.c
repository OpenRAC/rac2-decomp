#include "include_asm.h"

extern char D_L03_00282D40[];
extern int D_L03_001B2850 __attribute__((sda));
extern int D_001A72E0;
extern int D_001AD390;
extern void func_002E37B0(void);
extern void func_002E3548(void);
extern void func_002E3820(void);
extern void func_002FC560(unsigned int, unsigned long);

void func_PAL_L03_002FF6E0(void) {
    float *p;

    func_002E37B0();
    D_L03_001B2850 = (int)D_L03_00282D40;
    func_002E3548();
    func_002E3820();
    func_002FC560(0x47, 0x5360B);
    func_002FC560(0x4E, 0x1000000 | (D_001A72E0 >> 13));
    p = (float *)(D_001AD390 + 0x74);
    *p += 0.013320001f;
    if (*p > 1.0f)
        *p -= 1.0f;
}
