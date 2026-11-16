#include "common.h"
#include "include_asm.h"

extern char *strncpy(char *dst, char *src, int len);
extern void text_format_number_separators(char *dst, int x, int idx);
extern unsigned char g_pal_region_mode MACRO_ADDR;

/* Copies a format string, replacing each %d or %N with a number from the pair list written with thousands separators. PAL copy of func_L01_00324410: the same C, where the
 * separator index 0 becomes the byte D_PAL_001A7C3C. */
void text_format_numbers_in_string_pal(char *out, char *src, int *nums)
{
    int values[10];
    unsigned char number_text[32];
    int count;
    int *pair;
    int *value_out;
    unsigned char *read;
    char *write;
    int len;
    int next_arg;
    int arg_index;

    pair = nums;
    count = 0;
    strncpy((char *)0x70000000, src, 0xFF);

    value_out = values;
    for (;;) {
        pair += 2;
        arg_index = pair[-2];
        if (arg_index == -1)
            break;
        *value_out++ = arg_index;
        count++;
        if (count >= 10)
            break;
    }

    read = (unsigned char *)0x70000000;
    write = out;
    next_arg = 0;
    while (*read != 0) {
        if (*read == '%') {
            if (read[1] == 'd') {
                arg_index = next_arg++;
                read += 2;
            } else {
                arg_index = read[1] - '0';
                read += 3;
            }
            text_format_number_separators((char *)number_text, values[arg_index], g_pal_region_mode);
            len = 0;
            if (*number_text != 0) {
                while (number_text[len] != 0 && len < 32) {
                    *write = number_text[len];
                    len++;
                    write++;
                }
            }
            *write = 0;
        } else {
            *write = *read;
            read++;
            write++;
        }
    }
    *write = 0;
}
