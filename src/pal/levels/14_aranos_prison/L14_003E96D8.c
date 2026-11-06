#include "include_asm.h"
#include "common.h"

/* func_PAL_L14_003E96D8, the PAL copy of func_L14_003E5218: the same C, where both ring heights
 * take the 50 Hz scale. */
void func_PAL_L14_003E96D8(char *self) {
    char *p = *(char **)(self + 0x68);
    short index = *(short *)(p + 0x16);
    if ((short)(index % 2) == 1) {
        int a = ((short *)p)[index];
        int b = ((short *)p)[(index + 1) % 8];
        char *obj;
        char *d;
        int green;
        obj = *(char **)(p + 0x28);
        if (obj) {
            d = *(char **)(obj + 0x68);
            *(int *)(d + 0x14) = *(short *)(p + 0x14) - ((s32)(a) * 5 + 2) / 6;
            *(int *)(d + 0x18) = ((s32)(a) * 5 + 2) / 6 - ((s32)(b) * 5 + 2) / 6;
            green = (*(short *)(p + 0x42) << 8) | 0x80000000;
            *(int *)(d + 0x30) = *(int *)(d + 0x38) = (*(short *)(p + 0x44) << 16) | green | *(short *)(p + 0x40);
            green = (*(short *)(p + 0x48) << 8) | 0x80000000;
            *(int *)(d + 0x34) = *(int *)(d + 0x3C) = (*(short *)(p + 0x4A) << 16) | green | *(short *)(p + 0x46);
            *(float *)(d + 0xC) = 1.0f;
        }
        obj = *(char **)(p + 0x2C);
        if (obj) {
            d = *(char **)(obj + 0x68);
            *(int *)(d + 0x14) = *(short *)(p + 0x14) - ((s32)(a) * 5 + 2) / 6;
            *(int *)(d + 0x18) = ((s32)(a) * 5 + 2) / 6 - ((s32)(b) * 5 + 2) / 6;
            green = (*(short *)(p + 0x42) << 8) | 0x80000000;
            *(int *)(d + 0x30) = *(int *)(d + 0x38) = (*(short *)(p + 0x44) << 16) | green | *(short *)(p + 0x40);
            green = (*(short *)(p + 0x48) << 8) | 0x80000000;
            *(int *)(d + 0x34) = *(int *)(d + 0x3C) = (*(short *)(p + 0x4A) << 16) | green | *(short *)(p + 0x46);
            *(float *)(d + 0xC) = 1.0f;
        }
    }
}

extern void func_L00_002E54E0(float);
extern int func_002B38B8(char *);
extern void func_L00_002E6EF8(void (*f)(char *), char *arg);
extern float func_002A7878(float, float);
extern void func_L14_003F0E68(char *);


/* func_PAL_L14_003F53E4, the PAL copy of func_L14_003F0D50: the same C, where both scroll
 * speeds are scaled by 1.2f for 50 Hz. */
void func_PAL_L14_003F53E4(char *arg0) {
    char *s2 = arg0;
    char *s1 = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) == 0) {
        *(int *)(s1 + 0x10) = 1;
        func_L00_002E54E0(2048.0f);
        *(unsigned char *)(arg0 + 0x20) = 1;
    }
    *(float *)(s1 + 0x0) = *(float *)(s1 + 0x0) + *(float *)(s1 + 0x4) * 1.2f;
    *(float *)(s1 + 0x8) = *(float *)(s1 + 0x8) + *(float *)(s1 + 0xC) * 1.2f;
    if (*(float *)(s1 + 0x0) >= 8.0f) {
        *(float *)(s1 + 0x0) = *(float *)(s1 + 0x0) - 8.0f;
    }
    if (*(float *)(s1 + 0x8) >= 8.0f) {
        *(float *)(s1 + 0x8) = *(float *)(s1 + 0x8) - 8.0f;
    }
    if (func_002B38B8(s2) != 0) {
        *(int *)(s1 + 0x10) = 0;
    }
    if (*(int *)(s1 + 0x10) != 0) {
        func_L00_002E6EF8(func_L14_003F0E68, s2);
    }
    *(float *)(s1 + 0x4) = func_002A7878(0.003f, 0.005f);
    *(float *)(s1 + 0xC) = func_002A7878(0.001f, 0.0025f);
}
