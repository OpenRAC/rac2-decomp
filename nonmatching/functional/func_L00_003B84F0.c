/* functional: high. The near-miss draft (2404/2404 bytes; register allocation and scheduling differ) read against all 601 retail instructions of level 00's copy: every call and argument, the gp/lui data (0x1AFCE0..0x1AFD78 tunables, 0x1B19C8 the frame counter, 0x138180+0x1A0 the cheat/option word, hero 0x189E20), every float constant (1/60 0x3C888889, 0.5, pi 0x40490FDB, 0x3C8EFA36, 0x3F7FFF58, 0x3C23D70A) and every compare's sense and operand order agree. Changed from the draft: the 64-bit GS words and func_0027C878's result typed long / unsigned long (retail builds them with dsll/dsll32 and stores them with sd), and func_00280B90 declared as the port's host routine defines it (host/render.c: gaddr, int, int; the packet passed as a 32-bit game address). */
/* func_L00_003B84F0 (shared, 27 places): draws a tractor/grind beam from the controller at *0x1AFD78
 * (+0 target moby, +0x20 origin, +0x30 direction, +0x40 phase, +0x44 current length). The length grows
 * toward the distance to the target (or 0x1AFCF4) while the beam is on (option word & hero+0x1230, hero
 * +0x340 set, no +0x34E/+0x1E0 and 0x1AFCE0 clear) and shrinks otherwise; reaching the target starts the
 * hero's grab (hero+0x1E0 = 30, func_L00_003294F0, func_002DF3F8). The phase scrolls by 0x1AFD18/60. Then
 * from the phase to the length in 0x1AFCF8 steps it draws a cross of two quads per step, its width eased by
 * a sine envelope, its colour cycling through three sines and its alpha alternating between two sets.
 * From the near-miss draft nonmatching/levels/func_L00_003B84F0.c. */
#include "common.h"

typedef int Quad_L00_003B84F0 __attribute__((mode(TI)));
typedef union {
    Quad_L00_003B84F0 bits;
    float f[4];
} Vec4_L00_003B84F0;

typedef struct {
    unsigned char pad0[0x10];
    Vec4_L00_003B84F0 pos;
    unsigned char pad20[0x11];
    unsigned char f31;
} Moby_L00_003B84F0;

typedef struct {
    Moby_L00_003B84F0 *moby;
    unsigned char pad4[0x1C];
    Vec4_L00_003B84F0 pos;
    Vec4_L00_003B84F0 dir;
    float f40;
    float f44;
} Ctl_L00_003B84F0;

typedef struct {
    Vec4_L00_003B84F0 m[4];
    int col[4];
    float uv[8];
    unsigned long q70;
    unsigned long q78;
    unsigned long q80;
    unsigned long q88;
} Packet_L00_003B84F0;

typedef struct {
    unsigned char pad0[0x80];
    Vec4_L00_003B84F0 v80;
    Vec4_L00_003B84F0 v90;
    unsigned char padA0[0x1E0 - 0xA0];
    short f1E0;
    unsigned char pad1E2[0x340 - 0x1E2];
    int f340;
    unsigned char pad344[0x34E - 0x344];
    short f34E;
    unsigned char pad350[0x1230 - 0x350];
    int f1230;
    unsigned char pad1234[0x2294 - 0x1234];
    int f2294;
    unsigned char pad2298[0x22B4 - 0x2298];
    unsigned char f22B4;
} Hero_L00_003B84F0;

extern Hero_L00_003B84F0 D_00189E20;
extern int D_00138180[];

extern int D_L00_001AFCE0 __attribute__((sda));
extern float D_L00_001AFCF4 __attribute__((sda));
extern float D_L00_001AFCF8 __attribute__((sda));
extern int D_L00_001AFCFC __attribute__((sda));
extern int D_L00_001AFD00 __attribute__((sda));
extern int D_L00_001AFD04 __attribute__((sda));
extern int D_L00_001AFD08 __attribute__((sda));
extern int D_L00_001AFD0C __attribute__((sda));
extern int D_L00_001AFD10 __attribute__((sda));
extern int D_L00_001AFD14 __attribute__((sda));
extern float D_L00_001AFD18 __attribute__((sda));
extern float D_L00_001AFD1C __attribute__((sda));
extern float D_L00_001AFD20 __attribute__((sda));
extern float D_L00_001AFD24 __attribute__((sda));
extern float D_L00_001AFD28 __attribute__((sda));
extern float D_L00_001AFD2C __attribute__((sda));
extern float D_L00_001AFD30 __attribute__((sda));
extern float D_L00_001AFD34 __attribute__((sda));
extern float D_L00_001AFD38 __attribute__((sda));
extern float D_L00_001AFD3C __attribute__((sda));
extern float D_L00_001AFD40 __attribute__((sda));
extern float D_L00_001AFD44 __attribute__((sda));
extern float D_L00_001AFD48 __attribute__((sda));
extern float D_L00_001AFD4C __attribute__((sda));
extern float D_L00_001AFD50 __attribute__((sda));
extern float D_L00_001AFD54 __attribute__((sda));
extern float D_L00_001AFD58 __attribute__((sda));
extern float D_L00_001AFD5C __attribute__((sda));
extern float D_L00_001AFD60 __attribute__((sda));
extern float D_L00_001AFD64 __attribute__((sda));
extern float D_L00_001AFD68 __attribute__((sda));
extern float D_L00_001AFD6C __attribute__((sda));
extern float D_L00_001AFD70 __attribute__((sda));
extern float D_L00_001AFD74 __attribute__((sda));
extern Ctl_L00_003B84F0 *D_L00_001AFD78 __attribute__((sda));
extern int D_L00_001B19C8;

extern unsigned long func_0027C878(int);
extern float func_00282E80(void *, void *);
extern void func_L00_003294F0(void *, int);
extern void func_002DF3F8(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_002A7798(float);
extern float func_L00_0031A6C8(float, int);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it */

void func_L00_003B84F0(Moby_L00_003B84F0 *obj)
{
    Packet_L00_003B84F0 pkt;
    Vec4_L00_003B84F0 b;
    Vec4_L00_003B84F0 a;
    Vec4_L00_003B84F0 c;
    Vec4_L00_003B84F0 vx;
    Vec4_L00_003B84F0 vy;
    Vec4_L00_003B84F0 vz;
    Vec4_L00_003B84F0 p;
    Ctl_L00_003B84F0 *ctl;
    unsigned long alpha0;
    unsigned long alpha1;
    int on;
    int flag;
    int col;
    int alpha;
    int r;
    int g;
    int bl;
    float dist;
    float x;
    float t;
    float w;
    float u;
    float s;
    float phase;
    float inset;
    float range;

    ctl = D_L00_001AFD78;
    if (ctl == 0) {
        return;
    }
    pkt.q78 = func_0027C878(D_L00_001AFD14);
    { long v; v = (long)D_L00_001AFD00 | ((long)D_L00_001AFCFC << 2); v |= (long)D_L00_001AFD04 << 4; v |= (long)D_L00_001AFD08 << 6; v |= (long)D_L00_001AFD0C << 32; alpha1 = v; }
    { long v; v = (long)D_L00_001AFCFC | ((long)D_L00_001AFD00 << 2); v |= (long)D_L00_001AFD04 << 4; v |= (long)D_L00_001AFD08 << 6; v |= (long)D_L00_001AFD0C << 32; alpha0 = v; }
    pkt.col[3] = D_L00_001AFD10;
    pkt.col[2] = D_L00_001AFD10;
    pkt.col[1] = D_L00_001AFD10;
    on = (D_00138180[0x1A0 / 4] & D_00189E20.f1230) != 0;
    pkt.col[0] = D_L00_001AFD10;
    pkt.q88 = alpha0;
    pkt.uv[0] = D_L00_001AFD34;
    pkt.uv[4] = D_L00_001AFD34;
    pkt.q80 = 0xFF9000000260UL;
    pkt.uv[2] = 1.0f - D_L00_001AFD34;
    pkt.uv[6] = 1.0f - D_L00_001AFD34;
    pkt.uv[1] = D_L00_001AFD34;
    pkt.q70 = 4;
    pkt.uv[3] = D_L00_001AFD34;
    pkt.uv[5] = 1.0f - D_L00_001AFD34;
    pkt.uv[7] = 1.0f - D_L00_001AFD34;

    dist = D_L00_001AFCF4;
    if (D_00189E20.f340 == 0 || D_00189E20.f34E != 0 || D_L00_001AFCE0 != 0 || D_00189E20.f1E0 != 0) {
        on = 0;
    }
    if (ctl->moby != 0 && ctl->moby->f31 != 0) {
        dist = func_00282E80(&obj->pos, &ctl->moby->pos);
    }
    if (ctl->f44 < dist - D_L00_001AFD1C * 0.016666668f && on != 0) {
        ctl->f44 = ctl->f44 + D_L00_001AFD1C * 0.016666668f;
    } else if (ctl->f44 > dist + D_L00_001AFD20 * 0.016666668f || on == 0) {
        ctl->f44 = ctl->f44 - D_L00_001AFD20 * 0.016666668f;
        if (ctl->f44 < 0.0f) {
            ctl->f44 = 0.0f;
        }
    } else {
        ctl->f44 = dist;
    }
    if (on != 0 && D_L00_001AFCE0 == 0 && D_00189E20.f1E0 == 0 && ctl->f44 > dist - 0.5f && ctl->moby != 0) {
        ctl->f44 = 0.0f;
        ctl->f40 = 0.0f;
        D_00189E20.f1E0 = 30;
        func_L00_003294F0(ctl->moby, 1);
        if (D_00189E20.f22B4 == 0) {
            func_002DF3F8(&D_00189E20.v80, &D_00189E20.v90);
        }
    }
    if (ctl->f44 > dist) {
        ctl->f44 = dist;
    }
    ctl->f40 = ctl->f40 + D_L00_001AFD18 * 0.016666668f;
    if (ctl->f40 > D_L00_001AFCF8 + D_L00_001AFCF8) {
        ctl->f40 = ctl->f40 - (D_L00_001AFCF8 + D_L00_001AFCF8);
    }
    a.bits = 0;
    a.f[0] = 1.0f;
    func_00282F20(&b, &ctl->dir, -1.0f);
    b.f[2] = -b.f[2];
    flag = 0;
    func_00282DD8(&c, &b, &a);
    func_00282F20(&c, &c, 1.0f);
    func_00282DD8(&a, &b, &c);
    func_00282F20(&a, &a, 1.0f);
    range = D_L00_001AFD70 - D_L00_001AFD74;
    for (x = ctl->f40; x < ctl->f44; x += D_L00_001AFCF8) {
        if (x <= ctl->f44) {
            t = 0.5f;
            if (D_L00_001AFCF4 < ctl->f44) {
                if (x < D_L00_001AFCF4 * 0.5f) {
                    t = x / D_L00_001AFCF4;
                } else if (ctl->f44 - D_L00_001AFCF4 * 0.5f < x) {
                    t = (x - (ctl->f44 - D_L00_001AFCF4)) / D_L00_001AFCF4;
                }
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                phase = x * D_L00_001AFD68;
                u = (func_00283198(func_002ABB18(phase + func_00283CE0(D_L00_001B19C8) * D_L00_001AFD6C)) + 1.0f) * 0.5f;
                if (u > 0.99999f) {
                    u = 0.99999f;
                } else if (u < 0.01f) {
                    u = 0.01f;
                }
                w = D_L00_001AFD74 + range * func_002A7798(u);
            } else {
                t = x / ctl->f44;
                if (t > 1.0f) {
                    t = 1.0f;
                } else if (t < 0.0f) {
                    t = 0.0f;
                }
                w = D_L00_001AFD70 * func_00283198(t * 3.1415927f);
                if (t > D_L00_001AFD70) {
                    t = D_L00_001AFD70;
                } else if (t < 0.01f) {
                    t = 0.01f;
                }
            }
            s = func_L00_0031A6C8(func_00283198(t * 3.1415927f), 2);
            alpha = func_00283CF0((flag ? D_L00_001AFD28 : D_L00_001AFD24) * s);
            r = func_00283CF0(D_L00_001AFD5C * (func_00283198(func_00283B98(func_002ABB18(D_L00_001AFD38 * func_00283CE0(D_L00_001B19C8) + x * D_L00_001AFD44), D_L00_001AFD50 * 0.017453294f)) + 1.0f));
            g = func_00283CF0(D_L00_001AFD60 * (func_00283198(func_00283B98(func_002ABB18(D_L00_001AFD3C * func_00283CE0(D_L00_001B19C8) + x * D_L00_001AFD48), D_L00_001AFD54 * 0.017453294f)) + 1.0f));
            bl = func_00283CF0(D_L00_001AFD64 * (func_00283198(func_00283B98(func_002ABB18(D_L00_001AFD40 * func_00283CE0(D_L00_001B19C8) + x * D_L00_001AFD4C), D_L00_001AFD58 * 0.017453294f)) + 1.0f));
            if ((D_00138180[0x1A0 / 4] & 8) || D_00189E20.f2294 == 0x1D) {
                alpha = func_00283CF0((flag ? D_L00_001AFD30 : D_L00_001AFD2C) * func_L00_0031A6C8(func_00283198(t * 3.1415927f), 2));
                if (x < ctl->f44 * 0.5f) {
                    alpha = func_00283CF0(flag ? D_L00_001AFD30 : D_L00_001AFD2C);
                }
            }
            col = r | (g << 8);
            col = col | (bl << 16);
            col = col | (alpha << 24);
            pkt.col[0] = col;
            pkt.col[3] = col;
            pkt.col[2] = col;
            pkt.col[1] = col;
            flag ^= 1;

            func_00282F20(&vx, &b, x);
            func_00282F20(&vy, &a, w);
            func_00282F20(&vz, &c, w);
            func_00282CF0(&p, &ctl->pos, &vx);
            pkt.m[3].bits = p.bits;
            func_00282CC0(&p, &pkt.m[3], &vz);
            pkt.m[1].bits = p.bits;
            func_00282CF0(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            func_00282CF0(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            func_00280B90((unsigned int)&pkt, 0, 1);
            func_00282CC0(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            func_00282CC0(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            func_00280B90((unsigned int)&pkt, 0, 1);
            func_00282CF0(&p, &pkt.m[3], &vz);
            pkt.m[1].bits = p.bits;
            func_00282CF0(&p, &pkt.m[2], &vz);
            pkt.m[0].bits = p.bits;
            func_00280B90((unsigned int)&pkt, 0, 1);
            func_00282CF0(&p, &pkt.m[1], &vy);
            pkt.m[0].bits = p.bits;
            func_00282CF0(&p, &pkt.m[3], &vy);
            pkt.m[2].bits = p.bits;
            func_00280B90((unsigned int)&pkt, 0, 1);
            if (flag) {
                pkt.q88 = alpha1;
            } else {
                pkt.q88 = alpha0;
            }
        }
    }
}
