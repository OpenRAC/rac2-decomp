#include "names.h"
/* The x offsets use small-data loads; incomplete SDA y declarations retain
 * the absolute macro loads without claiming an unmeasured array extent. */
extern void prompt_bar_update(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *text_format_location_name(char *, int);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, void *);
extern void info_panel_place_counters(void *);
extern void DrawMapScreen(int);
extern char g_map_overlay_state[], D_001ADC88[];
extern int D_00258D70[];
extern float D_001ADF28 __attribute__((sda));
extern float D_001ADF2C[] __attribute__((sda));
extern float D_001ADF30 __attribute__((sda));
extern float D_001ADF34[] __attribute__((sda));
extern float D_001ADF38 __attribute__((sda));
extern float D_001ADF3C[] __attribute__((sda));
extern float D_001ADF40 __attribute__((sda));
extern float D_001ADF44[] __attribute__((sda));
extern float D_001ADF48 __attribute__((sda));
extern float D_001ADF4C[] __attribute__((sda));
extern float D_001ADF50 __attribute__((sda));
extern float D_001ADF54[] __attribute__((sda));
extern float D_001ADF58 __attribute__((sda));
extern float D_001ADF5C[] __attribute__((sda));
/* Updates the info panel: moves every part into place and shows the text for the selected item. */
int info_panel_update(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x578;
    char *state;
    int text;
    float x, y;

    prompt_bar_update(child);
    menu_set_anchor_pos(child, (*(float **)(object + 0x2A8))[0], (*(float **)(object + 0x2A8))[1]);
    x = D_001ADF28 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF2C[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x2E8, x, y, 0.0f, 0.0f);
    x = D_001ADF30 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF34[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x330, x, y, 0.0f, 0.0f);
    x = D_001ADF38 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF3C[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x378, x, y, 0.0f, 0.0f);
    x = D_001ADF50 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF54[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x2AC, x, y, 0.0f, 0.0f);
    x = D_001ADF58 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF5C[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x3C0, x, y, 0.0f, 0.0f);
    x = D_001ADF48 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF4C[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(label, x, y, 0.0f, 0.0f);
    x = D_001ADF40 + (*(float **)(object + 0x2A8))[0];
    y = D_001ADF44[0] + (*(float **)(object + 0x2A8))[1];
    object_set_first_float4(object + 0x530, x, y, 0.0f, 0.0f);
    state = g_map_overlay_state;
    text_format_location_name(object + 0x5C0, *(int *)(state + 0x230));
    text = D_00258D70[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        hud_set_widget_field_b(label, GetLocalizedString(text));
    else
        hud_set_widget_field_b(label, D_001ADC88);
    info_panel_place_counters(object);
    DrawMapScreen(0);
    return (flags >> 6) & 1;
}
