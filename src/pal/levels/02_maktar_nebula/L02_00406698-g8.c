#include "include_asm.h"
typedef unsigned int u32;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern char D_L02_001B1730[8] __attribute__((sda));
extern float D_L02_001B1750 __attribute__((sda));
extern float D_L02_001B1754;
extern u32 D_L02_001B1758 __attribute__((sda));
extern u32 D_L02_001B175C;
extern u32 D_L02_001B1760;
extern u32 D_L02_001B1764;
extern u32 D_L02_001B1768;
extern u32 D_L02_001B176C;
extern u32 D_L02_001B1770 __attribute__((sda));
extern u32 D_L02_001B1774;
extern u32 D_L02_001B1778;
extern s32 D_L02_001B30C8;

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern void func_002BAE50(void *, void *, u32, s32, s32, s32, s32, s32);

/* func_PAL_L02_00406698, the PAL copy of func_L02_00401D38: the same C, where 1/60 becomes 1/50
   and the three picks of func_002A7820 are scaled to 50 Hz. Retail shows no interblock motion in
   this loop: i and p step in its last block, so this unit builds with -fno-sched-interblock and
   p steps at the end of the body. */
void func_PAL_L02_00406698(char *a0, char *a1) {
    float v0[4];
    float v1[4];
    float v2[4];
    float *w = v1;
    char *p = D_L02_001B1730;
    s32 i;
    float f;

    for (i = 1; i >= 0; i--) {
        func_00283098(v0, p, a0 + 0xC0);
        func_00282CC0(v0, v0, a0 + 0x10);
        *(TI128 *)v2 = 0;
        f = func_002A7878(D_L02_001B1750, D_L02_001B1754);
        v2[2] = -(f * 0.020000001f);
        *(TI128 *)v1 = *(TI128 *)v2;
        func_00282CC0(v1, v1, a1);
        if (D_L02_001B30C8 & 1) {
            func_002BAE50(v0, w, D_L02_001B1758, D_L02_001B175C, ((s32)func_002A7820(0x12, 0x16) * 5 + 2) / 6, D_L02_001B1770, -10, 1);
        } else {
            func_002BAE50(v0, w, D_L02_001B1760, D_L02_001B1764, ((s32)func_002A7820(0x14, 0x18) * 5 + 2) / 6, D_L02_001B1774, -10, 1);
        }
        func_002BAE50(v0, w, D_L02_001B1768, D_L02_001B176C, ((s32)func_002A7820(0xA, 0xF) * 5 + 2) / 6, D_L02_001B1778, -10, 1);
        p += 0x10;
    }
}
