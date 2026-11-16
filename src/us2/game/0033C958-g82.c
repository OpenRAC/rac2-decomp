#include "include_asm.h"
#include "names.h"

typedef unsigned char u8_Ff4eb83c9;
typedef int s32_Ff4eb83c9;
extern int UpdateFourOptionMenuInput(u8_Ff4eb83c9 *, s32_Ff4eb83c9);
extern void prompt_bar_update_us2(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern int snd_play_from_global_bank(int, int, void *);
extern void UpdateViewContext(void);

/* Handles input for the four option menu: moves the selection and changes the chosen option. */
int UpdateFourOptionMenuInput_us2(u8_Ff4eb83c9 *object, int flags)
{
    u8_Ff4eb83c9 *bar = object + 8;
    unsigned int *sfx = (unsigned int *)0x1A7BAC;
    unsigned int *music = (unsigned int *)0x1A7BB0;
    int *mode = (int *)0x1A7BB4;
    unsigned char *toggle = (unsigned char *)0x1A7BB9;
    float *anchor;
    int selected;

    prompt_bar_update_us2(bar);
    anchor = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(bar, anchor[0], anchor[1]);
    if (flags & 0x1000) {
        snd_play_from_global_bank(3, 0, 0);
        selected = *(int *)(object + 0x2D8);
        *(int *)(object + 0x2D8) = (selected + 3) % 4;
    } else if (flags & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        selected = *(int *)(object + 0x2D8);
        *(int *)(object + 0x2D8) = (selected + 1) % 4;
    } else if (flags & 0x40) {
        snd_play_from_global_bank(4, 0, 0);
        switch (*(int *)(object + 0x2D8)) {
        case 0:
            *sfx = *sfx < 1;
            break;
        case 1:
            *music = *music < 1;
            break;
        case 2:
            *mode = (*mode + 1) % 3;
            break;
        case 3:
            *toggle = *toggle < 1;
            UpdateViewContext();
            break;
        }
    }
    return (flags >> 6) & 1;
}

typedef struct { int ids[2]; } OptionPair;
typedef struct { int ids[3]; } OptionTriple;
extern OptionPair g_on_off_option_text __attribute__((section(".data")));
extern OptionPair g_on_off_text_ids __attribute__((section(".data")));
extern OptionTriple g_mode_option_text __attribute__((section(".data")));
extern char g_str_menu_option_format[];
extern int g_four_option_label_x_first __attribute__((sda));
extern int g_four_option_label_y_first[] __attribute__((sda));
extern int g_four_option_label_x_second __attribute__((sda));
extern int g_four_option_label_y_second[] __attribute__((sda));
extern int g_four_option_label_x_third __attribute__((sda));
extern int g_four_option_label_y_third[] __attribute__((sda));
extern int g_four_option_label_x_fourth __attribute__((sda));
extern int g_four_option_label_y_fourth[] __attribute__((sda));
extern int g_invert_aim_option, g_ship_steer_option, g_control_mode_option;
extern unsigned char g_display_mode_flag;
extern void prompt_bar_draw_us2(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);

/* Draws the four option menu: its prompt bar and the four option lines. */
void four_option_menu_draw_us2(char *object)
{
    char buffer[128];
    OptionPair onoff;
    OptionTriple modes;
    OptionPair toggle;
    char *first, *second, *format;
    char *label2, *label3, *label4;
    int color;
    prompt_bar_draw_us2(object + 8);
    onoff = g_on_off_option_text;
    modes = g_mode_option_text;
    toggle = g_on_off_text_ids;
    format = g_str_menu_option_format;
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    first = GetLocalizedString(0x2C78);
    second = GetLocalizedString(onoff.ids[g_invert_aim_option != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_medium(g_four_option_label_x_first, g_four_option_label_y_first[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label2 = GetLocalizedString(0x2C77);
    second = GetLocalizedString(onoff.ids[g_ship_steer_option != 0]);
    sprintf(buffer, format, label2, second);
    text_draw_centered_medium(g_four_option_label_x_second, g_four_option_label_y_second[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    {
        int mode = g_control_mode_option;
        label3 = GetLocalizedString(0x2DAE);
        second = GetLocalizedString(modes.ids[mode]);
    }
    sprintf(buffer, format, label3, second);
    text_draw_centered_medium(g_four_option_label_x_third, g_four_option_label_y_third[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 3 ? (int)0x80D0D0D0 : 0x70808080;
    label4 = GetLocalizedString(0x307A);
    second = GetLocalizedString(toggle.ids[g_display_mode_flag != 0]);
    sprintf(buffer, format, label4, second);
    text_draw_centered_medium(g_four_option_label_x_fourth, g_four_option_label_y_fourth[0], color, buffer, -1);
}
