#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_pal(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, int, int, int);
extern void prompt_bar_set_text_offsets_pal(void *, float, float, float, float, float, float);
extern int menu_handle_page_input_c_pal(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

extern int g_prompt_bar_params_a[2] __attribute__((sda));

/* Builds the first on/off menu page: allocates its cell, sets up the prompt bar with three texts and offsets. */
void menu_build_page_a_pal(char *object, void *parent)
{
    int *cell;
    char *child;
    int text_a, text_b;
    *(void **)object = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(object + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, parent, g_prompt_bar_params_a);
    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    menu_handle_page_input_c_pal(object, 0);
}



extern int menu_update_two_part_flags_b_pal(void *, int);

extern int g_prompt_bar_params_b[2] __attribute__((sda));

/* Builds the text_b on/off menu page, the same as the first with its own parameters. */
void menu_build_page_b_pal(char *object, void *parent)
{
    int *cell;
    char *child;
    int text_a, text_b;
    *(void **)object = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(object + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, parent, g_prompt_bar_params_b);
    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    menu_update_two_part_flags_b_pal(object, 0);
}



extern int menu_update_two_part_flags_c_pal(void *, int);

extern int g_level_child_params_c[2] __attribute__((sda));

/* Builds the third on/off menu page, the same as the first with its own parameters. */
void menu_build_page_c_pal(char *object, void *parent)
{
    int *cell;
    char *child;
    int text_a, text_b;
    *(void **)object = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(object + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, parent, g_level_child_params_c);
    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    menu_update_two_part_flags_c_pal(object, 0);
}


