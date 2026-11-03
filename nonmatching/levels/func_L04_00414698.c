/* Opus 5.5 xhigh (task v2123), 3 November 2026: 6020/6032 bytes, 0 of 2 places (04 and 11);
 * opcode alignment 1494 of 1508 equal, 15 hunks (previous draft 5976 bytes on -G0).
 * Unit: src/levels/shared/L04_0040F8F0-hover-g8.c, cflags line
 *   src/levels/shared/L04_0040F8F0-hover-g8.c<TAB>-O2 -G8 -ffunction-sections -g
 * Declarations needed (below): D_L04_001B08F0 and D_001A7CC0 __attribute__((sda)) (gp), D_00189FC0,
 *   D_00138320 and D_001B24DC NOT_SDA (absolute at -G8); hero/config struct casts for D_00189E20 and
 *   D_001B9540 (per-block lui/addiu bases, as retail).
 * Findings:
 *  - Dead pitch comparison (retail 00415D58..): `if (f21 > 1.2217305f) height = 0.0f;` after the case-2
 *    func_00283C80 call. flow1 deletes the dead store (cse does not), the empty branch survives to jump2,
 *    which deletes it; the c.lt.s stays (delete_computation skips it after reload with sched2 on).
 *    NOTE REVIEW: that is the one allowed dead store to a local with a real effect.
 *  - GP/absolute debug word: file-scope `extern int D_001A7CC0 __attribute__((sda));` gives the gp read in
 *    the else arm; a block-scope `extern int D_001A7CC0;` inside the func_00282948()==0 arm makes a
 *    separate decl whose RTL has no sda flag, so that read is lui 0x1A / lw 0x7CC0 as in retail.
 *    dbg is set in both arms (if/else), so reorg steals the gp load into the bnez delay slot.
 *  - qcopy for the vD0/vE0/v20/D_001B9900 copies; object+0x10, st+0x290 and st+0x2B0 written as expressions
 *    at every use (no pos/vel/s2 locals) so GCSE PRE makes the retail reaching-register copies
 *    (addiu $fp,$s7,0x10; daddu $s3,$s1; daddu $s2,$s0).
 *  - ?: arguments for the two D_L04_001B08F0 constant pairs and the 0x338 limit constant; damping = 0.016f
 *    set right after grip and multiplied later (retail keeps 0.016 in $f23 across func_002AA140).
 * Remaining: saved-register rotation (ours st=$s5/object=$s6, retail $s6/$s7), bne vs bnel at 004147A8,
 *   cvt.w.s $f3 vs $f2 at 00415404 (round value lives in $f2 vs $f21), lwc1 0x14($s7)/lui 0x1B order at
 *   00415668, a missing addiu $a0,15 / sw 0x32C / b block near 00415878 (cross-jumped tail), and the
 *   lui $s1,0x1B / sw 0x16C order around 0041596C and 00415A58.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
extern u8 D_00188660[];
extern u8 D_00189E20[];
extern float D_00189FC0 NOT_SDA;
extern u8 D_001B9540[];
extern u8 D_00189EA0[];
extern u8 D_001BFAC0[];
extern Quad D_001B9900;
extern int D_00138320 NOT_SDA;
extern int D_001A7CC0 __attribute__((sda));
extern int D_L04_001B08F0 __attribute__((sda));
extern u8 *D_001B24DC NOT_SDA;
extern float D_001BFB00[];
extern char D_L04_001A8F20[];
extern float func_002A89A8(char *, int, float);
extern int func_00278E78(void);
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_L04_004135B8(u8 *, u8 *);
extern void func_L00_002A9D38(void *, void *, float);
extern float func_00283B98(float, float);
extern float func_00283248(float, float);
extern float func_00282C48(float);
extern float func_002AA2E8(float *, float, float);
extern void func_00282D30(void *, void *, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_L04_0040BD50(Vec *, int, int, float, float);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void *func_L04_00362768(void *, void *, u32, float);
extern void * func_002C19D8(void *, int, int, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern float func_002AA140(float, float, float);
extern float func_002AA898(float *, float, float *, float, float, float, int);
extern void func_002AF000(float *, float, float, float);
extern void func_002AC9F8(float *, float);
extern void func_00282F20(float *, float *, float);
extern int func_00282948(void *);
extern void func_L04_00412C58(u8 *, u8 *, float, float, float, float, float);
extern void func_L04_0040BED0(Vec *, Vec *, int, u8 *, float);
extern void func_L04_0040C0C0(Vec *, Vec *, int, int);
extern void func_L04_00347AB8(void *, void *, void *, void *, float, float, float);
extern void func_L04_00412E38(void *, void *, float, float);
extern int func_L04_00413A38(u8 *, u8 *, u8 *, u8 *, Vec *, Vec *, u8 *, int *, int, int *,
                             float, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
extern void func_L04_0040E248(u8 *, u8 *);
extern int func_L00_002D6900(int);
extern void * func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L00_00322EC8(void *);
extern float func_002A7940(void);
extern void * func_L04_00407078(u8 *, int, Vec *, u8 *, int, int, Vec *, char *, char *, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_00282E20(void *);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern void func_L04_002DAD10(Quad);
typedef struct { u8 pad000[0x1A0]; float heading; u8 pad1A4[0x24B8 - 0x1A4]; float turnScale; } L04_HoverHero;
typedef struct { u8 pad000[0x158]; float f158; u8 pad15C[4]; float f160; u8 pad164[4]; int f168; int f16C;
                 u8 pad170[0x10]; float f180; u8 pad184[4]; int f188; } L04_HoverCfg;
#define HERO ((L04_HoverHero *)D_00189E20)
#define CFG ((L04_HoverCfg *)D_001B9540)
#define I(o) (*(s32 *)(st + (o)))
#define F(o) (*(float *)(st + (o)))
#define S(o) (*(s16 *)(st + (o)))
#define U16(o) (*(u16 *)(st + (o)))
#define OF(o) (*(float *)(object + (o)))
#define HEAD (HERO->heading)
#define SND_STOP(field) { int h = I(field); if (h != -1) { u8 *e = D_00188660 + h * 0x70; if (*(u8 **)(e + 0x88) == object && e[0x74] != 0) func_002E59F8(h); } I(field) = -1; }

/* Hover board physics for the rider: steering, speed, landing and crash handling. */
void func_L04_00414698(u8 *object, u8 *st)
{
    Vec v20, v30, v40, v50, start, v70, v80, v90, vA0, vB0, vC0, vD0, vE0, vF0;
    int flag, flag2, idle, dbg;
    float ground, height, limit, speed, grip, factor, damping, x;
    u8 *prev;

    flag = 0;
    start.q = *(Quad *)(object + 0x10);
    ground = func_002A89A8((char *)(object + 0x10), 0, 0.5f);
    height = OF(0x18) - ground;
    if ((func_00278E78() != 0 || S(0x274) != 0) && func_002E59B0(object, I(0x3BC)) != 0) {
        SND_STOP(0x3BC)
    }
    if (object[0x20] == 3) func_L04_004135B8(object, st);
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) {
            func_L00_002A9D38(&v20, st + 0x2C0, 0.12f);
            D_00189FC0 = func_00283B98(CFG->f158,
                                       func_00283248(func_00282C48(v20.f[1]), v20.f[0]));
        } else {
            float t = func_00283248(F(0x6A0) - OF(0x10), F(0x6A4) - OF(0x14));
            HEAD = t;
            if (I(0x750) >= 11) HEAD = func_00283B98(t, (float)I(0x750) * 0.01f);
        }
        idle = 1;
        if (st[0x348] != 0 && I(0x4D8) == 0) {
            idle = 0;
            func_002AA2E8((float *)(st + 0x30C), 0.050000004f, 0.0030555557f);
        } else {
            if (func_00278E78() == 0 && S(0x274) == 0) {
                u8 *s5, *s0;
                float yaw, z;
                if (F(0x30C) > 0.19166668f) {
                    idle = 0;
                    func_002AA2E8((float *)(st + 0x30C), 0.19166668f, 0.0031944446f);
                }
                I(0x278) = 0;
                s5 = object + 0xC0;
                func_00282D30(&v70, s5, 0.95f);
                s0 = object + 0xD0;
                func_00282D30(&v80, s0, 0.45f);
                func_00282D30(&v90, s0, -0.45f);
                func_0029FCC0(object, 0, &vA0);
                func_00282CC0(&vA0, &vA0, &v70);
                func_00282CC0(&vA0, &vA0, &v80);
                z = ground - 0.25f;
                vA0.f[2] = ground;
                func_L04_0040BD50(&vA0, 1, 0, z, F(0x30C));
                func_0029FCC0(object, 1, &vB0);
                func_00282CC0(&vB0, &vB0, &v70);
                func_00282CC0(&vB0, &vB0, &v90);
                vB0.f[2] = ground;
                func_L04_0040BD50(&vB0, 1, 0, z, F(0x30C));
                qcopy(&vD0, &vB0);
                qcopy(&vE0, &vA0);
                yaw = OF(0xF8);
                vC0.f[0] = func_00283180(yaw) * func_002A7878(0.031666666f, 0.06666667f);
                vC0.f[1] = func_00283198(yaw) * func_002A7878(0.031666666f, 0.06666667f);
                vC0.f[2] = F(0x30C) * 0.5f;
                if (func_002A77E0(func_00283CF0(1.0f / F(0x30C)) - 1) == 0) {
                    if (F(0x30C) >= 0.1f) {
                        func_L04_00362768(&vD0, &vC0, 0x40, 0.6f);
                        func_00282D30(&v70, s5, -0.4f);
                        func_00282CC0(&vD0, &vD0, &v70);
                        func_L04_00362768(&vD0, &vC0, 0x40, 0.7f);
                        func_00282CC0(&vD0, &vD0, &v70);
                        func_L04_00362768(&vD0, &vC0, 0x40, 0.8f);
                        func_L04_00362768(&vE0, &vC0, 0x40, 0.6f);
                        func_00282D30(&v70, s5, -0.4f);
                        func_00282CC0(&vE0, &vE0, &v70);
                        func_L04_00362768(&vE0, &vC0, 0x40, 0.7f);
                        func_00282CC0(&vE0, &vE0, &v70);
                        func_L04_00362768(&vE0, &vC0, 0x40, 0.8f);
                    }
                }
                if (F(0x30C) <= 0.1f && func_002A77E0(2) == 0) {
                    func_00282D30(&v70, s5, 0.5f);
                    func_00282CC0(&vF0, (object + 0x10), &v70);
                    vF0.f[2] = ground;
                    func_002C19D8(&vF0, 0, 0x40645050, 0.8f, 14700.0f);
                }
                if (func_002E59B0(object, I(0x3BC)) == 0 && object[0x20] != 3) {
                    I(0x3BC) = func_002E5CF8(0x10, 4, object);
                    if (height < 0.5f) func_002E5CF8(6, 0, object);
                }
            }
        }
        if (func_00278E78() == 7 && S(0x274) == 0) {
            if (D_L04_001B08F0 == 0) func_002E5CF8(0x11, 0, object);
            if (func_002E59B0(object, I(0x748)) == 0) I(0x748) = func_002E5CF8(0x12, 4, object);
            if (func_002E59B0(object, I(0x74C)) == 0) I(0x74C) = func_002E5CF8(0x13, 4, object);
            D_L04_001B08F0 = 1;
        } else {
            SND_STOP(0x748)
            SND_STOP(0x74C)
            D_L04_001B08F0 = 0;
        }
        if (idle) {
            if ((D_00138320 & 0x40) || object[0x20] == 3) {
                func_002AA3A8((float *)(st + 0x30C), (float *)(st + 0x288), 0.33333334f,
                              D_L04_001B08F0 != 0 ? 0.011f : 0.022f, 0.5f,
                              D_L04_001B08F0 != 0 ? 0.013888889f : 0.027777778f);
            } else {
                func_002AA2E8((float *)(st + 0x30C), 0.050000004f, 0.0027777778f);
            }
        }
        speed = F(0x30C) + F(0x27C);
    } else {
        speed = 0.0f;
    }
    grip = F(0x30C) * 3.0f;
    damping = 0.016f;
    if (grip > 1.0f) grip = 1.0f;
    limit = func_002AA140(0.05817765f, I(0x338) != 0 ? 0.01658063f : 0.021816619f, grip);
    factor = (1.0f - grip) + 1.0f;
    if (factor > 1.9f) factor = 1.9f;
    if (D_L04_001B08F0 != 0) {
        factor = 2.75f;
        limit = limit * 1.25f;
    }
    if (I(0x4C4) != 0) {
        factor = 4.0f;
        limit = limit * F(0x63C);
    }
    damping = factor * damping;
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) limit = limit * HERO->turnScale;
        if (limit < 0.000029088826f) limit = 0.000029088826f;
        func_002AA898((float *)(object + 0xF8), HEAD, (float *)(st + 0x308), damping, 0.3f, limit, 0);
    }
    if (D_L04_001B08F0 != 0) {
        if (I(0x64C) != 0 && I(0x71C) != 0) {
            func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
            func_00282CF0((st + 0x290), (st + 0x290), &v20);
            I(0x71C) = 0;
        }
        func_002AF000(v20.f, speed, OF(0xF8), 0.0f);
        func_00282D30(&v20, &v20, 0.025f);
        func_00282CC0((st + 0x290), (st + 0x290), &v20);
        func_002AC9F8((float *)(st + 0x290), speed);
    } else {
        func_002AF000((float *)(st + 0x290), speed, OF(0xF8), 0.0f);
        func_002AC9F8((float *)(st + 0x290), speed);
        qcopy(&v20, object + 0xD0);
        func_00282F20(v20.f, v20.f, F(0x30C) * (F(0x308) * -1.75f));
        func_00282CC0((st + 0x290), (st + 0x290), &v20);
    }
    if (func_00282948(st + 0x64C) == 0) {
        extern int D_001A7CC0;
        func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
        func_00282CC0((st + 0x290), (st + 0x290), &v20);
        I(0x71C) = 1;
        dbg = D_001A7CC0;
    } else {
        dbg = D_001A7CC0;
    }
    if (dbg != 0) qcopy(&D_001B9900, &v20);
    func_L04_00412C58(object, st, height, 0.2f, 0.23f, 12.0f, 0.1f);
    if (height > 0.44f) {
        S(0x274) = 1;
        prev = st + 0x2A0;
        U16(0x276) = U16(0x276) + 1;
    } else {
        prev = st + 0x2A0;
        if (S(0x274) != 0 && S(0x276) >= 13 && F(0x358) < 0.0f && func_00278E78() != 0) {
            if (S(0x276) >= 46) {
                func_00282D30(&v30, prev, 0.5f);
                func_00282CD8(&v70, &v30, (object + 0x10));
                v40.q = *(Quad *)(st + 0x2A0);
                v30.f[2] = OF(0x18);
                v40.f[2] = 0.016666668f;
                func_00282D30(&v40, &v40, 0.85f);
                func_L04_0040BED0(&v30, &v40, 0, object, F(0x30C));
                func_L04_0040C0C0(&v30, &v40, 8, 1);
                if (object[0x20] != 3) {
                    SND_STOP(0x328)
                    I(0x328) = func_002E5CF8(4, 4, object);
                    I(0x32C) = 4;
                    I(0x324) = 15;
                }
            }
            if (st[0x349] == 0 && func_00278E78() != 5) {
                float sink, t;
                if (F(0x358) > -0.05f) F(0x358) = -0.05f;
                sink = F(0x358);
                t = 1.0f - (sink + 0.35f) * 2.857143f;
                if (t > 1.0f) t = 1.0f;
                if (t < 0.0f) t = 0.0f;
                I(0x34C) = (int)(t * 5.0f) + 15;
                if (t < 0.5f) t = 0.5f;
                st[0x349] = 1;
                F(0x354) = t * 0.06f;
                F(0x2A8) = sink * -0.3f;
            }
        }
        S(0x274) = 0;
        U16(0x276) = 0;
    }
    x = OF(0xF0);
    if (st[0x349] != 0) {
        OF(0xF4) = OF(0xF4) + F(0x354);
        func_00282948(st + 0x34C);
        if (I(0x34C) == 0) st[0x349] = 0;
    } else if (S(0x274) == 0) {
        func_00282F20((float *)(st + 0x2B0), D_001BFB00, 1.0f);
        func_L04_00347AB8(object + 0xC0, object + 0xF0, st + 0x304, (st + 0x2B0), 0.03f, 0.3f, 0.0f);
    } else {
        func_002AF000((float *)(st + 0x2B0), 1.0f, func_00283B98(OF(0xF8), 3.1415927f), 0.99483776f);
        func_L04_00347AB8(object + 0xC0, object + 0xF0, st + 0x304, (st + 0x2B0), 0.03f, 0.3f, 0.0f);
    }
    OF(0xF0) = x;
    func_L04_00412E38(object, st, 0.15f, 0.004f);
    *(Quad *)(st + 0x2A0) = *(Quad *)(st + 0x290);
    F(0x358) = F(0x2A8);
    {
    int result = func_L04_00413A38(object, (object + 0x10), (st + 0x290), prev, &v30, &v50, (st + 0x2B0), &flag, 1, &flag2,
                                   F(0x30C) + F(0x27C), F(0x280), 0.16666667f, F(0x24), F(0x20));
    if (result != 0) {
        if (D_L04_001B08F0 != 0) func_00282D30((st + 0x290), (st + 0x290), 0.85f);
        if (flag2 != 0)
            I(0x70C) = I(0x70C) + 1;
        else
            I(0x70C) = 0;
        switch (result) {
        case 1:
            if (I(0x1DC) != -1) {
                u8 *target = D_001B24DC + (I(0x1DC) << 8);
                float a = func_00283BE0(OF(0xF8), func_00283248(v30.f[0] - OF(0x10), v30.f[1] - OF(0x14)));
                int dir;
                if (a > 0.52359885f && a < 2.617994f) {
                    dir = 3;
                } else {
                    dir = 5;
                    if (a < -0.52359885f && a > -2.617994f) dir = 4;
                }
                if (I(0x36C) != 0 && S(0x34A) == dir) {
                    I(0x36C) = 30;
                } else {
                    I(0x36C) = 30;
                    S(0x34A) = dir;
                    func_002A7470(target, dir, 3, 3);
                }
            }
            switch (flag) {
            case 0:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 4) {
                        SND_STOP(0x328)
                        I(0x328) = func_002E5CF8(4, 4, object);
                        I(0x32C) = 4;
                    }
                    I(0x324) = 15;
                }
                break;
            case 1:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 5) {
                        SND_STOP(0x328)
                        I(0x328) = func_002E5CF8(5, 4, object);
                        I(0x32C) = 5;
                    }
                    I(0x324) = 15;
                }
                break;
            case 2:
                if (object[0x20] != 3) func_002E5CF8(2, 0, object);
                break;
            case 3:
                if (I(0x4D8) == 0) F(0x30C) = F(0x30C) * 0.25f;
                break;
            }
            v30.f[2] = OF(0x18) + 0.05f;
            func_L04_0040BED0(&v30, (Vec *)(st + 0x290), flag, object, F(0x30C));
            break;
        case 2:
            if (I(0x4D8) == 0) {
                if (object[0x20] != 3) {
                    float r;
                    func_L04_0040E248(object, st);
                    CFG->f168 = 0x3C;
                    CFG->f188 = 0x5A;
                    CFG->f160 = 0.2f;
                    CFG->f16C = 0;
                    CFG->f180 = 0.1f;
                    func_L00_002D6900(0x1C);
                    func_0032C700((object + 0x10), 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.666f, 20.0f, 1, 1, 0, 0);
                    func_L00_00322EC8(st + 0x4E0);
                    func_002E5CF8(3, 0, object);
                    object[0xBC] = 6;
                    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
                    *(s16 *)(object + 0x96) = 0x64;
                    func_00282D30(&v50, &v50, func_002A7878(0.1f, 0.2f));
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3D, (Vec *)(object + 0x10), object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3E, (Vec *)(object + 0x10), object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3F, (Vec *)(object + 0x10), object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.0f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB40, (Vec *)(object + 0x10), object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB40, (Vec *)(object + 0x10), object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    if (I(0x1DC) != -1) {
                        v90.q = *(Quad *)(object + 0x10);
                        v90.f[2] = v90.f[2] + 0.25f;
                        v80.f[0] = func_00283180(OF(0xF8));
                        v80.f[1] = func_00283198(OF(0xF8));
                        v80.f[2] = 0.0f;
                        func_00282CD8(&vA0, &v80, &v90);
                        if (func_002761F8(&v90, &v80, 2, 0, 0) != 0) {
                            if (func_00278E78() != result) {
                                float f21 = func_00283248(*(float *)(D_001BFAC0 + 0x48), func_00282E20(D_001BFAC0 + 0x40));
                                float f20 = func_00283B98(func_00283248(*(float *)(D_001BFAC0 + 0x40), *(float *)(D_001BFAC0 + 0x44)), 3.1415927f);
                                func_00283C80(func_00283248(v80.f[0], v80.f[1]), f20);
                                if (f21 > 1.2217305f) height = 0.0f;
                            }
                        }
                    }
                }
            }
            break;
        }
    } else {
        I(0x750) = 0;
    }
    }
    func_00282CF0(&v20, &start, (object + 0x10));
    v20.i[2] = 0;
    F(0x280) = func_00282DF0(&v20);
    if (F(0x280) < 0.01f) I(0x750) = I(0x750) + 1;
    {
        Quad q = *(Quad *)(object + 0x10);
        *(Quad *)D_00189EA0 = q;
        *(Quad *)(D_00189EA0 + 0x10) = *(Quad *)(object + 0xF0);
        func_L04_002DAD10(q);
    }
}
