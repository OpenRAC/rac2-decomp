#include "include_asm.h"

#include "common.h"
extern f32  g_fan_rotation_rate __attribute__((sda));
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern void moby_build_effect_packet(char *a0);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void gfx_add_draw_callback_first(void *fn, void *entity);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 g_fan_float_table[] SDATA(D_L03_001B0350);
extern f32 g_trail_projectile_scale __attribute__((sda));
extern u32 g_shared_record_pending;
extern s32  flag_is_third_pending_set(char *a0);
extern s32  PlayMobySound(s32 a0, s32 a1, char *a2);
extern u8  *g_moby_record_base;
extern u8   g_sound_state[];
extern s32  g_ant_bridge_divisor __attribute__((sda));
extern f32  g_ant_bridge_angle_limit __attribute__((sda));
extern s32  g_camera_trigger_active __attribute__((sda));
extern s32  point_in_path_xy(char *a0, void *a1, u32 a2);
extern f32  FastVecLength(f32 *a0);
extern f32 math_approach_target_with_direction_mode(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);

/* case 0 makes the object opaque and moves it to state 1; case 1 scrolls the three
   offsets in its vars by the table's rates per frame (wrapping below -1) and queues
   its draw callback with the object as argument (AddDrawCallback in rac1-decomp) */
void UpdateThreeScrollOffsets_pal(char *a0)
{
    s32 state = *(u8 *)(a0 + 0x20);
    char *s0 = *(char **)(a0 + 0x68);

    switch (state) {
    case 0:
        *(u8 *)(a0 + 0x30) = 0xFF;
        moby_set_state(a0, 1, -1);
        *(s32 *)(s0 + 0xC) = 1;
        break;
    case 1: {
        f32 *dst = (f32 *)s0;
        f32 *src = &g_fan_float_table[0];
        s32 i;

        for (i = 2; i >= 0; i--) {
            f32 f = *dst - *src * 0.020000001f;

            *dst = f;
            if (f < -1.0f)
                *dst = f + 1.0f;
            src++;
            dst++;
        }
        gfx_add_draw_callback_first(moby_build_effect_packet, a0);
        break;
    }
    }
}
