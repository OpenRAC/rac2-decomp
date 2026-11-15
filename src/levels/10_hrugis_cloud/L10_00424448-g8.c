#include "common.h"

extern int D_L10_001B13A4 __attribute__((sda));
extern int D_L10_00221CFC __attribute__((section(".data")));
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern unsigned char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(void *, int);
extern void func_L10_00425798(void);
extern void func_L10_00425410(int, void *);
extern void *func_L05_00379ED0(int);
extern int func_L05_0037B3A0(void *);
extern void func_L10_00423DC8(void *, int);

/* Mission controller for the third challenge: sets up on the first frame, then ends the round
   once every class 3982 target is gone. */
void func_L10_00424448(void *object)
{
    unsigned char **entries;
    int i, count;

    if (!gMissionInitialized) {
        D_L10_00221CFC = 0;
        gMissionInitialized = 1;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        entries = GetLevelObjectList();
        count = GetLevelSavedValue();
        for (i = 0; i < count; i++) {
            if (*(short *)(entries[i] + 0xAA) == 0xF8E /* moby class 3982 */)
                SpawnEntryListObjectsWithFlag(entries[i], 1);
        }
        DestroyLeftoverCloudObjects();
        SpawnCloudObjects(0x32, (void *)0xC);
    }
    if (!CountReadyListObjects(FindLevelObjectByClassId(0xF8E /* moby class 3982 */)))
        FinishMissionAndGrantReward(object, 2);
}
