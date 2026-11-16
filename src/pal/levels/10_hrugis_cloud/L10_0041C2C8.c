#include "include_asm.h"

#include "common.h"
extern u8 *moby_get_motion_data(u8 *);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 fast_vec_dist(void *, void *);
extern f32 FastVecDot(void *, void *);
extern f32 math_fast_angle_helper(f32);
extern f32 FastVecLength(void *);
extern u8 g_view_origin_vec[];
extern f32 func_00335320(void);
extern u8 *func_0037B670();
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern u8 *g_unused_pointer_table[];
extern u8 *g_moby_pool_base;
extern u8 g_group_state_buffer[];
extern u8 g_effect_l10_record_table[];
extern u8 g_mission_state[];
extern u8 g_sound_state[];
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_angle(void);
extern u8 *g_spot_record_table __attribute__((sda));
extern u8 *moby_get_motion_data(u8 *arg0);
extern f32 math_random_angle(void);
extern f32 math_fast_sin_or_cos_a(f32 f12);
extern f32 func_00309B38(f32 f12, f32 f13);
extern u8 func_L10_00423780(void);

/* func_L10_004170F8 is in L10_003170D0-path-g8.c. */

/* func_L10_004174C8 is in L10_003170D0-g8.c: it only comes out right with -G8. */

/* Raises the boss sway speeds in state 1 and lowers them in state 2, within limits (PAL copy of hrugis_update_sway_speed). */
void hrugis_update_sway_speed_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 1:
        *(f32 *)(vars + 0x2CC) = *(f32 *)(vars + 0x2CC) + 5.5850545e-05f;
        *(f32 *)(vars + 0x2D0) = *(f32 *)(vars + 0x2D0) + 5.5850545e-05f;
        if (*(f32 *)(vars + 0x2CC) > 0.027925273f)
            *(f32 *)(vars + 0x2CC) = 0.027925273f;
        if (*(f32 *)(vars + 0x2D0) > 0.013962637f)
            *(f32 *)(vars + 0x2D0) = 0.013962637f;
        break;
    case 2:
        *(f32 *)(vars + 0x2CC) = *(f32 *)(vars + 0x2CC) - 8.377582e-05f;
        *(f32 *)(vars + 0x2D0) = *(f32 *)(vars + 0x2D0) - 8.377582e-05f;
        if (*(f32 *)(vars + 0x2CC) < 0.0f)
            *(f32 *)(vars + 0x2CC) = 0.0f;
        if (*(f32 *)(vars + 0x2D0) < 0.0f)
            *(f32 *)(vars + 0x2D0) = 0.0f;
        break;
    }
}

