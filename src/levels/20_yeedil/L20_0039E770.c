#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern float func_00282E80(const void *, const void *);
extern void func_L20_0039E9F8(unsigned char *);

/* Turns the trooper toward its target, tilts it up or down to aim, then runs the move step. */
void func_L20_0039E770(unsigned char *object) {
    Vector position;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    if (*(unsigned short *)(object + 0x96) < 65000)
        ++*(unsigned short *)(object + 0x96);
    *(float *)(state + 0xF8) = FastMatrixHelperA(*(float *)(state + 0x50) - *(float *)(object + 0x10),
                                           *(float *)(state + 0x54) - *(float *)(object + 0x14));
    *(float *)(state + 0xF8) = fast_subtract_rotations(*(float *)(state + 0xF8), *(float *)(object + 0xF8));
    UpdateEasedNode(object, state + 0x90, 0, 0.03f, 0.3f);
    position.q = *(Quadword *)(object + 0x10);
    position.f[2] += 2.0f;
    *(float *)(state + 0x174) = -FastMatrixHelperA(vec_distance_xy(&position, state + 0x50),
                                            *(float *)(state + 0x58) - position.f[2]);
    UpdateEasedNode(object, state + 0x110, 1, 0.03f, 0.3f);
    SwingObjectAlongArc(object);
}
