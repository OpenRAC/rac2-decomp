#include "include_asm.h"

#include "common.h"
extern int D_L20_001B2AC8 __attribute__((sda));
extern int func_PAL_L20_003A0E60(char *, int);
extern void func_PAL_L20_003A07C8(char *);
extern void func_L20_0039D680(char *);
extern float func_00283BE0(float, float);
extern float func_002AAA00(char *, char *, float, float, float, float, int);
extern f32 func_00303270(f32, f32);
extern f32 func_002A7878(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00282DF0(void *);
extern f32 func_00282E80(void *, void *);
extern s32 func_L09_00329028(char *, s32);
extern f32 func_00282E80(void *, void *);

void func_PAL_L20_003A06F8(char *arg0) {
    char *s0 = arg0;
    char *s1;
    f32 c;
    f32 r;
    u32 v1;
    u16 v2;

    s1 = *(char **)(s0 + 0x68);
    func_PAL_L20_003A0E60(s0, 0);
    func_PAL_L20_003A07C8(s0);
    if ((D_L20_001B2AC8 & 7) == (((s32)s0 >> 8) & 7)) {
        func_L20_0039D680(s0);
    }
    c = 0.013962637f;
    r = func_00283BE0(*(f32 *)(s1 + 0x284), *(f32 *)(s0 + 0xF8));
    {
        f32 c2 = c;
        func_002AAA00(s1 + 0x288, s1 + 0x28C, r, c, c2, 0.69813186f, 0);
    }
    *(f32 *)(s1 + 0x284) = *(f32 *)(s0 + 0xF8);
    v2 = *(u16 *)(s0 + 0x96);
    if ((u32)v2 <= 0xFFFEu) {
        *(u16 *)(s0 + 0x96) = v2 + 1;
    }
}


