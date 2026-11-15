#include "common.h"
extern char *func_0029EFD0(int);

extern void func_002A0F48(void *);

typedef int TI128 __attribute__((mode(TI)));

char *func_L05_00432080(char *a0, float f12)
{
    char *obj = CreateMoby(0x10E3);

    if (obj != 0) {
        int i;
        TI128 *src;
        TI128 *dst;
        char *sub = *(char **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0xFF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0x23) = 0x60;
        *(unsigned short *)(obj + 0x34) |= 0x108;
        *(unsigned char *)(obj + 0x20) = 0;
        *(char **)sub = a0;
        dst = (TI128 *)(obj + 0x10);
        src = (TI128 *)(a0 + 0x10);
        qcopy(dst, src);
        {
            src = (TI128 *)(a0 + 0xC0);
            i = 0;
            dst = (TI128 *)(obj + 0xC0);
            do {
                *dst++ = *src++;
                i++;
            } while (i < 3);
        }
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f12;
        func_002A0F48(obj);
    }
    return obj;
}
