#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int TI128 __attribute__((mode(TI)));
extern char *func_002A9640(char *, int, int);
extern float func_PAL_002AA108(char *, void *);
extern void func_L08_0032A4D0(char *, char *, char *, char *);
extern void func_PAL_L08_0032DFC0(char *, char *, int, int, int, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_PAL_002A7650(char *, int, int);
extern void func_PAL_002AC290(char *, char *);
extern void func_PAL_002AC3C0(char *, char *);

void func_PAL_L08_003FAAB0(char *self, char *a1)
{
    char *s0 = a1;
    char *s2;
    struct { TI128 in; float out[4]; } l;
    float v;
    float f;

    if (*(u8 *)(self + 0x20) == 4)
        return;
    s2 = func_002A9640(self, 0xC30000, 0);
    f = func_PAL_002AA108(self, s2);
    if (0.0f < f) {
        v = *(float *)(s0 + 0x20) - *(float *)(s2 + 0x2C);
        *(float *)(s0 + 0x20) = v;
        if (0.0f < v) {
            *(float *)(s0 + 0x78) = 0.16000001f;
            *(float *)(s0 + 0x7C) = 0.14000002f;
            l.in = *(TI128 *)(s2 + 0x10);
            func_L08_0032A4D0((char *)&l.in, (char *)l.out, s0 + 0x78, s0 + 0x7C);
            func_PAL_L08_0032DFC0(self, s0 + 0x60, 3, 1, 0, l.out[0]);
            if (1.0f <= f) {
                *(u8 *)(s0 + 0x57) = 0x78;
                *(u8 *)(self + 0x20) = 3;
                func_PAL_002A7E68(self, 2, 0, 0);
            } else {
                *(u8 *)(s0 + 0x57) = 0x78;
            }
        } else {
            *(u16 *)(self + 0x34) &= 0xEFFF;
            *(u8 *)(s0 + 0x57) = 0xFA;
            *(u8 *)(self + 0x20) = 4;
            *(float *)(s0 + 0x78) = 0.22000001f;
            *(float *)(s0 + 0x7C) = 0.14000002f;
            l.in = *(TI128 *)(s2 + 0x10);
            func_L08_0032A4D0((char *)&l.in, (char *)(l.out + 1), s0 + 0x78, s0 + 0x7C);
            func_PAL_L08_0032DFC0(self, s0 + 0x60, 3, 1, 0, l.out[1]);
            *(float *)(s0 + 0xB0) = 5.0f;
            *(float *)(s0 + 0xB4) = 10.0f;
            if (*(u8 *)(self + 0x43) != 3)
                func_PAL_002A7E68(self, 3, 0, 0);
            func_PAL_002A7650(self, 0, 3);
        }
        func_PAL_002AC290(self, s0 + 0x50);
    }
    *(u8 *)(self + 0xA8) = 0xFF;
    func_PAL_002AC3C0(self, s0 + 0x50);
}

