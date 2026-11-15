#include "include_asm.h"
#include "names.h"

extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, char *);
extern int sprintf(char *, const char *, ...);
extern void hud_set_widget_field_a(void *, int);
extern void text_label_draw(void *);
extern int save_count_filled_slots(void);
extern int save_get_baseline_count(void);
extern int save_count_items_above_baseline(void);
extern float *object_get_first_field(void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_flag_value(void *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern char D_001ADBC8[], D_001ADF98[], D_001AE2F8[];
extern short D_001A7A1A;
extern int D_001A7A1C;
extern int D_001A79FC;
extern int D_001AE2F0 __attribute__((sda));
extern int D_001AE2E0 __attribute__((sda));
extern int D_001AE2E4;
extern int D_001AE2E8 __attribute__((sda));
extern int D_001AE2EC;

/* Updates the texts of the grid menu for the selected entry, such as counts and descriptions, and draws the cursor box. */
void grid_menu_update_labels(char *menu)
{
    int sel = 0;
    float zero;

    if (*(int *)(menu + 0x448) == 3)
        sel = *(int *)(menu + 0x43C) + *(int *)(menu + 0x440) * 2;
    menu[0x410] = 0;
    menu[0x420] = 0;
    hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD2));
    switch (sel) {
    case 0:
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD2));
        zero = 0.0f;
        sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, D_001ADF98, save_count_filled_slots());
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x328)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x410, D_001ADBC8, GetLocalizedString(0x2DBC));
        hud_set_widget_field_a(menu + 0x370, 0);
        text_label_draw(menu + 0x370);
        sprintf(menu + 0x410, D_001ADF98, save_get_baseline_count());
        object_set_first_float4(menu + 0x370, object_get_first_field(menu + 0x370)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x370)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x370, 2);
        text_label_draw(menu + 0x370);
        sprintf(menu + 0x420, D_001ADBC8, GetLocalizedString(0x2DBD));
        hud_set_widget_field_a(menu + 0x3B8, 0);
        text_label_draw(menu + 0x3B8);
        sprintf(menu + 0x420, D_001ADF98, save_count_items_above_baseline());
        object_set_first_float4(menu + 0x3B8, object_get_first_field(menu + 0x3B8)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x3B8)[1], zero, zero);
        hud_set_widget_field_a(menu + 0x3B8, 2);
        text_label_draw(menu + 0x3B8);
        break;
    case 1:
        sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, D_001ADF98, D_001A7A1A);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD1));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD1));
        break;
    case 2:
        sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, D_001ADF98, D_001A7A1C);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xAD0));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xAD0));
        break;
    case 3:
        sprintf(menu + 0x400, D_001ADBC8, GetLocalizedString(0x2DBB));
        hud_set_widget_field_a(menu + 0x328, 0);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, D_001ADF98, D_001A79FC);
        object_set_first_float4(menu + 0x328, object_get_first_field(menu + 0x328)[0] + (float)D_001AE2F0,
                      object_get_first_field(menu + 0x328)[1] + 16.0f, 0.0f, 0.0f);
        hud_set_widget_field_a(menu + 0x328, 2);
        text_label_draw(menu + 0x328);
        sprintf(menu + 0x400, D_001AE2F8, GetLocalizedString(0x2DBB), D_001A79FC);
        hud_set_widget_field_b(menu + 0x2E0, GetLocalizedString(0xACF));
        hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0xACF));
        break;
    }
    text_label_draw(menu + 0x2E0);
    if (*(int *)(menu + 0x444) == sel) {
        object_set_flag_value(menu + 0x210, 1);
        object_set_first_float4(menu + 0x210, (*(float **)(menu + 0x430))[0] + -117.0f,
                      (*(float **)(menu + 0x430))[1] + 3.0f, 0.0f, 0.0f);
        text_label_draw(menu + 0x210);
    }
    if (sel == 0) {
        int x = (*(float **)(menu + 0x430))[0];
        int y = (*(float **)(menu + 0x430))[1];
        AppendScreenRectPacket(x + D_001AE2E0, y + D_001AE2E4, x + D_001AE2E8, y + D_001AE2EC,
                      0x55F0C070, 0);
    }
}
