#include "common.h"

extern char *D_L02_001B359C;
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x530];
    char *captured;
    char pad5c4[0xE90];
    unsigned short captureMode;
} Hero003E87D8;
/* Prefix of the resident hero: position, captured actor and capture mode. */
extern char D_00189E20[];
extern char D_00188660[];
extern unsigned short D_0018CA6C NOT_SDA;
extern float D_L02_001B0B80 __attribute__((sda));
extern float D_L02_001B0B84 __attribute__((sda));
extern float D_L02_001B0B88 __attribute__((sda));
extern float D_L02_001B0B8C __attribute__((sda));
extern float D_L02_001B0B90 __attribute__((sda));
extern float D_L02_001B0B94 __attribute__((sda));
extern float D_L02_001B0BA0 __attribute__((sda));
extern float D_L02_001B0BF0[4] __attribute__((sda, aligned(16)));
/* The vector address uses GP; its fourth component uses the absolute view. */
extern float effectOffset003E87D8[4] SDATA(D_L02_001B0BF0);
typedef struct { char pad[0x34]; unsigned short flags; } Actor003E87D8;
extern void func_002A7750(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_L00_003294F0(void *, int);
extern void func_00282C88(void *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_002AAA00(void *, void *, int, float, float, float, float);
extern void func_L02_003E8CE8(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_00424F58(char *, float, float);
extern void func_L00_00424C28(void);
extern void func_L00_00424B70(float, float);
extern int func_002B3868(void *);
extern int func_L02_003E8E90(void *);
extern void func_L02_003CADA8(void *, void *);
extern void func_L02_003D01F0(void *, void *);
extern float func_00282C48(float);
extern void func_002E59F8(int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002B38B8(void *);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L02_003E98A8(char *);
/* Updates a tether actor's capture, release, turning and attached effect. */
void func_L02_003E87D8(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *target = gMobyPool_L02 + *(int *)state * 0x100;
    float effectPoint[4] __attribute__((aligned(16)));
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(float *)(state + 0x48) = *(float *)(actor + 0xF8);
        if (*(int *)state != -1) {
            SetMobyState(actor, 1, -1);
            if (*(short *)(gMobyPool_L02 + *(int *)state * 0x100 + 0xAA) == 0x9BC /* moby class 2492 */) {
                char *effect = CreateMoby(0xA61 /* moby class 2657 */);
                *(char **)(state + 0x54) = effect;
                if (effect) {
                    InitChildObjectFromParent(effect, actor);
                    *(unsigned short *)(*(char **)(state + 0x54) + 0x34) |= 2;
                }
            }
        } else {
            SetMobyState(actor, 4, -1);
        }
        break;
    case 1:
        if ((*(unsigned short *)(target + 0x34) & 0x1000) && ((Hero003E87D8 *)gHeroState)->captured == target &&
            vec_distance_xy(target + 0x10, actor + 0x10) < D_L02_001B0B80) {
            SetObjectFlagBit(target, 1);
            ClearVector128(state + 0x10);
            SetMobyState(actor, 2, -1);
            break;
        }
        break;
    case 2:
        {
            float separation;
            float turnStep, turnLimit;
            float angle = FastAddRotations(FastMatrixHelperA(
                *(float *)(target + 0x10) - *(float *)(actor + 0x10),
                *(float *)(target + 0x14) - *(float *)(actor + 0x14)), 3.1415927f);
            if (FastDiffRots(angle, *(float *)(actor + 0xF8)) > 1.5707964f)
                angle = FastAddRotations(angle, 3.1415927f);
            turnStep = D_L02_001B0B88 * 0.0000048481375f;
            turnLimit = D_L02_001B0B8C * 0.00029088825f;
            ApproachTargetWithDirectionMode(actor + 0xF8, state + 0x40, 0, angle, turnStep, turnStep * 3.0f, turnLimit);
            PullTetheredEntityToActor(actor);
            separation = vec_distance_xy(actor + 0x10, ((Hero003E87D8 *)gHeroState)->position);
            if (((Hero003E87D8 *)gHeroState)->captured != target || separation > D_L02_001B0BA0) {
                float distance, scaledDistance;
                ((Hero003E87D8 *)gHeroState)->captured = 0;
                distance = fast_vec_dist(actor + 0x10, ((Hero003E87D8 *)gHeroState)->position) - D_L02_001B0B84;
                if (distance < 0.0f)
                    distance = 0.0f;
                scaledDistance = distance * 0.016666668f;
                ((Actor003E87D8 *)target)->flags &= 0xEFFF;
                *(float *)(state + 0x44) = D_L02_001B0B90 * 0.016666668f + D_L02_001B0B94 * scaledDistance;
                PlayMobySound(0, 0, actor);
                SetMobyState(actor, 3, -1);
            } else {
                ((Hero003E87D8 *)gHeroState)->captureMode = 2;
                SetCameraStrengthAndSteerToTarget(actor + 0x10, 0.78539824f, 0.0f);
                SetCameraLockFlag();
                SetCameraSpeedsIfNonZero(0.03f, 0.2f);
                if (*(unsigned short *)(target + 0x34) & 0x1000)
                    break;
                SetMobyState(actor, 1, -1);
            }
        }
        break;
    case 3:
        if (SetFirstPendingFlag(actor)) {
            qzero_nc(state + 0x10);
            PlayMobySound(0, 0, actor);
        }
        if (SwingTetheredEntity(actor)) {
            SetObjectFlagBit(target, 0);
            if (*(short *)(target + 0xAA) == 0x9BC /* moby class 2492 */) {
                StartPathEnemyFall(target, state + 0x10);
                D_0018CA6C = 0xFFFF;
            } else {
                StartPlatformFall(target, state + 0x10);
            }
            SetMobyState(actor, 1, -1);
        }
        break;
    }
    if (FloatAbs(*(float *)(state + 0x40)) > 0.004363324f) {
        char *slot = gSoundState + *(int *)(state + 0x58) * 0x70;
        if (*(char **)(slot + 0x88) != actor || *(unsigned char *)(slot + 0x74) == 0)
            *(int *)(state + 0x58) = PlayMobySound(1, 4, actor);
        if (*(unsigned char *)(actor + 0x20) != 2)
            *(float *)(state + 0x40) = 0;
    } else {
        int index = *(int *)(state + 0x58);
        if (index != -1) {
            char *slot = gSoundState + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74))
                StopSoundVoice(index);
        }
        *(int *)(state + 0x58) = -1;
    }
    if (*(char **)(state + 0x54)) {
        matrix_mul_vec3(effectPoint, effectOffset003E87D8, actor + 0xC0);
        FastVecAdd(*(char **)(state + 0x54) + 0x10, effectPoint, actor + 0x10);
        *(float *)(*(char **)(state + 0x54) + 0xF8) = *(float *)(actor + 0xF8);
        *(float *)(*(char **)(state + 0x54) + 0x2C) = *(float *)(*(char **)(*(char **)(state + 0x54) + 0x24) + 0x24) * D_L02_001B0BF0[3];
    }
    if (IsThirdPendingFlagSet(target))
        AddDrawCallbackToList1(DrawMirroredRibbons, actor);
}
