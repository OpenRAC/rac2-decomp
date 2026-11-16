#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_pal(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, int, int, int);
extern void prompt_bar_set_text_offsets_pal(void *, float, float, float, float, float, float);
extern int onoff_menu_update_pal(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

/* Sets up the on/off option page (PAL): its button prompt bar, three labels, spacing and position. */
void onoff_menu_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_onoff_menu_prompt_ids);
    first_text = GetLocalizedString(0x10FC);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.65f);
    *(int *)(object + 0x2D8) = 0;
    onoff_menu_update_pal(object, 0);
}

extern int four_option_menu_update_pal(void *, int);

extern int g_child_params_a[2] __attribute__((sda));

/* Sets up an option page with its own on/off prompt: its button prompt bar, three labels, spacing and position. */
void onoff_menu_b_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_a);
    first_text = GetLocalizedString(0xBA9);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.65f);
    *(int *)(object + 0x2D8) = 0;
    four_option_menu_update_pal(object, 0);
}



extern int two_toggle_a_update_pal(void *, int);

extern int g_child_params_b[2] __attribute__((sda));

/* Sets up a two-toggle option page: its button prompt bar, three labels, spacing and position. */
void two_toggle_a_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_b);
    first_text = GetLocalizedString(0xBA4);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.2f);
    *(int *)(object + 0x2D8) = 0;
    two_toggle_a_update_pal(object, 0);
}



extern int single_toggle_a_update_pal(void *, int);

extern int g_child_params_c[2] __attribute__((sda));

/* Sets up a single-toggle option page: its button prompt bar, three labels, spacing and position. */
void single_toggle_a_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_c);
    first_text = GetLocalizedString(0xBAA);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_a_update_pal(object, 0);
}



extern int two_toggle_b_update_pal(void *, int);

extern int g_child_params_d[2] __attribute__((sda));

/* Sets up a two-toggle option page: its button prompt bar, three labels, spacing and position. */
void two_toggle_b_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_d);
    first_text = GetLocalizedString(0xB72);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    two_toggle_b_update_pal(object, 0);
}



extern int single_toggle_c_update_pal(void *, int);

extern int g_child_params_e[2] __attribute__((sda));

/* Sets up a single-toggle option page: its button prompt bar, three labels, spacing and position. */
void single_toggle_c_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_e);
    first_text = GetLocalizedString(0xB72);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_c_update_pal(object, 0);
}



extern int single_toggle_d_update_pal(void *, int);

extern int g_child_params_f[2] __attribute__((sda));

/* Sets up a single-toggle option page: its button prompt bar, three labels, spacing and position. */
void single_toggle_d_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_f);
    first_text = GetLocalizedString(0xB72);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_d_update_pal(object, 0);
}



extern int single_toggle_e_update_pal(void *, int);

extern int g_child_params_g[2] __attribute__((sda));

/* Sets up a single-toggle option page: its button prompt bar, three labels, spacing and position. */
void single_toggle_e_init_pal(char *object, void *owner)
{
    int *allocation;
    char *child;
    int first_text, second_text;
    *(void **)object = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(object + 0x2DC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2DC) = 255.0f;
    (*(float **)(object + 0x2DC))[1] = 195.0f;
    child = object + 8;
    prompt_bar_init_pal(child, owner, g_child_params_g);
    first_text = GetLocalizedString(0xB72);
    second_text = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, first_text, second_text, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_e_update_pal(object, 0);
}


