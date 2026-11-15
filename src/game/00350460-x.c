#include "include_asm.h"
#include "names.h"

extern void *func_001153D4(void *, const void *, unsigned int);

/* Copies a two-part source (len1 bytes at src1, then len2 bytes at src2) into
   two destination blocks: the first holds pos bytes, the second takes the
   rest.  Returns the total length, or 0 when it does not fit in pos + size. */
int func_00350460(char *dst1, int pos, char *dst2, int size, char *src1, int len1, char *src2, int len2)
{
    int rest;

    if (pos + size < len1 + len2)
        return 0;
    if (len1 >= pos) {
        memcpy_001153D4(dst1, src1, pos);
        memcpy_001153D4(dst2, src1 + pos, len1 - pos);
        memcpy_001153D4(dst2 + len1 - pos, src2, len2);
    } else {
        rest = pos - len1;
        if (len2 >= rest) {
            memcpy_001153D4(dst1, src1, len1);
            memcpy_001153D4(dst1 + len1, src2, rest);
            memcpy_001153D4(dst2, src2 + pos - len1, len2 - rest);
        } else {
            memcpy_001153D4(dst1, src1, len1);
            memcpy_001153D4(dst1 + len1, src2, len2);
        }
    }
    return len1 + len2;
}
