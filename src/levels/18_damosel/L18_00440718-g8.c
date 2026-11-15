#include "common.h"

#define S32_AT(p, o) (*(int *)((u8 *)(p) + (o)))
#define F32_AT(p, o) (*(float *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x84]; u8 first; u8 pad85; u8 second; u8 pad87[2]; u8 third; } PurchaseParts;
typedef struct { u8 pad[0x37]; u8 planet; } PurchaseSave;
typedef struct { u8 pad[0x80]; int cost; u8 tail[0x5C]; } PurchaseLevelInfo;
typedef struct { u8 pad[0xE0]; float x; float y; } PurchaseHero;

extern u8 D_00189EA0[], D_L18_0026BCF0[], D_L18_001BF9C0[];
extern PurchaseParts D_001395B8;
extern PurchaseSave D_00139568;
extern int D_001397F8 NOT_SDA;
extern int D_001A79F8;
extern int D_00138324 NOT_SDA;
extern u8 D_001A7B2F;
extern u8 D_0013959F NOT_SDA;
extern u8 D_001A7A40;
extern int D_L18_001A8F00;
extern int D_L18_001B2564[] __attribute__((sda));
extern u8 *D_L18_001B290C, *D_L18_001B281C;

extern void func_L04_00423178(void *), func_L01_003128C0(void *), func_L01_003246D0(void *);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int), func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);
extern int func_L01_003245E0(void *, int, float);
extern void func_L01_00324550(int, int, int), func_L00_0030C710(int), func_002A0430(int);
extern void func_00288308(int), func_002AD860(int), func_002B0A18(int, int), func_00288E18(int, int);
extern void func_002DF3F8(void *, void *), func_0029B3E0(int, int), func_0029F338(void *);
extern int func_00282948(void *), func_00282978(void *), func_00283CF0(float);
extern float func_002A7878(float, float), func_00282E80(void *, void *), func_00283248(float, float);
extern float func_00283C80(float, float), func_00282DF0(void *), func_00283B98(float, float);
extern float func_00283BE0(float, float), func_00282E20(void *);
extern void func_002A7470(void *, int, int, int), func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
extern void func_002AEC48(void *, void *, int, float, float);

/* Updates the ship parts shop character (moby class 4754): it checks which parts the player has, talks about the price, takes the bolts when the player buys, and turns its head toward the player. */
void func_L18_00440718(u8 *obj)
{
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    float speed, yaw, pitch, randomYaw;
    float blend = 0.3f;
    int active;

    ResetMatchingMobyEffects(obj);
    switch (U8_AT(obj, 0x20)) {
    case 0:
        if (D_001A7B2F)
            goto remove_object;
        if (D_001397F8 & 0x10000)
            SetMobyState(obj, 3, -1);
        else
            SetMobyState(obj, 1, -1);
        ResetMobyVarsDefaults(obj);
        break;
    case 1:
        if (IsPointInCuboid(gHeroPosition, S32_AT(state, 0x120)) && PushRequestQueue(D_L18_001BF9C0, 0x90)) {
            ApplyIndexForKey(obj);
            LaunchQueuedRequest(D_L18_001BF9C0);
            SetMobyState(obj, 2, -1);
        }
        break;
    case 2:
        D_L18_001B2564[1] = 1;
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            ResetHeroPositionAndDirection(gWaypointTable + S32_AT(state, 0x120) * 128 + 0x30,
                              gWaypointTable + S32_AT(state, 0x120) * 128 + 0x70, 0, 1);
            U8_AT(obj, 0x31) = 1;
            U16_AT(obj, 0x34) &= 0xFFFE;
            D_L18_001B2564[1] = 0;
            SetMobyState(obj, 3, -1);
        }
        break;
    case 3:
        if (D_001395B8.first && D_001395B8.second && D_001395B8.third) {
            if (gPlayerBolts >= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost)
                SetMobyState(obj, 5, -1);
            else
                SetMobyState(obj, 4, -1);
        } else if (IsHeroReachableForCount(obj, 10, 1.0f)) {
            int count = 3;
            if (D_001395B8.first)
                count = 2;
            if (D_001395B8.second)
                count--;
            if (D_001395B8.third)
                count--;
            PrintLocalizedFormatted(0x27D9, count, -1);
            ApplyIndexForKey(obj);
        }
        break;
    case 4:
        if (((PurchaseLevelInfo *)D_L18_0026BCF0)[gItemSlotToRecord.planet].cost < gPlayerBolts) {
            SetMobyState(obj, 5, -1);
        } else if (IsHeroReachableForCount(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            PrintLocalizedFormatted(0x27DA, ((PurchaseLevelInfo *)D_L18_0026BCF0)[gItemSlotToRecord.planet].cost, -1);
            ApplyIndexForKey(obj);
        }
        break;
    case 5:
        if (gPlayerBolts < ((PurchaseLevelInfo *)D_L18_0026BCF0)[gItemSlotToRecord.planet].cost) {
            func_L00_0030C710(180);
            SetMobyState(obj, 4, -1);
        } else if (IsHeroReachableForCount(obj, 10, 1.0f)) {
            func_L00_0030C710(180);
            PrintLocalizedFormatted(0x27DB, ((PurchaseLevelInfo *)D_L18_0026BCF0)[gItemSlotToRecord.planet].cost, -1);
            ApplyIndexForKey(obj);
            if ((D_00138324 & 16) && PushRequestQueue(D_L18_001BF9C0, 0x91)) {
                LaunchQueuedRequest(D_L18_001BF9C0);
                SetMobyState(obj, 6, -1);
                MarkTableEntryFlagged(U8_AT(obj, 0xB0));
            }
        }
        break;
    case 6:
        if (D_L18_001A8F00 == 2) {
            U8_AT(obj, 0x31) = 0;
            U16_AT(obj, 0x34) |= 1;
        }
        {
            unsigned int timer = U16_AT(obj, 0x96);
            unsigned int elapsed = timer++;
            U16_AT(obj, 0x96) = timer;
            if (elapsed >= 20) {
                D_L18_001B2564[1] = 1;
                if (!IsEitherModeTwo()) {
                    D_L18_001B2564[1] = 0;
                    U8_AT(obj, 0x31) = 1;
                    U16_AT(obj, 0x34) &= 0xFFFE;
                    if (!D_001A7B2F) {
                        gPlayerBolts -= ((PurchaseLevelInfo *)D_L18_0026BCF0)[D_0013959F].cost;
                        func_L00_0030C710(180);
                        if (S32_AT(state, 0x124) != -1)
                            U8_AT(gMobyTable_L18 + S32_AT(state, 0x124) * 256, 0xBC) = 1;
                        UnlockHelpEntry(55);
                        HandleRequestSlotState(55);
                    }
                    SetMobyState(obj, 7, -1);
                    U8_AT(obj, 0x31) = 0;
                    U16_AT(obj, 0x34) |= 1;
                }
            }
        }
        break;
    case 7: {
        unsigned int timer = U16_AT(obj, 0x96);
        unsigned int elapsed = timer++;
        U16_AT(obj, 0x96) = timer;
        if (elapsed >= 41) {
            SetEntryValueByIndex(0x1231, -1);
            RequestSubtitleVoiceLine(0xA11, 0x68);
            CaptureCheckpointState(gHeroPosition, gHeroPosition + 16);
            MemcardSave(0, -1);
        remove_object:
            MarkMobySpawned(obj);
            return;
        }
        break;
    }
    }
    if (U8_AT(obj, 0x20)) {
        if (!U8_AT(obj, 0x43) && FastDecTimer(state + 0x11E)) {
            U16_AT(state, 0x11E) = FloatToInt(RandomFloatRange(1200, 2400));
            if (U8_AT(obj, 0x43) != 1)
                StartAnimationBlended(obj, 1, 0, 10);
        } else if ((U8_AT(obj, 0x60) & 2) && U8_AT(obj, 0x43)) {
            StartAnimationBlended(obj, 0, 0, 10);
        }
    }
    speed = 0.02f;
    active = 0;
    if (!U8_AT(obj, 0x43)) {
        active = 1;
        if (vec_distance_xy(obj + 0x10, gHeroPosition) < 8 &&
            FastDiffRots(F32_AT(obj, 0xF8),
                          FastMatrixHelperA(((PurchaseHero *)(gHeroPosition - 128))->x - F32_AT(obj, 0x10),
                                        ((PurchaseHero *)(gHeroPosition - 128))->y - F32_AT(obj, 0x14))) < 1.5707965f) {
            if (FastVecLength(gHeroPosition + 0x90) > 0.01f)
                S32_AT(state, 0x114) = 120;
            else
                FastFloatHelperD(state + 0x114);
        } else if (S32_AT(state, 0x114)) {
            S32_AT(state, 0x114) = 0;
            qcopy_nc(state + 0x100, gHeroPosition + 0x60);
        }
        if (FastFloatHelperD(state + 0x118)) {
            S32_AT(state, 0x118) = FloatToInt(RandomFloatRange(180, 300));
            randomYaw = FastAddRotations(F32_AT(obj, 0xF8), RandomFloatRange(-90, 90) * 0.017453294f);
            pitch = RandomFloatRange(0, 30);
            BuildSphericalOffset(state + 0x100, 6, randomYaw, pitch * 0.017453294f);
            FastVecAdd(state + 0x100, state + 0x100, obj + 0x10);
        }
        if (S32_AT(state, 0x114)) {
            qcopy_nc(target, gHeroPosition + 0x60);
            speed = 0.04f;
        } else {
            qcopy_nc(target, state + 0x100);
        }
    }
    if (active) {
        qcopy_nc(position, obj + 0x10);
        position[2] += 2;
        FastVecSub(delta, target, position);
        yaw = fast_subtract_rotations(FastMatrixHelperA(delta[0], delta[1]), F32_AT(obj, 0xF8));
        pitch = -FastMatrixHelperA(vec_length_xy(delta), delta[2]);
        if (yaw > 1.5707965f)
            yaw = 1.5707965f;
        else if (yaw < -1.5707965f)
            yaw = -1.5707965f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F32_AT(state, 0x64) = pitch;
        F32_AT(state, 0x68) = yaw * 0.6f;
        F32_AT(state, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40)
        F32_AT(state, 0x70) = 2.75f;
    UpdateEasedNode(obj, state, 0, speed, blend);
    UpdateEasedNode(obj, state + 0x80, 1, speed, blend);
}
