#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_us2(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_us2(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_us2(void *, int, int, int);
extern void prompt_bar_set_text_offsets_us2(void *, float, float, float, float, float, float);
extern int menu_handle_page_input_c_us2(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

extern int g_child_param_pair_e[2] __attribute__((sda));

/* Initialises a menu page with a prompt bar of three texts (confirm, back, extra), a sizing cell and the page's first state. */
void menu_l00_init_page_record_g_us2(char *menu, void *parent)
{
    int *cell;
    char *prompt_bar;
    int first_text, second_text;
    *(void **)menu = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(menu + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(menu + 0x2DC) = 255.0f;
    (*(float **)(menu + 0x2DC))[1] = 195.0f;
    prompt_bar = menu + 8;
    prompt_bar_init_us2(prompt_bar, parent, g_child_param_pair_e);
    first_text = GetLocalizedString(0x2BF7);
    second_text = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(prompt_bar, first_text, second_text, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(prompt_bar, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(prompt_bar, 0.4f);
    *(int *)(menu + 0x2D8) = 0;
    menu_handle_page_input_c_us2(menu, 0);
}



extern int menu_handle_page_input_e_us2(void *, int);

extern int g_child_param_pair_f[2] __attribute__((sda));

/* Initialises a menu page with a prompt bar of three texts (confirm, back, extra), a sizing cell and the page's first state. */
void menu_l00_init_page_record_h_us2(char *menu, void *parent)
{
    int *cell;
    char *prompt_bar;
    int first_text, second_text;
    *(void **)menu = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(menu + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(menu + 0x2DC) = 255.0f;
    (*(float **)(menu + 0x2DC))[1] = 195.0f;
    prompt_bar = menu + 8;
    prompt_bar_init_us2(prompt_bar, parent, g_child_param_pair_f);
    first_text = GetLocalizedString(0x2BF7);
    second_text = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(prompt_bar, first_text, second_text, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(prompt_bar, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(prompt_bar, 0.4f);
    *(int *)(menu + 0x2D8) = 0;
    menu_handle_page_input_e_us2(menu, 0);
}



extern int menu_handle_page_input_f_us2(void *, int);

extern int g_child_param_pair_g[2] __attribute__((sda));

/* Initialises a menu page with a prompt bar of three texts (confirm, back, extra), a sizing cell and the page's first state. */
void menu_l00_init_page_record_i_us2(char *menu, void *parent)
{
    int *cell;
    char *prompt_bar;
    int first_text, second_text;
    *(void **)menu = parent;
    if (parent) {
        cell = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(int **)(menu + 0x2DC) = cell;
        cell[1] = 0;
        cell[2] = 0;
        cell[3] = 0;
        cell[0] = 0;
    }
    **(float **)(menu + 0x2DC) = 255.0f;
    (*(float **)(menu + 0x2DC))[1] = 195.0f;
    prompt_bar = menu + 8;
    prompt_bar_init_us2(prompt_bar, parent, g_child_param_pair_g);
    first_text = GetLocalizedString(0x2BF7);
    second_text = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(prompt_bar, first_text, second_text, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(prompt_bar, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(prompt_bar, 0.4f);
    *(int *)(menu + 0x2D8) = 0;
    menu_handle_page_input_f_us2(menu, 0);
}


