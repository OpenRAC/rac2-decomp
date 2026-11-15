#include "common.h"

/* Convert the signed input using an unsigned magnitude, then reverse the digits. */
extern char D_00134640[];

extern char *func_001184D0(char *arg0);

/* Writes a whole number as text in the given number base. */
char *func_00118548(int input, char *buf, unsigned int base) {
    unsigned int value = input;
    unsigned int neg = (unsigned int)input >> 31;
    int len;

    if (neg) {
        if (base == 10)
            value = -input;
    }
    len = 0;
    do {
        buf[len++] = D_00134640[value % base];
        value /= base;
    } while (value != 0);
    if (neg)
        buf[len++] = '-';
    buf[len] = '\0';
    return ReverseString(buf);
}
