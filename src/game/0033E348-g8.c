#include "include_asm.h"
#include "names.h"
extern void prompt_bar_draw(char *);
extern void menu_set_field_bc(char *, int);
extern void option_list_draw_rows(char *);
extern unsigned char g_language;
extern int g_list_page_field_table[2] __attribute__((sda));

/* Draws the list menu page and its list. */
void list_page_draw(char *object)
{
    char *p;
    prompt_bar_draw(object + 8);
    p = object + 0x2B0;
    menu_set_field_bc(p, g_list_page_field_table[g_language]);
    option_list_draw_rows(p);
}

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init(void *, void *, void *);
extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts(void *, int, int, int);
extern void prompt_bar_set_text_offsets(void *, float, float, float, float, float, float);
extern int simple_page_update(void *, int);
extern int g_simple_page_prompt_ids[2] __attribute__((sda));
/* Sets up a simple menu page with a title. */
void simple_page_init(char *object, void *argument)
{
    int *allocation;
    char *child;
    int text;
    *(void **)object = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(object + 0x2A8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(object + 0x2A8) = 255.0f;
    (*(float **)(object + 0x2A8))[1] = 208.0f;
    child = object + 8;
    prompt_bar_init(child, argument, g_simple_page_prompt_ids);
    text = GetLocalizedString(0x2E21);
    prompt_bar_set_texts(child, text, 0, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, -128.0f, -183.0f, 112.0f, 110.0f, 102.0f, 110.0f);
    simple_page_update(object, 0);
}
