#include "include_asm.h"
/* func_PAL_L00_002CB6A8, the PAL copy of func_L00_002CB2D8. */
typedef struct {
    char pad0[0x1248];
    int f1248;
    char pad124C[0x22C8 - 0x124C];
    int f22C8;
    char pad22CC[0x24F8 - 0x22CC];
    short h24F8;
    short h24FA;
    char pad24FC[0x2538 - 0x24FC];
    int f2538;
} Hero_2CB2D8;

typedef struct {
    char pad0[0x174];
    unsigned short count;
    char pad176[2];
    unsigned int best;
    unsigned int mask;
} Stats_2CB2D8;

extern Hero_2CB2D8 D_00189E20;
extern Stats_2CB2D8 D_0018C750;
extern int D_001A7A04 __attribute__((section(".sdata")));
extern int D_001A7398 __attribute__((section(".sdata")));
extern unsigned int D_001A7390 __attribute__((section(".sdata")));
extern int D_001A79F0 __attribute__((section(".sdata")));
extern int func_L00_002D3FB0(int);

void func_PAL_L00_002CB6A8(void)
{
    int v;
    int alt;

    if (D_00189E20.f2538 == 0)
        return;
    alt = D_001A7398;
    v = D_001A7A04;
    if (D_00189E20.f1248 == 10)
        v = alt;
    D_00189E20.f2538 = 0;
    if (v == 0)
        return;
    if (D_00189E20.f1248 == D_001A7A04)
        return;
    if (D_0018C750.count <= 0xFFFE)
        D_0018C750.count++;
    if ((((int)(D_001A7390) * 5 + 2) / 6) > D_0018C750.best)
        D_0018C750.best = ((int)(D_001A7390) * 5 + 2) / 6;
    D_0018C750.mask = D_0018C750.mask | (1 << D_001A79F0) | 0x80000000;
    D_00189E20.f22C8 = func_L00_002D3FB0(v);
    D_00189E20.h24F8 = 0;
    D_00189E20.h24FA = 0;
}
