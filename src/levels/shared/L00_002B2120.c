#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x2290];
    char *moby;
    int state;
    char pad2298[0x229C - 0x2298];
    int mode;
    char pad22A0[0x22B7 - 0x22A0];
    unsigned char b22B7;
    char pad22B8[0x22BC - 0x22B8];
    unsigned char b22BC;
    unsigned char pad22BD;
    unsigned char b22BE;
} Hero_2B2120;

extern Hero_2B2120 D_00189E20;
extern int func_L00_002ADF80(void);
extern void func_L00_002AFBF0(void);
extern void func_L00_002B0968(char *);
extern void func_L00_002D4A38(void);
extern void func_L00_002A7E60(void);
extern void func_L00_002B1F90(void);

/* Sets the hero lock flags for the current state, then updates the hero item slots and related effects. */
void func_L00_002B2120(void)
{
    int mode = gHeroState.mode;

    if ((unsigned int)(mode - 0x15) < 2 || mode == 0x1F || IsHeroInSpecialKindOrMode() != 0) {
        gHeroState.b22B7 = 1;
        gHeroState.b22BC = 1;
    }
    if (IsHeroInSpecialKindOrMode() != 0 || gHeroState.state == 0x31 || gHeroState.mode == 3 ||
        gHeroState.state == 0x12 || gHeroState.state == 0x82)
        gHeroState.b22BE = 1;
    else
        gHeroState.b22BE = 0;
    SpawnHeroItemMobies();
    update_hero_item_mobys(gHeroState.moby);
    FadeLevelGlowColors();
    UpdateEquippedItemGlow();
    UpdateHeroSlotCallbacks();
}
