#include "include_asm.h"
#include "names.h"

typedef signed short s16;
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(s32 a0);
extern u8 **level_get_object_list(void);
extern s32 level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag_pal(u8 *a0, s32 a1);
extern void func_L05_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_L05_0037D608(u8 *a0, u8 *a1, f32 f12);
extern void feltzin_mission_reward_update_pal(u8 *a0, s32 a1);
extern s32 g_feltzin_challenge_active __attribute__((sda));
extern s32 g_feltzin_challenge_state[];
extern s32 g_feltzin_mission_index;
extern u8 *g_feltzin_enemy_table;

/* Third Feltzin mission: on the first frame starts the challenge and spawns the listed objects, then pays the reward once the mission is complete. */
void feltzin_mission_three_update_pal(u8 *actor) {
    s32 remaining;
    s32 object_count;
    u8 **objects;

    if (g_feltzin_challenge_active == 0) {
        g_feltzin_challenge_state[11] = 0;
        g_feltzin_challenge_active = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        object_count = level_get_saved_value();
        if (object_count > 0) {
            remaining = object_count;
            do {
                if (*(s16 *)(*objects + 0xAA) == 0xF73) {
                    entry_spawn_list_objects_with_flag_pal(*objects, 1);
                    func_L05_0037CEE0(*objects, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*objects, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                }
                remaining--;
                objects++;
            } while (remaining);
        }
    }
    if (g_feltzin_challenge_state[4] == 0 && g_feltzin_mission_index >= 6)
        feltzin_mission_reward_update_pal(actor, 2);
}
