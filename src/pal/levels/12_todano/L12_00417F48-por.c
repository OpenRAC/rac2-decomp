#include "include_asm.h"

/* func_PAL_L12_00417F48, the PAL copy of func_L12_00413108: the same C, where 1/60 becomes 1/50
   and the fifth argument of each func_002BAE50 call is scaled to 50 Hz. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F413108;

extern s32 D_L12_001B29C8[];

extern float func_002A7878(char *, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_00282CC0(void *, void *, char *);
extern void func_0029FCC0(char *, s32, void *);
extern void func_002BAE50(void *, void *, s32, s32, s32, s32, s32, s32);

/* Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void func_PAL_L12_00417F48(char *obj)
{
    V4_F413108 a, b, org, tmp;
    char *rec = *(char **)(obj + 0x68);
    char *tgt = *(char **)(rec + 0x2F8);
    s32 big, small, st;

    if (tgt != 0 && *(short *)(tgt + 0xAA) == 0x114B) {
        st = *(u8 *)(tgt + 0x20);
        if (st != 0xFE) {
            if (st != 0xFD) {
                tmp.q = 0;
                tmp.f[2] = -(func_002A7878(tgt, 1.7f, 3.0f) * 0.020000001f);
                org.q = tmp.q;
                func_00282CC0(&org, &org, rec + 0x1A0);
                func_0029FCC0(*(char **)(rec + 0x2F8), 5, &a);
                func_0029FCC0(*(char **)(rec + 0x2F8), 6, &b);
                if (D_L12_001B29C8[0] & 1) {
                    func_002BAE50(&a, &org, 0xCF0000FF, 0xCF, ((s32)func_002A7820(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                    func_002BAE50(&b, &org, 0xCF0000FF, 0xCF, ((s32)func_002A7820(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                } else {
                    func_002BAE50(&a, &org, 0x6000FFFF, 0x80, ((s32)func_002A7820(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                    func_002BAE50(&b, &org, 0x6000FFFF, 0x80, ((s32)func_002A7820(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                }
                big = func_002A7820(10, 0x19);
                small = func_002A7820(10, 15);
                func_002BAE50(&a, &org, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
                big = func_002A7820(10, 0x19);
                small = func_002A7820(10, 15);
                func_002BAE50(&b, &org, 0xEFFF7F4F, 0xFF0000, ((s32)small * 5 + 2) / 6, big, -big, 1);
            }
        }
    }
}
