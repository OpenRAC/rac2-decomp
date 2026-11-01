#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vec73E8;
typedef struct { Vec73E8 vertex[4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } Packet73E8;
extern char D_001A8F20[] __attribute__((sda));
extern char D_L04_001B9680[];
extern void func_00283388(void *);
extern void func_L04_0030EDE0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern u64 func_0027C878(int);
extern void func_00280B90(void *, void *, int);

/* Draws the trail behind the object: up to 30 points, each the previous one less the drifting
   offset at +0x00 of the state, and two strips of quads on both sides of them, widening from 0
   at the head to the width at +0x3C, fading out to the tail.

   The spelling of each access picks retail's addresses: `p + i` keeps the frame offset out of
   the index sum, `&p[i + 1]` folds it into the base, and one `side` array (left edge, then right
   edge) shares its base, so the right-edge store joins the points' induction variable. */
void func_L04_004073E8(u8 *obj)
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
    func_00283388(cam);
    head.quad = *(Quad *)D_001A8F20;
    n = *(short *)(st + 0x32);
    if (n > 30)
        n = 30;
    pts[0].quad = *(Quad *)(obj + 0x10);
    off.quad = *(Quad *)st;
    for (j = 1; j < n; j++) {
        (pts + j)->quad = pts[j - 1].quad;
        off.f[2] += *(float *)(st + 0x38);
        func_L04_0030EDE0(&eye, &pts[j], &off);
    }
    for (i = 0; i < n - 1; i++) {
        Vec73E8 *l = &side[i];

        t = func_00283CE0(n - i) / func_00283CE0(n);
        if (t > 1.0f)
            t = 1.0f;
        t *= *(float *)(st + 0x3C);
        if (i == 0)
            t = 0.0f;
        func_00282CF0(&d, &pts[i + 1], &pts[i]);
        tangent.quad = d.quad;
        func_00282CF0(&d, D_L04_001B9680, &pts[i]);
        eye.quad = d.quad;
        func_00282DD8(&normal, &eye, &tangent);
        func_00282F20(l, &normal, t);
        func_00282CF0(&d, &pts[i], l);
        side[i + 30].quad = d.quad;
        func_00282CD8(&d, l, &pts[i]);
    }
    pkt.texture = func_0027C878(0x16);
    pkt.mode = 0xFF9000000260ULL;
    pkt.flags = 0x8000000048ULL;
    pkt.primitive = 0;
    pkt.uv[0] = 0.5f;
    pkt.uv[2] = 0.7f;
    pkt.uv[4] = 0.5f;
    pkt.uv[6] = 0.7f;
    for (k = 0; k < n - 2; k++) {
        pkt.uv[1] = func_00283CE0(k) / func_00283CE0(n);
        pkt.uv[3] = func_00283CE0(k) / func_00283CE0(n);
        pkt.uv[5] = func_00283CE0(k + 1) / func_00283CE0(n);
        pkt.uv[7] = func_00283CE0(k + 1) / func_00283CE0(n);
        c = ((n - k) * 0x60 / n) << 24 | 0x30FF;
        pkt.color[3] = 0x8080;
        pkt.color[1] = 0x8080;
        pkt.color[2] = c;
        pkt.color[0] = c;
        pkt.vertex[0].quad = (pts + k)->quad;
        pkt.vertex[1].quad = (side + k)->quad;
        pkt.vertex[2].quad = (&pts[k + 1])->quad;
        pkt.vertex[3].quad = (&side[k + 1])->quad;
        func_00280B90(&pkt, cam, 0);
        pkt.vertex[0].quad = (pts + k)->quad;
        pkt.vertex[1].quad = (side + k + 30)->quad;
        pkt.vertex[2].quad = (&pts[k + 1])->quad;
        pkt.vertex[3].quad = (&side[k + 31])->quad;
        func_00280B90(&pkt, cam, 0);
    }
}
