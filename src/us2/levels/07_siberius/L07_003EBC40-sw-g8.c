#include "include_asm.h"

#include "common.h"
#define FLOAT_AT(p, offset) (*(float *)((char *)(p) + (offset)))
#define INT_AT(p, offset) (*(int *)((char *)(p) + (offset)))
#define PTR_AT(p, offset) (*(char **)((char *)(p) + (offset)))
#define BYTE_AT(p, offset) (*(unsigned char *)((char *)(p) + (offset)))
extern int g_frame_l07_counter[] __attribute__((sda));
extern int g_cutscene_l07_active_flag NOT_SDA;
extern float g_shooter_cam_distance __attribute__((sda)), g_shooter_cam_height __attribute__((sda));
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x40];
    float target_position[4];
    char padE0[0x21B0];
    char *target_object;
} SiberiusPlayerView;
extern SiberiusPlayerView g_hero_state;
extern char *g_shooter_mount_table[] __attribute__((sda));
extern float g_default_hit_direction[] __attribute__((sda));
extern void shooter_entity_base_update_b(void *);
extern void entity_spawn_death_effects_b(void *);
extern void entity_tick_timers_ride_platform(void *);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_mark_spawned(void *);
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int moby_transform_point_by_attachment(void *, void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void *part_spawn_spinning_effect_moby(void *, void *, void *, int, int, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int moby_aim_move_record_at_target(void *, void *, float, float);
extern int hero_adjust_jump_speed_to_target(void *, float, float, float);
extern int moby_move_to_target_temp_limits(void *, void *, int, float, float, float);
extern int moby_start_effect_from_entry(void *, float);
extern int moby_l01_turn_toward_target(void *, void *);
extern int math_random_int_range(int, int);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int math_is_value_within_step_us2(void *, float);
extern int math_random_int_below(int);
extern int moby_count_group_not_in_state(int, int);
extern int IsPointInCuboid(void *, int);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);

/* Update the phase and behavior state, then run the common update pass. */
void shooter_entity_update_us2(unsigned char *object)
{
    char *state = PTR_AT(object, 0x68);
    char *target_object;
    float origin[4] __attribute__((aligned(16)));
    float target_position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float unit_direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float angle;
    int hit_flags;

    if (g_frame_l07_counter[0] >= 2 && g_cutscene_l07_active_flag != INT_AT(state, 0x320)) return;
    shooter_entity_base_update_b(object);
    switch (object[0x95]) {
    case 0:
        if (INT_AT(state, 0x2DC) == 1) moby_set_state(object, 5, 2);
        else if (INT_AT(state, 0x2D0)) {
            moby_set_state(object, 2, 1);
            INT_AT(state, 0x2D0) = 0;
            if (INT_AT(state, 0x2D4) < 300) INT_AT(state, 0x2D4) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (INT_AT(state, 0x2DC) == 1) moby_set_state(object, 5, 2);
        else if (INT_AT(state, 0x2D4) == 0) moby_set_state(object, 1, 0);
        break;
    case 2:
        follow_camera_set_distance(0, g_shooter_cam_distance, 0.003000000026077032f);
        follow_camera_set_height(g_shooter_cam_height, 0.003000000026077032f);
        if (INT_AT(state, 0x2DC) != 1) {
            moby_set_state(object, 2, 1);
            INT_AT(state, 0x2D4) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        hit_flags = moby_dispatch_action_by_kind(object, state + 0x140);
        if (hit_flags & 1) {
            entity_spawn_death_effects_b(object);
            moby_mark_spawned(object);
            return;
        }
        if (hit_flags & 2) {
            if (INT_AT(state, 0x2DC) == 1) moby_set_state(object, 5, 2);
            else {
                moby_set_state(object, 2, 1);
                INT_AT(state, 0x2D4) = math_random_int_range(580, 600);
            }
        }
    }
    switch (object[0x20]) {
    case 1:
        if (flag_set_first_pending(object) && object[0x43] != 2) anim_start_blended(object, 2, 0, 20);
        break;
    case 2:
        if (flag_set_first_pending(object) && object[0x43] != 5) anim_start_blended(object, 5, 0, 20);
        break;
    case 3:
        if (flag_set_first_pending(object) && object[0x43] != 20) anim_start_blended(object, 20, 0, 20);
        if (math_is_value_within_step_us2(object, 17.0f)) {
            moby_transform_joint_to_world(object, 4, origin);
            target_object = PTR_AT(state, 0x220);
            if (target_object == g_hero_state.target_object) {
                qcopy(target_position, g_hero_state.target_position);
                if (PTR_AT(state, 0x314)) {
                    moby_transform_point_by_attachment(object, PTR_AT(state, 0x314), target_position, axis);
                    FastVecAdd(target_position, target_position, axis);
                }
            } else if (target_object) {
                qcopy(target_position, target_object + 0x10);
                target_position[2] += FLOAT_AT(target_object, 0xC) * 0.0009765625f;
            } else qcopy(target_position, state + 0x210);
            FastVecSub(unit_direction, target_position, origin);
            vec_scale_to_length(unit_direction, unit_direction, 1.0f);
            angle = FastVecDot(object + 0xC0, unit_direction);
            if (angle < math_fast_sin_or_cos_a(0.3490658700466156f)) {
                FastVecSub(delta, target_position, origin);
                qcopy(direction, object + 0xC0);
                FastVecCross(axis, object + 0xC0, delta);
                math_apply_axis_rotation_to_quat(direction, direction, axis, -0.3490658700466156f);
            } else FastVecSub(direction, target_position, origin);
            vec_scale_to_length(direction, direction, 0.3333333432674408f);
            part_spawn_spinning_effect_moby(object, direction, origin, 0, INT_AT(state, 0x314), (float)BYTE_AT(state, 0x34));
        } else if (object[0x60] & 2) {
            if (math_random_int_below(2) ||
                FastDiffRots(FLOAT_AT(object, 0xF8),
                    mat_fast_helper_a(g_hero_state.position[0] - FLOAT_AT(object, 0x10),
                                  g_hero_state.position[1] - FLOAT_AT(object, 0x14))) > 0.3490658700466156f)
                moby_set_state(object, 5, -1);
            else moby_set_state(object, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(object) && object[0x43] != 14) anim_start_blended(object, 14, 0, 20);
        if (object[0x60] & 2) moby_set_state(object, 3, -1);
        break;
    case 5:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 7) anim_start_blended(object, 7, 0, 15);
            angle = mat_fast_helper_a(g_hero_state.position[0] - FLOAT_AT(object, 0x10),
                                  g_hero_state.position[1] - FLOAT_AT(object, 0x14));
            FLOAT_AT(state, 0x324) = FastAddRotations(angle, math_random_signed_float_range(45.0f, 100.0f) * 0.01745329424738884f);
        }
        moby_move_to_target_temp_limits(object, g_default_hit_direction, INT_AT(state, 0x88) | 0x10,
                         FLOAT_AT(state, 0x324), -1.0f, -1.0f);
        moby_start_effect_from_entry(object,
            mat_fast_helper_a(FLOAT_AT(state, 0x210) - FLOAT_AT(object, 0x10),
                          FLOAT_AT(state, 0x214) - FLOAT_AT(object, 0x14)));
        if (INT_AT(state, 0xD0) >= 31 || *(unsigned short *)(object + 0x96) >= 121) moby_set_state(object, 3, -1);
        break;
    case 7:
        if (!moby_count_group_not_in_state(INT_AT(state, 0x2B8), -1) ||
            FLOAT_AT(state, 0x20) < (float)*(short *)(state + 0x24))
            moby_set_state(object, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(object) && object[0x43] != 1) anim_start_blended(object, 1, 0, 2);
        if (object[0x60] & 2) {
            if (INT_AT(state, 0x2C0) == -1 || INT_AT(state, 0x2C4) == -1) moby_set_state(object, 3, 2);
            else moby_set_state(object, 9, -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(object) && object[0x43] != 10) anim_start_blended(object, 10, 0, 2);
        follow_camera_set_distance(0, g_shooter_cam_distance, 0.003000000026077032f);
        follow_camera_set_height(g_shooter_cam_height, 0.003000000026077032f);
        FastVecSub(origin, object + 0x10, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
        matrix_mul_vec3(origin, origin, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7) + 0x40);
        origin[0] = 0.5f;
        matrix_mul_vec3(origin, origin, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7));
        FastVecAdd(origin, origin, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
        moby_l01_turn_toward_target(object, origin);
        if (IsPointInCuboid(object + 0x10, INT_AT(state, 0x2C0))) {
            FastVecSub(target_position, object + 0x10, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7) + 0x30);
            matrix_mul_vec3(target_position, target_position, g_shooter_mount_table[0] + (INT_AT(state, 0x2C0) << 7) + 0x40);
            target_position[0] = math_random_float_range(0.0f, 1.0f);
            matrix_mul_vec3(target_position, target_position, g_shooter_mount_table[0] + (INT_AT(state, 0x2C4) << 7));
            FastVecAdd(target_position, target_position, g_shooter_mount_table[0] + (INT_AT(state, 0x2C4) << 7) + 0x30);
            moby_aim_move_record_at_target(object, target_position, 0.10000000894069672f, 0.0055555556900799274f);
            moby_set_state(object, 10, -1);
        }
        break;
    case 10:
        if (flag_set_first_pending(object) && object[0x43] != 4) anim_start_blended(object, 4, 0, 2);
        hero_adjust_jump_speed_to_target(object, 1.0f, 8.0f, 12.5f);
        follow_camera_set_distance(0, g_shooter_cam_distance, 0.003000000026077032f);
        follow_camera_set_height(g_shooter_cam_height, 0.003000000026077032f);
        FLOAT_AT(state, 0x180) = FLOAT_AT(object, 0x18)-3.0f;
        if (object[0x60] & 2) {
            angle = FastDiffRots(FLOAT_AT(object, 0xF8),
                mat_fast_helper_a(FLOAT_AT(state, 0x210) - FLOAT_AT(object, 0x10),
                              FLOAT_AT(state, 0x214) - FLOAT_AT(object, 0x14)));
            if (angle < 0.1745329350233078f) moby_set_state(object, 3, 2);
            else moby_set_state(object, 5, 2);
        }
        break;
    }
    entity_tick_timers_ride_platform(object);
}
