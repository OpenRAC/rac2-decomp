#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L00_001AFFA4 MACRO_ADDR;
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern void vec_clear_128(Quad *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
/* Moves the child down its owner's local axis, fading it near the end of its life. */
void sheepinator_trail_update(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *owner, *ownerState;
    *(float *)(state + 4) += (D_L00_001AFFA4 + D_L00_001AFFA4) * 0.016666668f;
    if (math_fast_float_d((int *)(state + 8)) || D_L00_001AFFA4 * 1.1f <= *(float *)(state + 4)) {
        moby_mark_spawned(actor);
        return;
    }
    owner = *(char **)state;
    if (!owner || *(short *)(owner + 0xAA) != MOBY_CLASS_SHEEPINATOR || *(unsigned char *)(owner + 0x20) == 0xFE || *(unsigned char *)(owner + 0x20) == 0xFD) {
        moby_mark_spawned(actor);
        return;
    }
    ownerState = *(char **)(owner + 0x68);
    vec_clear_128((Quad *)(actor + 0x10));
    *(float *)(actor + 0x14) = -*(float *)(state + 4);
    matrix_mul_vec3(actor + 0x10, actor + 0x10, *(char **)state + 0xC0);
    FastVecAdd(actor + 0x10, actor + 0x10, ownerState);
    *(Quad *)(actor + 0xF0) = *(Quad *)(*(char **)state + 0xF0);
    if (*(float *)(state + 4) > D_L00_001AFFA4)
        *(unsigned char *)(actor + 0x23) = FloatToInt((1.0f - (*(float *)(state + 4) - D_L00_001AFFA4) * 10.0f) * 127.0f);
    *(float *)(actor + 0x2C) = *(float *)(state + 0xC) * 0.1f + (*(float *)(state + 0xC) * *(float *)(state + 4)) / D_L00_001AFFA4;
}
