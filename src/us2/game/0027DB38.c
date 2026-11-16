#include "include_asm.h"
#include "names.h"

extern int g_text_pulse_counter;
extern unsigned char g_display_mode_flag __attribute__((sda));
extern float math_fast_sin_or_cos_a(float);
extern int FastTweenColor(float, int, int);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, long, unsigned char *, int);

/* Draws a line of text that slowly changes colour back and forth. */
void text_draw_pulsing_us2(void)
{
    int y;
    long style;
    unsigned char *text;
    float pulse;
    int counter;

    y = 0x148;
    if (g_display_mode_flag) {
        y = 0x17C;
    }
    counter = g_text_pulse_counter;
    pulse = (float)(counter % 100) * 0.02f - 1.0f;
    if (pulse < -1.0f) {
        pulse = -1.0f;
    }
    if (1.0f < pulse) {
        pulse = 1.0f;
    }
    pulse = math_fast_sin_or_cos_a(pulse * 3.14159274f);
    pulse = pulse + 1.0f;
    style = FastTweenColor(pulse * 0.5f, 0x7FE0E0E0, 0x5FF0C070);
    text = GetLocalizedString(0x2DB6);
    text_draw_medium(0x3C, y, style, text, -1);
}

