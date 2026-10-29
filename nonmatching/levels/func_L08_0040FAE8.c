/* Complete C near miss; not linked and no matching credit.
 * Default -O2 -G0 -ffunction-sections: 628/628 bytes.
 * USA, USA2 and PAL each 0/1, first mismatch +0x13C. The four-instruction
 * sleep exit is inverted/threaded into the common epilogue; retail retains
 * a false-condition continuation and a separate unconditional exit stub.
 * Nine bounded trials. Delaying the synchronized-position pointer until after
 * each movement copy restores the retail pointer lifetime and every transfer.
 * Keep-block-order, thread-jump control and -g tie. A real integration guard
 * expands to 652 bytes and is not retained. No fake dependency or padding.
 * Full aligned next[4] and 32-byte motion state cover all vector reads. The
 * actual collision result has a 0x20 header and six full vectors through 0x7F.
 * All dependent copy/float pairs use default qcopy with its memory contract.
 * Missing, dead or wrong-class child and out-of-range coordinates delete the
 * parent actor; the valid child receives complete position/rotation vectors.
 * Reopen with grounded sleep-exit control-flow evidence, not equivalent flags.
 */
#include "common.h"

typedef struct {
    float velocity[4];
    float gravity, spin;
    u8 *owner, *child;
} MotionState;

typedef struct {
    u8 prefix00[0x20];
    float hit[4], adjusted[4], normal[4], auxiliary[3][4];
} __attribute__((aligned(16))) CollisionResult;
extern CollisionResult D_L08_001BFF40;
extern void func_00282CC0(void *, const void *, const void *);
extern int func_002761F8(const void *, const void *, int, void *, void *);
extern int func_00277258(const void *, int, void *, float);
extern void func_00283028(void *, const void *, const void *);
extern void func_00282D30(void *, const void *, float);
extern float func_00282DF0(const void *);
extern float func_00283B98(float, float);
extern void func_0029F338(void *);

void func_L08_0040FAE8(u8 *actor)
{
    float next[4] __attribute__((aligned(16)));
    MotionState *state = *(MotionState **)(actor + 0x68);
    float *position;
    int hit;
    u8 *child;

    func_00282CC0(next, actor + 0x10, state->velocity);
    hit = func_002761F8(actor + 0x10, next, 0, state->owner, 0);
    if (hit == 0) {
        next[2] += 0.3f;
        hit = func_00277258(next, 0, state->owner, 0.3f);
        next[2] -= 0.3f;
    } else {
        qcopy(D_L08_001BFF40.adjusted, D_L08_001BFF40.hit);
        D_L08_001BFF40.adjusted[2] += 0.3f;
    }
    if (hit != 0) {
        qcopy(actor + 0x10, D_L08_001BFF40.adjusted);
        position = (float *)(actor + 0x10);
        *(float *)(actor + 0x18) -= 0.3f;
        func_00283028(state->velocity, state->velocity, D_L08_001BFF40.normal);
        func_00282D30(state->velocity, state->velocity, 0.75f);
        if (func_00282DF0(state->velocity) < 0.01f)
            return;
    } else {
        qcopy(actor + 0x10, next);
        position = (float *)(actor + 0x10);
    }
    state->velocity[2] -= state->gravity;
    *(float *)(actor + 0xF4) = func_00283B98(*(float *)(actor + 0xF4), state->spin);
    child = state->child;
    if (child == 0 || *(s16 *)(child + 0xAA) != 0x326 ||
        child[0x20] == 0xFE || child[0x20] == 0xFD ||
        *(float *)(actor + 0x10) < 2.0f || *(float *)(actor + 0x10) > 1021.0f ||
        *(float *)(actor + 0x14) < 2.0f || *(float *)(actor + 0x14) > 1021.0f ||
        *(float *)(actor + 0x18) < 2.0f || *(float *)(actor + 0x18) > 1021.0f) {
        func_0029F338(actor);
    } else {
        qcopy(child + 0x10, position);
        qcopy(child + 0xF0, actor + 0xF0);
    }
}
