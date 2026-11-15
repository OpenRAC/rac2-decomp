#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2168 __attribute__((sda));
extern float D_L20_001B216C __attribute__((sda));
extern float D_L20_001B2170 __attribute__((sda));

extern void *func_0029EFD0(int);
extern void func_002B37E8(char *, char *);
extern void func_002833F0(char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_00282DD8(char *, char *, char *);
extern float func_00283198(float);
extern void func_002ACE78(float *, float *, float);
extern float func_L00_0031CDD0(char *, char *, float *, float, float);
extern int func_00283CF0(float);
extern void func_L20_00443908(char *);

char *func_L20_00443790(char *arg0, int arg1, char *arg2) {
    char *obj = (char *)CreateMoby(arg1);
    char *state;
    char *p;
    float f20;
    float f21;
    float local;
    unsigned short flags;

    if (obj != 0) {
        func_002B37E8(obj, arg0);
        qcopy(obj + 0xF0, arg0 + 0xF0);
        euler_rotation_basis(obj + 0xC0, obj + 0xF0);
        flags = *(unsigned short *)(obj + 0x34);
        flags |= 0x100;
        flags &= 0xEFDF;
        state = *(char **)(obj + 0x68);
        f20 = D_L20_001B2168 * 0.0166666675f;
        f21 = D_L20_001B216C * 0.000277777785f;
        p = state + 0x10;
        *(unsigned short *)(obj + 0x34) = flags;
        local = 0.0f;
        FastVecSub(state, arg2, obj + 0x10);
        *(float *)(state + 8) = 0.0f;
        vec_scale_to_length(state, state, f20);
        FastVecCross(p, state, obj + 0xE0);
        func_002ACE78((float *)p, (float *)p, func_00283198(D_L20_001B2170 * 0.000290888245f));
        *(float *)(state + 8) = func_L00_0031CDD0(obj + 0x10, arg2, &local, f20, -f21);
        *(float *)(state + 0x20) = f21;
        *(int *)(state + 0x24) = FloatToInt(local);
        *(void (**)(char *))(obj + 0x64) = func_L20_00443908;
    }
    return obj;
}
