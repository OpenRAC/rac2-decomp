#include "include_asm.h"

#include "common.h"
extern int math_fast_float_d(void *);
extern void group_sync_counter(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastAddRotations(float, float);
extern void enemy_attach_turn_child_parts_pal(void *, void *, int, void *, float);
extern void value_set_and_smooth_pal(void *, void *, int, int, float);
extern int math_fast_float_d(void *);

/* Spins the climbing enemy's parts to follow its movement each frame (faster while in state 1). */
void climbing_enemy_update_parts_pal(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float delta[4] __attribute__((aligned(16)));
    math_fast_float_d(vars + 0x30c);
    math_fast_float_d(vars + 0x310);
    if (*(unsigned short *)(moby + 0x96) < 65535)
        ++*(unsigned short *)(moby + 0x96);
    group_sync_counter(moby, vars + 0x308);
    FastVecSub(delta, moby + 0x10, vars + 0x2d0);
    qcopy(vars + 0x2d0, moby + 0x10);
    if (moby[0x95] == 1) {
        *(float *)(vars + 0x2fc) = FastAddRotations(*(float *)(vars + 0x2fc), 0.25132746f);
        enemy_attach_turn_child_parts_pal(moby, vars + 0x300, 1, delta, *(float *)(vars + 0x2fc));
    } else {
        *(float *)(vars + 0x2fc) = FastAddRotations(*(float *)(vars + 0x2fc), 0.013962637f);
        enemy_attach_turn_child_parts_pal(moby, vars + 0x300, 0, delta, *(float *)(vars + 0x2fc));
    }
    value_set_and_smooth_pal(moby, vars + 0x230, 7, 1, 2.0f);
}


