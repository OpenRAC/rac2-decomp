/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain the constructor pointer return instead of a false void declaration.
 * The 540-byte source remains a near miss; complete-position and W-component grouping do not recover the decrement slot.
 * Earlier measurements below describe earlier sources or toolchains.
 */
/* Claude Opus 5.5 (xhigh), 2026-10-30. Best rule-compliant result: 540/540 bytes, 0/8 places,
 * us level 02: one instruction differs in two slots. Profile: -O2 -G8 -ffunction-sections
 * -mno-split-addresses, in a unit of its own (L02_002EFB60-g8.c).
 * Still differs: the down-counter decrement fills the first jal's slot (retail: nop there,
 * and the decrement in the slot of the post-copy func_002A7878 call).
 * Why: reorg's forward scan from the first jal (fill_simple_delay_slots) runs through the
 * whole body and takes the decrement unless needed.volatil is set when it reaches it.
 * resource.c assigns that flag at every MEM (res->volatil = MEM_VOLATILE_P), so after the
 * volatile asm only two orders stop the scan: the decrement directly behind the copy, or a
 * volatile read between them. sched1 gives copy, f12 load, decrement, f13 load: the second
 * load waits a cycle for the memory unit, and the decrement takes that slot.
 * This draft's view of D_L02_001A8D78: SDATA gives the GP form, nosda keeps cc1's length at
 * two words so it stays out of the call slot, as in retail.
 * Measured, not landable:
 * - `extern volatile float D_L02_001A8D78 __attribute__((sda));`, read as a scalar, in this
 *   for loop: 8/8 places in us. Not checked in pal/us2. Level 2 reads this record only here,
 *   once each per iteration, and never writes it, so no retail evidence supports volatile.
 * - `do { qcopy(...); } while (0); i--;` in an explicit do/while counter: the LOOP_END note
 *   makes the decrement a barrier, and it reaches retail's slot. 552 bytes: the note also
 *   ends cse1's block, so 0.0f/1.0f stop being shared and -gravity is hoisted. Non-empty
 *   wrappers are an open maintainer question (MATCHING-BLOCKERS.md), so not pursued.
 * Reopen with: a non-volatile reason the decrement directly follows the copy (the loads
 * must not be ready in the copy's next cycle), or evidence that this record is volatile.
 */

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern int D_L02_001A8D68 __attribute__((sda));
extern float D_L02_001A8D78[] SDATA(D_L02_001A8D78) __attribute__((nosda));
extern int D_L02_001A8D58 __attribute__((sda));
extern int D_L02_001A8D50 __attribute__((sda));
extern float D_L02_001A8D7C __attribute__((nosda));
extern int D_L02_001A8D5C __attribute__((nosda));
extern int D_L02_001A8D60 __attribute__((nosda));
extern int D_L02_001A8D64 __attribute__((nosda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

void func_L02_002EFB60(void *owner, void *from, void *to, int count, int *colour, float speed) {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    float gravity = speed * 0.00027777778f;
    float brightness, t;
    int r, g, b, first, second, i;
    int *rgb = &D_L02_001A8D68;
    if (colour) rgb = colour;
    for (i = 0; i < count; i++) {
        brightness = func_002A7878(0.7f, 1.3f);
        r = func_00283CF0((float)rgb[0] * brightness);
        g = func_00283CF0((float)rgb[1] * brightness);
        b = func_00283CF0((float)rgb[2] * brightness);
        func_00282D08(&direction, from, to, func_002A7878(0.0f, 1.0f));
        qcopy(&position, &direction);
        position.f[3] = func_002A7878(D_L02_001A8D78[0], D_L02_001A8D7C);
        func_00282C88(&velocity);
        velocity.f[2] = -gravity * (float)(r + g + b);
        func_00282CC0(&velocity, &velocity, &direction);
        velocity.f[3] = position.f[3];
        t = func_002A7878(0.0f, 1.0f);
        first = func_00283D38(D_L02_001A8D58, D_L02_001A8D5C, t);
        t = func_002A7878(0.0f, 1.0f);
        second = func_00283D38(D_L02_001A8D60, D_L02_001A8D64, t);
        func_002BAA28(owner, &position, &velocity, first, second, r, g, b, D_L02_001A8D50);
    }
}
