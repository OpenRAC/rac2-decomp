#include "include_asm.h"

#include "common.h"
extern f32  g_fan_rotation_rate __attribute__((sda));
extern void moby_set_state(char *moby, s32 a1, s32 a2);
extern s32  math_random_int_range(s32 moby, s32 a1);
extern s32  math_random_int_below(s32 moby);
extern f32  FastAddRotations(f32 moby, f32 a1);
extern void moby_set_state(char *moby, s32 a1, s32 a2);
extern f32  func_2EF670(f32 moby, f32 a1);
extern f32  func_2EF110(f32 *moby);
extern f32 g_fan_float_table[] SDATA(D_L03_001B0350);
extern f32 g_trail_projectile_scale __attribute__((sda));
extern u32 g_shared_record_pending;
extern s32  flag_is_third_pending_set(char *moby);
extern s32  PlayMobySound(s32 moby, s32 a1, char *a2);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));
extern s32  g_camera_trigger_active __attribute__((sda));
extern void moby_set_state(char *moby, s32 a1, s32 a2);
extern s32  point_in_path_xy(char *moby, void *a1, u32 a2);
extern f32  FastVecLength(f32 *moby);
extern f32 math_approach_target_with_direction_mode(char *moby, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);

/* Spins a fan at a random speed set when it starts. (PAL) */
void fan_l03_update_pal(char *moby)
{
    if (*(u8 *)(moby + 0x31) == 0) {
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0xBC) = (u8)math_random_int_range(5, 10);
        if (math_random_int_below(2) != 0) {
            *(u8 *)(moby + 0xBC) += 15;
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8),
            g_fan_rotation_rate * 0.0003490659f * (f32)(*(u8 *)(moby + 0xBC) - 15));
        break;
    }
}
