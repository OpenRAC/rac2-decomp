#include "include_asm.h"
#include "names.h"

/* func_L00_002A9600 in its own unit for the grouped lq/sq profile. Its first two
   callees differ by level (ref_ names). */

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
    char pad2294[0x20];
    unsigned char unk22B4;
    unsigned char unk22B5;
} HeroView_L00_002A9600;

extern char D_00189E20[];
extern void ref_L00_002A9600_00(void);
extern void ref_L00_002A9600_01(void);
extern void func_L00_002D2E68(void);
extern void func_00282AB0(void *, void *, int);
extern void func_002A0F48(void *);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_00310748(void *, int, void *, float, float);

/* Places the hero's moby at the hero and, when it is standing on something,
   updates its two foot contacts. */
void func_L00_002A9600(void)
{
    float footPos[4] __attribute__((aligned(16)));
    float footHeight;
    unsigned char *mobyPtr;

    if (((HeroView_L00_002A9600 *)gHeroState)->unk22B5 != 0)
        ref_L00_002A9600_00();
    else
        ref_L00_002A9600_01();
    if (((HeroView_L00_002A9600 *)gHeroState)->unk22B4 != 4)
        SetHeroObjectsFlagBit();
    ((HeroView_L00_002A9600 *)gHeroState)->moby[0xA8] = 0xFF;
    mobyPtr = ((HeroView_L00_002A9600 *)gHeroState)->moby;
    *(TI128 *)(mobyPtr + 0x10) = ((HeroView_L00_002A9600 *)gHeroState)->position;
    *(TI128 *)(mobyPtr + 0xF0) = ((HeroView_L00_002A9600 *)gHeroState)->unk90;
    CopyMemoryAligned(mobyPtr + 0xC0, gHeroState, 0x30);
    func_002A0F48(((HeroView_L00_002A9600 *)gHeroState)->moby);
    if (((HeroView_L00_002A9600 *)gHeroState)->unk1F0 != 0 || *(int *)(((HeroView_L00_002A9600 *)gHeroState)->moby + 0x98) == 0)
        return;
    *(TI128 *)footPos = ((HeroView_L00_002A9600 *)gHeroState)->position;
    ApplyHeroModeTransformReversed(footPos, footPos, ((HeroView_L00_002A9600 *)gHeroState)->unk254);
    StoreTransformedTableEntry(((HeroView_L00_002A9600 *)gHeroState)->moby, 0, footPos, ((HeroView_L00_002A9600 *)gHeroState)->unk264, ((HeroView_L00_002A9600 *)gHeroState)->unk250 - ((HeroView_L00_002A9600 *)gHeroState)->unk254);
    footHeight = ((HeroView_L00_002A9600 *)gHeroState)->unk264 + 0.05f;
    *(TI128 *)footPos = ((HeroView_L00_002A9600 *)gHeroState)->position;
    ApplyHeroModeTransformReversed(footPos, footPos, footHeight);
    StoreTransformedTableEntry(((HeroView_L00_002A9600 *)gHeroState)->moby, 1, footPos, ((HeroView_L00_002A9600 *)gHeroState)->unk264, ((HeroView_L00_002A9600 *)gHeroState)->unk250 - footHeight);
}
