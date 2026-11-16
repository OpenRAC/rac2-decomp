/* func_PAL_L04_0040B8B8, the PAL copy of func_L04_004073E8: the same C with the trail keeps at
   most 25 points instead of 30. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vec73E8;
typedef struct { Vec73E8 vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } Packet73E8;
extern char g_default_quad[] __attribute__((sda));
extern char g_tether_zero_vec[];
extern void set_identity_matrix(void *);
extern void part_compute_ribbon_point_offset(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);

/* Draws the trail behind the object: up to 30 points, each the previous one less the drifting
   offset at +0x00 of the state, and two strips of quads on both sides of them, widening from 0
   at the head to the width at +0x3C, fading out to the tail.

   The spelling of each access picks retail's addresses: `p + i` keeps the frame offset out of
   the index sum, `&p[i + 1]` folds it into the base, and one `side` array (left edge, then right
   edge) shares its base, so the right-edge store joins the points' induction variable. */
void func_PAL_L04_0040B8B8(u8 *obj)
{
    Packet73E8 pkt;
    float cam[12];
    Vec73E8 head;
    Vec73E8 pts[30];
    Vec73E8 side[60];   /* [0, 30): left edge, [30, 60): right edge */
    Vec73E8 off;
    Vec73E8 eye;
    Vec73E8 normal;
    Vec73E8 tangent;
    Vec73E8 d;
    u8 *st = *(u8 **)(obj + 0x68);
    int n;
    int i;
    int j;
    int k;
    float t;
    u32 c;

    if (*(short *)(st + 0x32) < 3)
        return;
    set_identity_matrix(cam);
    head.quad = *(Quad *)g_default_quad;
    n = *(short *)(st + 0x32);
    if (n > 25)
        n = 25;
    pts[0].quad = *(Quad *)(obj + 0x10);
    off.quad = *(Quad *)st;
    for (j = 1; j < n; j++) {
        (pts + j)->quad = pts[j - 1].quad;
        off.f[2] += *(float *)(st + 0x38);
        part_compute_ribbon_point_offset(&eye, &pts[j], &off);
    }
    for (i = 0; i < n - 1; i++) {
        Vec73E8 *l = &side[i];

        t = IntToFloat(n - i) / IntToFloat(n);
        if (t > 1.0f)
            t = 1.0f;
        t *= *(float *)(st + 0x3C);
        if (i == 0)
            t = 0.0f;
        FastVecSub(&d, &pts[i + 1], &pts[i]);
        tangent.quad = d.quad;
        FastVecSub(&d, g_tether_zero_vec, &pts[i]);
        eye.quad = d.quad;
        FastVecCross(&normal, &eye, &tangent);
        vec_scale_to_length(l, &normal, t);
        FastVecSub(&d, &pts[i], l);
        side[i + 30].quad = d.quad;
        add_vectors(&d, l, &pts[i]);
    }
    pkt.texture = GetEffectTextureDescriptor(0x16);
    pkt.mode = 0xFF9000000260ULL;
    pkt.flags = 0x8000000048ULL;
    pkt.primitive = 0;
    pkt.uv[0] = 0.5f;
    pkt.uv[2] = 0.7f;
    pkt.uv[4] = 0.5f;
    pkt.uv[6] = 0.7f;
    for (k = 0; k < n - 2; k++) {
        pkt.uv[1] = IntToFloat(k) / IntToFloat(n);
        pkt.uv[3] = IntToFloat(k) / IntToFloat(n);
        pkt.uv[5] = IntToFloat(k + 1) / IntToFloat(n);
        pkt.uv[7] = IntToFloat(k + 1) / IntToFloat(n);
        c = ((n - k) * 0x60 / n) << 24 | 0x30FF;
        pkt.color[3] = 0x8080;
        pkt.color[1] = 0x8080;
        pkt.color[2] = c;
        pkt.color[0] = c;
        pkt.vertex[0].quad = (pts + k)->quad;
        pkt.vertex[1].quad = (side + k)->quad;
        pkt.vertex[2].quad = (&pts[k + 1])->quad;
        pkt.vertex[3].quad = (&side[k + 1])->quad;
        draw_world_quad(&pkt, cam, 0);
        pkt.vertex[0].quad = (pts + k)->quad;
        pkt.vertex[1].quad = (side + k + 30)->quad;
        pkt.vertex[2].quad = (&pts[k + 1])->quad;
        pkt.vertex[3].quad = (&side[k + 31])->quad;
        draw_world_quad(&pkt, cam, 0);
    }
}
