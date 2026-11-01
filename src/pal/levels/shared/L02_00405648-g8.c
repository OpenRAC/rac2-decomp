#include "include_asm.h"

#include "common.h"
extern float D_L02_001B1720 __attribute__((sda));
extern float D_L02_001B1724;
extern int D_L02_001B1710 __attribute__((sda));
extern int D_L02_001B1714 __attribute__((nosda));
extern int D_L02_001B1718 __attribute__((nosda));
extern int D_L02_001B171C __attribute__((nosda));
extern char D_L02_001A8F20[];
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_PAL_002BE880(void *, void *, float, u32, s32, s32);

void func_PAL_L02_00405D00(void *a0)
{
    void *s1 = a0;
    void *s0;
    int local[2];
    float f20;
    float r;
    int t0;

    s0 = *(void **)(s1 + 0x68);
    r = func_002A7878(D_L02_001B1720, D_L02_001B1724);
    f20 = r * 210000.0f;
    t0 = ((s32)(func_002A7820(*(unsigned char *)(s0 + 0x75), *(unsigned char *)(s0 + 0x76))) * 5 + 2) / 6;
    if (*(short *)(s1 + 0xAA) == 0xB5A) {
        local[0] = D_L02_001B1710;
        local[1] = D_L02_001B1714;
    } else {
        local[0] = D_L02_001B1718;
        local[1] = D_L02_001B171C;
    }
    func_PAL_002BE880(s1 + 0x10, D_L02_001A8F20, f20, D_L02_001B1710, D_L02_001B1714, t0);
}
