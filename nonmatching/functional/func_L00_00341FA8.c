/* functional: high. SAME on 3 calls (level 12's copy of the shared routine). The matching draft as it is: seven instructions are scheduled differently. Unrun blocks read against retail: the empty path (func_00282C88 on out, return 0), the no-wrap skip of the previous segment, and the whole next-segment branch (func_L00_00341D08 into the temporary, c.lt.s against the previous distance, copy to out, *index, offset from the path point to out). */
/* func_L00_00341FA8: find the path segment nearest a point and the projected position on it. */
/* GPT-6.1 Sol, high effort; measured 2026-10-29 (task v0924).
 * Profile: default game -O2 -G0 -ffunction-sections; USA v1.01.
 * Best check.py: 924/924 bytes, 0/23 places; seven instructions differ.
 * First difference +0x288: saving the projection distance and preparing a/b
 * addresses occur in a different order. At +0x298..+0x2A8 the two vector loads
 * and stores are scheduled differently. All remaining instructions agree.
 * Requires common.h for the approved qcopy helper; declarations follow below.
 *
 * Improvements over the retained 912-byte draft: the first/final transfers use
 * qcopy; point indexing uses the 16-byte record index (node + 1), avoiding an
 * extra saved path-point base. A separate searchRange gives the retail FPRs.
 * A two-step previous-index calculation and ABI-preserving float/integer
 * interleaving on func_L00_00341820 recover the other scheduling differences.
 * The interleaving preserves five GPR arguments, one float argument and returns.
 *
 * Plain point-before-output copies and explicit quadword load temporaries
 * (both load orders), plus a separate projection-distance local, tie at seven
 * remaining instructions. -g, aligned float-array locals and disabling strength
 * reduction supplied no remedy. Stop at the source tie; reopen with evidence
 * for the original projection/offset copy and argument-expression lifetimes.
 * PAL/US2 and linked builds were not run; this function remains assembly.
 */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { int count; int reserved[3]; Vector points[0]; } Path;
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern float func_L00_00341A88(void *, void *, float);
extern int func_L00_00341820(const Path *, Vector *, int *, float *, float, int);
extern int func_L00_003417B8(const int *, int, int, int);
extern float func_L00_00341D08(Vector *, const Vector *, const Vector *, const Vector *, float);
extern void func_00282C88(Quadword *);



/* Find the nearby path segment and the projected position on that segment. */
int func_L00_00341FA8(const Path *path, const Vector *point, Vector *out,
                     int *index, float *offset, int wrap,
                     float range, float step, float height) {
    Vector current, a, b, candidate;
    int scanIndex = 0;
    float scanOffset = 0.0f;
    int left, right;
    int nearestIndex;
    float nearestOffset;
    float nearestDistance, distance, searchRange;
    int finished, previous, next;
    qcopy(&current, &((const Vector *)path)[1]);
    a.q = point->q;
    nearestIndex = 0;
    nearestOffset = 0.0f;
    nearestDistance = func_L00_00341A88(&current, &a, height);
    if (path->count == 0) {
        func_00282C88(&out->q);
        return 0;
    }
    searchRange = step + range;
    do {
        finished = func_L00_00341820(path, &current, &scanIndex, &scanOffset, step, wrap);
        a.q = point->q;
        distance = func_L00_00341A88(&current, &a, height);
        if (distance < nearestDistance) {
            nearestIndex = scanIndex;
            nearestDistance = distance;
            nearestOffset = scanOffset;
        }
    } while (!finished);
    if (searchRange < nearestDistance) return 0;
    left = nearestIndex;
    scanOffset = nearestOffset;
    func_L00_00341820(path, &current, &left, &scanOffset, -step, wrap);
    right = nearestIndex;
    scanOffset = nearestOffset;
    func_L00_00341820(path, &current, &right, &scanOffset, step, wrap);
    right = func_L00_003417B8(&path->count, right, 1, wrap);
    scanIndex = left;
    nearestDistance = 1000000000.0f;
    for (;;) {
        a.q = ((const Vector *)path)[scanIndex + 1].q;
        b.q = point->q;
        distance = func_L00_00341A88(&a, &b, height);
        if (distance < nearestDistance) {
            nearestIndex = scanIndex;
            nearestDistance = distance;
        }
        if (scanIndex == right) break;
        scanIndex = (scanIndex + 1) % path->count;
    }
    nearestDistance = 1000000000.0f;
    if (nearestIndex > 0 || wrap) {
        previous = path->count - 1;
        previous = (nearestIndex + previous) % path->count;
        nearestDistance = func_L00_00341D08(out, point, &((const Vector *)path)[previous + 1], &((const Vector *)path)[nearestIndex + 1], height);
        *index = previous;
        b.q = out->q;
        a.q = ((const Vector *)path)[previous + 1].q;
        *offset = func_L00_00341A88(&a, &b, 0.0f);
    }
    if (nearestIndex < path->count - 1 || wrap) {
        next = (nearestIndex + 1) % path->count;
        distance = func_L00_00341D08(&a, point, &((const Vector *)path)[nearestIndex + 1], &((const Vector *)path)[next + 1], height);
        if (distance < nearestDistance) {
            qcopy(out, &a);
            *index = nearestIndex;
            b.q = ((const Vector *)path)[nearestIndex + 1].q;
            candidate.q = out->q;
            *offset = func_L00_00341A88(&b, &candidate, 0.0f);
        }
    }
    return 1;
}
