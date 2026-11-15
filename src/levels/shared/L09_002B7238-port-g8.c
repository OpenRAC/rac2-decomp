#include "common.h"

/* Adapted from public OpenRAC/rac1-decomp hero_collision.c (GPL-3.0),
 * with the measured Going Commando fields and additional gravity probes. */
typedef int Q __attribute__((mode(TI)));
typedef union { float F; int I; } U32;
typedef union { short H; unsigned short U; } U16;
typedef union { float f[2]; int i[2]; } PAIR;
typedef union { float f[4]; int i[4]; } Vec4;
typedef struct {
    u8 pad0[136];
    float xF88;
    u8 pad8c[472];
    float xF234;
    u8 pad268[56];
    int xI270;
    int xI274;
    float xF278;
    u8 pad2ac[28];
    float xF298;
    u8 pad2cc[52];
    PAIR a2c0;
    PAIR a2c8;
    PAIR a2d0;
    U32 u2d8;
    float xF2dc;
    U32 u2e0;
    U32 u2e4;
    U32 u2e8;
    float xF2ec;
    float xF2f0;
    float xF2f4;
    int xI2f8;
    int xI2fc;
    int xI300;
    u8 pad344[6];
    short xH30a;
    U16 u30c;
    U16 u30e;
    u8 pad350[2240];
    int xIa80;
    u8 padc14[2172];
    short xH12e0;
    u8 pad1492[11];
    u8 xB12ed;
    u8 pad149e[1058];
    int field18c0;
    u8 pad18c4[2508];
    int xI2080;
    int xI2084;
    u8 pad2298[4];
    int xI208c;
    u8 pad22a0[35];
    u8 xB20b3;
} HeroGround;
extern HeroGround g_hero_state;
typedef struct { u8 pad[24]; int i18, i1C; Vec4 v20; u8 pad30[16]; float f40, f44; } Hit;
extern Hit D_L09_001BFE40;
extern char D_L09_001BFE60[];
extern int g_current_map_index;
extern int D_001A8FF0 MACRO_ADDR;
extern int D_001A8FF4;
extern int hero_is_in_special_kind_or_mode(void);
extern void vec_clear_128(void *);
extern void BuildOffsetVectorPair(void *, void *, int, float, float);
extern int CollLine(void *, void *, int, int, int);
extern int func_L00_002E2048(void), GetCollHitMaterial(void);
extern float coll_get_ground_height_at_position(void *, void *);
extern int moby_is_in_special_class_range(int);
extern u8 *moby_get_private_value_0(int);
extern u8 *moby_get_private_value_2(int);
extern float gravity_get_center_distance(void *);
extern void vec_compute_flat_direction_from_point(void *, void *, int);
extern f32 ApproachValue(float *, float, float);
extern float fast_vec_dist(void *, void *);
extern void func_001290E0(void *, void *);
extern float cam_get_view_space_angle(void *), mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float), vec_scale_to_length(void *, void *, float);
extern void hero_compute_angles_to_local_dir(void *, void *);
/* The EE integer and FP argument banks retain their original order. */
extern void hero_build_relative_offset(void *, float, float, float, int);
extern float math_fabs(float);

/* Checks the ground under the player each frame and records the surface height, slope and what it is standing on. */
void hero_probe_ground(void) {
    Vec4 v0, v10, v20, v30, v40, v50, v60;
    s32 r;
    s32 i;
    f32 a;
    u8 *p;
    Vec4 *normal;
    HeroGround *hero;

    s32 k;
    f32 g;
    HeroGround *body;

    g_hero_state.xF278 = 1.0f;
    g_hero_state.u30e.U++;
    g_hero_state.u30c.U++;
    g_hero_state.xI270 = 0;
    g_hero_state.xI274 = 0;
    g_hero_state.u2e0.I = 0;
    g_hero_state.u2d8.I = 0;
    vec_clear_128((u8 *)&g_hero_state + 0x2D0);
    g_hero_state.xH30a = 0;
    g_hero_state.xF2dc = 32.0f;
    g_hero_state.xI2fc = 0;
    if (g_hero_state.xI2f8 != 0) {
        g_hero_state.xI2f8++;
    }
    k = 1;
    g = g_hero_state.xF234 * 2.2f;
    if (g_hero_state.xI208c == 2) {
        g = g_hero_state.xF234 * 2.9f;
    }
    if (hero_is_in_special_kind_or_mode()) g = 0.0f;
    BuildOffsetVectorPair(&v10, &v0, k, g, -48.0f);
    if (CollLine(&v10, &v0, 2, g_hero_state.xI2080, 0) == 0) {
        goto tail;
    }
    r = func_L00_002E2048();

    g_hero_state.xB12ed = r;
    if (D_L09_001BFE40.i18 != 0) g_hero_state.xB12ed = 0;
    if (g_current_map_index == 7 && D_L09_001BFE40.i18 != 0) g_hero_state.xB12ed = 1;
    g_hero_state.xH12e0 = GetCollHitMaterial();
    if (g_hero_state.xH12e0 == 0) {
        g_hero_state.xF2f0 = coll_get_ground_height_at_position(D_L09_001BFE60, (u8 *)&g_hero_state + 0x2B0);
        if (g_hero_state.xF88 < g_hero_state.xF2f0 && g_hero_state.xI2f8 <= 0) {
            g_hero_state.xI2f8 = 1;
        }
        if (CollLine(&v10, &v0, 0x24, g_hero_state.xI2080, 0) == 0) {
            goto tail;
        }
        r = func_L00_002E2048();
        g_hero_state.xB12ed = r;
    }
    if (g_hero_state.xH12e0 == 3) {
        g_hero_state.xF2f4 = D_L09_001BFE40.v20.f[2];
        v10.f[2] = D_L09_001BFE40.v20.f[2] - 0.01f;
        if (CollLine(&v10, &v0, 4, g_hero_state.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (g_hero_state.xH12e0 == 11) {
        g_hero_state.xF2f4 = D_L09_001BFE40.v20.f[2];
        goto tail;
    }
    if (g_hero_state.xH12e0 == 1 && (u32)(g_hero_state.xI2084 - 0x79) < 2) {
        goto tail;
    }
    if (D_L09_001BFE40.i18 != 0) {
        if (moby_is_in_special_class_range(D_L09_001BFE40.i18)) {
            g_hero_state.xH30a = 1;
        }
        p = moby_get_private_value_0(D_L09_001BFE40.i18);
        if (p != 0 && (*(u16 *)(p + 0x1E) & 8)) {
            g_hero_state.xH30a = 1;
        }
        p = moby_get_private_value_2(D_L09_001BFE40.i18);
        if (p != 0 && (*(int *)(p + 0x3c) & 8)) g_hero_state.xH30a = 1;
    }
    if (D_L09_001BFE40.i1C > 0) {
        qcopy((u8 *)&g_hero_state + 0x2D0, &D_L09_001BFE40.v20);
        g_hero_state.u2d8.F = D_L09_001BFE40.v20.f[2];
        if (D_001A8FF0) g_hero_state.u2d8.F = gravity_get_center_distance(&D_L09_001BFE40.v20);
        g_hero_state.xF2dc = fast_vec_dist((u8 *)&g_hero_state + 0x80, ((u8 *)&g_hero_state + 0x2D0));
        g_hero_state.xI2fc = D_L09_001BFE40.i18;
        func_001290E0((u8 *)&g_hero_state + 0x2A0, (u8 *)&D_L09_001BFE40.f40);
        g_hero_state.u2e0.F = cam_get_view_space_angle((u8 *)&D_L09_001BFE40.f40);
        g_hero_state.xF2ec = mat_fast_helper_a(D_L09_001BFE40.f40, D_L09_001BFE40.f44);
        FastVecSub(&v20, ((u8 *)&g_hero_state + 0x2D0), (u8 *)&g_hero_state + 0x80);
        if (0.0f < FastVecDot(&v20, (u8 *)&g_hero_state + 0x2A0)) {
            g_hero_state.xF2dc = -g_hero_state.xF2dc;
        }
        if (g_hero_state.xF2dc < 0.02f) {
            g_hero_state.u30c.H = 0;
            if (g_hero_state.u2e0.F <= 0.87266469f || g_hero_state.xB20b3 != 0) {
                g_hero_state.u30e.H = 0;
                g_hero_state.xIa80 = D_L09_001BFE40.i18;
            }
        }
    }
tail:
    body = &g_hero_state;
    if (body->xF88 > body->xF2f0) body->xI2f8 = 0;
    if (body->u30e.H != 0) body->xI300 = 0;
    else {
        body->xI300++;
        qcopy((u8 *)body + 0x2E0, (u8 *)body + 0x2D0);
        if (body->xI2084 != 0x38) body->field18c0 = 0;
    }
    normal = (Vec4 *)((u8 *)&g_hero_state + 0x2C0);
    vec_clear_128(normal);
    hero = (HeroGround *)((u8 *)normal - 0x2C0);
    switch (hero->xB20b3) {
    case 0:
        hero->xF298 = -1.0f;
        break;
    case 1:
        if (D_001A8FF4) vec_compute_flat_direction_from_point((u8 *)normal - 0x240, normal, 0);
        else if (*(float *)((u8 *)hero + 0x2fc) != 0.0f) {
            ApproachValue((float *)((u8 *)normal + 0x3c), 0.0f, 1.0f);
            qcopy(normal, (u8 *)normal + 0x30);
        } else {
            qcopy(normal, (u8 *)normal - 0x20);
            FastVecScale(normal, normal, -1.0f);
        }
        break;
    case 2:
        a = -1.0f;
        if (*(float *)((u8 *)hero + 0xbc) > 0.0f) a = 1.0f;
        FastVecSub(normal, (u8 *)normal - 0x210, (u8 *)normal - 0x240);
        vec_scale_to_length(normal, normal, a);
        break;
    }
    g_hero_state.u2e4.I = 0;
    g_hero_state.u2e8.I = 0;
    g_hero_state.a2d0.i[0] = 0;
    g_hero_state.a2d0.i[1] = 0;
    g_hero_state.a2c8.i[0] = 0;
    g_hero_state.a2c8.i[1] = 0;
    g_hero_state.a2c0.i[0] = 0;
    g_hero_state.a2c0.i[1] = 0;
    if (!(g_hero_state.xF2dc < 0.25f)) {
        return;
    }
    if (!(g_hero_state.xI208c == 0 || g_hero_state.xI208c == 12 || g_hero_state.xI208c == 9 || g_hero_state.xI208c == 7 || (g_hero_state.xI208c == 4 && *(u8 *)((u8 *)&g_hero_state + 0x49c)) || g_hero_state.xI208c == 1)) {
        return;
    }
    hero_compute_angles_to_local_dir((u8 *)&g_hero_state + 0x2A0, &v20);
    if (-0.785398244f < v20.f[1] && v20.f[1] < 0.785398244f) {
        g_hero_state.u2e4.F = v20.f[1];
    }
    if (-0.785398244f < v20.f[0] && v20.f[0] < 0.785398244f) {
        g_hero_state.u2e8.F = v20.f[0];
    }
    for (i = 0; i < 2; i++) {
        a = 1.57079649f;
        if (i == 1) {
            a = -a;
        }
        hero_build_relative_offset(&v30, 0.2f, a, 0.45f, 1);
        hero_build_relative_offset(&v40, 0.2f, a, -0.45f, 1);
        if (CollLine(&v30, &v40, 0x22, g_hero_state.xI2080, 0)) {
            if (D_001A8FF0) g_hero_state.a2c0.f[i] = gravity_get_center_distance(&D_L09_001BFE40.v20) - gravity_get_center_distance((u8 *)&g_hero_state + 0x2d0);
            else g_hero_state.a2c0.f[i] = D_L09_001BFE40.v20.f[2] - g_hero_state.u2d8.F;
            if (0.4f < math_fabs(g_hero_state.a2c0.f[i])) {
                g_hero_state.a2c0.f[i] = 0.0f;
            }
            func_001290E0(&v60, (u8 *)&D_L09_001BFE40.f40);
            hero_compute_angles_to_local_dir(&v60, &v50);
            if (-0.785398244f < v50.f[1] && v50.f[1] < 0.785398244f) {
                g_hero_state.a2c8.f[i] = v50.f[1];
            }
            if (-0.785398244f < v50.f[0] && v50.f[0] < 0.785398244f) {
                g_hero_state.a2d0.f[i] = v50.f[0];
            }
        } else {
            g_hero_state.a2c0.i[i] = 0;
            g_hero_state.a2c8.f[i] = g_hero_state.u2e4.F;
            g_hero_state.a2d0.f[i] = g_hero_state.u2e8.F;
        }
    }
}
