#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);

/* Spawns an object of type 0x12F2 and fills its position and its sub-record vector. */
char *func_L20_0039C540(char *arg0, char *arg1, char *arg2, float f12) {
    char *v;
    char *o = CreateMoby(0x12F2);

    if (o != 0) {
        *(int *)(o + 0xB8) = (int)arg0;
        *(TI128 *)(o + 0x10) = *(TI128 *)arg1;
        v = *(char **)(o + 0x68);
        *(unsigned char *)(o + 0x30) = 0xFF;
        *(TI128 *)(v + 0x10) = *(TI128 *)arg2;
        *(float *)(v + 0x2C) = f12;
        *(int *)(v + 0x20) = 0x12C;
    }
    return o;
}
