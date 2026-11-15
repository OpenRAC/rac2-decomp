/* func_US2_L30_003B4E94, the USA v2.00 copy of func_L08_003C5940: the same C, where rename func_0027C878 becomes func_US2_0027CED8. */
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
extern u8 D_L08_001AFAE0 __attribute__((sda)), D_L08_001AFAE1 __attribute__((sda)), D_L08_001AFAE2 __attribute__((sda));
extern u8 D_L08_001AFAE3 __attribute__((sda)), D_L08_001AFAE4 __attribute__((sda)), D_L08_001AFAE5 __attribute__((sda));
extern u8 D_L08_001AFAE6 __attribute__((sda)), D_L08_001AFAE7 __attribute__((sda)), D_L08_001AFAE8 __attribute__((sda));
extern u8 D_L08_001AFAE9 __attribute__((sda)), D_L08_001AFAEA __attribute__((sda)), D_L08_001AFAEB __attribute__((sda));
extern u8 D_L08_001AFAEC __attribute__((sda));
extern int g_current_map_index, g_screen_height;
extern int D_00138320[];
extern int D_L08_001AFA30 __attribute__((sda)), D_L08_001AFA34 __attribute__((sda)), D_L08_001AFA38 __attribute__((sda));
extern int D_L08_001AFA3C __attribute__((sda)), D_L08_001AFA40 __attribute__((sda)), D_L08_001AFA44 __attribute__((sda));
extern int D_L08_001AFA48 __attribute__((sda)), D_L08_001AFA4C __attribute__((sda)), D_L08_001AFA50 __attribute__((sda));
extern int D_L08_001AFA54 __attribute__((sda));
extern int D_L08_001AFAD0 __attribute__((sda)), D_L08_001AFB14 __attribute__((sda));
extern int D_L08_001B2508;
extern int D_L08_001AFAF4[] MACRO_ADDR;
extern float D_L08_001AF9C4 __attribute__((sda)), D_L08_001AFA58 __attribute__((sda)), D_L08_001AFA5C __attribute__((sda));
extern float D_L08_001AFA60 __attribute__((sda)), D_L08_001AFA64 __attribute__((sda)), D_L08_001AFA68 __attribute__((sda));
extern float D_L08_001AFB1C __attribute__((sda)), D_L08_001AFB20 __attribute__((sda)), D_L08_001B031C __attribute__((sda));
/* Palette pointer storage, accessed through its word-pointer view as in RAC1 HUDs. */
extern unsigned char D_L08_001AFAD8[4] __attribute__((sda));
extern unsigned D_L08_0023E6A0[];
extern char D_L08_001AFB28[];
typedef struct { char pad[0x183C]; float health, maxHealth; } HudHero;
extern HudHero g_hero_state;
extern int sprintf(char *, const char *, ...);
extern double __extendsfdf2(float);
extern unsigned long func_US2_0027CED8(int);
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
void func_US2_L30_003B4E94(char *object)
{
    char text[16];
    Hud *state = *(Hud **)(object + 0x68);
    unsigned long test, alpha;
    unsigned long tex;
    float delta, angle;
    int fade;
    int level, low, high, i;
    test = D_L08_001AFAE5;
    test = PackGaugeFlag(test, D_L08_001AFAE6, 1);
    test = PackGaugeFlag(test, D_L08_001AFAE7, 4);
    test = PackGaugeFlag(test, D_L08_001AFAE8, 12);
    test = PackGaugeFlag(test, D_L08_001AFAE9, 14);
    test = PackGaugeFlag(test, D_L08_001AFAEA, 15);
    alpha = D_L08_001AFAE0;
    alpha = PackGaugeFlag(alpha, D_L08_001AFAE1, 2);
    test = PackGaugeFlag(test, D_L08_001AFAEB, 16);
    alpha = PackGaugeFlag(alpha, D_L08_001AFAE2, 4);
    alpha = PackGaugeFlag(alpha, D_L08_001AFAE3, 6);
    gfx_append_vectors_to_packet(2, 0x47, test | ((unsigned long)D_L08_001AFAEC << 17),
        0x42, alpha | ((unsigned long)D_L08_001AFAE4 << 32));
    FastDecTimer(&state->message);
    if (g_current_map_index == 8) {
        if (state->message != 0) {
            float t, scale, alpha;
            char *msg;
            t = IntToFloat(D_L08_001AFAD0 - state->message);
            t /= IntToFloat(D_L08_001AFAD0);
            scale = math_ease_out_quad(t) * 2.0f + 0.5f;
            alpha = IntegerPower(3, 1.0f - t) * 127.0f;
            fade = FloatToInt(alpha * 0.5f) << 24;
            msg = GetLocalizedString(0x2def);
            DrawCenteredScaledText(0x100, 0x20, fade | 0x80, (u8 *)msg, 0x11, scale * 0.96f);
            fade = FloatToInt(alpha * 0.75f) << 24;
            DrawCenteredScaledText(0x100, 0x20, fade | 0x60, (u8 *)msg, 0x11, scale * 0.98f);
            fade = FloatToInt(alpha) << 24;
            DrawCenteredScaledText(0x100, 0x20, fade | 0x40, (u8 *)msg, 0x11, scale);
        } else if (state->active != 0) {
            if (state->limit > D_L08_001B031C) {
                text_draw_centered_medium(0x100, 0x18, 0x80008000, GetLocalizedString(0x2deb), 10);
                sprintf(text, D_L08_001AFB28, __extendsfdf2(state->limit));
                text_draw_centered_large(0x100, 0x28, 0x80008000, (u8 *)text, 3);
                text_draw_centered_medium(0x100, 0x38, 0x80008000, GetLocalizedString(0x2dec), 6);
            } else if (D_00138320[0] & 4) {
                DrawCenteredScaledText(0x100, 0x20, 0x80802020, (u8 *)GetLocalizedString(0x2ded), 13, 1.4f);
            } else {
                float pulse = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508) * 0.1f)) * 0.1f + 1.2f;
                DrawCenteredScaledText(0x100, 0x20, 0x80202080, (u8 *)GetLocalizedString(0x2dee), 0x11, pulse);
            }
        }
        if (state->hitCount != 0) {
            int *colors = D_L08_001AFAF4;
            int offset = 0x40;
            int i = 6;
            float size, x, y;
            int color;
            float t, base, a, b, angleA, angleB;
            t = IntToFloat(state->hitTimer);
            t /= IntToFloat(D_L08_001AFB14);
            size = math_square(t) * 32.0f;
            base = D_L08_001AFB1C * math_ease_out_quad(t);
            fade = FloatToInt(t * 128.0f) << 24;
            y = 16.0f - size * 0.5f;
            x = base - size * 0.5f;
            angleA = math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508) * 0.025f);
            angleB = math_wrap_angle_to_pi(IntToFloat(D_L08_001B2508) * 0.033333335f);
            a = math_fast_sin_or_cos_b(angleA) * 2.0f * state->shake;
            b = math_fast_sin_or_cos_a(angleB) * 2.0f * state->shake;
            tex = func_US2_0027CED8(D_L08_001AFA40 + state->texture);
            color = fade | 0x808080;
            AppendSubpixelTexturedScreenQuad(x + a, D_L08_001AFB20 + b + (1.0f - state->shake) * 4.0f + y, size, size, 0, 0, 0x20, 0x20, color, tex);
            tex = func_US2_0027CED8(D_L08_001AFA48 + state->texture);
            AppendSubpixelTexturedScreenQuad(x, D_L08_001AFB20 + 32.0f, size, 32.0f, 0, 0, 0x20, 0x20, color, tex);
            tex = func_US2_0027CED8(D_L08_001AFA4C + state->texture);
            do {
                float z = IntToFloat(offset);
                i--;
                offset += 0x20;
                AppendSubpixelTexturedScreenQuad(x, D_L08_001AFB20 + z, size, 32.0f, 0, 0, 0x20, 0x20, *colors | fade, tex);
                colors++;
            } while (i >= 0);
            if (state->hitCount < 3) {
                tex = func_US2_0027CED8(D_L08_001AFA44 + state->texture);
                AppendSubpixelTexturedScreenQuad(x, D_L08_001AFB20 + (float)state->extra + 32.0f + y, size, size, 0, 0, 0x20, 0x20, fade | 0x808080, tex);
            }
        }
    }
    tex = func_US2_0027CED8(D_L08_001AFA34 + state->texture);
    DrawTexturedQuad(FloatToInt(D_L08_001AFA68), g_screen_height - 0x50, 0x40, 0x40, 0, 0, 0x40, 0x40, D_L08_001AFA30, tex);
    tex = func_US2_0027CED8(D_L08_001AFA38 + state->texture);
    DrawTexturedQuad(FloatToInt(D_L08_001AFA68) + 0x40, g_screen_height - 0x50, 0x40, 0x40, 0, 0, 0x40, 0x40, D_L08_001AFA30, tex);
    tex = func_US2_0027CED8(D_L08_001AFA3C + state->texture);
    {
        float distance = D_L08_001AFA58 * (FastVecLength(state) * 0.017453294f);
        float frame = D_L08_001AF9C4 * 0.016666668f;
        angle = FastAddRotations(distance / frame, D_L08_001AFA5C * 0.017453294f);
    }
    AppendRotatedSpriteQuad(D_L08_001AFA68 + 32.0f, (float)(g_screen_height - 0x30), 32.0f, 32.0f, angle, 0x20, 0x20, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    {
        float rate = math_fabs(state->speed) * 0.017453294f;
        float scaled = D_L08_001AFA60 * rate;
        angle = FastAddRotations(D_L08_001AFA64 * 0.017453294f, scaled);
    }
    AppendRotatedSpriteQuad(D_L08_001AFA68 + 64.0f + 32.0f, (float)(g_screen_height - 0x30), 32.0f, 32.0f, angle, 0x20, 0x20, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
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
            (*(unsigned **)&D_L08_001AFAD8)[index] = D_L08_0023E6A0[index];
        } else {
            (*(unsigned **)&D_L08_001AFAD8)[index] = 0x80000000;
        }
    }
    tex = func_US2_0027CED8(state->texture + D_L08_001AFA50);
    DrawTexturedQuad(0x170, g_screen_height - 0x90, 0x80, 0x80, 0, 0, 0x80, 0x80, 0x70808080, tex);
    tex = func_US2_0027CED8(state->texture + D_L08_001AFA54);
    DrawTexturedQuad(0x170, g_screen_height - 0x90, 0x80, 0x80, 0, 0, 0x80, 0x80, 0x70808080, tex);
    state->segments = level;
    if (g_hero_state.health < g_hero_state.maxHealth * 0.1f) {
        if ((D_L08_001B2508 / 90) & 1)
            text_draw_centered_medium(0x100, 0x172, 0x80000080, GetLocalizedString(0x31d5), 100);
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044ULL);
}
