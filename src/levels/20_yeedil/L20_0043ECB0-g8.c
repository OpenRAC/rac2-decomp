#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern int g_moby_glow_trail_texture __attribute__((sda));

extern float g_local_to_world_vec __attribute__((sda));

extern float g_motion_limit_speed __attribute__((sda));

extern float g_motion_limit_accel __attribute__((sda));

extern float g_motion_limit_small_angle __attribute__((sda));

extern float g_motion_limit_angle __attribute__((sda));

extern float g_motion_range_speed __attribute__((sda));

extern float g_motion_range_accel __attribute__((sda));

extern float g_motion_range_angle __attribute__((sda));

extern float g_motion_range_small_angle __attribute__((sda));

extern void moby_set_controller_speed_limits(char *, float, float, float, float);

extern void FastVecAdd(char *, char *, char *);

extern void matrix_mul_vec3(char *, int *, char *);

/* Sets the motion limits of a moby from four stored settings, converting them to game units. */
void moby_set_motion_limits(char *moby) {
    moby_set_controller_speed_limits(moby, g_motion_limit_accel * 0.000277777785f,
                  g_motion_limit_speed * 0.0166666675f,
                  g_motion_limit_small_angle * 4.84813745e-06f,
                  g_motion_limit_angle * 0.000290888245f);
}

/* Sets the motion limits of a moby like the function above, and also stores an extra range value. */
void moby_set_motion_limits_range(char *moby, float range) {
    char *state = *(char **)(moby + 0x68);

    moby_set_controller_speed_limits(moby, g_motion_range_accel * 0.000277777785f,
                  g_motion_range_speed * 0.0166666675f,
                  g_motion_range_small_angle * 4.84813745e-06f,
                  g_motion_range_angle * 0.000290888245f);
    *(float *)(state + 0x84) = range;
}

/* Turns a point from the moby's own space into world space by rotating it and adding the moby position. */
void moby_local_to_world_point(char *moby, char *point) {
    matrix_mul_vec3(point, &g_local_to_world_vec, moby + 0xC0);
    FastVecAdd(point, point, moby + 0x10);
}

extern void part_draw_glow_quad(char *, int);

extern void DrawTaperedBeam(TI128 *, char *, int, int, float, float);

/* Leaves a short glowing trail behind a moving moby. */
void part_add_moby_glow_trail(char *moby) {
    TI128 position;
    char *state = *(char **)(moby + 0x68);

    part_draw_glow_quad(moby + 0x10, g_moby_glow_trail_texture);
    position = *(TI128 *)(moby + 0x10);
    DrawTaperedBeam(&position, state + 0x10, g_moby_glow_trail_texture, 3,
                      *(float *)(state + 0x74), 0.25f);
}

extern float g_moby_smooth_value __attribute__((sda));

extern void value_set_and_smooth(void *, void *, int, int, float);

/* Counts up a frame counter on the moby, up to its limit, and plays its looping animation. */
void moby_advance_frame_counter(char *moby) {
    char *state = *(char **)(moby + 0x68);
    unsigned short frameCount = *(unsigned short *)(moby + 0x96);

    if (frameCount <= 0xFFFE) {
        *(unsigned short *)(moby + 0x96) = frameCount + 1;
    }
    value_set_and_smooth(moby, state + 0x2B0, 2, 1, g_moby_smooth_value);
}

extern float g_yeedil_shot_speed __attribute__((sda));

extern int g_yeedil_shot_homing_param __attribute__((sda));

extern void vec_scale_to_length(char *, char *, float);

extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);

extern char *homing_l20_shot_spawn(char *, char *, char *, char *, int, float, int);

/* func_L20_00444088 is defined in L20_00444088-g8.c (it needs its own flags). */

extern float g_shard_speed_min __attribute__((sda));

extern float g_shard_speed_max;

extern int g_shard_puff_color_a __attribute__((sda));

extern int g_shard_puff_color_b __attribute__((nosda));

extern int g_shard_color __attribute__((nosda));

extern int g_shard_color_a __attribute__((nosda));

extern int g_shard_color_b __attribute__((nosda));

extern char g_effect_color_table[];

extern float math_random_float_range(float, float);

extern int math_random_int_range(int, int);

extern void part_spawn_growing_puff(char *, char *, int, int, int, float);

/* Spawns a small particle at the moby with random speed and lifetime. */
void part_spawn_shard(char *mobyArg) {
    char *moby = mobyArg;
    float speed;
    int lifetime;
    int colors[2];

    speed = math_random_float_range(g_shard_speed_min, g_shard_speed_max) * 210000.0f;
    lifetime = math_random_int_range(0x14, 0x50);
    if (*(short *)(moby + 0xAA) == 0xB5A /* moby class 2906 */) {
        colors[0] = g_shard_puff_color_a;
        colors[1] = g_shard_color;
    } else {
        colors[0] = g_shard_color_a;
        colors[1] = g_shard_color_b;
    }
    part_spawn_growing_puff(moby + 0x10, g_effect_color_table, g_shard_puff_color_a, g_shard_puff_color_b, lifetime, speed);
}
