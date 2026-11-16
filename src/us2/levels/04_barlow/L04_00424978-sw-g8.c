#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } BarlowVector;
extern u8 g_request_l04_queue[];
extern int g_game_l04_mode;
extern int g_cutscene_flags[] __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
extern u8 g_unlocked_item_flags;
extern void moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, f32);
extern void level_apply_index_for_key(int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(int *);
extern f32 math_random_float_range(f32, f32);
extern int FloatToInt(f32);
extern void anim_start_blended(void *, int, int, int);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern f32 FastVecLength(void *);
extern f32 FastAddRotations(f32, f32);
extern void vec_build_spherical_offset(void *, f32, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 vec_length_xy(void *);
extern void moby_update_eased_node(void *, void *, int, f32, f32);
extern u32 g_object_state_flags_a __attribute__((nosda));
extern u8 g_level_event_flag_3;
extern u8 g_bike_variant_flag __attribute__((nosda));
extern int g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern void moby_reset_matching_effects(void *);
extern void level_set_flag(void);
extern void game_set_slowdown_factor(void);
extern void moby_mark_flag_and_append_to_list(int);
extern void help_unlock_entry(int);
extern void snd_play_indexed_us2(int);
extern void moby_mark_table_entry_flagged(int);
extern void level_capture_checkpoint_state(void *, void *);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(void *);

/* Advances the conversation states and turns the two manipulators toward the
 * hero or a periodically chosen idle target. */
void UpdateBarlowConversationNpc_us2(u8 *object) {
    BarlowVector target, origin, delta;
    u8 *data = *(u8 **)(object + 0x68);
    unsigned int state;
    f32 rate, heading, yaw, pitch;
    f32 blend = 0.3f;
    int look;
    moby_reset_matching_effects(object);
    state = object[0x20];
    switch (state) {
    case 0:
    if (g_level_event_flag_3) {
        moby_mark_spawned(object);
        return;
    }
    moby_reset_vars_defaults(object);
    if (g_object_state_flags_a & 0x800000) moby_set_state(object, 3, -1);
    else moby_set_state(object, 1, -1);
    goto stateDone;
    case 1:
    if (hero_is_reachable_for_count(object, 10, 4.0f)) {
        level_apply_index_for_key((int)object);
        if (req_push_queue(g_request_l04_queue, 0x37)) {
            req_launch_queued(g_request_l04_queue);
            moby_set_state(object, 2, -1);
        }
    }
    goto stateDone;
    case 2:
    g_cutscene_flags[1] = 1;
    if (g_game_l04_mode == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!game_is_either_mode_two()) {
        g_cutscene_flags[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        level_set_flag();
        moby_set_state(object, 3, -1);
    }
    goto stateDone;
    case 3:
    if (g_bike_variant_flag && hero_is_reachable_for_count(object, 10, 2.5f)) {
        level_apply_index_for_key((int)object);
        if (req_push_queue(g_request_l04_queue, 0x39)) {
            req_push_queue(g_request_l04_queue, 5);
            req_push_queue(g_request_l04_queue, 0x3A);
            req_launch_queued(g_request_l04_queue);
            game_set_slowdown_factor();
            moby_set_state(object, 4, -1);
        }
    }
    goto stateDone;
    case 4:
    g_cutscene_flags[1] = 1;
    if (g_game_l04_mode == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!game_is_either_mode_two()) {
        g_cutscene_flags[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        moby_mark_flag_and_append_to_list(5);
        help_unlock_entry(0x30);
        snd_play_indexed_us2(5);
        if (object[0xB0] != 0xFF) {
            int channel = object[0xB0];
            if (!(g_moby_group_flags[channel + g_current_map_index * 16] & 0x80))
                moby_mark_table_entry_flagged(channel);
            level_capture_checkpoint_state(&((Hero *)g_hero_state)->q[0x80 / 16], &((Hero *)g_hero_state)->q[0x90 / 16]);
        } else {
            MemcardSave(0, -1);
        }
        moby_mark_spawned(object);
        return;
    }
    }
stateDone:
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && math_fast_float_d((int *)(data + 0x11C))) {
            *(int *)(data + 0x11C) = FloatToInt(math_random_float_range(1200.0f, 2400.0f));
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            anim_start_blended(object, 0, 0, 10);
        }
    }
    rate = 0.02f;
    look = 0;
    if (object[0x43] == 0) {
        look = 1;
        if (vec_distance_xy(object + 0x10, &((Hero *)g_hero_state)->q[0x80 / 16]) < 8.0f &&
            FastDiffRots(*(f32 *)(object + 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0xE0 / 4] - *(f32 *)(object + 0x10), ((Hero *)g_hero_state)->f[0xE4 / 4] - *(f32 *)(object + 0x14))) < 1.5707964897155762f) {
            if (FastVecLength(&((Hero *)g_hero_state)->f[0x110 / 4]) > 0.01f)
                *(int *)(data + 0x114) = 120;
            else
                math_fast_float_d((int *)(data + 0x114));
        } else if (*(int *)(data + 0x114)) {
            *(int *)(data + 0x114) = 0;
            qcopy((data + 0x100), &((Hero *)g_hero_state)->q[0xE0 / 16]);
        }
        if (math_fast_float_d((int *)(data + 0x118))) {
            *(int *)(data + 0x118) = FloatToInt(math_random_float_range(180.0f, 300.0f));
            heading = FastAddRotations(*(f32 *)(object + 0xF8), math_random_float_range(-90.0f, 90.0f) * 0.01745329424738884f);
            pitch = math_random_float_range(0.0f, 30.0f) * 0.01745329424738884f;
            vec_build_spherical_offset(data + 0x100, 6.0f, heading, pitch);
            FastVecAdd(data + 0x100, data + 0x100, object + 0x10);
        }
        if (*(int *)(data + 0x114)) {
            qcopy(&target, &((Hero *)g_hero_state)->q[0xE0 / 16]);
            rate = 0.04f;
        } else {
            qcopy(&target, (data + 0x100));
        }
    }
    if (look) {
        qcopy(&origin, (object + 0x10));
        origin.f[2] += 2.0f;
        FastVecSub(&delta, &target, &origin);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta.f[0], delta.f[1]), *(f32 *)(object + 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(&delta), delta.f[2]);
        if (yaw > 1.5707964897155762f)
            yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f)
            yaw = -1.5707964897155762f;
        /* This object's update computes pitch but only applies yaw. */
        if (pitch > 0.523598849773407f)
            pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f)
            pitch = -0.523598849773407f;
        *(f32 *)(data + 0x68) = yaw * 0.6f;
        *(f32 *)(data + 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags)
        *(f32 *)(data + 0x70) = 2.75f;
    moby_update_eased_node(object, data, 0, rate, blend);
    moby_update_eased_node(object, data + 0x80, 1, rate, blend);
}
