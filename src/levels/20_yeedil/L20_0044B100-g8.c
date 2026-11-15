/* Creates the child, copies both full vectors and initializes its motion.
 * Returns the created object or null; the fifth integer slot and float input are preserved. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2470 __attribute__((sda));
extern int D_L20_001B246C __attribute__((sda));

extern void *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern float func_002A7940(void);
extern float func_002A7878(float a, float b);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L11_00460258(char *, int);
extern int func_002E5DA0(int, int, char *, int);

char *func_L20_0044B100(char *arg0, char *arg1, char *arg2, char *arg3, int arg4,
                        float f12) {
    char *obj;
    char *state;
    char *dst;
    TI128 buf;
    float r;

    obj = CreateMoby(0x12F7);
    if (obj != 0) {
        func_002B37E8((u8 *)obj, (u8 *)arg0);
        dst = obj + 0x10;
        qcopy(dst, arg1);
        *(float *)(obj + 0x2C) =
            *(float *)(*(u32 *)(obj + 0x24) + 0x24) * D_L20_001B2470;
        state = *(char **)(obj + 0x68);
        qcopy(state, arg2);
        *(float *)(state + 0x20) = f12;
        *(float *)(state + 0x24) = func_002A7940();
        *(float *)(state + 0x28) = func_002A7878(0.052359886f, 0.10471977f);
        *(int *)(state + 0x30) = 0;
        r = IntToFloat(arg4);
        *(float *)(state + 0x34) = 1.0f / r;
        FastVecScale(&buf, arg2, (float)(arg4 >> 1));
        FastVecAdd(&buf, &buf, arg1);
        FastVecSub(state + 0x10, arg3, &buf);
        r = FastVecLength(state);
        vec_scale_to_length(state + 0x10, state + 0x10, r);
        func_L11_00460258(dst, D_L20_001B246C);
        func_002E5DA0(0, 0, obj, 0x12F7);
    }
    return obj;
}
