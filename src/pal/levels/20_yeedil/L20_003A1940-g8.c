#include "include_asm.h"
#include "names.h"

typedef float f32;
extern void moby_mark_spawned(char *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(float, int, int);
extern float IntToFloat(int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void electric_orb_draw_pal(char *);
extern int g_electric_orb_spin_rate __attribute__((sda));
extern int g_electric_orb_color_a __attribute__((sda));
extern int g_electric_orb_color_b;
extern int g_electric_orb_color_c;
extern int g_electric_orb_color_d;

/* Per-frame update of the electric orb: pulses its colour and queues its draw, or removes it when its timer ends. */
void electric_orb_update_pal(char *orb) {
    char *state = *(char **)(orb + 0x68);

    if (math_fast_float_d(state) != 0) {
        moby_mark_spawned(orb);
    } else {
        f32 phase_old = *(f32 *)(state + 0x8);
        f32 phase, wave;
        int color, blended, rgb, alpha_bits;

        if (*(int *)(state + 0xC) != 0) {
            phase = FastAddRotations(phase_old, (f32)g_electric_orb_spin_rate * 0.0003490659f);
            *(f32 *)(state + 0x8) = phase;
            wave = math_fast_sin_or_cos_b(phase);
            color = FastTweenColor(wave * 0.5f + 0.5f, g_electric_orb_color_a, g_electric_orb_color_b);
        } else {
            phase = FastAddRotations(phase_old, (f32)g_electric_orb_spin_rate * 0.0003490659f);
            *(f32 *)(state + 0x8) = phase;
            wave = math_fast_sin_or_cos_b(phase);
            color = FastTweenColor(wave * wave * 0.5f + 0.5f, g_electric_orb_color_c, g_electric_orb_color_d);
        }
        blended = FastTweenColor(0.15f, *(int *)(state + 0x10) | *(int *)(state + 0x4), color);
        rgb = blended & 0xFFFFFF;
        alpha_bits = blended & 0xFF000000;
        *(int *)(state + 0x10) = alpha_bits;
        *(int *)(state + 0x4) = rgb;
        *(f32 *)(state + 0x14) = IntToFloat(alpha_bits >> 24) * 0.00390625f;
        gfx_add_draw_callback_first(electric_orb_draw_pal, orb);
    }
}
