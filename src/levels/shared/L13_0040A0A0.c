#include "common.h"
extern void func_L13_00409B08(char *, char *);
extern float func_00282E48(void *, void *);
extern float func_L02_00329410(char *, float *, const void *);
extern float func_002AFF38(char *, char *, char *);
extern void func_002AFD88(float, float, float, char *, char *);
extern char D_L13_001B2590[] MACRO_ADDR;

void func_L13_0040A0A0(char *object, char *state, char *target,
                       char *old_position, char *transform)
{
    int blocked = 0;
    char *position;
    float height;
    func_L13_00409B08(object, state);
    height = func_00282E48(object + 0x10, D_L13_001B2590);
    if (height < *(float *)(state + 0x90) - *(float *)(state + 8)) {
        *(int *)(state + 0x94) |= 2;
        blocked = 1;
    }
    if (((*(int *)(state + 0x38) ^ 1) & 1) && *(short *)(state + 0xc2) < 5) {
        if (*(float *)(state + 0x90) + *(float *)(state + 0xc) < height) {
            *(int *)(state + 0x94) |= 1;
            blocked = 1;
        }
    }
    if (*(short *)(state + 0xc0) != 0) {
        if (*(float *)(state + 0x10) < func_L02_00329410(object, (float *)(state + 0x50), 0)) {
            *(int *)(state + 0x94) |= 4;
            blocked = 1;
        }
    }
    position = object + 0x10;
    if (blocked) {
        qcopy(position, old_position);
        func_L13_00409B08(object, state);
        height = func_00282E48(position, D_L13_001B2590);
    }
    if (height <= *(float *)(state + 0x90) + 0.005f) {
        func_002AFF38(object, state + 0xa0, 0);
        if (transform != 0)
            func_002AFD88(0.0f, 0.0f, *(float *)(state + 0x90) - height, object, position);
        *(short *)(state + 0xc2) = 0;
        *(short *)(state + 0xc0) += 1;
    } else if (*(float *)(state + 0x90) + *(float *)(state + 0xc) <= height) {
        *(short *)(state + 0xc0) = 0;
        *(short *)(state + 0xc2) += 1;
    }
    {
        float distance = func_00282E48(position, target);
        *(float *)(state + 0xcc) = distance;
        if (distance <= *(float *)(state + 0x34))
            *(int *)(state + 0x94) |= 0x80;
    }
}
