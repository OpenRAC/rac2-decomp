/* Nonmatching hero collision response, 2026-10-28. No C coverage credit.
 * Four US probes, 0/6 placements. Retained788/796B and exact frame0xA0
 * with -O2 -G0 -ffunction-sections. Narrow unsplit edges is identical;
 * no-split addresses is worse800B with a changed prologue. Remaining:
 * second position-builder argument scheduling and hero/collision global
 * high-half/low-half materialization across the two ray probes.
 * First792B diagnostic used the wrong force-flag polarity. Actual +0xE0
 * branches to the direct orientation path: force OR low planar speed selects
 * that path. Retained body corrects this. Reopen with independent original
 * address/field lifetime evidence, not repeated equivalent variants.
 *
 * Actual002D3A58 and002D3EA8 definitions return float; actual002D3B58 is a
 * void projection/mutation helper. Full002D36E0 raw body writes16B after
 * whole clear, XYZ stores, transform and optional origin add; its raw-only
 * void-return hypothesis remains provisional. Existing callers declare this
 * target void(int) and pass0/1. Actual/query return banks and fifth optional
 *40-byte input packet are preserved; both probes pass null.
 * Four local16B vectors are filled before use. Projection writes all16B for
 * hero modes0..2; the initial002D3A58 gate rejects other modes. Continued
 * mode stability across the geometry/ray calls remains a conditional source
 * invariant, not a new initialization store. Collision and hero storage stay
 * incomplete. The selected normal is flattened/normalized in place before
 * its negative velocity component is projected out, as retail does.
 */

#include "common.h"
extern unsigned char D_00189E20[], D_L01_001BF900[];
extern float func_L00_002D3A58(void *), func_L00_002D3EA8(void *);
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_L00_002D3B58(void *, void *, float);
extern float func_00282E20(const void *), func_00282DB0(const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern int func_002761F8(const void *, const void *, int, void *, const void *);
extern int func_00278E78(void);

void func_L01_002B4DA0(int forceDirection)
{
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float lowOrigin[4] __attribute__((aligned(16)));
    float farEndpoint[4] __attribute__((aligned(16)));
    float *velocity = (float *)(D_00189E20 + 0xF0);
    unsigned char *hero;
    unsigned char *hit;
    int material;
    float height, radius, slope, dot;
    if (func_L00_002D3A58(velocity) < 0.0016666668234393f) return;
    hero = (unsigned char *)velocity - 0xF0;
    height = 0.37f;
    radius = 0.5f;
    if ((unsigned int)(*(int *)(hero + 0x229C) - 17) < 2) {
        height = 0.0f;
        radius = 0.7f;
    }
    func_L00_002D36E0(origin, 1, 0.0f, 0.0f, height);
    func_L00_002D36E0(lowOrigin, 1, 0.0f, 0.0f, height * 0.3f);
    if (forceDirection || func_00282E20(velocity) < 0.01f) {
        func_00282F20(endpoint, hero, radius);
        func_00282F20(farEndpoint, hero, radius * 1.4f);
    } else {
        func_L00_002D3B58(endpoint, velocity, 0.0f);
        func_00282F20(endpoint, endpoint, radius);
        func_00282D30(farEndpoint, endpoint, 1.4f);
    }
    func_00282CC0(endpoint, endpoint, origin);
    func_00282CC0(farEndpoint, farEndpoint, lowOrigin);
    material = -1;
    if (func_002761F8(lowOrigin, farEndpoint, 2, *(void **)(D_00189E20 + 0x2290), 0)) {
        if (*(int *)(D_L01_001BF900 + 0x1C) > 0) material = func_00278E78();
    }
    slope = 0.0f;
    if (func_002761F8(origin, endpoint, 2, *(void **)(D_00189E20 + 0x2290), 0)) {
        if (*(int *)(D_L01_001BF900 + 0x1C) > 0) slope = func_L00_002D3EA8(D_L01_001BF900 + 0x40);
    }
    if (slope >= 0.8726646900177002f || material == 8 || material == 12) {
        hit = D_L01_001BF900;
        *(int *)(D_00189E20 + 0x270) = *(int *)(hit + 0x18);
        func_L00_002D3B58(hit + 0x40, hit + 0x40, 0.0f);
        func_00282F20(hit + 0x40, hit + 0x40, 1.0f);
        dot = func_00282DB0(hit + 0x40, D_00189E20 + 0xF0);
        if (dot < 0.0f) {
            func_00282D30(hit + 0x40, hit + 0x40, -dot);
            func_00282CC0(D_00189E20 + 0xF0, D_00189E20 + 0xF0, hit + 0x40);
        }
    }
}
