#include "common.h"

extern int D_L11_001CAE40[];
extern unsigned int D_00138324 __attribute__((nosda));
extern u8 D_00189EA0[];
extern int *D_L11_001FF580[];
extern float D_L11_001B2978 __attribute__((sda));
extern float D_L11_001B297C __attribute__((sda));
extern int D_L11_001AED08;
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L02_0031E9E8(float *, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_002A7750(u8 *, int, int);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *, int, int, int);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002A7820(int, int);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_L07_00321D68(char *, void *);
extern void func_002A7CA0(void *, float *, float, float, float, float);
extern void func_0029F338(void *);
extern float func_00283248(float, float);
extern void func_002AEE70(float *, float *, float *, float, float, float);
extern void func_L01_00321178(char *, char *);
extern void func_002A7A00(float *, float, float);
extern u8 *func_L11_00396DC8(u8 *, float *, float *);
extern void *func_002A9640(void *, unsigned int, int);
extern void func_002B0990(void *, float *, float, int, int);
#define VF(offset) (*(float *)(vars + (offset)))
#define VI(offset) (*(int *)(vars + (offset)))

/* Level-11 creature update, a state machine on object[0x20]: wanders between random points
 * near its spawn, follows a path from D_L11_001FF580, or turns away from the hero; when hit it
 * bursts into 14 pieces (func_L11_00396DC8), counts towards D_L11_001AED08 and deletes itself. */
void func_L11_004702F0(u8 *object) {
    float motion[4], previous[4];
    u8 *vars;
    int *path;
    float *point;
    float angle, distance;
    int first, second;
    u16 timer;
    if (D_L11_001CAE40[0]) return;
    vars = *(u8 **)(object + 0x68);
    switch (object[0x20]) {
    case 0:
        *(u8 **)(vars + 0x18) = vars + 0x20;
        *(float *)(object + 0x2C) *= 1.5f;
        qcopy(vars + 0x110, object + 0x10);
        VF(0x24) = VF(0x20) = 0.4f;
        VF(0x54) = 0.25f;
        VF(0x2C) = VF(0x28) = 0.6f;
        VF(0x50) = VF(0x30) = 1.48353004f;
        VF(0x4C) = 0.00138888892f;
        SetControllerSpeedLimits(object, 0.000555555569f, 0.0166666675f, 0.00116355298f, 0.104719773f);
        RandomPlanarOffset((float *)(vars + 0x120), 4.0f);
        FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
        SetMobyState(object, VI(0x130), -1);
        object[0x30] = 255;
        first = RandomIntBelow(8);
        second = RandomIntBelow(18);
        StartAnimationBlended(object, 0, first, second);
        VI(0x144) = 0;
        if (VI(0x140) != -1 && VI(0x130) != 8) {
            *(float *)(object + 0x2C) *= 1.5f;
            if (object[0x43] != 4) {
                first = RandomIntBelow(3);
                second = RandomIntBelow(8);
                StartAnimationBlended(object, 4, first, second + 10);
            }
            SetMobyState(object, 7, -1);
        }
        break;
    case 2:
        if (fast_vec_dist(object + 0x10, gHeroPosition) < 9.0f) {
            if (object[0x43] != 3) StartAnimationBlended(object, 3, 0, 10);
            SetMobyState(object, 4, -1);
            break;
        }
        if (*(int *)(gHeroPosition + 0x11C8) != 10 && *(int *)(gHeroPosition + 0x11C8) != 13 && (D_00138324 & 0x20)) {
            if (!(vec_distance_xy(object + 0x10, gHeroPosition) < 64.0f) || VI(0x150)) break;
            VF(0x134) = (float)RandomIntRange(170, 190);
            if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 10);
            VF(0x138) = 0.083333336f;
            SetMobyState(object, 6, -1);
        }
        break;
    case 4:
        if (object[0x60] & 2) {
            VF(0x134) = (float)RandomIntRange(170, 190);
            if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 10);
            VF(0x138) = 0.033333335f;
            SetMobyState(object, 5, -1);
        }
        break;
    case 5:
        VF(0x138) += 0.008333334f;
        if (VF(0x138) > 0.116666675f) VF(0x138) = 0.116666675f;
        qcopy(previous, object + 0x10);
        angle = FastAddRotations(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        BuildSphericalOffset(motion, VF(0x138), angle, 2.96706009f);
        SetControlMotionAndStep((char *)object, motion);
        if (vec_distance_xy(object + 0x10, previous) < VF(0x138)) {
            angle = FastAddRotations(*(float *)(object + 0xF8), 3.141593f);
            MobySpringTurn(object, (float *)(vars + 0x13C), angle, 0.000199999995f, 0.00200000009f, 0.04f);
        }
        if (vec_distance_xy(object + 0x10, gHeroPosition) > 64.0f) {
            MarkMobySpawned(object);
            return;
        }
        UpdateWrappedAngleOffset((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.00029088825f, -1.0f);
        break;
    case 6:
        VF(0x138) += 0.008333334f;
        if (VF(0x138) > 0.416666687f) VF(0x138) = 0.416666687f;
        angle = FastAddRotations(*(float *)(object + 0xF8), VF(0x134) * 0.017453294f);
        BuildSphericalOffset(motion, VF(0x138), angle, 2.96706009f);
        FastVecAdd((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (vec_distance_xy(object + 0x10, gHeroPosition) > 64.0f) {
            MarkMobySpawned(object);
            return;
        }
        break;
    case 7:
        path = D_L11_001FF580[VI(0x140)];
        distance = vec_distance_xy(object + 0x10, path + 4 + VI(0x144) * 4);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = FastMatrixHelperA(distance, point[6] - *(float *)(object + 0x18));
        BuildSphericalOffset(motion, 0.116666675f, *(float *)(object + 0xF8), angle);
        point = (float *)((u8 *)path + VI(0x144) * 16);
        angle = FastMatrixHelperA(point[4] - *(float *)(object + 0x10), point[5] - *(float *)(object + 0x14));
        MobySpringTurn(object, (float *)(vars + 0x13C), angle, 9.99999975e-05f, 0.00100000005f, 0.02f);
        FastVecAdd((float *)(object + 0x10), (float *)(object + 0x10), motion);
        if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 10);
        if (vec_distance_xy(object + 0x10, path + 4 + VI(0x144) * 4) < 0.5f) {
            ++VI(0x144);
            if (VI(0x144) >= *path - 1) VI(0x144) = *path - 1;
        }
        UpdateWrappedAngleOffset((float *)object, (float *)(vars + 0x148), (float *)(vars + 0x14C), D_L11_001B2978, D_L11_001B297C * 0.00029088825f, -1.0f);
        break;
    case 8:
        if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 10);
        if (vec_distance_xy(object + 0x10, vars + 0x120) < 0.5f ||
            VI(0xA0) || *(u16 *)(object + 0x96) >= 240) {
            *(u16 *)(object + 0x96) = 0;
            VI(0xA0) = 0;
            RandomPlanarOffset((float *)(vars + 0x120), 4.0f);
            FastVecAdd((float *)(vars + 0x120), (float *)(vars + 0x120), (float *)(vars + 0x110));
            if (RandomIntBelow(4) == 1) {
                if (object[0x43] != 1) StartAnimationBlended(object, 1, 0, 10);
                SetMobyState(object, 9, -1);
            }
        } else {
            TurnMobyTowardTarget((char *)object, (char *)vars + 0x120);
        }
        if (fast_vec_dist(object + 0x10, gHeroPosition) < 10.0f) {
            if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 10);
            SetMobyState(object, 4, -1);
        }
        break;
    case 9:
        if (object[0x60] & 2) {
            SetMobyState(object, 8, -1);
            if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 10);
        }
        if (fast_vec_dist(object + 0x10, gHeroPosition) < 10.0f) {
            if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 10);
            SetMobyState(object, 4, -1);
        }
        break;
    }
    timer = *(u16 *)(object + 0x96);
    if (timer < 65535) *(short *)(object + 0x96) = timer + 1;
    if (object[0x42] == 4) *(float *)(object + 0x48) = 2.5f;
    else if (object[0x42]) *(float *)(object + 0x48) = 1.0f;
    if (FindOwnedEffectSlot(object, 0x10000, 0)) {
        int i;
        for (i = 0; i < 14; i++) {
            u8 *particle;
            RandomDirectionVector(motion, 0.06666667f, 0.100000009f);
            particle = SpawnDebrisPiece_L11(object, (float *)(object + 0x10), motion);
            particle[0x30] = *(u16 *)(particle + 0x32) = 255;
        }
        ++D_L11_001AED08;
        MarkMobySpawned(object);
    } else {
        SetValueAndStartSmoothChange(object, (float *)(vars + 0x160), 2.5f, 0, 1);
    }
}
