#include "common.h"
/* Rounds the decimal digit string buf of length len in place when its last digit is 5 or more,
   carrying through 9s; returns 0 if the carry overflows the first digit, else 1. */
int func_00118460(char *buf, int len) {
    char *p;
    if (len <= 0) goto done;
    --len;
    p = buf + len;
    if (*p < '5') goto done;
    do {
        *p = '0';
        --p;
    } while (--len > 0 && *p == '9');
    buf += len;
    if (*buf == '9') return 0;
    ++*buf;
done:
    return 1;
}
