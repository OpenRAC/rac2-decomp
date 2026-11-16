#include "names.h"
/* func_PAL_0028B038 (1,192 bytes): the PAL copy of func_0028A670 (src/game/00288D88.c), the
 * counters panel, with its frame counts for 50 Hz: the fade-in ends after 12 frames instead of
 * 14 and the fade-out starts after 6 instead of 7. Built with the v1.01 unit's flags
 * (-frac2-reload-lone-class-no-rotate -frac2-reload-reuse-pseudo-reg, config/cflags.txt). The
 * hud_coord dead-test helper is allowed by owner ruling (7 November 2026). */
#include "common.h"

typedef struct {
    int value;
    int timer;
    int age;
    short reserved;
    short state;
} CounterRow;
typedef struct {
    CounterRow rows[2];
    int shown;
    int base;
    int pending;
    int active;
    int falling;
} CounterState;
extern CounterState g_bolt_counter_state __attribute__((sda));

typedef struct { float value[7]; } CounterWidths;
extern float g_bolt_counter_widths[];
extern char g_str_bolt_counter_format[];
extern unsigned char *g_resident_data_base __attribute__((sda));
extern float g_hud_scale __attribute__((sda));
extern int FastTweenColor(int, int, float);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern void *table_find_by_id(unsigned char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern void text_draw_right_aligned_small(int, int, unsigned long long, unsigned char *, int);

/* The display mode word beside the HUD scale. */
extern int g_hud_mode __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel; the display-mode test
   has no effect on the result (as func_00326A10). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && g_hud_mode == active)
        scaled = 1.0f;
    return result;
}

/* Draws the bolt counter change boxes with their text, fading in and out by row state (PAL: 50 Hz frame counts). */
void DrawBoltCounterDeltas_pal(void)
{
    char text[16];
    unsigned char active;
    CounterWidths widths;
    int first_x, y, second_y, x, first_y, second_x;
    unsigned int color;
    CounterRow *row;
    int i;
    unsigned int first_color, second_color;
    float fade, scale, width;
    int text_length;
    int one, table_entry;

    second_x = 0;
    color = 0;
    y = 0;
    second_y = 0;
    x = 0;
    first_y = 0;
    widths = *(CounterWidths *)g_bolt_counter_widths;
    scale = 0.0f;
    first_color = 0;
    second_color = 0;
    for (i = 0; i < 2; i++) {
        row = &g_bolt_counter_state.rows[i];
        first_x = 0;
        one = 1;
        switch (row->state) {
        case 1:
            fade = (float)row->age * 0.0714285746f;
            first_color = FastTweenColor(0x00F0C070, 0x55F0C070, fade);
            second_color = FastTweenColor(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x0029A1FF, 0x6029A1FF, fade);
            first_x = 499;
            first_y = 2;
            second_x = 499;
            second_y = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 2:
            if (row->timer < 12)
                fade = (float)row->timer * 0.0714285746f;
            else
                fade = 1.0f;
            first_color = 0x55F0C070;
            second_color = 0x60442D00;
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x8000FFFF, 0x6029A1FF, fade);
            first_x = 499;
            first_y = 2;
            second_x = 499;
            second_y = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 3:
            if (row->timer < 6)
                fade = 1.0f;
            else
                fade = 1.0f - ((float)row->timer - 7.0f) * 0.142857149f;
            first_color = FastTweenColor(0x00F0C070, 0x55F0C070, fade);
            second_color = FastTweenColor(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x0029A1FF, 0x6029A1FF, fade);
            x = 442;
            scale = 1.0f;
            y = 36;
            first_x = 499;
            first_y = 2;
            second_x = 499;
            second_y = 2;
            break;
        }
        if (first_x) {
            sprintf(text, g_str_bolt_counter_format, g_bolt_counter_state.rows[i].value);
            text_length = func_001157AC(text);
            if (text_length > 0) {
                width = widths.value[text_length - 1];
                active = one;
                table_entry = table_find_by_id(g_resident_data_base + 0x8710, 178);
                gfx_draw_scaled_object_two_axes((char *)table_entry, first_color,
                    (float)first_x, (float)hud_coord((float)first_y, g_hud_scale, 0.5f, active), scale, scale, width);
                table_entry = table_find_by_id(g_resident_data_base + 0x8710, 179);
                gfx_draw_scaled_object_two_axes((char *)table_entry, second_color,
                    (float)second_x, (float)hud_coord((float)second_y, g_hud_scale, 0.5f, active), scale, scale, width);
                text_draw_right_aligned_small(x, hud_coord((float)y, g_hud_scale, 0.5f, one), (int)color, (unsigned char *)text, func_001157AC(text));
            }
        }
    }
}



