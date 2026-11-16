#include "names.h"
/* func_PAL_L12_004075B8, the PAL copy of func_L12_00402B48: the same C at 50 Hz (0.02f steps, the
   0-255 phase scaled by 5/6 so its range is 212). */
#include "common.h"
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int math_random_int_below(int);
extern u8 g_hero_prev_position[];
extern void FastVecSub(void *,void *,void *),matrix_mul_vec3(void *,void *,void *);
extern float g_sparkle_trail_velocity_a __attribute__((sda)),g_sparkle_trail_velocity_b __attribute__((sda)),g_sparkle_trail_delta_a __attribute__((sda)),g_sparkle_trail_delta_b __attribute__((sda));
extern u8 g_sparkle_trail_spawn_flag __attribute__((sda));
extern int g_sparkle_trail_part_type_a __attribute__((sda)),g_sparkle_trail_part_type_b __attribute__((sda));
extern float g_sparkle_trail_scale_a __attribute__((sda)),g_sparkle_trail_scale_b __attribute__((sda));
extern int g_sparkle_trail_color_a __attribute__((sda)),g_sparkle_trail_color_b __attribute__((sda));
extern float g_sparkle_trail_base_offset __attribute__((sda)),g_sparkle_trail_step __attribute__((sda));
extern int g_sparkle_trail_fade_param_a __attribute__((sda)),g_sparkle_trail_fade_param_b __attribute__((sda));
extern float g_sparkle_trail_local_offset[4] __attribute__((sda));
extern int g_frame_l12_counter MACRO_ADDR;
extern void vec_random_direction(void *,float,float);
extern void *part_spawn_hero_relative(void *,void *,int,int,int,int,float);
extern float IntToFloat(int),math_fabs(float);
extern int FastTweenColor(int,int,float);
extern unsigned char *part_spawn_fading(void *,int,int,int,int,int,int,float);
extern void func_00282E70(void *,void *,void *);

/* Spawns the sparkle trail of a collectible: occasional random sparks at its tip and four fading glows stepping toward the hero (PAL: 50 Hz). */
void gfx_draw_sparkle_trail_to_hero_pal(u8 *moby) {
    float pos[4], velocity[4], delta[4], toward[4], step[4];
    int i, j;

    func_00282E70(pos, g_sparkle_trail_local_offset, moby + 0xC0);
    FastVecAdd(pos, pos, moby + 0x10);
    if (!math_random_int_below(4)) {
        vec_random_direction(velocity, g_sparkle_trail_velocity_a * 0.020000001f,
                     g_sparkle_trail_velocity_b * 0.020000001f);
        part_spawn_hero_relative(pos, velocity, g_sparkle_trail_part_type_a, g_sparkle_trail_spawn_flag,
                     (u8)math_random_int_below(255), 0, g_sparkle_trail_scale_a);
        for (j = 2; j >= 0; j--) {
            vec_random_direction(delta, g_sparkle_trail_delta_a * 0.020000001f,
                         g_sparkle_trail_delta_b * 0.020000001f);
            FastVecAdd(velocity, velocity, delta);
            part_spawn_hero_relative(pos, velocity, g_sparkle_trail_part_type_b, g_sparkle_trail_spawn_flag,
                         (u8)math_random_int_below(255), 0, g_sparkle_trail_scale_b);
        }
    }
    FastVecSub(toward, g_hero_prev_position, pos);
    vec_scale_to_length(toward, toward, -0.3f);
    vec_scale_to_length(step, toward, 0.1f);
    FastVecAdd(toward, toward, pos);
    for (i = 0; i < 4; i++) {
        int color, alpha;

        color = FastTweenColor(g_sparkle_trail_color_a, g_sparkle_trail_color_b,
            math_fabs(0.5f - IntToFloat(
                212 - ((s32)((g_frame_l12_counter + i * 20) & 255) * 5 + 2) / 6) * 0.004716981f));
        alpha = *(u8 *)&g_frame_l12_counter;
        if (i & 2) alpha *= 2;
        if (i & 1) alpha = 255 - alpha;
        part_spawn_fading(toward, color, (u8)alpha, g_sparkle_trail_fade_param_b,
                     g_sparkle_trail_fade_param_a, 2, 0,
                     (g_sparkle_trail_base_offset + IntToFloat(i) * g_sparkle_trail_step) *
                     (*(float *)(moby + 0x2C) /
                      *(float *)(*(u8 **)(moby + 0x24) + 0x24)));
        FastVecAdd(toward, toward, step);
    }
}
