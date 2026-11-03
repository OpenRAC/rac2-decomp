/* 2 November 2026, remaining-function review: nonmatching; no linked credit.
 * Profile: -O2 -G0 -ffunction-sections.
 * US check: 1200/1200 bytes, 0/3 placements.
 * Matched func_L04_00358AE8 returns u8*. Correcting its ignored result ties at 1200/1200, first mismatch+0x2D0; four loop-preheader setup rows remain.
 */
/* Sol high, v1027, 2026-10-29: 1200/1200 bytes, 0/3 USA v1.01 places.
 * Profile: default game -O2 -G0 -ffunction-sections.
 * Seven check.py compiles (plus one regalloc baseline) improve the prior draft
 * to four instructions differing, all in the loop preheader at +0x2D0,
 * +0x2DC, +0x2E8 and +0x2EC. Retail orders the normal-symbol high half,
 * random-vector address, velocity-vector address, then counter initialization;
 * C puts the symbol high half last. All remaining instructions agree.
 * Approved qcopy for the two external-to-local transfers, ordinary TI for the
 * local-to-local transfer, fixes the previous branch, float argument moves,
 * and call-delay-slot stack copy without qcopy compiler flags.
 * Explicit vector pointers, for-vs-do loop wording and grouping the measured
 * collision position/normal storage tie on these four setup instructions.
 * An explicit normal pointer outside the loop hoists an unwanted low half.
 * Reopen with a new hypothesis for partial-symbol loop-invariant ordering;
 * no MMI/compiler-reachability blocker remains. All declarations follow.
 * Symbols: _00 is the bounds reference; _01/_02 are collision point/normal
 * at level-08 001BFF60/001BFF80; no level address is embedded in the C.
 */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    Vector dir;
    float spin;
    int unused;
    void *owner;
    short life, initialLife;
    float distance;
    int approaching, triggered;
} BoltState;
typedef struct {
    Vector vector;
    void *object;
    int flags;
    u8 enabled, kind;
    u16 group;
    float radius;
    int active;
} CollisionInput;
extern char D_00189EA0[];
extern Vector ref_L08_003B2F70_00, ref_L08_003B2F70_01, ref_L08_003B2F70_02, ref_L08_003B2F70_03;
extern float func_00282E48(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern int func_00282978(short *);
extern void func_0029F338(void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_002A7878(float, float);
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern int func_002A7820(int, int);
extern u8 *func_L04_00358AE8(void *, void *, int, int, float);
extern void func_002ABBB8(void *, void *, int, int, int, int, int, int,
    int, int, int, int, float, float, float, float, float, float, float);
extern void func_00277F48(void *, float, int, void *, void *);
void func_L08_003B2F70(char *obj) {
    struct { Vector old; CollisionInput collision; Vector velocity, random; } frame;
    CollisionInput *input;
    BoltState *state = *(BoltState **)(obj + 0x68);
    float distance = func_00282E48(obj + 0x10, D_00189EA0);
    qcopy(&frame.old, obj + 0x10);
    func_00282CC0(obj + 0x10, obj + 0x10, state);
    if (!state->triggered && state->approaching && state->distance < distance && distance < 3.0f) {
        func_002E5CF8(0, 0, obj);
        state->triggered = 1;
    }
    if (distance < state->distance) state->approaching = 1;
    state->distance = distance;
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f ||
        func_00282E80(obj + 0x10, &ref_L08_003B2F70_00) > 255.0f) goto destroy;
    input = 0;
    if (!*(u8 *)(obj + 0xBC)) {
        frame.collision.flags = 0x70001;
        frame.collision.radius = 3.0f;
        frame.collision.object = obj;
        frame.collision.active = 1;
        qcopy(&frame.collision.vector, state);
        func_00282CF0(&frame.collision.vector, obj + 0x10, D_00189EA0);
        func_00282F70(&frame.collision.vector, &frame.collision.vector, 1.0f);
        input = &frame.collision;
        frame.collision.vector.f[2] = 1.0f;
        frame.collision.vector.f[3] = 5627.9248046875f;
        frame.collision.enabled = 1;
        frame.collision.kind = 3;
        frame.collision.group = *(u16 *)(obj + 0xAA);
    }
    if (func_00282978(&state->life) && !*(u8 *)(obj + 0xBC)) {
        *(u8 *)(obj + 0xBC) = 1;
        state->life = state->initialLife / 4;
    } else if (state->life <= 0 && *(u8 *)(obj + 0xBC)) {
destroy:
        func_0029F338(obj);
        return;
    }
    if (!func_002761F8(&frame.old, obj + 0x10, 0, state->owner, input)) return;
    qcopy(obj + 0x10, &ref_L08_003B2F70_01);
    if (!*(u8 *)(obj + 0xBC)) {
        Vector *random = &frame.random;
        Vector *velocity = &frame.velocity;
        int n = 4;
        do {
            frame.random.q = 0;
            --n;
            frame.random.f[0] = func_002A7878(-1.0f, 1.0f);
            frame.random.f[1] = func_002A7878(-1.0f, 1.0f);
            frame.random.f[2] = func_002A7878(-1.0f, 1.0f);
            frame.velocity.q = frame.random.q;
            func_00283028(random, state, &ref_L08_003B2F70_02);
            func_00282F20(velocity, velocity, func_00282DF0(random) * 0.5f);
            func_00282CC0(velocity, random, velocity);
            func_00282F20(velocity, velocity, func_002A7878(0.05000000447034836f, 0.10000000894069672f));
            func_L04_00358AE8(obj + 0x10, velocity, 0x7F2F4F6F, func_002A7820(10, 15), 60000.0f);
        } while (n >= 0);
    }
    func_002ABBB8(obj, state, 0, 4, 3, 6, -1, 0, 1, -1, 0, 0x810001,
        0.0f, 0.0f, 1.1f, 0.6f, 1.0f, 0.9f, 0.0f);
    func_00277F48(obj + 0x10, 1.1f, 16, obj, input);
    func_0029F338(obj);
}
