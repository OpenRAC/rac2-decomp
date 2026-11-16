#include "include_asm.h"
#include "names.h"

extern void prompt_bar_draw_us2(char *);
extern void func_US2_00348E58(char *, int);
extern void option_list_draw_rows_us2(char *);
extern unsigned char g_language;
extern int g_list_page_field_table[2] __attribute__((sda));

/* Draws a list page: its prompt bar and the language dependent list widget. */
void list_page_draw_us2(char *object)
{
    char *widget;
    prompt_bar_draw_us2(object + 8);
    widget = object + 0x2E0;
    func_US2_00348E58(widget, g_list_page_field_table[g_language]);
    option_list_draw_rows_us2(widget);
}

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_us2(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_us2(void *, int, int, int);
extern void prompt_bar_set_text_offsets_us2(void *, float, float, float, float, float, float);
extern int simple_page_update_us2(void *, int);
extern int g_simple_page_prompt_ids[2] __attribute__((sda));

/* Sets up a simple page: prompt bar and texts. */
void simple_page_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2D8) = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 208.0f;
    child = object + 8;
    prompt_bar_init_us2(child, argument, g_simple_page_prompt_ids);
    text = GetLocalizedString(0x2CB7);
    prompt_bar_set_texts_us2(child, text, 0, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, -128.0f, -183.0f, 112.0f, 110.0f, 102.0f, 110.0f);
    simple_page_update_us2(object, 0);
}

extern void prompt_bar_set_spacing_us2(void *, float);
extern int list_page_update_us2(void *, int);
extern int g_list_page_prompt_ids[2] __attribute__((sda));
extern void list_menu_reset_attach_items_us2(void *, void *);
extern void func_US2_00348E10(void *, int, int);
extern void option_list_set_highlight_us2(void *, int);

/* Sets up a list page: prompt bar, texts and list widget. */
void list_page_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child, *widget;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x3BC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x3BC) = 255.0f;
    (*(float **)(object + 0x3BC))[1] = 195.0f;
    child = object + 8;
    widget = object + 0x2E0;
    prompt_bar_init_us2(child, argument, g_list_page_prompt_ids);
    text = GetLocalizedString(0x2C36);
    second = GetLocalizedString(0x2C0B);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    list_menu_reset_attach_items_us2(widget, argument);
    func_US2_00348E10(widget, -83, 32);
    option_list_set_highlight_us2(widget, 1);
    list_page_update_us2(object, 0);
}

extern int two_toggle_b_update_us2(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

extern int g_child_param_pair_a[2] __attribute__((sda));

/* Sets up a two-option menu: prompt bar and texts. */
void two_toggle_b_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_us2(child, argument, g_child_param_pair_a);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    two_toggle_b_update_us2(object, 0);
}



extern int single_toggle_c_update_us2(void *, int);

extern int g_child_param_pair_b[2] __attribute__((sda));

/* Sets up a one-option menu: prompt bar and texts. */
void single_toggle_c_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_us2(child, argument, g_child_param_pair_b);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_c_update_us2(object, 0);
}



extern int single_toggle_d_update_us2(void *, int);

extern int g_child_param_pair_c[2] __attribute__((sda));

/* Sets up a one-option menu: prompt bar and texts. */
void single_toggle_d_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_us2(child, argument, g_child_param_pair_c);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_d_update_us2(object, 0);
}



extern int single_toggle_e_update_us2(void *, int);

extern int g_child_param_pair_d[2] __attribute__((sda));

/* Sets up a one-option menu: prompt bar and texts. */
void single_toggle_e_init_us2(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text, second;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_us2(child, argument, g_child_param_pair_d);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_e_update_us2(object, 0);
}



extern void prompt_bar_update_us2(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void snd_send_cmd11_one_value(int);
extern void meter_set_value(void *, int);
extern void snd_set_default_group_volumes(void);
extern unsigned char g_subtitles_option[] __attribute__((sda));
extern struct { int w0, w1, w2; } g_pad_menu_flags;
extern float g_audio_menu_offset_a __attribute__((sda));
extern float g_audio_menu_offset_c __attribute__((sda));
extern float g_audio_menu_offset_b, g_audio_menu_offset_d;

/* Handles input for the audio menu: moves the selection and changes the volumes. */
int audio_menu_update_us2(char *object, int flags)
{
    char *p = object + 8;
    float *vec;

    prompt_bar_update_us2(p);
    vec = *(float **)(object + 0x36C);
    menu_set_anchor_pos(p, vec[0], vec[1]);
    vec = *(float **)(object + 0x36C);
    object_set_first_float4(object + 0x2DC, vec[0] + g_audio_menu_offset_a,
                 vec[1] + g_audio_menu_offset_b, 0.0f, 0.0f);
    vec = *(float **)(object + 0x36C);
    object_set_first_float4(object + 0x324, vec[0] + g_audio_menu_offset_c,
                 vec[1] + g_audio_menu_offset_d, 0.0f, 0.0f);
    if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 2) % 3;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        *(int *)(object + 0x2D8) = (*(int *)(object + 0x2D8) + 1) % 3;
    } else if (g_pad_menu_flags.w0 & 0x8000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(g_subtitles_option + 12) - 6;
            *(int *)(g_subtitles_option + 12) = value < 0 ? 0 : value;
            break;
        }
        case 1: {
            int value = *(int *)(g_subtitles_option + 8) - 6;
            *(int *)(g_subtitles_option + 8) = value < 0 ? 0 : value;
            break;
        }
        }
    } else if (g_pad_menu_flags.w0 & 0x2000) {
        switch (*(int *)(object + 0x2D8)) {
        case 0: {
            int value = *(int *)(g_subtitles_option + 12) + 6;
            *(int *)(g_subtitles_option + 12) = value > 1024 ? 1024 : value;
            break;
        }
        case 1: {
            int value = *(int *)(g_subtitles_option + 8) + 6;
            *(int *)(g_subtitles_option + 8) = value > 1024 ? 1024 : value;
            break;
        }
        }
    } else if (flags & 0x40) {
        if (*(int *)(object + 0x2D8) == 2) {
            int value;
            snd_play_from_global_bank(4, 0, 0);
            value = *(int *)(g_subtitles_option + 4) == 0;
            *(int *)(g_subtitles_option + 4) = value;
            snd_send_cmd11_one_value(!value);
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    meter_set_value(object + 0x324, *(int *)(g_subtitles_option + 8));
    meter_set_value(object + 0x2DC, *(int *)(g_subtitles_option + 12));
    snd_set_default_group_volumes();
    return (flags >> 6) & 1;
}
