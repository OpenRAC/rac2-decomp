#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L02_0043F638);

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7750(u8 *,s32,s32);
extern u8 *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float,
                           int, int, int, void *);
struct Pair43E150 {
    float a;
    float b;
};
extern const struct Pair43E150 D_L02_001B29B0;
extern const struct Pair43E150 D_L02_001B29B8;
extern const TI128 D_L02_001B29C0[2];
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void func_L00_00324F18(char *, char *, float, float, float);
extern int func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_PAL_L00_002ED7E8(void *,void *,float,void *,float,int,unsigned char,float,float,float);

void func_PAL_L02_00443B98(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    int kind = a0[0x20];
    struct Pair43E150 a = D_L02_001B29B0;
    struct Pair43E150 b = D_L02_001B29B8;
    TI128 c[2];
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));

    c[0] = D_L02_001B29C0[0];
    c[1] = D_L02_001B29C0[1];
    *(TI128 *)d = 0;
    switch (kind) {
    case 0:
        func_PAL_L00_0032C328(a0, c, &b, &a, 0xFFFF, 0, -1, 0x10, 0xFFFF, 0xFF, 0);
        *(u32 *)(a0 + 0x98) = *(u32 *)(*(u8 **)(a0 + 0x24) + 0x10);
        *(u16 *)(a0 + 0x7C) = 0;
        func_L00_00324F18((char *)a0, (char *)e, d[0], d[1], d[2]);
        func_PAL_L00_003FB330(e, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(float *)(a0 + 0x2C) * 7.0f,
                      20.0f, 1, 1, 1, 0);
        *(s32 *)state = 0x11;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_00282948(state) != 0) {
            func_L00_00324F18((char *)a0, (char *)e, d[0], d[1], d[2]);
            func_PAL_L00_003FB330(e, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0,
                          *(float *)(a0 + 0x2C) * 3.5f, 20.0f, 0, 0, 0, 0);
            *(s32 *)(state + 4) = 0x64;
            func_002A7750(a0, 2, -1);
        }
        break;
    case 2:
        if (func_00282948(state + 4) != 0 || *(s32 *)(state + 4) >= 0x4C) {
            *(TI128 *)e = 0;
            e[1] = -0.020000001f;
            e[2] = 0.060000002f;
            func_00283098(e, e, a0 + 0xC0);
            func_PAL_L00_002ED7E8(a0,d,0.0f,e,0.040000003f,func_002A7820(3,6),0,0.5f,15.0f,2.0f);
            func_PAL_L00_002ED7E8(a0,d,0.0f,e,0.040000003f,func_002A7820(3,6),1,0.5f,15.0f,2.0f);
            *(s32 *)(state + 4) = ((s32)(func_002A7820(0x2D, 0x5A)) * 5 + 2) / 6;
        }
        break;
    }
}

