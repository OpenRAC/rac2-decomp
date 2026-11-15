#include "include_asm.h"
#include "names.h"

extern void prompt_bar_init(char *p, void *argument, void *table);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts(char *p, int a, int b, int c);
extern void prompt_bar_set_text_offsets(char *p, float a, float b, float c, float d, float e, float f);
extern void prompt_bar_set_spacing(char *p, float f);
extern int *ui_return_second_arg(int size, int count);
extern void *pool_alloc_cell(void *argument);

extern int menu_update_two_part_flags_b(char *object, int flags);
extern int menu_update_two_part_flags_c(char *object, int flags);

extern int D_L00_001AE1E8[2] __attribute__((sda));
extern int D_L00_001AE1F8[2] __attribute__((sda));

/* Builds the labelled sub-view on the object: allocation record, two size floats, then the
   three localized strings, the box and the scale, finally the next layer down. */
void menu_build_page_b(char *object, void *argument)
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
    prompt_bar_init(child, argument, D_L00_001AE1E8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    menu_update_two_part_flags_b(object, 0);
}

/* Same construction as func_L00_004336E8 with its own label table and lower layer. */
/* Builds a second menu page the same way as the first one. */
void menu_build_page_c(char *object, void *argument)
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
    prompt_bar_init(child, argument, D_L00_001AE1F8);
    text = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, text, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    menu_update_two_part_flags_c(object, 0);
}
