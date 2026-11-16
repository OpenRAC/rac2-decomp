#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int menu_list_get_count(u8 *);
extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern float g_menu_empty_label_y_offset;
extern float g_menu_empty_label_x_offset __attribute__((sda));

void func_US2_003444E8(u8 *a0) {
    if (menu_list_get_count(a0 + 0x2C8) == 0) {
        object_set_flag_value(a0 + 0x208, 0);
    } else {
        int *v = *(int **)(a0 + 0x2B8);
        object_set_first_float4(a0 + 0x208, g_menu_empty_label_x_offset + *(float *)v,
                      g_menu_empty_label_y_offset + *(float *)((u8 *)v + 4), 0.0f, 0.0f);
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

void func_US2_00344558(char *object)
{
    char buffer[256];
    float *position;
    object_set_flag_value((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x2C4)) {
    case 0:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2BE7), GetLocalizedString(0x2BEB));
        break;
    case 2:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2BEA), GetLocalizedString(0x2BEB));
        break;
    case 1:
        sprintf(buffer, g_str_menu_title_format, GetLocalizedString(0x2BE8), GetLocalizedString(0x2BEB));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        sprintf(object + 0x120, g_str_string_format, GetLocalizedString(0));
    else
        strncpy(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x2B8);
    object_set_first_float4(object + 0x1B0, g_menu_title_text_x_offset + position[0], g_menu_title_text_y_offset + position[1], 0.0f, 0.0f);
}
