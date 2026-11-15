/* func_002C27B0: own unit, the two 16-byte copies are qcopy() so the count at state + 4
 * is read after the first copy, as retail does. */
#include "common.h"
extern void func_002B9180(void *);
extern float func_002A7878(float, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0029FCC0(int, int, void *);
extern void func_00282CC0(char *, char *, char *);

typedef int V4 __attribute__((mode(TI)));

void func_002C27B0(char *self)
{
    V4 local;
    char *state = self + 0x30;
    char *sub = *(char **)(self + 0x30);
    float f0;
    float f21;
    float f22;
    int count;

    if (sub == 0)
        goto kill;
    if (*(short *)(sub + 0xAA) == *(int *)(state + 8)) {
        if (*(unsigned char *)(sub + 0x20) == 0xFE)
            goto kill;
        if (*(unsigned char *)(sub + 0x20) != 0xFD)
            goto cont;
    }
kill:
    func_002B9180(self);
    return;
cont:
    f0 = func_002A7878(0.5f, 1.0f);
    f22 = *(float *)(self + 0x2C);
    f21 = *(float *)(state + 0xC) * f0;
    qcopy(&local, self + 0x10);
    count = *(int *)(state + 4);
    if (count > 0) {
        func_0029FCC0(*(int *)(self + 0x30), count, self + 0x10);
    } else {
        qcopy(self + 0x10, (char *)*(int *)(self + 0x30) + 0x10);
    }
    if (1.5f < fast_vec_dist(self + 0x10, self + 0x20)) {
        FastVecSub(&local, &local, self + 0x10);
        vec_scale_to_length(&local, &local, 1.5f);
        FastVecAdd(self + 0x20, self + 0x10, &local);
    }
    *(float *)(self + 0x1C) = f21;
    *(float *)(self + 0x2C) = f22;
}
