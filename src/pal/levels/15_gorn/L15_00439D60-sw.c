#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int func_L00_00367720(void);
extern void func_L05_00379E60(void *, void *, int, int);
extern void func_L05_0037AE40(void *);
extern void func_PAL_L15_0043B0D8(char *);
extern void func_PAL_L15_0043A270(void *, int);
extern void func_PAL_L15_0043BB70(void);
extern void func_L15_00434D28(void *);
extern void func_PAL_L05_0042A240(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);
extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern s32 func_00283CF0(f32 a);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002E5CF8(int, int, void *);
extern int func_002A77E0(int);
extern void func_0029F338(void *);
extern void func_002833F0(void *, void *);

void func_PAL_L15_00439D60(unsigned char *object) {
    float point[4] __attribute__((aligned(16)));
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float ratio;
    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        if (!func_L00_00367720()) return;
        func_PAL_L15_0043B0D8((char *)object);
        if (*(int *)(state + 0x264))
            func_L05_00379E60(object, func_PAL_L15_0043BB70, 0, 0);
        qcopy(state + 0x430, object + 0x10);
        break;
    case 1:
        func_PAL_L15_0043A270(object, 0);
        break;
    case 2:
        func_PAL_L15_0043A270(object, 1);
        if (func_00282948(state + 0x274)) {
            object[0x20] = 3;
            *(int *)(state + 0x274) = 150;
        }
        break;
    case 3:
        func_PAL_L15_0043A270(object, 1);
        ratio = func_00283CE0(*(int *)(state + 0x274)) / func_00283CE0(150);
        object[0x23] = func_00283CF0((1.0f - ratio) * 95.0f) + 32;
        if (func_00282948(state + 0x274)) {
            *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
            object[0x20] = 4;
            *(int *)(state + 0x274) = 500;
            object[0x23] = 128;
            *(unsigned short *)(object + 0x34) &= 0xFFF7;
        }
        break;
    case 4:
        func_PAL_L15_0043A270(object, 0);
        if (func_00282948(state + 0x274)) {
            *(int *)(object + 0x98) = 0;
            object[0x20] = 5;
            *(int *)(state + 0x274) = 150;
            *(unsigned short *)(object + 0x34) |= 8;
        }
        break;
    case 5:
        func_PAL_L15_0043A270(object, 1);
        ratio = func_00283CE0(*(int *)(state + 0x274)) / func_00283CE0(150);
        object[0x23] = func_00283CF0(ratio * 95.0f) + 32;
        if (func_00282948(state + 0x274)) {
            *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
            object[0x20] = 2;
            *(int *)(state + 0x274) = 400;
            object[0x23] = 32;
        }
        break;
    case 6:
        point[0] = *(float *)(object + 0x10) + func_002A7878(-3.0f, 3.0f);
        point[1] = *(float *)(object + 0x14) + func_002A7878(-3.0f, 3.0f);
        point[2] = *(float *)(object + 0x18) + func_002A7878(-3.0f, 3.0f);
        if (*(int *)(state + 0x278) == 0) {
            func_PAL_L05_0042A240(point, 1, 24, 24, 24, 24, 24, 0, 3.0f, 1, 1, 1);
            *(int *)(state + 0x278) = 1;
        }
        if (func_002A77E0(12) == 0 && *(float *)(object + 0x18) > 350.0f)
            func_PAL_L05_0042A240(point, 0, 4, 4, 4, 4, 4, 0, 1.5f, 0, 0, 0);
        *(float *)(object + 0x18) -= *(float *)(state + 0x27C);
        *(float *)(state + 0x27C) += 0.00080000004f;
        *(float *)(state + 0x404) = func_00283B98(*(float *)(state + 0x404), 0.0017453296f);
        func_002833F0(object + 0xC0, state + 0x400);
        func_L15_00434D28(object);
        if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
            *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
            *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
            func_L05_0037AE40(object);
        break;
    case 7:
        func_00282CC0(object + 0x10, state + 0x410, object + 0x10);
        *(float *)(state + 0x418) -= 0.0044f;
        *(float *)(state + 0x404) = func_00283B98(*(float *)(state + 0x404), 0.031415932f);
        func_002833F0(object + 0xC0, state + 0x400);
        if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
            *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
            *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
            func_0029F338(object);
            return;
        }
        break;
    }
    func_00282948(state + 0x450);
}
