#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *dst, void *src, void *src2);
extern void func_002A7750();
extern void func_L14_003DFA10();
extern int func_002B38B8();
extern int func_002B3868();
extern void func_002E5CF8();
extern void func_00282C98();
extern void func_00282CC0(void *dst, void *src, void *src2);
extern void func_00282DD8(void *dst, void *src, void *mtx);
extern void func_00282F20(void *dst, void *src, float s);
extern float func_00283B98(float a, float b);
extern float func_00282C48(float a);
extern void func_0029F338();
extern void func_L00_002E6CF0();
extern void func_L14_003DFA60();
extern float D_L14_001B0388 __attribute__((sda));
extern float D_L14_001B038C __attribute__((sda));
extern float D_L14_001B0390 __attribute__((sda));

void func_PAL_L14_003E3968(char *arg0) {
    char *v = *(char **)(arg0 + 0x68);

    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        func_002A7750(arg0, 1, -1);
        if (*(int *)(v + 0x0) != -1) {
            func_L14_003DFA10(arg0, 0);
        }
        break;
    case 1:
        if (func_002B38B8(arg0) != 0) {
            if (*(int *)(v + 0x0) != -1) {
                func_L14_003DFA10(arg0, 1);
            }
            func_002A7750(arg0, 2, -1);
            {
                float s = D_L14_001B0388 * 0.020000001f;

                *(float *)(v + 0xC) = s;
                if (*(int *)(v + 0x8) != 0) {
                    *(float *)(v + 0xC) = -s;
                }
            }
            *(int *)(v + 0x10) = 0;
        }
        break;
    case 2:
        {
            float a[4];
            float b[4];

            if (func_002B3868(arg0) != 0) {
                func_002E5CF8(0, 0, arg0);
            }
            func_00282C98(b);
            func_00282DD8(a, arg0 + 0xC0, b);
            func_00282F20(a, a, *(float *)(v + 0xC));
            func_00282CC0(arg0 + 0x10, arg0 + 0x10, a);
            {
                float old = *(float *)(v + 0xC);
                float m;

                *(float *)(v + 0x10) = *(float *)(v + 0x10) + old;
                if (*(int *)(v + 0x8) != 0) {
                    m = old - D_L14_001B038C * 0.00040000002f;
                } else {
                    m = old + D_L14_001B038C * 0.00040000002f;
                }
                {
                    float x = m * D_L14_001B0390;

                    *(float *)(v + 0xC) = m;
                    *(float *)(arg0 + 0xF0) = func_00283B98(*(float *)(arg0 + 0xF0), x);
                }
            }
            if (func_00282C48(*(float *)(v + 0x10)) > 4.0f) {
                func_0029F338(arg0);
                return;
            }
        }
        break;
    }
    if (*(unsigned char *)(arg0 + 0x31) != 0 && *(int *)(v + 0x4) != -1) {
        func_L00_002E6CF0(func_L14_003DFA60, arg0);
    }
}
