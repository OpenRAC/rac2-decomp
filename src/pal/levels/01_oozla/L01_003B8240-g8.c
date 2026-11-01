#include "include_asm.h"

#include "common.h"
extern char *D_L01_001B255C MACRO_ADDR;
extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);

void func_PAL_L01_003B8240(char *object)
{
    float position[4], offset[4], matrix[16];
    char *state = *(char **)(object + 0x68);
    char *target;
    int index = *(int *)(state + 0x384);
    if (index != -1) {
        target = D_L01_001B255C + (index << 8);
        if (target == 0) return;
        if (*(short *)(target + 0xAA) == 0xA56) {
            if (func_00282E80(object + 0x10, target + 0x10) > 1.0f) {
                func_00282CF0(offset, object + 0x10, target + 0x10);
                func_00282F20(offset, offset, 1.0f);
                func_00282CC0(position, target + 0x10, offset);
            } else {
                qcopy(position, (object + 0x10));
            }
            if (position[2] < *(float *)(target + 0x18) + 0.01f)
                position[2] = *(float *)(target + 0x18) + 0.011f;
        } else if (*(short *)(target + 0xAA) == 0xA53) {
            func_00283698(matrix, target + 0xC0);
            func_00282CF0(offset, object + 0x10, target + 0x10);
            func_002830C0(offset, offset, matrix);
            if (offset[0] > 2.0f) offset[0] = 2.0f;
            else if (offset[0] < -2.0f) offset[0] = -2.0f;
            if (offset[1] > 5.0f) offset[1] = 5.0f;
            else if (offset[1] < -5.0f) offset[1] = -5.0f;
            if (offset[2] < 0.01f) offset[2] = 0.01f;
            func_00283098(offset, offset, target + 0xC0);
            func_00282CC0(position, target + 0x10, offset);
        } else {
            qcopy(position, (object + 0x10));
        }
        func_00282CF0(offset, position, object + 0x10);
        func_00282FB8(offset, offset, 0.120000005f);
        func_00282CC0(object + 0x10, object + 0x10, offset);
    } else {
        char *attached = *(char **)(state + 0x198);
        if (attached && (*(short *)(attached + 0xAA) == 0xA56 || *(short *)(attached + 0xAA) == 0xA53))
            *(int *)(state + 0x384) = (attached - D_L01_001B255C) >> 8;
    }
}
