#include "common.h"

extern void *func_0029EFD0(int id);
extern float func_00283CE0(int value);
extern void func_002A0F48(void *moby);

void *func_L08_003CCC30(void *src, int id, short flag, int value, int extra, unsigned char b1,
                        unsigned char b2) {
    unsigned char *s = (unsigned char *)src;
    unsigned char *d = (unsigned char *)CreateMoby(id);
    unsigned char *sub;

    if (d) {
        d[0x30] = s[0x30];
        *(unsigned short *)(d + 0x32) = *(unsigned short *)(s + 0x32);
        d[0x31] = 1;
        qcopy(d + 0x10, s + 0x10);
        qcopy(d + 0xF0, s + 0xF0);
        *(float *)(d + 0xF8) = *(float *)(s + 0xF8);
        *(int *)(d + 0xF0) = 0;
        *(int *)(d + 0xF4) = 0;
        sub = (unsigned char *)*(unsigned int *)(d + 0x68);
        *(unsigned short *)(sub + 0x4) = flag;
        sub[0x1C] = value;
        *(float *)(sub + 0x8) = IntToFloat(value);
        sub[0x1D] = b2;
        *(int *)sub = extra;
        sub[0x1E] = b1;
        *(unsigned short *)(sub + 0x6) = 0;
        func_002A0F48(d);
        d[0x20] = 0;
    }
    return d;
}
