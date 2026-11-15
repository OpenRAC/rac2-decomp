/* func_L00_002A9460: needs -frac2-sticky-volatile-refs (reorg stops at the second qcopy asm); see docs/build/compiler-notes.md. */
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


/* Copies the hero position and facing onto the hero object each frame. When it is on the ground it updates the two foot contact points. */
void func_L00_002A9460(void)
{
    float footPos[4] __attribute__((aligned(16)));
    float footHeight, footGap;
    unsigned char *mobyPtr;

    ((HeroView_L00_002A9460 *)gHeroState)->moby[0xA8] = 0xFF;
    qcopy(((HeroView_L00_002A9460 *)gHeroState)->moby + 0x10, &((HeroView_L00_002A9460 *)gHeroState)->position);
    UpdateHeroModelTilt();
    qcopy(((HeroView_L00_002A9460 *)gHeroState)->moby + 0xF0, &((HeroView_L00_002A9460 *)gHeroState)->unk90);
    UpdateHeroModelWobble();
    CopyMemoryAligned(((HeroView_L00_002A9460 *)gHeroState)->moby + 0xC0, gHeroState, 0x30);
    func_002A0F48(((HeroView_L00_002A9460 *)gHeroState)->moby);
    mobyPtr = ((HeroView_L00_002A9460 *)gHeroState)->moby;
    if ((*(unsigned char **)(mobyPtr + 0x24))[6] != 0)
        mobyPtr[0x63] = 0x10;
    else
        mobyPtr[0x63] = 0x10;
    if (((HeroView_L00_002A9460 *)gHeroState)->unk1F0 != 0 || *(int *)(((HeroView_L00_002A9460 *)gHeroState)->moby + 0x98) == 0)
        return;
    qcopy(footPos, &((HeroView_L00_002A9460 *)gHeroState)->position);
    ApplyHeroModeTransformReversed(footPos, footPos, ((HeroView_L00_002A9460 *)gHeroState)->unk254);
    footGap = ((HeroView_L00_002A9460 *)gHeroState)->unk250 - ((HeroView_L00_002A9460 *)gHeroState)->unk254;
    if (footGap < 0.05f)
        footGap = 0.05f;
    StoreTransformedTableEntry(((HeroView_L00_002A9460 *)gHeroState)->moby, 0, footPos, ((HeroView_L00_002A9460 *)gHeroState)->unk264, footGap);
    footHeight = ((HeroView_L00_002A9460 *)gHeroState)->unk264 + 0.05f;
    if (((HeroView_L00_002A9460 *)gHeroState)->unk229C == 4)
        footHeight += 0.15f;
    if (IsHeroInSpecialKindOrMode() != 0)
        footHeight = ((HeroView_L00_002A9460 *)gHeroState)->unk254;
    qcopy(footPos, &((HeroView_L00_002A9460 *)gHeroState)->position);
    ApplyHeroModeTransformReversed(footPos, footPos, footHeight);
    footGap = ((HeroView_L00_002A9460 *)gHeroState)->unk250 - footHeight;
    if (footGap < 0.05f)
        footGap = 0.05f;
    StoreTransformedTableEntry(((HeroView_L00_002A9460 *)gHeroState)->moby, 1, footPos, ((HeroView_L00_002A9460 *)gHeroState)->unk264, footGap);
}
