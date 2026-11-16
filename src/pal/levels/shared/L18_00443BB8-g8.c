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
void banner_update_pal(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    f32 phase;
    f32 rise;
    s32 a;
    s32 b;
    s32 period;
    s32 x;
    s32 y;
    f32 buf[4];

    if (obj[0x20] == 0) {
        *(f32 *)(state + 0x150) = math_random_angle();
        *(TI128 *)(state + 0x140) = *(TI128 *)(obj + 0x10);
        ribbon_init_emitters_pal(obj);
        moby_set_state(obj, 1, -1);
    }
    if (obj[0x31] != 0) {
        period = 50;
        phase = IntToFloat(g_frame_l18_counter % period);
        rise = IntToFloat(50);
        phase = phase * 6.2831855f;
        phase = phase / rise;
        phase = phase - 3.1415927f;
        rise = math_fast_sin_or_cos_a(phase);
        x = g_banner_x;
        y = g_banner_y;
        *(f32 *)(state + 0x158) = rise * 0.5f + 0.5f;
        a = PulseColor(x, y, phase);
        b = PulseColor(g_banner_pulse_color_a, g_banner_pulse_color_b, phase);
        FastVecSub(buf, g_camera_l18_position, obj + 0x10);
        vec_scale_to_length(buf, buf, 1.0f);
        rise = math_fabs(FastVecDot(buf, obj + 0xC0));
        rise = rise * rise;
        *(f32 *)(state + 0x15C) = rise;
        *(s32 *)(obj + 0x78) = math_lerp_int_fraction(b, a, rise);
        banner_pick_table_vectors_pal(obj);
        gfx_add_draw_callback_first(ribbon_draw_with_bursts, obj);
        gfx_add_draw_callback_first(probe_place_at_height, obj);
        gfx_add_draw_callback_first(part_emit_fade_burst, obj);
    }
    math_update_wrapped_angle_offset(obj, (f32 *)(state + 0x150), (f32 *)(state + 0x154), g_banner_angle_offset_base, g_banner_angle_speed_deg * 0.0003490659f, *(f32 *)(state + 0x148));
}
