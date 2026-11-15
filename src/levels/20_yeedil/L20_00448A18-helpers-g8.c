#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int);

extern void func_002B37E8(void *, void *);

extern float func_002A7878(float, float);

extern void func_002A7A00(float *, float, float);

extern void func_002A0F48(void *);

extern int func_002A7820(int, int);

extern float D_L20_001B2394 __attribute__((nosda));
extern float D_L20_001B2384 __attribute__((nosda));
extern float D_L20_001B237C __attribute__((nosda));
extern int D_L20_001B238C __attribute__((nosda));

extern float D_L20_001B2390 __attribute__((sda));
extern float D_L20_001B2380 __attribute__((sda));
extern int D_L20_001B2388 __attribute__((sda));
extern float D_L20_001B2378 __attribute__((sda));

/* Creates a small piece of debris (moby class 4698) at the given place with a random size and spin. Returns the new object. */
char *func_L20_00448A18(char *owner, char *position, char *rotation, char *velocity) {
    char *obj = (char *)CreateMoby(0x125A /* moby class 4698 */);
    char *state;
    float f;

    if (obj != 0) {
        state = *(char **)(obj + 0x68);
        InitChildObjectFromParent(obj, owner);
        f = RandomFloatRange(D_L20_001B2390, D_L20_001B2394);
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f;
        qcopy(obj + 0x10, position);
        qcopy(obj + 0xF0, rotation);
        qcopy(state, velocity);
        func_002A0F48(obj);
        RandomDirectionVector((float *)(state + 0x10), D_L20_001B2380 * 0.000290888245f,
                      D_L20_001B2384 * 0.000290888245f);
        f = RandomFloatRange(D_L20_001B2378, D_L20_001B237C);
        *(float *)(state + 0x20) = f * 0.00027777778f;
        *(int *)(state + 0x24) = RandomIntRange(D_L20_001B2388, D_L20_001B238C);
    }
    return obj;
}
