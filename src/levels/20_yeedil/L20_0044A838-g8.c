/* Advances the phase and restores the complete saved position before the height update. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2410 __attribute__((sda));
extern float D_L20_001B2414 __attribute__((sda));
extern float D_L20_001B241C __attribute__((sda));

extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002A9288(char *, float);
extern void func_L20_0044AA88(char *);

/* Ends each turret frame: counts the frame, bobs the turret up and down, and turns its aim. */
void func_L20_0044A838(char *moby) {
    char *state = *(char **)(moby + 0x68);
    u16 frame = *(u16 *)(moby + 0x96);
    float phase;

    *(u16 *)(moby + 0x96) = frame + 1;
    if (*(u8 *)(moby + 0x31)) {
        qcopy((moby + 0x10), (state + 0x180));
        phase = D_L20_001B2414;
        phase = FastAddRotations(*(float *)(state + 0x1A0), phase * 0.000290888245f);
        *(float *)(state + 0x1A0) = phase;
        phase = FastSinOrCosB(phase);
        {
            float amount = D_L20_001B241C;
            *(float *)(moby + 0x18) = *(float *)(moby + 0x18) + D_L20_001B2410 * phase;
            QueueGroundShadow(moby, amount);
        }
    }
    if (((*(u16 *)(moby + 0x34)) ^ 1) & 1) {
        TurnTurretTowardTarget(moby);
    }
}
