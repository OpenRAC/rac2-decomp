#include "include_asm.h"

#include "common.h"
extern int math_fast_float_d(void *);
extern void group_sync_counter(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts_pal(void *, void *, int, void *, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern int math_fast_float_d(void *);

void func_PAL_L14_0042F0D8(unsigned char *self) {
    unsigned char *state = *(unsigned char **)(self + 0x68);
    float delta[4] __attribute__((aligned(16)));
    math_fast_float_d(state + 0x30c);
    math_fast_float_d(state + 0x310);
    if (*(unsigned short *)(self + 0x96) < 65535)
        ++*(unsigned short *)(self + 0x96);
    group_sync_counter(self, state + 0x308);
    FastVecSub(delta, self + 0x10, state + 0x2d0);
    qcopy(state + 0x2d0, self + 0x10);
    if (self[0x95] == 1) {
        *(float *)(state + 0x2fc) = FastAddRotations(*(float *)(state + 0x2fc), 0.25132746f);
        enemy_attach_turn_child_parts_pal(self, state + 0x300, 1, delta, *(float *)(state + 0x2fc));
    } else {
        *(float *)(state + 0x2fc) = FastAddRotations(*(float *)(state + 0x2fc), 0.013962637f);
        enemy_attach_turn_child_parts_pal(self, state + 0x300, 0, delta, *(float *)(state + 0x2fc));
    }
    func_PAL_002B14F8(self, state + 0x230, 7, 1, 2.0f);
}


