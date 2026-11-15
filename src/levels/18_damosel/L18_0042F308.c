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
extern void part_l18_spawn_exhaust(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_draw_beams_both_tables(void *);
extern u8 *g_moby_l18_table;
extern float D_L18_001B1430 __attribute__((sda));
extern float D_L18_001B1434 __attribute__((sda));
extern float D_L18_001B1438 __attribute__((sda));
extern float D_L18_001B143C __attribute__((sda));
extern float D_L18_001B1440 __attribute__((sda));
extern float D_L18_001B1444 __attribute__((sda));
extern float D_L18_001B1448 __attribute__((sda));
extern float D_L18_001B144C __attribute__((sda));
extern float D_L18_001B1450 __attribute__((sda));
extern float D_L18_001B1454 __attribute__((sda));
extern float D_L18_001B1458 __attribute__((sda));
extern float D_L18_001B145C __attribute__((sda));
extern float D_L18_001B1460 __attribute__((sda));
extern float D_L18_001B1468[6] __attribute__((sda));
extern u8 D_L18_001B1480[16] __attribute__((sda));
extern u8 D_L18_001B1490[] __attribute__((sda));
extern u8 D_L18_002A9BE0[];

#define F(p, o) (*(float *)((p) + (o)))
#define W(p, o) (*(int *)((p) + (o)))

/* Turns and tilts the leader toward its target spot, moves it there, places its
   attached pieces, and sprays exhaust particles. */
void leader_steer(u8 *moby, int turn, int tilt)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    int i;

    if (turn) {
        if (moby[0x20] == 2)
            math_update_wrapped_angle_offset(moby, vars + 0xC8, vars + 0xCC, D_L18_001B1444,
                          D_L18_001B1434 * 0.00029088824f, -1.0f);
        else
            math_update_wrapped_angle_offset(moby, vars + 0xC8, vars + 0xCC, D_L18_001B1430,
                          D_L18_001B1434 * 0.00029088824f, -1.0f);
    }
    if (tilt) {
        if (moby[0x20] == 2)
            moby_scale_owner_words_by_angles(moby, vars + 0xD0, vars + 0xD4, D_L18_001B1448,
                          D_L18_001B143C * 0.00029088824f,
                          D_L18_001B1440 * 0.00029088824f);
        else
            moby_scale_owner_words_by_angles(moby, vars + 0xD0, vars + 0xD4, D_L18_001B1438,
                          D_L18_001B143C * 0.00029088824f,
                          D_L18_001B1440 * 0.00029088824f);
    } else {
        ApproachValue(moby + 0xF0, 0.0f, 0.052359886f);
        ApproachValue(moby + 0xF4, 0.0f, 0.052359886f);
    }
    math_step_value_toward_target(moby + 0x10, vars + 0x80, F(vars, 0x70),
                  D_L18_001B1458 * 0.00027777778f,
                  D_L18_001B145C * 0.00027777778f,
                  D_L18_001B1460 * 0.0166666675f);
    math_step_value_toward_target(moby + 0x14, vars + 0x84, F(vars, 0x74),
                  D_L18_001B1458 * 0.00027777778f,
                  D_L18_001B145C * 0.00027777778f,
                  D_L18_001B1460 * 0.0166666675f);
    math_step_value_toward_target(moby + 0x18, vars + 0x88, F(vars, 0x78),
                  D_L18_001B1458 * 0.00027777778f,
                  D_L18_001B145C * 0.00027777778f,
                  D_L18_001B1460 * 0.0166666675f);
    if (vec_distance_xy(moby + 0x10, vars + 0x70) > 1.0f) {
        u8 *heading = moby + 0xF8;
        float angle = mat_fast_helper_a(F(vars, 0x70) - F(moby, 0x10),
                                    F(vars, 0x74) - F(moby, 0x14));
        math_approach_target_with_direction_mode(heading, vars + 0xD8, angle,
                      D_L18_001B144C * 0.0000048481374f,
                      D_L18_001B1450 * 0.0000048481374f,
                      D_L18_001B1454 * 0.00029088824f, 0);
    }
    {
        int *ids = (int *)(vars + 0x90);
        u8 *offset = D_L18_002A9BE0;

        for (i = 0; i < 6; i++, offset += 16, ids++) {
            if (*ids != -1) {
                u8 *piece = g_moby_l18_table + (*ids << 8);
                matrix_mul_vec3(piece + 0x10, offset, moby + 0xC0);
                FastVecAdd(piece + 0x10, piece + 0x10, moby + 0x10);
                if (i < 3) {
                    F(piece, 0xF0) = F(moby, 0xF4);
                    F(piece, 0xF4) = -F(moby, 0xF0);
                    F(piece, 0xF8) = FastAddRotations(F(moby, 0xF8), D_L18_001B1468[i]);
                } else {
                    F(piece, 0xF0) = -F(moby, 0xF4);
                    F(piece, 0xF4) = F(moby, 0xF0);
                    F(piece, 0xF8) = FastAddRotations(F(moby, 0xF8), D_L18_001B1468[i]);
                }
            }
        }
    }
    part_l18_spawn_exhaust(moby, D_L18_001B1480);
    part_l18_spawn_exhaust(moby, D_L18_001B1490);
    gfx_add_draw_callback_third(gfx_draw_beams_both_tables, moby);
}
