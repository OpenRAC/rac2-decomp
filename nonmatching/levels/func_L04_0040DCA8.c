/* 3 November 2026: owning vector/UV storage; still not matching.
 * Default game -O2 -G0 -ffunction-sections. US, PAL and US2 each:
 * 728/740 bytes, 0/6 places. This supersedes the historical 740-byte draft.
 * Corners use complete quadword/float unions, with each input and output
 * vertex addressed within its own array member. The copied matrix row is
 * explicitly 16-byte aligned. The unused rotation array is removed.
 * UVs are four owning pairs: the old second float cursor advanced to uv+9
 * after its last use, beyond the eight-float allocation. The pair cursor
 * instead ends at the array's one-past position. Union vertices and an
 * indexed vertex loop alone preserved the old five store-order differences;
 * the defined paired UV accesses change the body to 728 bytes.
 * Do not recover the historical size by restoring the invalid cursor or
 * crossing a float subarray. Reopen on the actual UV-loop/corner-store
 * dependence and scheduling, with complete storage and truthful interfaces.
 */
/* func_L04_0040DCA8 (740 bytes, 6 places). Tier opus-1, 28 October 2026.
 * Unit: default flags (-O2 -G0 -ffunction-sections), in L04_00402D90.c or a
 * file of its own. Best check.py: 740/740 bytes, 0/6 places, the corner
 * stores at +0x224..+0x23c in another order (5 words): retail stores
 * c2.z, c0.z, c1.w, c3.z, c1.z, c2.y; this C stores c1.w, c2.z, c0.z, c2.y,
 * c1.z, c3.z. Everything else matches (frame, allocation, the por/sq clears).
 * Retail's tail is exactly this C's statement order: sched2 keeps sched1's
 * order for ready ties, and sched1 puts c1.w (1.0, ready since the clears)
 * in the memory slot at t30 because h = 1-skew*0.3 is ready only at t31
 * (0.3 load t23, mul t25, sub t28). With the R5900 model (one memory unit,
 * two issues, TImode const-0 stores typed alu before reload) the memory unit
 * has one idle slot (t25) between the call and t31; retail's order needs a
 * second one, so no ordering of these stores reproduces it. Probably the
 * original RTL had one more pre-reload insn there (a coalesced copy, or
 * register-source clears that use the memory unit). Tried without gain:
 * chained/pointer/variable forms of the field stores, a TImode zero
 * variable (constant-propagated), an aggregate initializer (stores every
 * element, no TImode clear), -fno-schedule-insns (breaks the earlier blocks).
 * Declarations: below.
 */
#include "common.h"
typedef unsigned int B781AimQuad __attribute__((mode(TI)));
typedef union { B781AimQuad bits; float f[4]; } Corner;
extern void func_00282CF0(void *,void *,void *), func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *), func_00282D30(void *,void *,float), func_00282CC0(void *,void *,void *);
typedef struct { float u, v; } UVPair;
typedef struct { float vertices[4][4]; int colors[4]; UVPair uv[4]; long state[4]; } B971Packet;
extern void func_00281DE8(void *, int, int, int);
extern float func_00283180(float), func_00283198(float);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(int, unsigned long long);
extern void func_00280B90(void *, int, int);
extern char D_L04_001B9680[], D_0018A0E0[];
void func_L04_0040DCA8(B781AimQuad *position, int texture, int color, int flags, float scale, float size, float angle, float skew)
{
    B971Packet packet;
    float tmp[2];
    float transform[4][4] __attribute__((aligned(16)));
    float offset[4];
    Corner corners[4];
    float c, sn;
    float *out;
    UVPair *uv;
    int i;
    func_00281DE8(&packet, texture, flags, 128);
    packet.state[0] = 5;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    packet.uv[0].u = 0; packet.uv[0].v = 0; packet.uv[1].u = 0; packet.uv[1].v = 1;
    packet.uv[2].u = 1; packet.uv[2].v = 0; packet.uv[3].u = 1; packet.uv[3].v = 1;
    c = func_00283180(angle);
    sn = func_00283198(angle);
    for (i = 3, uv = packet.uv; i >= 0; i--, uv++) {
        tmp[0] = uv->u - 0.5f;
        tmp[1] = uv->v - 0.5f;
        uv->u = tmp[0] * c - tmp[1] * sn;
        uv->v = tmp[0] * sn + tmp[1] * c;
        uv->u += 0.5f;
        uv->v += 0.5f;
    }
    qcopy(transform[3], position);
    func_00282CF0(transform[0], D_L04_001B9680, transform[3]);
    func_00282F20(transform[0], transform[0], 1.0f);
    func_00282DD8(transform[1], transform[0], D_0018A0E0);
    func_00282F20(transform[1], transform[1], 1.0f);
    func_00282DD8(transform[2], transform[1], transform[0]);
    func_00282D30(offset, transform[0], size);
    func_00282CC0(transform[3], transform[3], offset);
    corners[0].bits = 0; corners[1].bits = 0; corners[2].bits = 0; corners[3].bits = 0;
    corners[0].f[1] = -1; corners[1].f[1] = -1;
    corners[0].f[3] = 1;
    corners[2].f[2] = 1 - skew * 0.3f; corners[0].f[2] = 1 - skew * 0.3f;
    corners[1].f[3] = 1;
    corners[3].f[2] = -(1 - skew * 0.3f); corners[1].f[2] = -(1 - skew * 0.3f);
    corners[2].f[1] = 1; corners[2].f[3] = 1; corners[3].f[1] = 1; corners[3].f[3] = 1;
    for (i = 0; i < 4; i++) {
        out = packet.vertices[i];
        func_00282D30(out, corners[i].f, scale);
        func_002830C0(out, out, transform);
    }
    func_002FC560(0x47, 0x33001);
    func_00280B90(&packet, 0, 0);
    func_002FC560(0x47, 0x5360b);
}
