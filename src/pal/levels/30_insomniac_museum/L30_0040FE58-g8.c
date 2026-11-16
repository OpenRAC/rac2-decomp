#include "include_asm.h"

#include "common.h"
extern unsigned char g_gauge_mode_base __attribute__((sda));
extern unsigned char g_gauge_mode_flag_a __attribute__((sda));
extern unsigned char g_gauge_mode_flag_b __attribute__((sda));
extern unsigned char g_gauge_mode_flag_c __attribute__((sda));
extern unsigned char g_gauge_mode_high_byte __attribute__((sda));
extern unsigned char g_gauge_flags_base __attribute__((sda));
extern unsigned char g_gauge_flag_a __attribute__((sda));
extern unsigned char g_gauge_flag_b __attribute__((sda));
extern unsigned char g_gauge_flag_c __attribute__((sda));
extern unsigned char g_gauge_flag_d __attribute__((sda));
extern unsigned char g_gauge_flag_e __attribute__((sda));
extern unsigned char g_gauge_flag_f __attribute__((sda));
extern unsigned char g_gauge_flags_high_bits __attribute__((sda));
extern int g_effect_texture_size_arg __attribute__((sda));
extern int g_effect_texture_base_a __attribute__((sda));
extern int g_effect_texture_base_b __attribute__((sda));
extern int g_effect_texture_base_c __attribute__((sda));
extern int g_effect_texture_offset __attribute__((sda));
extern int g_effect_texture_offset_alt __attribute__((sda));
extern float g_gauge_angle_scale __attribute__((sda));
extern float g_gauge_angle_rate __attribute__((sda));
extern float g_gauge_delta_scale __attribute__((sda));
extern float g_gauge_angle_offset_scale __attribute__((sda));
extern float g_gauge_l30_screen_x __attribute__((sda));
extern float g_vehicle_turn_speed __attribute__((sda));
extern unsigned char g_gauge_palette_ptr[4] __attribute__((sda));
extern int g_low_health_blink_timer __attribute__((sda));
typedef struct {
    char pad[0x183C];
    float current;
    float maximum;
} GaugeState;
extern GaugeState g_hero_state;
extern int g_screen_height;
extern unsigned g_palette_copy[];
extern void gfx_append_vectors_to_packet(int, int, unsigned long, int, unsigned long);
extern unsigned long GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern float FastVecLength(void *), math_fabs(float), FastAddRotations(float, float);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long, unsigned long);
extern void AppendRotatedSpriteQuad(float, float, float, float, float,
                              int, int, unsigned long, int, int, int, int, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long, int, int);
static __inline__ unsigned long PackGaugeFlag(unsigned long flags,
                                              unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* Draws the museum status gauge and updates its swizzled palette (PAL version). */
void DrawMuseumStatusGauge_pal(char *obj) {
    char *state = *(char **)(obj + 0x68);
    unsigned long texture;
    float scale = 0.017453294f, delta, absdelta, angle;
    int fill, lo, hi, i, palette_index;

    unsigned long flags, mode;
    flags = g_gauge_flags_base;
    flags = PackGaugeFlag(flags, g_gauge_flag_a, 1);
    flags = PackGaugeFlag(flags, g_gauge_flag_b, 4);
    flags = PackGaugeFlag(flags, g_gauge_flag_c, 12);
    flags = PackGaugeFlag(flags, g_gauge_flag_d, 14);
    flags = PackGaugeFlag(flags, g_gauge_flag_e, 15);
    mode = g_gauge_mode_base;
    mode = PackGaugeFlag(mode, g_gauge_mode_flag_a, 2);
    flags = PackGaugeFlag(flags, g_gauge_flag_f, 16);
    mode = PackGaugeFlag(mode, g_gauge_mode_flag_b, 4);
    mode = PackGaugeFlag(mode, g_gauge_mode_flag_c, 6);
    gfx_append_vectors_to_packet(2, 0x47, flags | ((unsigned long)g_gauge_flags_high_bits << 17),
            0x42, mode | ((unsigned long)g_gauge_mode_high_byte << 32));
    texture = GetEffectTextureDescriptor(g_effect_texture_base_a + *(int *)(state + 0x64));
    DrawTexturedQuad(FloatToInt(g_gauge_l30_screen_x), g_screen_height - 80,
           64, 64, 0, 0, 64, 64, g_effect_texture_size_arg, texture);
    texture = GetEffectTextureDescriptor(g_effect_texture_base_b + *(int *)(state + 0x64));
    DrawTexturedQuad(FloatToInt(g_gauge_l30_screen_x) + 64, g_screen_height - 80,
           64, 64, 0, 0, 64, 64, g_effect_texture_size_arg, texture);
    texture = GetEffectTextureDescriptor(g_effect_texture_base_c + *(int *)(state + 0x64));
    angle = g_gauge_angle_scale * (FastVecLength(state) * scale);
    angle /= g_vehicle_turn_speed * 0.020000001f;
    angle = FastAddRotations(angle, g_gauge_angle_rate * scale);
    AppendRotatedSpriteQuad(g_gauge_l30_screen_x + 32.0f, (float)(g_screen_height - 48),
           32.0f, 32.0f, angle, 32, 32, texture, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    absdelta = g_gauge_delta_scale * (math_fabs(*(float *)(state + 0x5C)) * scale);
    angle = FastAddRotations(g_gauge_angle_offset_scale * scale, absdelta);
    AppendRotatedSpriteQuad(g_gauge_l30_screen_x + 64.0f + 32.0f, (float)(g_screen_height - 48),
           32.0f, 32.0f, angle, 32, 32, texture, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    delta = g_hero_state.current - *(float *)(state + 0x94);
    delta *= 0.2f;
    absdelta = math_fabs(delta);
    if (absdelta > 1.0f) {
        delta /= absdelta;
    }
    *(float *)(state + 0x94) += delta;
    fill = FloatToInt(*(float *)(state + 0x94) * 251.0f / g_hero_state.maximum) + 2;
    if (fill > 253) {
        fill = 253;
    }
    if (fill < 2) {
        fill = 2;
    }
    lo = *(int *)(state + 0x98) <= fill ? *(int *)(state + 0x98) : fill;
    hi = *(int *)(state + 0x98) < fill ? fill : *(int *)(state + 0x98);
    for (i = lo; i <= hi; i++) {
        palette_index = (i & 0xE7) | ((i & 16) >> 1) | ((i & 8) << 1);
        if (i < fill) {
            (*(unsigned **)&g_gauge_palette_ptr)[palette_index] = g_palette_copy[palette_index];
        } else {
            (*(unsigned **)&g_gauge_palette_ptr)[palette_index] = 0x80000000;
        }
    }
    texture = GetEffectTextureDescriptor(*(int *)(state + 0x64) + g_effect_texture_offset);
    DrawTexturedQuad(368, g_screen_height - 144, 128, 128, 0, 0, 128, 128, 0x70808080, texture);
    texture = GetEffectTextureDescriptor(*(int *)(state + 0x64) + g_effect_texture_offset_alt);
    DrawTexturedQuad(368, g_screen_height - 144, 128, 128, 0, 0, 128, 128, 0x70808080, texture);
    *(int *)(state + 0x98) = fill;
    if (g_hero_state.current < g_hero_state.maximum * 0.1f && ((g_low_health_blink_timer / 90) & 1)) {
        text_draw_centered_medium(256, 370, 0x80000080, GetLocalizedString(0x1149), 100);
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
