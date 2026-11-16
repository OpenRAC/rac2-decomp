#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_us2(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_us2(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_us2(void *, int, int, int);
extern void prompt_bar_set_text_offsets_us2(void *, float, float, float, float, float, float);
extern int func_US2_L00_004348C8(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

extern int g_child_param_pair_e[2] __attribute__((sda));

void func_US2_L00_004347A0(char *object, void *argument)
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
    prompt_bar_init_us2(child, argument, g_child_param_pair_e);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_004348C8(object, 0);
}



extern int func_US2_L00_00434F48(void *, int);

extern int g_child_param_pair_f[2] __attribute__((sda));

void func_US2_L00_00434E20(char *object, void *argument)
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
    prompt_bar_init_us2(child, argument, g_child_param_pair_f);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_00434F48(object, 0);
}



extern int func_US2_L00_00435140(void *, int);

extern int g_child_param_pair_g[2] __attribute__((sda));

void func_US2_L00_00435018(char *object, void *argument)
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
    prompt_bar_init_us2(child, argument, g_child_param_pair_g);
    text = GetLocalizedString(0x2BF7);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts_us2(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets_us2(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_us2(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_US2_L00_00435140(object, 0);
}


