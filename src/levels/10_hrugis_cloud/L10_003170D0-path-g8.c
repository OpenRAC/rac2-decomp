#include "common.h"

typedef struct {
    u8 pad[0x2C8];
    u8 *child;
} HrugisPathState;

typedef int TI128 __attribute__((mode(TI)));

extern u8 *func_L05_0037B440(s32, s32);
extern f32 func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern f32 func_002A7798(f32);
extern f32 func_L01_00311C18(void *, void *, void *, void *);
extern u8 *D_L10_001B2614 MACRO_ADDR;
extern u8 D_L10_00221CD0[];
extern f32 D_L10_001B0F4C NOT_SDA;
extern s32 D_L10_001B0F44 __attribute__((sda));

/* Creates a small flying object next to the nearest of four marked spots and sets up the
   curved path it will follow towards the player. */
void func_L10_004170F8(u8 *moby) {
    f32 up[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 scaled[4] __attribute__((aligned(16)));
    f32 closest[4] __attribute__((aligned(16)));
    f32 correction[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *best, *record, *target, *childpos;
    s32 *index;
    f32 distance, dist, scale;
    s32 i;
    *(TI128 *)up = 0;
    up[2] = 1.0f;
    if (((HrugisPathState *)vars)->child) return;
    record = SpawnFreeLevelObjectById(0xF8D, 1);
    ((HrugisPathState *)vars)->child = record;
    distance = D_L10_001B0F4C;
    best = 0;
    for (index = (s32 *)(vars + 0x2A0), i = 3; i >= 0; i--, index++) {
        record = D_L10_001B2614 + *index * 128;
        dist = fast_vec_dist(record + 0x30, moby + 0x10);
        if (dist < distance) {
            distance = dist;
            best = record;
        }
    }
    if (!best) return;
    target = D_L10_001B2614 + *(s32 *)D_L10_00221CD0 * 128;
    childpos = ((HrugisPathState *)vars)->child + 0x10;
    qcopy(childpos, best + 0x30);
    FastVecSub(delta, target + 0x30, childpos);
    delta[3] = 0;
    vec_scale_to_length(((HrugisPathState *)vars)->child + 0xC0, delta, 1.0f);
    FastVecCross(((HrugisPathState *)vars)->child + 0xD0, ((HrugisPathState *)vars)->child + 0xC0, up);
    *(s32 *)(((HrugisPathState *)vars)->child + 0xDC) = 0;
    vec_scale_to_length(((HrugisPathState *)vars)->child + 0xD0, ((HrugisPathState *)vars)->child + 0xD0, 1.0f);
    FastVecCross(((HrugisPathState *)vars)->child + 0xE0, ((HrugisPathState *)vars)->child + 0xD0, ((HrugisPathState *)vars)->child + 0xC0);
    *(s32 *)(((HrugisPathState *)vars)->child + 0xEC) = 0;
    /* Retail keeps the saved position pointer live across these copies. */
    qcopy_nc(vars + 0x260, ((HrugisPathState *)vars)->child + 0x10);
    qcopy_nc(vars + 0x270, moby + 0x10);
    dist = fast_vec_dist(vars + 0x260, vars + 0x270);
    scale = EaseOutQuad(dist * 0.001953129889f) * 160.0f;
    vec_scale_to_length(scaled, delta, scale);
    FastVecAdd(vars + 0x280, scaled, vars + 0x260);
    ClosestPointOnSegment(closest, vars + 0x260, vars + 0x270, vars + 0x280);
    FastVecSub(correction, vars + 0x280, closest);
    FastVecScale(correction, correction, -1.0f);
    FastVecAdd(vars + 0x280, closest, correction);
    FastVecSub(delta, target + 0x30, vars + 0x270);
    vec_scale_to_length(scaled, delta, scale);
    FastVecAdd(vars + 0x290, scaled, vars + 0x270);
    ClosestPointOnSegment(closest, vars + 0x260, vars + 0x270, vars + 0x290);
    FastVecSub(correction, vars + 0x290, closest);
    FastVecScale(correction, correction, -1.0f);
    FastVecAdd(vars + 0x290, closest, correction);
    FastVecSub(delta, vars + 0x260, vars + 0x270);
    vec_scale_to_length(scaled, delta, 8.0f);
    FastVecAdd(vars + 0x270, scaled, vars + 0x270);
    *(s32 *)(vars + 0x2D4) = 0;
    *(f32 *)(vars + 0x2D8) = 0.011635531f;
    D_L10_001B0F44 = 1;
}
