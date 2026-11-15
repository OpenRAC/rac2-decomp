#include "include_asm.h"

#include "common.h"
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern void ApproachValue(void *, float, float);
extern void math_step_value_toward_target(void *, void *, float, float, float, float);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void func_PAL_L18_004347D0(void *, void *);
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

void func_PAL_L18_00434320(u8 *a, int turn, int tilt)
{
    u8 *s = *(u8 **)(a + 0x68);
    int i;

    if (turn) {
        if (a[0x20] == 2)
            math_update_wrapped_angle_offset(a, s + 0xC8, s + 0xCC, D_L18_001B1444,
                          D_L18_001B1434 * 0.0003490659f, -1.0f);
        else
            math_update_wrapped_angle_offset(a, s + 0xC8, s + 0xCC, D_L18_001B1430,
                          D_L18_001B1434 * 0.0003490659f, -1.0f);
    }
    if (tilt) {
        if (a[0x20] == 2)
            moby_scale_owner_words_by_angles(a, s + 0xD0, s + 0xD4, D_L18_001B1448,
                          D_L18_001B143C * 0.0003490659f,
                          D_L18_001B1440 * 0.0003490659f);
        else
            moby_scale_owner_words_by_angles(a, s + 0xD0, s + 0xD4, D_L18_001B1438,
                          D_L18_001B143C * 0.0003490659f,
                          D_L18_001B1440 * 0.0003490659f);
    } else {
        ApproachValue(a + 0xF0, 0.0f, 0.062831864f);
        ApproachValue(a + 0xF4, 0.0f, 0.062831864f);
    }
    math_step_value_toward_target(a + 0x10, s + 0x80, F(s, 0x70),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    math_step_value_toward_target(a + 0x14, s + 0x84, F(s, 0x74),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    math_step_value_toward_target(a + 0x18, s + 0x88, F(s, 0x78),
                  D_L18_001B1458 * 0.00040000002f,
                  D_L18_001B145C * 0.00040000002f,
                  D_L18_001B1460 * 0.020000001f);
    if (vec_distance_xy(a + 0x10, s + 0x70) > 1.0f) {
        u8 *heading = a + 0xF8;
        float angle = mat_fast_helper_a(F(s, 0x70) - F(a, 0x10),
                                    F(s, 0x74) - F(a, 0x14));
        math_approach_target_with_direction_mode(heading, s + 0xD8, angle,
                      D_L18_001B144C * 6.981318e-06f,
                      D_L18_001B1450 * 6.981318e-06f,
                      D_L18_001B1454 * 0.0003490659f, 0);
    }
    {
        int *ids = (int *)(s + 0x90);
        u8 *offset = D_L18_002A9BE0;

        for (i = 0; i < 6; i++, offset += 16, ids++) {
            if (*ids != -1) {
                u8 *e = g_moby_l18_table + (*ids << 8);
                matrix_mul_vec3(e + 0x10, offset, a + 0xC0);
                FastVecAdd(e + 0x10, e + 0x10, a + 0x10);
                if (i < 3) {
                    F(e, 0xF0) = F(a, 0xF4);
                    F(e, 0xF4) = -F(a, 0xF0);
                    F(e, 0xF8) = FastAddRotations(F(a, 0xF8), D_L18_001B1468[i]);
                } else {
                    F(e, 0xF0) = -F(a, 0xF4);
                    F(e, 0xF4) = F(a, 0xF0);
                    F(e, 0xF8) = FastAddRotations(F(a, 0xF8), D_L18_001B1468[i]);
                }
            }
        }
    }
    func_PAL_L18_004347D0(a, D_L18_001B1480);
    func_PAL_L18_004347D0(a, D_L18_001B1490);
    gfx_add_draw_callback_third(gfx_draw_beams_both_tables, a);
}
