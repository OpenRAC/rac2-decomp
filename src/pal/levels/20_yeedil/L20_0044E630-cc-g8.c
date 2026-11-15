#include "names.h"
/* func_PAL_L20_0044E630, the PAL copy of func_L20_00448A18: the same C, where scale func_002A7820(D_L20_001B2388, D_L20_001B238C). */
#include "common.h"

extern void *CreateMoby(int);

extern void moby_init_child_from_parent(void *, void *);

extern float math_random_float_range(float, float);

extern void vec_random_direction(float *, float, float);

extern void func_002A0F48(void *);

extern int math_random_int_range(int, int);

extern float D_L20_001B2394 __attribute__((nosda));
extern float D_L20_001B2384 __attribute__((nosda));
extern float D_L20_001B237C __attribute__((nosda));
extern int D_L20_001B238C __attribute__((nosda));

extern float D_L20_001B2390 __attribute__((sda));
extern float D_L20_001B2380 __attribute__((sda));
extern int D_L20_001B2388 __attribute__((sda));
extern float D_L20_001B2378 __attribute__((sda));

char *func_PAL_L20_0044E630(char *arg0, char *arg1, char *arg2, char *arg3) {
    char *obj = (char *)CreateMoby(0x125A);
    char *state;
    float f;

    if (obj != 0) {
        state = *(char **)(obj + 0x68);
        moby_init_child_from_parent(obj, arg0);
        f = math_random_float_range(D_L20_001B2390, D_L20_001B2394);
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f;
        qcopy(obj + 0x10, arg1);
        qcopy(obj + 0xF0, arg2);
        qcopy(state, arg3);
        func_002A0F48(obj);
        vec_random_direction((float *)(state + 0x10), D_L20_001B2380 * 0.0003490659f,
                      D_L20_001B2384 * 0.0003490659f);
        f = math_random_float_range(D_L20_001B2378, D_L20_001B237C);
        *(float *)(state + 0x20) = f * 0.00040000002f;
        *(int *)(state + 0x24) = (((int)(math_random_int_range(D_L20_001B2388, D_L20_001B238C)) * 5 + 2) / 6);
    }
    return obj;
}
