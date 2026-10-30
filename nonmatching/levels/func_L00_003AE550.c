/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G0 -ffunction-sections.
 * 952/944 bytes; shared hero-base high-half lifetime and branch scheduling differ.
 * Reopen with a source witness for the independent hero-base evaluations; the RAC1 mine predictor is the semantic analogue.
 * ABI/bounds: All four local vectors have 16-byte extent/alignment. The ride-transform helper returns a pointer, verified against the current thrown-moby source.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
/* Projectile-impact prediction. The related RAC1 predict_mine_impact in
 * src/overlays/shared/bolts_and_wrench.c supplied the control-flow analogue;
 * all offsets, states and constants below are from the RAC2 body. */
#include "common.h"

typedef float ImpactVector[4] __attribute__((aligned(16)));
extern unsigned char D_00189E20[];
extern int D_L00_001A8F00;
extern unsigned char D_L00_001BF200[];
extern unsigned char D_L00_001B8DC0[];
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void *func_002AD0B0(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern int func_00282948(int *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_003AD7C8(void);

int func_L00_003AE550(unsigned char *motion, unsigned char *object, int mode)
{
    ImpactVector position, velocity, previous, ray;
    int frames, i;
    unsigned char *vars, *hero = D_00189E20;

    if (*(int *)(hero + 0x2294) == 0x6f) return 0;
    if (D_L00_001A8F00) return 0;
    qcopy(previous, object + 0x10);
    if (object[0x20] == 1) {
        position[0] = func_00283180(func_00283B98(-0.36196801f,
            func_00283248(*(float *)(hero + 0x760), *(float *)(hero + 0x764)))) * 0.85903901f;
        position[1] = func_00283198(func_00283B98(-0.36196801f,
            func_00283248(*(float *)(hero + 0x760), *(float *)(hero + 0x764)))) * 0.85903901f;
        *(int *)&position[2] = 0;
        func_00282CC0(position, position, hero + 0x80);
        position[2] += 0.49082f;
        qcopy(velocity, motion);
        if (*(void **)(hero + 0x33c) && func_002AD0B0(*(void **)(hero + 0x33c)) && mode)
            func_00282CC0(velocity, velocity, hero + 0x110);
        frames = 120;
    } else {
        vars = *(unsigned char **)(*(unsigned char **)(motion + 0x30) + 0x68);
        qcopy(position, object + 0x10);
        qcopy(velocity, motion);
        frames = *(short *)(motion + 0x34);
        if (*(int *)(vars + 0x50)) *(short *)(motion + 0x36) = 1;
    }
    qcopy(ray, *(unsigned char **)(hero + 0x2290) + 0x10);
    ray[2] = position[2];
    if (func_002761F8(ray, position, 0x10, *(void **)(hero + 0x2290), 0)) {
        if (func_00278E78() && *(int *)(D_L00_001BF200 + 0x1c) > 0)
            qcopy(motion + 0x10, D_L00_001BF200 + 0x20);
    }
    while (!func_00282948(&frames)) {
        qcopy(previous, position);
        i = 9;
        do {
            func_00282CC0(position, position, velocity);
            velocity[2] -= 0.0027222224f;
        } while (--i >= 0);
        if (!func_002761F8(previous, position, 0x12, object, 0)) continue;
        if (!func_00278E78() && velocity[2] > 0.0f) continue;
        if (*(int *)(D_L00_001BF200 + 0x1c) > 0) {
            qcopy(motion + 0x10, D_L00_001BF200 + 0x20);
            break;
        }
    }
    if (!frames) return 0;
    if (!mode && (!*(void **)(D_L00_001BF200 + 0x18)
        || !func_002AD0B0(*(void **)(D_L00_001BF200 + 0x18)))) return 0;
    if (mode != 2 || !*(void **)(D_L00_001BF200 + 0x18)
        || !func_002AD0B0(*(void **)(D_L00_001BF200 + 0x18)))
        func_L00_002E6CF0(func_L00_003AD7C8, object);
    qcopy(motion + 0x20, D_L00_001BF200 + 0x40);
    func_00282CF0(previous, motion + 0x10, D_L00_001B8DC0);
    func_00282D30(previous, previous, 0.95f);
    func_00282CC0(motion + 0x10, previous, D_L00_001B8DC0);
    return 1;
}
