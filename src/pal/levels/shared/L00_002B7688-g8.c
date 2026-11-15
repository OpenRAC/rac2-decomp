#include "include_asm.h"

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
extern Pose D_L00_0025BE10;
extern int ref_L00_002B7718_0 __attribute__((sda));
extern int D_L00_001A8FF4;
extern void transform_vector(void *, void *, void *);
extern void cam_set_limits_second(float, float);
extern float fast_vec_dist(void *, void *);

void func_PAL_L00_002B7688(void)
{
    union { Vec q; float f[4]; } vector;
    float limit, x, y, z;
    int flag;

    if (g_hero_state.f348 && !g_hero_state.f22ba) {
        vector.q = 0;
        vector.f[2] = -1.0f;
        transform_vector(&vector, &vector, (char *)&g_hero_state + 0x40);
        cam_set_limits_second(0.018720001f, 0.43200004f);
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
            D_L00_0025BE10.f114 = x;
            D_L00_0025BE10.f274 = -x * 0.5f;
            if (g_hero_state.f22bb) {
                D_L00_0025BE10.f5e4 = -x;
                D_L00_0025BE10.f694 = -x;
            }
        }
        y = -vector.f[1] * 0.6981318f;
        if (y > limit) y = limit;
        else if (y < -limit) y = -limit;
        z = -vector.f[0] * 1.2217305898666382f;
        D_L00_0025BE10.f110 = y;
        D_L00_0025BE10.f270 = -y * 0.25f;
        if (z > 0.994837760925293f) z = 0.994837760925293f;
        if (z < -0.12217305600643158f) z = -0.12217305600643158f;
        if (vector.f[2] > 0.85f) {
            if (z < 1.396263599395752f) z = 1.396263599395752f;
        } else if (vector.f[2] > 0.5f) {
            if (z < 1.2217305898666382f) z = 1.2217305898666382f;
        }
        y = vector.f[1] * 1.2217305898666382f;
        D_L00_0025BE10.f954 = z * 0.57f;
        D_L00_0025BE10.fa04 = z * 0.5f;
        D_L00_0025BE10.fb64 = z * 0.35f;
        D_L00_0025BE10.fab4 = z * 0.5f;
        if (y > 1.2217305898666382f) y = 1.2217305898666382f;
        else if (y < -1.2217305898666382f) y = -1.2217305898666382f;
        D_L00_0025BE10.fb60 = y;
        D_L00_0025BE10.f950 = y * 0.7f;
        D_L00_0025BE10.fa00 = y * 0.7f;
        D_L00_0025BE10.fab0 = y * 0.7f;
    }
    if (g_hero_state.f22c3 == 1 || ref_L00_002B7718_0) {
        vector.q = 0;
        vector.f[0] = 330.0f;
        vector.f[1] = 245.0f;
        vector.f[2] = 138.0f;
        flag = 0;
        if (fast_vec_dist((char *)&g_hero_state + 0x80, &vector) < 35.0f)
            flag = 1;
        if (D_L00_001A8FF4) flag = 1;
        if (g_hero_state.f22bb && flag) {
            D_L00_0025BE10.f6d4 = 0.072000004f;
            D_L00_0025BE10.f6d8 = 0.43200004f;
            D_L00_0025BE10.f694 = -0.22689282894134521f;
            D_L00_0025BE10.f5e4 = -0.22689282894134521f;
            D_L00_0025BE10.f628 = 0.43200004f;
            D_L00_0025BE10.f624 = 0.072000004f;
        }
    }
}
