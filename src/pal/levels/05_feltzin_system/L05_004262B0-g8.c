#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern int g_feltzin_challenge_active __attribute__((sda));
extern int g_feltzin_no_challenge_flag __attribute__((sda));
extern int g_feltzin_frame_counter __attribute__((sda));
extern int g_feltzin_challenge_data __attribute__((sda));
extern int g_feltzin_challenge_state[];
extern int g_feltzin_mission_index;
extern char *g_feltzin_target_mobys;
extern char g_str_feltzin_transition_src[] SDATA(D_L05_001B1380);
extern char g_str_feltzin_transition_dest[] SDATA(D_L05_001B1370);
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag_pal(char *, int);
extern void func_L05_0037CEE0(char *, void *, float);
extern void func_L05_0037D608(char *, void *, float);
extern int math_fast_float_d(void *);
extern void ship_start_transition_pal(void *, void *, int);
extern void ship_point_camera_at_target(void *, void *);
extern void feltzin_mission_clamp_save_counts(void);
extern int MemcardSave(int, int);
extern void moby_set_flag_bit(char *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void feltzin_mission_reward_update_pal(char *, int);

/* func_PAL_L05_004262B0, the PAL copy of func_L05_00420A88: the same C, where the 25 frame timer
 * becomes 21 (25 at 50 Hz) and the timer arm also calls func_002AD7B8(6). */
void feltzin_mission_one_update_pal(char *actor)
{
    Vector pos_a;
    Vector pos_b;
    Vector pos_c;
    char *state = *(char **)(actor + 0x68);
    char **object_list;
    int count;
    int saved_count2;

    if (g_feltzin_challenge_active == 0) {
        g_feltzin_challenge_state[11] = 0;
        g_feltzin_challenge_active = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        object_list = level_get_object_list();
        count = level_get_saved_value();
        pos_a.q = 0;
        pos_a.f[0] = 487.0f;
        pos_a.f[1] = 526.0f;
        pos_a.f[2] = 531.0f;
        if (count > 0) {
            int i = count;
            do {
                switch (*(short *)(*object_list + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    entry_spawn_list_objects_with_flag_pal(*object_list, 1);
                    func_L05_0037CEE0(*object_list, &pos_a, 64.0f);
                    func_L05_0037D608(*object_list, &pos_a, 64.0f);
                    break;
                }
                object_list++;
            } while (--i != 0);
        }
    }
    if (g_feltzin_challenge_state[4] != 0 || g_feltzin_mission_index < 6)
        return;
    if (g_feltzin_challenge_state[5] <= 0) {
        if (math_fast_float_d(state + 0x58) == 0)
            return;
        *(int *)(state + 0x58) = 100;
        ship_start_transition_pal(g_str_feltzin_transition_src, g_str_feltzin_transition_dest, 200);
        pos_a.q = 0;
        pos_b.q = 0;
        pos_c.q = 0;
        actor[0x20] = 3;
        pos_a.f[0] = 593.5f;
        pos_a.f[1] = 599.0f;
        pos_a.f[2] = 566.0f;
        pos_b.f[0] = 512.5f;
        pos_b.f[1] = 530.0f;
        pos_b.f[2] = 540.0f;
        pos_c.f[0] = 438.0f;
        pos_c.f[1] = 487.0f;
        pos_c.f[2] = 535.0f;
        ship_point_camera_at_target(&pos_a, &pos_c);
        object_list = level_get_object_list();
        saved_count2 = level_get_saved_value();
        if (saved_count2 > 0) {
            int i = saved_count2;
            do {
                switch (*(short *)(*object_list + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    entry_spawn_list_objects_with_flag_pal(*object_list, 1);
                    func_L05_0037CEE0(*object_list, &pos_a, 10.0f);
                    func_L05_0037D608(*object_list, &pos_b, 20.0f);
                    break;
                }
                object_list++;
            } while (--i != 0);
        }
    } else if (g_feltzin_no_challenge_flag != 0) {
        if (math_fast_float_d(state + 0x58) != 0) {
            *(int *)(state + 0x58) = 21;
            moby_mark_flag_and_append_to_list(6);
            g_feltzin_challenge_data++;
            feltzin_mission_clamp_save_counts();
            MemcardSave(0, -1);
            g_feltzin_challenge_data--;
            moby_set_flag_bit(g_feltzin_target_mobys + (*(int *)(state + 0x2C) << 8), 1);
            g_feltzin_frame_counter = 0;
            g_feltzin_no_challenge_flag = 0;
            hero_set_state_value_c(1);
            moby_mark_flag_and_append_to_list(6);
        }
    } else if (math_fast_float_d(state + 0x58) != 0) {
        feltzin_mission_reward_update_pal(actor, 0);
    }
}
