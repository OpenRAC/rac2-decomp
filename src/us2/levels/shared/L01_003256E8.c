#include "common.h"
#include "include_asm.h"

extern char *strncpy(char *dst, char *src, int len);
extern void text_format_number_separators(char *dst, int x, int idx);
extern unsigned char g_display_mode_index MACRO_ADDR;

/* func_US2_L01_003256E8, the USA v2.00 copy of func_L01_00324410: the same C, where the
 * separator index 0 becomes the byte D_US2_001A7BBC. */
void text_expand_number_template_us2(char *out, char *src, int *nums)
{
    int values[10];
    unsigned char digits[32];
    int i;
    int *src_nums;
    int *value_ptr;
    unsigned char *text_in;
    char *text_out;
    int len;
    int auto_index;
    int value;

    src_nums = nums;
    i = 0;
    strncpy((char *)0x70000000, src, 0xFF);

    value_ptr = values;
    for (;;) {
        src_nums += 2;
        value = src_nums[-2];
        if (value == -1)
            break;
        *value_ptr++ = value;
        i++;
        if (i >= 10)
            break;
    }

    text_in = (unsigned char *)0x70000000;
    text_out = out;
    auto_index = 0;
    while (*text_in != 0) {
        if (*text_in == '%') {
            if (text_in[1] == 'd') {
                value = auto_index++;
                text_in += 2;
            } else {
                value = text_in[1] - '0';
                text_in += 3;
            }
            text_format_number_separators((char *)digits, values[value], g_display_mode_index);
            len = 0;
            if (*digits != 0) {
                while (digits[len] != 0 && len < 32) {
                    *text_out = digits[len];
                    len++;
                    text_out++;
                }
            }
            *text_out = 0;
        } else {
            *text_out = *text_in;
            text_in++;
            text_out++;
        }
    }
    *text_out = 0;
}
