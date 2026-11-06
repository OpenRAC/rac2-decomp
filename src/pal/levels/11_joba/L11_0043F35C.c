/* func_PAL_L11_0043F9A8, the PAL copy of func_L11_0043A3F8: the same C, where the value at 0xAC and
   the four func_002B60B0 arguments take their 50 Hz values. */
#include "common.h"

extern int func_00283CF0(float);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_L11_004400D0(char *);
extern void func_PAL_002B1A50(char *, char *, int);
extern int func_002B3BA8(char *, int, int, int, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
extern char D_L11_001BA8C0[];

void func_PAL_L11_0043F9A8(char *object) {
    char *state = *(char **)(object + 0x68);

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(state + 0x48) = func_00283CF0(15.0f);
        *(unsigned char *)(state + 0x4A) = func_00283CF0(12.0f);
        *(float *)(state + 0x1A0) = 1.0f;
        *(unsigned char *)(state + 0x180) = 6;
        *(int *)(state + 0x1B8) = 2;
        *(float *)(state + 0x1AC) = 0.15f;
        *(float *)(state + 0x80) = 1.0f;
        *(float *)(state + 0x84) = 0.4f;
        *(float *)(state + 0x88) = 0.3f;
        *(float *)(state + 0x8C) = 0.3f;
        *(float *)(state + 0x90) = 1.5707965f;
        *(float *)(state + 0xB0) = 0.52359885f;
        *(float *)(state + 0xB4) = 2.0f;
        *(float *)(state + 0xAC) = 0.004f;
        *(int *)(state + 0x1A4) = 0;
        func_002B60B0(object, 0.4f, 0.40000004f,
                      0.0025132746f, 0.062831864f);
        if (*(short *)(state + 0x24) == 0) {
            *(short *)(state + 0x24) = 10;
            *(float *)(state + 0x20) = 10;
        }
        if (*(unsigned char *)(object + 0x43) != 1)
            func_PAL_002A7E68(object, 1, 0, 0);
        func_002A7750(object, 1, -1);
        func_PAL_L11_004400D0(object);
    }
    if (*(unsigned char *)(object + 0x20) >= 4)
        func_PAL_002B1A50(object, state + 0x170, 0);
    if (*(unsigned char *)(object + 0x20) >= 3 &&
        *(unsigned char *)(state + 0x2E) == 2)
        func_PAL_L11_004400D0(object);
    *(int *)(state + 0x2D8) = func_002B3BA8(object, *(int *)(state + 0x2E8),
                                         0, 0, 255.0f, 255.0f);
    if (*(unsigned char *)(object + 0x31) != 0) {
        if (func_00282E48(object + 0x10, D_L11_001BA8C0) < 48.0f) {
            func_002A93B0(object);
            *(unsigned char *)(object + 0x6F) = 45;
        }
    }
}

