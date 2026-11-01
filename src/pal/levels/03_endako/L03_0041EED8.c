#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_00282F20(void *, void *, float);
extern void *func_L00_0033E220(void *, void *, u32, int, int, int, int, int, float, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, u32, int);
extern void func_PAL_L00_0032C328(void *, float *, float *, float *, int, int, int, int, int, u8, void *);
extern void func_PAL_L00_003281C0(void *, int, float);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void *func_PAL_L00_003FB330(void *, float, int, int, int, int, int, int, int, int, int, int, int, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, int, int, int, int, int, int, float, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_PAL_L00_00328480(float, void *, void *, int, int, void *, u32, int, float, float, float);
extern void func_0029F338(void *);
extern int D_L03_001AEBF8 __attribute__((sda));
extern int D_L03_001B1AD0 SDATA(D_L03_001B1AD0) __attribute__((sda));
extern float D_L03_001B1AB0[2] SDATA(D_L03_001B1AB0) __attribute__((sda));
extern float D_L03_001B1AA8[2] SDATA(D_L03_001B1AA8) __attribute__((sda));
extern float D_L03_001B1AA0[2] SDATA(D_L03_001B1AA0) __attribute__((sda));

void func_PAL_L03_0041EED8(u8 *e) {
    u8 *s = *(u8 **)(e + 0x68);
    float a[4] __attribute__((aligned(16)));
    Quad zero = 0;
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    int i;
    switch (e[0x20]) {
    case 0:
        func_00282F20(a, e+0xE0, *(float *)(e+0x2C)*20.0f);
        func_L00_0033E220(a, e, 0x28208080, -1, 0, -1, 0, 0x60, 367500.0f, 0.0f);
        func_L00_0033E220(a, e, 0x20208080, -1, 1, -1, 0, 0x60, 325500.0f, 0.75f);
        if (*(int *)s)
            --D_L03_001AEBF8;
        func_002A7750(e, 1, -1);
        break;
    case 1:
        if (func_002A9640(e, 0x4010000, 0) && !*(int *)s) {
            --D_L03_001AEBF8;
            func_002A7750(e, 2, -1);
        }
        e[0xA8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(e, D_L03_001B1AB0, D_L03_001B1AA8, D_L03_001B1AA0, 127, 0, D_L03_001B1AD0, 1, 65535, 255, 0);
        func_PAL_L00_003281C0(e, 1, 3.0f);
        *(Quad *)b = zero;
        func_L01_0031A278(e, a, 0, 0, *(float *)(e+0x2C)*20.0f);
        func_PAL_L00_003FB330(a, 0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 20.0f);
        func_PAL_002AC718(e, b, a, 0.0f, 0.0f, 15, 0, 0, 0.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, 9.0f, 1.0f, 0.0f);
        func_L01_0031A278(e, c, 0, 0, *(float *)(e+0x2C)*20.0f);
        for (i = 0; i < 4; i++) {
            float d[4] __attribute__((aligned(16)));
            d[0] = (i / 2 * 2 - 1) * 0.040000003f;
            d[1] = (i % 2 * 2 - 1) * 0.040000003f;
            d[2] = 0.080000006f;
            func_00283098(d, d, e+0xC0);
            func_PAL_L00_00328480(0.25f, e, c, 6, 1, d, 0x50404040, 0, 5, 0.75f, 1.25f);
        }
        if (D_L03_001B1AD0 >= 0) {
            *(u16 *)(e+0x7C)=(1<<D_L03_001B1AD0)|0x8000;
            func_002A7750(e, 3, -1);
        } else {
            func_0029F338(e);
        }
        break;
    }
}



