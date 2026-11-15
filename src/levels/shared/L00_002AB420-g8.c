/* Updates the hero idle rotation targets and the two rotation blends. */
#include "include_asm.h"
#include "names.h"
typedef struct {
    unsigned char pad0[0x1E8];
    int f1e8;
    unsigned char pad1ec[0x1C];
    short f208;
    unsigned char pad20a[0x6E];
    float f278;
    unsigned char pad27c[0xC];
    float f288;
    float f28c;
    int f290;
    unsigned char pad294[0x964];
    int fbf8;
    unsigned char padbfc[0x598];
    float f1194;
    float f1198;
    unsigned char pad119c[0x4];
    int f11a0;
    float f11a4;
    float f11a8;
    unsigned char pad11ac[0x168];
    int f1314;
    unsigned char pad1318[0xF78];
    unsigned char *f2290;
    int f2294;
    unsigned char pad2298[0x20];
    unsigned char f22b8;
    unsigned char pad22b9[0x1D7];
    int f2490;
} HeroPitchYawState;
extern HeroPitchYawState D_00189E20_2;

typedef struct {
    unsigned char pad0[0x114];
    float f114;
    float f118;
    unsigned char pad11c[0x158];
    float f274;
    float f278;
    unsigned char pad27c[0x9E0];
    float fc5c;
    unsigned char padc60[0xAC];
    float fd0c;
} HeroRotationBlends;
extern HeroRotationBlends D_L00_0025BE10;

extern unsigned char D_001A7A43,  D_001A7A41;
extern float D_L00_001A7CF4 __attribute__((sda));
extern float D_L00_001A7CF8 __attribute__((sda));
extern void func_002AA2E8(float *, float, float);
extern int func_002A7820(int, int);
extern int func_00282948(int *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002AA140(float, float, float);
extern int func_00283CF0(float);
extern void func_L00_002AB3E0(void);
extern void func_L00_002AB0F0(float, float);
extern void func_L00_002AB0C0(float, float);
extern int func_L00_002ADEA0(int);
/* Picks new random head and body turn targets while the hero stands idle, and eases toward them. */
void func_L00_002AB420(void)
{
    float lookAngle;
    int applyBlend, status;
    int kind;

    if (D_001A7A43 && D_00189E20_2.f1314)
        D_L00_0025BE10.fd0c = D_L00_001A7CF8;
    D_L00_0025BE10.fc5c = D_L00_001A7CF4;
    if (D_001A7A41)
        ApproachValue(&D_L00_001A7CF4, 1.57f, 0.05f);
    else
        ApproachValue(&D_L00_001A7CF4, 0.875f, 0.05f);

    if (D_00189E20_2.f1e8 < 20)
        return;
    if (D_00189E20_2.f22b8 || D_00189E20_2.fbf8) {
        ClearHeroSlotRecords();
        SetCameraLimitsSlot3(0.03f, 0.2f);
        SetCameraLimitsSlot1(0.03f, 0.2f);
        D_00189E20_2.f11a0 = RandomIntRange(90, 120);
        D_00189E20_2.f208 = RandomIntRange(90, 120);
        return;
    }
    if (D_00189E20_2.f290 && D_00189E20_2.f288 > 1.4f &&
        D_00189E20_2.f278 > 1.0f) {
        SetCameraLimitsSlot3(0.015f, 0.3f);
        lookAngle = D_00189E20_2.f288 * (1.5f * 0.017453294f) + 0.19198623f;
        if (lookAngle > 0.47123894f)
            lookAngle = 0.47123894f;
        {
            float ratio = (1.0f - D_00189E20_2.f28c) * (35.0f * 0.017453294f);
            if (ratio < lookAngle)
                lookAngle = ratio;
        }
        D_L00_0025BE10.f274 = lookAngle;
        SetCameraLimitsSlot1(0.008f, 0.3f);
        D_L00_0025BE10.f114 = D_L00_0025BE10.f274 * 0.7f;
        return;
    }

    status = hero_slot_item_id(0);
    applyBlend = 1;
    if (status == 30 || status == 24)
        applyBlend = 0;
    if (D_00189E20_2.f2294)
        return;
    kind = D_00189E20_2.f2290[0x43];
    if ((unsigned char)kind >= 3 && (unsigned char)kind != 58)
        return;
    if (D_00189E20_2.f2490)
        return;
    if ((unsigned)(kind - 1) < 2)
        D_00189E20_2.f11a0 = RandomIntRange(40, 70);
    if (FastFloatHelperD(&D_00189E20_2.f11a0)) {
        D_00189E20_2.f1194 = -RandomFloatRange((-9.0f * 0.017453294f),
                                         (25.0f * 0.017453294f));
        if (D_00189E20_2.f278 < 1.5f)
            D_00189E20_2.f1198 = RandomSignedFloatRange((50.0f * 0.017453294f),
                                             (70.0f * 0.017453294f));
        else
            D_00189E20_2.f1198 = RandomSignedFloatRange((20.0f * 0.017453294f),
                                             (57.0f * 0.017453294f));
        {
            float ratio = RandomFloatRange(0.0f, 1.0f);
            D_00189E20_2.f11a4 = LerpFloat_002AA140(0.015f, 0.007f, ratio);
            D_00189E20_2.f11a8 = LerpFloat_002AA140(0.29f, 0.3f, ratio);
            D_00189E20_2.f11a0 = RandomIntRange(90, 200);
            D_00189E20_2.f11a0 += FloatToInt(ratio * 80.0f);
        }
    }
    if ((unsigned)(D_00189E20_2.f2290[0x43] - 1) < 2) {
        if (D_00189E20_2.f1198 > (20.0f * 0.017453294f))
            D_00189E20_2.f1198 = (20.0f * 0.017453294f);
        else if (D_00189E20_2.f1198 < -(20.0f * 0.017453294f))
            D_00189E20_2.f1198 = -(20.0f * 0.017453294f);
        if (D_00189E20_2.f1194 > (15.0f * 0.017453294f))
            D_00189E20_2.f1194 = (15.0f * 0.017453294f);
        if (D_00189E20_2.f1194 < 0.0f)
            D_00189E20_2.f1194 = 0.0f;
    }
    SetCameraLimitsSlot3(D_00189E20_2.f11a4, D_00189E20_2.f11a8);
    D_L00_0025BE10.f278 = D_00189E20_2.f1198;
    D_L00_0025BE10.f274 = D_00189E20_2.f1194;
    if (applyBlend) {
        SetCameraLimitsSlot1(0.008f, 0.3f);
        D_L00_0025BE10.f118 = D_L00_0025BE10.f278 * 0.52f;
        D_L00_0025BE10.f114 = D_L00_0025BE10.f274 * 0.55f;
    }
}
