#include "common.h"

/* Reverse a string in place (IntegerToAscii's last step): find its length,
   then swap characters from both ends towards the middle. */
char *func_001184D0(char *s) {
    int c, i, j;

    for (j = 0; s[j] != 0; j++) {
    }
    for (i = 0, j--; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    return s;
}
