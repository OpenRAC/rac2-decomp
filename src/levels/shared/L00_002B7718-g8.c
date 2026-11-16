/* Applies state-dependent clamps to hero pose rotation components. */
#include "common.h"
typedef int Vec __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[828];
    int f33c;
    unsigned char pad340[8];
    short f348;
    unsigned char pad34a[8010];
    int f2294;
    unsigned char pad2298[34];
    unsigned char f22ba;
    unsigned char f22bb;
    unsigned char pad22bc[7];
    unsigned char f22c3;
    unsigned char pad22c4[552];
    short f24ec;
} Root;
extern Root g_hero_state;
typedef struct {
    unsigned char pad110[272];
    float f110;
    float f114;
    unsigned char pad270[344];
    float f270;
    float f274;
    unsigned char pad5e4[876];
    float f5e4;
    unsigned char pad624[60];
    float f624;
    float f628;
    unsigned char pad694[104];
    float f694;
    unsigned char pad6d4[60];
    float f6d4;
    float f6d8;
    unsigned char pad950[628];
    float f950;
    float f954;
    unsigned char pada00[168];
    float fa00;
    float fa04;
    unsigned char padab0[168];
    float fab0;
    float fab4;
    unsigned char padb60[168];
    float fb60;
    float fb64;
} Pose;
extern Pose g_hero_item_attach_records;
extern int ref_L00_002B7718_0 __attribute__((sda));
extern int g_hero_action_blocked_flag;
extern void transform_vector(void *, void *, void *);
extern void cam_set_limits_second(float, float);
extern float fast_vec_dist(void *, void *);

/* Tilts the hero's head, spine and arms toward where the stick or aim points, with limits that depend on what the hero is doing. */
void UpdateHeroTiltPoseTargets(void)
{
    union { Vec q; float f[4]; } vector;
    float limit, x, y, z;
    int flag;

    if (g_hero_state.f348 && !g_hero_state.f22ba) {
        vector.q = 0;
        vector.f[2] = -1.0f;
        transform_vector(&vector, &vector, (char *)&g_hero_state + 0x40);
        cam_set_limits_second(0.013f, 0.3f);
        limit = 0.36651918292045593f;
        if (g_hero_state.f2294 == 109)
            limit = 0.087266475f;
        else if (g_hero_state.f2294 == 110 || g_hero_state.f2294 == 4)
            limit = 0.19198623299598694f;
        if (g_hero_state.f22bb && limit > 0.12217305600643158f)
            limit = 0.12217305600643158f;
        if (g_hero_state.f33c && limit > 0.15707965195178986f)
            limit = 0.15707965195178986f;
        if (!g_hero_state.f24ec) {
            x = vector.f[0] * 0.6981318f;
            if (x > limit) x = limit;
            else if (x < -limit) x = -limit;
            g_hero_item_attach_records.f114 = x;
            g_hero_item_attach_records.f274 = -x * 0.5f;
            if (g_hero_state.f22bb) {
                g_hero_item_attach_records.f5e4 = -x;
                g_hero_item_attach_records.f694 = -x;
            }
        }
        y = -vector.f[1] * 0.6981318f;
        if (y > limit) y = limit;
        else if (y < -limit) y = -limit;
        z = -vector.f[0] * 1.2217305898666382f;
        g_hero_item_attach_records.f110 = y;
        g_hero_item_attach_records.f270 = -y * 0.25f;
        if (z > 0.994837760925293f) z = 0.994837760925293f;
        if (z < -0.12217305600643158f) z = -0.12217305600643158f;
        if (vector.f[2] > 0.85f) {
            if (z < 1.396263599395752f) z = 1.396263599395752f;
        } else if (vector.f[2] > 0.5f) {
            if (z < 1.2217305898666382f) z = 1.2217305898666382f;
        }
        y = vector.f[1] * 1.2217305898666382f;
        g_hero_item_attach_records.f954 = z * 0.57f;
        g_hero_item_attach_records.fa04 = z * 0.5f;
        g_hero_item_attach_records.fb64 = z * 0.35f;
        g_hero_item_attach_records.fab4 = z * 0.5f;
        if (y > 1.2217305898666382f) y = 1.2217305898666382f;
        else if (y < -1.2217305898666382f) y = -1.2217305898666382f;
        g_hero_item_attach_records.fb60 = y;
        g_hero_item_attach_records.f950 = y * 0.7f;
        g_hero_item_attach_records.fa00 = y * 0.7f;
        g_hero_item_attach_records.fab0 = y * 0.7f;
    }
    if (g_hero_state.f22c3 == 1 || ref_L00_002B7718_0) {
        vector.q = 0;
        vector.f[0] = 330.0f;
        vector.f[1] = 245.0f;
        vector.f[2] = 138.0f;
        flag = 0;
        if (fast_vec_dist((char *)&g_hero_state + 0x80, &vector) < 35.0f)
            flag = 1;
        if (g_hero_action_blocked_flag) flag = 1;
        if (g_hero_state.f22bb && flag) {
            g_hero_item_attach_records.f6d4 = 0.05f;
            g_hero_item_attach_records.f6d8 = 0.3f;
            g_hero_item_attach_records.f694 = -0.22689282894134521f;
            g_hero_item_attach_records.f5e4 = -0.22689282894134521f;
            g_hero_item_attach_records.f628 = 0.3f;
            g_hero_item_attach_records.f624 = 0.05f;
        }
    }
}
