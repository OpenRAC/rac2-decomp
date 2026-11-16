#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern unsigned int func_001157AC(const char *);
extern char *strncpy(void *, int, int);
extern char g_str_string_format[];
extern float g_menu_title_text_x_offset __attribute__((sda));
extern float g_menu_title_text_y_offset;

/* func_PAL_003456B0, the PAL copy of func_00343638: the same C, where the selector field moves, the
   text ids change and each case formats one string through D_001ADBC8 instead of two. */
void menu_update_title_text_pal(char *object)
{
    char buffer[256];
    float *position;
    object_set_flag_value((u8 *)object + 0x1B0, 1);
    switch (*(int *)(object + 0x2C4)) {
    case 0:
        sprintf(buffer, g_str_string_format, GetLocalizedString(0xB62));
        break;
    case 2:
        sprintf(buffer, g_str_string_format, GetLocalizedString(0xB65));
        break;
    case 1:
        sprintf(buffer, g_str_string_format, GetLocalizedString(0xB63));
        break;
    }
    if (func_001157AC(buffer) >= 49)
        sprintf(object + 0x120, g_str_string_format, GetLocalizedString(0));
    else
        strncpy(object + 0x120, (int)buffer, 49);
    position = *(float **)(object + 0x2B8);
    object_set_first_float4(object + 0x1B0, g_menu_title_text_x_offset + position[0], g_menu_title_text_y_offset + position[1], 0.0f, 0.0f);
}
