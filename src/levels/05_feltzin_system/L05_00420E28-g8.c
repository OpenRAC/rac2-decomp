#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

extern s32 func_00282948(u8 *a0);
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(s32 a0);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_L05_0037B280(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_00420788(u8 *a0, s32 a1);
extern void func_L05_004209D8(u8 *a0, s32 a1);

extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_001B2048 __attribute__((sda));
typedef struct { s32 count; u8 pad04[12]; s32 active; u8 pad14[24]; s32 reset; } FeltzinState;
extern u8 D_L05_00221D10[];
extern u8 D_L05_001B3550[] __attribute__((section(".sdata")));
extern u8 *D_L05_001B2614;

/* Controls the second Feltzin mission: sets up the scene once, then starts the reward when the
   timer is done or reports a failure when the time runs out. */
void func_L05_00420E28(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 **objects;
    u32 count;
    s32 index;
    s32 objectCount;

    FastFloatHelperD(D_L05_001B3550);
    if (D_L05_001B1364 == 0) {
        ((FeltzinState *)D_L05_00221D10)->reset = 0;
        *(s32 *)D_L05_001B3550 = 0x1C20;
        *(s32 *)(vars + 0x44) = 0x1C20;
        D_L05_001B1364 = 1;
        music_Unpause();
        InitAllRegisteredEntries();
        SetPlayerStateField13(0);
        objects = GetLevelObjectList();
        objectCount = GetLevelSavedValue();
        if (objectCount > 0) {
            count = objectCount;
            do {
                u8 *object = *objects;

                if (*(s16 *)(object + 0xAA) == 0x10F5 /* moby class 4341 */) {
                    f32 scale = 64.0f;

                    SpawnEntryListObjectsWithFlag(object, 1);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037CEE0(*objects, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                    index = ((FeltzinState *)D_L05_00221D10)->count;
                    func_L05_0037D608(*objects, (u8 *)D_L05_001B2614 + (index << 7) + 0x30, scale);
                }
                count--;
                objects++;
            } while (count != 0);
        }
    }
    if (((FeltzinState *)D_L05_00221D10)->active == 0 && D_L05_001B2048 >= 6) {
        UpdateFeltzinMissionReward(moby, 1);
        return;
    }
    if (FastFloatHelperD(vars + 0x44) != 0)
        HandleFeltzinMissionFailure(moby, 1);
}
