#include "include_asm.h"
#include "names.h"
extern void prompt_bar_set_spacing(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts(void *, int, int, int);
extern void prompt_bar_set_text_offsets(void *, float, float, float, float, float, float);
extern int single_toggle_a_update(void *, int);
extern int g_single_toggle_a_prompt_ids[2] __attribute__((sda));

void single_toggle_a_init_us2(char *object, void *argument)
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
    prompt_bar_init(child, argument, g_single_toggle_a_prompt_ids);
    text = GetLocalizedString(0x2C2F);
    second = GetLocalizedString(0x2BE4);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2BE5));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.3f);
    *(int *)(object + 0x2D8) = 0;
    single_toggle_a_update(object, 0);
}
