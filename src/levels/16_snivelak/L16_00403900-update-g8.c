#include "common.h"
/* Interfaces as the call sites load them; ignored results stay unqualified.
 * Retail's call to func_L16_00404E40 loads a1, f12 and f13 although the callee
 * never reads them, so this caller declares the arguments it really passes. */
extern int func_L16_00404A60(void *), func_002B3890(void *);
extern int func_002A7820(int, int), func_00282978(short *);
extern void func_002A7470(void *, int, int, int), func_002A7750(void *, int, int);
extern void func_002A6C58(void *, int, int), func_002A7A00(void *, float, float);
extern float func_00282C48(float), func_002A78D8(float, float), func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern u8 *func_00273730(void *, int, int, int, void *, void *, void *, u8, float, float);
extern void func_00310C88(void *), func_002AB650(void *), func_0029F338(void *);
extern int func_002E5CF8(int, int, void *);
extern void *func_L16_00406080(void *, int, int, int, int, int, int, int, float, int, int);
extern int func_L01_00322288(int, float), func_L09_00329028(char *, int);
extern int func_L16_00404E40(void *, void *, float, float);
extern float func_00283248(float, float), func_00282E80(void *, void *), func_00283C80(float, float);
extern float func_002AAA00(float *, float *, float, float, float, float, int);
extern int func_002AEB60(void *, float);
extern void func_0029FCC0(char *, int, char *);
extern void *func_L16_00405488(void *, void *, void *, int, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_L16_00404F50(void *);
typedef struct {
    u8 unknown00[0x80];
    float position80[4];
    u8 unknown90[0x50];
    float aimPositionE0[4];
    u8 unknownF0[0x2290 - 0xf0];
    u8 *target2290;
} PlayerView;
extern PlayerView D_00189E20 NOT_SDA;
extern float D_L16_001A8F20[4] __attribute__((sda));
extern u8 *D_L16_001BFF58 NOT_SDA;
/* Partial view shared with the matched sibling death/debris update. */
extern struct {
    u8 pad000[0x160];
    float strength;
    u8 pad164[4];
    int duration, timer;
    u8 pad170[0x10];
    float damping;
    u8 pad184[4];
    int lifetime;
} D_L16_001B99C0;

/* Both destruction exits are written out. Sched2 still sees func_0029F338 in
 * the debris block, and its extra dependence decides that block's order; jump2
 * then merges the exits, so the early-out branches into the debris tail. */
void func_L16_00403900(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float position[4] __attribute__((aligned(16)));
    float aim[4] __attribute__((aligned(16)));
    u8 *child;
    int i, attack;
    float angle, pitch;
    float *pitchField3, *pitchField6, *pitchField7, *pitchField5;
    if (UpdateSnivelakBossMain(moby)) {
        MarkMobySpawned(moby);
        return;
    }
    switch (moby[0x95]) {
    case 0:
        if (SetSecondPendingFlag(moby)) *(short *)(state + 0x25e) = RandomIntRange(0, 30);
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
            SetMobyState(moby, 5, 2);
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
                SetMobyState(moby, 4, 2);
            }
            if (*(int *)(state + 0x294) != -1) {
                SetMobyState(moby, 3, 2);
                if (!*(int *)(state + 0x2a8) || *(int *)(state + 0x2ac))
                    if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
            }
        } else if (*(int *)(state + 0x264) && FastDecTimer((short *)(state + 0x25e))) {
            SetMobyState(moby, 2, 1);
            *(int *)(state + 0x264) = 0;
            if (*(int *)(state + 0x258) < 300)
                *(int *)(state + 0x258) = RandomIntRange(480, 600);
        }
        break;
    case 1:
        if (*(int *)(state + 0x260) == 1 || *(int *)(state + 0x2b4) == 1)
            SetMobyState(moby, 5, 2);
        break;
    case 2:
        if (*(int *)(state + 0x260) == 1) break;
        if (*(int *)(state + 0x2b4) != 1 && moby[0x20] != 4 && moby[0x20] != 3) {
            SetMobyState(moby, 1, 0);
            if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
            *(int *)(state + 0x258) = RandomIntRange(580, 600);
        }
        break;
    case 3:
        if (*(float *)(state + 0x20) <= 0.0f) {
            SetDeathBits(moby, 0, 3);
            for (i = 0; i < 5; i++) {
                RandomDirectionVector(position, 0.13333334f, 0.20000002f);
                position[2] = FloatAbs(position[2]);
                position[2] *= 2.5f;
                FastVecAdd(position, position, D_L16_001A8F20);
                child = CreateCameraMoby(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, position, 255, 30.0f, 15.0f);
                *(void (**)(void *))(child + 0x64) = UpdateFadeOutMoby;
            }
            PlayMobySound(0, 0, moby);
            CreateFlashEffectMoby(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 2.0f, 1, 1);
            CreateFlashEffectMoby(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 1.0f, 1, 1);
            D_L16_001B99C0.damping = 0.1f;
            D_L16_001B99C0.lifetime = 90;
            D_L16_001B99C0.strength = 0.2f;
            D_L16_001B99C0.duration = 60;
            D_L16_001B99C0.timer = 0;
            MarkMobySpawned(*(void **)(state + 0x274));
            position[0] = RandomSignedFloatRange(0.5f, 4.0f) * 0.016666668f;
            position[1] = RandomSignedFloatRange(0.0f, 4.0f) * 0.016666668f;
            position[2] = RandomFloatRange(7.0f, 9.0f) * 0.016666668f;
            position[2] = FloatAbs(position[2]);
            position[2] += position[2];
            FastVecAdd(position, position, D_L16_001A8F20);
            child = CreateCameraMoby(moby, 3, 0xecb, 0, moby + 0x10,
                moby + 0xf0, position, 255, 180.0f, 25.0f);
            CopyHeroField38ToMoby(child);
            MarkMobySpawned(moby);
            return;
        }
        if (!(moby[0x60] & 2)) break;
        *(int *)(state + 0x2b8) = 0;
        *(short *)(state + 0x25c) = 0;
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
            SetMobyState(moby, 5, 2);
            if (*(int *)(state + 0x298) != -1) SetMobyState(moby, 6, -1);
        } else {
            SetMobyState(moby, 2, 1);
            if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
            *(int *)(state + 0x258) = RandomIntRange(580, 600);
        }
        if (*(int *)(state + 0x2ac)) {
            SetMobyState(moby, 4, 2);
            if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
        }
        break;
    }
    attack = moby[0x20];
    switch (attack) {
    case 1:
    case 2:
        break;
    case 3:
        if (!*(int *)(state + 0x2ac))
            StartMobyEffectFromEntry((int)moby, FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
                gHeroState.position80[1] - *(float *)(moby + 0x14)));
        if (FollowPathPoints(moby, moby + 0x10, 0.0f, 0.0f)) {
            if (*(int *)(state + 0x298) != -1) {
                SetMobyState(moby, 6, -1);
                if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
            } else {
                SetMobyState(moby, 5, -1);
                if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
            }
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
                SetMobyState(moby, 4, 2);
                *(float *)(state + 0x28c) = *(float *)(moby + 0x18) + 260.0f;
            }
        }
        if (!*(int *)(state + 0x2ac)) {
            pitchField3 = (float *)(moby + 0xf4);
            pitch = FastMatrixHelperA(vec_distance_xy(moby + 0x10, gHeroState.target2290 + 0x10),
                *(float *)(gHeroState.target2290 + 0x18) - *(float *)(moby + 0x18));
            ApproachTargetWithDirectionMode(pitchField3, (float *)(state + 0x270),
                -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        }
        if (!IsValueWithinStepOfThreshold(moby, 1.5f)) break;
        angle = FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        TransformMobyJointToWorld((char *)moby, 2, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        TransformMobyJointToWorld((char *)moby, 3, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        break;
    case 6:
        StartMobyEffectFromEntry((int)moby, FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14)));
        if (CheckPathTableEntryForMoby((char *)moby, *(int *)(state + 0x298)) &&
            *(int *)(state + 0x29c) != -1) SetMobyState(moby, 7, -1);
        pitchField6 = (float *)(moby + 0xf4);
        pitch = FastMatrixHelperA(vec_distance_xy(moby + 0x10, gHeroState.target2290 + 0x10),
            *(float *)(gHeroState.target2290 + 0x18) - *(float *)(moby + 0x18));
        ApproachTargetWithDirectionMode(pitchField6, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!IsValueWithinStepOfThreshold(moby, 1.5f)) break;
        angle = FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        TransformMobyJointToWorld((char *)moby, 2, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        TransformMobyJointToWorld((char *)moby, 3, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 7:
        StartMobyEffectFromEntry((int)moby, FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14)));
        if (CheckPathTableEntryForMoby((char *)moby, *(int *)(state + 0x29c)) &&
            *(int *)(state + 0x298) != -1) SetMobyState(moby, 6, -1);
        pitchField7 = (float *)(moby + 0xf4);
        pitch = FastMatrixHelperA(vec_distance_xy(moby + 0x10, gHeroState.target2290 + 0x10),
            *(float *)(gHeroState.target2290 + 0x18) - *(float *)(moby + 0x18));
        ApproachTargetWithDirectionMode(pitchField7, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!IsValueWithinStepOfThreshold(moby, 1.5f)) break;
        angle = FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        TransformMobyJointToWorld((char *)moby, 2, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        TransformMobyJointToWorld((char *)moby, 3, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 4:
        StepValueTowardTarget((float *)(moby + 0x18), (float *)(state + 0x290),
            *(float *)(state + 0x28c), 0.0125f, 0.0027777778f, 0.06666667f);
        if (!(*(float *)(state + 0x28c) - *(float *)(moby + 0x18) < 0.3f) ||
            *(int *)(state + 0x2ac)) break;
        if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
        SetMobyState(moby, 5, -1);
        if (*(int *)(state + 0x298) != -1) SetMobyState(moby, 6, -1);
        break;
    case 5:
        StartMobyEffectFromEntry((int)moby, FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14)));
        pitchField5 = (float *)(moby + 0xf4);
        pitch = FastMatrixHelperA(vec_distance_xy(moby + 0x10, gHeroState.target2290 + 0x10),
            *(float *)(gHeroState.target2290 + 0x18) - *(float *)(moby + 0x18));
        ApproachTargetWithDirectionMode(pitchField5, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!IsValueWithinStepOfThreshold(moby, 1.5f)) break;
        angle = FastMatrixHelperA(gHeroState.position80[0] - *(float *)(moby + 0x10),
            gHeroState.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        TransformMobyJointToWorld((char *)moby, 2, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        TransformMobyJointToWorld((char *)moby, 3, (char *)position);
        FastVecSub(aim, gHeroState.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, gHeroState.aimPositionE0, 0, moby, 0)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        } else if (D_L16_001BFF58 && (D_L16_001BFF58 == gHeroState.target2290 ||
                   *(short *)(D_L16_001BFF58 + 0xaa) != 0xebb)) {
            SpawnAimedShot_L16(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    }
    if ((unsigned int)moby[0x20] - 6 < 2) {
        if (moby[0x42] == 3) {
            if (++*(int *)(state + 0x2b8) > 240) {
                if (moby[0x43]) StartAnimationBlended(moby, 0, 0, 10);
                *(int *)(state + 0x2b8) = 0;
            }
        } else if (!moby[0x42] && ++*(short *)(state + 0x25c) > 60) {
            if (moby[0x43] != 3) StartAnimationBlended(moby, 3, 0, 10);
            *(short *)(state + 0x25c) = 0;
        }
    }
    UpdateBossTurretMoby(moby);
}
