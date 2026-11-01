#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; } Hero;
extern char D_00189E20[];
typedef struct {
    float pos[4];
    float vel[4];
    char pad20[0x30];
    float aim[4];
    char pad60[0x20];
    float size;
    char pad84[0x10];
    float near[4];
} Cam;
typedef struct {
    float base[4];
    float step[4];
    float mid[4];
    char pad30[0x20];
    float look[4];
    float target[4];
    float o70[4];
    float rate;
    char pad84[0x24];
    float a0;
    char padB4[0x20];
    short o;
} Dummy;
extern float func_002702C8(void *, float, float, float, float, float);
extern int func_002761F8(void *, void *, int, int, int);
extern int func_00282978(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern float func_00282DF0(void *);
extern void func_00334710(void *, void *);
extern void func_L00_00420C38(void *);
extern void func_L00_004212B8(void *, void *);
extern void func_L00_00421B50(void *, void *);
extern void func_L00_00424A50(float, float);
extern float D_L00_001B14D0 __attribute__((sda));
extern int D_L00_001B184C MACRO_ADDR;
extern char *D_L00_001B8E10[];
extern char D_L00_001B8E20[];
extern char D_L00_001BF220[];
#define HERO ((Hero *)D_00189E20)
void func_L00_00421C50(char *moby)
{
    float out[4], a[4], b[4], c[4], d[4], e[4], f[4], g[4], h[4], i[4];
    float v0[4];
    char *p = *(char **)(moby + 0x70);
    char *s = p + 0x60;
    char *q = p + 0x160;
    char *t = p + 0x70;
    char *u;
    char *cam = D_L00_001B8E20;
    char *pi;
    char *vp;
    float dist, scale, r, r2, dd;
    func_00334710(moby, a);
    func_L00_00420C38(moby);
    func_L00_004212B8(moby, out);
    qcopy(p + 0x70, out);
    qcopy(b, s);
    u = p + 0xC0;
    dist = func_00282DB0(cam + 0x30, u);
    func_00282D30(c, cam + 0x30, dist);
    func_00282CF0(d, u, c);
    *(float *)(s + 0xF0) = func_00282E48(c, t);
    c[0] = func_002702C8(p + 0xE0, c[0], *(float *)(s + 0x10), *(float *)(s + 0xE4), *(float *)(s + 0xE8), 0.0f);
    c[1] = func_002702C8(p + 0xE4, c[1], *(float *)(s + 0x14), *(float *)(s + 0xE4), *(float *)(s + 0xE8), 0.0f);
    c[2] = func_002702C8(p + 0xE8, c[2], *(float *)(s + 0x18), *(float *)(s + 0xE4), *(float *)(s + 0xE8), 0.0f);
    d[0] = func_002702C8(p + 0xD0, d[0], *(float *)(s + 0x0), *(float *)(s + 0xDC), *(float *)(s + 0xE0), 0.0f);
    d[1] = func_002702C8(p + 0xD4, d[1], *(float *)(s + 0x4), *(float *)(s + 0xDC), *(float *)(s + 0xE0), 0.0f);
    d[2] = func_002702C8(p + 0xD8, d[2], *(float *)(s + 0x8), *(float *)(s + 0xDC), *(float *)(s + 0xE0), 0.0f);
    func_00282CC0(s, s, t);
    func_00282CC0(u, d, c);
    func_00282D30(e, cam + 0x20, *(float *)(s + 0xB0));
    if (*(u8 *)(s + 0xD6)) {
        *(short *)(s + 0xD8) += 1;
        if (*(short *)(s + 0xEC) < *(short *)(s + 0xD8))
            *(short *)(s + 0xD8) = *(short *)(s + 0xEC);
        r = func_00283CE0(*(short *)(s + 0xD8));
        r = r / func_00283CE0(*(short *)(s + 0xEC));
        func_00282D08(f, s, u, r);
        func_00282CC0(p + 0xA0, e, f);
    } else {
        func_00282978(p + 0x138);
        if (*(short *)(s + 0xD8) < 0)
            *(short *)(s + 0xD8) = 0;
        r = func_00283CE0(*(short *)(s + 0xD8));
        r = r / func_00283CE0(*(short *)(s + 0xEC));
        func_00282D08(f, s, u, r);
        func_00282CC0(p + 0xA0, e, f);
    }
    func_L00_00421B50(moby, e);
    if (HERO->b[0x22B4] == 2)
        func_00282D30(e, cam + 0x20, 3.0f);
    else if (HERO->b[0x22B4] == 1)
        func_00282D30(e, cam + 0x20, 0.4f);
    else if (HERO->i[0x8A7] == 0x11)
        qzero(e);
    else
        func_00282D30(e, cam + 0x20, 0.5f);
    func_00282CC0(f, a, e);
    func_00282D30(e, cam + 0x20, *(float *)(q + 0x30));
    func_00282CC0(s + 0x50, e, s);
    {
        char *o = *(char **)(D_L00_001B8E10[0] + 0x70);
        scale = D_L00_001B14D0 + *(float *)(o + 0x234) * *(float *)(o + 0x22C) * (*(float *)(o + 0x230) - 1.0f);
    }
    func_00282D30(g, cam + 0x20, 20.0f);
    func_00282CC0(g, f, g);
    if (func_002761F8(f, g, D_L00_001B184C, HERO->i[0x8A4], 0))
        qcopy(h, D_L00_001BF220);
    else
        qcopy(h, g);
    func_00282D30(g, cam + 0x20, 20.0f);
    func_00282CF0(g, f, g);
    if (func_002761F8(f, g, D_L00_001B184C, HERO->i[0x8A4], 0))
        qcopy(g, D_L00_001BF220);
        func_00282CF0(i, g, h);
    if (func_00282DF0(i) < 2.0f * scale) {
        func_00282CC0(v0, h, g);
        func_00282D30(v0, v0, 0.5f);
        qcopy(s + 0x50, v0);
        func_00282CF0(i, v0, s);
        func_L00_00424A50(func_00282DB0(i, cam + 0x20), 0.006f);
        return;
    }
    func_00282CF0(i, h, s);
    dd = func_00282DF0(i);
    r2 = *(float *)(q + 0x30);
    if (dd <= r2 + scale) {
        func_00282D30(v0, cam + 0x20, scale);
        func_00282CF0(v0, h, v0);
        qcopy(s + 0x50, v0);
        func_00282CF0(i, v0, s);
        func_L00_00424A50(func_00282DB0(i, cam + 0x20), 0.006f);
        return;
    }
    dd = func_00282DB0(s, cam + 0x30);
    if (func_00282DB0(g, cam + 0x30) < dd)
        qcopy(g, s);
    func_00282D30(e, cam + 0x20, r2);
    func_00282CC0(s + 0x50, e, g);
}
