#include "include_asm.h"

#include "common.h"
#define F(p, o) (*(float *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
extern void drone_setup_and_hits_pal(char *);
extern void drone_count_frames_draw_glow(char *);
extern void drone_kill_with_effects_pal(char *);
extern void drone_aim_head_at_hero_pal(char *);
extern u8 *joba_spark_create_pal(void *, void *, void *, float);
extern void PlacePointWithPolarJitterFlat(float, void *, void *, float, float);
extern int projectile_compute_flight_time(float, float, float, float);
extern char *arena_get_center_point(void *);
extern float vec_distance_xy(void *, void *);
extern float vec_distance_squared_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern int flag_set_first_pending(void *);
extern int math_random_int_below(int);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern int moby_step_at_own_position_pal(void *);
extern float moby_get_anim_value(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern int PlayMobySound(int, int, void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int math_fast_float_d(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern float g_l11_enemy_height_step __attribute__((sda));
extern float g_l11_enemy_state_value __attribute__((sda));
extern float g_l11_enemy_aim_jitter_radius __attribute__((sda));
extern float g_l11_enemy_aim_range __attribute__((sda));
extern int g_l11_enemy_fire_timer_init __attribute__((sda));
extern int g_l11_enemy_spin_random_range __attribute__((sda));
extern char g_l11_enemy_local_offset[16] SDATA(D_L11_001B1360) __attribute__((sda));

/* Updates the airborne tumble, approach, firing and reaction states. */
void UpdateTumbleAndFireStates_pal(char *object)
{
    float target[4], before[4], after[4], delta[4], velocity[16];
    char *state = *(char **)(object + 0x68);
    float distance, angle, height, frames, anim;
    int result, fire_timer;
    char *pos;
    char *aim;

    drone_setup_and_hits_pal(object);
    qcopy(target, state + 0x50);
    pos = object + 0x10;
    distance = vec_distance_xy(pos, target);
    angle = mat_fast_helper_a(target[0] - F(object, 0x10), target[1] - F(object, 0x14));
    FastDiffRots(F(object, 0xF8), angle);
    switch (B(object, 0x20)) {
    case 3:
        if (flag_set_first_pending(object)) {
            height = F(object, 0x18);
            height -= g_l11_enemy_height_step;
            F(object, 0xF8) = angle;
            I(object, 0xF0) = 0;
            I(object, 0xF4) = 0;
            frames = projectile_compute_flight_time(height,
                F(arena_get_center_point(*(void **)(object + 0xB8)), 8),
                F(state, 0x2A8), F(state, 0x2AC));
            F(state, 0x2B0) = (math_random_int_below(g_l11_enemy_spin_random_range) + 1) * 6.2831855f / frames;
            F(state, 0x2B4) = (math_random_int_below(g_l11_enemy_spin_random_range) + 1) * 6.2831855f / frames;
            F(state, 0x2B8) = (math_random_int_below(g_l11_enemy_spin_random_range) + 1) * 6.2831855f / frames;
        }
        height = F(object, 0x18);
        height -= g_l11_enemy_height_step;
        if (height >= F(arena_get_center_point(*(void **)(object + 0xB8)), 8)) {
            FastVecAdd(pos, pos, state + 0x2A0);
            F(state, 0x2A8) -= F(state, 0x2AC);
            matrix_mul_vec3(before, g_l11_enemy_local_offset, object + 0xC0);
            F(object, 0xF0) = FastAddRotations(F(state, 0x2B0), F(object, 0xF0));
            F(object, 0xF4) = FastAddRotations(F(state, 0x2B4), F(object, 0xF4));
            F(object, 0xF8) = FastAddRotations(F(state, 0x2B8), F(object, 0xF8));
            euler_rotation_basis(object + 0xC0, object + 0xF0);
            matrix_mul_vec3(after, g_l11_enemy_local_offset, object + 0xC0);
            FastVecSub(delta, before, after);
            FastVecAdd(pos, pos, delta);
        } else {
            I(object, 0xF0) = 0;
            I(object, 0xF4) = 0;
            moby_set_state(object, 4, -1);
        }
        break;
    case 4:
        result = flag_set_first_pending(object);
        aim = state + 0x2C0;
        if (result) {
            if (B(object, 0x43) != 7)
                anim_start_blended_pal(object, 7, 0, 2);
            F(object, 0x48) = g_l11_enemy_state_value;
            qcopy(aim, pos);
            PlacePointWithPolarJitterFlat(g_l11_enemy_aim_jitter_radius, aim, target, 45, 2);
        }
        F(object, 0x18) -= g_l11_enemy_height_step;
        moby_turn_toward_target_and_step_pal(object, aim, F(state, 0x2D4));
        F(object, 0x18) += g_l11_enemy_height_step;
        if (vec_distance_squared_xy(object + 0x10, aim) < 4.84f && B(object, 0x31)) {
            F(object, 0x48) = 1;
            moby_set_state(object, 5, -1);
            return;
        }
        if (vec_distance_squared_xy(aim, target) > g_l11_enemy_aim_range * g_l11_enemy_aim_range) {
            moby_set_state(object, 4, -1);
            return;
        }
        break;
    case 5:
        if (flag_set_first_pending(object)) {
            B(object, 0xBC) = 0;
            if (B(object, 0x43) != 3)
                anim_start_blended_pal(object, 3, 0, 2);
            I(state, 0x2D0) = 0;
        } else {
            if (B(object, 0xBC) == 0) {
                if (B(object, 0x60) & 2) {
                    B(object, 0xBC) = 1;
                    if (B(object, 0x43) != 4)
                        anim_start_blended_pal(object, 4, 0, 6);
                    F(object, 0x48) = I(state, 0x2E4);
                    goto attack;
                }
            }
            if (B(object, 0xBC) == 3 && (B(object, 0x60) & 2))
                moby_set_state(object, 4, -1);
        }
attack:
        if (B(object, 0xBC) == 1) {
            anim = moby_get_anim_value(object);
            drone_aim_head_at_hero_pal(object);
            PlayMobySound(2, 0, object);
            if (!I(state, 0x2D0) && anim < (fire_timer = g_l11_enemy_fire_timer_init) + 1) {
                I(state, 0x2D0) = ((s32)(fire_timer) * 5 + 2) / 6;
                moby_transform_joint_to_world(object, 1, before);
                /* This helper writes the complete 64-byte joint matrix. */
                moby_transform_joint_point(object, 1, velocity);
                joba_spark_create_pal(before, object, velocity, B(state, 0x34));
                snd_play_from_class_bank(0, 0, object, 0xD4B);
            }
            math_fast_float_d(state + 0x2D0);
            if (distance > g_l11_enemy_aim_range) {
                B(object, 0xBC) = 3;
                F(object, 0x48) = 1;
                if (B(object, 0x43) != 5)
                    anim_start_blended_pal(object, 5, 0, 2);
            }
        }
        F(object, 0x18) -= g_l11_enemy_height_step;
        moby_step_at_own_position_pal(object);
        F(object, 0x18) += g_l11_enemy_height_step;
        break;
    case 6:
        if (flag_set_first_pending(object))
            snd_play_from_class_bank(2, 0, object, 0xD4B);
        result = moby_dispatch_action_by_kind(object, state + 0x170);
        if (result & 2)
            moby_set_state(object, 4, 1);
        if (result & 1) {
            PlayMobySound(3, 0, object);
            drone_kill_with_effects_pal(object);
        }
        break;
    }
    drone_count_frames_draw_glow(object);
}
