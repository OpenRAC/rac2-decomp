#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } BarlowVector;
extern u8 D_L04_001BF880[];
extern int D_L04_001A8F00;
/* Shared conversation flags, as in func_L04_00439950. */
extern int D_L04_001B2224[] __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; TI128 q[0x260]; } Hero;
extern u8 D_00189E20[];
extern u8 D_001A7A40;
extern void func_L01_003128C0(void *);
extern int func_L01_003245E0(void *, int, f32);
/* Interface assumption: retain the incoming owner/key in a0. The current
 * linked wrapper is declared void(void), but its query forwards a live a0
 * key; removing this input is not independently justified. */
extern void func_L01_003246D0(int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_002A7750(void *, int, int);
extern int func_00282948(int *);
extern f32 func_002A7878(f32, f32);
extern int func_00283CF0(f32);
extern void func_002A7470(void *, int, int, int);
extern f32 func_00282E80(void *, void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00282DF0(void *);
extern f32 func_00283B98(f32, f32);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00282E20(void *);
extern void func_002AEC48(void *, void *, int, f32, f32);
extern u32 D_0013979C __attribute__((nosda));
extern u8 D_001A7BCD;
extern u8 D_00139605 __attribute__((nosda));
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern void func_L04_00423178(void *);
extern void func_L00_00427290(void);
extern void func_002F5CC8(void);
extern void func_002AD7B8(int);
extern void func_00288308(int);
extern void func_002AF0A8(int);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_0029B3E0(int, int);
extern void func_0029F338(void *);

/* Advances the conversation states and turns the two manipulators toward the
 * hero or a periodically chosen idle target. */
void func_L04_00423258(u8 *object) {
    BarlowVector target, origin, delta;
    u8 *data = *(u8 **)(object + 0x68);
    unsigned int state;
    f32 rate, heading, yaw, pitch;
    f32 blend = 0.3f;
    int look;
    ResetMatchingMobyEffects(object);
    state = object[0x20];
    switch (state) {
    case 0:
    if (D_001A7BCD) {
        MarkMobySpawned(object);
        return;
    }
    ResetMobyVarsDefaults(object);
    if (D_0013979C & 0x800000) SetMobyState(object, 3, -1);
    else SetMobyState(object, 1, -1);
    goto stateDone;
    case 1:
    if (IsHeroReachableForCount(object, 10, 4.0f)) {
        ApplyIndexForKey((int)object);
        if (PushRequestQueue(D_L04_001BF880, 0x37)) {
            LaunchQueuedRequest(D_L04_001BF880);
            SetMobyState(object, 2, -1);
        }
    }
    goto stateDone;
    case 2:
    D_L04_001B2224[1] = 1;
    if (D_L04_001A8F00 == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!IsEitherModeTwo()) {
        D_L04_001B2224[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        SetLevelFlag();
        SetMobyState(object, 3, -1);
    }
    goto stateDone;
    case 3:
    if (D_00139605 && IsHeroReachableForCount(object, 10, 2.5f)) {
        ApplyIndexForKey((int)object);
        if (PushRequestQueue(D_L04_001BF880, 0x39)) {
            PushRequestQueue(D_L04_001BF880, 5);
            PushRequestQueue(D_L04_001BF880, 0x3A);
            LaunchQueuedRequest(D_L04_001BF880);
            SetSlowdownFactorAndLowFpsFade();
            SetMobyState(object, 4, -1);
        }
    }
    goto stateDone;
    case 4:
    D_L04_001B2224[1] = 1;
    if (D_L04_001A8F00 == 2) {
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
    }
    if (!IsEitherModeTwo()) {
        D_L04_001B2224[1] = 0;
        object[0x31] = 1;
        *(u16 *)(object + 0x34) &= ~1;
        MarkFlagAndAppendToList(5);
        UnlockHelpEntry(0x30);
        PlayIndexedSound(5);
        if (object[0xB0] != 0xFF) {
            int channel = object[0xB0];
            if (!(D_0019B2E8[channel + gCurrentMapIndex * 16] & 0x80))
                MarkTableEntryFlagged(channel);
            CaptureCheckpointState(&((Hero *)gHeroState)->q[0x80 / 16], &((Hero *)gHeroState)->q[0x90 / 16]);
        } else {
            MemcardSave(0, -1);
        }
        MarkMobySpawned(object);
        return;
    }
    }
stateDone:
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && FastFloatHelperD((int *)(data + 0x11C))) {
            *(int *)(data + 0x11C) = FloatToInt(RandomFloatRange(1200.0f, 2400.0f));
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            StartAnimationBlended(object, 0, 0, 10);
        }
    }
    rate = 0.02f;
    look = 0;
    if (object[0x43] == 0) {
        look = 1;
        if (vec_distance_xy(object + 0x10, &((Hero *)gHeroState)->q[0x80 / 16]) < 8.0f &&
            FastDiffRots(*(f32 *)(object + 0xF8), FastMatrixHelperA(((Hero *)gHeroState)->f[0xE0 / 4] - *(f32 *)(object + 0x10), ((Hero *)gHeroState)->f[0xE4 / 4] - *(f32 *)(object + 0x14))) < 1.5707964897155762f) {
            if (FastVecLength(&((Hero *)gHeroState)->f[0x110 / 4]) > 0.01f)
                *(int *)(data + 0x114) = 120;
            else
                FastFloatHelperD((int *)(data + 0x114));
        } else if (*(int *)(data + 0x114)) {
            *(int *)(data + 0x114) = 0;
            qcopy((data + 0x100), &((Hero *)gHeroState)->q[0xE0 / 16]);
        }
        if (FastFloatHelperD((int *)(data + 0x118))) {
            *(int *)(data + 0x118) = FloatToInt(RandomFloatRange(180.0f, 300.0f));
            heading = FastAddRotations(*(f32 *)(object + 0xF8), RandomFloatRange(-90.0f, 90.0f) * 0.01745329424738884f);
            pitch = RandomFloatRange(0.0f, 30.0f) * 0.01745329424738884f;
            BuildSphericalOffset(data + 0x100, 6.0f, heading, pitch);
            FastVecAdd(data + 0x100, data + 0x100, object + 0x10);
        }
        if (*(int *)(data + 0x114)) {
            qcopy(&target, &((Hero *)gHeroState)->q[0xE0 / 16]);
            rate = 0.04f;
        } else {
            qcopy(&target, (data + 0x100));
        }
    }
    if (look) {
        qcopy(&origin, (object + 0x10));
        origin.f[2] += 2.0f;
        FastVecSub(&delta, &target, &origin);
        yaw = fast_subtract_rotations(FastMatrixHelperA(delta.f[0], delta.f[1]), *(f32 *)(object + 0xF8));
        pitch = -FastMatrixHelperA(vec_length_xy(&delta), delta.f[2]);
        if (yaw > 1.5707964897155762f)
            yaw = 1.5707964897155762f;
        else if (yaw < -1.5707964897155762f)
            yaw = -1.5707964897155762f;
        /* This object's update computes pitch but only applies yaw. */
        if (pitch > 0.523598849773407f)
            pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f)
            pitch = -0.523598849773407f;
        *(f32 *)(data + 0x68) = yaw * 0.6f;
        *(f32 *)(data + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40)
        *(f32 *)(data + 0x70) = 2.75f;
    UpdateEasedNode(object, data, 0, rate, blend);
    UpdateEasedNode(object, data + 0x80, 1, rate, blend);
}
