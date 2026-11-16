#include "common.h"
extern u8 *g_moby_l07_array[] __attribute__((sda));
typedef struct { u8 pad[0x34]; f32 y; u8 rest[0x80 - 0x38]; } Record5B50;
extern Record5B50 *g_shooter_mount_table[] __attribute__((sda));
typedef struct {
    u8 pad[0x80];
    f32 position[4];
    f32 rotation[4];
    u8 rest[0x33C - 0xA0];
    u8 *platform;
} Player5B50;
extern Player5B50 g_lift_state;
extern u8 g_hero_position_block[];
extern f32 g_platform_height_tolerance __attribute__((sda));
extern f32 g_lift_height_offset __attribute__((sda));
extern f32 math_fabs(f32);
extern f32 mat_fast_helper_a(f32, f32);
extern u8 *moby_get_private_value_2(void *);
extern s32 IsPointInCuboid(void *, s32);
extern void hero_reset_position_and_direction(void *, void *, s32, s32);
/* Nudges the object up or down in small steps to stay level with the lift beside it. It also turns the player to face it when the player stands on the lift. */
void lift_keep_height(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *lift = g_moby_l07_array[0] + (*(s32 *)(state + 0xE8) << 8);
    f32 height_diff = *(f32 *)(moby + 0x14) - g_shooter_mount_table[0][*(s32 *)(state + 0xEC)].y;
    f32 step, saved_yaw;
    f32 max_step = 1.0f/6.0f;
    u8 *lift_parent;
    if (*(f32 *)(lift + 0x18) < 218.5f) {
        step = height_diff + 4.0f;
        if (math_fabs(step) < g_platform_height_tolerance) {
            if (step < 0.0f) step = -(step + g_platform_height_tolerance);
            else step = g_platform_height_tolerance - step;
            if (step > max_step) step = 1.0f/6.0f;
            else if (step < -max_step) step = -max_step;
            *(f32 *)(moby + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(lift + 0x18) > 199.7f) {
        step = height_diff - 4.0f;
        if (math_fabs(step) < g_platform_height_tolerance) {
            if (step < 0.0f) step = -(step + g_platform_height_tolerance);
            else step = g_platform_height_tolerance - step;
            if (step > max_step) step = 1.0f/6.0f;
            else if (step < -max_step) step = -max_step;
            *(f32 *)(moby + 0x14) += step;
            *(f32 *)(state + 0x54) = 0.0f;
            *(f32 *)(state + 0x64) += step;
        }
    }
    if (*(f32 *)(lift + 0x18) > 202.0f && *(f32 *)(lift + 0x18) < 204.0f && g_lift_state.platform == lift) {
        lift_parent = moby_get_private_value_2(lift);
        if (lift_parent != 0 && *(f32 *)(lift_parent + 0x18) > 0.0f && !IsPointInCuboid(g_hero_position_block, *(s32 *)(state + 0xEC))) {
            saved_yaw = g_lift_state.rotation[2];
            g_lift_state.rotation[2] = mat_fast_helper_a(g_lift_state.position[0] - *(f32 *)(lift + 0x10), g_lift_state.position[1] - *(f32 *)(lift + 0x14));
            hero_reset_position_and_direction(g_lift_state.position, g_lift_state.rotation, 0x6F, 1);
            g_lift_state.rotation[2] = saved_yaw;
            hero_reset_position_and_direction(g_lift_state.position, g_lift_state.rotation, 0, 0);
        }
    }
    if (IsPointInCuboid(moby + 0x10, *(s32 *)(state + 0xEC))) {
        *(f32 *)(moby + 0x18) = *(f32 *)(lift + 0x18) + g_lift_height_offset;
        *(f32 *)(state + 0x68) = *(f32 *)(moby + 0x18);
        *(f32 *)(state + 0x58) = 0.0f;
    }
}
