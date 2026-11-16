#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, s32, s32);
extern void moby_mark_spawned(char *);
extern s32 PlayMobySound(s32, s32, char *);
extern void FastVecSub(char *, char *, char *);
extern f32 FastVecLength(char *);
extern void math_approach_target_with_braking(f32 *, f32, f32, f32, f32);
extern void moby_transform_joint_to_world(char *, s32, void *);
extern void FastVecAdd(char *, char *, char *);
extern s32 path_push_point_away(s32, char *, char *, f32);
extern void vec_clear_128(char *);
extern s32 FastDecTimer(void *);
extern s32 coll_test_point(char *, s32, char *, f32);
extern f32 g_spring_holder_params[];
extern f32 g_collision_hit_height[];
extern s32 g_pad_held_flags[];
extern f32 g_spring_holder_offset __attribute__((sda));
extern f32 g_spring_holder_decay_rate __attribute__((sda));
extern f32 g_spring_holder_length_limits[3] __attribute__((sda));
extern f32 g_spring_holder_min_height;
extern char *g_collision_hit_result[];
extern s32 CollLine(char *, char *, s32, char *, s32);
extern void AttachManipulator(char *, s32, char *);
extern void moby_start_fall_state(char *, char *);
extern void laser_bot_set_state_copy_vector(char *, char *);
extern float math_step_value_toward_target(f32 *, f32 *, f32, f32, f32, f32);
extern void held_platform_move_by_input_pal(char *);
extern void moby_set_flag_bit(char *, s32);
extern f32 vec_distance_xy(char *, char *);
extern void vec_clamp_length(char *, f32);
extern f32 fast_vec_dist(char *, char *);
extern void object_store_mode_release(char *, s32);
extern void robot_set_speed_state(char *, char *);
extern void func_002A0F48(char *);

/* Updates the held object, vertical spring motion and three track scales. */
void spring_holder_update_pal(char *moby)
{
    char buf[0x30] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);

    s32 i, landed;
    f32 height, distance, length;

    if (*(char **)(vars + 0xF0)) {
        *(s32 *)(*(char **)(vars + 0xF0) + 0x98) = 0;
    }
    FastDecTimer(vars + 0x104);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        g_spring_holder_params[0] = -1.0f;
        *(s32 *)(moby + 0x9C) = 1;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 4) & ~0x400;
        *(s32 *)(vars + 0x10C) = 0;
        *(s32 *)(vars + 0x108) = -1;
        vec_clear_128(vars + 0xE0);
        *(f32 *)(vars + 0xF8) = *(f32 *)(moby + 0x18);
        qcopy(buf, moby + 0x10);
        *(f32 *)(buf + 8) += 20.0f;
        qcopy(buf + 0x10, moby + 0x10);
        *(f32 *)(buf + 0x18) += 1.0f;
        if (!CollLine(buf + 0x10, buf, 0, moby, 0)) {
            moby_mark_spawned(moby);
            return;
        }
        *(f32 *)(vars + 0xF4) = g_collision_hit_height[0];
        for (i = 0; i < 3; i++) {
            AttachManipulator(moby, i, vars + 0x20 + i * 0x40);
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
    case 2: {
        if (*(u8 *)(moby + 0x20) == 2) {
            if (g_pad_held_flags[0] & 0xE0) {
                if (*(char **)(vars + 0xF0)) {
                    switch (*(s16 *)((*(char **)(vars + 0xF0)) + 0xAA)) {
                    case 0xB85:
                    case 0xCFC:
                        moby_start_fall_state(*(char **)(vars + 0xF0), vars + 0xE0);
                        break;
                    case 0xFFD:
                        laser_bot_set_state_copy_vector(*(char **)(vars + 0xF0), vars + 0xE0);
                        break;
                    }
                    *(s32 *)(*(char **)(vars + 0xF0) + 0x98) =
                        *(s32 *)(*(char **)(*(char **)(vars + 0xF0) + 0x24) + 0x10);
                    *(s16 *)(vars + 0x104) = 25;
                    *(s32 *)(vars + 0xF0) = 0;
                    *(s32 *)(vars + 0xE8) = 0;
                } else if (!*(s16 *)(vars + 0x104) && *(f32 *)(vars + 0xFC) >= -1.5f) {
                    moby_set_state(moby, 3, -1);
                    break;
                }
            } else if (*(s16 *)(vars + 0x106)) {
                *(s16 *)(vars + 0x106) = 0;
                *(u16 *)(moby + 0x34) &= ~0x400;
                moby_set_state(moby, 1, -1);
            }
        }
        math_approach_target_with_braking((f32 *)(vars + 0xE8),
            *(f32 *)(vars + 0xF4) + g_spring_holder_offset - *(f32 *)(moby + 0x18),
            0.004f, 0.004f, 0.20000002f);
        math_step_value_toward_target((f32 *)(vars + 0xFC), (f32 *)(vars + 0x100),
            0.0f, 0.004f, 0.004f, 0.40000004f);
        held_platform_move_by_input_pal(moby);
        break;
    }
    case 3: {
        char *contact;

        *(f32 *)(vars + 0x100) -= g_spring_holder_decay_rate * 0.00040000002f;
        *(f32 *)(vars + 0xFC) += *(f32 *)(vars + 0x100);
        if (!*(s32 *)(vars + 0x10C)) {
            PlayMobySound(1, 0, moby);
            *(s32 *)(vars + 0x10C) = 1;
        }
        held_platform_move_by_input_pal(moby);
        moby_transform_joint_to_world(moby, 2, buf);
        if (coll_test_point(buf, 0, moby, 1.0f) || *(f32 *)(vars + 0xFC) < g_spring_holder_min_height) {
            contact = g_collision_hit_result[0];
            landed = 1;
            if (contact) {
                switch (*(s16 *)(contact + 0xAA)) {
                case 0xB85:
                    height = *(f32 *)(contact + 0x18) + 2.7f;
                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        *(char **)(vars + 0xF0) = contact;
                    }
                    break;
                case 0xCFC: {
                    f32 height = *(f32 *)(contact + 0x18) + 2.7f;

                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        if (*(u8 *)(contact + 0x20) < 2) {
                            *(char **)(vars + 0xF0) = contact;
                        }
                    }
                    break;
                }
                case 0xFFD:
                    height = *(f32 *)(contact + 0x18) + 2.0f;
                    if (height < *(f32 *)(buf + 8)) {
                        landed = 0;
                    } else {
                        *(f32 *)(vars + 0xFC) += height - *(f32 *)(buf + 8);
                        moby_set_flag_bit(contact, 1);
                        *(char **)(vars + 0xF0) = contact;
                    }
                    break;
                }
            }
            if (landed) {
                if (*(char **)(vars + 0xF0)) {
                    moby_set_state(moby, 4, -1);
                } else {
                    moby_set_state(moby, 2, -1);
                }
                *(s32 *)(vars + 0x100) = 0;
                *(s32 *)(vars + 0x10C) = 0;
            }
        }
        break;
    }
    case 4: {
        f32 height, y;
        char *held = *(char **)(vars + 0xF0);

        qcopy(buf, held + 0x10);
        switch (*(s16 *)(held + 0xAA)) {
        case 0xB85:
            *(f32 *)(buf + 8) += 2.2f;
            break;
        case 0xCFC:
            height = 2.2f;
            y = *(f32 *)(buf + 8);
            goto add_height;
        case 0xFFD:
        default:
            y = *(f32 *)(buf + 8);
            height = 2.0f;
        add_height:
            *(f32 *)(buf + 8) = y + height;
            break;
        }
        moby_transform_joint_to_world(moby, 2, buf + 0x10);
        *(f32 *)(buf + 0x20) = FastVecLength(vars + 0xE0);
        distance = vec_distance_xy(buf + 0x10, buf);
        math_approach_target_with_braking((f32 *)(vars + 0x100), *(f32 *)(buf + 8) - *(f32 *)(buf + 0x18),
            0.008f, 0.008f, 0.20000002f);
        *(f32 *)(vars + 0xFC) += *(f32 *)(vars + 0x100);
        math_approach_target_with_braking((f32 *)(buf + 0x20), distance, 0.008f, 0.008f, 0.20000002f);
        FastVecSub(vars + 0xE0, buf, buf + 0x10);
        *(s32 *)(vars + 0xE8) = 0;
        vec_clamp_length(vars + 0xE0, *(f32 *)(buf + 0x20));
        FastVecAdd(moby + 0x10, moby + 0x10, vars + 0xE0);
        path_push_point_away(*(s32 *)vars, moby + 0x10, moby + 0x10, 1.25f);
        if (fast_vec_dist(buf + 0x10, buf) < 0.01f) {
            moby_set_state(moby, 2, -1);
            *(s32 *)(vars + 0xE8) = 0;
            *(s32 *)(vars + 0x100) = 0;
            switch (*(s16 *)(*(char **)(vars + 0xF0) + 0xAA)) {
            case 0xB85:
            case 0xCFC:
                PlayMobySound(2, 0, moby);
                object_store_mode_release(*(char **)(vars + 0xF0), (s32)moby);
                break;
            case 0xFFD:
                PlayMobySound(2, 0, moby);
                robot_set_speed_state(*(char **)(vars + 0xF0), moby);
                break;
            }
        }
        break;
    }
    }
    if (*(char **)(vars + 0xF0)) {
        *(s32 *)(*(char **)(vars + 0xF0) + 0x98) = *(s32 *)(*(char **)(*(char **)(vars + 0xF0) + 0x24) + 0x10);
    }
    {
        s32 j;

        for (j = 0; j < 3; j++) {
            length = *(f32 *)(vars + 0xFC);
            if (length < g_spring_holder_length_limits[j]) {
                length = g_spring_holder_length_limits[j];
            }
            *(f32 *)(vars + 0x58 + j * 0x40) = length * 1024.0f / *(f32 *)(moby + 0x2C);
        }
    }
    func_002A0F48(moby);
    *(f32 *)(moby + 0xC) *= 4.0f;
}
