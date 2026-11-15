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
extern u8 D_001A7BD3 MACRO_ADDR, D_001A7A40 MACRO_ADDR;
extern DobboInput D_00139768 NOT_SDA;
extern DobboProgress D_001395B8 NOT_SDA;
extern char D_0019B2E8[] NOT_SDA;
extern char g_hero_state[] NOT_SDA;
extern char D_L09_001BFC00[] NOT_SDA;
extern int D_L09_001A8F00 MACRO_ADDR, D_L09_001B2388 MACRO_ADDR;
extern int D_L09_001B25A0[] MACRO_ADDR;
extern int D_L09_001B15A0 __attribute__((sda)), g_current_map_index __attribute__((sda));
extern void moby_reset_matching_effects(char *);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_reset_vars_defaults(char *);
extern int req_push_queue(void *, int);
extern void level_apply_index_for_key(char *);
extern s32 req_launch_queued(void *);
extern int game_is_either_mode_two(void);
extern void data_set_small_value_and_refresh(int, int), game_set_slowdown_factor(void), level_capture_checkpoint_state(void *, void *);
extern void moby_mark_flag_and_append_to_list(int), func_US2_002AFF10(int), moby_mark_table_entry_flagged(int);
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
static inline float yawToHero(char *obj) {
    char *hero = g_hero_state;
    return mat_fast_helper_a(F32(hero, 0xE0) - F32(obj, 0x10), F32(hero, 0xE4) - F32(obj, 0x14));
}
static inline void updateJoint(char *obj, char *joint, int index, float speed, float rate) {
    moby_update_eased_node(obj, joint, index, speed, rate);
}

void func_US2_L09_0040B7D8(char *obj) {
    float target[4], pos[4], delta[4];
    char *data = *(char **)(obj + 0x68);
    char *player;
    float speed, yaw, pitch, randomYaw;
    int active;
    u64 status;

    moby_reset_matching_effects(obj);
    switch (U8(obj, 0x20)) {
    case 0:
        if (D_001A7BD3) {
            U16(obj, 0x34) = (U16(obj, 0x34) | 0x41) & 0xEFFF;
            I32(obj, 0x98) = 0;
        }
        status = D_00139768.status;
        if (status >> 7) {
            moby_set_state(obj, 6, -1);
        } else if (D_001395B8.unlocked || (D_00139768.flags & 8)) {
            moby_set_state(obj, 3, -1);
        } else {
            moby_set_state(obj, 1, -1);
        }
        if (U8(obj, 0x20) == 3) {
            if (!IsPointInCuboid(HERO_POS, I32(data, 0x118)) || !D_001395B8.unlocked) {
                D_L09_001B15A0 = 1;
            }
        }
        moby_reset_vars_defaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (req_push_queue(D_L09_001BFC00, 99)) {
                level_apply_index_for_key(obj);
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            D_L09_001B25A0[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            moby_set_state(obj, 3, -1);
            D_001395B8.unlocked = 1;
            D_001395B8.started = 1;
            data_set_small_value_and_refresh(22, 1);
        }
        break;
    case 3:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (D_001395B8.completed) {
                if (req_push_queue(D_L09_001BFC00, 103)) {
                    req_push_queue(D_L09_001BFC00, 11);
                    level_apply_index_for_key(obj);
                    req_launch_queued(D_L09_001BFC00);
                    game_set_slowdown_factor();
                    D_L09_001B15A0 = 1;
                    moby_set_state(obj, 5, -1);
                }
            } else if (D_L09_001B2388 < 10 && D_001395B8.unlocked && !D_L09_001B15A0) {
                if (req_push_queue(D_L09_001BFC00, 102)) {
                    req_launch_queued(D_L09_001BFC00);
                    game_set_slowdown_factor();
                    D_L09_001B15A0 = 1;
                    moby_set_state(obj, 4, -1);
                }
            }
        }
        break;
    case 4:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            level_capture_checkpoint_state(HERO_POS, HERO_ROT);
            D_L09_001B25A0[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            MemcardSave(0, -1);
            moby_set_state(obj, 3, -1);
        }
        break;
    case 5:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            D_L09_001B25A0[2] = 0;
            moby_mark_flag_and_append_to_list(11);
            func_US2_002AFF10(11);
            if (U8(obj, 0xB0) != 255 && !(U8(D_0019B2E8, U8(obj, 0xB0) + (g_current_map_index << 4)) & 0x80)) {
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
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118)) && D_L09_001B2388 < 10 && D_001395B8.unlocked
            && !D_L09_001B15A0) {
            if (req_push_queue(D_L09_001BFC00, 102)) {
                req_launch_queued(D_L09_001BFC00);
                game_set_slowdown_factor();
                D_L09_001B15A0 = 1;
                moby_set_state(obj, 7, -1);
            }
        }
        break;
    case 7:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!game_is_either_mode_two()) {
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            D_L09_001B25A0[2] = 0;
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
            && FastDiffRots(F32(obj, 0xF8), yawToHero(obj)) < 1.57079649f) {
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
            randomYaw = FastAddRotations(F32(obj, 0xF8), math_random_float_range(-90.0f, 90.0f) * 0.017453294f);
            pitch = math_random_float_range(0.0f, 30.0f) * 0.017453294f;
            vec_build_spherical_offset(data + 0x100, 6.0f, randomYaw, pitch);
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
    if (D_001A7A40) {
        F32(data, 0x70) = 2.75f;
    }
    updateJoint(obj, data, 0, speed, 0.3f);
    updateJoint(obj, data + 0x80, 1, speed, 0.3f);
}
