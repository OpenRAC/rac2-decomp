/* func_L02_003EA4E0: a Maktar platform's state handler (activation, swing, travel, release and
   the scrolling surface), a nine-state switch. The activation timer is read into one local that
   is incremented and stored while a copy keeps the old value for the test: retail's
   daddu copy / addiu. The usual `timer = field++` gives an andi 0xFFFF instead.
   -O2 -G8 -ffunction-sections (config/cflags.txt). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L02_001B0D50 __attribute__((sda));
extern int D_L02_001B0D54 __attribute__((sda));
extern float D_L02_001B0D58 __attribute__((sda));
extern float D_L02_001B0D5C __attribute__((sda));
extern int D_L02_001B30C8;
/* Prefix view of the shared owner flag; the whole object remains unqualified. */
typedef struct { unsigned char pad[3]; unsigned char active; } OwnerFlagView;
extern OwnerFlagView D_001395B8 __attribute__((nosda));
extern char D_00188660[], D_00189F10[];
extern void func_L02_003EAA68(void *);
extern int func_002B38B8(void *);
extern void func_0029B3E0(int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L02_003EAD38(void *);
extern float func_00282C48(float);
extern int func_L02_003EAE10(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002833F0(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00283B98(float, float);
extern int func_L02_003EAFC8(void *);
extern void func_002E59F8(int);
extern void func_L02_003EB098(void *);
extern float func_002AA2E8(float *, float, float);
extern void func_00282F20(void *, void *, float);
extern int func_L02_003EB138(void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L02_003EB258(char *);
typedef union { int i[0x20]; float f[0x20]; } PlatState;

/* Updates the platform's activation, swing, travel and scrolling surface. */
void func_L02_003EA4E0(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float angles[4], rotation[12], inverse[16], offset[4];
    float speed, distance, target;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
    InitSwingPlatformGroup(actor);
    return;
    case 2:
    if (D_L02_001B0D50 == 0) {
        unsigned int timer, next;
        if (!IsThirdPendingFlagSet(actor)) return;
        next = *(unsigned short *)(actor + 0x96);
        timer = next;
        next++;
        *(unsigned short *)(actor + 0x96) = next;
        if (timer < 6) return;
    }
    if (*(int *)(state + 4)) { D_001395B8.active = 1; MemcardSave(0, -1); }
    *(int *)(state + 0x2C) = PlayMobySound(0, 4, actor);
    SetGroupMobyStatesFromMode(actor);
    return;
    case 3:
    if (!(FloatAbs((float)gFrameCounter_L02 - **(float **)(state + 0x28)) > 10.0f)) return;
    if (IsPlatformLeadingGroup(actor)) {
        **(float **)(state + 0x28) = (float)gFrameCounter_L02;
        SetMobyState(actor, 4, -1);
        *(unsigned short *)(actor + 0x34) = (*(unsigned short *)(actor + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
        *(float *)(state + 0xC) = 0;
    }
    return;
    case 4:
    speed = 0.016666668f;
    if (SetFirstPendingFlag(actor)) speed = 60.0f;
    qzero(angles);
    angles[2] = *(float *)(state + 0x3C);
    euler_rotation_basis(rotation, angles);
    matrix_from_basis_rows(inverse, rotation);
    FastVecSub(offset, actor + 0x10, state + 0x30);
    matrix_mul_vec3(offset, offset, inverse);
    distance = FloatAbs(offset[1]);
    if (distance <= FloatAbs(*(float *)(state + 0xC))) {
        offset[1] = 0;
        SetMobyState(actor, 5, -1);
    } else StepValueTowardTarget(offset + 1, state + 0xC, 0.0f, speed, speed, 1.0f);
    matrix_mul_vec3(offset, offset, rotation);
    FastVecAdd(actor + 0x10, state + 0x30, offset);
    return;
    case 5:
    if (SetFirstPendingFlag(actor)) {
        qcopy(state + 0x40, actor + 0x10);
        *(float *)(state + 0x10) = 0;
        *(float *)(state + 0xC) = 0;
    }
    distance = FloatAbs(*(float *)(state + 0x10) - 1.0f);
    if (distance < FloatAbs(*(float *)(state + 0xC))) {
        *(float *)(state + 0x10) = 1.0f;
        SetMobyState(actor, 6, -1);
    } else StepValueTowardTarget(state + 0x10, state + 0xC, 1.0f, 0.0027777778f, 0.0027777778f, 0.16666667f);
    lerp_vector(actor + 0x10, state + 0x40, state + 0x30, *(float *)(state + 0x10));
    *(float *)(actor + 0xF8) = FastAddRotations(*(float *)(state + 0x3C), (1.0f - *(float *)(state + 0x10)) * 1.5707965f);
    *(float *)(actor + 0xF0) = (1.0f - *(float *)(state + 0x10)) * 3.1415927f;
    return;
    case 7:
    if (AreGroupMobysSettled(actor)) {
        int index = *(int *)(state + 0x2C);
        if (index != -1) {
            char *slot = gSoundState + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74)) StopSoundVoice(index);
        }
        *(int *)(state + 0x2C) = -1;
        ResetGroupMobyHitPoints(actor);
        SetMobyState(actor, 8, -1);
    }
    return;
    case 8:
    target = (float)D_L02_001B0D54 * 0.06666667f;
    ApproachValue(&D_L02_001B0D58, target, 0.0044444446f);
    vec_scale_to_length(angles, actor + 0xD0, D_L02_001B0D58);
    if (UpdateGroupEffectMobys(actor, angles)) {
        if (D_L02_001B0D58 == target) {
            if (FastVecDot(D_00189F10, angles) < -0.001f) {
                if (++((PlatState *)state)->i[8] > 30) D_L02_001B0D54 = -D_L02_001B0D54;
            } else ((PlatState *)state)->i[8] = 0;
        } else ((PlatState *)state)->i[8] = 0;
    }
    ((PlatState *)state)->f[5] = FastAddRotations(((PlatState *)state)->f[5], D_L02_001B0D5C * 0.00029088825f);
    ((PlatState *)state)->f[6] += D_L02_001B0D58 * 0.5f;
    if (((PlatState *)state)->f[6] > 1.0f) ((PlatState *)state)->f[6] -= 1.0f;
    else if (((PlatState *)state)->f[6] < -1.0f) ((PlatState *)state)->f[6] += 1.0f;
    ApproachValue(&((PlatState *)state)->f[7], 1.0f, 0.016666668f);
    AddDrawCallbackToList1(DrawEnergySheet, actor);
    case 1:
    case 6:
        return;
    }
}
