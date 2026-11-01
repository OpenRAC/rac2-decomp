#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L18_001B1B40[16] __attribute__((sda));
extern int D_L18_001B1B30 __attribute__((sda));
extern float D_L18_001B1B08[2] __attribute__((sda));
extern float D_L18_001B1B00[2] __attribute__((sda));
extern float D_L18_001B1B10[4] __attribute__((sda));
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_L17_00326F38(void *, void *, float, float, float);
extern void func_L00_0033E220(void *, void *, int, int, int, int, int, int, float, float);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern int func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern float func_002A7878(float, float);
extern void func_0029F338(void *);

void func_PAL_L18_00441B80(u8 *obj) {
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68), *p;
    int i, x, y;
    float *q, *ap, *bp;

    switch (obj[0x20]) {
    case 0:
        i = 0;
        bp = b;
        ap = a;
        y = 20;
        x = 4;
        q = D_L18_001B1B40;
        for (; i < 4; i++, y -= 8, x -= 8, q += 4) {
            func_00282D30(v, q, *(float *)(obj + 0x2C));
            func_L00_0033E220(v, obj, 0x28808080, -1, 0, -1, 0, 0x60,
                             *(float *)(obj + 0x2C) * 1050000.f, .15f);
            func_L00_00324F18(obj, ap, q[0], q[1], q[2]);
            qcopy(bp, ap);
            if (i < 2) {
                func_L17_00326F38(obj, bp, (float)x, 0, -4.f);
            } else {
                func_L17_00326F38(obj, bp, 0, (float)y, -4.f);
            }
            a[3] = .2f;
            b[3] = 1.f;
        }
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        p = func_002A9640(obj, 0x4010000, 0);
        if (p && !*(int *)state) {
            *(TI128 *)b = 0;
            b[0] = 3.f;
            b[1] = 3.f;
            *(float *)(p + 0x18) = .75f;
            func_00282D30(v, p + 0x10, func_002A7878(6.f, 8.f));
            qcopy(a, v);
            func_00282CF0(v, v, b);
            func_00282CC0(a, a, b);
            func_PAL_L00_0032C328(obj, v, D_L18_001B1B08, D_L18_001B1B00,
                             0xFFFF, -1, D_L18_001B1B30, 9, -128, 255, 0);
            func_002A7750(obj, 2, -1);
        }
        obj[0xA8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(obj, D_L18_001B1B10, D_L18_001B1B08, D_L18_001B1B00,
                         0xFFFF, 0, D_L18_001B1B30, 6, 0xFA7F, 255, 0);
        func_L00_00324F18(obj, v, 0, 0, 20.f);
        func_PAL_L00_003FB330(v, 0, 5, 5, 5, 5, 5, 0, 1, 0, 1, 0,
                      *(float *)(obj + 0x2C) * 2.f, 20.f);
        func_0029F338(obj);
        break;
    }
}
