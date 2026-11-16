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
extern HeroRotationBlends g_hero_item_attach_records;

extern unsigned char g_state_flag_b,  g_state_flag_a;
extern float g_glow_angle_a __attribute__((sda));
extern float g_glow_scale __attribute__((sda));
extern float ApproachValue(float *, float, float);
extern int math_random_int_range(int, int);
extern int math_fast_float_d(int *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_lerp_float(float, float, float);
extern int FloatToInt(float);
extern void hero_clear_slot_records(void);
extern void cam_set_limits_fourth(float, float);
extern void cam_set_limits_second(float, float);
extern int hero_slot_item_id(int);
/* Picks new random head and body turn targets while the hero stands idle, and eases toward them. */
void UpdateHeroPitchAndYawEasingTargets(void)
{
    float lookAngle;
    int applyBlend, status;
    int kind;

    if (g_state_flag_b && D_00189E20_2.f1314)
        g_hero_item_attach_records.fd0c = g_glow_scale;
    g_hero_item_attach_records.fc5c = g_glow_angle_a;
    if (g_state_flag_a)
        ApproachValue(&g_glow_angle_a, 1.57f, 0.05f);
    else
        ApproachValue(&g_glow_angle_a, 0.875f, 0.05f);

    if (D_00189E20_2.f1e8 < 20)
        return;
    if (D_00189E20_2.f22b8 || D_00189E20_2.fbf8) {
        hero_clear_slot_records();
        cam_set_limits_fourth(0.03f, 0.2f);
        cam_set_limits_second(0.03f, 0.2f);
        D_00189E20_2.f11a0 = math_random_int_range(90, 120);
        D_00189E20_2.f208 = math_random_int_range(90, 120);
        return;
    }
    if (D_00189E20_2.f290 && D_00189E20_2.f288 > 1.4f &&
        D_00189E20_2.f278 > 1.0f) {
        cam_set_limits_fourth(0.015f, 0.3f);
        lookAngle = D_00189E20_2.f288 * (1.5f * 0.017453294f) + 0.19198623f;
        if (lookAngle > 0.47123894f)
            lookAngle = 0.47123894f;
        {
            float ratio = (1.0f - D_00189E20_2.f28c) * (35.0f * 0.017453294f);
            if (ratio < lookAngle)
                lookAngle = ratio;
        }
        g_hero_item_attach_records.f274 = lookAngle;
        cam_set_limits_second(0.008f, 0.3f);
        g_hero_item_attach_records.f114 = g_hero_item_attach_records.f274 * 0.7f;
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
        D_00189E20_2.f11a0 = math_random_int_range(40, 70);
    if (math_fast_float_d(&D_00189E20_2.f11a0)) {
        D_00189E20_2.f1194 = -math_random_float_range((-9.0f * 0.017453294f),
                                         (25.0f * 0.017453294f));
        if (D_00189E20_2.f278 < 1.5f)
            D_00189E20_2.f1198 = math_random_signed_float_range((50.0f * 0.017453294f),
                                             (70.0f * 0.017453294f));
        else
            D_00189E20_2.f1198 = math_random_signed_float_range((20.0f * 0.017453294f),
                                             (57.0f * 0.017453294f));
        {
            float ratio = math_random_float_range(0.0f, 1.0f);
            D_00189E20_2.f11a4 = math_lerp_float(0.015f, 0.007f, ratio);
            D_00189E20_2.f11a8 = math_lerp_float(0.29f, 0.3f, ratio);
            D_00189E20_2.f11a0 = math_random_int_range(90, 200);
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
    cam_set_limits_fourth(D_00189E20_2.f11a4, D_00189E20_2.f11a8);
    g_hero_item_attach_records.f278 = D_00189E20_2.f1198;
    g_hero_item_attach_records.f274 = D_00189E20_2.f1194;
    if (applyBlend) {
        cam_set_limits_second(0.008f, 0.3f);
        g_hero_item_attach_records.f118 = g_hero_item_attach_records.f278 * 0.52f;
        g_hero_item_attach_records.f114 = g_hero_item_attach_records.f274 * 0.55f;
    }
}
