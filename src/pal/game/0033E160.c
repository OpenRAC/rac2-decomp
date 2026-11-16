#include "include_asm.h"
#include "names.h"

extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, char *, char *, char *);
extern void prompt_bar_update_pal(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);
extern int snd_play_from_global_bank(int a, int b, int c);
extern void UpdateViewContext(void);
extern unsigned char g_display_mode_flag;

/* func_PAL_0033E160, the PAL copy of func_0033C2D8: the same C, with the three-string setup added. */
int onoff_menu_update_pal(char *object, int mask)
{
    float *position;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0x10FC);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    position = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, position[0], position[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0) {
        g_display_mode_flag = g_display_mode_flag == 0;
        snd_play_from_global_bank(4, 0, 0);
        UpdateViewContext();
    }
    return (mask >> 6) & 1;
}
