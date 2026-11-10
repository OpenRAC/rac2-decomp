/* func_PAL_L04_00418DE8, the PAL copy of func_L04_00414698: the same C, where rename func_L04_004135B8 becomes func_PAL_L04_00417CB0; rename func_L04_00362768 becomes func_PAL_L04_00364B90; rename func_L04_00412C58 becomes func_PAL_L04_00417310; rename func_L04_0040BED0 becomes func_PAL_L04_00410488; rename func_L04_0040C0C0 becomes func_PAL_L04_00410678; rename func_L04_00413A38 becomes func_PAL_L04_00418180; rename func_002A7470 becomes func_PAL_002A7E68; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L04_00407078 becomes func_PAL_L04_0040B520; scale (int)(x * 5.0f) + 2; lit 15 becomes 12; lit 15 becomes 12. */
/* func_PAL_L04_00418DE8: hover board physics for the rider (Barlow, Joba). A unit of its own for
 * -G8, -g, -frac2-hazard-labels and -frac2-frame-pointer-liveness (config/cflags.txt). The hazard
 * option puts the 00414AD8 bc1f target on the nop at 00414BF8, as retail. Without the liveness
 * option flow keeps $fp live after reload and reorg annuls the slot of the branch at 004147A8
 * (bnel where retail has bne, same slot `addiu $fp,$s7,0x10`; docs/COMPILER-NOTES.md).
 * D_L04_001B08F0 and D_001A7CC0 are sda ($gp); D_00189FC0 and D_00138320 are NOT_SDA (absolute);
 * D_L04_001B24DC is plain (unsplit -G8 macro load); D_L04_001A8F20 is MACRO_ADDR (unsplit la).
 * Source notes:
 *  - x is one float reused for the sink factor, the saved OF(0xF0) and the case-2 pitch (all retail
 *    $f21); yaw stays a separate block-local.
 *  - object + 0xC0, object + 0x10 and st + 0x2A0 are written as expressions at every use: gcse's PRE
 *    makes retail's reaching-register copies, and a local pseudo would block $s5 for st and object.
 *  - SPAWN's `r` is block-scoped, one pseudo per spawn, so local-alloc takes each (single-death rule)
 *    and the case-2 constants land in retail's $f20-$f24.
 *  - Retail keeps a dead pitch comparison: `if (x > 1.2217306f) height = 0.0f;`. flow1 deletes the
 *    dead store and jump2 the empty branch; the c.lt.s stays.
 *  - The block-scope `extern int D_001A7CC0;` in one arm is a second declaration without the sda
 *    flag, which gives retail's absolute read there.
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
extern u8 *D_L04_001B24DC;
extern float D_001BFB00[];
extern char D_L04_001A8F20[] MACRO_ADDR;
extern float func_002A89A8(char *, int, float);
extern int func_00278E78(void);
extern int func_002E59B0(void *, int);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_L04_00417CB0(u8 *, u8 *);
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
extern void *func_PAL_L04_00364B90(void *, void *, u32, float);
extern void * func_002C19D8(void *, int, int, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern float func_002AA140(float, float, float);
extern float func_002AA898(float *, float, float *, float, float, float, int);
extern void func_002AF000(float *, float, float, float);
extern void func_002AC9F8(float *, float);
extern void func_00282F20(float *, float *, float);
extern int func_00282948(void *);
extern void func_PAL_L04_00417310(u8 *, u8 *, float, float, float, float, float);
extern void func_PAL_L04_00410488(Vec *, Vec *, int, u8 *, float);
extern void func_PAL_L04_00410678(Vec *, Vec *, int, int);
extern void func_L04_00347AB8(void *, void *, void *, void *, float, float, float);
extern void func_L04_00412E38(void *, void *, float, float);
extern int func_PAL_L04_00418180(u8 *, u8 *, u8 *, u8 *, Vec *, Vec *, u8 *, int *, int, int *,
                             float, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_L04_0040E248(u8 *, u8 *);
extern int func_L00_002D6900(int);
extern void * func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L00_00322EC8(void *);
extern float func_002A7940(void);
extern void * func_PAL_L04_0040B520(u8 *, int, Vec *, u8 *, int, int, Vec *, char *, char *, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern float func_00282E20(void *);
extern float func_00283BE0(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern void func_L04_002DAD10(Quad);
typedef struct { u8 pad000[0x1A0]; float heading; u8 pad1A4[0x24B8 - 0x1A4]; float turnScale; } L04_HoverHero;
typedef struct { u8 pad000[0x158]; float f158; u8 pad15C[4]; float f160; u8 pad164[4]; int f168; int f16C;
                 u8 pad170[0x10]; float f180; u8 pad184[4]; int f188; } L04_HoverCfg;
typedef struct { u8 pad00[0x40]; float v[4]; } L04_HoverTarget;
#define I(o) (*(s32 *)(st + (o)))
#define F(o) (*(float *)(st + (o)))
#define S(o) (*(s16 *)(st + (o)))
#define U16(o) (*(u16 *)(st + (o)))
#define OF(o) (*(float *)(object + (o)))
#define SND_STOP(field) { int h = I(field); if (h != -1) { u8 *e = D_00188660 + h * 0x70; if (*(u8 **)(e + 0x88) == object && e[0x74] != 0) func_002E59F8(h); } I(field) = -1; }

#define SPAWN(id, a, b) { float r = func_002A7940(); func_002AF000(dir->f, 0.10000001f, r, func_002A7878(0.78539824f, 1.5707965f)); func_00282CD8(&v80, dir, &v50); func_PAL_L04_0040B520(object, id, (Vec *)(object + 0x10), object + 0xF0, 0, 0, dir, tag, tag, a, b); }

/* Hover board physics for the rider: steering, speed, landing and crash handling. */
void func_PAL_L04_00418DE8(u8 *object, u8 *st)
{
    Vec v20, v30, v40, v50, start, v70, v80, v90, vA0, vB0, vC0, vD0, vE0, vF0;
    int flag, flag2, idle, dbg;
    float ground, height, limit, speed, grip, factor, damping, x;

    flag = 0;
    start.q = *(Quad *)(object + 0x10);
    ground = func_002A89A8((char *)(object + 0x10), 0, 0.5f);
    height = OF(0x18) - ground;
    if ((func_00278E78() != 0 || S(0x274) != 0) && func_002E59B0(object, I(0x3BC)) != 0) {
        SND_STOP(0x3BC)
    }
    if (object[0x20] == 3) func_PAL_L04_00417CB0(object, st);
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) {
            func_L00_002A9D38(&v20, st + 0x2C0, 0.1728f);
            D_00189FC0 = func_00283B98(((L04_HoverCfg *)D_001B9540)->f158,
                                       func_00283248(func_00282C48(v20.f[1]), v20.f[0]));
        } else {
            float t = func_00283248(F(0x6A0) - OF(0x10), F(0x6A4) - OF(0x14));
            ((L04_HoverHero *)D_00189E20)->heading = t;
            if (I(0x750) >= 9) ((L04_HoverHero *)D_00189E20)->heading = func_00283B98(t, (float)I(0x750) * 0.01f);
        }
        idle = 1;
        if (st[0x348] != 0 && I(0x4D8) == 0) {
            idle = 0;
            func_002AA2E8((float *)(st + 0x30C), 0.060000002f, 0.0044f);
        } else {
            if (func_00278E78() == 0 && S(0x274) == 0) {
                u8 *s0;
                float yaw, z;
                if (F(0x30C) > 0.23000002f) {
                    idle = 0;
                    func_002AA2E8((float *)(st + 0x30C), 0.23000002f, 0.0046f);
                }
                I(0x278) = 0;
                func_00282D30(&v70, (object + 0xC0), 0.95f);
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
                vC0.f[0] = func_00283180(yaw) * func_002A7878(0.038000003f, 0.080000006f);
                vC0.f[1] = func_00283198(yaw) * func_002A7878(0.038000003f, 0.080000006f);
                vC0.f[2] = F(0x30C) * 0.5f;
                if (func_002A77E0(func_00283CF0(1.0f / F(0x30C)) - 1) == 0) {
                    if (F(0x30C) >= 0.1f) {
                        func_PAL_L04_00364B90(&vD0, &vC0, 0x40, 0.6f);
                        func_00282D30(&v70, (object + 0xC0), -0.4f);
                        func_00282CC0(&vD0, &vD0, &v70);
                        func_PAL_L04_00364B90(&vD0, &vC0, 0x40, 0.7f);
                        func_00282CC0(&vD0, &vD0, &v70);
                        func_PAL_L04_00364B90(&vD0, &vC0, 0x40, 0.8f);
                        func_PAL_L04_00364B90(&vE0, &vC0, 0x40, 0.6f);
                        func_00282D30(&v70, (object + 0xC0), -0.4f);
                        func_00282CC0(&vE0, &vE0, &v70);
                        func_PAL_L04_00364B90(&vE0, &vC0, 0x40, 0.7f);
                        func_00282CC0(&vE0, &vE0, &v70);
                        func_PAL_L04_00364B90(&vE0, &vC0, 0x40, 0.8f);
                    }
                }
                if (F(0x30C) <= 0.1f && func_002A77E0(2) == 0) {
                    func_00282D30(&v70, (object + 0xC0), 0.5f);
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
                func_002AA3A8((float *)(st + 0x30C), (float *)(st + 0x288), 0.40000004f,
                              D_L04_001B08F0 != 0 ? 0.015840001f : 0.031680003f, 0.72f,
                              D_L04_001B08F0 != 0 ? 0.020000001f : 0.040000003f);
            } else {
                func_002AA2E8((float *)(st + 0x30C), 0.060000002f, 0.004f);
            }
        }
        speed = F(0x30C) + F(0x27C);
    } else {
        speed = 0.0f;
    }
    grip = F(0x30C) * 2.4999998f;
    damping = 0.023040002f;
    if (grip > 1.0f) grip = 1.0f;
    limit = func_002AA140(0.06981318f, I(0x338) != 0 ? 0.019896757f : 0.026179943f, grip);
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
        if (object[0x20] != 3) limit = limit * ((L04_HoverHero *)D_00189E20)->turnScale;
        if (limit < 3.4906592e-05f) limit = 3.4906592e-05f;
        func_002AA898((float *)(object + 0xF8), ((L04_HoverHero *)D_00189E20)->heading, (float *)(st + 0x308), damping, 0.43200004f, limit, 0);
    }
    if (D_L04_001B08F0 != 0) {
        if (I(0x64C) != 0 && I(0x71C) != 0) {
            func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.030303031f);
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
        func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.030303031f);
        func_00282CC0((st + 0x290), (st + 0x290), &v20);
        I(0x71C) = 1;
        dbg = D_001A7CC0;
    } else {
        dbg = D_001A7CC0;
    }
    if (dbg != 0) qcopy(&D_001B9900, &v20);
    func_PAL_L04_00417310(object, st, height, 0.2f, 0.23f, 12.0f, 0.1f);
    if (height > 0.44f) {
        S(0x274) = 1;
        U16(0x276) = U16(0x276) + 1;
    } else {
        if (S(0x274) != 0 && S(0x276) >= 11 && F(0x358) < 0.0f && func_00278E78() != 0) {
            if (S(0x276) >= 38) {
                func_00282D30(&v30, (st + 0x2A0), 0.75f);
                func_00282CD8(&v70, &v30, (object + 0x10));
                v40.q = *(Quad *)(st + 0x2A0);
                v30.f[2] = OF(0x18);
                v40.f[2] = 0.020000001f;
                func_00282D30(&v40, &v40, 0.85f);
                func_PAL_L04_00410488(&v30, &v40, 0, object, F(0x30C));
                func_PAL_L04_00410678(&v30, &v40, 8, 1);
                if (object[0x20] != 3) {
                    SND_STOP(0x328)
                    I(0x328) = func_002E5CF8(4, 4, object);
                    I(0x32C) = 4;
                    I(0x324) = 12;
                }
            }
            if (st[0x349] == 0 && func_00278E78() != 5) {
                float sink;
                if (F(0x358) > -0.05f) F(0x358) = -0.05f;
                sink = F(0x358);
                x = 1.0f - (sink + 0.35f) * 2.857143f;
                if (x > 1.0f) x = 1.0f;
                if (x < 0.0f) x = 0.0f;
                I(0x34C) = (((int)((int)(x * 5.0f) + 15) * 5 + 2) / 6);
                if (x < 0.5f) x = 0.5f;
                st[0x349] = 1;
                F(0x354) = x * 0.06f;
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
    int result = func_PAL_L04_00418180(object, (object + 0x10), (st + 0x290), (st + 0x2A0), &v30, &v50, (st + 0x2B0), &flag, 1, &flag2,
                                   F(0x30C) + F(0x27C), F(0x280), 0.20000002f, F(0x24), F(0x20));
    if (result != 0) {
        if (D_L04_001B08F0 != 0) func_00282D30((st + 0x290), (st + 0x290), 0.85f);
        if (flag2 != 0)
            I(0x70C) = I(0x70C) + 1;
        else
            I(0x70C) = 0;
        switch (result) {
        case 1:
            if (I(0x1DC) != -1) {
                u8 *target = D_L04_001B24DC + (I(0x1DC) << 8);
                float a = func_00283BE0(OF(0xF8), func_00283248(v30.f[0] - OF(0x10), v30.f[1] - OF(0x14)));
                int dir;
                if (a > 0.52359885f && a < 2.617994f) {
                    dir = 3;
                } else {
                    dir = 5;
                    if (a < -0.52359885f && a > -2.617994f) dir = 4;
                }
                if (I(0x36C) != 0 && S(0x34A) == dir) {
                    I(0x36C) = 25;
                } else {
                    I(0x36C) = 25;
                    S(0x34A) = dir;
                    func_PAL_002A7E68(target, dir, 3, 2);
                }
            }
            switch (flag) {
            case 0:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 4) {
                        SND_STOP(0x328)
                        I(0x328) = func_002E5CF8(4, 4, object);
                        I(0x32C) = 4;
                        I(0x324) = 12;
                    } else {
                        I(0x324) = 12;
                    }
                }
                break;
            case 1:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 5) {
                        SND_STOP(0x328)
                        I(0x328) = func_002E5CF8(5, 4, object);
                        I(0x32C) = 5;
                        I(0x324) = 12;
                    } else {
                        I(0x324) = 12;
                    }
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
            func_PAL_L04_00410488(&v30, (Vec *)(st + 0x290), flag, object, F(0x30C));
            break;
        case 2:
            if (I(0x4D8) == 0) {
                if (object[0x20] != 3) {
                    char *tag;
                    Vec *dir;
                    func_L04_0040E248(object, st);
                    ((L04_HoverCfg *)D_001B9540)->f188 = 0x4b;
                    ((L04_HoverCfg *)D_001B9540)->f168 = 0x32;
                    ((L04_HoverCfg *)D_001B9540)->f160 = 0.2f;
                    ((L04_HoverCfg *)D_001B9540)->f180 = 0.1f;
                    tag = D_L04_001A8F20;
                    ((L04_HoverCfg *)D_001B9540)->f16C = 0;
                    func_L00_002D6900(0x1C);
                    func_PAL_L00_003FB330((object + 0x10), 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.666f, 20.0f, 1, 1, 0, 0);
                    func_L00_00322EC8(st + 0x4E0);
                    func_002E5CF8(3, 0, object);
                    object[0xBC] = 6;
                    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
                    *(s16 *)(object + 0x96) = 0x53;
                    func_00282D30(&v50, &v50, func_002A7878(0.1f, 0.2f));
                    dir = &v70;
                    SPAWN(0xB3D, 0.0f, 0.05f)
                    SPAWN(0xB3E, 0.0f, 0.05f)
                    SPAWN(0xB3F, 0.0f, 0.0f)
                    SPAWN(0xB40, 0.0f, 0.05f)
                    SPAWN(0xB40, 0.0f, 0.05f)
                    if (I(0x1DC) != -1) {
                        v90.q = *(Quad *)(object + 0x10);
                        v90.f[2] = v90.f[2] + 0.25f;
                        v80.f[0] = func_00283180(OF(0xF8));
                        v80.f[1] = func_00283198(OF(0xF8));
                        v80.f[2] = 0.0f;
                        func_00282CD8(&vA0, &v80, &v90);
                        if (func_002761F8(&v90, &v80, 2, 0, 0) != 0) {
                            if (func_00278E78() != result) {
                                L04_HoverTarget *hit = (L04_HoverTarget *)D_001BFAC0;
                                float f20;
                                x = func_00283248(hit->v[2], func_00282E20(hit->v));
                                f20 = func_00283B98(func_00283248(hit->v[0], hit->v[1]), 3.1415927f);
                                func_00283C80(func_00283248(v80.f[0], v80.f[1]), f20);
                                if (x > 1.2217306f) height = 0.0f;
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
