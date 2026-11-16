#include "common.h"

/* Convert the signed input using an unsigned magnitude, then reverse the digits. */
extern char g_str_digit_chars[];

extern char *str_reverse(char *arg0);

/* Writes a whole number as text in the given number base. */
char *IntegerToAscii(int input, char *buf, unsigned int base) {
    unsigned int value = input;
    unsigned int neg = (unsigned int)input >> 31;
    int len;

    if (neg) {
        if (base == 10)
            value = -input;
    }
    len = 0;
    do {
        buf[len++] = g_str_digit_chars[value % base];
        value /= base;
    } while (value != 0);
    if (neg)
        buf[len++] = '-';
    buf[len] = '\0';
    return str_reverse(buf);
}
