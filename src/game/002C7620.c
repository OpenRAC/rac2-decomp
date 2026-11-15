#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;

extern int func_00282978(void *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);

void func_002C7620(char *self) {
    Vec4 buf, offset;
    char *s0;
    char *s2 = self + 0x30;
    float t;
    int color;

    if (FastDecTimer(self + 0xA) != 0) {
        func_002B9180(self);
        return;
    }
    s0 = self + 0x10;
    buf.word = *(TI128 *)s0;
    FastVecAdd(s0, s0, s2);
    *(float *)(s2 + 8) = *(float *)(s2 + 8) - *(float *)(s2 + 0xC);
    t = FastVecLength(s2);
    vec_scale_to_length(&offset, s2, t * 0.4f);
    FastVecSub(self + 0x20, s0, &offset);
    *(float *)(self + 0x2C) = 1.0f;
    if (*(short *)(self + 0xA) < *(unsigned char *)(self + 8)) {
        t = IntToFloat(*(short *)(self + 0xA)) / IntToFloat(*(unsigned char *)(self + 8));
        color = (FloatToInt(t * 127.0f) << 24) | 0x00FFFFFF;
        *(int *)(self + 0xC) = color;
        *(int *)(self + 4) = color;
    }
}
