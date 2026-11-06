/* func_L00_002A9460: needs -frac2-sticky-volatile-refs (reorg stops at the second qcopy asm); see docs/COMPILER-NOTES.md. */
#include "common.h"

/* Its first two callees differ by level (ref_ names); func_L00_002ADF80 is C in
   L00_002A6420.c with the same 27 places. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad000[0x80];
    TI128 position;
    TI128 unk90;
    char padA0[0x150];
    short unk1F0;
    char pad1F2[0x5E];
    float unk250;
    float unk254;
    char pad258[0xC];
    float unk264;
    char pad268[0x2028];
    unsigned char *moby;
    char pad2294[0x8];
    int unk229C;
} HeroView_L00_002A9460;

extern char D_00189E20[];
extern void func_L00_002A75D8(void);
extern void func_L00_002A76B8(void);
extern void func_00282AB0(void *, void *, int);
extern void func_002A0F48(void *);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_00310748(void *, int, void *, float, float);
extern int func_L00_002ADF80(void);


void func_L00_002A9460(void)
{
    float v[4] __attribute__((aligned(16)));
    float t, gap;
    unsigned char *m;

    ((HeroView_L00_002A9460 *)D_00189E20)->moby[0xA8] = 0xFF;
    qcopy(((HeroView_L00_002A9460 *)D_00189E20)->moby + 0x10, &((HeroView_L00_002A9460 *)D_00189E20)->position);
    func_L00_002A75D8();
    qcopy(((HeroView_L00_002A9460 *)D_00189E20)->moby + 0xF0, &((HeroView_L00_002A9460 *)D_00189E20)->unk90);
    func_L00_002A76B8();
    func_00282AB0(((HeroView_L00_002A9460 *)D_00189E20)->moby + 0xC0, D_00189E20, 0x30);
    func_002A0F48(((HeroView_L00_002A9460 *)D_00189E20)->moby);
    m = ((HeroView_L00_002A9460 *)D_00189E20)->moby;
    if ((*(unsigned char **)(m + 0x24))[6] != 0)
        m[0x63] = 0x10;
    else
        m[0x63] = 0x10;
    if (((HeroView_L00_002A9460 *)D_00189E20)->unk1F0 != 0 || *(int *)(((HeroView_L00_002A9460 *)D_00189E20)->moby + 0x98) == 0)
        return;
    qcopy(v, &((HeroView_L00_002A9460 *)D_00189E20)->position);
    func_L00_002D3778(v, v, ((HeroView_L00_002A9460 *)D_00189E20)->unk254);
    gap = ((HeroView_L00_002A9460 *)D_00189E20)->unk250 - ((HeroView_L00_002A9460 *)D_00189E20)->unk254;
    if (gap < 0.05f)
        gap = 0.05f;
    func_L00_00310748(((HeroView_L00_002A9460 *)D_00189E20)->moby, 0, v, ((HeroView_L00_002A9460 *)D_00189E20)->unk264, gap);
    t = ((HeroView_L00_002A9460 *)D_00189E20)->unk264 + 0.05f;
    if (((HeroView_L00_002A9460 *)D_00189E20)->unk229C == 4)
        t += 0.15f;
    if (func_L00_002ADF80() != 0)
        t = ((HeroView_L00_002A9460 *)D_00189E20)->unk254;
    qcopy(v, &((HeroView_L00_002A9460 *)D_00189E20)->position);
    func_L00_002D3778(v, v, t);
    gap = ((HeroView_L00_002A9460 *)D_00189E20)->unk250 - t;
    if (gap < 0.05f)
        gap = 0.05f;
    func_L00_00310748(((HeroView_L00_002A9460 *)D_00189E20)->moby, 1, v, ((HeroView_L00_002A9460 *)D_00189E20)->unk264, gap);
}
