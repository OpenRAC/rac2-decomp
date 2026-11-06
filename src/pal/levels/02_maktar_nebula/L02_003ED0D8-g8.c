#include "include_asm.h"

/* func_PAL_L02_003ED0D8, the PAL copy of func_L02_003E8CE8: the same C and the same unit flags,
   where the spring's 1/3600 becomes 1/2500 and the damping divisor takes PAL's 50 Hz scale,
   (x * 5 + 2) / 6, in floats. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad000[0xE0];
    float vecE0[4];
    unsigned char pad0F0[0x5C0 - 0xF0];
    char *target5C0;
} Player003ED0D8;

extern char *D_L02_001B359C[3] __attribute__((sda));
extern float D_L02_001B0C00 __attribute__((sda));
extern float D_L02_001B0C04 __attribute__((sda));
extern float D_L02_001B0C08 __attribute__((sda));
extern float D_L02_001B0C0C __attribute__((sda));
extern Player003ED0D8 D_00189E20;

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA2E8(float *, float, float);

void func_PAL_L02_003ED0D8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *target = D_L02_001B359C[0] + (*(int *)state << 8);
    float pos[4];
    float vec[4];
    float diff[4];
    float spring[4];
    float damp[4];
    float step;
    float *q;
    float a;
    float b;

    *(TI128 *)pos = *(TI128 *)(arg0 + 0x10);
    pos[2] += D_L02_001B0C00;
    if (D_00189E20.target5C0 == target) {
        func_00282CF0(vec, D_00189E20.vecE0, pos);
        step = func_00282DF0(vec);
        func_002AA2E8(&step, 0.1f, D_L02_001B0C04);
        func_00282F20(vec, vec, step);
        func_00282CC0(vec, vec, pos);
    } else {
        *(TI128 *)vec = *(TI128 *)pos;
    }
    q = vec;
    func_00282CF0(diff, target + 0x10, q);
    a = func_00282DF0(diff);
    b = func_00282DF0(state + 0x10);
    a = a * 0.00040000002f;
    b = b / ((D_L02_001B0C0C * 5.0f + 2.0f) * 0.16666667f);
    func_00282F20(spring, diff, -(D_L02_001B0C08 * a));
    func_00282F20(damp, state + 0x10, -b);
    func_00282CC0(state + 0x10, state + 0x10, spring);
    func_00282CC0(state + 0x10, state + 0x10, damp);
    func_00282CC0(target + 0x10, target + 0x10, state + 0x10);
}
