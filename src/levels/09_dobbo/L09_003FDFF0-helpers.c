#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283DB8(float *, float);
extern void func_0029FC20(char *, int, char *);
extern void func_00282F20(float *, float *, float);

void func_L09_003FDFF0(unsigned char *a0) {
    unsigned char *s1 = a0;
    unsigned char *s2 = *(unsigned char **)(s1 + 0x68);
    float buf[4] __attribute__((aligned(16)));
    if (func_002A77E0(5) == 0)
        return;
    qcopy(buf, s1 + 0x10);
    buf[3] = 4.0f;
    if (func_00283DB8(buf, IntToFloat(*(short *)(s1 + 0x32))) == -1)
        return;
    func_0029FC20((char *)s1, 1, (char *)(s2 + 0x340));
    vec_scale_to_length((float *)(s2 + 0x340), (float *)(s2 + 0x340), 1.0f);
    vec_scale_to_length((float *)(s2 + 0x350), (float *)(s2 + 0x350), 1.0f);
    vec_scale_to_length((float *)(s2 + 0x360), (float *)(s2 + 0x360), 1.0f);
    *(int *)(s2 + 0x42C) = 2;
}
