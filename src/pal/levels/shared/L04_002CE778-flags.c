#include "include_asm.h"

#include "common.h"
extern float g_water_tile_half_x MACRO_ADDR, g_water_tile_half_y MACRO_ADDR;
extern unsigned char g_contact_hit_flag MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern u32 FastDecTimer(u8 *);
extern int FloatToInt(float);
extern float FastVecDot(void *, void *);
extern int g_hero_height_zone_active MACRO_ADDR;
extern float g_hero_airborne_speed_limit MACRO_ADDR;
extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 g_hero_state;
extern void math_update_wrapped_angle_offset(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
extern s32 FloatToInt(f32 value);
extern s32 math_random_int_below(s32 limit);
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;
extern s32 GetFirstMobyInGroup(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u32 *out, u32 value, s32 arg2, s32 arg3);
extern f32 FastVecDot(void *a, void *b);
extern f32 square_root(f32 x);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern s32 func_001163B0(void);
extern u8 *ref_L04_00358868_00[];
extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern f32 g_water_texture_coords[];
extern f32 g_water_base_texture_coords[];
extern s32 g_water_scroll_flags[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);
extern u32 FastDecTimer(u8 *ptr);
extern f32 g_particle_speeds[];
extern f32 g_particle_sizes[];
extern f32 g_particle_uv_offsets[];
extern f32 g_particle_life_rates[];
extern u8 g_particle_sprite_flags[];
extern u16 g_particle_fade_in_timers[];
extern u16 g_particle_fade_out_timers[];
extern u16 g_particle_delay_timers[];
#define MACRO_ADDR __attribute__((section(".sdata")))
extern s32 g_particle_life_step MACRO_ADDR;
extern u16 g_particle_life_reload MACRO_ADDR;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern f32 g_particle_speeds[];
extern f32 g_particle_sizes[];
extern f32 g_particle_uv_offsets[];
extern f32 g_particle_life_rates[];
extern u8 g_particle_sprite_flags[];
extern u16 g_particle_fade_in_timers[];
extern u16 g_particle_fade_out_timers[];
extern u16 g_particle_delay_timers[];
extern s32 g_particle_life_step;
extern u16 g_particle_life_reload;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern u32 g_running_total __attribute__((sda));

void hero_start_turn_sway_anim_pal(void) {
    if (g_hero_state.field2294 != 0x7C)
        return;
    math_update_wrapped_angle_offset(g_hero_state.field2290, &g_hero_state.field7A8, &g_hero_state.field7AC,
                  0.3f, 0.13962635f, -1.0f);
}

extern void moby_scale_owner_words_by_angles(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);

void hero_start_second_sway_anim_pal(void) {
    if (g_hero_state.field2294 != 0x7C)
        return;
    moby_scale_owner_words_by_angles(g_hero_state.field2290, &g_hero_state.field7B0, &g_hero_state.field7B4,
                  0.174532949924469f, 0.031415932f, 0.04188791f);
}
