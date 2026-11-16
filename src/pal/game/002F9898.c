#include "include_asm.h"
#include "common.h"




/* func_PAL_002FAB40, the PAL copy of func_002F9BC0: the same C, with the thousands separator
   chosen by the language byte D_PAL_001A7C3C ('.' for 3, 4 and 5, ' ' for 2, ',' elsewhere). */
extern int func_00115DA8_1(char *, char *, ...);
extern unsigned char g_pal_region_mode MACRO_ADDR;
extern char g_str_millions_format_a[];
extern char g_str_millions_format_b[];
extern char g_str_number_millions_format[];
extern char g_str_thousands_format_a[];
extern char g_str_thousands_format_b[];
extern char g_str_number_thousands_format[];
extern char g_str_number_plain_format[];

void func_PAL_002FAB40(char *dst, int value)
{
    if (value > 999999) {
        if (g_pal_region_mode == 3 || g_pal_region_mode == 5 || g_pal_region_mode == 4)
            func_00115DA8_1(dst, g_str_millions_format_a, value / 1000000, (value / 1000) % 1000, value % 1000);
        else if (g_pal_region_mode == 2)
            func_00115DA8_1(dst, g_str_millions_format_b, value / 1000000, (value / 1000) % 1000, value % 1000);
        else
            func_00115DA8_1(dst, g_str_number_millions_format, value / 1000000, (value / 1000) % 1000, value % 1000);
    } else if (value >= 1000) {
        if (g_pal_region_mode == 3 || g_pal_region_mode == 5 || g_pal_region_mode == 4)
            func_00115DA8_1(dst, g_str_thousands_format_a, value / 1000, value % 1000);
        else if (g_pal_region_mode == 2)
            func_00115DA8_1(dst, g_str_thousands_format_b, value / 1000, value % 1000);
        else
            func_00115DA8_1(dst, g_str_number_thousands_format, value / 1000, value % 1000);
    } else
        func_00115DA8_1(dst, g_str_number_plain_format, value);
}
