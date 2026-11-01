#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_00278E60);

#include "common.h"
struct Rac2Native_00169805055547ed_Rec31cd0302 {
    int v[10];
};
extern struct Rac2Native_00169805055547ed_Rec31cd0302 D_L04_001BCE48[];

/* Store ten integer arguments in the indexed record when the unsigned index is below 32; otherwise leave the table unchanged. */
void func_PAL_00279B50(int p0, int p1, int p2, int p3, int p4, int p5,
                                      int p6, int p7, int p8, int p9, unsigned idx)
{
    if (idx >= 32u)
        return;
    D_L04_001BCE48[idx].v[0] = p0;
    D_L04_001BCE48[idx].v[1] = p1;
    D_L04_001BCE48[idx].v[2] = p2;
    D_L04_001BCE48[idx].v[3] = p3;
    D_L04_001BCE48[idx].v[4] = p4;
    D_L04_001BCE48[idx].v[5] = p5;
    D_L04_001BCE48[idx].v[6] = p6;
    D_L04_001BCE48[idx].v[7] = p7;
    D_L04_001BCE48[idx].v[8] = p8;
    D_L04_001BCE48[idx].v[9] = ((s32)(p9) * 5 + 2) / 6;
}

