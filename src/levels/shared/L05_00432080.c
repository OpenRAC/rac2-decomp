#include "common.h"
extern char *CreateMoby(int);

extern void func_002A0F48(void *);

typedef int TI128 __attribute__((mode(TI)));

/* Creates an object of class 0x10E3 that copies the position and orientation of the given object. */
char *CreateTransformClone(char *source, float scale_factor)
{
    char *new_obj = CreateMoby(0x10E3);

    if (new_obj != 0) {
        int i;
        TI128 *src;
        TI128 *dst;
        char *vars = *(char **)(new_obj + 0x68);
        *(unsigned char *)(new_obj + 0x30) = 0xFF;
        *(unsigned short *)(new_obj + 0x32) = 0xFF;
        *(unsigned char *)(new_obj + 0x31) = 1;
        *(unsigned char *)(new_obj + 0x23) = 0x60;
        *(unsigned short *)(new_obj + 0x34) |= 0x108;
        *(unsigned char *)(new_obj + 0x20) = 0;
        *(char **)vars = source;
        dst = (TI128 *)(new_obj + 0x10);
        src = (TI128 *)(source + 0x10);
        qcopy(dst, src);
        {
            src = (TI128 *)(source + 0xC0);
            i = 0;
            dst = (TI128 *)(new_obj + 0xC0);
            do {
                *dst++ = *src++;
                i++;
            } while (i < 3);
        }
        *(float *)(new_obj + 0x2C) = *(float *)(*(char **)(new_obj + 0x24) + 0x24) * scale_factor;
        func_002A0F48(new_obj);
    }
    return new_obj;
}
