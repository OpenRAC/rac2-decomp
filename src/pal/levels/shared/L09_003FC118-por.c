#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_PAL_F3FC118;

extern s32 D_L09_001B2388[];

extern float func_002A7878(char *, float, float);
extern s32 func_002A7820(s32, s32);
extern void func_00282CC0(void *, void *, char *);
extern void func_0029FCC0(char *, s32, void *);
extern void func_002BAE50(void *, void *, s32, s32, s32, s32, s32, s32);

/* func_PAL_L09_003FC118, the PAL copy of func_L09_003F7840: the same C, where 1/60 becomes 1/50 and the random fifth argument of each burst takes the 5/6 scale. Sprays the flame sprites of the object's grabbed target: while the target is the live flame moby it draws two bursts at each of its two hand points. */
void func_PAL_L09_003FC118(char *obj)
{
    V4_PAL_F3FC118 a, b, org, tmp;
    char *rec = *(char **)(obj + 0x68);
    char *tgt = *(char **)(rec + 0x2F8);
    s32 big, small, st;

    if (tgt != 0 && *(short *)(tgt + 0xAA) == 0xD0E) {
        st = *(u8 *)(tgt + 0x20);
        if (st != 0xFE) {
            if (st != 0xFD) {
                tmp.q = 0;
                tmp.f[2] = -(func_002A7878(tgt, 1.7f, 3.0f) * 0.020000001f);
                org.q = tmp.q;
                func_00282CC0(&org, &org, rec + 0x1A0);
                func_0029FCC0(*(char **)(rec + 0x2F8), 5, &a);
                func_0029FCC0(*(char **)(rec + 0x2F8), 6, &b);
                if (D_L09_001B2388[0] & 1) {
                    func_002BAE50(&a, &org, 0xCF0000FF, 0xCF, ((s32)func_002A7820(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                    func_002BAE50(&b, &org, 0xCF0000FF, 0xCF, ((s32)func_002A7820(0x12, 0x16) * 5 + 2) / 6, 0x28, -10, 1);
                } else {
                    func_002BAE50(&a, &org, 0x6000FFFF, 0x80, ((s32)func_002A7820(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                    func_002BAE50(&b, &org, 0x6000FFFF, 0x80, ((s32)func_002A7820(0x14, 0x18) * 5 + 2) / 6, 0x50, -10, 1);
                }
                big = func_002A7820(10, 0x19);
                small = func_002A7820(10, 15);
                func_002BAE50(&a, &org, 0xEFFF7F4F, 0xFF0000, (small * 5 + 2) / 6, big, -big, 1);
                big = func_002A7820(10, 0x19);
                small = func_002A7820(10, 15);
                func_002BAE50(&b, &org, 0xEFFF7F4F, 0xFF0000, (small * 5 + 2) / 6, big, -big, 1);
            }
        }
    }
}
