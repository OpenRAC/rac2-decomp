#include "common.h"

extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern int func_00282948(void *);
extern char D_L10_002BAC40[];
extern char D_L10_001B1790[16] __attribute__((sda));
extern void func_002AA458(void *, void *, void *, float, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A7750(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);
extern int func_L10_0042E590(void *);
extern void func_L05_00398F18(void *, int, int, int, int, int, int, int, float);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, int, int, int, float);
extern void func_0029F338(void *);
extern void func_L10_0042E4D0(void *);
extern void func_L10_0042E660(char *, int);
extern char *func_L10_0042DF10(int);

/* Update of a cloud object spawned by func_L10_0042DF10. State 0 waits for the timer at
   work+0x1C; state 1 steers to its point in D_L10_002BAC40 (state 2 within 2 units); state 2
   steers to the 16-byte target D_L10_001B1790 and bursts there. Then the velocity at work+0
   moves the object and decays, the angles spin, and leaving the 2..1021 box (or
   func_L10_0042E590) bursts it as well; otherwise func_L10_0042E4D0 runs on a random half of the frames.
   -G16 for the $gp target; -frac2-gcse-unsplit-edges keeps the object+0x10 PRE copy in the
   dispatch block, as retail (the split edge of the state-0 timer test would get its own). */
void func_L10_0042E100(char *object)
{
    char *work = *(char **)(object + 0x68);

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (FastFloatHelperD(work + 0x1C))
            SetMobyState(object, 1, -1);
        break;
    case 1: {
        float speed = RandomFloatRange(2.0f, 4.0f) * 0.016666668f;
        SpringVectorToTarget(object + 0x10, D_L10_002BAC40 + *(int *)(work + 0x28) * 16, work + 0x18,
                      0.00083333335f, 0.027777778f, speed);
        if (fast_vec_dist(object + 0x10, D_L10_002BAC40 + *(int *)(work + 0x28) * 16) < 2.0f)
            SetMobyState(object, 2, -1);
        break;
    }
    case 2:
        SpringVectorToTarget(object + 0x10, D_L10_001B1790, work + 0x18, 0.0033333334f, 0.0033333334f,
                      0.13333334f);
        if (fast_vec_dist(object + 0x10, D_L10_001B1790) < 0.5f) {
            if (*(short *)(object + 0xAA) == 0x1315 /* moby class 4885 */)
                func_L05_00398F18(object + 0x10, 0, 0, 0, 0, 15, 0, 1, 0.7f);
            else
                SpawnShockwaveBurst(object + 0x10, 0, 0, 0, 0, 10, 20, 1, 1, 0, 0, 0.7f);
            SpawnCloudObject(*(int *)(work + 0x14));
            MarkMobySpawned(object);
            return;
        }
        break;
    }
    FastVecAdd(object + 0x10, object + 0x10, work);
    vec_scale_to_length(work, work, FastVecLength(work) * 0.9875f);
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), 0.01f);
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), -0.02f);
    if (CheckCloudObjectBlocked(object) || *(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        DropRewardAtCloudObject(object, 0);
        if (*(short *)(object + 0xAA) == 0x1315 /* moby class 4885 */)
            func_L05_00398F18(object + 0x10, 0, 0, 0, 0, 30, 0, 1, 0.7f);
        else
            SpawnShockwaveBurst(object + 0x10, 0, 0, 0, 0, 20, 40, 1, 1, 0, 0, 0.7f);
        SpawnCloudObject(*(int *)(work + 0x14));
        MarkMobySpawned(object);
    } else if (RandomIntBelow(2)) {
        ProbeCloudObjectObstacle(object);
    }
}
