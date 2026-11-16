#include "include_asm.h"

#include "common.h"
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_animation_and_speed(void *, int, int, int);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_step_at_own_position_factor_pal(void *, float);
typedef struct {
    u8 prefix[0x30];
    float centre[4];
    u8 rest[0x40];
} L01ArenaRow;
extern L01ArenaRow *g_swamp_patrol_positions[] __attribute__((sda));
extern float g_swamp_monster_arena_turn_angle __attribute__((sda));
typedef struct {
    u8 prefix[0x80];
    float position[4];
} L01HeroPositionView;
extern u8 g_hero_state[];

/* Moves the Swamp Monster II around the arena centre towards its target, and returns its distance to the target (PAL version). */
float swamp_monster_move_around_arena_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float distance, angle, delta, magnitude;

    if (*(int *)(state + 0x124) == 1) {
        distance = vec_distance_xy(moby + 0x10, *(u8 **)(state + 0x120) + 0x10);
        angle = mat_fast_helper_a(
            *(float *)(moby + 0x10) - g_swamp_patrol_positions[0][*(int *)(state + 0x2CC)].centre[0],
            *(float *)(moby + 0x14) - g_swamp_patrol_positions[0][*(int *)(state + 0x2CC)].centre[1]);
        delta = fast_subtract_rotations(
            mat_fast_helper_a(
                *(float *)(*(u8 **)(state + 0x120) + 0x10) - g_swamp_patrol_positions[0][*(int *)(state + 0x2CC)].centre[0],
                *(float *)(*(u8 **)(state + 0x120) + 0x14) - g_swamp_patrol_positions[0][*(int *)(state + 0x2CC)].centre[1]),
            angle);
        magnitude = math_fabs(delta);
        if (distance > *(float *)(state + 0x2EC)) {
            if (moby[0x43] != state[0x2E1])
                moby_set_animation_and_speed(moby, state[0x2E1], 0, 20);
            if (magnitude < g_swamp_monster_arena_turn_angle * 0.017453294f) {
                qcopy(state + 0x2A0, *(u8 **)(state + 0x120) + 0x10);
            } else {
                delta = delta / magnitude;
                delta = delta * 0.087266474f;
                qcopy(state + 0x2A0, g_swamp_patrol_positions[0][*(int *)(state + 0x2CC)].centre);
                *(float *)(state + 0x2A0) += math_fast_sin_or_cos_a(FastAddRotations(angle, delta)) * 38.0f;
                *(float *)(state + 0x2A4) += math_fast_sin_or_cos_b(FastAddRotations(angle, delta)) * 38.0f;
            }
            moby_l01_turn_toward_target_pal(moby, state + 0x2A0);
            *(float *)(moby + 0x18) = *(float *)(state + 0x2E8);
        } else {
            if (moby[0x43] != state[0x2E2] && moby[0x95] != 3)
                moby_set_animation_and_speed(moby, state[0x2E2], 0, 20);
            moby_step_at_own_position_factor_pal(moby, mat_fast_helper_a(*(float *)(*(u8 **)(state + 0x120) + 0x10) - *(float *)(moby + 0x10),
                                             *(float *)(*(u8 **)(state + 0x120) + 0x14) - *(float *)(moby + 0x14)));
            *(float *)(moby + 0x18) = *(float *)(state + 0x2E8);
        }
        return distance;
    }
    if (moby[0x43] != state[0x2E2] && moby[0x95] != 3)
        moby_set_animation_and_speed(moby, state[0x2E2], 0, 20);
    moby_step_at_own_position_factor_pal(moby, mat_fast_helper_a(((L01HeroPositionView *)g_hero_state)->position[0] - *(float *)(moby + 0x10),
                                     ((L01HeroPositionView *)g_hero_state)->position[1] - *(float *)(moby + 0x14)));
    *(float *)(moby + 0x18) = *(float *)(state + 0x2E8);
    return -1000.0f;
}
