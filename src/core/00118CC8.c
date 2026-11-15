#include "names.h"
/* vfprintf_dispatch (symbol_addrs/usa-v2 0x00118cc8, size 0xCC): the split
   newlib/SDK printf picks its engine from the format string. It scans for a
   conversion and, when the conversion is one of the floating point set
   (E G L e f g), tail-calls the float-capable engine VfprintfFloat 0x118D98;
   otherwise, once the string is exhausted, it tail-calls the integer-only
   engine VfprintfInteger 0x119BF8. Both engines get (fp->_data, fp, fmt0, ap).
   The switch over (c - 0x45) is what makes cc1 emit the 35-entry table at
   0x13A4B0. */
extern int VfprintfFloat(void *arg0, void *arg1, char *arg2, void *arg3);

extern int VfprintfInteger(void *arg0, void *arg1, char *arg2, void *arg3);

/* Looks at the format string and picks the float-capable or the integer-only print routine. */
int vfprintf_dispatch(void *fp, char *fmt, void *ap) {
    char *p;

    for (p = fmt; *p != '\0'; p++) {
        if (*p == '%' && p[1] != '\0') {
            p++;
            while (*p < 'A' && p[1] != '\0') {
                p++;
            }
            switch (*p) {
            case 'E':
            case 'G':
            case 'L':
            case 'e':
            case 'f':
            case 'g':
                return VfprintfFloat(*(void **)((char *)fp + 0x54), fp, fmt, ap);
            }
        }
    }
    return VfprintfInteger(*(void **)((char *)fp + 0x54), fp, fmt, ap);
}
