#include "include_asm.h"
#include "names.h"

extern void prompt_bar_set_spacing_pal(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init_pal(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, int, int, int);
extern void prompt_bar_set_text_offsets_pal(void *, float, float, float, float, float, float);
extern int func_PAL_L00_004388F8(void *, int);
extern int g_onoff_menu_prompt_ids[2] __attribute__((sda));

extern int g_level_child_params_a[2] __attribute__((sda));

void func_PAL_L00_004387D0(char *object, void *argument)
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
    prompt_bar_init_pal(child, argument, g_level_child_params_a);
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_L00_004388F8(object, 0);
}



extern int func_PAL_L00_00438FB8(void *, int);

extern int g_level_child_params_b[2] __attribute__((sda));

void func_PAL_L00_00438E90(char *object, void *argument)
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
    prompt_bar_init_pal(child, argument, g_level_child_params_b);
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_L00_00438FB8(object, 0);
}



extern int func_PAL_L00_004391F8(void *, int);

extern int g_level_child_params_c[2] __attribute__((sda));

void func_PAL_L00_004390D0(char *object, void *argument)
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
    prompt_bar_init_pal(child, argument, g_level_child_params_c);
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_set_text_offsets_pal(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing_pal(child, 0.4f);
    *(int *)(object + 0x2D8) = 0;
    func_PAL_L00_004391F8(object, 0);
}


