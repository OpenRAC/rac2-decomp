#include "names.h"
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
extern void FastVecSub(void *,void *,void *), vec_scale_to_length(void *,void *,float);
extern void FastVecCross(void *,void *,void *), FastVecScale(void *,void *,float), FastVecAdd(void *,void *,void *);
typedef struct { float u, v; } UVPair;
typedef struct { float vertices[4][4]; int colors[4]; UVPair uv[4]; long state[4]; } B971Packet;
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(int, unsigned long long);
extern void draw_world_quad(void *, int, int);
extern char D_L04_001B9680[], D_0018A0E0[];
/* Draws a flat glowing sprite that faces the camera at a position. It can be turned by an angle and squashed. */
void gfx_l04_draw_billboard_sprite(B781AimQuad *position, int texture, int color, int flags, float scale, float size, float angle, float skew)
{
    B971Packet packet;
    float tmp[2];
    float transform[4][4] __attribute__((aligned(16)));
    /* scratch type shared with func_L30_0041B848, allowed by owner ruling */
    struct { float angles[4]; float rotation[3][4]; } scratch;
    Corner corners[4];
    float cosAngle, sinAngle;
    float *out;
    u8 *uPtr;
    int i;
    gfx_init_quad_packet_state(&packet, texture, flags, 128);
    packet.state[0] = 5;
    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = color;
    packet.uv[0].u = 0; packet.uv[0].v = 0; packet.uv[1].u = 0; packet.uv[1].v = 1;
    packet.uv[2].u = 1; packet.uv[2].v = 0; packet.uv[3].u = 1; packet.uv[3].v = 1;
    cosAngle = math_fast_sin_or_cos_a(angle);
    sinAngle = math_fast_sin_or_cos_b(angle);
    {
        int k;
        u8 *vPtr = (u8 *)&packet + 0x54;
        for (uPtr = (u8 *)&packet + 0x50, k = 3; k >= 0; k--, uPtr += 8, vPtr += 8) {
            tmp[0] = *(float *)uPtr - 0.5f;
            tmp[1] = *(float *)vPtr - 0.5f;
            *(float *)uPtr = tmp[0] * cosAngle - tmp[1] * sinAngle;
            *(float *)vPtr = tmp[0] * sinAngle + tmp[1] * cosAngle;
            *(float *)uPtr += 0.5f;
            *(float *)vPtr += 0.5f;
        }
    }
    qcopy(transform[3], position);
    FastVecSub(transform[0], D_L04_001B9680, transform[3]);
    vec_scale_to_length(transform[0], transform[0], 1.0f);
    FastVecCross(transform[1], transform[0], D_0018A0E0);
    vec_scale_to_length(transform[1], transform[1], 1.0f);
    FastVecCross(transform[2], transform[1], transform[0]);
    FastVecScale(scratch.angles, transform[0], size);
    FastVecAdd(transform[3], transform[3], scratch.angles);
    corners[0].bits = 0; corners[1].bits = 0; corners[2].bits = 0; corners[3].bits = 0;
    corners[0].f[1] = -1; corners[0].f[2] = 1 - skew * 0.3f; corners[0].f[3] = 1;
    corners[1].f[1] = -1; corners[1].f[2] = -(1 - skew * 0.3f); corners[1].f[3] = 1;
    corners[2].f[1] = 1; corners[2].f[2] = 1 - skew * 0.3f; corners[2].f[3] = 1;
    corners[3].f[1] = 1; corners[3].f[2] = -(1 - skew * 0.3f); corners[3].f[3] = 1;
    for (i = 0; i < 4; i++) {
        out = packet.vertices[i];
        FastVecScale(out, corners[i].f, scale);
        transform_vector(out, out, transform);
    }
    VU1_addGSregister(0x47, 0x33001);
    draw_world_quad(&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360b);
}
