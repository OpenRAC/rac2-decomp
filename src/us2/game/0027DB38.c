#include "include_asm.h"
#include "names.h"

extern int g_text_pulse_counter;
extern unsigned char g_display_mode_flag __attribute__((sda));
extern float math_fast_sin_or_cos_a(float);
extern int FastTweenColor(float, int, int);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

void text_draw_pulsing_us2(void)
{
    int y;
    long style;
    unsigned char *text;
    float f;
    int v;

    y = 0x148;
    if (g_display_mode_flag) {
        y = 0x17C;
    }
    v = g_text_pulse_counter;
    f = (float)(v % 100) * 0.02f - 1.0f;
    if (f < -1.0f) {
        f = -1.0f;
    }
    if (1.0f < f) {
        f = 1.0f;
    }
    f = math_fast_sin_or_cos_a(f * 3.14159274f);
    f = f + 1.0f;
    style = FastTweenColor(f * 0.5f, 0x7FE0E0E0, 0x5FF0C070);
    text = GetLocalizedString(0x2DB6);
    text_draw_medium(0x3C, y, style, text, -1);
}

