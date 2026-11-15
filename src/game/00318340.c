#include "include_asm.h"
#include "common.h"

extern int D_001B2758 MACRO_ADDR;
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern void func_00282C88(void *), func_002B00B0(void *, void *, int);
extern char *func_002AB1F0(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float), func_002A7820(int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern float D_001BAFA8;

typedef int TI128_00318340 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_00318340 q[0x260]; } Hero_00318340;
extern u8 D_00189E20[];
extern char D_00189EA0[];
extern u8 D_00188660[];

extern char D_001A8BD0[16] MACRO_ADDR;
extern char D_001AFA80[];
extern void func_0026FEB8(const char *, ...);
extern void func_0027CFD0(void (*)(char *), char *);
extern int func_00282948(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_0029F338(void *);
extern float func_0029F530(void *);
extern void func_002A6C58(void *, int, int);
extern int func_002A77E0(int);
extern void func_002A7E08(void *, void *, void *, float, float, float);
extern float func_002A89A8(void *, int, float);
extern float func_002AA3A8(void *, float, void *, float, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_002AC728(void *, void *, int, float, float);
extern int func_002ACBC8(void *, int);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_002AEB60(void *, float);
extern int func_002B3868(void *);
extern int func_002B38B8(void *);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_00319780(char *);
extern void func_00319FB8(char *);
extern void func_00319EC0(char *);
extern int func_0031A580(char *);
extern int func_0031A628(char *);
extern int func_0031A708(unsigned char *);
extern int func_0031A848(char *, float);
extern void func_0031AAB0(char *);
extern void *func_003280C8(char *, void *, void *, int, int, float);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AEF28(float, float, char *, char *, float, char *);

/* One of the twelve 0xA0-byte records at *D_001B2758 that func_0031DEE8 steps for their
   owner: the boot counterpart of the level records func_L00_003BBB68 updates. */
typedef struct {
    float out0[4];          /* 0x00: ang0 through the two angle helpers, times amp0 */
    float out1[4];          /* 0x10: the same for ang1 */
    float start[4];         /* 0x20: copied from the owner's position each frame */
    float pos[4];           /* 0x30: follows the target */
    float ang0[3];          /* 0x40 */
    float rate0[3];         /* 0x4C */
    float amp0[3];          /* 0x58 */
    float ang1[3];          /* 0x64 */
    float rate1[3];         /* 0x70 */
    float amp1[3];          /* 0x7C */
    int life;               /* 0x88: timer, frees the record when it expires */
    char *owner;            /* 0x8C */
    char *target;           /* 0x90 */
    int time;               /* 0x94: timer, also counts the approach */
    int duration;           /* 0x98 */
    int hit;                /* 0x9C */
} Slot31DEE8;

/* The 0xE0-byte class records; D_00139568 maps a class number to its record. */
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class31DEE8;

extern unsigned char D_00139568[];
extern Class31DEE8 D_00239BA0[];
extern float func_00283B98(float angle, float step);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern float func_00283CE0(int ticks);
extern int func_00282948(void *timer);
extern void func_00282D08(void *out, void *from, void *to, float t);
extern void func_002A8C00(void *packet, char *owner, int flags, void *direction, float amount);
extern void func_002A8E20(char *target, void *packet);
extern void func_0031F6E8(void *pos, int count, int mode);
extern void func_0032D758(char *target, int kind, int value);

extern char F669d6320_D_001BAFC0[];

extern void F669d6320_FUN_00282F20(void *out, void *in, float scale);

extern void F669d6320_FUN_00282CC0(void *out, void *in1, void *in2);

extern int F669d6320_FUN_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void F669d6320_FUN_00282D30(void *out, void *in, float scale);

extern void F2c74c194_FUN_00282D30(char *dst, char *src, float scale);

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);

extern void F5a19df7a_FUN_0031E2A0(char *p);

extern void F5a19df7a_FUN_0031E560(char *p);

extern char *F5a19df7a_FUN_002A7820(int a, int b);

extern float F5a19df7a_FUN_002A7940(void);

extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

extern void Fc936841d_FUN_00282CF0(char *local, char *first, char *second);

extern void Fc936841d_FUN_00282CC0(char *target, char *first, char *local);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* The four 16-byte blocks the record carries and scales. */
#ifndef RAC2_T_BLOCK_0031A340
#define RAC2_T_BLOCK_0031A340
typedef struct {
    float q[4];
} Block_0031a340;
#endif

/* The 240-byte record func_0031A340 builds: a scaled matrix, a colour, the
   looked-up handle, the fixed fields and the two computed vectors. */
#ifndef RAC2_T_LOC_0031A340
#define RAC2_T_LOC_0031A340
typedef struct {
    Block_0031a340 b0;
    Block_0031a340 b1;
    Block_0031a340 b2;
    Block_0031a340 b3;
    int k0;
    int k1;
    int k2;
    int k3;
    int z80;
    int z84;
    int z88;
    float f92;
    float f96;
    int z100;
    float f104;
    float f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float v192;
    float v196;
    float v200;
    float v204;
    float v208;
    float f212;
    float f216;
    float v220;
    float e0;
    float e1;
    float e2;
    float e3;
} Loc_0031a340;
#endif

/* The state block whose +0x140 holds the position the record is built around. */
#ifndef RAC2_T_STATE_001B5200
#define RAC2_T_STATE_001B5200
typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;
#endif

extern State_001b5200 D_001B5200;

extern void func_002A91F0(void *, float *);

extern int func_00317D78(char *);
extern int func_002B3890(char *);
extern int func_002B1C20(char *, char *);
extern void func_002E59F8(int);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_002A677C(void *);
extern int func_002B4FF0(void *, void *, float);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_00318200(char *);
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *D_001F1700[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");

#undef FI
#undef FF
#undef FH
#undef FU
#undef FB
#undef FP

extern void func_003182C0(void *);



extern void func_002AB8C0(char *, char *);
extern int func_00282978(void *);
extern void func_002AEE70(char *, float, float, char *, float, char *);
extern void func_002AEF28(float, float, char *, char *, float, char *);

/* A moby's per-frame update: pvars at moby+0x68, a switch on moby+0x95, a switch on the state at
   moby+0x20, then the sound-slot keep-alive on pvars+0x2C4. The template vector is MACRO_ADDR: retail
   schedules its address as one `la`, not a split %hi/%lo pair. func_L00_003BD7E0 is the level twin. */
/* Updates one flying enemy each frame: picks its next action, moves it, aims and fires at the hero, and keeps its sound playing. */
void func_00318340(char *obj)
{
    f32 muzzlePos[4] __attribute__((aligned(16)));
    f32 targetPos[4] __attribute__((aligned(16)));
    f32 aimDir[4] __attribute__((aligned(16)));
    f32 axis[4] __attribute__((aligned(16)));
    f32 toTarget[4] __attribute__((aligned(16)));
    char *pv = *(char **)(obj + 0x68);
    char *tgt13, *tgt10, *tgt16;
    f32 *pos;
    s32 *path;
    int id;
    int mode0, mode2, flags, stateNow;
    float h13, h12, floor12, y12, diff12, h5, diff5, dist10, dot, dist11, dist16, sx, sy, sz;

    if (((Hero_00318340 *)gHeroState)->b[0x22B4] == 1)
        return;
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        if (*(s32 *)(pv + 0x2E0) != 0 && IsThirdPendingFlagSet(obj) == 0)
            break;
        if (SetSecondPendingFlag(obj) != 0)
            SetControllerSpeedLimits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        mode0 = *(s32 *)(pv + 0x34);
        if (mode0 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (FastFloatHelperD(pv + 0x2D0) != 0) {
                SetMobyState(obj, 9, 3);
                if (*(u8 *)(obj + 0x43) != mode0)
                    StartAnimationBlended(obj, 1, 0, 4);
            }
        } else if (*(s16 *)(pv + 0x286) != 0) {
            SetMobyState(obj, 8, 2);
            *(s16 *)(pv + 0x286) = 0;
            if (*(s16 *)(pv + 0x280) < 300)
                *(s16 *)(pv + 0x280) = RandomIntRange(0x1E0, 0x258);
        }
        break;
    case 2:
        if (SetSecondPendingFlag(obj) != 0) {
            SetControllerSpeedLimits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        mode2 = *(s32 *)(pv + 0x34);
        if (mode2 == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            SetMobyState(obj, 9, 3);
            if (*(u8 *)(obj + 0x43) != mode2)
                StartAnimationBlended(obj, 1, 0, 4);
        } else if (*(s16 *)(pv + 0x280) == 0) {
            SetMobyState(obj, 2, 0);
            if (*(u8 *)(obj + 0x43) != 2)
                StartAnimationBlended(obj, 2, 0, 10);
        }
        break;
    case 1:
        if (SetSecondPendingFlag(obj) != 0)
            SetControllerSpeedLimits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(pv + 0x34) == 1 && *(s32 *)(pv + 0x2A4) != 0) {
            if (FastFloatHelperD(pv + 0x2D0) == 0)
                break;
        } else {
            if (*(s16 *)(pv + 0x286) == 0 || *(s32 *)(pv + 0x2A4) == 0)
                break;
            *(s16 *)(pv + 0x286) = 0;
        }
        SetMobyState(obj, 0xD, 3);
        if (*(u8 *)(obj + 0x43) != 0x19)
            StartAnimationBlended(obj, 0x19, 0, 4);
        break;
    case 3:
        if (SetSecondPendingFlag(obj) != 0) {
            SetControllerSpeedLimits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(f32 *)(obj + 0x48) = 1.0f;
        }
        if (*(s32 *)(pv + 0x34) != 1 && *(u8 *)(obj + 0x20) != 0xD && *(u8 *)(obj + 0x20) != 0xC && *(u8 *)(obj + 0x20) != 0xF) {
            SetMobyState(obj, 8, 2);
            if (*(u8 *)(obj + 0x43) != 6)
                StartAnimationBlended(obj, 6, 0, 10);
            *(s16 *)(pv + 0x280) = RandomIntRange(0x244, 0x258);
            if (*(s32 *)(pv + 0x28C) != 0) {
                SetMobyState(obj, 3, 1);
                if (*(u8 *)(obj + 0x43) != 0xB)
                    StartAnimationBlended(obj, 0xB, 0, 0x14);
            }
        }
        break;
    case 4:
        if (SetFirstPendingFlag(obj) != 0)
            *(s16 *)(pv + 0x46) = 0x3C;
        flags = DispatchActionByKind(obj, pv + 0x80);
        if ((flags & 1) || *(f32 *)(pv + 0x40) <= 0.0f) {
            SpawnExplosionWithSparks(obj, obj + 0x10, -1, 1.0f, 13.0f);
            SetDeathBits(obj, 0, 3);
            MarkMobySpawned(obj);
            return;
        }
        if (flags & 2) {
            if (*(s32 *)(pv + 0x34) == 1) {
                SetMobyState(obj, 7, 3);
                if (*(u8 *)(obj + 0x43) != 7)
                    StartAnimationBlended(obj, 7, 0, 6);
            } else {
                SetMobyState(obj, 8, 2);
                if (*(u8 *)(obj + 0x43) != 6)
                    StartAnimationBlended(obj, 6, 0, 10);
                *(s16 *)(pv + 0x280) = RandomIntRange(0x244, 0x258);
            }
            if (*(s32 *)(pv + 0x2A4) != 1)
                *(s32 *)(pv + 0x2A4) = 1;
        }
        break;
    }

    switch (*(u8 *)(obj + 0x20)) {
    case 2:
        break;
    case 7:
        if (IsTargetOutsideTurnLimit(obj, 10.0f) != 0) {
            TurnTowardTargetMoby(obj);
        } else {
            SetMobyState(obj, 0xA, -1);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                StartAnimationBlended(obj, 0x1E, 0, 6);
        }
        break;
    case 3:
        ScaleOwnerWordsByAngles(0.06981318f, 0.052359886f, obj, pv + 0x2A8, 0.013089972f, pv + 0x2AC);
        break;
    case 13:
        tgt13 = *(char **)(pv + 0x30);
        *(s32 *)(pv + 0x2C0) += 1;
        if (tgt13 != 0) {
            TurnTowardPosition(obj, tgt13, pv + 0x29C, 0.001f, 0.01f, 0.1f);
            SpringFloatToGoal(obj + 0xF4, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            SpringFloatToGoal(obj + 0xF0, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            h13 = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
            if (*(f32 *)(obj + 0x18) - h13 > 0.05f) {
                *(f32 *)(obj + 0x18) -= h13 * 0.00025f;
            } else {
                SetMobyState(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    StartAnimationBlended(obj, 0xE, 0, 3);
            }
            if (*(u8 *)(obj + 0x60) & 2) {
                SetMobyState(obj, 0xC, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    StartAnimationBlended(obj, 0x1A, 0, 0xF);
            }
        }
        break;
    case 12:
        *(s32 *)(pv + 0x2C0) += 1;
        TurnTowardTargetMoby(obj);
        h12 = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
        y12 = *(f32 *)(obj + 0x18);
        floor12 = *(f32 *)(pv + 0x2DC);
        diff12 = y12 - h12;
        h12 -= 3.0f;
        if (floor12 != -1.0f && y12 <= floor12) {
            if (IsMobyInGroup(obj) == 0) {
                SetMobyState(obj, 0x10, -1);
                if (*(u8 *)(obj + 0x43) != 0x1D)
                    StartAnimationBlended(obj, 0x1D, 0, 3);
            } else {
                *(s32 *)(pv + 0x354) = 0;
                ClaimGroupLeadToken(obj);
                SetMobyState(obj, 0xE, -1);
            }
        } else if (diff12 > 0.05f) {
            StepValueTowardTarget(obj + 0x18, pv + 0x290, h12, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            STUB_printf(D_001AFA80, *(s32 *)(pv + 0x2C0));
            SetMobyState(obj, 6, -1);
            if (*(u8 *)(obj + 0x43) != 0xE)
                StartAnimationBlended(obj, 0xE, 0, 3);
        }
        break;
    case 14:
        if (SetFirstPendingFlag(obj) != 0) {
            *(TI128_00318340 *)(pv + 0x360) = *(TI128_00318340 *)(obj + 0x10);
            if (*(s32 *)(pv + 0x350) != 0)
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + RandomFloatRange(4.0f, 7.0f);
            else
                *(f32 *)(pv + 0x368) = *(f32 *)(pv + 0x2DC) + RandomFloatRange(-3.0f, 3.0f);
        }
        if (fast_vec_dist(obj + 0x10, pv + 0x360) < 0.05f) {
            *(s32 *)(pv + 0x354) = 0;
            SetMobyState(obj, 0x10, -1);
        }
        *(s32 *)(pv + 0x2C0) += 1;
        TurnTowardTargetMoby(obj);
        StepValueTowardTarget(obj + 0x18, pv + 0x290, *(f32 *)(pv + 0x368), 0.004166667f, 0.004166667f, 0.16666667f);
        break;
    case 4:
        if (*(u8 *)(obj + 0x60) & 2) {
            SetMobyState(obj, 5, -1);
            if (*(u8 *)(obj + 0x43) != 0xD)
                StartAnimationBlended(obj, 0xD, 0, 0xF);
        }
        break;
    case 5:
        if (*(char **)(pv + 0x30) != 0) {
            SpringFloatToGoal(obj + 0xF4, 0.0f, pv + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            TurnTowardPosition(obj, *(char **)(pv + 0x30), pv + 0x29C, 0.001f, 0.01f, 0.1f);
            h5 = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
            diff5 = *(f32 *)(obj + 0x18) - h5;
            h5 -= 3.0f;
            if (diff5 > 0.05f) {
                StepValueTowardTarget(obj + 0x18, pv + 0x290, h5, 0.025000002f, 0.16333334f, 0.25f);
            } else {
                SetMobyState(obj, 6, -1);
                if (*(u8 *)(obj + 0x43) != 0xE)
                    StartAnimationBlended(obj, 0xE, 0, 3);
            }
        }
        break;
    case 6:
        if (*(u8 *)(obj + 0x60) & 2) {
            SetMobyState(obj, 0xA, 3);
            if (*(u8 *)(obj + 0x43) != 0x1E)
                StartAnimationBlended(obj, 0x1E, 0, 6);
            *(f32 *)(obj + 0x18) = ProbeGroundHeightBelow(obj + 0x10, 0, 0.5f);
        }
        break;
    case 9:
        if (*(u8 *)(obj + 0x60) & 2) {
            SetControllerSpeedLimits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            SetMobyState(obj, 7, -1);
            if (*(u8 *)(obj + 0x43) != 7)
                StartAnimationBlended(obj, 7, 0, 6);
        }
        break;
    case 10:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (IsTargetOutsideTurnLimit(obj, 10.0f) != 0) {
                SetMobyState(obj, 7, -1);
                if (*(u8 *)(obj + 0x43) != 7)
                    StartAnimationBlended(obj, 7, 0, 6);
            } else if (((Hero_00318340 *)gHeroState)->ptr[0x249C / 4] == (u8 *)obj || RandomIntBelow(6) == 1) {
                SetMobyState(obj, 0xB, -1);
                if (*(u8 *)(obj + 0x43) != 0x10)
                    StartAnimationBlended(obj, 0x10, 0, 7);
            }
        }
        dist10 = GetMobyAnimationValue(obj);
        if (IsValueWithinStepOfThreshold(obj, 17.0f) != 0) {
            TransformMobyJointToWorld(obj, 4, muzzlePos);
            tgt10 = *(char **)(pv + 0x30);
            if (tgt10 == (char *)((Hero_00318340 *)gHeroState)->ptr[0x2290 / 4]) {
                qcopy(targetPos, &((Hero_00318340 *)gHeroState)->q[0xD0 / 16]);
                pos = targetPos;
            } else {
                if (tgt10 == 0)
                    break;
                qcopy(targetPos, tgt10 + 0x10);
                pos = targetPos;
                targetPos[2] += *(f32 *)(tgt10 + 0xC) * 0.0009765625f;
            }
            if (IsTargetOutsideTurnLimit(obj, 10.0f) != 0) {
                FastVecSub(toTarget, pos, muzzlePos);
                qcopy(aimDir, D_001A8BD0);
                aimDir[0] = 1.0f;
                matrix_mul_vec3(aimDir, aimDir, obj + 0xC0);
                FastVecCross(axis, aimDir, toTarget);
                dot = FastVecDot(aimDir, toTarget);
                if (dot > 0.0f)
                    ApplyAxisRotationToQuaternion(aimDir, aimDir, axis, -0.17453294f);
                else
                    ApplyAxisRotationToQuaternion(aimDir, aimDir, axis, 0.17453294f);
            } else {
                FastVecSub(aimDir, pos, muzzlePos);
            }
            vec_scale_to_length(aimDir, aimDir, 0.33333334f);
            SpawnSpinningEffectMoby(obj, aimDir, muzzlePos, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist10 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            TransformMobyJointToWorld(obj, 4, muzzlePos);
        }
        break;
    case 11:
        if (*(u8 *)(obj + 0x60) & 2) {
            if (vec_distance_xy(obj + 0x10, gHeroPosition) > 4.0f) {
                SetControllerSpeedLimits(obj, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                SetMobyState(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    StartAnimationBlended(obj, 0x1E, 0, 6);
            } else {
                SetControllerSpeedLimits(obj, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                SetMobyState(obj, 0xA, -1);
                if (*(u8 *)(obj + 0x43) != 0x1E)
                    StartAnimationBlended(obj, 0x1E, 0, 6);
            }
        }
        dist11 = GetMobyAnimationValue(obj);
        if (*(u8 *)(obj + 0x42) == 0x10 && (dist11 <= 5.0f || (dist11 >= 12.0f && dist11 <= 15.0f)))
            *(s32 *)(pv + 0x2C8) = 1;
        else
            *(s32 *)(pv + 0x2C8) = 0;
        break;
    case 15:
        if (SetFirstPendingFlag(obj) != 0) {
            *(f32 *)(pv + 0x374) = 0.0f;
            *(f32 *)(pv + 0x378) = 0.0f;
        }
        if (*(s32 *)(pv + 0x37C) == 0) {
            if (IsPointInCuboid(gHeroPosition, *(s32 *)(pv + 0x35C)) != 0)
                *(s32 *)(pv + 0x37C) = 1;
        } else {
            path = (s32 *)gPathTable_001F1700[*(s32 *)(pv + 0x370)];
            StepValueTowardTarget(pv + 0x374, pv + 0x378, (f32)(*path - 1), 0.013888889f, 0.0013888889f, 0.33333334f);
            SamplePathPosition(path, 0, obj + 0x10, obj + 0xF0, 0, *(f32 *)(pv + 0x374));
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            if ((f32)(*path - 1) <= *(f32 *)(pv + 0x374))
                SetMobyState(obj, 0xA, 3);
        }
        break;
    case 16:
        if ((*(u8 *)(obj + 0x60) & 2) && IsMobyInGroup(obj) != 0) {
            *(s32 *)(pv + 0x354) += 1;
            if (*(s32 *)(pv + 0x350) != 0) {
                if (*(s32 *)(pv + 0x354) >= 3 && PassGroupLeadToken(obj) != 0) {
                    SetMobyState(obj, 0xE, -1);
                    if (*(u8 *)(obj + 0x43) != 0x1A)
                        StartAnimationBlended(obj, 0x1A, 0, 0xF);
                }
            } else {
                SetMobyState(obj, 0xE, -1);
                if (*(u8 *)(obj + 0x43) != 0x1A)
                    StartAnimationBlended(obj, 0x1A, 0, 0xF);
            }
        }
        dist16 = GetMobyAnimationValue(obj);
        if (IsValueWithinStepOfThreshold(obj, 16.0f) != 0) {
            TransformMobyJointToWorld(obj, 4, muzzlePos);
            tgt16 = *(char **)(pv + 0x30);
            if (tgt16 == (char *)((Hero_00318340 *)gHeroState)->ptr[0x2290 / 4]) {
                qcopy(targetPos, &((Hero_00318340 *)gHeroState)->q[0xD0 / 16]);
                pos = targetPos;
            } else {
                if (tgt16 == 0)
                    break;
                qcopy(targetPos, tgt16 + 0x10);
                pos = targetPos;
                targetPos[2] += *(f32 *)(tgt16 + 0xC) * 0.0009765625f;
            }
            FastVecSub(aimDir, pos, muzzlePos);
            vec_scale_to_length(aimDir, aimDir, 0.33333334f);
            PlayMobySound(0xB, 0, obj);
            SpawnSpinningEffectMoby(obj, aimDir, muzzlePos, 0, 0, *(u8 *)(pv + 0x54));
        } else if (dist16 < 17.0f && *(u8 *)(obj + 0x43) == 0x1E) {
            TransformMobyJointToWorld(obj, 4, muzzlePos);
            sx = RandomFloatRange(1.0f, 1.5f) * 210000.0f;
            sy = RandomFloatRange(0.2f, 0.4f) * 210000.0f;
            sz = RandomSignedFloatRange(0.0f, 0.1f);
            SpawnGravityFadeParticle(muzzlePos, D_001A8BD0, 4, 0x808080, 9, 0x4F, 0, 0, sx, sy, sz);
        }
        break;
    }

    stateNow = *(u8 *)(obj + 0x20);
    if (stateNow == 12 || stateNow == 13 || stateNow == 14 || stateNow == 16) {
        u8 *recA;
        recA = *(s32 *)(pv + 0x2C4) * 0x70 + gSoundState;
        if (*(char **)(recA + 0x88) != obj || recA[0x74] == 0)
            *(s32 *)(pv + 0x2C4) = PlayMobySound(10, 4, obj);
    } else {
        u8 *recB;
        id = *(s32 *)(pv + 0x2C4);
        if (id != -1) {
            recB = id * 0x70 + gSoundState;
            if (*(char **)(recB + 0x88) == obj && recB[0x74] != 0)
                StopSoundVoice(id);
        }
        *(s32 *)(pv + 0x2C4) = -1;
    }
    UpdateClass2484BodyAndGroup(obj);
    TickClass2484Timers(obj);
    RegisterOverlayDrawCallback(DrawClass2484Effects, obj);
}
