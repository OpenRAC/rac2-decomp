#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { float x; float y; float z; } ContactVector3;
typedef struct {
    unsigned char pad0[0x1d4];
    int f1D4;
    unsigned char pad1d8[0x38];
    short f210;
    unsigned char pad212[0x52];
    float f264;
    unsigned char pad268[0x1c];
    unsigned char f284;
    unsigned char f285;
    unsigned char pad286[0xe];
    unsigned char *f294;
    unsigned char pad298[0x84];
    float f31C;
    unsigned char pad320[0x1cc];
    float f4EC;
    unsigned char pad4f0[0xc];
    float f4FC;
    unsigned char pad500[0x20];
    float f520;
    unsigned char pad524[0x54];
    int f578;
    unsigned char pad57c[0x1d18];
    int f2294;
    unsigned char pad2298[0x4];
    int f229C;
    unsigned char pad22a0[0x4];
    int f22A4;
    unsigned char pad22a8[0x8];
    int f22B0;
    unsigned char pad22b4[0xf];
    unsigned char f22C3;
    unsigned char pad22c4[0x214];
    short f24D8;
    unsigned char f24DA;
    unsigned char f24DB;
} WallContactHero;
extern WallContactHero g_hero_state;
typedef struct {
    unsigned char pad0[0x18];
    unsigned char *object;
    unsigned char pad1c[4];
    Vector point;
    unsigned char pad30[0x10];
    Vector normal;
} WallContactHit;
extern WallContactHit g_collision_result;
extern float cam_get_view_space_height(char *);
extern void cam_set_view_space_height(Quadword *, Quadword *, float);
extern void cam_set_view_space_vector_length(char *, int, float);
extern void hero_apply_mode_transform_reversed(ContactVector3 *, ContactVector3 *, float);
extern void FastVecAdd(void *, void *, void *);
extern int func_PAL_L00_002ACE70(void *, void *, void *);
extern int hero_test_reach_blend(float *, float, float);
extern char *moby_get_private_value_2(unsigned char *);
extern void hero_build_relative_offset(float *output, float scale, float angle, float height, int flag);
extern int CollLine(void *, void *, unsigned int, void *, void *);
extern int GetCollHitMaterial(void);
extern float cam_get_view_space_angle(void *);
extern void transform_vector(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float vec_distance_xy(void *, void *);

/* Predict the next ledge contact, then validate the two obstruction probes. */
void func_PAL_L00_002AC460(void)
{
    Vector predicted, probeEnd, localNormal;
    unsigned char *state;
    int contact;
    int ticks;
    float steps;
    float height, distance, angle, limit;

    if (g_hero_state.f31C < 0.4f) return;
    if (cam_get_view_space_height((char *)&g_hero_state + 0xF0) < -0.40000004f || g_hero_state.f22C3) return;
    if (g_hero_state.f578) {
        g_hero_state.f1D4 = 0;
        return;
    }
    qcopy(&predicted, (unsigned char *)&g_hero_state + 0x80);
    ticks = 17;
    qcopy(&probeEnd, (unsigned char *)&g_hero_state + 0x110);
    steps = (float)ticks;
    cam_set_view_space_height(&probeEnd.q, &probeEnd.q, 0.0f);
    cam_set_view_space_vector_length((char *)&probeEnd, (int)&probeEnd, steps);
    FastVecAdd(&predicted, &predicted, &probeEnd);
    distance = cam_get_view_space_height((char *)&g_hero_state + 0xF0);
    distance = distance * steps - g_hero_state.f520 * steps * steps * 0.5f;
    hero_apply_mode_transform_reversed((ContactVector3 *)&predicted,
                     (ContactVector3 *)&predicted, distance);
    if (func_PAL_L00_002ACE70(&predicted, (unsigned char *)&g_hero_state + 0x90, 0)) {
        g_hero_state.f1D4 = 0;
        g_hero_state.f210 = 0x13;
        return;
    }
    if (!hero_test_reach_blend(0, 0.3f, 1.0f)) return;
    state = 0;
    if (g_collision_result.object) state = (unsigned char *)moby_get_private_value_2(g_collision_result.object);
    height = 1.7f;
    if (state && (*(unsigned int *)(state + 0x3C) & 0x20)) height = 0.5f;
    else if (g_hero_state.f2294 != 0x11 && (!g_hero_state.f285 || g_hero_state.f284)) height = 3.0f;
    hero_build_relative_offset(predicted.f, 0.0f, 0.0f, height, 1);
    hero_build_relative_offset(probeEnd.f, g_hero_state.f264 + 1.4f, 0.0f, height, 1);
    if (!CollLine(&predicted, &probeEnd, 2, 0, 0)) return;
    contact = GetCollHitMaterial();
    if (contact == 10 || contact == 12) return;
    g_hero_state.f294 = g_collision_result.object;
    angle = cam_get_view_space_angle(&g_collision_result.normal);
    if (angle < 1.3089970350265503f) return;
    transform_vector(&localNormal, &g_collision_result.normal, (unsigned char *)&g_hero_state + 0x40);
    angle = mat_fast_helper_a(localNormal.f[0], localNormal.f[1]);
    angle = FastDiffRots(angle, 3.1415927410125732f);
    if (0.8726646900177002f < angle) return;
    limit = g_hero_state.f2294 == 0x11 ? 0.95f : 0.72f;
    hero_build_relative_offset(predicted.f, 0.0f, 0.0f, 0.2f, 1);
    hero_build_relative_offset(probeEnd.f, g_hero_state.f264 + 1.4f, 0.0f, 0.2f, 1);
    if (!CollLine(&predicted, &probeEnd, 2, 0, 0)) return;
    distance = vec_distance_xy(&g_collision_result.point, &predicted);
    if (limit < distance) return;
    *(Quadword *)((unsigned char *)&g_hero_state + 0x4E0) = g_collision_result.normal.q;
    g_hero_state.f4EC = mat_fast_helper_a(g_collision_result.normal.f[0], g_collision_result.normal.f[1]);
    if (g_hero_state.f229C != 4 && g_hero_state.f22A4 != 4 && g_hero_state.f22B0 != 4) return;
    if (g_hero_state.f24D8 && FastDiffRots(g_hero_state.f4FC, g_hero_state.f4EC) < 2.967060089111328f) return;
    g_hero_state.f24DA = 0;
    if (contact == 15) g_hero_state.f24DA = 1;
    else if (g_hero_state.f24DB) return;
    if (g_hero_state.f2294 == 0x11)
        g_hero_state.f1D4 = 6;
    else
        g_hero_state.f1D4 = 5;
}
