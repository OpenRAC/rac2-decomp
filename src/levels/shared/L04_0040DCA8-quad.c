/* func_L04_0040DCA8 (740 bytes, 6 places): builds a textured quad packet (corner vertices,
 * UVs and colours). Own unit: -O2 -G0 -ffunction-sections -frac2-sched-clear-holds-store
 * (config/cflags.txt). The corners are stored in plain order, c0.y..c3.w. In retail the
 * quadword clear issued in a sched1 cycle takes that cycle's store slot, so the h stores reach
 * the packet ahead of c1.w; the switch models that (docs/build/compiler-notes.md). Owner
 * standard of 12 November 2026; forced on for every USA v1.01 unit it changes 5 functions.
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
    /* scratch type shared with func_L30_0041B848, allowed by owner ruling */
    struct { float angles[4]; float rotation[3][4]; } scratch;
    Corner corners[4];
    float c, sn;
    float *out;
    u8 *u;
    int i;
    func_00281DE8(&packet, texture, flags, 128);
    packet.state[0] = 5;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    packet.uv[0].u = 0; packet.uv[0].v = 0; packet.uv[1].u = 0; packet.uv[1].v = 1;
    packet.uv[2].u = 1; packet.uv[2].v = 0; packet.uv[3].u = 1; packet.uv[3].v = 1;
    c = func_00283180(angle);
    sn = func_00283198(angle);
    {
        int k;
        u8 *v = (u8 *)&packet + 0x54;
        for (u = (u8 *)&packet + 0x50, k = 3; k >= 0; k--, u += 8, v += 8) {
            tmp[0] = *(float *)u - 0.5f;
            tmp[1] = *(float *)v - 0.5f;
            *(float *)u = tmp[0] * c - tmp[1] * sn;
            *(float *)v = tmp[0] * sn + tmp[1] * c;
            *(float *)u += 0.5f;
            *(float *)v += 0.5f;
        }
    }
    qcopy(transform[3], position);
    func_00282CF0(transform[0], D_L04_001B9680, transform[3]);
    func_00282F20(transform[0], transform[0], 1.0f);
    func_00282DD8(transform[1], transform[0], D_0018A0E0);
    func_00282F20(transform[1], transform[1], 1.0f);
    func_00282DD8(transform[2], transform[1], transform[0]);
    func_00282D30(scratch.angles, transform[0], size);
    func_00282CC0(transform[3], transform[3], scratch.angles);
    corners[0].bits = 0; corners[1].bits = 0; corners[2].bits = 0; corners[3].bits = 0;
    corners[0].f[1] = -1; corners[0].f[2] = 1 - skew * 0.3f; corners[0].f[3] = 1;
    corners[1].f[1] = -1; corners[1].f[2] = -(1 - skew * 0.3f); corners[1].f[3] = 1;
    corners[2].f[1] = 1; corners[2].f[2] = 1 - skew * 0.3f; corners[2].f[3] = 1;
    corners[3].f[1] = 1; corners[3].f[2] = -(1 - skew * 0.3f); corners[3].f[3] = 1;
    for (i = 0; i < 4; i++) {
        out = packet.vertices[i];
        func_00282D30(out, corners[i].f, scale);
        func_002830C0(out, out, transform);
    }
    func_002FC560(0x47, 0x33001);
    func_00280B90(&packet, 0, 0);
    func_002FC560(0x47, 0x5360b);
}
