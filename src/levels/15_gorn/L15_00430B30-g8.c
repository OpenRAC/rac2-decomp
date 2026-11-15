#include "names.h"
typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(s32 a0);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_L05_0037B280(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_L15_00430590(u8 *a0, s32 a1);

extern s32 D_L15_001B1534 __attribute__((sda));
typedef struct StageState {
    s32 initial;
    s32 pad04[3];
    s32 active;
    s32 pad14[6];
    s32 timer;
} StageState;
extern StageState D_L15_00221E10;
extern s32 D_L15_001B2148;
extern u8 *D_L15_001B2714;

/* Applies both material passes to matching objects once, then advances the stage. */
void func_L15_00430B30(u8 *moby) {
    s32 remaining;
    s32 count;
    u8 **listPtr;

    if (D_L15_001B1534 == 0) {
        D_L15_00221E10.timer = 0;
        D_L15_001B1534 = 1;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        listPtr = GetLevelObjectList();
        count = GetLevelSavedValue();
        if (count > 0) {
            remaining = count;
            do {
                if (*(s16 *)(*listPtr + 0xAA) == 0xF93 /* moby class 3987 */) {
                    SpawnEntryListObjectsWithFlag(*listPtr, 1);
                    func_L05_0037CEE0(*listPtr, (u8 *)D_L15_001B2714 + (D_L15_00221E10.initial << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*listPtr, (u8 *)D_L15_001B2714 + (D_L15_00221E10.initial << 7) + 0x30, 64.0f);
                }
                remaining--;
                listPtr++;
            } while (remaining);
        }
    }
    if (D_L15_00221E10.active == 0 && D_L15_001B2148 >= 6)
        FinishGornChallengeStage(moby, 1);
}
