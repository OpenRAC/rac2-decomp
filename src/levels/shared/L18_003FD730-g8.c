#include "include_asm.h"
#include "common.h"

extern f32 g_train_l18_value_mid[] __attribute__((sda));
extern f32 g_burst_intensity_start __attribute__((sda));
extern f32 g_burst_intensity_end[] NOT_SDA;
extern s32 g_burst_particle_scale __attribute__((sda));
extern f32 g_burst_quad_size __attribute__((sda));

extern void gfx_set_gs_register_constant(void);
extern f32 math_lerp_float(f32, f32, f32);
extern s32 FloatToInt(f32);
extern void gfx_draw_billboard_quad_with_uv(void *, s32, s32, f32, f32, f32);

/* The func_L18_0043E9B0 pulse driven by a clamped ratio of the state's +0xC0 timer; the
   count and size go to the state's own emitter at +0x90. */
/* Fires a burst of effect particles whose number and size depend on a timer value. */
void part_emit_timer_burst(u8 *moby) {
    u8 *state;
    f32 ratio;
    f32 intensity;
    s32 particle_count;

    gfx_set_gs_register_constant();
    state = *(u8 **)(moby + 0x68);
    ratio = *(f32 *)(state + 0xC0) / g_train_l18_value_mid[0];
    if (ratio > 1.0f)
        ratio = 1.0f;
    else if (ratio < 0.0f)
        ratio = 0.0f;
    intensity = math_lerp_float(g_burst_intensity_start, g_burst_intensity_end[0], ratio);
    if (ratio < 0.1f) {
        particle_count = FloatToInt((f32)g_burst_particle_scale * ratio * 10.0f);
    } else {
        particle_count = FloatToInt((f32)g_burst_particle_scale * (1.0f - ratio));
    }
    gfx_draw_billboard_quad_with_uv(state + 0x90, particle_count, 0, intensity, g_burst_quad_size, 0.08f);
}
