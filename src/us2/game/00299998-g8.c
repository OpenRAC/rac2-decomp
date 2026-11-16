#include "names.h"
/* func_US2_00299998, the USA v2.00 copy of func_00298BB8: the same C, with one more region test. */

extern unsigned char g_save_name_source[];
extern unsigned char g_save_name_title[];
extern unsigned char g_save_name_header[];
extern unsigned char g_save_name_icon[];
extern unsigned char g_save_name_data[];
extern unsigned char g_save_name_format[];
extern char *strncpy(void *, int, int);

void func_US2_00299998(unsigned char *source)
{
    int i;
    int value = source[0x12];
    if (value == 0x45)
        g_save_name_source[2] = value;
    else if (value == 0x50)
        g_save_name_source[2] = 0x49;
    else if (value == 0x4B)
        g_save_name_source[2] = value;
    for (i = 3; i < 7; i++)
        g_save_name_source[i] = source[i + 0xd];
    for (i = 8; i < 11; i++)
        g_save_name_source[i] = source[i + 0xd];
    for (i = 11; i < 13; i++)
        g_save_name_source[i] = source[i + 0xe];
    strncpy(g_save_name_title, (int)g_save_name_source, 13);
    strncpy(g_save_name_header, (int)g_save_name_source, 13);
    strncpy(g_save_name_icon, (int)g_save_name_source, 13);
    strncpy(g_save_name_data, (int)g_save_name_source, 13);
    strncpy(g_save_name_data + 0x14, (int)g_save_name_source, 13);
    strncpy(g_save_name_format, (int)g_save_name_source, 13);
}
