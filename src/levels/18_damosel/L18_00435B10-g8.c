#include "common.h"
extern struct { char pad[0x1830]; u8 *hero; char pad2[0xA60]; int mode; } D_00189E20;
extern float D_L18_001B97C0[];
extern int D_L18_001B1698 __attribute__((sda));
extern int D_L18_001B16B0 __attribute__((sda));
extern int D_L18_001B16D4 __attribute__((sda));
extern int D_L18_001B16D8 __attribute__((sda));
extern char D_L18_002A9C40[], D_L18_00257C80[], D_L18_00257DA0[], D_L18_002BD860[];
extern void func_L18_00435CC8(void);
extern void func_L00_002E6EF8(void);
extern int func_L00_00329520(void *, int);
extern void func_L04_003A1A78(void *), func_L04_003A1C98(void *), func_L04_003A1FA0(void *), func_L04_003A1FE0(void *);
extern void func_L04_003A5C08(void *, float);
/* Updates a ring of linked effects (moby class 3929) by calling the shared effect code for the current state. It does nothing while the hero is in a special mode. */
void func_L18_00435B10(u8 *moby) {
    u8 *vars;
    u8 *hero = gHeroState.hero;
    int effectArgs[13], count;
    if (hero && *(short *)(hero + 0xAA) == 0x45 /* moby class 69 */ && hero[0x20] != 0xFE && hero[0x20] != 0xFD && gHeroState.mode == 0x31) return;
    vars = *(u8 **)(moby + 0x68);
    if (!vars) return;
    if (*(int *)(vars + 0x10) && moby[0x20] && *(int *)(vars + 0x28) != -1 && !IsPointInsideRegion(gCameraPosition_L18, *(int *)(vars + 0x28))) return;
    count = 1;
    if (*(int *)(vars + 0x18) != -1) count = (&D_L18_001B1698)[*(int *)(vars + 0x18)];
    count += *(int *)(vars+0x10);
    effectArgs[0]=0x12;
    effectArgs[1]=count;
    effectArgs[8]=(int)&D_L18_001B16D4;
    effectArgs[9]=(int)&D_L18_001B16D8;
    effectArgs[2]=(int)D_L18_002A9C40;
    effectArgs[3]=(int)D_L18_00257C80;
    effectArgs[4]=(int)&D_L18_001B16B0;
    effectArgs[5]=(int)&D_L18_001B1698;
    effectArgs[6]=(int)D_L18_00257DA0;
    effectArgs[7]=(int)D_L18_002BD860;
    effectArgs[10]=(int)moby;
    effectArgs[11]=(int)RunDamoselEffectCallback;
    effectArgs[12]=(int)AddDrawCallbackToList3;
    switch(moby[0x20]) {
    case 0: InitWaterObject(effectArgs); AddWaterSplashEntry(moby, *(float *)(vars+0x2C));
    case 1: UpdateWaterController(effectArgs); break;
    case 2: AdvanceWaterControllerState(effectArgs); break;
    }
    UpdateWaterRipplePatches_L04(effectArgs);
}
