/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G16 -Wa,-G16 -ffunction-sections.
 * us: 11_joba: 1148 bytes, expected 1156; us2: 11_joba: 1148 bytes, expected 1156; pal: ABSENT.
 * All eight jump-table destinations were decoded. Complete initialization, forward/backward
 * motion, animation timers and child tracking retain full four-vector storage and three-row
 * child basis copies. The shared delay word is read through its measured int/halfword views; the
 * GP offset vector is a complete 16-byte object. Switch layout and pointer lifetimes differ.
 * Reopen: Independent child-basis copy and switch lifetime witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
typedef union { int word; u16 half; } Delay;
extern u16 D_L11_001B0D90 __attribute__((sda));
extern float D_L11_001B0D94 __attribute__((sda));
extern Delay D_L11_001B0D98 __attribute__((sda));
extern float D_L11_001B0DA0[4] __attribute__((sda));
extern void func_002A7750(void *,int,int),func_002A7470(void *,int,int,int);
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern void func_00283098(void *,void *,void *),func_0029FCC0(void *,int,void *);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(void *),func_002A10E8(void *),func_002AB028(void *);
extern int func_002B3868(void *),func_00282978(void *);
extern void func_L11_00417340(void *);

/* Eight measured jump-table states; the child receives a complete three-row basis. */
void func_L11_00416D70(u8 *object)
{
    struct {float original[4], step[4], point[4], offset[4];} f;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *child;
    int i;
    qcopy(f.original, object + 0x10);
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x10) = 0; *(int *)(state + 0x14) = 0; *(int *)(state + 0x18) = 0;
        func_002A7750(object, 2, -1);
        if (object[0x43]) func_002A7470(object, 0, 0, 0);
        *(int *)(object + 0x48) = 0;
        func_00282F20(f.step, object + 0xD0, D_L11_001B0D94);
        func_00282CC0(object + 0x10, object + 0x10, f.step);
        qcopy(state, object + 0x10);
        child = func_0029EFD0(0x1172);
        *(u8 **)(state + 0x1C) = child;
        if (!child) return;
        *(u16 *)(child + 0x34) |= 0x41;
        child[0x30] = object[0x30];
        *(u16 *)(child + 0x32) = 0;
        func_0029FCC0(object, 0, f.point);
        func_00283098(f.offset, D_L11_001B0DA0, object + 0xC0);
        func_00282CC0(f.point, f.offset, f.point);
        child = *(u8 **)(state + 0x1C);
        qcopy(child + 0x10, f.point);
        func_002A0F48(child);
        child = *(u8 **)(state + 0x1C);
        for (i = 0; i < 3; i++) qcopy(child + 0xC0 + i * 16, object + 0xC0 + i * 16);
        func_002AB028(child + 0xC0);
        func_002A10E8(*(u8 **)(state + 0x1C));
        child = *(u8 **)(state + 0x1C);
        *(u16 *)(child + 0x34) |= 6;
        break;
    case 1:
        if (func_002B3868(object)) *(u16 *)(state + 0x22) = D_L11_001B0D98.half;
        if (!func_00282978(state + 0x22)) {
            func_00282F20(f.step, object + 0xD0, D_L11_001B0D94 / (float)D_L11_001B0D98.word);
            func_00282CC0(object + 0x10, object + 0x10, f.step);
        }
        if (object[0x60] & 2) {
            qcopy(object + 0x10, state);
            *(int *)(object + 0x48) = 0;
            func_002A7750(object, 2, -1);
        }
        break;
    case 2: break;
    case 3:
        if (func_002B3868(object)) *(u16 *)(state + 0x22) = D_L11_001B0D98.half;
        if (!func_00282978(state + 0x22)) {
            func_00282F20(f.step, object + 0xD0, -D_L11_001B0D94 / (float)D_L11_001B0D98.word);
            func_00282CC0(object + 0x10, object + 0x10, f.step);
        }
        if (object[0x60] & 2) {
            *(int *)(object + 0x48) = 0;
            func_002A7750(object, 4, -1);
        }
        break;
    case 4:
        func_002A7750(object, 5, -1);
        *(float *)(object + 0x48) = 1.0f;
        if (object[0x43] != 1) func_002A7470(object, 1, 0, 0);
        func_L11_00417340(object);
        break;
    case 5:
        if (object[0x60] & 2) {
            *(u16 *)(state + 0x20) = D_L11_001B0D90;
            *(int *)(object + 0x48) = 0;
            func_002A7750(object, 6, -1);
        }
        break;
    case 6:
        if (*(short *)(state + 0x20) == 0) {
            *(float *)(object + 0x48) = 1.0f;
            if (object[0x43] != 2) func_002A7470(object, 2, 0, 0);
            func_002A7750(object, 7, -1);
        } else func_00282978(state + 0x20);
        break;
    case 7:
        if (object[0x60] & 2) {
            if (object[0x43] != 3) func_002A7470(object, 3, 0, 0);
            func_002A7750(object, 1, -1);
        }
        break;
    }
    if (*(u8 **)(state + 0x1C) && *(float *)(object + 0x48) != 0.0f) {
        func_0029FCC0(object, 0, f.step);
        func_00283098(f.point, D_L11_001B0DA0, object + 0xC0);
        func_00282CC0(f.step, f.point, f.step);
        child = *(u8 **)(state + 0x1C);
        qcopy(child + 0x10, f.step);
        func_002A0F48(child);
        child = *(u8 **)(state + 0x1C);
        for (i = 0; i < 3; i++) qcopy(child + 0xC0 + i * 16, object + 0xC0 + i * 16);
        func_002AB028(child + 0xC0);
        func_002A10E8(*(u8 **)(state + 0x1C));
        child = *(u8 **)(state + 0x1C);
        *(u16 *)(child + 0x34) |= 6;
    }
}
