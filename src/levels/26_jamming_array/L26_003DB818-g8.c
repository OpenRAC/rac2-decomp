#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { int action[4]; } ActionChoices;
extern int D_L26_001A8FF0;
extern ActionChoices D_L26_001B05C8;
extern float D_L26_001B05C0 __attribute__((sda));
extern float D_00189EA0[4];
extern int func_L26_003DBE18(unsigned char *);
extern void func_002A7750(unsigned char *, int, int);
extern unsigned long func_002B1C20(void *, void *);
extern void func_00325D30(char *, char *);
extern void func_002A6C58(void *, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002E5CF8(int, int, char *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, void *, float, float);
extern void func_002AB6D8(float *, float *);
extern void func_00282F20(void *, void *, float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern void func_0029F338(void *);
extern int func_002A7820(int, int);
extern int func_002B3868(unsigned char *);
extern int func_002A77E0(int);
extern void func_002A7470(void *, int, int, int);
extern int func_L02_00332630(char *, void *);
extern void func_L02_00333438(char *, char *);
extern float func_L26_00324598(unsigned char *, void *, void *);
extern float func_00282C48(float);
extern float func_0029F530(char *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_L26_003DC048(void *);

/* Per-frame update for the moby of class 3214: a creature that picks between idle, walking and
   attack animations, and blows up in a burst of effects when it dies. */
void func_L26_003DB818(unsigned char *object) {
    /* Mutually exclusive uses of the same 16-byte retail workspace. */
    union { ActionChoices choices; Vector position; } workspace;
    Vector seed;
    Vector velocity;
    char *private;
    unsigned long flags;
    float time;
    int next;
    int i;
    if (!D_L26_001A8FF0) return;
    private = *(char **)(object + 0x68);
    if (UpdateFlyingCreatureState(object)) { MarkMobySpawned(object); return; }
    switch (object[0x95]) {
    case 0:
        if (*(short *)(private + 0x224) == 1) {
            if (object[0x20] == 1) SetMobyState(object, 4, 2);
            else SetMobyState(object, 5, 2);
        } else if (*(short *)(private + 0x226)) {
            SetMobyState(object, 3, 1);
            *(short *)(private + 0x226) = 0;
            if (*(short *)(private + 0x220) < 300)
                *(short *)(private + 0x220) = RandomIntRange(480, 600);
        }
        break;
    case 1:
        if (*(short *)(private + 0x224) == 1)
            SetMobyState(object, 5, 2);
        else if (*(short *)(private + 0x220) == 0 && (object[0x60] & 2))
            SetMobyState(object, 2, 0);
        break;
    case 2:
        if (*(short *)(private + 0x224) != 1 && object[0x20] != 6) {
            SetMobyState(object, 3, 1);
            *(short *)(private + 0x220) = RandomIntRange(580, 600);
        }
        break;
    case 3:
        flags = DispatchActionByKind(object, private + 0x50);
        if (((flags & 1UL) == 1UL) || *(float *)(private + 0x20) <= 0.0f) {
            DestroyAttachedParts((char *)object, private + 0x270);
            SetDeathBits(object, 0, 3);
            seed.q = 0;
            seed.f[2] = 1.0f;
            matrix_mul_vec3(&workspace.position, &seed, object + 0xC0);
            FastVecAdd(&workspace.position, &workspace.position, object + 0x10);
            PlayMobySound(13, 0, (char *)object);
            SpawnExplosion(&workspace.position, 0, 25, 20, 20, 20, 45, 0, 0, 1, 0, 0, 0.8f, 20.0f);
            GetEulerAnglesFromMatrix((float *)(object + 0xC0), (float *)(object + 0xF0));
            vec_scale_to_length(&velocity, private + 0xD0, 0.083333336f);
            SpawnDebrisForMaskedParts((char *)object, 0x3F8, velocity.f, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            MarkMobySpawned(object);
            return;
        }
        if (((flags & 2UL) == 2UL) || (unsigned char)private[0x6A] > 1) {
            SetMobyState(object, 6, 2);
            *(short *)(private + 0x220) = RandomIntRange(580, 600);
        }
        break;
    }
    switch (object[0x20]) {
    case 2:
        if (SetFirstPendingFlag(object) && object[0x43] != 2)
            StartAnimationBlended(object, 2, 0, 20);
        break;
    case 3:
        workspace.choices = D_L26_001B05C8;
        if (SetFirstPendingFlag(object) && object[0x43] != workspace.choices.action[RandomIntBelow(4)])
            StartAnimationBlended(object, workspace.choices.action[RandomIntBelow(4)], 0, 20);
        CheckTargetPointFromOffset((char *)object, gHeroPosition);
        if (object[0x60] & 2) {
            next = workspace.choices.action[RandomIntBelow(4)];
            if (next == object[0x43]) next = (next + RandomIntBelow(3)) % 4;
            if (object[0x43] != next) StartAnimationBlended(object, next, 0, 20);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(object) && object[0x43] != 4)
            StartAnimationBlended(object, 4, 0, 10);
        if (object[0x60] & 2) SetMobyState(object, 5, -1);
        break;
    case 5:
        if (SetFirstPendingFlag(object) && object[0x43] != 8)
            StartAnimationBlended(object, 8, 0, 20);
        AimAtTargetOffset((char *)object, private + 0x1F0);
        if ((*(float *)(private + 0x1CC) < D_L26_001B05C0) &&
            (FloatAbs(SampleHeightAtPosition(object, private + 0x1F0, private + 0x230)) < 0.17453295f))
            SetMobyState(object, 6, -1);
        break;
    case 6:
        if (SetFirstPendingFlag(object) && object[0x43] != 9)
            StartAnimationBlended(object, 9, 8, 20);
        if (object[0x60] & 2) SetMobyState(object, 5, -1);
        time = GetMobyAnimationValue((char *)object);
        if (object[0x42] == object[0x43] && time >= 18.0f && time <= 24.0f) {
            for (i = 0; i < 2; i++)
                SweepCollisionFromObject(object, *(char **)(private + 0x270 + i * 4) + 0x10,
                              0x4000001, 0, 1, 0, 0.333f, (float)(unsigned char)private[0x34], 1.0f);
        }
        break;
    }
    TickCreatureTimers(object);
    return;
}
