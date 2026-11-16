#include "include_asm.h"
#include "names.h"

extern float g_wave_line_scroll_step __attribute__((sda));
extern int g_wave_ribbon_first_color __attribute__((sda));
extern int g_wave_ribbon_second_color __attribute__((sda));
extern int g_wave_ribbon_first_alpha __attribute__((sda));
extern int g_wave_ribbon_second_alpha __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void wave_line_draw_ribbon(char *, int, int, int, int);

/* Scrolls the wave line texture and draws its two ribbons. */
void wave_line_draw_effect(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scroll = *(float *)(state + 0x14) - g_wave_line_scroll_step;

    *(float *)(state + 0x14) = scroll;
    if (scroll <= -8.0f) {
        *(float *)(state + 0x14) = scroll + 8.0f;
    }
    VU1_addGSregister(0x47, 0x51001ULL);

    wave_line_draw_ribbon(object, *(int *)(state + 0), g_wave_ribbon_first_color, g_wave_ribbon_first_alpha, 10);
    wave_line_draw_ribbon(object, *(int *)(state + 4), g_wave_ribbon_second_color, g_wave_ribbon_second_alpha, 20);
}
