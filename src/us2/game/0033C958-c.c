#include "include_asm.h"
#include "names.h"
extern void prompt_bar_set_spacing(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts(void *, int, int, int);
extern void prompt_bar_set_text_offsets(void *, float, float, float, float, float, float);
extern int audio_menu_update(void *, int);
extern int g_audio_menu_prompt_ids[2] __attribute__((sda));
extern char g_circle_menu_icon_data[];
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, int);
extern void widget_store_field(void *, int);

void audio_menu_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child, *widget, *secondWidget;
    void *table;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x36C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x36C) = 255.0f;
    (*(float **)(object + 0x36C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2DC;
    secondWidget = object + 0x324;
    prompt_bar_init(child, argument, g_audio_menu_prompt_ids);
    text = GetLocalizedString(0x2C2D);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.67f);
    table = g_circle_menu_icon_data;
    object_init_derived_b(widget, 150, 1, table, argument);
    widget_set_pos_y(widget, 16);
    meter_set_max(widget, 0x400);
    meter_set_value(widget, 0);
    object_set_first_pair(widget, 0x55F0C070, 0x55F0C070);
    object_set_second_pair(widget, 0x60442D00, 0x60442D00);
    text_set_alignment(widget, 0x20FFFFFF);
    widget_store_field(widget, 0);
    object_init_derived_b(secondWidget, 150, 1, table, argument);
    widget_set_pos_y(secondWidget, 16);
    meter_set_max(secondWidget, 0x400);
    meter_set_value(secondWidget, 0);
    object_set_first_pair(secondWidget, 0x55F0C070, 0x55F0C070);
    object_set_second_pair(secondWidget, 0x60442D00, 0x60442D00);
    text_set_alignment(secondWidget, 0x20FFFFFF);
    widget_store_field(secondWidget, 0);
    *(int *)(object + 0x2D8) = 0;
    audio_menu_update(object, 0);
}
