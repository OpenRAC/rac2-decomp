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
extern void func_PAL_L05_00425FB0(u8 *a0, s32 a1);
extern s32 g_feltzin_challenge_active __attribute__((sda));
extern s32 g_feltzin_challenge_state[];
extern s32 g_feltzin_mission_index;
extern u8 *g_feltzin_enemy_table;

void feltzin_mission_three_update_pal(u8 *arg0) {
    s32 n;
    s32 count;
    u8 **p;

    if (g_feltzin_challenge_active == 0) {
        g_feltzin_challenge_state[11] = 0;
        g_feltzin_challenge_active = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        p = level_get_object_list();
        count = level_get_saved_value();
        if (count > 0) {
            n = count;
            do {
                if (*(s16 *)(*p + 0xAA) == 0xF73) {
                    entry_spawn_list_objects_with_flag_pal(*p, 1);
                    func_L05_0037CEE0(*p, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                    func_L05_0037D608(*p, (u8 *)g_feltzin_enemy_table + (g_feltzin_challenge_state[0] << 7) + 0x30, 64.0f);
                }
                n--;
                p++;
            } while (n);
        }
    }
    if (g_feltzin_challenge_state[4] == 0 && g_feltzin_mission_index >= 6)
        func_PAL_L05_00425FB0(arg0, 2);
}
