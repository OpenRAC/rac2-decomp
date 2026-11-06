#include "include_asm.h"
typedef int TI128 __attribute__((mode(TI)));

extern int D_001AEF60 __attribute__((sda));

/* func_PAL_L03_0038E5C8, the PAL copy of func_L03_0038B4E8: the same C, with the three
   timers at 0x18, 0x1C and 0x20 scaled to 50 Hz. */
void func_PAL_L03_0038E5C8(unsigned char *a0) {
    unsigned char *p = *(unsigned char **)(a0 + 0x68);
    unsigned char *q = a0;
    int v;

    v = *(int *)(p + 0x9C);
    *(int *)(p + 0x94) = 0;
    if (v < 0)
        *(int *)(p + 0x9C) = 0xE;
    v = *(int *)(p + 0x80);
    if (v < 0)
        *(int *)(p + 0x80) = 0x10;
    *(int *)(p + 0xBC) = 0x80402080;
    *(int *)(p + 0xC0) = 0x80004880;
    *(float *)(p + 0xA4) = 1.0f;
    *(float *)(p + 0xA0) = 0.25f;
    *(int *)(p + 0xA8) = 0;
    *(int *)(p + 0x60) = 0x807F0000;
    *(int *)(p + 0x64) = 0x8000007F;
    *(int *)(p + 0x68) = 0x807F0000;
    *(int *)(p + 0x6C) = 0x8000007F;
    q += 0x10;
    *(TI128 *)(p + 0xE0) = *(TI128 *)q;
    *(float *)(p + 0xE8) = *(float *)(p + 0xE8) + 1.1f;
    *(int *)(p + 0x18) = (*(int *)(p + 0x18) * 5 + 2) / 6;
    *(int *)(p + 0x1C) = (*(int *)(p + 0x1C) * 5 + 2) / 6;
    *(int *)(p + 0x20) = (*(int *)(p + 0x20) * 5 + 2) / 6;
    *(int *)(p + 0xD8) = -1;
    *(int *)(p + 0xDC) = *(int *)(p + 0xDC) << 3;
    D_001AEF60 = 0;
}
