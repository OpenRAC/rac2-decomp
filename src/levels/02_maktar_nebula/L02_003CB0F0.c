/* func_L02_003CB0F0 (5,824 bytes; twin func_L15_003DBB08). The last spot, in case 11, was
 * D_L02_001B30C8's absolute macro read (lui $v1; lw $v1 in one register, before the sra of
 * self): the sda incomplete-array declaration at -G0 gives it (docs/build/compiler-notes.md), and
 * retail compares the table value first.
 * The shape (big13): case bodies of the second switch in jump-table address order;
 * every state change written out per arm (retail cross-jumps the func_002A7750 tails); hero
 * fields through D_00189E20 directly (no resident pointer, which cost $s5 and the 0xC0 frame);
 * switch statements for the func_002A77E0 choices; retail's compare senses and arm orders;
 * case 10's own contact local and the collision record through L02Collision *col;
 * func_002B1C20 returns int; func_L02_00401530 is (p, p, p, float, float, float, int, int, int);
 * one frame area with two views (union work) for case 21's matrix, as func_L16_0040ECC0 does.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
struct L02NearObject;
struct L02GroupObject;
extern char D_00189E20[] NOT_SDA;
typedef struct { char pad[0x18]; char *hit; int count; } L02Collision;
extern L02Collision D_L02_001C0940;
extern char *D_L02_001FF1C0[];
extern int D_L02_001B30C8[] __attribute__((sda));
extern int func_L02_003CC7B0(char *), func_L02_003CCFE8(char *, void *);
extern void func_L02_003CCCC8(char *), func_L02_003CCEA0(char *), func_L02_003CD1E8(char *, void *), func_L02_003CD758(char *);
extern void func_L02_003CD298(struct L02NearObject *), func_L02_003CD4A8(struct L02GroupObject *), func_L02_003CED70(char *, void *, void *);
extern u8 *func_L02_003CEBB8(int);
extern void func_0029F338(void *), func_002A7750(u8 *, int, int), func_002A7470(char *, int, int, int), func_002A6C58(char *, void *, int);
extern int func_002B3868(u8 *), func_002B3890(u8 *), func_002A77E0(int), func_002A7820(int, int), func_00282978(short *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_002B1C20(void *, void *);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
/* The retail wrapper forwards B50E0's GPR flags. */
extern int func_L01_00321178(char *, char *), func_L01_00322288(int, float), func_L02_00331440(void *, void *, int, float, float, float), func_L02_00332630(char *, void *);
extern float func_00283248(float, float), func_00283C80(float, float), func_00282E48(void *, void *), func_00282E80(void *, void *), func_00282C48(float), func_00282DB0(void *, void *), func_0029F530(char *);
extern int func_002761F8(void *, void *, int, char *, void *), func_002ABB78(char *), func_002AEB60(char *, float), func_002ACBC8(void *, int), func_002B6120(char *, char *), func_002B6318(u8 *);
extern int func_002A8D70(float, float, float, void *, void *, int, int, int, int);
extern void func_0029FC20(char *, int, char *), func_0029FCC0(char *, int, char *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282D30(void *, void *, float);
extern void *func_L02_00401530(void *, void *, void *, float, float, float, int, int, int);
/* Runs a ranged enemy's patrol, attack, group coordination and projectile states. */
/* This is a view of observed fields, not the complete resident allocation. */
typedef struct {
    u8 prefix[0x80]; Vector position_80; u8 gap_90[0x40]; Vector target_d0;
    u8 gap_e0[0x21B0]; char *pointer_2290; u8 gap_2294[8]; int mode_229c;
    u8 gap_22a0[0x1FC]; char *pointer_249c;
} L02_ResidentCombatPrefix;
/* Per-frame update of the ranged enemy (moby class 2501). */
void func_L02_003CB0F0(char *self) {
    /* One frame area, two layouts: the aiming states and the case-21 hand-off. */
    union {
        struct { Vector muzzle, velocity, acceleration, transform[4]; } aim;
        struct { Vector frame[4], direction, origin; } relay;
    } work;
    char *state = *(char **)(self + 0x68), *path, *other;
    L02Collision *col;
    int flags;
    float angle, time, power;

    int choice, animation, collision, contact;
    if (UpdateLinkedChildMoby(self)) { MarkMobySpawned(self); return; }
    switch (((u8 *)self)[0x95]) {
    case 0:
        if (SetSecondPendingFlag((u8 *)self)) SetControllerSpeedLimits((u8 *)self, 0.0011111111380159855f, 0.050000004f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) {
            if (*(int *)(state + 0x33C)) { *(int *)(state + 0x33C) = 0; SetMobyState((u8 *)self, 8, 2); }
            else SetMobyState((u8 *)self, 10, 2);
        } else if (*(short *)(state + 0x382)) {
            SetMobyState((u8 *)self, 3, 1); *(short *)(state + 0x382) = 0; *(short *)(state + 0x374) = RandomIntRange(480, 600);
        }
        break;
    case 1:
        if (SetSecondPendingFlag((u8 *)self)) SetControllerSpeedLimits((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) SetMobyState((u8 *)self, 10, 2);
        else if (!*(short *)(state + 0x374)) {
            if (vec_distance_xy(self + 0x10, &((L02_ResidentCombatPrefix *)gHeroState)->position_80) > 26) SetMobyState((u8 *)self, 1, 0);
            else *(short *)(state + 0x374) = 120;
        }
        break;
    case 2:
        if (SetSecondPendingFlag((u8 *)self)) {
            DelayGroupMembersExceptNearest((struct L02NearObject *)self);
            SetControllerSpeedLimits((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        }
        if (*(int *)(state + 0x204) != 1 && (((u8 *)self)[0x60] & 2) && ((u8 *)self)[0x20] != 11) {
            if (fast_vec_dist(self + 0x10, state + 0x340) > 4) SetMobyState((u8 *)self, 6, -1);
            else {
                switch (RandomIntBelow(4)) {
                case 0: SetMobyState((u8 *)self, 3, 1); break;
                case 1: SetMobyState((u8 *)self, 4, 1); break;
                case 2: SetMobyState((u8 *)self, 5, 1); break;
                case 3: SetMobyState((u8 *)self, 7, 1); break;
                }
            }
            *(short *)(state + 0x374) = RandomIntRange(580, 600);
        }
        break;
    case 3:
        flags = DispatchActionByKind(self, state + 0x50);
        if (flags & 1) {
            *(u16 *)(*(char **)(state + 0x370) + 0x34) |= 0x41; *(u16 *)(*(char **)(state + 0x370) + 0x34) &= 0xEFFF; *(int *)(*(char **)(state + 0x370) + 0x98) = 0;
            SetDeathBits(self, 0, 3); QueueMobyForGlowEffect(self, 0, UpdateLinkedEffectMoby); return;
        }
        if (flags & 2) {
            *(int *)(state + 0x33C) = 0;
            if (*(int *)(state + 0x320) != -1) SetMobyState((u8 *)self, 18, 4);
            else if (*(int *)(state + 0x204) == 1) SetMobyState((u8 *)self, 10, 2);
            else { SetMobyState((u8 *)self, 3, 1); *(short *)(state + 0x374) = RandomIntRange(580, 600); }

        }
        break;
    case 4:
        if (SetSecondPendingFlag((u8 *)self)) {
            SetControllerSpeedLimits((u8 *)self, 0.0033333334140479565f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f); *(float *)(state + 0x134) = 0.25f;
        }
        break;
    }
    switch (((u8 *)self)[0x20]) {
    case 1:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43]) StartAnimationBlended(self, 0, 0, 20);
        if (!(((u8 *)self)[0x60] & 2)) break;
        if (!RandomIntBelow(4)) { SetMobyState((u8 *)self, 5, -1); break; }
        else if (!*(int *)(state + 0x33C)) { SetMobyState((u8 *)self, 2, -1); break; }
        break;
    case 2:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (((u8 *)self)[0x43] != 5) StartAnimationBlended(self, 5, 0, 20); SetRandomSpreadVelocity(self, state + 0x350);
        }
        if ((TurnMobyTowardTarget(self, state + 0x350) & 0x80) || *(u16 *)(self + 0x96) >= 181 || *(int *)(state + 0x180) >= 21) { SetMobyState((u8 *)self, 5, -1); break; }
        break;
    case 3:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 9) StartAnimationBlended(self, 9, 0, 20);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.26179942f) { SetMobyState((u8 *)self, 9, -1); break; }
        else if ((((u8 *)self)[0x60] & 2) && RandomIntBelow(2)) {
            switch (RandomIntBelow(3)) {
            case 0: SetMobyState((u8 *)self, 4, -1); break;
            case 1: SetMobyState((u8 *)self, 5, -1); break;
            case 2: SetMobyState((u8 *)self, 7, -1); break;
            }

        }
        break;
    case 4:
        if (SetFirstPendingFlag((u8 *)self)) {
            animation = ComputeAlignedDirection(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) StartAnimationBlended(self, animation, 0, 10);
        }
        angle = FastMatrixHelperA(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((MoveToTargetWithTempLimits(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) >= 121) { SetMobyState((u8 *)self, 3, -1); break; }
        break;
    case 5:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1 && ((u8 *)self)[0x43] != RandomIntBelow(2) + 3) StartAnimationBlended(self, RandomIntBelow(2) + 3, 0, 20); }
            else if (((u8 *)self)[0x43] != 1) StartAnimationBlended(self, 1, 0, 20);
        }
        if (((u8 *)self)[0x60] & 2) { if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1) { SetMobyState((u8 *)self, 3, -1); break; } } else { SetMobyState((u8 *)self, 1, -1); break; } }

        break;
    case 7:
        if (SetFirstPendingFlag((u8 *)self)) { animation = RandomIntBelow(2) ? 20 : 21; if (((u8 *)self)[0x43] != animation) StartAnimationBlended(self, animation, 0, 15); }
        if (((u8 *)self)[0x60] & 2) { SetMobyState((u8 *)self, 3, -1); break; }
        break;
    case 6:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 6) StartAnimationBlended(self, 6, 0, 15);
        if ((TurnMobyTowardTarget(self, state + 0x340) & 0x80) || *(u16 *)(self + 0x96) >= 241) { SetMobyState((u8 *)self, 3, -1); break; }
        break;
    case 9:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 5) StartAnimationBlended(self, 5, 0, 10);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        StartMobyEffectFromEntry((int)self, angle); AimTurretAtPlayer(self);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) < 0.087266475f) {
            switch (((u8 *)self)[0x95]) {
            case 2: SetMobyState((u8 *)self, 10, -1); break;
            case 1: SetMobyState((u8 *)self, 3, -1); break;
            }

        }

        break;
    case 8:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 2) StartAnimationBlended(self, 2, 0, 10);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        StartMobyEffectFromEntry((int)self, angle); AimTurretAtPlayer(self); if (((u8 *)self)[0x60] & 2) { SetMobyState((u8 *)self, 10, -1); break; }
        break;
    case 10:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 9) StartAnimationBlended(self, 9, 0, 20);
        AimTurretAtPlayer(self);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) { { SetMobyState((u8 *)self, 9, -1); break; } break; }
        if (!*(short *)(state + 0x378) && *(u16 *)(self + 0x96) > 15) {
            TransformMobyJointToWorld(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            contact = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)gHeroState)->target_d0, 16, self, 0);
            if (contact && D_L02_001C0940.hit && *(short *)(D_L02_001C0940.hit + 0xAA) == 0xC1B /* moby class 3099 */) { { SetMobyState((u8 *)self, 13, -1); break; } break; }
            if (contact && (col = &D_L02_001C0940)->hit != ((L02_ResidentCombatPrefix *)gHeroState)->pointer_2290 && !*(short *)(state + 0x386)) {
                if (!col->hit || (!IsMobyInSpecialClassRange(col->hit) && (!*(char **)(col->hit + 0x24) || *(short *)(*(char **)(col->hit + 0x24) + 0x46) != 22))) break;
            }
            { SetMobyState((u8 *)self, 11, -1); break; }
        } else {
            if (vec_distance_xy(self + 0x10, &((L02_ResidentCombatPrefix *)gHeroState)->position_80) < 3 && FloatAbs(*(float *)(self + 0x18) - ((L02_ResidentCombatPrefix *)gHeroState)->position_80.f[2]) < 0.5f) { { SetMobyState((u8 *)self, 14, -1); break; } break; }
            if ((((u8 *)self)[0x60] & 2) && !RandomIntBelow(2)) { SetMobyState((u8 *)self, 13, -1); break; }
        }
        break;
    case 13:
        if (SetFirstPendingFlag((u8 *)self)) {
            animation = ComputeAlignedDirection(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) StartAnimationBlended(self, animation, 0, 10);
        }
        angle = FastMatrixHelperA(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((MoveToTargetWithTempLimits(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) > 120 || *(int *)(state + 0x180) >= 21) { SetMobyState((u8 *)self, 10, -1); break; }
        break;
    case 11:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (((u8 *)self)[0x43] != 10) StartAnimationBlended(self, 10, 0, 10);
            *(short *)(state + 0x380) = RandomIntRange(3, 5); RandomizeGroupTimers((struct L02GroupObject *)self);
            qcopy(state + 0x360,state + 0x1F0); *(float *)(state + 0x368) += 0.5f;
        }
        AimTurretAtPlayer(self);
        if ((gFrameCounter_L02[0] & 15) == (((int)self >> 8) & 15))
 RandomizeGroupTimers((struct L02GroupObject *)self);
        if (IsValueWithinStepOfThreshold(self, 5)) {
            TransformMobyJointToWorld(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            FastVecSub(&work.aim.velocity, state + 0x360, &work.aim.muzzle); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 0.23333334922790527f);
            FastVecScale(&work.aim.acceleration, &work.aim.velocity, 0.25f);
            power = (float)(u8)state[0x34];
            if (*(short *)(state + 0x380) >= 2)
                SpawnTrailEffectMoby_L02(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 10, 30, 1);
            else
                SpawnTrailEffectMoby_L02(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 30, 80, 1);
            break;
        }
        if (!(((u8 *)self)[0x60] & 2)) break;
        TransformMobyJointToWorld(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
        collision = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)gHeroState)->target_d0, 0, self, 0);
        if (FastDecTimer((short *)(state + 0x380)) || (collision && D_L02_001C0940.hit != ((L02_ResidentCombatPrefix *)gHeroState)->pointer_2290)) {
            *(short *)(state + 0x378) += 15; { if (!RandomIntBelow(3)) SetMobyState((u8 *)self, 12, -1); else SetMobyState((u8 *)self, 13, -1); break; }
        } else {
            angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) { SetMobyState((u8 *)self, 9, -1); break; }
            else if (((L02_ResidentCombatPrefix *)gHeroState)->mode_229c == 7 && ((L02_ResidentCombatPrefix *)gHeroState)->pointer_249c && *(short *)(((L02_ResidentCombatPrefix *)gHeroState)->pointer_249c + 0xAA) == 0xB5A /* moby class 2906 */) { SetMobyState((u8 *)self, 12, -1); break; }
        }
        break;
    case 14:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 13) StartAnimationBlended(self, 13, 0, 10);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        StartMobyEffectFromEntry((int)self, angle); time = GetMobyAnimationValue(self);
        if (time >= 11 && time < 12.5f) TestHitAtBone(0.6f, (float)(u8)state[0x35], 3.0f, self, (void *)3, 1, 0, 1, 0);
        if (((u8 *)self)[0x60] & 2) { SetMobyState((u8 *)self, 15, -1); break; }
        break;
    case 15:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 11) StartAnimationBlended(self, 11, 10, 10);
        AimTurretAtPlayer(self); if (!(((u8 *)self)[0x60] & 2)) break;
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) SetMobyState((u8 *)self, 9, -1); else SetMobyState((u8 *)self, 11, -1);
        break;
    case 12:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (((L02_ResidentCombatPrefix *)gHeroState)->mode_229c == 7) { if (((u8 *)self)[0x43] != 12) StartAnimationBlended(self, 12, 0, 20); }
            else if (((u8 *)self)[0x43] != 11) StartAnimationBlended(self, 11, 0, 20);
        }

        AimTurretAtPlayer(self); if (((u8 *)self)[0x60] & 2) { SetMobyState((u8 *)self, 10, -1); break; }
        break;
    case 16:
        if (!(*(float *)(state + 0x20) > 0)) {

            if (SetFirstPendingFlag((u8 *)self)) { *(short *)(state + 0x378) = RandomIntRange(10, 15); *(short *)(state + 0x384) = RandomIntBelow(3) == 0; }
            if (*(short *)(state + 0x384) && FastDecTimer((short *)(state + 0x378))) {
                TransformMobyJointPoint(*(char **)(state + 0x370), 0, (char *)work.aim.transform);
                vec_scale_to_length(&work.aim.muzzle, work.aim.transform, 0.23333334922790527f);
                FastVecSub(&work.aim.velocity, gHeroState + 0xE0, &work.aim.transform[3]); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 1);
                if (FastVecDot(&work.aim.velocity, work.aim.transform) < 0.2f) {
                SpawnTrailEffectMoby_L02(&work.aim.transform[3], &work.aim.muzzle, &work.aim.muzzle, 1.0f, 0.0f, 1.0f, 30, 80, 1);
                    *(short *)(state + 0x378) = RandomIntRange(15, 30);
                }
            }
        }
        break;
    case 17:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43]) StartAnimationBlended(self, 0, 0, 20);
        if (IsPointInCuboid(&((L02_ResidentCombatPrefix *)gHeroState)->position_80, *(int *)(state + 0x324)) || *(int *)(state + 0x204) == 1) { SetMobyState((u8 *)self, 18, -1); break; }
        break;
    case 18:
        path = gRoutePolygons[*(int *)(state + 0x320)];
        if (SetFirstPendingFlag((u8 *)self)) { if (((u8 *)self)[0x43] != 6) StartAnimationBlended(self, 6, 0, 20); CheckObjectInsidePolygon((u8 *)self); }
        if (!(vec_distance_xy(self + 0x10, path + *(int *)path * 16) < *(float *)(state + 0x134)) && !FollowPathNodes(self, path)) break;

        if (((u8 *)self)[0x43] != 2) {
            angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (FastDiffRots(*(float *)(self + 0xF8), angle > 0.3490659f ? 1.0f : 0.0f) != 0 && ((u8 *)self)[0x43] != 2) StartAnimationBlended(self, 2, 5, 10);
        }
        CheckTargetPointFromOffset(self, state + 0x1F0);
        angle = FastMatrixHelperA(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) < 0.087266475f && (((u8 *)self)[0x43] != 2 || (((u8 *)self)[0x60] & 2))) {
            *(int *)(state + 0x320) = -1; qcopy(state + 0x340,self + 0x10);
            if (*(int *)(state + 0x328) != -1) SetMobyState((u8 *)self, 19, 4); else SetMobyState((u8 *)self, 1, 0);

        }
        break;
    case 22:
        if (SetFirstPendingFlag((u8 *)self)) { if (((u8 *)self)[0x43] != 6) StartAnimationBlended(self, 6, 0, 20); CheckObjectInsidePolygon((u8 *)self); }
        if (TurnMobyTowardTarget(self, state + 0x340) & 0x80) { SetMobyState((u8 *)self, 1, 0); qcopy(state + 0x340,self + 0x10); }
        break;
    case 19:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43]) StartAnimationBlended(self, 0, 0, 20);
        if (*(int *)(state + 0x32C) == -1 || IsPointInCuboid(&((L02_ResidentCombatPrefix *)gHeroState)->position_80, *(int *)(state + 0x32C)) || *(int *)(state + 0x204) == 1) { SetMobyState((u8 *)self, 20, -1); break; }
        break;
    case 20:
        if (SetFirstPendingFlag((u8 *)self)) {
            if (((u8 *)self)[0x43] != 9) StartAnimationBlended(self, 9, 0, 20);
            if (*(float *)(state + 0x37C) == 0) *(float *)(state + 0x37C) = RandomIntBelow(2) ? 0.3490659f : -0.3490659f;
            else *(float *)(state + 0x37C) = -*(float *)(state + 0x37C);
        }
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (*(u16 *)(self + 0x96) < 11) break;
        if (FindGroupMobyInState13(*(int *)(state + 0x328))) SetMobyState((u8 *)self, 21, -1); else SetMobyState((u8 *)self, 3, 1);
        break;
    case 21:
        if (SetFirstPendingFlag((u8 *)self) && ((u8 *)self)[0x43] != 10) StartAnimationBlended(self, 10, 0, 10);
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (IsValueWithinStepOfThreshold(self, 5)) {
            if ((other = (char *)FindGroupMobyInState13(*(int *)(state + 0x328))) != 0) {
                TransformMobyJointPoint(*(char **)(state + 0x370), 0, (char *)work.relay.frame);
                vec_scale_to_length(&work.relay.direction, work.relay.frame, 0.23333334922790527f);
                {
                    Quad q = *(Quad *)&work.relay.frame[3];
                    *(Quad *)&work.relay.origin = q;
                }
                TeleportObjectToNewPose(other, &work.relay.origin, &work.relay.direction);
            }
        } else if (((u8 *)self)[0x60] & 2) SetMobyState((u8 *)self, 20, -1);

        break;
    }
    UpdateGlowPulseAndTimers(self);
}
