/* Picks the hero's current weapon animation id. Own unit: -frac2-gcse-unsplit-edges lets PRE
   hoist the hero's high half above the first test, while each block forms its own low half. */
#include "include_asm.h"
#include "names.h"
typedef unsigned char u8; typedef short s16; typedef unsigned short u16; typedef int s32; typedef unsigned int u32; typedef float f32;
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;
extern char D_00189E20[];
extern u8 D_00139568[];
extern char D_L04_0027B470[];
extern int func_L00_002ADEA0(int);
typedef struct { u8 pad[0x28]; int v; } WeaponEntry;
/* Returns the animation id for the weapon the hero is holding. */
int func_L04_002CC748(char *a0)
{
    if (a0 != 0 && ((Hero *)gHeroState)->b[0x22BA] != 0 && ((Hero *)gHeroState)->h[0x24EC / 2] == 0) {
        int idx = hero_slot_item_id(0);
        return ((WeaponEntry *)(D_L04_0027B470 + gItemSlotToRecord[idx] * 224))->v;
    }
    if (((Hero *)gHeroState)->i[0x24CC / 4] != 1)
        return ((Hero *)gHeroState)->b[0x1492] ? 0x67 : 0;
    return 0x51;
}
