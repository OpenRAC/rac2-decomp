#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002833F0(u8 *, u8 *);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern float func_002A89A8(void *, int, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void func_0029F338(void *);

void func_PAL_L07_00415B88(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    TI128 effect;
    float length, ratio;
    switch (object[0x20]) {
    case 0:
        *(unsigned short *)(object + 0x34) |= 0x100;
        func_002833F0(object + 0xc0, object + 0xf0);
        if (*(int *)(state + 0xc) == 1) func_00282D30(object + 0xe0, object + 0xe0, 2.0f);
        else if (*(int *)(state + 0xc) == -1) func_00282D30(object + 0xe0, object + 0xe0, 0.5f);
        if (*(int *)(state + 0x24) == 0) {
            *(int *)(state + 0x10) = 0;
            *(int *)(state + 0x14) = 0;
            *(float *)(state + 0x18) = -(func_002A7878(3.0f, 6.0f) * 0.020000001f);
        } else func_00282D30(state + 0x10, state + 0x10, 0.020000001f);
        *(float *)(state + 4) = func_002A7878(13.0f, 20.0f) * 0.00040000002f;
        length = func_00282DF0(object + 0xe0);
        ratio = *(float *)(object + 0x2c) / *(float *)(*(char **)(object + 0x24) + 0x24);
        ratio *= length * -10.0f;
        *(float *)(state + 0x20) = ratio;
        if (*(float *)(state + 8) == 0.0f)
            *(float *)(state + 8) = func_002A89A8(object + 0x10, 0, 0.5f);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002A9640(object, 0x4010000, 0) && !*(int *)state)
            func_002A7750(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        func_00282CC0(object + 0x10, object + 0x10, state + 0x10);
        *(float *)(state + 0x18) -= *(float *)(state + 4);
        if (*(int *)(state + 0x24)) {
            func_L01_0031A278(object, &effect, 0.0f, 0.0f, *(float *)(state + 0x20));
            func_002A8C28(object, &effect, 0x4010000, 0, 1, 0, 2.0f * (*(float *)(object + 0x2c) / *(float *)(*(char **)(object + 0x24) + 0x24)), 8.0f, 1.0f);
        }
        if (*(float *)(object + 0x18) + *(float *)(state + 0x20) < *(float *)(state + 8))
            func_002A7750(object, 4, -1);
        break;
    case 4:
        func_002E5CF8(0, 0, object);
        if (object[0x31]) {
            effect = 0;
            ((float *)&effect)[2] = 0.060000002f;
            func_PAL_002B15D8(object, 3, &effect, 3.0f, 6.0f, 3.0f, 6.0f, 255);
        }
        func_0029F338(object);
        break;
    }
}
