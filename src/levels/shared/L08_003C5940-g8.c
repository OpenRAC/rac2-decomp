#include "common.h"

typedef struct {
    float position[4];
    u8 pad10[0x5C - 0x10];
    float speed;
    u8 pad60[4];
    int texture;
    float limit;
    int active;
    u8 pad70[0x78 - 0x70];
    float shake;
    u8 pad7C[0x88 - 0x7C];
    s16 hitTimer;
    u8 hitCount;
    u8 pad8B;
    s16 extra;
    s16 message;
    u8 pad90[0xA4 - 0x90];
    float shown;
    int segments;
} Hud;
extern u8 g_gauge_alpha_base __attribute__((sda)), g_gauge_alpha_flag_a __attribute__((sda)), g_gauge_alpha_flag_b __attribute__((sda));
extern u8 g_gauge_alpha_flag_c __attribute__((sda)), g_gauge_alpha_high __attribute__((sda)), g_gauge_test_base __attribute__((sda));
extern u8 g_gauge_test_flag_a __attribute__((sda)), g_gauge_test_flag_b __attribute__((sda)), g_gauge_test_flag_c __attribute__((sda));
extern u8 g_gauge_test_flag_d __attribute__((sda)), g_gauge_test_flag_e __attribute__((sda)), g_gauge_test_flag_f __attribute__((sda));
extern u8 g_gauge_prim_flag __attribute__((sda));
extern int g_current_map_index, g_screen_height;
extern int g_pad_pressed_flags[];
extern int g_gauge_quad_color __attribute__((sda)), g_gauge_tex_base_a __attribute__((sda)), g_gauge_tex_base_b __attribute__((sda));
extern int g_gauge_tex_base_c __attribute__((sda)), g_gauge_tex_base_d __attribute__((sda)), g_gauge_tex_base_e __attribute__((sda));
extern int g_gauge_tex_base_f __attribute__((sda)), g_gauge_tex_base_g __attribute__((sda)), g_gauge_tex_base_h __attribute__((sda));
extern int g_gauge_tex_base_i __attribute__((sda));
extern int g_gauge_message_duration __attribute__((sda)), g_hover_frame_limit __attribute__((sda));
extern int g_frame_l08_counter;
extern int g_gauge_color_table[] MACRO_ADDR;
extern float g_hover_cruise_speed __attribute__((sda)), g_gauge_distance_scale __attribute__((sda)), g_gauge_angle_offset_deg __attribute__((sda));
extern float g_gauge_rate_scale __attribute__((sda)), g_gauge_angle_base_deg __attribute__((sda)), g_gauge_l08_screen_x __attribute__((sda));
extern float g_gauge_base_offset __attribute__((sda)), g_gauge_screen_y __attribute__((sda)), g_hud_l08_bar_threshold __attribute__((sda));
/* Palette pointer storage, accessed through its word-pointer view as in RAC1 HUDs. */
extern unsigned char g_color_row_ptr[4] __attribute__((sda));
extern unsigned g_hud_gauge_values[];
extern char g_str_gauge_limit_format[];
typedef struct { char pad[0x183C]; float health, maxHealth; } HudHero;
extern HudHero g_hero_state;
extern int sprintf(char *, const char *, ...);
extern double __extendsfdf2(float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern void AppendRotatedSpriteQuad(float, float, float, float, float, int, int, u64, unsigned, unsigned, int, int, float, float);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern int text_draw_centered_large(int, int, u64, u8 *, int);
extern int FastDecTimer(void *);
extern float math_fabs(float);
extern float FastVecLength(void *);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern char *GetLocalizedString(int);
extern float math_square(float), math_ease_out_quad(float);
extern float math_wrap_angle_to_pi(float);
extern void AppendSubpixelTexturedScreenQuad(float, float, float, float, int, int, int, int, unsigned long, unsigned long);
extern void DrawCenteredScaledText(int, int, u64, u8 *, int, float);
extern float IntegerPower(int, float);
extern void gfx_append_vectors_to_packet(int, int, unsigned long, int, unsigned long);

static __inline__ unsigned long PackGaugeFlag(unsigned long flags, unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* Draws the status gauge and updates its swizzled palette. */
void hud_draw_health_gauge(char *object)
{
    char text[16];
    Hud *state = *(Hud **)(object + 0x68);
    unsigned long test, alpha;
    unsigned long tex;
    float delta, angle;
    int fade;
    int level, low, high, i;
    test = g_gauge_test_base;
    test = PackGaugeFlag(test, g_gauge_test_flag_a, 1);
    test = PackGaugeFlag(test, g_gauge_test_flag_b, 4);
    test = PackGaugeFlag(test, g_gauge_test_flag_c, 12);
    test = PackGaugeFlag(test, g_gauge_test_flag_d, 14);
    test = PackGaugeFlag(test, g_gauge_test_flag_e, 15);
    alpha = g_gauge_alpha_base;
    alpha = PackGaugeFlag(alpha, g_gauge_alpha_flag_a, 2);
    test = PackGaugeFlag(test, g_gauge_test_flag_f, 16);
    alpha = PackGaugeFlag(alpha, g_gauge_alpha_flag_b, 4);
    alpha = PackGaugeFlag(alpha, g_gauge_alpha_flag_c, 6);
    gfx_append_vectors_to_packet(2, 0x47, test | ((unsigned long)g_gauge_prim_flag << 17),
        0x42, alpha | ((unsigned long)g_gauge_alpha_high << 32));
    FastDecTimer(&state->message);
    if (g_current_map_index == 8) {
        if (state->message != 0) {
            float t, scale, alpha;
            char *msg;
            t = IntToFloat(g_gauge_message_duration - state->message);
            t /= IntToFloat(g_gauge_message_duration);
            scale = math_ease_out_quad(t) * 2.0f + 0.5f;
            alpha = IntegerPower(3, 1.0f - t) * 127.0f;
            fade = FloatToInt(alpha * 0.5f) << 24;
            msg = GetLocalizedString(0x2F59);
            DrawCenteredScaledText(0x100, 0x20, fade | 0x80, (u8 *)msg, 0x11, scale * 0.96f);
            fade = FloatToInt(alpha * 0.75f) << 24;
            DrawCenteredScaledText(0x100, 0x20, fade | 0x60, (u8 *)msg, 0x11, scale * 0.98f);
            fade = FloatToInt(alpha) << 24;
            DrawCenteredScaledText(0x100, 0x20, fade | 0x40, (u8 *)msg, 0x11, scale);
        } else if (state->active != 0) {
            if (state->limit > g_hud_l08_bar_threshold) {
                text_draw_centered_medium(0x100, 0x18, 0x80008000, GetLocalizedString(0x2F55), 10);
                sprintf(text, g_str_gauge_limit_format, __extendsfdf2(state->limit));
                text_draw_centered_large(0x100, 0x28, 0x80008000, (u8 *)text, 3);
                text_draw_centered_medium(0x100, 0x38, 0x80008000, GetLocalizedString(0x2F56), 6);
            } else if (g_pad_pressed_flags[0] & 4) {
                DrawCenteredScaledText(0x100, 0x20, 0x80802020, (u8 *)GetLocalizedString(0x2F57), 13, 1.4f);
            } else {
                float pulse = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter) * 0.1f)) * 0.1f + 1.2f;
                DrawCenteredScaledText(0x100, 0x20, 0x80202080, (u8 *)GetLocalizedString(0x2F58), 0x11, pulse);
            }
        }
        if (state->hitCount != 0) {
            int *colors = g_gauge_color_table;
            int offset = 0x40;
            int i = 6;
            float size, x, y;
            int color;
            float t, base, a, b, angleA, angleB;
            t = IntToFloat(state->hitTimer);
            t /= IntToFloat(g_hover_frame_limit);
            size = math_square(t) * 32.0f;
            base = g_gauge_base_offset * math_ease_out_quad(t);
            fade = FloatToInt(t * 128.0f) << 24;
            y = 16.0f - size * 0.5f;
            x = base - size * 0.5f;
            angleA = math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter) * 0.025f);
            angleB = math_wrap_angle_to_pi(IntToFloat(g_frame_l08_counter) * 0.033333335f);
            a = math_fast_sin_or_cos_b(angleA) * 2.0f * state->shake;
            b = math_fast_sin_or_cos_a(angleB) * 2.0f * state->shake;
            tex = GetEffectTextureDescriptor(g_gauge_tex_base_d + state->texture);
            color = fade | 0x808080;
            AppendSubpixelTexturedScreenQuad(x + a, g_gauge_screen_y + b + (1.0f - state->shake) * 4.0f + y, size, size, 0, 0, 0x20, 0x20, color, tex);
            tex = GetEffectTextureDescriptor(g_gauge_tex_base_f + state->texture);
            AppendSubpixelTexturedScreenQuad(x, g_gauge_screen_y + 32.0f, size, 32.0f, 0, 0, 0x20, 0x20, color, tex);
            tex = GetEffectTextureDescriptor(g_gauge_tex_base_g + state->texture);
            do {
                float z = IntToFloat(offset);
                i--;
                offset += 0x20;
                AppendSubpixelTexturedScreenQuad(x, g_gauge_screen_y + z, size, 32.0f, 0, 0, 0x20, 0x20, *colors | fade, tex);
                colors++;
            } while (i >= 0);
            if (state->hitCount < 3) {
                tex = GetEffectTextureDescriptor(g_gauge_tex_base_e + state->texture);
                AppendSubpixelTexturedScreenQuad(x, g_gauge_screen_y + (float)state->extra + 32.0f + y, size, size, 0, 0, 0x20, 0x20, fade | 0x808080, tex);
            }
        }
    }
    tex = GetEffectTextureDescriptor(g_gauge_tex_base_a + state->texture);
    DrawTexturedQuad(FloatToInt(g_gauge_l08_screen_x), g_screen_height - 0x50, 0x40, 0x40, 0, 0, 0x40, 0x40, g_gauge_quad_color, tex);
    tex = GetEffectTextureDescriptor(g_gauge_tex_base_b + state->texture);
    DrawTexturedQuad(FloatToInt(g_gauge_l08_screen_x) + 0x40, g_screen_height - 0x50, 0x40, 0x40, 0, 0, 0x40, 0x40, g_gauge_quad_color, tex);
    tex = GetEffectTextureDescriptor(g_gauge_tex_base_c + state->texture);
    {
        float distance = g_gauge_distance_scale * (FastVecLength(state) * 0.017453294f);
        float frame = g_hover_cruise_speed * 0.016666668f;
        angle = FastAddRotations(distance / frame, g_gauge_angle_offset_deg * 0.017453294f);
    }
    AppendRotatedSpriteQuad(g_gauge_l08_screen_x + 32.0f, (float)(g_screen_height - 0x30), 32.0f, 32.0f, angle, 0x20, 0x20, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    {
        float rate = math_fabs(state->speed) * 0.017453294f;
        float scaled = g_gauge_rate_scale * rate;
        angle = FastAddRotations(g_gauge_angle_base_deg * 0.017453294f, scaled);
    }
    AppendRotatedSpriteQuad(g_gauge_l08_screen_x + 64.0f + 32.0f, (float)(g_screen_height - 0x30), 32.0f, 32.0f, angle, 0x20, 0x20, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    delta = g_hero_state.health - state->shown;
    delta *= 0.2f;
    {
        float d = math_fabs(delta);
        if (d > 1.0f)
            delta /= d;
    }
    state->shown += delta;
    level = FloatToInt(state->shown * 251.0f / g_hero_state.maxHealth) + 2;
    if (level > 0xFD)
        level = 0xFD;
    if (level < 2)
        level = 2;
    low = state->segments <= level ? state->segments : level;
    high = state->segments < level ? level : state->segments;
    for (i = low; i <= high; i++) {
        int index = (i & 0xE7) | ((i & 0x10) >> 1) | ((i & 8) << 1);
        if (i < level) {
            (*(unsigned **)&g_color_row_ptr)[index] = g_hud_gauge_values[index];
        } else {
            (*(unsigned **)&g_color_row_ptr)[index] = 0x80000000;
        }
    }
    tex = GetEffectTextureDescriptor(state->texture + g_gauge_tex_base_h);
    DrawTexturedQuad(0x170, g_screen_height - 0x90, 0x80, 0x80, 0, 0, 0x80, 0x80, 0x70808080, tex);
    tex = GetEffectTextureDescriptor(state->texture + g_gauge_tex_base_i);
    DrawTexturedQuad(0x170, g_screen_height - 0x90, 0x80, 0x80, 0, 0, 0x80, 0x80, 0x70808080, tex);
    state->segments = level;
    if (g_hero_state.health < g_hero_state.maxHealth * 0.1f) {
        if ((g_frame_l08_counter / 90) & 1)
            text_draw_centered_medium(0x100, 0x172, 0x80000080, GetLocalizedString(0x1149), 100);
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}
