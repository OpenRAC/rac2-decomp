#include "include_asm.h"
typedef int TI128 __attribute__((mode(TI)));

extern int D_001AEF60 __attribute__((sda));

/* Sets the starting values (colors, sizes, timers and position) of an effect moby when it is created. */
void func_L03_0038B4E8(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *source = object;
    int value;

    value = *(int *)(state + 0x9C);
    *(int *)(state + 0x94) = 0;
    if (value < 0)
        *(int *)(state + 0x9C) = 0xE;
    value = *(int *)(state + 0x80);
    if (value < 0)
        *(int *)(state + 0x80) = 0x10;
    *(int *)(state + 0xBC) = 0x80402080;
    *(int *)(state + 0xC0) = 0x80004880;
    *(float *)(state + 0xA4) = 1.0f;
    *(float *)(state + 0xA0) = 0.25f;
    *(int *)(state + 0xA8) = 0;
    *(int *)(state + 0x60) = 0x807F0000;
    *(int *)(state + 0x64) = 0x8000007F;
    *(int *)(state + 0x68) = 0x807F0000;
    *(int *)(state + 0x6C) = 0x8000007F;
    source += 0x10;
    *(TI128 *)(state + 0xE0) = *(TI128 *)source;
    *(int *)(state + 0xD8) = -1;
    *(int *)(state + 0xDC) = *(int *)(state + 0xDC) << 3;
    *(float *)(state + 0xE8) = *(float *)(state + 0xE8) + 1.1f;
    D_001AEF60 = 0;
}
