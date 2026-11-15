#include "include_asm.h"
#include "names.h"

extern void func_00335E38_1(char *p, float x, float y, float zero, float zero2);

extern float D_L04_001AE1E0 __attribute__((sda));

extern float D_L04_001AE1E8 __attribute__((sda));

extern float D_L04_001AE1F0 __attribute__((sda));

extern float D_L04_001AE1F8 __attribute__((sda));

extern float D_L04_001AE1E4;

extern float D_L04_001AE1EC;

extern float D_L04_001AE1F4;

extern float D_L04_001AE1FC;

struct pos {
    float x;
    float y;
};

/* Moves four of the panel parts to their places next to the panel position. */
void info_panel_place_counters(char *object)
{
    float zero = 0.0f;

    func_00335E38_1(object + 1256, D_L04_001AE1F8 + (*(struct pos **)(object + 680))->x,
            D_L04_001AE1FC + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1040, D_L04_001AE1E0 + (*(struct pos **)(object + 680))->x,
            D_L04_001AE1E4 + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1112, D_L04_001AE1E8 + (*(struct pos **)(object + 680))->x,
            D_L04_001AE1EC + (*(struct pos **)(object + 680))->y, zero, zero);
    func_00335E38_1(object + 1184, D_L04_001AE1F0 + (*(struct pos **)(object + 680))->x,
            D_L04_001AE1F4 + (*(struct pos **)(object + 680))->y, zero, zero);
}

extern char D_001ADBC8[];
extern char D_001ADF98[];
extern int D_001ADF80 __attribute__((sda));
extern int D_001ADF84;
extern int D_001ADF88 __attribute__((sda));
extern int D_001ADF8C;
extern int D_001ADF90 __attribute__((sda));
extern const char *GetLocalizedString(int);
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

    sprintf(object + 0x600, D_001ADBC8, GetLocalizedString(0x2DBB));
    hud_set_widget_field_a(object + 0x410, 0);
    text_label_draw(object + 0x410);
    sprintf(object + 0x600, D_001ADF98, save_count_filled_slots());
    object_set_first_float4(object + 0x410, object_get_first_field(object + 0x410)[0] + (float)D_001ADF90,
                  object_get_first_field(object + 0x410)[1], zero, zero);
    hud_set_widget_field_a(object + 0x410, 2);
    text_label_draw(object + 0x410);

    sprintf(object + 0x618, D_001ADBC8, GetLocalizedString(0x2DBC));
    hud_set_widget_field_a(object + 0x458, 0);
    text_label_draw(object + 0x458);
    sprintf(object + 0x618, D_001ADF98, save_get_baseline_count());
    object_set_first_float4(object + 0x458, object_get_first_field(object + 0x458)[0] + (float)D_001ADF90,
                  object_get_first_field(object + 0x458)[1], zero, zero);
    hud_set_widget_field_a(object + 0x458, 2);
    text_label_draw(object + 0x458);

    sprintf(object + 0x630, D_001ADBC8, GetLocalizedString(0x2DBD));
    hud_set_widget_field_a(object + 0x4A0, 0);
    text_label_draw(object + 0x4A0);
    sprintf(object + 0x630, D_001ADF98, save_count_items_above_baseline());
    object_set_first_float4(object + 0x4A0, object_get_first_field(object + 0x4A0)[0] + (float)D_001ADF90,
                  object_get_first_field(object + 0x4A0)[1], zero, zero);
    hud_set_widget_field_a(object + 0x4A0, 2);
    text_label_draw(object + 0x4A0);

    text_label_draw(object + 0x4E8);
    {
        struct pos *box = *(struct pos **)(object + 0x2A8);

        AppendScreenRectPacket((int)box->x + D_001ADF80, (int)box->y + D_001ADF84, (int)box->x + D_001ADF88,
                      (int)box->y + D_001ADF8C, 0x55F0C070UL, 0);
    }
}
