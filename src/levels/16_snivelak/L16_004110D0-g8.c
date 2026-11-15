#include "common.h"

extern u8 *D_L16_001FE7C0[];
extern float D_L16_001B1750 __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void math_approach_target_with_braking(float *, float, float, float, float);
extern float mat_fast_helper_a(float, float);
/* The callee explicitly returns the updated rate (or angular difference) in f0. */
extern float math_approach_target_with_direction_mode(float *, float *, int, float, float, float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
/* EE EABI uses independent GPR/FP argument banks. This interleaving preserves
 * object, bone, mode, first, second, third in a0-a3/t0-t1 and x, y, z in f12-f14.
 * Native ports must reconcile this declaration with the canonical callee API. */
extern int coll_test_hit_at_bone(void *, float, int, int, float, float, int, int, int);
extern void snivelak_pick_next_path_segment(u8 *);

/* Walks the boss toward its next path point at a smooth speed, turns it to face the way it walks and updates the path points when it arrives. */
void snivelak_move_along_path(u8 *moby, float dt)
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
            *(int *)(state + 0x228) != *(int *)(state + 0x220) || *(int *)(state + 0x228) != *(int *)(state + 0x224)) snivelak_pick_next_path_segment(moby);
        qcopy(point, (path + *(int *)(state + 0x228) * 16 + 16));
        finalPoint = 0;
    }
    orientation = (float *)(moby + 0xf8);
    FastVecSub(delta, point, moby + 0x10);
    delta[2] = 0.0f;
    distance = FastVecLength(delta);
    math_approach_target_with_braking((float *)(state + 0x230), distance, D_L16_001B1750 * 0.00027777778f, D_L16_001B1750 * 0.00027777778f, dt);
    heading = mat_fast_helper_a(delta[0], delta[1]);
    math_approach_target_with_direction_mode(orientation, (float *)(state + 0x234), 0, heading, 0.00174532947f, 0.00174532947f, 0.104719773f);
    vec_scale_to_length(step, delta, *(float *)(state + 0x230));
    FastVecAdd(moby + 0x10, moby + 0x10, step);
    if (!*(int *)(state + 0x26c)) {
        coll_test_hit_at_bone(moby, 6.0f, 0, 0x90000, 50.0f, 1.0f, 0, 1, 0);
        coll_test_hit_at_bone(moby, 6.0f, 1, 0x90000, 50.0f, 1.0f, 0, 1, 0);
    }
    if (!finalPoint && distance < 0.5f) {
        int current = *(int *)(state + 0x228);
        int previous = *(int *)(state + 0x22c);
        if (previous < current) { *(int *)(state + 0x220) = previous; *(int *)(state + 0x224) = current; }
        else { *(int *)(state + 0x220) = current; *(int *)(state + 0x224) = previous; }
    }
}
