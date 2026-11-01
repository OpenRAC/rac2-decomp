#include "include_asm.h"



#include "common.h"
extern void func_002AFFD8(void *, void *, int);
extern char *func_0029EFD0(int);
extern void func_00282F20(float *, float *, float);
extern void func_00282DD8(float *, float *, float *);
extern void func_00282DD8(float *, float *, float *);
extern void func_00282F20(float *, float *, float);

/* func_L23_0041E5B0 is defined in its dedicated source unit. */

char *func_PAL_L23_00427920(char *pos, char *dir, float *damage) {
    char axis[16];
    char scaled[16];
    char *obj;
    char *state;
    func_002AFFD8(pos, axis, 1);
    obj = func_0029EFD0(0x118E);
    if (obj) {
        state = *(char **)(obj + 0x68);
        *(float *)(state + 0x1C) = *damage;
        *(int *)(state + 0x10) = 0x32;
        *(u8 *)(obj + 0x30) = 0xFF;
        *(u16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        qcopy(state, dir);
        *(int *)(state + 0x18) = 0;
        *(int *)(state + 0x14) = 0;
        func_00282F20((float *)scaled, (float *)dir, 1.0f);
        qcopy(obj + 0xC0, scaled);
        func_00282DD8((float *)(obj + 0xD0), (float *)(obj + 0xC0), (float *)axis);
        func_00282F20((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        func_00282DD8((float *)(obj + 0xE0), (float *)(obj + 0xD0), (float *)(obj + 0xC0));
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
    }
    return obj;
}


