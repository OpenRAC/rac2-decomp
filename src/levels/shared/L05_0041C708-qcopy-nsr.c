#include "common.h"

extern char *func_0029EFD0(int kind);
extern void func_002A0F48(char *a0);

/* Arms the rung the factory returns: stamps the five flag bytes, binds the owner and the handle,
 * copies the owner's position and three matrix rows into the rung, folds the rate, then starts it. */
char *func_L05_0041C708(char *a0, char *a1, int kind, f32 f12)
{
    char *s0 = CreateMoby(kind);
    char *sub;
    char *src;
    char *dst;
    int i;

    if (s0 != 0) {
        sub = *(char **)(s0 + 0x68);
        *(u8 *)(s0 + 0x30) = 0xFF;
        *(u16 *)(s0 + 0x32) = 0xFF;
        *(u8 *)(s0 + 0x31) = 1;
        *(u16 *)(s0 + 0x34) |= 0x100;
        *(u8 *)(s0 + 0x20) = 0;
        *(char **)sub = a0;
        qcopy(s0 + 0x10, a0 + 0x10);
        i = 0;
        src = a0 + 0xC0;
        dst = s0 + 0xC0;
        for (; i < 3; i++) {
            qcopy(dst, src);
            src += 16;
            dst += 16;
        }
        *(f32 *)(s0 + 0x2C) = *(f32 *)(*(char **)(s0 + 0x24) + 0x24) * f12;
        *(char **)(sub + 4) = a1;
        func_002A0F48(s0);
    }
    return s0;
}
