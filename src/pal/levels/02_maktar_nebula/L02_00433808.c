#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void func_002A7750();
extern void func_00282CC0(void *, void *, void *);
typedef int TI128 __attribute__((mode(TI)));
extern void *func_002A9640(void *, int, int);
extern u8 D_001A7BCB __attribute__((sda));
extern u8 D_L02_001395B8[];
extern u8 D_L02_001C0700[];
extern s32 func_00288AA0(u8 *, s32);
extern s32 func_00288BE8(u8 *);
extern void func_0029F338(u8 *);
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern void *func_002A9640(void *, int, int);
extern void func_00283098(void *, void *, void *);
struct Pair42E2F8 {
    float a;
    float b;
};
extern const struct Pair42E2F8 D_L02_001B23E0;
extern const struct Pair42E2F8 D_L02_001B23E8;
extern const TI128 D_L02_001B23F0[2];
extern s32 D_L02_001AEC78 __attribute__((sda));
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void *func_L00_0033E220(void *, void *, int, int, int, int, int, int, float, float);
extern void func_PAL_L00_003281C0(void *, int, float);
extern void *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_PAL_L00_00328480(void *,void *,int,int,void *,u32,void *,float,float,float,float);
extern void func_PAL_L02_00433B90(u8 *, float, float);
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));

void func_PAL_L02_00433808(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    struct Pair42E2F8 a = D_L02_001B23E0;
    struct Pair42E2F8 b = D_L02_001B23E8;
    TI128 c[2];
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));

    c[0] = D_L02_001B23F0[0];
    c[1] = D_L02_001B23F0[1];
    switch (a0[0x20]) {
    case 0:
        *(TI128 *)d = 0;
        d[2] = 4.0f;
        func_L00_0033E220(d, a0, 0x28208080, -1, 0, -1, 0, 0x60, 409500.0f, 0.0f);
        func_L00_0033E220(d, a0, 0x20208080, -1, 1, -1, 0, 0x60, 367500.0f, 0.75f);
        if (*(s32 *)state != 0)
            D_L02_001AEC78 = D_L02_001AEC78 - 1;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0 && *(s32 *)state == 0) {
            D_L02_001AEC78 = D_L02_001AEC78 - 1;
            func_002A7750(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_PAL_L00_0032C328(a0, c, &b, &a, 0xB, 0, 1, 5, 0xFFFF, 0xFF, 0);
        func_PAL_L00_003281C0(a0, 1, 4.0f);
        *(TI128 *)d = 0;
        d[1] = -0.120000005f;
        d[2] = 0.060000002f;
        func_00283098(d, d, a0 + 0xC0);
        func_PAL_002735D0(a0, 1, *(s16 *)(a0 + 0xAA), 1, a0 + 0x10, a0 + 0xF0, d, 0xFF, 0.0f, 15.0f);
        *(TI128 *)e = 0;
        e[1] = 0.2f;
        e[2] = 4.3f;
        func_00283098(e, e, a0 + 0xC0);
        func_00282CC0(e, e, a0 + 0x10);
        *(TI128 *)f = 0;
        f[1] = 0.060000002f;
        f[2] = 0.030000001f;
        func_00283098(f, f, a0 + 0xC0);
        func_PAL_L00_00328480(a0,e,4,1,f,0x50404040,0,0.25f,5.0f,0.5f,1.0f);
        func_PAL_L02_00433B90(a0, 0.020000001f, 0.28000003f);
        func_0029F338(a0);
        break;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L02_00433B90);

