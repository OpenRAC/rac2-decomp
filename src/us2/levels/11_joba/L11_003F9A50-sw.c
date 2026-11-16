#include "include_asm.h"

#include "common.h"
extern void moby_reset_matching_effects(void *);
extern void moby_reset_vars_defaults(void *);
extern int IsPointInCuboid(void *, int);
extern void level_apply_index_for_key(int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void game_set_slowdown_factor(void);
extern void moby_set_state(void *, int, int);
extern void help_unlock_entry(int);
extern int moby_handle_request_slot_state(int);
extern void value_set_entry_by_index_us2(int, int);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(void *);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void anim_start_blended(void *, int, int, int);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastVecLength(void *);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float fast_subtract_rotations(float, float);
extern float vec_length_xy(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern unsigned char g_action_flag, g_unlocked_item_flags;
extern int g_object_state_flags_e NOT_SDA;
extern unsigned char g_level_event_flag_c NOT_SDA;
extern int g_arena_state;
extern volatile int g_arena_script_flags[] MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_moby_group_flags[][16];
extern unsigned char g_request_l11_queue[];
typedef struct {
    unsigned char pad[0x80];
    float position[4];
    float rotation[4];
    unsigned char padA0[0x40];
    float aim[4];
    unsigned char padF0[0x20];
    float velocity[4];
} JobaPlayerView;
extern JobaPlayerView g_hero_state;
extern char g_hero_target_point[];

void UpdateJobaDialogueActor_us2(unsigned char *moby) {
    float target[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    unsigned char *data = *(unsigned char **)(moby + 0x68);
    int track, i;
    float speed, angle, pitch, heading;

    moby_reset_matching_effects(moby);
    switch (moby[0x20]) {
    case 0:
        if (g_action_flag) {
            moby_mark_spawned(moby);
            return;
        }
        {
            moby_reset_vars_defaults(moby);
            if (g_object_state_flags_e & 0x10000)
                moby_set_state(moby, 3, -1);
            else
                moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_state.position, *(int *)(data + 0x120))) {
            level_apply_index_for_key((int)moby);
            if (req_push_queue(g_request_l11_queue, 0x70)) {
                req_launch_queued(g_request_l11_queue);
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 2:
        g_arena_script_flags[0] = 1;
        if (g_arena_state == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_arena_script_flags[0] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            moby_set_state(moby, 3, -1);
        }
        break;
    case 3:
        if (g_level_event_flag_c &&
            IsPointInCuboid(g_hero_state.position, *(int *)(data + 0x120))) {
            level_apply_index_for_key((int)moby);
            if (req_push_queue(g_request_l11_queue, 0x71)) {
                req_launch_queued(g_request_l11_queue);
                game_set_slowdown_factor();
                moby_set_state(moby, 4, -1);
            }
        }
        break;
    case 4:
        g_arena_script_flags[0] = 1;
        if (g_arena_state == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_arena_script_flags[0] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            if (!g_action_flag) {
                help_unlock_entry(0x36);
                moby_handle_request_slot_state(0x36);
                value_set_entry_by_index_us2(0x1232, -1);
                if (moby[0xB0] != 255) {
                    if (!(g_moby_group_flags[g_current_map_index][moby[0xB0]] & 0x80))
                        moby_mark_table_entry_flagged(moby[0xB0]);
                    level_capture_checkpoint_state(g_hero_state.position, g_hero_state.rotation);
                } else {
                    MemcardSave(0, -1);
                }
            }
            moby_mark_spawned(moby);
            return;
        }
        break;
    }

    if (moby[0x20] != 0) {
        if (moby[0x43] == 1 && FastDecTimer(data + 0x11E)) {
            *(u16 *)(data + 0x11E) = FloatToInt(math_random_float_range(1200.0f, 2400.0f));
        } else if ((moby[0x60] & 2) && moby[0x43] != 1) {
            anim_start_blended(moby, 1, 0, 10);
        }
    }

    speed = 0.02f;
    track = 0;
    if (moby[0x43] == 1) {
        track = 1;
        if (vec_distance_xy(moby + 0x10, g_hero_state.position) < 8.0f &&
            FastDiffRots(*(float *)(moby + 0xF8),
                mat_fast_helper_a(g_hero_state.aim[0] - *(float *)(moby + 0x10),
                              g_hero_state.aim[1] - *(float *)(moby + 0x14))) < 1.5707964897155762f) {
            if (FastVecLength(g_hero_state.velocity) > 0.01f)
                *(int *)(data + 0x114) = 120;
            else
                math_fast_float_d(data + 0x114);
        } else if (*(int *)(data + 0x114)) {
            *(int *)(data + 0x114) = 0;
            qcopy(data + 0x100, g_hero_target_point);
        }
        if (math_fast_float_d(data + 0x118)) {
            *(int *)(data + 0x118) = FloatToInt(math_random_float_range(180.0f, 300.0f));
            heading = FastAddRotations(*(float *)(moby + 0xF8),
                math_random_float_range(-90.0f, 90.0f) * 0.01745329424738884f);
            angle = math_random_float_range(0.0f, 30.0f);
            vec_build_spherical_offset(data + 0x100, 6.0f, heading, angle * 0.01745329424738884f);
            FastVecAdd(data + 0x100, data + 0x100, moby + 0x10);
        }
        if (*(int *)(data + 0x114)) {
            qcopy(target, g_hero_target_point);
            speed = 0.04f;
        } else {
            qcopy(target, data + 0x100);
        }
    }

    if (track) {
        qcopy(origin, moby + 0x10);
        origin[2] += 2.0f;
        FastVecSub(delta, target, origin);
        angle = fast_subtract_rotations(mat_fast_helper_a(delta[0], delta[1]), *(float *)(moby + 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        if (angle > 1.5707964897155762f)
            angle = 1.5707964897155762f;
        else if (angle < -1.5707964897155762f)
            angle = -1.5707964897155762f;
        if (pitch > 0.523598849773407f)
            pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f)
            pitch = -0.523598849773407f;
        *(float *)(data + 0x64) = pitch;
        *(float *)(data + 0x68) = angle * 0.6f;
        *(float *)(data + 0xE8) = angle * 0.4f;
    }
    if (g_unlocked_item_flags)
        *(float *)(data + 0x70) = 2.75f;
    for (i = 0; i < 2; i++)
        moby_update_eased_node(moby, data + i * 0x80, i, speed, 0.3f);
}
