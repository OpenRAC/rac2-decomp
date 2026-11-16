#include "include_asm.h"
#include "names.h"

extern void func_00335E38_1(char *p, float x, float y, float zero, float zero2);

extern float g_info_panel_counter_x0 __attribute__((sda));

extern float g_info_panel_counter_x1 __attribute__((sda));

extern float g_info_panel_counter_x2 __attribute__((sda));

extern float g_info_panel_counter_offset_x __attribute__((sda));

extern float g_info_panel_counter_y0;

extern float g_info_panel_counter_y1;

extern float g_info_panel_counter_y2;

extern float g_info_panel_counter_offset_y;

struct pos {
    float x;
    float y;
};

/* Moves four of the panel parts to their places next to the panel position. */
void info_panel_place_counters(char *object)
{
    float zero = 0.0f;

    func_00335E38_1(object + 1256, g_info_panel_counter_offset_x + (*(struct pos **)(object + 680))->x,
            g_info_panel_counter_offset_y + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1040, g_info_panel_counter_x0 + (*(struct pos **)(object + 680))->x,
            g_info_panel_counter_y0 + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1112, g_info_panel_counter_x1 + (*(struct pos **)(object + 680))->x,
            g_info_panel_counter_y1 + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1184, g_info_panel_counter_x2 + (*(struct pos **)(object + 680))->x,
            g_info_panel_counter_y2 + (*(struct pos **)(object + 680))->y, zero, zero);
}

extern char g_str_string_format[];
extern char g_str_count_format[];
extern int g_info_panel_rect_left __attribute__((sda));
extern int g_info_panel_rect_top;
extern int g_info_panel_rect_right __attribute__((sda));
extern int g_info_panel_rect_bottom;
extern int g_info_panel_counter_shift_x __attribute__((sda));
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(char *, int);
extern void text_label_draw(char *);
extern int save_count_filled_slots(void);
extern int save_get_baseline_count(void);
extern int save_count_items_above_baseline(void);
extern float *object_get_first_field(char *);
extern void object_set_first_float4(char *, float, float, float, float);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);

/* formats three message strings (0x2DBB to 0x2DBD) and a count each into buffers at +0x600/+0x618/+0x630,
   places the text objects at +0x410/+0x458/+0x4A0 from the position pointer at +0x2A8, then draws one box;
   func_0028FC48 takes its colour as unsigned long (as in 002D5E98-g8.c): with an int the argument setup
   is scheduled differently from retail */
/* Draws the three counter lines of the panel and the box behind them. */
void info_panel_draw_counters(char *object)
{
    float zero = 0.0f;

    sprintf(object + 0x600, g_str_string_format, GetLocalizedString(0x2DBB));
    hud_set_widget_field_a(object + 0x410, 0);
    text_label_draw(object + 0x410);
    sprintf(object + 0x600, g_str_count_format, save_count_filled_slots());
    object_set_first_float4(object + 0x410, object_get_first_field(object + 0x410)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(object + 0x410)[1], zero, zero);
    hud_set_widget_field_a(object + 0x410, 2);
    text_label_draw(object + 0x410);

    sprintf(object + 0x618, g_str_string_format, GetLocalizedString(0x2DBC));
    hud_set_widget_field_a(object + 0x458, 0);
    text_label_draw(object + 0x458);
    sprintf(object + 0x618, g_str_count_format, save_get_baseline_count());
    object_set_first_float4(object + 0x458, object_get_first_field(object + 0x458)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(object + 0x458)[1], zero, zero);
    hud_set_widget_field_a(object + 0x458, 2);
    text_label_draw(object + 0x458);

    sprintf(object + 0x630, g_str_string_format, GetLocalizedString(0x2DBD));
    hud_set_widget_field_a(object + 0x4A0, 0);
    text_label_draw(object + 0x4A0);
    sprintf(object + 0x630, g_str_count_format, save_count_items_above_baseline());
    object_set_first_float4(object + 0x4A0, object_get_first_field(object + 0x4A0)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(object + 0x4A0)[1], zero, zero);
    hud_set_widget_field_a(object + 0x4A0, 2);
    text_label_draw(object + 0x4A0);

    text_label_draw(object + 0x4E8);
    {
        struct pos *box = *(struct pos **)(object + 0x2A8);

        AppendScreenRectPacket((int)box->x + g_info_panel_rect_left, (int)box->y + g_info_panel_rect_top, (int)box->x + g_info_panel_rect_right,
                      (int)box->y + g_info_panel_rect_bottom, 0x55F0C070UL, 0);
    }
}
