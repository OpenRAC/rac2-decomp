/* functional: high. Plain floats in place of VU0 macro code, in the assembly's order of operations; the VU divide by zero gives the largest finite float with the sign of the divisor, written out here; retail loops forever for a count of zero, this returns. */
#include "common.h"

extern int D_001B2080;              /* number of segments */

#define SCRATCH_SEGMENTS ((float *)0x70000000)

/* Moves the end points of each segment held in the scratchpad (two 4-float points per segment,
   32 bytes apart) to the places where the segment meets the planes a and b (4 floats each:
   normal xyz and offset w). With d = p2 - p1 and q = 1 / dot(d, a.xyz), p1 moves along d by
   -(dot(p1, a) + a.w) * q and p2 moves along d by -(dot(p2, b) + b.w) * q. */
void func_002E0BA8(float *a, float *b)
{
    float *seg = SCRATCH_SEGMENTS;
    int count = D_001B2080;
    float ax = a[0], ay = a[1], az = a[2], aw = a[3];
    float bx = b[0], by = b[1], bz = b[2], bw = b[3];

    if (count <= 0) {
        return;
    }
    do {
        float dx = seg[4] - seg[0];
        float dy = seg[5] - seg[1];
        float dz = seg[6] - seg[2];
        float den, q, s1, s2, t;
        union {
            float f;
            int i;
        } u;

        den = dx * ax;
        den = den + dy * ay;
        den = den + dz * az;
        if (den == 0.0f) {
            u.f = den;
            u.i = (u.i < 0) ? (int)0xFF7FFFFF : 0x7F7FFFFF;
            q = u.f;
        } else {
            q = 1.0f / den;
        }

        t = seg[0] * ax;
        t = t + seg[1] * ay;
        t = t + seg[2] * az;
        t = t + aw;
        s1 = 0.0f - t;

        t = seg[4] * bx;
        t = t + seg[5] * by;
        t = t + seg[6] * bz;
        t = t + bw;
        s2 = 0.0f - t;

        seg[0] = seg[0] + (dx * s1) * q;
        seg[1] = seg[1] + (dy * s1) * q;
        seg[2] = seg[2] + (dz * s1) * q;
        seg[4] = seg[4] + (dx * s2) * q;
        seg[5] = seg[5] + (dy * s2) * q;
        seg[6] = seg[6] + (dz * s2) * q;
        seg += 8;
        count--;
    } while (count != 0);
}
