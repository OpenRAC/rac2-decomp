#include "names.h"
extern void prompt_bar_set_spacing(void *, float);
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void prompt_bar_init(void *, void *, void *);
extern int GetLocalizedString(int);
extern void prompt_bar_set_texts(void *, int, int, int);
extern void prompt_bar_set_text_offsets(void *, float, float, float, float, float, float);
extern void onoff_menu_update(void *, int);
extern int D_001ADDE0[2] __attribute__((sda));
/* Sets up the on/off option menu: its button prompt bar, labels and position. */
void onoff_menu_init(char *menu, void *owner)
{
    int *allocation;
    char *prompt;
    int textA, textB;
    *(void **)menu = owner;
    if (owner) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(menu + 0x2AC) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)(menu + 0x2AC) = 255.0f;
    (*(float **)(menu + 0x2AC))[1] = 195.0f;
    prompt = menu + 8;
    prompt_bar_init(prompt, owner, D_001ADDE0);
    textA = GetLocalizedString(0x31E4);
    textB = GetLocalizedString(0x2D4E);
    prompt_bar_set_texts(prompt, textA, textB, GetLocalizedString(0x2D4F));
    prompt_bar_set_text_offsets(prompt, 0.0f, -143.0f, 0.0f, 114.0f, 0.0f, 140.0f);
    prompt_bar_set_spacing(prompt, 0.65f);
    *(int *)(menu + 0x2A8) = 0;
    onoff_menu_update(menu, 0);
}
