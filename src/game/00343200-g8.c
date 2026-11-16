#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;

extern int menu_list_get_count(u8 *);
extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern float g_menu_empty_label_y_offset;
extern float g_menu_empty_label_x_offset __attribute__((sda));
/* Hides the menu's label when its list is empty, otherwise places it next to the menu. */
void menu_update_empty_label(u8 *menu) {
    if (menu_list_get_count(menu + 0x298) == 0) {
        object_set_flag_value(menu + 0x1F8, 0);
    } else {
        int *position = *(int **)(menu + 0x288);
        object_set_first_float4(menu + 0x1F8, g_menu_empty_label_x_offset + *(float *)position,
                      g_menu_empty_label_y_offset + *(float *)((u8 *)position + 4), 0.0f, 0.0f);
    }
}

extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern char *strncpy(void *, int, int);
extern char g_str_menu_title_format[];
extern char g_str_string_format[];
extern float g_menu_title_text_x_offset __attribute__((sda));
extern float g_menu_title_text_y_offset;
/* Fills in the menu's title text for the current mode and puts it in place. */
void menu_update_title_text(char *object)
{
    char buffer[256];
    float *position;
    object_set_flag_value((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x294)) {
    case 0:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2D51), GetLocalizedString(0x2D55));
        break;
    case 2:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2D54), GetLocalizedString(0x2D55));
        break;
    case 1:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2D52), GetLocalizedString(0x2D55));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        sprintf(object + 0x120, g_str_string_format, GetLocalizedString(0));
    else
        strncpy(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x288);
    object_set_first_float4(object + 0x1B0, g_menu_title_text_x_offset + position[0], g_menu_title_text_y_offset + position[1], 0.0f, 0.0f);
}
