#include "common.h"
/* Rounds a string of decimal digits up when the next digit is 5 or more, carrying to the left. */
int RoundDecimalDigits(char *buf, int len) {
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
