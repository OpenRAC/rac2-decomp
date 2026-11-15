#include "include_asm.h"
#include "common.h"

extern char *D_001B2348 __attribute__((sda));
extern void func_002FF290(char *, int);
extern void func_002A7398(char *, int, int);
extern void func_002A0F48(char *);

/* Sets up the shared effect object with default size and position data and starts the chosen variant. */
char *func_002FF300(int mode, int variant)
{
    char *object;
    object = D_001B2348;
    InitObjectWithPrivateData(object, mode);
    *(unsigned short *)(object + 0x34) &= 0xFFBC;
    *(unsigned char *)(object + 0x30) = 0xFF;
    *(short *)(object + 0x32) = 0x20;
    *(unsigned char *)(object + 0x31) = 1;
    *(float *)(object + 0x10) = 5.0f;
    *(float *)(object + 0x14) = 5.0f;
    *(float *)(object + 0x18) = 900.0f;
    *(float *)(object + 0x1C) = 1.0f;
    qzero(object + 0xF0);
    if (variant >= 0) {
        StartAnimationImmediate(object, variant, 0);
    } else {
        char *objectClass = *(char **)(object + 0x24);
        if (objectClass != 0 && *(unsigned char *)(objectClass + 0xC) >= 2)
            StartAnimationImmediate(object, 1, 0);
    }
    if ((*(unsigned short *)(object + 0x34) & 4) == 0)
        func_002A0F48(object);
    return object;
}
