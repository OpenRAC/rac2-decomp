/* func_PAL_L20_00450D78, the PAL copy of func_L20_0044B100: the same C, where the motion
 * range constants are scaled by 6/5 and the rate takes the 50 Hz scale. */
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
extern void func_PAL_L11_00465FD0(char *, int);
extern int func_002E5DA0(int, int, char *, int);

char *func_PAL_L20_00450D78(char *arg0, char *arg1, char *arg2, char *arg3, int arg4,
                        float f12) {
    char *obj;
    char *state;
    char *dst;
    TI128 buf;
    float r;

    obj = func_0029EFD0(0x12F7);
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
        *(float *)(state + 0x28) = func_002A7878(0.062831864f, 0.12566373f);
        *(int *)(state + 0x30) = 0;
        r = func_00283CE0(arg4);
        *(float *)(state + 0x34) = 1.0f / ((r * 5.0f + 2.0f) * 0.16666667f);
        func_00282D30(&buf, arg2, (float)(arg4 >> 1));
        func_00282CC0(&buf, &buf, arg1);
        func_00282CF0(state + 0x10, arg3, &buf);
        r = func_00282DF0(state);
        func_00282F20(state + 0x10, state + 0x10, r);
        func_PAL_L11_00465FD0(dst, D_L20_001B246C);
        func_002E5DA0(0, 0, obj, 0x12F7);
    }
    return obj;
}
