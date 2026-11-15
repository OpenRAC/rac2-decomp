#include "names.h"
extern void prompt_bar_set_spacing(void *, float);
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init(void *, void *, void *);
extern int GetLocalizedString(int);
extern void prompt_bar_set_texts(void *, int, int, int);
extern void prompt_bar_set_text_offsets(void *, float, float, float, float, float, float);
extern void single_toggle_a_update(void *, int);
extern int D_001ADE78[2] __attribute__((sda));
/* Sets up a menu page with a single on/off option. */
void single_toggle_a_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init(child, argument, D_001ADE78);
    text = GetLocalizedString(0x2D99);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.3f);
    *(int *)(object + 0x2A8) = 0;
    single_toggle_a_update(object, 0);
}
extern void two_toggle_b_update(void *, int);
extern int D_001ADE88[2] __attribute__((sda));
/* Sets up a menu page with two on/off options. */
void two_toggle_b_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init(child, argument, D_001ADE88);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    two_toggle_b_update(object, 0);
}
extern void single_toggle_c_update(void *, int);
extern int D_001ADE98[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void single_toggle_c_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init(child, argument, D_001ADE98);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.3f);
    *(int *)(object + 0x2A8) = 0;
    single_toggle_c_update(object, 0);
}

extern void single_toggle_d_update(void *, int);
extern int D_001ADEA8[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void single_toggle_d_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init(child, argument, D_001ADEA8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    single_toggle_d_update(object, 0);
}

extern void single_toggle_e_update(void *, int);
extern int D_001ADEB8[2] __attribute__((sda));
/* Sets up another menu page with a single on/off option. */
void single_toggle_e_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2AC) = 255.0f;
    (*(float **)(object + 0x2AC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init(child, argument, D_001ADEB8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    single_toggle_e_update(object, 0);
}

extern void list_page_update(void *, int);
extern int D_001ADEC8[2] __attribute__((sda));
extern void list_menu_reset_attach_items(void *, void *);
extern void menu_set_settings(void *, int, int);
extern void menu_set_field_b8(void *, int);
/* Sets up a menu page that shows a scrolling list. */
void list_page_init(char *object, void *argument)
{
    int *allocation;
    char *child, *widget;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x37C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x37C) = 255.0f;
    (*(float **)(object + 0x37C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2B0;
    prompt_bar_init(child, argument, D_001ADEC8);
    text = GetLocalizedString(0x2DA0);
    second = GetLocalizedString(0x2D75);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    list_menu_reset_attach_items(widget, argument);
    menu_set_settings(widget, -83, 32);
    menu_set_field_b8(widget, 1);
    list_page_update(object, 0);
}

extern void audio_menu_update(void *, int);
extern int D_001ADE48[2] __attribute__((sda));
extern char D_001ADC88[];
extern void object_init_derived_b(void *, int, int, void *, void *);
extern void widget_set_pos_y(void *, int);
extern void meter_set_max(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, int, int);
extern void object_set_second_pair(void *, int, int);
extern void text_set_alignment(void *, int);
extern void widget_store_field(void *, int);
/* Sets up the audio options menu with its two volume sliders and title box. */
void audio_menu_init(char *object, void *argument)
{
    int *allocation;
    char *child, *widget, *secondWidget;
    void *table;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x33C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x33C) = 255.0f;
    (*(float **)(object + 0x33C))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2AC;
    secondWidget = object + 0x2F4;
    prompt_bar_init(child, argument, D_001ADE48);
    text = GetLocalizedString(0x2D97);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.67f);
    table = D_001ADC88;
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
    *(int *)(object + 0x2A8) = 0;
    audio_menu_update(object, 0);
}
