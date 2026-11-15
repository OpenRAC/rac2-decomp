#include "names.h"
extern unsigned int D_L00_001B26B4_1;
extern int D_L00_001B26B0[] __attribute__((sda));

extern int D_L00_001ADB2C __attribute__((sda));
extern unsigned char D_L00_0022FF40[];
extern int D_L00_00231340[][4];
extern int D_L00_00231A60[][8];
extern int D_L00_00231950[];
extern int D_L00_00231540[];
extern void *D_L00_001B26A8[] __attribute__((sda));
extern void func_L00_003BB600(void);
extern void func_L00_003C58E0(void);
extern void func_L00_003CA470(void);
extern void func_L00_003D5320(void);
extern void func_L00_003E5328(void);
extern void func_L00_003ECB00(void);
extern void func_L00_003EF548(void);
extern void func_L00_003F1448(void);
extern void func_L00_00387EF0(void);
extern void func_L00_0038A968(void);
extern void func_L00_003F8E08(void);
extern void func_L00_004115E8(void);
extern void func_L00_0037FF98(void);
extern void *func_00302A20(void *);

/* Clears the level's object tables, runs each part's setup function and creates the first object. */
void func_L00_0037E418(void)
{
    unsigned char *tablePtr;
    int i;
    int empty;
    union { int q __attribute__((mode(TI))); float f[4]; } v;
    unsigned char *newObject;
    D_L00_001ADB2C = 0;
    tablePtr = D_L00_0022FF40;
    do {
        tablePtr[1] = 0;
        *(int *)(tablePtr + 0x40) = 0;
        tablePtr += 0x50;
    } while ((int)tablePtr < (int)(D_L00_0022FF40 + 0x1400));
    for (i = 31; i >= 0; i--) gOwnerKeyTable[i][1] = 0;
    for (i = 127; i >= 0; i--) D_L00_00231A60[i][7] = 0;
    empty = -1;
    for (i = 63; i >= 0; i--) D_L00_00231950[i] = empty;
    D_L00_00231950[64] = 0;
    D_L00_00231540[256] = 0;
    ClearEffectSlotTables();
    ClearTrailEffectPointer();
    ClearSparkRecords();
    ClearFourWordTable();
    ClearSavedBlastPointer();
    ClearSynthenoidSlots();
    ClearEffectFlag();
    ClearLightningBurstActiveFlag();
    ResetStateRecords();
    ResetStateWords();
    InitHealthDrainSlots();
    InitShotTables();
    v.q = 0;
    v.f[0] = 5.0f;
    v.f[3] = 1.0f;
    v.f[1] = 5.0f;
    v.f[2] = 5.0f;
    newObject = SpawnClass1007Object(&v);
    D_L00_001B26A8[0] = newObject;
    *(int *)(newObject + 0x98) = 0;
    *(unsigned short *)(newObject + 0x34) |= 2;
    D_L00_001B26B0[0] = 0;
    D_L00_001B26B4_1 = 0;
    CollectClass135FObjects();
}
