#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef struct GornConfig { int words[10]; } GornConfig;
extern char D_L10_00221CD0[];
extern GornConfig D_L10_002A3C70[];
extern int D_L10_001B13A0 __attribute__((sda));
extern int D_L10_001B13A4 __attribute__((sda));
extern void *D_L10_001B1400 __attribute__((sda));
extern void *D_L10_001B1404 __attribute__((sda));
extern int D_L10_001B1438 __attribute__((sda));
extern int D_L10_001B1440 __attribute__((sda));
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern int func_002ED8A0(int);
extern void func_L05_00379F28(int);
extern void func_L05_0037D6E8(void);
extern void func_L05_00379F68(void);
extern void func_L05_00445A98(void);
extern void func_0029F338(void *);

/* Resets the mission (the 004235A0 body without the carried-object test, with two more counters)'s shared counters and removes its two temporary objects. */
void func_L10_00423698(void) {
    char *state;
    int i;
    InitAllRegisteredEntries();
    SetPlayerStateField13(1);
    state = D_L10_00221CD0;
    D_L10_001B13A0 = -2;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0xC) = 0;
    D_L10_001B1438 = 1;
    *(int *)(state + 0x2C) = 1;
    *(int *)(state + 0x28) = 100;
    gMissionInitialized = 0;
    *(int *)(state + 0x14) = 0;
    i = FindLastUsedChainEntry(6);
    D_L10_001B1440 = 0;
    *(float *)(state + 0x30) = 8.0f;
    D_L10_002A3C70[i].words[5] = D_L10_002A3C70[i].words[4];
    SetPlayerStateField15(0);
    ResetTableWorkingValues();
    ClearLevelObjectRecords();
    SaveShipTransformState();
    if (D_L10_001B1400) { MarkMobySpawned(D_L10_001B1400); D_L10_001B1400 = 0; }
    if (D_L10_001B1404) { MarkMobySpawned(D_L10_001B1404); D_L10_001B1404 = 0; }
}
