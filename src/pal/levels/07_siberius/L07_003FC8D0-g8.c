#include "include_asm.h"

#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 g_unused_float_param __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 g_boss_cam_distance __attribute__((sda));
extern f32 g_boss_cam_height __attribute__((sda));
extern u32 g_boss_screen_color __attribute__((sda));
extern f32 g_bomb_scale __attribute__((sda));
extern f32 g_beam_fade_in_rate __attribute__((sda));
extern f32 g_beam_fade_out_rate __attribute__((sda));
extern f32 g_beam_spin_rate __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 g_hero_reset_offset_z;
extern u8 g_hero_l07_reset_position __attribute__((sda));
extern u8 *g_joint_record_table;
extern u8 *g_matrix_l07_record_table;
extern s32 g_ship_phase_state;
extern void follow_camera_set_distance(s32, f32, f32);
extern void follow_camera_set_height(f32, f32);
extern u8 *cam_alloc_override_slot_pal(s32);
typedef struct { f32 x, y; u8 pad08[0x2C]; u32 color; } Effect;
typedef struct { u8 pad[0x450]; Effect *effect; } EffectState;
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 g_aim_yaw_turn_accel __attribute__((sda));
extern f32 g_aim_yaw_max_turn_speed __attribute__((sda));
extern u8 *g_world_info __attribute__((nosda));
extern u8 *g_snowfall_target_moby MACRO_ADDR;
extern u8 g_aim_yaw_init_flag;
extern u8 g_hero_state[];
extern u32 g_frame_l07_counter MACRO_ADDR;
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern f32 g_bomb_scale __attribute__((sda));
extern u8 *g_hit_object_list[];

/* Sets up the screen effect of the boss. For one variant it also creates the effect record once and fills it in. */
void boss_setup_screen_effect_pal(u8 *moby)
{
    EffectState *vars = *(EffectState **)(moby + 0x68);

    follow_camera_set_distance(0, g_boss_cam_distance, 0.003f);
    follow_camera_set_height(g_boss_cam_height, 0.003f);
    if (*(u8 *)(moby + 0x95) != 0) {
        if (vars->effect == 0)
            vars->effect = (Effect *)cam_alloc_override_slot_pal(5);
        {
            f32 x = g_boss_cam_distance;
            f32 y = g_boss_cam_height;
            u32 z;
            vars->effect->x = x;
            z = g_boss_screen_color;
            vars->effect->y = y;
            vars->effect->color = z;
        }
    }
}
