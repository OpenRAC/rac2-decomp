#include "common.h"

/* This unit is built with -G8: every body here reaches a global through $gp. */

extern float g_platform_bob_amplitude __attribute__((sda));

extern float g_platform_bob_period __attribute__((sda));

extern float g_platform_sway_amplitude __attribute__((sda));

extern float g_platform_sway_period __attribute__((sda));

extern float g_platform_tilt_period __attribute__((sda));

extern float g_platform_footprint_half_size __attribute__((sda));

extern float g_hero_position[];

extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);

extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);

extern void FastVecSub(float *, float *, float *);

extern void mat_fast_helper_c(float *, float *);

extern void matrix_mul_vec3(float *, float *, float *);

extern float math_fabs(float);

/* Re-aims one record's two angle pairs from the level's shared angle words: the 0x118/0x11C
   pair takes 0.000290888245f (arcseconds to radians) times the shared 0x1B0330 word, with the
   record's own 0x12C float as the third argument in the type-3 arm and -1.0f otherwise; the
   0x120/0x124 pair then takes the other two scaled words. */
void platform_update_bob_sway(char *moby)
{
    char *state = *(char **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 3) {
        math_update_wrapped_angle_offset(moby, state + 0x11C, state + 0x118, g_platform_bob_amplitude,
                      g_platform_bob_period * 0.000290888245f,
                      *(f32 *)(state + 0x12C));
    } else {
        math_update_wrapped_angle_offset(moby, state + 0x11C, state + 0x118, g_platform_bob_amplitude,
                      g_platform_bob_period * 0.000290888245f, -1.0f);
    }
    moby_scale_owner_words_by_angles(moby, state + 0x120, state + 0x124, g_platform_sway_amplitude,
                  g_platform_sway_period * 0.000290888245f,
                  g_platform_tilt_period * 0.000290888245f);
}

/* Transforms the level's fixed point through the object's own matrix, then through the
   object's second matrix, and keeps the result when both coordinates stay inside the
   shared bound and the object's own height is within two of the fixed point's. */
int platform_is_player_inside_footprint(char *moby)
{
    float local_point[4];
    float matrix[12];

    FastVecSub(local_point, g_hero_position, moby + 0x10);
    mat_fast_helper_c(matrix, moby + 0xC0);
    matrix_mul_vec3(local_point, local_point, matrix);
    if (!(math_fabs(local_point[0]) <= g_platform_footprint_half_size))
        return 0;
    if (!(math_fabs(local_point[1]) <= g_platform_footprint_half_size))
        return 0;
    if (math_fabs(g_hero_position[2] - *(float *)(moby + 0x18)) < 2.0f)
        return 1;
    return 0;
}

extern s32 g_flashing_frame;

/* Scales the level's shared word by the object's own signed halfword, takes it modulo
   sixty and paints the object with 0x80FFFFFF when the remainder is under fifteen and
   with 0x80404040 otherwise; then it sets the sub-object's two flag words. */
void flashing_update(s32 moby)
{
    s32 frame = g_flashing_frame;
    s32 period = 60;
    s32 value = *(short *)(moby + 0xB2);
    s32 dim_color = 0x80404040;
    s32 bright_color = 0x80FFFFFF;
    s32 color;
    s32 vars;

    frame = frame + value;
    value = frame % period;
    if (value >= 15)
        color = dim_color;
    else
        color = bright_color;
    *(s32 *)(moby + 0x78) = color;
    vars = *(s32 *)(moby + 0x68);
    *(u32 *)(vars + 0x8C) |= 1;
    *(u16 *)(vars + 0x3E) |= 8;
    *(u8 *)(moby + 0x30) = 0;
}
