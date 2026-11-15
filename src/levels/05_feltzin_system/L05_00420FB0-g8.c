#include "names.h"
typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

extern void func_003404B8(void);
extern void func_0037B210(void);
extern void func_00379F18(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern void func_0037B280(u8 *a0, s32 a1);
extern void func_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void UpdateFeltzinMissionReward(u8 *a0, s32 a1);

extern s32 D_L05_001B1364 __attribute__((sda));
extern s32 D_L05_00221D10[];
extern s32 D_L05_001B2048;
extern u8 *D_L05_001B2614;

/* Controls the third Feltzin mission: sets up the scene once, then starts the reward. */
void feltzin_mission_three_update(u8 *moby) {
    s32 remaining;
    s32 count;
    u8 **objects;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        func_003404B8();
        func_0037B210();
        func_00379F18(0);
        objects = func_00379EB8();
        count = func_00379EC8();
        if (count > 0) {
            remaining = count;
            do {
                if (*(s16 *)(*objects + 0xAA) == 0xF73 /* moby class 3955 */) {
                    func_0037B280(*objects, 1);
                    func_0037CEE0(*objects, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                    func_0037D608(*objects, (u8 *)D_L05_001B2614 + (D_L05_00221D10[0] << 7) + 0x30, 64.0f);
                }
                remaining--;
                objects++;
            } while (remaining);
        }
    }
    if (D_L05_00221D10[4] == 0 && D_L05_001B2048 >= 6)
        UpdateFeltzinMissionReward(moby, 2);
}
