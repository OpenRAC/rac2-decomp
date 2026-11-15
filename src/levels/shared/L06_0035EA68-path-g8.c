#include "common.h"
typedef int L06Qword __attribute__((mode(TI)));
typedef union { L06Qword bits; float f[4]; } L06Vector;
extern char *D_L06_001FE500[];
extern u8 D_L06_001DB610[];
extern char D_00188660[];
extern float D_L06_001AF528 __attribute__((sda));
extern float D_L06_001AF52C __attribute__((sda));
extern float D_L06_001AF530 __attribute__((sda));
extern float D_L06_001AF534 __attribute__((sda));
extern float D_L06_001AF538 __attribute__((sda));
extern float D_L06_001AF53C __attribute__((sda));
extern float D_L06_001AF540 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E20(void *);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283248(float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_002AAA00(void *, void *, int, float, float, float, float);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_002E59F8(int);

/* Moves a moby along a numbered path one point at a time, turning and tilting it, and plays a hum while it moves. Returns 1 when it reaches the end. */
int func_L06_003E4BE0(char *moby, int path, int *sound)
{
    L06Vector target, delta;
    float height;
    char **route = &gPathList[path];
    char *st = *(char **)(moby + 0x68);
    int done = 0;
    float limit, angle;
    int handle;
    u8 *slot;
    float *yaw;
    int point = *(int *)(st + 0x64);
    char *node = *route;
    height = 0;
    qcopy(&target, node + point * 16 + 0x10);
    *(float *)(st + 0x108) = target.f[2];
    *(float *)(st + 0xEC) = 0;
    *(float *)(st + 0xE8) = 0;
    FastVecSub(&delta, &target, moby + 0x10);
    if (FastVecLength(&delta) < D_L06_001AF528 * (1.0f / 60.0f) * 2.0f) {
        ++*(int *)(st + 0x64);
        done = *(int *)(st + 0x64) == *(int *)*route;
    }
    limit = fast_vec_dist(moby + 0x10, *route + *(int *)*route * 16);
    StepValueTowardTarget(&height, st + 0x60, limit,
        D_L06_001AF52C * 0.00027777778450399637f,
        D_L06_001AF52C * 0.00027777778450399637f,
        D_L06_001AF528 * (1.0f/60.0f));
    vec_scale_to_length(&delta, &delta, *(float *)(st + 0x60));
    FastVecAdd(moby + 0x10, &delta, moby + 0x10);
    angle = -FastMatrixHelperA(vec_length_xy(&delta), delta.f[2]);
    if (angle > 0.2617994248867035f) angle = 0.2617994248867035f;
    else if (angle < -0.2617994248867035f) angle = -0.2617994248867035f;
    yaw = (float *)(moby + 0xF8);
    ApproachTargetWithDirectionMode(moby + 0xF4, st + 0x6C, 0, angle,
        D_L06_001AF538 * 0.000004848137291264255f,
        D_L06_001AF538 * 0.000004848137291264255f, 0.20943954586982727f);
    angle = FastMatrixHelperA(target.f[0] - *(float *)(moby + 0x10), target.f[1] - *(float *)(moby + 0x14));
    ApproachTargetWithDirectionMode(yaw, st + 0x68, 0, angle,
        D_L06_001AF530 * 0.000004848137291264255f,
        D_L06_001AF530 * 0.000004848137291264255f,
        D_L06_001AF534 * 0.0002908882452175021f);
    ApproachTargetWithDirectionMode(moby + 0xF0, st + 0x70, 0,
        *(float *)(st + 0x68) * *(float *)(st + 0x60) * D_L06_001AF540,
        D_L06_001AF53C * 0.000004848137291264255f,
        D_L06_001AF53C * 0.000004848137291264255f, 0.20943954586982727f);
    if (!done) {
        if (!IsVoicePlayingForOwner(moby, *sound) && D_L06_001DB610[0] != 0xFF)
            *sound = PlaySoundFromClassBank(0, 4, moby, 0x330);
    } else {
        handle = *sound;
        if (handle != -1) {
            slot = (u8 *)gSoundState + handle * 0x70;
            if (*(char **)(slot + 0x88) == moby && slot[0x74]) StopSoundVoice(handle);
        }
        *sound = -1;
    }
    return done;
}
