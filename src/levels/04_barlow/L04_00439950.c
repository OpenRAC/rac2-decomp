#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } BarlowVector;
extern u8 *g_moby_l04_pool MACRO_ADDR;
extern u8 g_request_l04_queue[];
extern int g_game_l04_mode MACRO_ADDR;
extern int g_cutscene_flags[] __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
extern BarlowVector g_hero_target_point;
extern f32 g_hero_zero_vector[4];
extern u8 g_unlocked_item_flags MACRO_ADDR;
extern void moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, f32);
/* Interface assumption: retain the incoming owner/key in a0. The current
 * linked wrapper is declared void(void), but its query forwards a live a0
 * key; removing this input is not independently justified. */
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
extern u32 g_object_state_flags_b;
typedef union { u8 b[0x200]; u32 w[0x80]; } GameFlags;
extern u8 g_game_flag_table[];
extern void conversation_clear_target_on_talk(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void add_vectors(void *, void *, void *);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern char *GetLocalizedString(int);
extern void settings_store_four(int, int, int, int);
extern void menu_set_size_limits(int, int);
extern int request_begin_slot(int, int, int, int, unsigned char *);

/* Runs a talking character: waits for the hero to come close, plays the dialogue, then shows a message and sets a game flag, while the head follows the hero. */
void barlow_hint_npc_update(u8 *object) {
    BarlowVector target, origin, delta;
    u8 *data = *(u8 **)(object + 0x68);
    u8 *linked;
    int message;
    f32 rate;
    f32 blend = 0.3f;
    f32 heading, yaw, pitch;
    int look;
    conversation_clear_target_on_talk(object);
    switch (object[0x20]) {
    case 0:
        linked = g_moby_l04_pool + *(int *)(data + 0x120) * 256;
        *(int *)(linked + 0x98) = 0;
        linked[0x31] = 0;
        *(u16 *)(linked + 0x34) |= 1;
        moby_reset_vars_defaults(object);
        if (g_object_state_flags_b & 0x20000000) moby_set_state(object, 4, -1);
        else moby_set_state(object, 1, -1);
        break;
    case 1:
        if (hero_is_reachable_for_count(object, 10, 6.5f)) {
            level_apply_index_for_key((int)object);
            req_push_queue(g_request_l04_queue, 0x3D);
            req_launch_queued(g_request_l04_queue);
            moby_set_state(object, 2, -1);
        }
        break;
    case 2:
        if (g_game_l04_mode == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        g_cutscene_flags[1] = 1;
        if (!game_is_either_mode_two()) {
            g_cutscene_flags[1] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= ~1;
            vec_scale_to_length(&target, object + 0xC0, 4.0f);
            add_vectors(&origin, &target, object + 0x10);
            hero_reset_position_and_direction(&target, &((Hero *)g_hero_state)->q[0x90 / 16], 0, 1);
            moby_set_state(object, 3, -1);
        }
        break;
    case 3:
        if (!((GameFlags *)g_game_flag_table)->b[0xA4]) {
            ((GameFlags *)g_game_flag_table)->b[0xA4] = 1;
            message = GetLocalizedString(0x1137);
            settings_store_four(message, 0, GetLocalizedString(0x3296), 1);
            menu_set_size_limits(0x40, 0);
            request_begin_slot(4, 1, 10, 0, 0);
            moby_set_state(object, 4, -1);
        }
        break;
    case 4:
        break;
    }
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && math_fast_float_d((int *)(data + 0x11C))) {
            *(int *)(data + 0x11C) = FloatToInt(math_random_float_range(1200.0f, 2400.0f));
            if (object[0x43] != 1)
                anim_start_blended(object, 1, 0, 10);
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
            if (FastVecLength(&((Hero *)g_hero_state)->q[0x110 / 16]) > 0.01f)
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
        if (pitch > 0.174532949924469f)
            pitch = 0.174532949924469f;
        else if (pitch < -0.174532949924469f)
            pitch = -0.174532949924469f;
        *(f32 *)(data + 0x64) = pitch;
        *(f32 *)(data + 0x68) = yaw * 0.6f;
        *(f32 *)(data + 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags)
        *(f32 *)(data + 0x70) = 2.75f;
    moby_update_eased_node(object, data, 0, rate, blend);
    moby_update_eased_node(object, data + 0x80, 1, rate, blend);
}
