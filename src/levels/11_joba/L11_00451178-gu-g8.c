/* func_L11_00451178: the Joba sentry's patrol, alert, attack and launch states; the twin of
 * func_L02_0040A4A8 (L02_0040A4A8-gu.c). Own unit for -frac2-gcse-unsplit-edges.
 * - work[6] is one function-scope scratch array: retail reuses sp+0x10..0x5F across the head
 *   and cases 7, 9 and 12.
 * - Case 7 passes the particle template through tmpl, set just before the template is filled.
 *   Its short life wins it a saved register in global-alloc, which reload then takes back, so
 *   its slot (0xCC) is assigned with case 12's reaching registers (state+0x2B0, object+0xC0,
 *   object+0xF0), in pseudo order after &work[1] and &work[4] (0xC4, 0xC8). Through a register,
 *   the template also keeps the particle loop at 46 insns, so loop.c hoists all seven
 *   constants in its first pass (see the twin's header).
 * - Case 12 sets spin = state + 0x2B0 before its loop, as func_L11_0044AFC8 does: the address
 *   then enters gcse's expression table before object+0xF0, which orders the PRE copies.
 * - turn() is inlined; with it gcse sees retail's insn count (S 583), and the bucket order of
 *   the reaching registers gives retail's spill slots.
 * - Case 11 preserves func_002B1C20's unsigned 64-bit return. Its early exit keeps the
 *   low-bit test in control flow; the compound OR spelling adds a 32-bit normalization.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L11_Palette;
extern L11_Palette D_L11_00200440;
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern float D_L11_001B1D04 __attribute__((sda));
extern float D_L11_001B1D08 __attribute__((sda));
extern s32 D_L11_001B1D0C __attribute__((sda));
extern u16 D_L11_001B1D10 __attribute__((sda));
extern float D_L11_001B1D14 __attribute__((sda));
extern float D_L11_001B1D18 __attribute__((sda));
extern float D_L11_001B1D1C __attribute__((sda));
extern float D_L11_001B1D20 __attribute__((sda));
extern float D_L11_001B1D24 __attribute__((sda));
extern u8 *D_L11_001C0D18[];
extern u8 *D_0018C0B0 __attribute__((nosda));
extern u8 *D_0018C2BC __attribute__((nosda));
extern char D_L11_001A8F20[] MACRO_ADDR;

extern void func_L11_00452450(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern void func_002A7470(u8 *, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(u8 *, void *, u8 *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern s32 func_002B3890(u8 *);
extern s32 func_002B3868(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern u8 *func_L11_004417E8(u8 *);
extern void func_L11_00452F30(u8 *, u8 *);
extern void func_L11_004530C0(u8 *);
extern void func_L02_00333438(u8 *, void *);
extern int func_L01_00321178(u8 *, void *);
extern s32 func_L11_00441808(u8 *, u8 *);
extern void func_002B5278(u8 *, float);
extern s32 func_00282978(void *);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_L11_004530E0(u8 *);
extern s32 func_002B4FF0(u8 *, float *, float);
extern int func_L02_00333480(u8 *, void *, void *);
extern s32 func_002B50E0(u8 *, void *, float);
extern s32 func_00283DB8(void *, float);
extern void func_0029FC20(u8 *, s32, void *);
extern void func_0029FCC0(u8 *, s32, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void *func_002C65A0(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 func_002A8C28(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *func_002C16C0(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 func_002A7820(s32, s32);
extern int func_L11_00340500(u8 *, void *);
extern float func_0029F530(u8 *);
extern s32 func_002AEB60(u8 *, float);
extern void func_00283098(void *, void *, void *);
extern void *func_003280C8(float, u8 *, void *, void *, s32, s32);
extern unsigned long func_002B1C20(u8 *, void *);
extern void func_L02_003FC248(u8 *, s32, s32);
extern void func_L11_00452DF8(u8 *);
extern void func_002AB6D8(void *, void *);
extern int func_L07_00321D68(u8 *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A3F10(u8 *, s32, s32 *, void *);
extern void func_002B4090(float, float, float, u8 *, void *);
extern void func_002833F0(void *, void *);
extern void func_L11_00452810(u8 *);
extern void func_L11_004528A0(u8 *);
extern void func_L00_002E6EF8(void (*)(u8 *), void *);

/* Movement tuning with the sentry's usual turn limits. */
static __inline__ void turn(u8 *object, float rate, float speed)
{
    SetControllerSpeedLimits(object, rate, speed, 0.0005817765f, 0.052359886f);
}

/* Update the Joba sentry's patrol, alert, attack and launch states. */
void func_L11_00451178(u8 *object)
{
    ActorVector target;
    ActorVector work[6];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    s32 count;
    ActorVector *tmpl;
    u8 *state;
    u8 *pos;
    float heading;
    float angle;
    float range;

    state = *(u8 **)(object + 0x68);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4 && object[0x20] != 12 && object[0x20] != 11))
        return;
    UpdateJobaTurretEnemyB(object);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4))
        return;
    if (*(s16 *)(state + 0x2D2) == 0 && object[0x95] == 3) {
        SetMobyState(object, 4, 2);
        if (RandomIntBelow(2)) {
            if (object[0x43] != 2)
                StartAnimationBlended(object, 2, 0, 10);
        } else if (object[0x43] != 3)
            StartAnimationBlended(object, 3, 0, 10);
    }
    if (*(u8 **)(state + 0x2C4))
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2C4) + 0x10);
    else
        target.quad = *(TI128 *)(gHeroState + 0x80);
    if (*(s16 *)(state + 0x2D8)) {
        FastVecSub(&work[0], &target, object + 0x10);
        pos = object + 0x10;
        heading = 0.0f;
        angle = GetHeadingAngleOfVector(object, &work[0], state + 0x230);
    } else {
        pos = object + 0x10;
        heading = FastMatrixHelperA(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        angle = FastDiffRots(heading, *(float *)(object + 0xF8));
    }
    range = fast_vec_dist(pos, &target);
    if (object[0x95] == 2) {
        u8 *goal;
        if (SetSecondPendingFlag(object)) {
            if (object[0x43] != 9)
                StartAnimationBlended(object, 9, 0, 10);
            object[0xBC] = 0;
            turn(object, 0.0044444446f, 0.13333334f);
            PickFlamethrowerRobotWanderPoint(object, GetArenaCenterPoint(*(u8 **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 301) {
            switch (RandomIntBelow(5)) {
            case 0: if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 10); break;
            case 1: if (object[0x43] != 3) StartAnimationBlended(object, 3, 0, 10); break;
            case 2: if (object[0x43] != 5) StartAnimationBlended(object, 5, 0, 10); break;
            case 3: if (object[0x43] != 6) StartAnimationBlended(object, 6, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = RandomIntBelow(100);
        }
        if (*(s16 *)(state + 0x2D2)) {
            SetMobyState(object, 5, 3);
            if (RandomIntBelow(2)) {
                if (object[0x43] != 1) StartAnimationBlended(object, 1, 0, 10);
            } else if (object[0x43] != 4) StartAnimationBlended(object, 4, 0, 10);
        }
        if (angle > 2.7925272f)
            StartFlamethrowerRobotTurnAround(object);
        goal = state + 0x2A0;
        if (!object[0xBC] && vec_distance_xy(pos, goal) < 0.5f)
            object[0xBC] = 1;
        else if (*(s16 *)(state + 0x2D8))
            AimAtTargetOffset(object, goal);
        else
            TurnMobyTowardTarget(object, goal);
    }
    switch (object[0x20]) {
    case 3:
        if (SetFirstPendingFlag(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) StartAnimationBlended(object, 2, 0, 0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (object[0xBC] == 0 && *(s16 *)(state + 0x2D4) < (s32)*(u16 *)(object + 0x96)) {
            if (object[0x43] != 9) StartAnimationBlended(object, 9, 0, 10);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (IsPointInArenaPolygon(*(u8 **)(object + 0xB8), pos))
                SetMobyState(object, 4, 2);
            TurnMobyTowardTarget(object, GetArenaCenterPoint(*(u8 **)(object + 0xB8)));
        }
        break;
    case 5:
        if (object[0x60] & 2)
            SetMobyState(object, 7, -1);
        break;
    case 6:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != 8) StartAnimationBlended(object, 8, 0, 10);
            SetControllerSpeedLimits(object, 0.0044444446f, 0.13333334f, 0.003490659f, 0.4188791f);
        }
        StepMovementAtOwnPositionWithFactor(object, heading);
        if (object[0x60] & 2)
            SetMobyState(object, 7, -1);
        break;
    case 7:
        if (SetFirstPendingFlag(object)) {
            if (object[0x43] != 9) StartAnimationBlended(object, 9, 0, 15);
            *(u16 *)(state + 0x2D6) = 0;
        }
        if (D_L11_001B1D24 < range)
            turn(object, 0.0044444446f, 0.13333334f);
        else if (range < D_L11_001B1D20)
            turn(object, 0.0011111111f, 0.033333335f);
        if (object[0x42] != 12 && range < D_L11_001B1D18 && angle < 1.5707965f) {
            if (object[0x43] != 12) StartAnimationBlended(object, 12, 0, 10);
        } else if (object[0x42] == 12 && D_L11_001B1D1C < range) {
            if (object[0x43] != 9) StartAnimationBlended(object, 9, 0, 15);
        } else if (object[0x42] != 12 && D_L11_001B1D04 < range && range < D_L11_001B1D08 && !RandomIntBelow(D_L11_001B1D0C)) {
            if (FastDecTimer(state + 0x2D6) && object[0x31]) {
                u8 *other;
                s16 id;
                if (!CollLine(pos, &target, 1, object, 0) ||
                    ((other = D_L11_001C0D18[0]) != 0 && (id = *(s16 *)(other + 0xAA)) != 0xD98 /* moby class 3480 */ && id != 0xDCF /* moby class 3535 */ &&
                     id != 0xDF4 /* moby class 3572 */ && id != 0xDF7 /* moby class 3575 */ && id != 0xDF9 /* moby class 3577 */ && id != 0xD37 /* moby class 3383 */)) {
                    SetMobyState(object, 9, -1);
                    *(u16 *)(state + 0x2D6) = D_L11_001B1D10;
                }
            }
        } else if (range > 2.8f) {
            if (*(s16 *)(state + 0x2D8))
                AimAtTargetOffset(object, &target);
            else if (!AimAtGroupEntityInConeC(object))
                TurnTowardTargetAndStepMovement(object, target.f, *(float *)(state + 0x2C8));
        } else if (*(s16 *)(state + 0x2D8)) {
            FastVecSub(&work[0], &target, pos);
            UpdateObjectController(object, pos, &work[0]);
        } else
            StepMovementController(object, pos, heading);
        if (angle > 2.7925272f)
            StartFlamethrowerRobotTurnAround(object);
        if (object[0x42] == 12) {
            work[1].quad = 0;
            work[1].f[0] = *(float *)(object + 0x10);
            work[1].f[1] = *(float *)(object + 0x14);
            work[1].f[2] = *(float *)(object + 0x18);
            work[1].f[3] = 2.0f;
            work[0].quad = work[1].quad;
            if (object[0x31] || FastMathHelperA(work, 128.0f) > 0) {
                s32 i;
                s32 j;
                TransformMobyJointPoint(object, 4, &work[2]);
                qcopy(&work[1], &work[3]);
                TransformMobyJointToWorld(object, 4, &effect);
                vec_scale_to_length(&near_point, work + 1, 0.85f);
                vec_scale_to_length(&far_point, work + 1, 1.6f);
                vec_scale_to_length(&velocity, work + 3, 0.25f);
                vec_scale_to_length(work + 1, work + 1, 3.0f);
                FastVecAdd(&near_point, &near_point, &effect);
                FastVecAdd(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                far_point.f[2] -= 0.1f;
                i = 2;
                do {
                    float first;
                    float second;
                    float third;
                    AddRandomOffsetToVector(effect.f, 0.1f);
                    first = RandomFloatRange(0.2f, 0.4f) * 210000.0f;
                    second = RandomFloatRange(1.0f, 1.5f) * 210000.0f;
                    third = RandomSignedFloatRange(0.0f, 0.01f);
                    SpawnGravityFadeParticle(&effect, &velocity, 9, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        SweepCollisionFromObject(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        SweepCollisionFromObject(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        SweepCollisionFromObject(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                } while (--i >= 0);
                tmpl = &particle;
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = SpawnBurstParticle_002C16C0(&near_point, tmpl, 15, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L11_00200440.ids;
                        part[3] = 0x44;
                        if (RandomIntRange(0, 1)) {
                            u8 *tail;
                            u16 alpha;
                            part[3] = 0x48;
                            alpha = 127;
                            *(u32 *)(part + 4) = 0x70707F;
                            tail = part + 0x20;
                            tail[0x11] = 0x70;
                            tail[0x12] = 0x70;
                            tail[0x13] = 0x70;
                            *(u16 *)(tail + 0x1E) = alpha;
                        }
                    }
                }
            }
        }
        break;
    case 9:
        if (SetFirstPendingFlag(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 7) StartAnimationBlended(object, 7, 0, 10);
        }
        if (!object[0xBC] && angle < D_L11_001B1D14 * 0.017453294f) {
            object[0xBC] = 1;
            if (object[0x43] != 17) StartAnimationBlended(object, 17, 0, 10);
        } else if (*(s16 *)(state + 0x2D8))
            CheckMoveToPoint(object, &target);
        else
            StepMovementAtOwnPositionWithFactor(object, heading);
        if (object[0xBC] == 1) {
            float dist = GetMobyAnimationValue(object);
            if (IsValueWithinStepOfThreshold(object, 17.0f)) {
                work[2].quad = 0;
                work[2].f[2] = 1.0f;
                TransformMobyJointToWorld(object, 4, &work[0]);
                if (*(u8 **)(state + 0x2C4))
                    matrix_mul_vec3(&work[2], &work[2], *(u8 **)(state + 0x2C4) + 0xC0);
                else
                    matrix_mul_vec3(&work[2], &work[2], gHeroMoby_0018C0B0 + 0xC0);
                FastVecAdd(&work[2], &work[2], &target);
                FastVecSub(&work[1], &work[2], &work[0]);
                vec_scale_to_length(&work[1], &work[1], 0.33333334f);
                SpawnSpinningEffectMoby((float)state[0x35], object, &work[1], &work[0], 0, 0);
            } else if (dist < 17.0f && object[0x43] == 17) {
                float first;
                float second;
                TransformMobyJointToWorld(object, 4, &work[0]);
                first = RandomFloatRange(1.0f, 1.5f) * 210000.0f;
                second = RandomFloatRange(0.2f, 0.4f) * 210000.0f;
                SpawnGravityFadeParticle(&work[0], D_L11_001A8F20, 4, 0x808080, 9, 0x4F, 0, first, second, RandomSignedFloatRange(0.0f, 0.1f), 0);
            }
            if (object[0x60] & 2) {
                if (gActiveAttackerRobot == object || !RandomIntBelow(6))
                    SetMobyState(object, 10, -1);
                else
                    SetMobyState(object, 7, -1);
            }
        }
        break;
    case 10:
        if (SetFirstPendingFlag(object) && object[0x43] != 11)
            StartAnimationBlended(object, 11, 0, 7);
        if (object[0x60] & 2)
            SetMobyState(object, 7, -1);
        break;
    case 11: {
        unsigned long flags = DispatchActionByKind(object, state + 0x50);
        if (object[0x42] == 15) {
            if (RandomIntBelow(30) && (flags & 1UL) == 0)
                break;
            if (GetMobyAnimationValue(object) < 15.0f && *(s16 *)(state + 0x2D8) && !RandomIntBelow(2))
                SetMobyState(object, 12, -1);
            else {
                SetMobyAnimTypeThree(object, 0, -1);
                DeactivateFlamethrowerRobot(object);
            }
        } else if ((flags & 2UL) != 0)
            SetMobyState(object, 7, 3);
        break;
    }
    case 12: {
        u8 *launch = state + 0x1A0;
        s32 started = SetFirstPendingFlag(object);
        if (started) {
            s32 k;
            float *spin;
            FastVecSub(launch, GetArenaCenterPoint(*(u8 **)(object + 0xB8)), pos);
            *(float *)(state + 0x1A8) = 0.0f;
            vec_scale_to_length(launch, launch, RandomFloatRange(3.0f, 5.0f) * 0.016666668f);
            *(s16 *)(state + 0x2D8) = 0;
            spin = (float *)(state + 0x2B0);
            for (k = 0; k < 3; k++) {
                spin[k] = RandomFloatRange(240.0f, 720.0f) * 0.00029088825f;
                qcopy(&work[k], &((ActorVector *)(object + 0xC0))[k]);
            }
            GetEulerAnglesFromMatrix(work, object + 0xF0);
            if (object[0x43] != 18) StartAnimationBlended(object, 18, 0, 30);
            *(u16 *)(object + 0x34) &= 0xEFFF;
        }
        *(float *)(state + 0x1A8) -= *(float *)(state + 0x12C);
        SetControlMotionAndStep(object, launch);
        FastVecScale(state + 0x2B0, state + 0x2B0, 0.98f);
        {
            float f = *(float *)(object + 0x2C) * 0.0009765625f;
            count = 3;
            get_moby_joint_matrices(object, 1, &count, &work[1]);
            FastVecScale(&work[0], &work[4], f);
        }
        RotateObjectAboutPoint(*(float *)(state + 0x2B0), *(float *)(state + 0x2B4), *(float *)(state + 0x2B8), object, work);
        euler_rotation_basis(object + 0xC0, object + 0xF0);
        if (*(float *)(object + 0x18) < ((float *)GetArenaCenterPoint(*(u8 **)(object + 0xB8)))[2] + 5.0f ||
            !RandomIntBelow(450) || *(u16 *)(object + 0x96) >= 301) {
            SetMobyAnimTypeThree(object, 0, -1);
            DeactivateFlamethrowerRobot(object);
        }
        break;
    }
    }
    FinishFlamethrowerRobotFrame(object);
    AddDrawCallbackToList3(AddFlamethrowerRobotLights, object);
}
