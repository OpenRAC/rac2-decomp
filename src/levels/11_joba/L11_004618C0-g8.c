#include "common.h"
typedef struct BarlowUtilityQueueView BarlowUtilityQueueView;
extern u8 D_001A7B00, D_001A7A40;
extern u32 D_001397D0 NOT_SDA;
extern u32 D_00138324 NOT_SDA;
extern u8 D_00139568[];
extern int D_001A79F8 MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; float position[4]; float rotation[4];
    u8 padA0[0x40]; float aim[4]; u8 padF0[0x20]; float velocity[4];
} JobaPlayerView;
extern JobaPlayerView D_00189E20;
extern u8 D_00189F00[];
extern u8 D_L11_001C0AC0[];
typedef struct {
    u8 pad[0x30];
    float position[4];
    u8 pad40[0x30];
    float rotation[4];
} VendorRecord;
extern VendorRecord *D_L11_001B368C[] MACRO_ADDR;
typedef struct {
    u8 pad[0x80];
    int price;
    u8 tail[0x5C];
} VendorOffer;
extern VendorOffer D_L11_00279BA0[];
/* The dialogue gate is written before each poll and cleared on completion. */
extern volatile int D_L11_001B32E8[] MACRO_ADDR;
extern int D_L11_001A8F00[] MACRO_ADDR;
extern void func_L04_00434AD0(u8 *);
extern void func_002A7750(u8 *, int, int);
extern void func_L01_003128C0(char *);
extern int func_002ACBC8(char *, int);
extern int func_00288AA0(u8 *, int);
extern int func_00288BE8(BarlowUtilityQueueView *);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(float *, float *, int, int);
extern int func_L01_003245E0(u8 *, int, float);
extern void func_L00_0030C710(int);
extern void func_L01_00324550(int, int, int);
extern void func_L01_003246D0(int);
extern void func_002A8598(int, int);
extern void func_00288308(int);
extern void func_002B0A18(int, int);
extern int func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern int func_00282978(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A7470(u8 *, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00283BE0(float, float);
extern float func_00282E20(void *);
extern void func_002AEC48(char *, u8 *, char *, float, float);

/* Updates the Shady Salesman (moby class 3733): he waits for the hero, offers an item for bolts, takes payment, and turns his head to watch the hero. */
void func_L11_004618C0(u8 *object) {
    float destination[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    int index, tracking;
    float rate;
    float yaw, pitch, distance, yawOffset, pitchOffset, heading;
    ResetMatchingMobyEffectsAlt(object);
    switch (object[0x20]) {
    case 0:
        if (D_001A7B00) { MarkMobySpawned(object); return; }
        if (D_001397D0 & 0x800) SetMobyState(object, 2, -1);
        else SetMobyState(object, 1, -1);
        ResetMobyVarsDefaults((char *)object);
        break;
    case 1:
        if (IsPointInCuboid((char *)gHeroState.position, *(int *)(vars + 0x120)) && PushRequestQueue(D_L11_001C0AC0, 0x6B)) {
            ApplyIndexForKey((int)object);
            LaunchQueuedRequest((BarlowUtilityQueueView *)D_L11_001C0AC0);
            SetMobyState(object, 2, -1);
        }
        break;
    case 2:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            VendorRecord *record;
            D_L11_001B32E8[0] = 0;
            record = (VendorRecord *)((u32)D_L11_001B368C[0] + *(int *)(vars + 0x120) * sizeof(VendorRecord));
            ResetHeroPositionAndDirection(record->position, record->rotation, 0, 1);
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (gPlayerBolts < ((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price) SetMobyState(object, 3, -1);
            else SetMobyState(object, 4, -1);
        }
        break;
    case 3:
        if (((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price < gPlayerBolts) {
            SetMobyState(object, 4, -1);
        } else if (IsHeroReachableForCount(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            PrintLocalizedFormatted(0x27BC, ((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price, -1);
            ApplyIndexForKey((int)object);
        }
        break;
    case 4:
        if (gPlayerBolts < ((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price) {
            func_L00_0030C710(180);
            SetMobyState(object, 3, -1);
        } else if (IsHeroReachableForCount(object, 10, 2.5f)) {
            func_L00_0030C710(180);
            PrintLocalizedFormatted(0x27BB, ((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price, -1);
            ApplyIndexForKey((int)object);
            if ((D_00138324 & 0x10) && PushRequestQueue(D_L11_001C0AC0, 0x6C)) {
                LaunchQueuedRequest((BarlowUtilityQueueView *)D_L11_001C0AC0);
                SetMobyState(object, 5, -1);
            }
        }
        break;
    case 5:
        D_L11_001B32E8[0] = 1;
        if (D_L11_001A8F00[0] == 2) {
            object[0x31] = 0;
            *(u16 *)(object + 0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            D_L11_001B32E8[0] = 0;
            object[0x31] = 1;
            *(u16 *)(object + 0x34) &= 0xFFFE;
            if (object[0x21] != 0xFF) SetByteOnGroupMobys(object[0x21], 1);
            if (!D_001A7B00) {
                gPlayerBolts = gPlayerBolts - ((VendorOffer *)((u32)D_L11_00279BA0 + gItemSlotToRecord[8] * sizeof(VendorOffer)))->price;
                func_L00_0030C710(180);
                UnlockHelpEntry(8);
            }
            index = *(int *)(vars + 0x124);
            if (index != -1) {
                VendorRecord *record = (VendorRecord *)((u32)D_L11_001B368C[0] + index * sizeof(VendorRecord));
                ResetHeroPositionAndDirection(record->position, record->rotation, 0, 1);
            }
            SetEntryValueByIndex(0x1230, -1);
            MemcardSave(0, -1);
            MarkMobySpawned(object);
            return;
        }
        break;
    }
    if (object[0x20] != 0) {
        if (object[0x43] == 0 && FastDecTimer(vars + 0x11E)) {
            *(short *)(vars + 0x11E) = FloatToInt(RandomFloatRange(1200.0f, 2400.0f));
            if (object[0x43] != 1) StartAnimationBlended(object, 1, 0, 10);
        } else if ((object[0x60] & 2) && object[0x43] != 0) {
            StartAnimationBlended(object, 0, 0, 10);
        }
    }
    tracking = 0;
    rate = 0.02f;
    if (object[0x43] == 0) {
        tracking = 1;
        distance = vec_distance_xy(object + 0x10, gHeroState.position);
        if (distance < 8.0f && FastDiffRots(*(float *)(object + 0xF8), FastMatrixHelperA(gHeroState.aim[0] - *(float *)(object + 0x10), gHeroState.aim[1] - *(float *)(object + 0x14))) < 1.5707965f) {
            if (FastVecLength(gHeroState.velocity) > 0.01f) *(int *)(vars + 0x114) = 120;
            else FastFloatHelperD(vars + 0x114);
        } else if (*(int *)(vars + 0x114)) {
            *(int *)(vars + 0x114) = 0;
            qcopy(vars + 0x100, D_00189F00);
        }
        if (FastFloatHelperD(vars + 0x118)) {
            *(int *)(vars + 0x118) = FloatToInt(RandomFloatRange(180.0f, 300.0f));
            yawOffset = RandomFloatRange(-90.0f, 90.0f);
            heading = FastAddRotations(*(float *)(object + 0xF8), yawOffset * 0.017453294f);
            pitchOffset = RandomFloatRange(0, 30.0f);
            BuildSphericalOffset((float *)(vars + 0x100), 6.0f, heading, pitchOffset * 0.017453294f);
            FastVecAdd((float *)(vars + 0x100), (float *)(vars + 0x100), (float *)(object + 0x10));
        }
        if (*(int *)(vars + 0x114)) {
            qcopy(destination, D_00189F00);
            rate = 0.04f;
        } else qcopy(destination, vars + 0x100);
    }
    if (tracking) {
        qcopy(origin, object + 0x10);
        origin[2] += 2.0f;
        FastVecSub(difference, destination, origin);
        yaw = fast_subtract_rotations(FastMatrixHelperA(difference[0], difference[1]), *(float *)(object + 0xF8));
        pitch = -FastMatrixHelperA(vec_length_xy(difference), difference[2]);
        if (yaw > 1.5707965f) yaw = 1.5707965f;
        else if (yaw < -1.5707965f) yaw = -1.5707965f;
        if (pitch > 0.52359885f) pitch = 0.52359885f;
        else if (pitch < -0.52359885f) pitch = -0.52359885f;
        *(float *)(vars + 0x64) = pitch;
        *(float *)(vars + 0x68) = yaw * 0.6f;
        *(float *)(vars + 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40) *(float *)(vars + 0x70) = 2.75f;
    for (index = 0; index < 2; index++)
        UpdateEasedNode((char *)object, vars + index * 0x80, (char *)index, rate, 0.3f);
    return;
}
