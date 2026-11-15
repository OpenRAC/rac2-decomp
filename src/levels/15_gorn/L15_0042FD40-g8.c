#include "names.h"
typedef struct StageSetup {
    int initial;
    char pad04[0x10];
    int count;
    char pad18[0x10];
    int limit;
    int timer;
    float scale;
} StageSetup;

typedef struct StageRecord {
    int words[10];
} StageRecord;

extern int D_L15_001B1530 __attribute__((sda));
extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B15C4 __attribute__((sda));
extern StageSetup D_L15_00221E10;
extern StageRecord D_L15_0029FD80[];
extern int func_002ED8A0(int);
extern void func_L05_00379F28(int);
extern void func_L05_0037D6E8(void);
extern void func_L05_00379F68(void);

/* Resets the Gorn stage counters and restores the selected record's value. */
void func_L15_0042FD40(void)
{
    StageSetup *stage = &D_L15_00221E10;
    int recordIndex;

    D_L15_001B1530 = -2;
    D_L15_001B15C4 = 1;
    stage->timer = 1;
    stage->limit = 100;
    D_L15_001B1534 = 0;
    stage->count = 0;
    recordIndex = FindLastUsedChainEntry(6);
    stage->scale = 8.0f;
    D_L15_0029FD80[recordIndex].words[5] = D_L15_0029FD80[recordIndex].words[4];
    SetPlayerStateField15(0);
    ResetTableWorkingValues();
    ClearLevelObjectRecords();
}

