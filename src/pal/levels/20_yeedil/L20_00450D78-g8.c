#include "names.h"
/* func_PAL_L20_00450D78, the PAL copy of func_L20_0044B100: the same C, where the motion
 * range constants are scaled by 6/5 and the rate takes the 50 Hz scale. */
/* Creates the child, copies both full vectors and initializes its motion.
 * Returns the created object or null; the fifth integer slot and float input are preserved. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2470 __attribute__((sda));
extern int D_L20_001B246C __attribute__((sda));

extern void *CreateMoby(int);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern float math_random_angle(void);
extern float math_random_float_range(float a, float b);
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void func_PAL_L11_00465FD0(char *, int);
extern int snd_play_from_class_bank(int, int, char *, int);

char *func_PAL_L20_00450D78(char *arg0, char *arg1, char *arg2, char *arg3, int arg4,
                        float f12) {
    char *obj;
    char *state;
    char *dst;
    TI128 buf;
    float r;

    obj = CreateMoby(0x12F7);
    if (obj != 0) {
        moby_init_child_from_parent((u8 *)obj, (u8 *)arg0);
        dst = obj + 0x10;
        qcopy(dst, arg1);
        *(float *)(obj + 0x2C) =
            *(float *)(*(u32 *)(obj + 0x24) + 0x24) * D_L20_001B2470;
        state = *(char **)(obj + 0x68);
        qcopy(state, arg2);
        *(float *)(state + 0x20) = f12;
        *(float *)(state + 0x24) = math_random_angle();
        *(float *)(state + 0x28) = math_random_float_range(0.062831864f, 0.12566373f);
        *(int *)(state + 0x30) = 0;
        r = IntToFloat(arg4);
        *(float *)(state + 0x34) = 1.0f / ((r * 5.0f + 2.0f) * 0.16666667f);
        FastVecScale(&buf, arg2, (float)(arg4 >> 1));
        FastVecAdd(&buf, &buf, arg1);
        FastVecSub(state + 0x10, arg3, &buf);
        r = FastVecLength(state);
        vec_scale_to_length(state + 0x10, state + 0x10, r);
        func_PAL_L11_00465FD0(dst, D_L20_001B246C);
        snd_play_from_class_bank(0, 0, obj, 0x12F7);
    }
    return obj;
}
