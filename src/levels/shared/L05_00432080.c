#include "common.h"
extern char *func_0029EFD0(int);

extern void func_002A0F48(void *);

typedef int TI128 __attribute__((mode(TI)));

/* Creates an object of class 0x10E3 that copies the position and orientation of the given object. */
char *func_L05_00432080(char *source, float scaleFactor)
{
    char *newObj = CreateMoby(0x10E3);

    if (newObj != 0) {
        int i;
        TI128 *src;
        TI128 *dst;
        char *vars = *(char **)(newObj + 0x68);
        *(unsigned char *)(newObj + 0x30) = 0xFF;
        *(unsigned short *)(newObj + 0x32) = 0xFF;
        *(unsigned char *)(newObj + 0x31) = 1;
        *(unsigned char *)(newObj + 0x23) = 0x60;
        *(unsigned short *)(newObj + 0x34) |= 0x108;
        *(unsigned char *)(newObj + 0x20) = 0;
        *(char **)vars = source;
        dst = (TI128 *)(newObj + 0x10);
        src = (TI128 *)(source + 0x10);
        qcopy(dst, src);
        {
            src = (TI128 *)(source + 0xC0);
            i = 0;
            dst = (TI128 *)(newObj + 0xC0);
            do {
                *dst++ = *src++;
                i++;
            } while (i < 3);
        }
        *(float *)(newObj + 0x2C) = *(float *)(*(char **)(newObj + 0x24) + 0x24) * scaleFactor;
        func_002A0F48(newObj);
    }
    return newObj;
}
