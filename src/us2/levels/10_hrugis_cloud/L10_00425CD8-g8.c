#include "names.h"
/* func_US2_L10_00425CD8 and func_US2_L10_00425F48, the v2.00 copies of func_L10_00424028 and
 * func_L10_00424290: the same C, plus destroying the two path markers func_US2_L10_00426260 may
 * have left behind (as func_US2_L10_00426130 does). func_US2_L10_00425CD8 also drops the
 * D_L10_001B1390 / func_L10_00425888 / func_0029B3E0 block and calls func_002AD7B8 first.
 * Their own unit for -G8. */
#include "common.h"

extern int g_mission_progress_flag __attribute__((section(".data")));
extern int g_mission_initialized __attribute__((sda));
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern void *level_get_object_list(void);
extern int level_get_saved_value(void);
extern void cloud_destroy_leftover_objects(void);
extern void cloud_spawn_objects(int, int);
extern void hero_set_state_value_c(int);
extern int g_hud_blink_timer_first __attribute__((sda));
extern int g_hud_blink_timer_second __attribute__((sda));
extern int g_no_first_completion_flag __attribute__((sda));
extern int g_state_frame_count __attribute__((sda));
extern char *g_moby_base_table;
extern void *CreateEnergyStrip(void *, void *, int, int, int, int, int, int, float, float, float, float);
extern int math_fast_float_d(void *);
extern void moby_set_flag_bit(void *, int);
extern void moby_mark_flag_and_append_to_list(int);

typedef struct { int idx; u8 pad[0x28]; int f2C; } G221CD0;
extern G221CD0 g_mission_state;
extern u8 *g_spot_record_table;
extern void entry_spawn_list_objects_with_flag(void *, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern void hrugis_set_group_states(void *);
extern void *level_find_object_by_class_id(int);
extern int group_count_alive(void *);
extern void hrugis_finish_mission_reward_us2(void *, int);
extern int list_count_ready_objects(void *);
extern void FadeToBlack(int);
extern void hrugis_reset_mission_state(void *);
extern void *g_gate_first __attribute__((sda)), *g_gate_second __attribute__((sda));
extern void moby_mark_spawned(void *);

void mission_first_update_us2(char *object)
{
    char **objects;
    int count;
    char *vars = *(char **)(object + 0x68);
    char *group;
    int i;
    if (!g_mission_initialized) {
        typedef int Quad __attribute__((mode(TI)));
        union { Quad q; float f[4]; } start_point, end_point;
        g_mission_progress_flag = 0;
        g_mission_initialized = 1;
        g_hud_blink_timer_first = 0;
        g_hud_blink_timer_second = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            if (*(short *)(objects[i] + 0xAA) == 0xF85) entry_spawn_list_objects_with_flag(objects[i], 1);
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(75,16);
        start_point.q = 0; end_point.q = 0;
        start_point.f[0] = 469.63f; start_point.f[1] = 407.93f; start_point.f[2] = 502.79f;
        end_point.f[0] = 476.13f; end_point.f[1] = 415.41f; end_point.f[2] = 502.79f;
        CreateEnergyStrip(&start_point,&end_point,1,2000000,0x7F7F7F,0xFF1010,70,70,0.5f,0.2f,0.402f,1.12225f);
        if (g_gate_first) {
            moby_mark_spawned(g_gate_first);
            g_gate_first = 0;
        }
        if (g_gate_second) {
            moby_mark_spawned(g_gate_second);
            g_gate_second = 0;
        }
    }
    group = level_find_object_by_class_id(0xF85);
    count = group ? group_count_alive(group) : 0;
    if (!count) {
        entry_init_all_registered();
        if (g_no_first_completion_flag) {
            if (math_fast_float_d(vars + 0x58)) {
                *(int *)(vars + 0x58) = 10;
                moby_mark_flag_and_append_to_list(12);
                moby_set_flag_bit(g_moby_base_table + *(int *)(vars + 0x2C) * 256,1);
                g_state_frame_count = 0;
                g_no_first_completion_flag = 0;
                hero_set_state_value_c(1);
            }
        } else if (math_fast_float_d(vars + 0x58)) {
            hrugis_finish_mission_reward_us2(object,0);
            g_hud_blink_timer_first = 0;
            g_hud_blink_timer_second = 0;
        }
    }
}

void mission_second_update_us2(u8 *moby) {
    u8 **objects;
    int count;
    int i;
    u8 *object;
    void *group;
    int alive;

    if (g_mission_initialized == 0) {
        g_mission_initialized = 1;
        g_mission_state.f2C = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        count = level_get_saved_value();
        for (i = 0; i < count; i++) {
            object = objects[i];
            switch (*(short *)(object + 0xAA)) {
            case 0xCBE:
                entry_spawn_list_objects_with_flag(object, 1);
                break;
            case 0xF93:
                entry_spawn_list_objects_with_flag(object, 1);
                func_L05_0037CEE0(objects[i], g_spot_record_table + g_mission_state.idx * 128 + 0x30, 64.0f);
                func_L05_0037D608(objects[i], g_spot_record_table + g_mission_state.idx * 128 + 0x30, 64.0f);
                hrugis_set_group_states(objects[i]);
                break;
            }
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(0x2D, 12);
        if (g_gate_first) {
            moby_mark_spawned(g_gate_first);
            g_gate_first = 0;
        }
        if (g_gate_second) {
            moby_mark_spawned(g_gate_second);
            g_gate_second = 0;
        }
    }
    group = level_find_object_by_class_id(0xF93);
    alive = group ? group_count_alive(group) : 0;
    if (alive == 0) {
        hrugis_finish_mission_reward_us2(moby, 1);
    }
    if (list_count_ready_objects(level_find_object_by_class_id(0xCBE)) == 0) {
        FadeToBlack(0x1E);
        hero_set_state_value_c(0);
        hrugis_reset_mission_state(moby);
    }
}
