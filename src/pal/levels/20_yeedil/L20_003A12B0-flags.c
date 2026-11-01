#include "include_asm.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern float func_00282E80(const void *, const void *);
extern void func_PAL_L20_003A1940(unsigned char *);

void func_PAL_L20_003A16B8(unsigned char *object) {
    Vector position;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    if (*(unsigned short *)(object + 0x96) < 65000)
        ++*(unsigned short *)(object + 0x96);
    *(float *)(state + 0xF8) = func_00283248(*(float *)(state + 0x50) - *(float *)(object + 0x10),
                                           *(float *)(state + 0x54) - *(float *)(object + 0x14));
    *(float *)(state + 0xF8) = func_00283BE0(*(float *)(state + 0xF8), *(float *)(object + 0xF8));
    func_002AEC48(object, state + 0x90, 0, 0.0432f, 0.43200004f);
    position.q = *(Quadword *)(object + 0x10);
    position.f[2] += 2.0f;
    *(float *)(state + 0x174) = -func_00283248(func_00282E80(&position, state + 0x50),
                                            *(float *)(state + 0x58) - position.f[2]);
    func_002AEC48(object, state + 0x110, 1, 0.0432f, 0.43200004f);
    func_PAL_L20_003A1940(object);
}
