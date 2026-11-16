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

void leader_steer_pal(u8 *a, int turn, int tilt)
{
    u8 *s = *(u8 **)(a + 0x68);
    int i;

    if (turn) {
        if (a[0x20] == 2)
            math_update_wrapped_angle_offset(a, s + 0xC8, s + 0xCC, g_leader_roll_blend,
                          g_leader_yaw_limit * 0.0003490659f, -1.0f);
        else
            math_update_wrapped_angle_offset(a, s + 0xC8, s + 0xCC, g_leader_yaw_blend,
                          g_leader_yaw_limit * 0.0003490659f, -1.0f);
    }
    if (tilt) {
        if (a[0x20] == 2)
            moby_scale_owner_words_by_angles(a, s + 0xD0, s + 0xD4, g_leader_roll_scale,
                          g_leader_pitch_limit * 0.0003490659f,
                          g_leader_pitch_rate * 0.0003490659f);
        else
            moby_scale_owner_words_by_angles(a, s + 0xD0, s + 0xD4, g_leader_pitch_blend,
                          g_leader_pitch_limit * 0.0003490659f,
                          g_leader_pitch_rate * 0.0003490659f);
    } else {
        ApproachValue(a + 0xF0, 0.0f, 0.062831864f);
        ApproachValue(a + 0xF4, 0.0f, 0.062831864f);
    }
    math_step_value_toward_target(a + 0x10, s + 0x80, F(s, 0x70),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    math_step_value_toward_target(a + 0x14, s + 0x84, F(s, 0x74),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    math_step_value_toward_target(a + 0x18, s + 0x88, F(s, 0x78),
                  g_leader_spin_rate_x * 0.00040000002f,
                  g_leader_spin_rate_y * 0.00040000002f,
                  g_leader_exhaust_speed * 0.020000001f);
    if (vec_distance_xy(a + 0x10, s + 0x70) > 1.0f) {
        u8 *heading = a + 0xF8;
        float angle = mat_fast_helper_a(F(s, 0x70) - F(a, 0x10),
                                    F(s, 0x74) - F(a, 0x14));
        math_approach_target_with_direction_mode(heading, s + 0xD8, angle,
                      g_leader_roll_limit * 6.981318e-06f,
                      g_leader_roll_rate * 6.981318e-06f,
                      g_leader_sway_limit * 0.0003490659f, 0);
    }
    {
        int *ids = (int *)(s + 0x90);
        u8 *offset = g_leader_steer_offsets;

        for (i = 0; i < 6; i++, offset += 16, ids++) {
            if (*ids != -1) {
                u8 *e = g_moby_l18_table + (*ids << 8);
                matrix_mul_vec3(e + 0x10, offset, a + 0xC0);
                FastVecAdd(e + 0x10, e + 0x10, a + 0x10);
                if (i < 3) {
                    F(e, 0xF0) = F(a, 0xF4);
                    F(e, 0xF4) = -F(a, 0xF0);
                    F(e, 0xF8) = FastAddRotations(F(a, 0xF8), g_leader_piece_rotation_table[i]);
                } else {
                    F(e, 0xF0) = -F(a, 0xF4);
                    F(e, 0xF4) = F(a, 0xF0);
                    F(e, 0xF8) = FastAddRotations(F(a, 0xF8), g_leader_piece_rotation_table[i]);
                }
            }
        }
    }
    part_l18_spawn_exhaust_pal(a, g_leader_exhaust_offset_left);
    part_l18_spawn_exhaust_pal(a, g_leader_exhaust_offset_right);
    gfx_add_draw_callback_third(gfx_draw_beams_both_tables, a);
}
