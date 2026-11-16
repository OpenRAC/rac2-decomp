#include "include_asm.h"

#include "common.h"
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern f32 ApproachValue(void *, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void part_l18_spawn_exhaust_pal(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_draw_beams_both_tables(void *);
extern u8 *g_moby_l18_table;
extern float g_leader_yaw_blend __attribute__((sda));
extern float g_leader_yaw_limit __attribute__((sda));
extern float g_leader_pitch_blend __attribute__((sda));
extern float g_leader_pitch_limit __attribute__((sda));
extern float g_leader_pitch_rate __attribute__((sda));
extern float g_leader_roll_blend __attribute__((sda));
extern float g_leader_roll_scale __attribute__((sda));
extern float g_leader_roll_limit __attribute__((sda));
extern float g_leader_roll_rate __attribute__((sda));
extern float g_leader_sway_limit __attribute__((sda));
extern float g_leader_spin_rate_x __attribute__((sda));
extern float g_leader_spin_rate_y __attribute__((sda));
extern float g_leader_exhaust_speed __attribute__((sda));
extern float g_leader_piece_rotation_table[6] __attribute__((sda));
extern u8 g_leader_exhaust_offset_left[16] __attribute__((sda));
extern u8 g_leader_exhaust_offset_right[] __attribute__((sda));
extern u8 g_leader_steer_offsets[];
#define F(p, o) (*(float *)((p) + (o)))

/* Turns and tilts the leader toward its target spot, moves it there, places its attached pieces, and sprays exhaust particles. (PAL: 50 Hz timings) */
void leader_steer_pal(u8 *moby, int turn, int tilt)
{
    u8 *state = *(u8 **)(moby + 0x68);
    int i;

    if (turn) {
        if (moby[0x20] == 2)
            math_update_wrapped_angle_offset(moby, state + 0xC8, state + 0xCC, g_leader_roll_blend,
                          g_leader_yaw_limit * 0.0003490659f, -1.0f);
        else
            math_update_wrapped_angle_offset(moby, state + 0xC8, state + 0xCC, g_leader_yaw_blend,
                          g_leader_yaw_limit * 0.0003490659f, -1.0f);
    }
    if (tilt) {
        if (moby[0x20] == 2)
            moby_scale_owner_words_by_angles(moby, state + 0xD0, state + 0xD4, g_leader_roll_scale,
                          g_leader_pitch_limit * 0.0003490659f,
                          g_leader_pitch_rate * 0.0003490659f);
        else
            moby_scale_owner_words_by_angles(moby, state + 0xD0, state + 0xD4, g_leader_pitch_blend,
                          g_leader_pitch_limit * 0.0003490659f,
                          g_leader_pitch_rate * 0.0003490659f);
    } else {
        ApproachValue(moby + 0xF0, 0.0f, 0.062831864f);
        ApproachValue(moby + 0xF4, 0.0f, 0.062831864f);
    }
    math_step_value_toward_target(moby + 0x10, state + 0x80, F(state, 0x70),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    math_step_value_toward_target(moby + 0x14, state + 0x84, F(state, 0x74),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    math_step_value_toward_target(moby + 0x18, state + 0x88, F(state, 0x78),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    if (vec_distance_xy(moby + 0x10, state + 0x70) > 1.0f) {
        u8 *heading = moby + 0xF8;
        float angle = mat_fast_helper_a(F(state, 0x70) - F(moby, 0x10),
                                    F(state, 0x74) - F(moby, 0x14));
        math_approach_target_with_direction_mode(heading, state + 0xD8, angle,
                      g_leader_roll_limit * 6.981318e-06f,
                      g_leader_roll_rate * 6.981318e-06f,
                      g_leader_sway_limit * 0.0003490659f, 0);
    }
    {
        int *ids = (int *)(state + 0x90);
        u8 *offset = g_leader_steer_offsets;

        for (i = 0; i < 6; i++, offset += 16, ids++) {
            if (*ids != -1) {
                u8 *piece = g_moby_l18_table + (*ids << 8);
                matrix_mul_vec3(piece + 0x10, offset, moby + 0xC0);
                FastVecAdd(piece + 0x10, piece + 0x10, moby + 0x10);
                if (i < 3) {
                    F(piece, 0xF0) = F(moby, 0xF4);
                    F(piece, 0xF4) = -F(moby, 0xF0);
                    F(piece, 0xF8) = FastAddRotations(F(moby, 0xF8), g_leader_piece_rotation_table[i]);
                } else {
                    F(piece, 0xF0) = -F(moby, 0xF4);
                    F(piece, 0xF4) = F(moby, 0xF0);
                    F(piece, 0xF8) = FastAddRotations(F(moby, 0xF8), g_leader_piece_rotation_table[i]);
                }
            }
        }
    }
    part_l18_spawn_exhaust_pal(moby, g_leader_exhaust_offset_left);
    part_l18_spawn_exhaust_pal(moby, g_leader_exhaust_offset_right);
    gfx_add_draw_callback_third(gfx_draw_beams_both_tables, moby);
}
