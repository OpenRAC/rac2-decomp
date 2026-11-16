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

extern s32 g_feltzin_challenge_active __attribute__((sda));
extern s32 g_feltzin_challenge_state[];
extern s32 g_feltzin_mission_index;
extern u8 *g_feltzin_enemy_table;

/* Controls the third Feltzin mission: sets up the scene once, then starts the reward. */
void feltzin_mission_three_update(u8 *moby) {
    s32 remaining;
    s32 count;
    u8 **objects;

    if (g_feltzin_challenge_active == 0) {
        g_feltzin_challenge_state[11] = 0;
        g_feltzin_challenge_active = 1;
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
                    func_0037CEE0(*objects, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                    func_0037D608(*objects, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                }
                remaining--;
                objects++;
            } while (remaining);
        }
    }
    if (g_feltzin_challenge_state[4] == 0 && g_feltzin_mission_index >= 6)
        UpdateFeltzinMissionReward(moby, 2);
}
