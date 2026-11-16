#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
extern s32 g_frame_l18_counter __attribute__((sda));
extern s32 g_banner_x __attribute__((sda));
extern s32 g_banner_y __attribute__((sda));
extern s32 g_banner_pulse_color_a __attribute__((sda));
extern s32 g_banner_pulse_color_b __attribute__((sda));
extern f32 g_banner_angle_offset_base __attribute__((sda));
extern f32 g_banner_angle_speed_deg __attribute__((sda));
extern char g_camera_l18_position[];
extern f32 math_random_angle(void);
extern void ribbon_init_emitters_pal(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern f32 IntToFloat(s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern s32 PulseColor(s32, s32, f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 FastVecDot(void *, void *);
extern f32 math_fabs(f32);
extern s32 math_lerp_int_fraction(s32, s32, f32);
extern void banner_pick_table_vectors_pal(u8 *);
extern void gfx_add_draw_callback_first(void *, void *);
extern void ribbon_draw_with_bursts(u8 *);
extern void probe_place_at_height(u8 *);
extern void part_emit_fade_burst(u8 *);
extern void math_update_wrapped_angle_offset(u8 *, f32 *, f32 *, f32, f32, f32);

/* Starts the banner object: on its first frame seeds the phase and copies its position, then
   every frame while it is live turns the frame counter into a phase over 60 frames, eases the
   rise and the two path samples from it, and queues the three updaters; finally hands the
   state's two coordinates to the shared mover. */
void banner_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 phase;
    f32 rise;
    s32 color_a;
    s32 color_b;
    s32 period;
    s32 banner_x;
    s32 banner_y;
    f32 to_camera[4];

    if (moby[0x20] == 0) {
        *(f32 *)(vars + 0x150) = math_random_angle();
        *(TI128 *)(vars + 0x140) = *(TI128 *)(moby + 0x10);
        ribbon_init_emitters_pal(moby);
        moby_set_state(moby, 1, -1);
    }
    if (moby[0x31] != 0) {
        period = 50;
        phase = IntToFloat(g_frame_l18_counter % period);
        rise = IntToFloat(50);
        phase = phase * 6.2831855f;
        phase = phase / rise;
        phase = phase - 3.1415927f;
        rise = math_fast_sin_or_cos_a(phase);
        banner_x = g_banner_x;
        banner_y = g_banner_y;
        *(f32 *)(vars + 0x158) = rise * 0.5f + 0.5f;
        color_a = PulseColor(banner_x, banner_y, phase);
        color_b = PulseColor(g_banner_pulse_color_a, g_banner_pulse_color_b, phase);
        FastVecSub(to_camera, g_camera_l18_position, moby + 0x10);
        vec_scale_to_length(to_camera, to_camera, 1.0f);
        rise = math_fabs(FastVecDot(to_camera, moby + 0xC0));
        rise = rise * rise;
        *(f32 *)(vars + 0x15C) = rise;
        *(s32 *)(moby + 0x78) = math_lerp_int_fraction(color_b, color_a, rise);
        banner_pick_table_vectors_pal(moby);
        gfx_add_draw_callback_first(ribbon_draw_with_bursts, moby);
        gfx_add_draw_callback_first(probe_place_at_height, moby);
        gfx_add_draw_callback_first(part_emit_fade_burst, moby);
    }
    math_update_wrapped_angle_offset(moby, (f32 *)(vars + 0x150), (f32 *)(vars + 0x154), g_banner_angle_offset_base, g_banner_angle_speed_deg * 0.0003490659f, *(f32 *)(vars + 0x148));
}
