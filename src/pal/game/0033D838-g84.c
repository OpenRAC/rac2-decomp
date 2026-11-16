#include "include_asm.h"
#include "names.h"

struct pos {
    float x;
    float y;
};
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
extern void func_PAL_00338770(char *);
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
void func_PAL_00340D78(char *self)
{
    float zero = 0.0f;

    sprintf(self + 0x6C0, g_str_string_format, GetLocalizedString(0xBCC));
    hud_set_widget_field_a(self + 0x470, 0);
    func_PAL_00338770(self + 0x470);
    sprintf(self + 0x6C0, g_str_count_format, save_count_filled_slots());
    object_set_first_float4(self + 0x470, object_get_first_field(self + 0x470)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(self + 0x470)[1], zero, zero);
    hud_set_widget_field_a(self + 0x470, 2);
    func_PAL_00338770(self + 0x470);

    sprintf(self + 0x6D8, g_str_string_format, GetLocalizedString(0xBCD));
    hud_set_widget_field_a(self + 0x4C8, 0);
    func_PAL_00338770(self + 0x4C8);
    sprintf(self + 0x6D8, g_str_count_format, save_get_baseline_count());
    object_set_first_float4(self + 0x4C8, object_get_first_field(self + 0x4C8)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(self + 0x4C8)[1], zero, zero);
    hud_set_widget_field_a(self + 0x4C8, 2);
    func_PAL_00338770(self + 0x4C8);

    sprintf(self + 0x6F0, g_str_string_format, GetLocalizedString(0xBCE));
    hud_set_widget_field_a(self + 0x520, 0);
    func_PAL_00338770(self + 0x520);
    sprintf(self + 0x6F0, g_str_count_format, save_count_items_above_baseline());
    object_set_first_float4(self + 0x520, object_get_first_field(self + 0x520)[0] + (float)g_info_panel_counter_shift_x,
                  object_get_first_field(self + 0x520)[1], zero, zero);
    hud_set_widget_field_a(self + 0x520, 2);
    func_PAL_00338770(self + 0x520);

    func_PAL_00338770(self + 0x578);
    {
        struct pos *pos = *(struct pos **)(self + 0x2D8);

        AppendScreenRectPacket((int)pos->x + g_info_panel_rect_left, (int)pos->y + g_info_panel_rect_top, (int)pos->x + g_info_panel_rect_right,
                      (int)pos->y + g_info_panel_rect_bottom, 0x55F0C070UL, 0);
    }
}
