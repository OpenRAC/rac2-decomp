#include "include_asm.h"

#include "common.h"
extern f32 g_part_pitch_speed __attribute__((sda));
extern f32 g_part_pitch_limit __attribute__((sda));
extern f32 g_part_yaw_speed __attribute__((sda));
extern f32 g_part_yaw_limit_min __attribute__((sda));
extern f32 g_part_yaw_limit_max __attribute__((sda));
extern void math_update_wrapped_angle_offset(char *moby, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);
extern void moby_scale_owner_words_by_angles(char *moby, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);

/* Drives the two angle pairs of the state, in degrees converted to radians. */
void parts_turn_to_target_angles_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    math_update_wrapped_angle_offset(moby, (f32 *)(vars + 0x74), (f32 *)(vars + 0x70), g_part_pitch_speed,
                g_part_pitch_limit * 0.0003490659f, -1.0f);
    moby_scale_owner_words_by_angles(moby, (f32 *)(vars + 0x78), (f32 *)(vars + 0x7C), g_part_yaw_speed,
                g_part_yaw_limit_min * 0.0003490659f, g_part_yaw_limit_max * 0.0003490659f);
}
