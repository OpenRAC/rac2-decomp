/* Updates motion and clamps the independent yaw and pitch components.
 * Full position transfers use the approved helper; the measured speed local is scalar. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B2444 __attribute__((sda));

extern float D_L20_001B2448 __attribute__((sda));

extern float D_L20_001B244C __attribute__((sda));

extern float func_00282DF0(void *);

extern void func_002AAC80(void *, float, float, float, float);

extern void func_002AFDD8(char *, char *, char *, char *);

extern int func_L07_00321D68(char *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Moves the turret toward its target spot, works out how far it must turn, and returns the distance still to go. */
float func_L20_0044A8F0(char *moby) {
    char *state = *(char **)(moby + 0x68);
    char *savedPos = state + 0x180;
    char *position = moby + 0x10;
    float toTarget[4] __attribute__((aligned(16)));
    float aimDelta[4] __attribute__((aligned(16)));
    float speed;
    float distance;
    float yaw;
    float turnGain;
    float pitch;

    FastVecSub(toTarget, state + 0x190, state + 0x180);
    speed = FastVecLength(state + 0xF0);
    distance = FastVecLength(toTarget);
    ApproachTargetWithBraking(&speed, distance, D_L20_001B2444 * 0.00027777778f,
                  D_L20_001B2444 * 0.00027777778f,
                  D_L20_001B2448 * 0.016666668f);
    vec_scale_to_length(state + 0xF0, toTarget, speed);
    qcopy(position, savedPos);
    SetControlMotionAndStep(moby, state + 0xF0);
    qcopy(savedPos, position);
    TransformVectorByObjectOrGiven(moby, aimDelta, state + 0xF0, 0);
    turnGain = D_L20_001B244C;
    yaw = aimDelta[1] * -turnGain;
    *(float *)(state + 0x1A8) = yaw;
    *(float *)(state + 0x1AC) = aimDelta[0] * turnGain;
    if (yaw > 0.78539824f) {
        *(float *)(state + 0x1A8) = 0.78539824f;
    } else if (yaw < -0.78539824f) {
        *(float *)(state + 0x1A8) = -0.78539824f;
    }
    pitch = *(float *)(state + 0x1AC);
    if (pitch > 0.78539824f) {
        *(float *)(state + 0x1AC) = 0.78539824f;
    } else if (pitch < 0.0f) {
        *(float *)(state + 0x1AC) = 0.0f;
    }
    return distance;
}
