/* -G16 -Wa,-G16 lets the two 9-byte state-transition tables (nw + old * 3) take retail's $gp form.
 * Both func_0029F338(self); return; tails are written out: jump2 cross-jumps them after sched2, and
 * until then the second a0 set in case 14's block gives a0 = self its extra dependent. */
#include "common.h"
#define NULL ((void *)0)
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; Quad q[0x260]; } Hero;
typedef struct { Vector pos, v30, v40, v50; void *obj; int kind; } Hit;
extern char D_00189E20[];
extern char D_00189EA0[];
extern u8 *D_0018C0B0 __attribute__((nosda));
extern s16 D_0018A16C __attribute__((nosda));
extern int D_L06_001B2348[] __attribute__((sda));
extern int D_L06_001B2FB8[] __attribute__((sda));
extern u8 D_L06_001BFCA0[];
extern char D_L06_001B1A68[], D_L06_001B1AA0[];
extern u8 *D_L06_001B281C __attribute__((sda));
extern int D_L06_001B2FB0 __attribute__((sda));
extern u8 D_L06_001B1970[9] __attribute__((sda));
extern u8 D_L06_001B1980[9] __attribute__((sda));
extern void func_0026FEB8(const char *, ...);
extern int func_00277258(void *, int, void *, float);
extern int func_00278E78(void);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern int func_00283CF0(float);
extern void func_0029F338(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7470(void *, int, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_002A7CA0(void *, float, void *, float, float, float);
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern int func_002A8AF0(void *, void *, int);
extern float func_002A90F8(void *, void *);
extern void func_002AB8C0(void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002FD1B8(int, int, int, float, float, float, float);
extern void func_L00_002C42E0(int, int);
extern void func_L00_00410D18(void *, void *, void *);
extern float func_L01_00310BC0(void *, float, float, float, float, float);
extern int func_L04_0033CB08(void *, void *, int, int, float, float);
extern int func_001163B0(void);
extern int func_L06_0035EA68(void *, void *);
extern void func_L06_00361728(void *, void *, float);
extern void func_L06_003660F0(void *, int, void *, float);
extern int func_L06_00459BA8(void *, void *);
extern void func_L06_00459C38(void *, void *);
extern int func_L06_00459D08(void *, void *);
extern void func_L06_00459EC0(void *, void *);
extern void func_L06_0045A0D0(void *, void *, float, float, float);
extern int func_L06_0045A1B0(void *, void *, float, float, float, float, float, float, float);
extern void func_L06_0045A2D8(void *, void *, int, int, float, float, float, float, float, int, int, int, void *);
extern int func_L06_0045A490(void *, void *, float);
extern int func_L06_0045A500(void *, int, int);

#define B(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define UH(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define W(p, o) (*(int *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))

void func_L06_0045A5B0(u8 *self) {
    Hit hit;
    Vector v70, v80, v90, vA0, vB0, vC0;
    u8 *s6;
    u8 *hp;
    float *wp;
    u8 *p1, *p4, *p5, *p7, *p8, *p9, *p16, *p15;
    int s2, s3, s1, st;
    u8 s4, s7;
    u8 old;
    int cur;
    int nw;
    float f20, f21, f22;

    if (self != NULL && (s6 = *(u8 **)(self + 0x68)) != NULL) {
        func_L06_003660F0(self, 0, s6 + 0x140, 2.20000005f);
        if (B(self, 0x20) == 0) {
            if (func_L06_00459D08(self, s6) != 0) {
                STUB_printf(D_L06_001B1A68, H(self, 0xB2));
                func_0029F338(self);
                return;
            }
            goto check;
        }
        func_L06_00361728(self, &hit, 30.0f);
        func_L00_00410D18(self, s6, s6 + 0x20);
        func_002AB8C0(self, s6 + 0x50);
        s3 = func_00282948(s6 + 0x124) != 0;
        if (W(s6, 0x100) != 0 && B(self, 0x20) >= 7) {
            hp = *(u8 **)(s6 + 0x138);
            s2 = point_in_path_xy(&hit, hp + 0x10, *(int *)hp) != 0;
        } else {
            hp = *(u8 **)(s6 + 0x138);
            s2 = point_in_path_xy(D_00189EA0, hp + 0x10, *(int *)hp) != 0;
            if (vec_distance_xy(self + 0x10, D_00189EA0) < 30.0f) {
                hit.obj = *(void **)(D_00189EA0 + 0x2210);
                qcopy(&hit.pos, D_00189EA0);
                qcopy(&hit.v30, D_00189EA0 + 0x10);
                qcopy(&hit.v40, D_00189EA0 + 0x50);
                qcopy(&hit.v50, D_00189EA0 + 0x60);
                hit.kind = 0;
            } else {
                hit.obj = NULL;
                qzero(&hit.pos);
                qzero(&hit.v30);
                qzero(&hit.v50);
                qzero(&hit.v40);
                hit.kind = 2;
            }
        }
        if (W(s6, 0x100) != 0) {
            hp = *(u8 **)(s6 + 0x118);
            point_in_path_xy(self + 0x10, hp + 0x10, *(int *)hp);
        }
        old = B(self, 0xBC);
        s7 = 0xFF;
        nw = func_L06_00459BA8(self, s6);
        s4 = 0xFF;
        B(self, 0xBC) = nw;
        if (old != (u8)nw) {
            st = (u8)nw + old * 3;
            s7 = D_L06_001B1970[st];
            s4 = D_L06_001B1980[st];
        }
        func_0029FCC0(self, 0, v70.f);
        if (func_00277258(v70.f, 1, self, 0.800000012f) != 0 && GetCollHitMaterial() == 0) {
            f20 = **(float **)(s6 + 0x11C);
            f20 -= F(s6, 0x120);
            f20 *= 0.5f;
            if (f20 < func_00282C48(F(self, 0x18) - v70.f[2])) {
                f20 = (**(float **)(s6 + 0x11C) - F(s6, 0x120)) * 0.5f;
            } else {
                f20 = func_00282C48(F(self, 0x18) - v70.f[2]);
            }
            if (F(s6, 0xC8) < 0.0f) {
                f20 = -f20;
            }
            if (B(self, 0x20) == 0xE || B(self, 0x20) == 0xC) {
                f20 *= 2.0f;
            }
            p1 = self + 0x10;
            if (vec_distance_xy(p1, D_L06_001BFCA0) > 0.5f) {
                f21 = vec_distance_xy(p1, D_L06_001BFCA0) * 2.0f;
            } else {
                f21 = 1.0f;
            }
            if (D_L06_001B2348[0] % 45 == H(self, 0xB2) && func_002A77E0(2) == 0) {
                RippleDisturb(D_L06_001B2FB0, D_L06_001B2FB8[0], 1, F(self, 0x10), F(self, 0x14), f21, f20);
            }
            if (D_L06_001B2348[0] % ((func_001163B0() & 7) + 0x14) == 0) {
                f22 = func_002A7878(1.5f, 2.4000001f);
                v70.f[0] += func_002A7878(-0.150000006f, 0.150000006f);
                v70.f[1] += func_002A7878(-0.150000006f, 0.150000006f);
                v70.f[2] = func_002A90F8(D_L06_001BFCA0, NULL);
                func_002C19D8(v70.f, NULL, -1, f22, 5250.0f);
            }
        }
        if (F(s6, 0x13C) >= 1.0f) {
            *(Quad *)D_00189EA0 = *(Quad *)(self + 0x10);
        }
        cur = W(s6, 0x108);
        if (cur != -1 && B(*(u8 **)(D_L06_001B281C + (cur << 8) + 0x68), 0x14) != 0) {
            if (B(self, 0x43) != 0xD) {
                func_002A7470(self, 0xD, 0, 0xA);
            }
            B(self, 0x20) = 0x14;
        }
        switch (B(self, 0x20)) {
        case 0:
            STUB_printf(D_L06_001B1AA0);
            break;
        case 20:
            cur = W(s6, 0x108);
            if (cur != -1 && B(*(u8 **)(D_L06_001B281C + (cur << 8) + 0x68), 0x14) == 0) {
                B(self, 0x20) = 0x15;
            }
            break;
        case 21:
            if (UH(self, 0x96) >= 0x168) {
                if (B(self, 0x43) != 0) {
                    func_002A7470(self, 0, 0, 0xA);
                }
                UH(self, 0x96) = 0;
                B(self, 0x20) = 1;
            } else {
                func_L06_0045A0D0(self, s6, 0.00416666688f, 0.013888889f, 0.13333334f);
                UH(self, 0x96) = UH(self, 0x96) + 1;
            }
            break;
        case 1:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 0) {
                func_002A7470(self, 0, 0, 0xA);
            }
            if (s2 != 0 && hit.obj != NULL && hit.obj == D_0018C0B0 && func_L06_0045A500(self, 4, 6) == 0) {
                if (B(self, 0x43) != 1) {
                    func_002A7470(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 4;
            }
            if (hit.obj != NULL && hit.obj == D_0018C0B0 && func_L06_0045A490(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            } else if (s3 != 0) {
                if (B(self, 0x43) != 1) {
                    func_002A7470(self, 1, 0, 0xA);
                }
                W(s6, 0x124) = func_001163B0() % 200 + 0x12C;
                F(s6, 0x12C) = func_002A7940();
                B(self, 0x20) = 2;
            }
            FastVecScale(s6 + 0xC0, s6 + 0xC0, 0.949999988f);
            func_L06_0045A0D0(self, s6, 0.00416666688f, 0.013888889f, 0.13333334f);
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 2:
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                func_002A7470(self, 1, 0, 0xA);
            }
            if (s2 != 0 && hit.obj != NULL && hit.obj == D_0018C0B0) {
                if (func_L06_0045A500(self, 4, 6) == 0) {
                    if (B(self, 0x43) != 1) {
                        func_002A7470(self, 1, 0, 0xA);
                    }
                    B(self, 0x20) = 4;
                }
            } else {
                MobySpringTurn(self, F(s6, 0x12C), s6 + 0x110, 0.000484813732f, 0.00126051577f, 0.029088825f);
                F(self, 0xF4) = func_L01_00310BC0(s6 + 0x114, F(self, 0xF4), 0.0f, 0.000484813732f, 0.00126051577f, 0.029088825f);
                if (s3 != 0 && IsPointInCuboid(self + 0x10, W(s6, 0x104)) != 0) {
                    if (B(self, 0x43) != 0) {
                        func_002A7470(self, 0, 0, 0xA);
                    }
                    W(s6, 0x124) = func_001163B0() % 120 + 0x3C;
                    B(self, 0x20) = 1;
                }
            }
            func_L06_00459EC0(self, s6);
            if (func_L06_0045A1B0(self, s6, F(s6, 0x12C), 0.209439531f, 0.00166666671f, 0.52359885f, 0.00111111114f, 0.116666675f, 0.0500000045f) != 0 && s3 != 0) {
                if (B(self, 0x43) != 0) {
                    func_002A7470(self, 0, 0, 0xA);
                }
                W(s6, 0x124) = func_001163B0() % 120 + 0x3C;
                B(self, 0x20) = 1;
            }
            if (hit.obj != NULL && hit.obj == D_0018C0B0 && func_L06_0045A490(self, hit.obj, 1.5f) != 0) {
                if (B(self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                B(self, 0x20) = 5;
            }
            func_L06_0045A0D0(self, s6, 0.00416666688f, 0.013888889f, 0.13333334f);
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 4:
            p4 = self + 0x10;
            s1 = 1;
            f22 = func_00283248(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, f22, s6 + 0x110, 0.00349065894f, 0.0f, 0.209439546f);
            { float t = -func_00283248(vec_distance_xy(p4, &hit), hit.pos.f[2] - F(self, 0x18));
            F(self, 0xF4) = func_L01_00310BC0(s6 + 0x114, F(self, 0xF4), t, 0.00349065894f, 0.0f, 0.209439546f); }
            if (vec_distance_xy(p4, D_00189EA0) < 3.0f) {
            } else {
                s1 = 0;
            }
            if (s1 != 0) {
                FastVecScale(s6 + 0xC0, s6 + 0xC0, 0.899999976f);
            }
            if (func_L06_0045A1B0(self, s6, f22, 0.209439531f, 0.00555555569f, 0.52359885f, 0.000833333354f, 0.333333343f, 0.0833333358f) != 0 && s1 != 0 && (u32)(W(D_00189EA0, 0x221C) - 0x11) < 2) {
                if (B(self, 0x43) != 2) {
                    func_002A7470(self, 2, 0, 2);
                }
                PlayMobySound(1, 0, self);
                W(self, 0x98) = 0;
                B(self, 0x20) = 5;
                F(s6, 0x13C) = 0.0f;
                qcopy(s6 + 0xF0, p4);
            }
            F(s6, 0x128) = hit.pos.f[2] - 0.25f;
            func_L06_0045A0D0(self, s6, 0.010555556f, 0.0f, 0.633333385f);
            if (s2 == 0 || D_0018A16C == 0) {
                if (B(self, 0x43) != 1) {
                    func_002A7470(self, 1, 0, 0xA);
                }
                B(self, 0x20) = 2;
            }
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 5:
            p5 = self + 0x10;
            func_0029FCC0(self, 0, v70.f);
            FastVecSub(&v80, v70.f, p5);
            f21 = func_00283248(hit.pos.f[0] - v70.f[0], hit.pos.f[1] - v70.f[1]);
            MobySpringTurn(self, f21, s6 + 0x110, 0.00349065894f, 0.0f, 0.209439546f);
            F(self, 0xF4) = F(self, 0xF4) * 0.699999988f;
            F(s6, 0x13C) = F(s6, 0x13C) + 0.0280000009f;
            qcopy(&vB0, p5);
            FastVecSub(&v90, &hit, &v80);
            FastVecSub(&vA0, &v90, s6 + 0xF0);
            FastVecScale(&vA0, &vA0, F(s6, 0x13C) < 1.0f ? F(s6, 0x13C) : 1.0f);
            FastVecAdd(&vC0, &vA0, s6 + 0xF0);
            func_002A7EA0(self, p5, &vC0, 0.75f, 0.75f, 40.0f, 6.28318596f, 3);
            FastVecSub(s6 + 0xC0, p5, &vB0);
            if (F(s6, 0x13C) >= 1.0f) {
                ((Hero *)D_00189E20)->i[0x24CC / 4] = 0;
                func_L00_002C42E0(0x39, 1);
                W(((Hero *)D_00189E20)->ptr[0x2290 / 4], 0x9C) = -1;
                ((Hero *)D_00189E20)->b[0x22B5] = 1;
                B(self, 0x20) = 6;
            } else {
                F(s6, 0x12C) = f21;
            }
            break;
        case 6:
            func_L06_00459EC0(self, s6);
            func_L06_0045A1B0(self, s6, F(s6, 0x12C), 0.209439531f, 0.00166666671f, 0.52359885f, 0.00111111114f, 0.116666675f, 0.0500000045f);
            func_L06_0045A0D0(self, s6, 0.00333333341f, 0.013888889f, 0.116666675f);
            MobySpringTurn(self, F(s6, 0x12C), s6 + 0x110, 0.000436332368f, 0.000872664736f, 0.0523598865f);
            F(self, 0xF4) = func_L01_00310BC0(s6 + 0x114, F(self, 0xF4), 0.0f, 0.000436332368f, 0.000872664736f, 0.0523598865f);
            if ((B(self, 0x60) & 2) && B(self, 0x43) != 1) {
                func_002A7470(self, 1, 0, 0xA);
            }
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 7:
            if (s2 != 0) {
                if (B(self, 0x43) != 4) {
                    func_002A7470(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else if (s3 != 0) {
                if (B(self, 0x43) != 4) {
                    func_002A7470(self, 4, 0, 0xA);
                }
                W(s6, 0x124) = func_001163B0() % 200 + 0x12C;
                F(s6, 0x12C) = func_002A7940();
                B(self, 0x20) = 8;
            }
            p7 = s6 + 0xC0;
            FastVecScale(p7, p7, 0.949999988f);
            F(s6, 0xC8) = F(s6, 0xC8) - 0.163333341f;
            if (func_L04_0033CB08(self, p7, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(p7, p7, 0.5f);
            }
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 8:
            if (s2 != 0) {
                if (B(self, 0x43) != 4) {
                    func_002A7470(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 9;
            } else {
                MobySpringTurn(self, F(s6, 0x12C), s6 + 0x110, 0.000218166184f, 0.000436332368f, 0.0130899716f);
                F(self, 0xF4) = func_L01_00310BC0(s6 + 0x114, F(self, 0xF4), 0.0f, 0.000218166184f, 0.000436332368f, 0.0130899716f);
                if (s3 != 0 && IsPointInCuboid(self + 0x10, W(s6, 0x104)) != 0) {
                    if (B(self, 0x43) != 3) {
                        func_002A7470(self, 3, 0, 0xA);
                    }
                    W(s6, 0x124) = func_001163B0() % 120 + 0x3C;
                    B(self, 0x20) = 7;
                }
            }
            func_L06_00459EC0(self, s6);
            if (func_L06_0045A1B0(self, s6, F(s6, 0x12C), 0.3490659f, 0.000833333354f, 1.0471977f, 0.00249999994f, 0.0166666675f, 0.0166666675f) != 0 && s3 != 0) {
                if (B(self, 0x43) != 3) {
                    func_002A7470(self, 3, 0, 0xA);
                }
                W(s6, 0x124) = func_001163B0() % 120 + 0x3C;
                B(self, 0x20) = 7;
            }
            p8 = s6 + 0xC0;
            F(s6, 0xC8) = F(s6, 0xC8) - 0.163333341f;
            if (func_L04_0033CB08(self, p8, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(p8, p8, 0.5f);
            }
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 9:
        case 10:
            f20 = func_00283248(hit.pos.f[0] - F(self, 0x10), hit.pos.f[1] - F(self, 0x14));
            MobySpringTurn(self, f20, s6 + 0x110, 0.000218166184f, 0.000436332368f, 0.0130899716f);
            if (func_L06_0045A1B0(self, s6, f20, 0.52359885f, 0.00111111114f, 1.57079649f, 0.00249999994f, 0.0250000022f, 0.0166666675f) != 0 && vec_distance_xy(self + 0x10, &hit) < 1.89999998f && B(self, 0x20) != 0xA) {
                if (B(self, 0x43) != 5) {
                    func_002A7470(self, 5, 0, 2);
                }
                B(self, 0x20) = 0xA;
            }
            p9 = s6 + 0xC0;
            F(s6, 0xC8) = F(s6, 0xC8) - 0.163333341f;
            if (func_L04_0033CB08(self, p9, 0x400, 0x10, 1.0f, 0.0f) != 0) {
                FastVecScale(p9, p9, 0.5f);
            }
            B(s6, 0x48) = FloatToInt(8.0f);
            B(s6, 0x4A) = FloatToInt(9.60000038f);
            if (s2 == 0) {
                if (B(self, 0x43) != 4) {
                    func_002A7470(self, 4, 0, 0xA);
                }
                B(self, 0x20) = 8;
            }
            func_L06_0045A2D8(self, s6, 0xA, 5, 17.0f, 20.0f, 1.0f, 1.0f, 1.0f, 4, 4, 0xB, hit.obj);
            if (B(self, 0x60) & 2) {
                if (B(self, 0x43) != 4) {
                    func_002A7470(self, 4, 0, 0xA);
                }
                W(s6, 0x124) = func_001163B0() % 200 + 0x12C;
                B(self, 0x20) = 8;
            }
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 11:
            if (B(self, 0x60) & 2) {
                B(self, 0x20) = 7;
            }
            break;
        case 12:
            if (mine_fall(self, s6 + 0x60) & 1) {
                func_L06_00459C38(self, s6);
            }
            break;
        case 13:
            if (B(self, 0x60) & 2) {
                func_L06_00459C38(self, s6);
            }
            break;
        case 14:
            if (mine_fall(self, s6 + 0x60) & (B(self, 0x60) & 2)) {
                SpawnExplosionEffects(self, s6 + 0xC0, NULL, 0.0f, 0.0f, 3, 3, 5, 2.0f, 1.0f, 4.0f, 1.0f, -1, 7.0f, 0, 1, -1, 0, 0x810001);
                func_0029F338(self);
                return;
            }
            break;
        case 16:
            p16 = s6 + 0xC0;
            FastVecScale(p16, p16, 0.949999988f);
            F(s6, 0xC8) = F(s6, 0xC8) - 0.163333341f;
            func_L04_0033CB08(self, p16, 0x400, 0x10, 1.0f, 0.0f);
            if (B(self, 0x60) & 2) {
                func_L06_00459C38(self, s6);
            }
            break;
        case 15:
            p15 = s6 + 0xC0;
            FastVecScale(p15, p15, 0.949999988f);
            F(s6, 0xC8) = F(s6, 0xC8) - 0.163333341f;
            func_L04_0033CB08(self, p15, 0x400, 0x10, 1.0f, 0.0f);
            if (s7 != 0xFF) {
                if (B(self, 0x43) != s4) {
                    func_002A7470(self, s4, 0, 6);
                }
                B(self, 0x20) = s7;
            }
            break;
        case 17:
            FastVecScale(s6 + 0xC0, s6 + 0xC0, 0.949999988f);
            if (B(self, 0x60) & 2) {
                func_L06_00459C38(self, s6);
            }
            break;
        }
    check:
        if (F(self, 0x10) < 2.0f || F(self, 0x10) > 1021.0f || F(self, 0x14) < 2.0f || F(self, 0x14) > 1021.0f || F(self, 0x18) < 2.0f || F(self, 0x18) > 1021.0f) {
            func_0029F338(self);
        }
    }
}
