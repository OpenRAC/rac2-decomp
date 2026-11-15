#include "common.h"

extern u8 *D_L16_001FE7C0[];
extern float D_L16_001B1750 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_002AAC80(float *, float, float, float, float);
extern float func_00283248(float, float);
/* The callee explicitly returns the updated rate (or angular difference) in f0. */
extern float func_002AAA00(float *, float *, int, float, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* EE EABI uses independent GPR/FP argument banks. This interleaving preserves
 * object, bone, mode, first, second, third in a0-a3/t0-t1 and x, y, z in f12-f14.
 * Native ports must reconcile this declaration with the canonical callee API. */
extern int func_002A8D70(void *, float, int, int, float, float, int, int, int);
extern void func_L16_00410FA8(u8 *);

/* Walks the boss toward its next path point at a smooth speed, turns it to face the way it walks and updates the path points when it arrives. */
void func_L16_004110D0(u8 *moby, float dt)
{
    float point[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(int *)(state + 0x170)];
    int finalPoint = 1;
    float distance, heading;
    float *orientation;
    *(float *)(moby + 0x48) = *(float *)(state + 0x230) * 3.0f;
    *(float *)(*(u8 **)(state + 0x1f0) + 0x48) = *(float *)(moby + 0x48);
    if (*(int *)(state + 0x220) == *(int *)(state + 0x1f4) && *(int *)(state + 0x224) == *(int *)(state + 0x1f8)) {
        qcopy(point, (state + 0x200));
    } else {
        int previous = *(int *)(state + 0x22c);
        if (previous == *(int *)(state + 0x220) || previous == *(int *)(state + 0x224) ||
            *(int *)(state + 0x228) != *(int *)(state + 0x220) || *(int *)(state + 0x228) != *(int *)(state + 0x224)) PickNextPathSegment(moby);
        qcopy(point, (path + *(int *)(state + 0x228) * 16 + 16));
        finalPoint = 0;
    }
    orientation = (float *)(moby + 0xf8);
    FastVecSub(delta, point, moby + 0x10);
    delta[2] = 0.0f;
    distance = FastVecLength(delta);
    ApproachTargetWithBraking((float *)(state + 0x230), distance, D_L16_001B1750 * 0.00027777778f, D_L16_001B1750 * 0.00027777778f, dt);
    heading = FastMatrixHelperA(delta[0], delta[1]);
    ApproachTargetWithDirectionMode(orientation, (float *)(state + 0x234), 0, heading, 0.00174532947f, 0.00174532947f, 0.104719773f);
    vec_scale_to_length(step, delta, *(float *)(state + 0x230));
    FastVecAdd(moby + 0x10, moby + 0x10, step);
    if (!*(int *)(state + 0x26c)) {
        TestHitAtBone(moby, 6.0f, 0, 0x90000, 50.0f, 1.0f, 0, 1, 0);
        TestHitAtBone(moby, 6.0f, 1, 0x90000, 50.0f, 1.0f, 0, 1, 0);
    }
    if (!finalPoint && distance < 0.5f) {
        int current = *(int *)(state + 0x228);
        int previous = *(int *)(state + 0x22c);
        if (previous < current) { *(int *)(state + 0x220) = previous; *(int *)(state + 0x224) = current; }
        else { *(int *)(state + 0x220) = current; *(int *)(state + 0x224) = previous; }
    }
}
