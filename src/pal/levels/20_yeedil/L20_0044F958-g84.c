#include "include_asm.h"

#include "common.h"
extern int D_L20_001A8F00;
extern int D_L20_001C0418 NOT_SDA;
extern float D_L20_001B2468 __attribute__((sda));
extern int D_L20_001B2460 __attribute__((sda));
extern void func_0029F338(void *object);
extern float func_00283B98(float, float);
extern void func_00282D08(float *out, char *a, char *b, float k);
extern float func_002AA2E8(float *p, float v, float w);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_002A7750(char *object, int a1, int a2);
extern void func_00282D30(void *dst, void *src, float value);
extern void func_00282C88(void *target);
extern float func_002A7878(float lo, float hi);
extern void *func_002C65A0(void *, void *, float, float, float, int, int, int, int, int,
                           int);
extern int func_002A8C28(char *, char *, int, int, float, float, float, int, int);
extern void func_PAL_L00_003FB330(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L11_0045FEF8(void *);

void func_PAL_L20_00450AD0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float buf20[4] __attribute__((aligned(16)));
    float buf30[4] __attribute__((aligned(16)));
    float buf40[4] __attribute__((aligned(16)));
    float buf50[4] __attribute__((aligned(16)));
    u8 mode;

    if (D_L20_001A8F00 == 2) {
        func_0029F338(arg0);
        return;
    }
    mode = *(u8 *)(arg0 + 0x20);
    switch (mode) {
    case 0: {
        char *base;
        float v = *(float *)(state + 0x28);
        float a;
        float b;

        base = arg0 + 0x10;
        *(float *)(arg0 + 0xF0) =
            func_00283B98(*(float *)(arg0 + 0xF0), v * 0.7f);
        *(float *)(arg0 + 0xF4) = func_00283B98(
            *(float *)(arg0 + 0xF4), *(float *)(state + 0x28) * 0.5f);
        *(float *)(arg0 + 0xF8) = func_00283B98(
            *(float *)(arg0 + 0xF8), *(float *)(state + 0x28));
        func_00282D08(buf30, state, state + 0x10,
                      *(float *)(state + 0x30));
        func_002AA2E8((float *)(state + 0x30), 1.0f, *(float *)(state + 0x34));
        func_00282CC0(buf20, base, buf30);
        if (func_00277258(buf20, 0, arg0, D_L20_001B2468) != 0) {
            int id = D_L20_001C0418;

            if (id != 0 && id != *(int *)(arg0 + 0xB8)) {
                func_002A7750(arg0, 1, -1);
                break;
            }
        }
        qcopy(arg0 + 0x10, buf20);
        func_00282D30(buf40, state, -0.5f);
        func_00282C88(buf50);
        a = func_002A7878(2.5f, 3.0f) * 210000.0f;
        b = func_002A7878(0.2f, 0.4f) * 210000.0f;
        func_002C65A0(arg0 + 0x10, buf40, a, b, 0.0f, 0xF,
                      D_L20_001B2460, 3, 0x50, 0, 0);
    } break;
    case 1: {
        char *base;
        base = arg0 + 0x10;
        func_002A8C28(arg0, base, 0x10001, 0, 3.0f, *(float *)(state + 0x20),
                      1.0f, 1, 0);
        func_PAL_L00_003FB330(base, 1, 0xA, 0xA, 0xA, 0xA, 0xA, 0, 2.0f, 20.0f, mode,
                      mode, 0, 0);
        func_0029F338(arg0);
        return;
    }
    }
    func_L00_002E6EF8(&func_L11_0045FEF8, arg0);
}
