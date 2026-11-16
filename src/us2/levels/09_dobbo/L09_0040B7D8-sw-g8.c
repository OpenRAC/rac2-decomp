#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x60];
    int flags;
    u8 status;
} DobboInput;
typedef struct {
    char pad[0x1D];
    u8 unlocked;
    char pad1[0xF];
    u8 started;
    u8 completed;
} DobboProgress;
extern u8 g_npc_talk_flag MACRO_ADDR, g_unlocked_item_flags MACRO_ADDR;
extern DobboInput g_request_flag_table NOT_SDA;
extern DobboProgress g_game_flag_table NOT_SDA;
extern char g_moby_group_flags[] NOT_SDA;
extern char g_hero_state[] NOT_SDA;
extern char g_request_l09_queue[] NOT_SDA;
extern int g_game_l09_mode MACRO_ADDR, g_frame_l09_counter MACRO_ADDR;
extern int g_dobbo_setting_flags[] MACRO_ADDR;
extern int g_talking_npc_greeted __attribute__((sda)), g_current_map_index __attribute__((sda));
extern void moby_reset_matching_effects(char *);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_reset_vars_defaults(char *);
extern int req_push_queue(void *, int);
extern void level_apply_index_for_key(char *);
extern s32 req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void data_set_small_value_and_refresh(int, int), game_set_slowdown_factor(void), level_capture_checkpoint_state(void *, void *);
extern void moby_mark_flag_and_append_to_list(int), snd_play_indexed_us2(int), moby_mark_table_entry_flagged(int);
extern int MemcardSave(int, int);
extern void moby_mark_spawned(char *);
extern int FastDecTimer(void *), FloatToInt(float);
extern float math_random_float_range(float, float), vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float), FastVecLength(void *), FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void anim_start_blended(char *, int, int, int), vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void moby_update_eased_node(char *, void *, int, float, float);
#define HERO_POS (D_00189E20 + 0x80)
#define HERO_ROT (D_00189E20 + 0x90)
#define HERO_AIM (D_00189E20 + 0xE0)
#define U8(p, o) (*(u8 *)((p) + (o)))
#define U16(p, o) (*(u16 *)((p) + (o)))
#define S16(p, o) (*(s16 *)((p) + (o)))
#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))
static inline float yaw_to_hero(char *obj) {
    char *hero = g_hero_state;
    return mat_fast_helper_a(F32(hero, 0xE0) - F32(obj, 0x10), F32(hero, 0xE4) - F32(obj, 0x14));
}
static inline void update_joint(char *obj, char *joint, int index, float speed, float rate) {
    moby_update_eased_node(obj, joint, index, speed, rate);
}

/* Per-frame update of the talking character (moby class 3678): it offers dialogue and rewards, then watches the hero with its head and eyes. (USA v2.00) */
void talking_npc_update_us2(char *obj) {
    float target[4], pos[4], delta[4];
    char *data = *(char **)(obj + 0x68);
    char *player;
    float speed, yaw, pitch, random_yaw;
    int active;
    u64 status;

    moby_reset_matching_effects(obj);
    switch (U8(obj, 0x20)) {
    case 0:
        if (g_npc_talk_flag) {
            U16(obj, 0x34) = (U16(obj, 0x34) | 0x41) & 0xEFFF;
            I32(obj, 0x98) = 0;
        }
        status = g_request_flag_table.status;
        if (status >> 7) {
            moby_set_state(obj, 6, -1);
        } else if (g_game_flag_table.unlocked || (g_request_flag_table.flags & 8)) {
            moby_set_state(obj, 3, -1);
        } else {
            moby_set_state(obj, 1, -1);
        }
        if (U8(obj, 0x20) == 3) {
            if (!IsPointInCuboid(HERO_POS, I32(data, 0x118)) || !g_game_flag_table.unlocked) {
                g_talking_npc_greeted = 1;
            }
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (req_push_queue(g_request_l09_queue, 99)) {
                level_apply_index_for_key(obj);
                req_launch_queued(g_request_l09_queue);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_dobbo_setting_flags[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            moby_set_state(obj, 3, -1);
            g_game_flag_table.unlocked = 1;
            g_game_flag_table.started = 1;
            data_set_small_value_and_refresh(22, 1);
        }
        break;
    case 3:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (g_game_flag_table.completed) {
                if (req_push_queue(g_request_l09_queue, 103)) {
                    req_push_queue(g_request_l09_queue, 11);
                    level_apply_index_for_key(obj);
                    req_launch_queued(g_request_l09_queue);
                    game_set_slowdown_factor();
                    g_talking_npc_greeted = 1;
                    moby_set_state(obj, 5, -1);
                }
            } else if (g_frame_l09_counter < 10 && g_game_flag_table.unlocked && !g_talking_npc_greeted) {
                if (req_push_queue(g_request_l09_queue, 102)) {
                    req_launch_queued(g_request_l09_queue);
                    game_set_slowdown_factor();
                    g_talking_npc_greeted = 1;
                    moby_set_state(obj, 4, -1);
                }
            }
        }
        break;
    case 4:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            level_capture_checkpoint_state(HERO_POS, HERO_ROT);
            g_dobbo_setting_flags[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            MemcardSave(0, -1);
            moby_set_state(obj, 3, -1);
        }
        break;
    case 5:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            g_dobbo_setting_flags[2] = 0;
            moby_mark_flag_and_append_to_list(11);
            snd_play_indexed_us2(11);
            if (U8(obj, 0xB0) != 255 && !(U8(g_moby_group_flags, U8(obj, 0xB0) + (g_current_map_index << 4)) & 0x80)) {
                moby_mark_table_entry_flagged(U8(obj, 0xB0));
            }
            level_capture_checkpoint_state(HERO_POS, HERO_ROT);
            MemcardSave(0, -1);
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            moby_mark_spawned(obj);
            return;
        }
        break;
    case 6:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118)) && g_frame_l09_counter < 10 && g_game_flag_table.unlocked
            && !g_talking_npc_greeted) {
            if (req_push_queue(g_request_l09_queue, 102)) {
                req_launch_queued(g_request_l09_queue);
                game_set_slowdown_factor();
                g_talking_npc_greeted = 1;
                moby_set_state(obj, 7, -1);
            }
        }
        break;
    case 7:
        g_dobbo_setting_flags[2] = 1;
        if (g_game_l09_mode == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            g_dobbo_setting_flags[2] = 0;
            moby_set_state(obj, 8, -1);
            level_capture_checkpoint_state(HERO_POS, HERO_ROT);
            MemcardSave(0, -1);
            moby_mark_spawned(obj);
            return;
        }
        break;
    }

    if (U8(obj, 0x20)) {
        if (U8(obj, 0x43) == 1 && FastDecTimer(data + 0x114)) {
            S16(data, 0x114) = FloatToInt(math_random_float_range(1200.0f, 2400.0f));
            if (U8(obj, 0x43) != 2) {
                anim_start_blended(obj, 2, 0, 10);
            }
        } else if ((U8(obj, 0x60) & 2) && U8(obj, 0x43) != 1) {
            anim_start_blended(obj, 1, 0, 10);
        }
    }

    speed = 0.02f;
    active = 0;
    if (U8(obj, 0x43) == 1) {
        player = HERO_POS;
        active = 1;
        if (vec_distance_xy(obj + 0x10, player) < 8.0f
            && FastDiffRots(F32(obj, 0xF8), yaw_to_hero(obj)) < 1.57079649f) {
            if (FastVecLength(player + 0x90) > 0.01f) {
                S16(data, 0x110) = 120;
            } else {
                FastDecTimer(data + 0x110);
            }
        } else if (S16(data, 0x110)) {
            S16(data, 0x110) = 0;
            qcopy(data + 0x100, HERO_AIM);
        }
        if (FastDecTimer(data + 0x112)) {
            S16(data, 0x112) = FloatToInt(math_random_float_range(180.0f, 300.0f));
            random_yaw = FastAddRotations(F32(obj, 0xF8), math_random_float_range(-90.0f, 90.0f) * 0.017453294f);
            pitch = math_random_float_range(0.0f, 30.0f) * 0.017453294f;
            vec_build_spherical_offset(data + 0x100, 6.0f, random_yaw, pitch);
            FastVecAdd(data + 0x100, data + 0x100, obj + 0x10);
        }
        if (S16(data, 0x110)) {
            qcopy(target, HERO_AIM);
            speed = 0.04f;
        } else {
            qcopy(target, data + 0x100);
        }
    }
    if (active) {
        qcopy(pos, obj + 0x10);
        pos[2] += 2.0f;
        FastVecSub(delta, target, pos);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta[0], delta[1]), F32(obj, 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        if (yaw > 1.57079649f) {
            yaw = 1.57079649f;
        } else if (yaw < -1.57079649f) {
            yaw = -1.57079649f;
        }
        if (pitch > 0.52359885f) {
            pitch = 0.52359885f;
        } else if (pitch < -0.52359885f) {
            pitch = -0.52359885f;
        }
        F32(data, 0x64) = pitch;
        F32(data, 0x68) = yaw * 0.6f;
        F32(data, 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags) {
        F32(data, 0x70) = 2.75f;
    }
    update_joint(obj, data, 0, speed, 0.3f);
    update_joint(obj, data + 0x80, 1, speed, 0.3f);
}
