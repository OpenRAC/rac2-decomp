/* An eight-state object update (Dobbo). A -G8 unit of its own: it reads $gp data and has a jump table.
 *
 * What the bytes show about the source:
 * - D_L09_001B25A0[2] is an element of a small-data array, not a scalar: (mem (const (plus sym 8)))
 *   is not a simple memory operand, so its stores are two-word macros that never enter a delay slot.
 *   Retail fixes only the element's address, 0x1B25A8; the array's base is a choice, not a measurement.
 * - updateJoint() takes the 0.3f as a parameter: inlined, the constant goes straight into $f13 at each
 *   call, where a literal argument would be one pseudo kept in $f20 across the first call.
 * - yawToHero() forms the hero's base only after the distance test, as a related value of its +0x80.
 * - status is a u64 local: a cast in the shift itself is narrowed back to a 32-bit srl.
 */
#include "common.h"

typedef struct {
    char pad[0x60];
    int flags;
    u8 status;
} DobboInput;

typedef struct {
    char pad[0x1D];
    u8 unlocked;
    char pad1[0xF];
    u8 started;
    u8 completed;
} DobboProgress;

extern u8 D_001A7BD3 MACRO_ADDR, D_001A7A40 MACRO_ADDR;
extern DobboInput D_00139768 NOT_SDA;
extern DobboProgress D_001395B8 NOT_SDA;
extern char D_0019B2E8[] NOT_SDA;
extern char D_00189E20[] NOT_SDA;
extern char D_L09_001BFC00[] NOT_SDA;
extern int D_L09_001A8F00 MACRO_ADDR, D_L09_001B2388 MACRO_ADDR;
extern int D_L09_001B25A0[] MACRO_ADDR;
extern int D_L09_001B15A0 __attribute__((sda)), D_001A79F0 __attribute__((sda));

extern void func_L04_00423178(char *);
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_L01_003128C0(char *);
extern int func_00288AA0(void *, int);
extern void func_L01_003246D0(char *), func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_00288CB0(int, int), func_002F5CC8(void), func_002DF3F8(void *, void *);
extern void func_0029B3E0(int, int), func_002AD7B8(int), func_002AF0A8(int), func_002A0430(int);
extern void func_0029F338(char *);
extern int func_00282978(void *), func_00283CF0(float);
extern float func_002A7878(float, float), func_00282E80(void *, void *), func_00283248(float, float);
extern float func_00283C80(float, float), func_00282DF0(void *), func_00283B98(float, float);
extern float func_00283BE0(float, float), func_00282E20(void *);
extern void func_002A7470(char *, int, int, int), func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_002AEC48(char *, void *, int, float, float);

#define HERO_POS (D_00189E20 + 0x80)
#define HERO_ROT (D_00189E20 + 0x90)
#define HERO_AIM (D_00189E20 + 0xE0)
#define U8(p, o) (*(u8 *)((p) + (o)))
#define U16(p, o) (*(u16 *)((p) + (o)))
#define S16(p, o) (*(s16 *)((p) + (o)))
#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))

static inline float yawToHero(char *obj) {
    char *hero = gHeroState;
    return FastMatrixHelperA(F32(hero, 0xE0) - F32(obj, 0x10), F32(hero, 0xE4) - F32(obj, 0x14));
}

static inline void updateJoint(char *obj, char *joint, int index, float speed, float rate) {
    UpdateEasedNode(obj, joint, index, speed, rate);
}

/* Per-frame update of the talking character (moby class 3678): it offers dialogue and rewards, then watches the hero with its head and eyes. */
void func_L09_0040A2E8(char *obj) {
    float target[4], pos[4], delta[4];
    char *data = *(char **)(obj + 0x68);
    char *player;
    float speed, yaw, pitch, randomYaw;
    int active;
    u64 status;

    ResetMatchingMobyEffects(obj);
    switch (U8(obj, 0x20)) {
    case 0:
        if (D_001A7BD3) {
            U16(obj, 0x34) = (U16(obj, 0x34) | 0x41) & 0xEFFF;
            I32(obj, 0x98) = 0;
        }
        status = D_00139768.status;
        if (status >> 7) {
            SetMobyState(obj, 6, -1);
        } else if (D_001395B8.unlocked || (D_00139768.flags & 8)) {
            SetMobyState(obj, 3, -1);
        } else {
            SetMobyState(obj, 1, -1);
        }
        if (U8(obj, 0x20) == 3) {
            if (!IsPointInCuboid(HERO_POS, I32(data, 0x118)) || !D_001395B8.unlocked) {
                D_L09_001B15A0 = 1;
            }
        }
        ResetMobyVarsDefaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (PushRequestQueue(D_L09_001BFC00, 99)) {
                ApplyIndexForKey(obj);
                LaunchQueuedRequest(D_L09_001BFC00);
                SetMobyState(obj, 2, -1);
            }
        }
        break;
    case 2:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            D_L09_001B25A0[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            SetMobyState(obj, 3, -1);
            D_001395B8.unlocked = 1;
            D_001395B8.started = 1;
            SetSmallDataValueAndRefresh(22, 1);
        }
        break;
    case 3:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118))) {
            if (D_001395B8.completed) {
                if (PushRequestQueue(D_L09_001BFC00, 103)) {
                    PushRequestQueue(D_L09_001BFC00, 11);
                    ApplyIndexForKey(obj);
                    LaunchQueuedRequest(D_L09_001BFC00);
                    SetSlowdownFactorAndLowFpsFade();
                    D_L09_001B15A0 = 1;
                    SetMobyState(obj, 5, -1);
                }
            } else if (D_L09_001B2388 < 10 && D_001395B8.unlocked && !D_L09_001B15A0) {
                if (PushRequestQueue(D_L09_001BFC00, 102)) {
                    LaunchQueuedRequest(D_L09_001BFC00);
                    SetSlowdownFactorAndLowFpsFade();
                    D_L09_001B15A0 = 1;
                    SetMobyState(obj, 4, -1);
                }
            }
        }
        break;
    case 4:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            CaptureCheckpointState(HERO_POS, HERO_ROT);
            D_L09_001B25A0[2] = 0;
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            MemcardSave(0, -1);
            SetMobyState(obj, 3, -1);
        }
        break;
    case 5:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            D_L09_001B25A0[2] = 0;
            MarkFlagAndAppendToList(11);
            PlayIndexedSound(11);
            if (U8(obj, 0xB0) != 255 && !(U8(D_0019B2E8, U8(obj, 0xB0) + (gCurrentMapIndex << 4)) & 0x80)) {
                MarkTableEntryFlagged(U8(obj, 0xB0));
            }
            CaptureCheckpointState(HERO_POS, HERO_ROT);
            MemcardSave(0, -1);
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            MarkMobySpawned(obj);
            return;
        }
        break;
    case 6:
        if (IsPointInCuboid(HERO_POS, I32(data, 0x118)) && D_L09_001B2388 < 10 && D_001395B8.unlocked
            && !D_L09_001B15A0) {
            if (PushRequestQueue(D_L09_001BFC00, 102)) {
                LaunchQueuedRequest(D_L09_001BFC00);
                SetSlowdownFactorAndLowFpsFade();
                D_L09_001B15A0 = 1;
                SetMobyState(obj, 7, -1);
            }
        }
        break;
    case 7:
        D_L09_001B25A0[2] = 1;
        if (D_L09_001A8F00 == 2) {
            U8(obj, 0x31) = 0;
            U16(obj, 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            U8(obj, 0x31) = 1;
            U16(obj, 0x34) &= 0xFFFE;
            D_L09_001B25A0[2] = 0;
            SetMobyState(obj, 8, -1);
            CaptureCheckpointState(HERO_POS, HERO_ROT);
            MemcardSave(0, -1);
            MarkMobySpawned(obj);
            return;
        }
        break;
    }

    if (U8(obj, 0x20)) {
        if (U8(obj, 0x43) == 1 && FastDecTimer(data + 0x114)) {
            S16(data, 0x114) = FloatToInt(RandomFloatRange(1200.0f, 2400.0f));
            if (U8(obj, 0x43) != 2) {
                StartAnimationBlended(obj, 2, 0, 10);
            }
        } else if ((U8(obj, 0x60) & 2) && U8(obj, 0x43) != 1) {
            StartAnimationBlended(obj, 1, 0, 10);
        }
    }

    speed = 0.02f;
    active = 0;
    if (U8(obj, 0x43) == 1) {
        player = HERO_POS;
        active = 1;
        if (vec_distance_xy(obj + 0x10, player) < 8.0f
            && FastDiffRots(F32(obj, 0xF8), yawToHero(obj)) < 1.57079649f) {
            if (FastVecLength(player + 0x90) > 0.01f) {
                S16(data, 0x110) = 120;
            } else {
                FastDecTimer(data + 0x110);
            }
        } else if (S16(data, 0x110)) {
            S16(data, 0x110) = 0;
            qcopy(data + 0x100, HERO_AIM);
        }
        if (FastDecTimer(data + 0x112)) {
            S16(data, 0x112) = FloatToInt(RandomFloatRange(180.0f, 300.0f));
            randomYaw = FastAddRotations(F32(obj, 0xF8), RandomFloatRange(-90.0f, 90.0f) * 0.017453294f);
            pitch = RandomFloatRange(0.0f, 30.0f) * 0.017453294f;
            BuildSphericalOffset(data + 0x100, 6.0f, randomYaw, pitch);
            FastVecAdd(data + 0x100, data + 0x100, obj + 0x10);
        }
        if (S16(data, 0x110)) {
            qcopy(target, HERO_AIM);
            speed = 0.04f;
        } else {
            qcopy(target, data + 0x100);
        }
    }
    if (active) {
        qcopy(pos, obj + 0x10);
        pos[2] += 2.0f;
        FastVecSub(delta, target, pos);
        yaw = fast_subtract_rotations(FastMatrixHelperA(delta[0], delta[1]), F32(obj, 0xF8));
        pitch = -FastMatrixHelperA(vec_length_xy(delta), delta[2]);
        if (yaw > 1.57079649f) {
            yaw = 1.57079649f;
        } else if (yaw < -1.57079649f) {
            yaw = -1.57079649f;
        }
        if (pitch > 0.52359885f) {
            pitch = 0.52359885f;
        } else if (pitch < -0.52359885f) {
            pitch = -0.52359885f;
        }
        F32(data, 0x64) = pitch;
        F32(data, 0x68) = yaw * 0.6f;
        F32(data, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40) {
        F32(data, 0x70) = 2.75f;
    }
    updateJoint(obj, data, 0, speed, 0.3f);
    updateJoint(obj, data + 0x80, 1, speed, 0.3f);
}
