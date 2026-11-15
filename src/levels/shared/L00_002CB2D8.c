#include "include_asm.h"
#include "names.h"
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

/* Applies a pending hero change request: counts it in the statistics and switches the hero to the new value. */
void func_L00_002CB2D8(void)
{
    int newValue;
    int altValue;

    if (gHeroState.f2538 == 0)
        return;
    altValue = D_001A7398;
    newValue = D_001A7A04;
    if (gHeroState.f1248 == 10)
        newValue = altValue;
    gHeroState.f2538 = 0;
    if (newValue == 0)
        return;
    if (gHeroState.f1248 == D_001A7A04)
        return;
    if (gProgressStatistics.count <= 0xFFFE)
        gProgressStatistics.count++;
    if (D_001A7390 > gProgressStatistics.best)
        gProgressStatistics.best = D_001A7390;
    gProgressStatistics.mask = gProgressStatistics.mask | (1 << gCurrentMapIndex) | 0x80000000;
    gHeroState.f22C8 = ReturnArgument_L00_2(newValue);
    gHeroState.h24F8 = 0;
    gHeroState.h24FA = 0;
}
