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
extern Hit g_collision_result;
extern char D_L00_001BF220[];
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
extern void ApproachValue(float *, float, float);
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

/* Finds the ground under the hero, and records its slope, height and what it is made of. It also checks the ground at the sides. */
void hero_l00_update_ground_contact(void) {
    Vec4 ray_end, ray_start, scratch_vec, side_start, side_end, side_slope, side_normal;
    s32 surface_type;
    s32 i;
    f32 angle;
    u8 *data;
    Vec4 *normal;
    HeroGround *hero;

    s32 probe_mode;
    f32 probe_depth;

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
    probe_mode = 1;
    probe_depth = g_hero_state.xF234 * 2.2f;
    if (g_hero_state.xI208c == 2) {
        probe_depth = g_hero_state.xF234 * 2.9f;
    }
    if (hero_is_in_special_kind_or_mode()) probe_depth = 0.0f;
    BuildOffsetVectorPair(&ray_start, &ray_end, probe_mode, probe_depth, -48.0f);
    if (CollLine(&ray_start, &ray_end, 2, g_hero_state.xI2080, 0) == 0) {
        goto tail;
    }
    surface_type = func_L00_002E2048();

    g_hero_state.xB12ed = surface_type;
    if (g_collision_result.i18 != 0) g_hero_state.xB12ed = 0;
    if (g_current_map_index == 7 && g_collision_result.i18 != 0) g_hero_state.xB12ed = 1;
    g_hero_state.xH12e0 = GetCollHitMaterial();
    if (g_hero_state.xH12e0 == 0) {
        g_hero_state.xF2f0 = coll_get_ground_height_at_position(D_L00_001BF220, (u8 *)&g_hero_state + 0x2B0);
        if (g_hero_state.xF88 < g_hero_state.xF2f0 && g_hero_state.xI2f8 <= 0) {
            g_hero_state.xI2f8 = 1;
        }
        if (CollLine(&ray_start, &ray_end, 0x24, g_hero_state.xI2080, 0) == 0) {
            goto tail;
        }
        surface_type = func_L00_002E2048();
        g_hero_state.xB12ed = surface_type;
    }
    if (g_hero_state.xH12e0 == 0xD) {
        g_hero_state.xF2f0 = g_collision_result.v20.f[2];
        ray_start.f[2] = g_collision_result.v20.f[2] - 0.01f;
        if (CollLine(&ray_start, &ray_end, 4, g_hero_state.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (g_hero_state.xH12e0 == 3) {
        g_hero_state.xF2f4 = g_collision_result.v20.f[2];
        ray_start.f[2] = g_collision_result.v20.f[2] - 0.01f;
        if (CollLine(&ray_start, &ray_end, 4, g_hero_state.xI2080, 0) == 0) {
            goto tail;
        }
    }
    if (g_hero_state.xH12e0 == 0xB) {
        g_hero_state.xF2f4 = g_collision_result.v20.f[2];
        goto tail;
    }
    if (g_hero_state.xH12e0 == 1 && (u32)(g_hero_state.xI2084 - 0x79) < 2) {
        goto tail;
    }
    if (g_collision_result.i18 != 0) {
        if (moby_is_in_special_class_range(g_collision_result.i18)) {
            g_hero_state.xH30a = 1;
        }
        data = moby_get_private_value_0(g_collision_result.i18);
        if (data != 0 && (*(u16 *)(data + 0x1E) & 8)) {
            g_hero_state.xH30a = 1;
        }
        data = moby_get_private_value_2(g_collision_result.i18);
        if (data != 0 && (*(int *)(data + 0x3c) & 8)) g_hero_state.xH30a = 1;
    }
    if (g_collision_result.i1C > 0) {
        qcopy((u8 *)&g_hero_state + 0x2D0, &g_collision_result.v20);
        g_hero_state.u2d8.F = g_collision_result.v20.f[2];
        if (D_001A8FF0) g_hero_state.u2d8.F = gravity_get_center_distance(&g_collision_result.v20);
        g_hero_state.xF2dc = fast_vec_dist((u8 *)&g_hero_state + 0x80, ((u8 *)&g_hero_state + 0x2D0));
        g_hero_state.xI2fc = g_collision_result.i18;
        func_001290E0((u8 *)&g_hero_state + 0x2A0, (u8 *)&g_collision_result.f40);
        g_hero_state.u2e0.F = cam_get_view_space_angle((u8 *)&g_collision_result.f40);
        g_hero_state.xF2ec = mat_fast_helper_a(g_collision_result.f40, g_collision_result.f44);
        FastVecSub(&scratch_vec, ((u8 *)&g_hero_state + 0x2D0), (u8 *)&g_hero_state + 0x80);
        if (0.0f < FastVecDot(&scratch_vec, (u8 *)&g_hero_state + 0x2A0)) {
            g_hero_state.xF2dc = -g_hero_state.xF2dc;
        }
        if (g_hero_state.xF2dc < 0.02f) {
            g_hero_state.u30c.H = 0;
            if (g_hero_state.u2e0.F <= 0.87266469f || g_hero_state.xB20b3 != 0) {
                g_hero_state.u30e.H = 0;
                g_hero_state.xIa80 = g_collision_result.i18;
            }
        }
    }
tail:
    if (g_hero_state.xF88 > g_hero_state.xF2f0) g_hero_state.xI2f8 = 0;
    if (g_hero_state.u30e.H != 0) g_hero_state.xI300 = 0;
    else {
        g_hero_state.xI300++;
        *(Q *)((u8 *)&g_hero_state + 0x2E0) = *(Q *)((u8 *)&g_hero_state + 0x2D0);
        if (g_hero_state.xI2084 != 0x38) g_hero_state.field18c0 = 0;
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
        angle = -1.0f;
        if (*(float *)((u8 *)hero + 0xbc) > 0.0f) angle = 1.0f;
        FastVecSub(normal, (u8 *)normal - 0x210, (u8 *)normal - 0x240);
        vec_scale_to_length(normal, normal, angle);
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
    hero_compute_angles_to_local_dir((u8 *)&g_hero_state + 0x2A0, &scratch_vec);
    if (-0.785398244f < scratch_vec.f[1] && scratch_vec.f[1] < 0.785398244f) {
        g_hero_state.u2e4.F = scratch_vec.f[1];
    }
    if (-0.785398244f < scratch_vec.f[0] && scratch_vec.f[0] < 0.785398244f) {
        g_hero_state.u2e8.F = scratch_vec.f[0];
    }
    for (i = 0; i < 2; i++) {
        angle = 1.57079649f;
        if (i == 1) {
            angle = -angle;
        }
        hero_build_relative_offset(&side_start, 0.2f, angle, 0.45f, 1);
        hero_build_relative_offset(&side_end, 0.2f, angle, -0.45f, 1);
        if (CollLine(&side_start, &side_end, 0x22, g_hero_state.xI2080, 0)) {
            if (D_001A8FF0) g_hero_state.a2c0.f[i] = gravity_get_center_distance(&g_collision_result.v20) - gravity_get_center_distance((u8 *)&g_hero_state + 0x2d0);
            else g_hero_state.a2c0.f[i] = g_collision_result.v20.f[2] - g_hero_state.u2d8.F;
            if (0.4f < math_fabs(g_hero_state.a2c0.f[i])) {
                g_hero_state.a2c0.f[i] = 0.0f;
            }
            func_001290E0(&side_normal, (u8 *)&g_collision_result.f40);
            hero_compute_angles_to_local_dir(&side_normal, &side_slope);
            if (-0.785398244f < side_slope.f[1] && side_slope.f[1] < 0.785398244f) {
                g_hero_state.a2c8.f[i] = side_slope.f[1];
            }
            if (-0.785398244f < side_slope.f[0] && side_slope.f[0] < 0.785398244f) {
                g_hero_state.a2d0.f[i] = side_slope.f[0];
            }
        } else {
            g_hero_state.a2c0.i[i] = 0;
            g_hero_state.a2c8.f[i] = g_hero_state.u2e4.F;
            g_hero_state.a2d0.f[i] = g_hero_state.u2e8.F;
        }
    }
}
