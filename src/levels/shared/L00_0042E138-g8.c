#include "names.h"
/* The level geometry block the model is bound to: the data the model is set up from lives in
   the level's literal pool and is read through $gp. */
extern void *pool_alloc_cell(int value);

extern int *ui_return_second_arg(int size, int pool);

extern void prompt_bar_init(void *object, int value, const void *data);

extern char *GetLocalizedString(int text);

extern void prompt_bar_set_texts(void *object, int first, int second, int third);

extern void prompt_bar_set_text_offsets(void *object, float x0, float y0, float z0, float x1, float y1, float z1);

extern void prompt_bar_set_spacing(void *object, float value);

extern int menu_handle_page_input_c(char *object, int value);

extern int D_L00_001AE1C8 __attribute__((sda));

/* Builds a menu page: allocates its data, sets its colours, text and box, then shows the first choice. */
void menu_build_page_a(char *object, int value)
{
    char *child;
    int *holder;
    int first;
    int second;

    *(int *)object = value;
    if (value != 0) {
        holder = (int *)ui_return_second_arg(16, pool_alloc_cell(value));
        *(int **)(object + 0x2AC) = holder;
        ((int *) holder)[1] = 0;
        ((int *) holder)[2] = 0;
        ((int *) holder)[3] = 0;
        ((int *) holder)[0] = 0;
    }
    child = object + 8;
    ((float *) *(int *)(object + 0x2AC))[0] = 255.0f;
    ((float *) *(int *)(object + 0x2AC))[1] = 195.0f;
    prompt_bar_init(child, value, &D_L00_001AE1C8);
    first = GetLocalizedString(0x2D61);
    second = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(child, first, second, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(child, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(child, 0.4f);
    *(int *)(object + 0x2A8) = 0;
    menu_handle_page_input_c(object, 0);
}
