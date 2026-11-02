/* Current retained result, 1 November 2026: 5976/6032 bytes. Restore the known pointer/integer helper
 * returns and remove the empty floating comparison probe, which emitted nothing. The seven-FPR frame,
 * vector lifetimes and dead retail comparison remain unresolved.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G0 -ffunction-sections -g.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* Sonnet first draft (big12 prep), 2026-10-26, for an Opus finish. Starting point: the m2c pass plus
 * the hover-vehicle sibling's idioms (func_L04_00400EE0); structure is a different routine, only helpers match.
 * Unit to test in: src/levels/shared/L04_00414698-x.c, flags -O2 -G0 -ffunction-sections -g
 *   (-g needed: retail has the two nops before div.s). Remove the INCLUDE_ASM line in L04_0040F8F0.c while testing.
 * Places: 04 0x00414698 and 11 0x00404198 (same body). Step 0: one function (one prologue, one jr $ra, no jump table).
 * Numbers (cmp.py on box2, level 04): 5,976 of 6,032 bytes; opcodes equal 1,419/1,508 (difflib); with registers equal 1,003.
 * No twin: nearest matched/unmatched sibling is func_L04_00400EE0 (0.44 opcode similarity), only the tail helpers overlap.
 * Facts learned (keep):
 * - gp scalars: D_L04_001B08F0 = 0x1900($gp) and D_001A7CC0 = -0x7330($gp), both __attribute__((sda)).
 * - D_00189FC0 is D_00189E20+0x1A0 (heading); retail uses both symbol names at different sites.
 * - func_L04_00413A38 has the sibling's signature (8 ptrs, int, int*, 5 floats); here it is passed st+0x2B0 as the 7th arg.
 * - 'if (func_00278E78() != result)' (compares with the switch value kept in a register), not != 2.
 * - switch (flag) bodies must be in order 0,1,2,3 (case 3 last); case 0 and 1 share a cross-jumped tail.
 * - damping = factor * 0.016f is computed before 'if (object[0xBC] == 5)'; limit (func_002AA140) is computed before factor.
 * - 'if (flag2 != 0) ++ else = 0' (then-arm first); the 0x2B0 vector chain is 'S(0x274) == 0' first.
 * Remaining differences (biggest first):
 * 1. Register numbering: retail has object=$s7, st=$s6, pos=$fp and seven saved FPRs ($f20-$f26, frame 0x1A0); ours has
 *    object=$s5, st=$s4 and six FPRs (frame 0x190). $f26 is the 0.0f held through case 2 (func_L04_00407078 args), $f24=0.05f,
 *    $f23/$f22/$f21 = 0.7854/0.0833/1.5708 there. Ours keeps the &v70 pointer alive in $s6 across the heading block; retail
 *    recomputes addiu $sX,$sp,0x70 per block (the vectors of different blocks are separate variables on the same stack slot,
 *    but scoping them (body.scoped variant) packed the stack tighter than retail, so the slots must stay at 0x70.. as here).
 * 2. After func_002AA140 retail recomputes (1.0f - grip) + 1.0f late and holds 0.016f in $f23 from the top; the
 *    func_002AA3A8 constant loads (0.022f/0.011f, 0.0278f/0.0139f) are scheduled before the gp test in retail.
 * 3. The vel pointer: retail has two distinct pseudos for st+0x290 ($s1 in the not-gp arm, $s3 in the gp arm and for the
 *    later calls, 'daddu $s3,$s1' in the else arm); ours has one.
 * 4. Case 2: retail compares 1.2217305f (0x3F9C61AB) with the f21 result of func_00283248(D_001BFAC0[0x48], func_00282E20(..))
 *    right after func_00283C80 and leaves a dead c.lt.s; an empty 'if (f21 > 1.2217305f) {}' is dropped by our GCC, so
 *    5 instructions (mov.s $f21,$f0 and the compare) are missing. The D_001B9540 stores use a different base in retail
 *    (base = &D_001B9540, offsets 0x168/0x188/0x160/0x16C/0x180) than ours (base = &D+0x168).
 * 5. Prologue scheduling (the mov of the pos and the order of sd saves).
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
extern u8 D_00188660[];
extern u8 D_00189E20[];
extern float D_00189FC0;
extern u8 D_001B9540[];
extern u8 D_00189EA0[];
extern u8 D_001BFAC0[];
extern Quad D_001B9900;
extern int D_00138320;
extern int D_001A7CC0 __attribute__((sda));
extern int D_L04_001B08F0 __attribute__((sda));
extern u8 *D_001B24DC;
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
#define I(o) (*(s32 *)(st + (o)))
#define F(o) (*(float *)(st + (o)))
#define S(o) (*(s16 *)(st + (o)))
#define U16(o) (*(u16 *)(st + (o)))
#define OF(o) (*(float *)(object + (o)))
#define HEAD (*(float *)(D_00189E20 + 0x1A0))
#define SND_STOP(field) { int h = I(field); if (h != -1) { u8 *e = D_00188660 + h * 0x70; if (*(u8 **)(e + 0x88) == object && e[0x74] != 0) func_002E59F8(h); } I(field) = -1; }

/* Hover board physics for the rider: steering, speed, landing and crash handling. */
void func_L04_00414698(u8 *object, u8 *st)
{
    Vec v20, v30, v40, v50, start, v70, v80, v90, vA0, vB0, vC0, vD0, vE0, vF0;
    int flag, flag2, idle, dbg;
    float ground, height, limit, speed, grip, factor, damping, x;
    u8 *pos, *vel, *prev, *s2;

    flag = 0;
    start.q = *(Quad *)(object + 0x10);
    ground = func_002A89A8((char *)(object + 0x10), 0, 0.5f);
    height = OF(0x18) - ground;
    if ((func_00278E78() != 0 || S(0x274) != 0) && func_002E59B0(object, I(0x3BC)) != 0) {
        SND_STOP(0x3BC)
    }
    if (object[0x20] == 3) func_L04_004135B8(object, st);
    pos = object + 0x10;
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) {
            func_L00_002A9D38(&v20, st + 0x2C0, 0.12f);
            D_00189FC0 = func_00283B98(*(float *)(D_001B9540 + 0x158),
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
                vD0.q = vB0.q;
                vE0.q = vA0.q;
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
                    func_00282CC0(&vF0, pos, &v70);
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
                float a = 0.022f, b = 0.027777778f;
                if (D_L04_001B08F0 != 0) a = 0.011f;
                if (D_L04_001B08F0 != 0) b = 0.013888889f;
                func_002AA3A8((float *)(st + 0x30C), (float *)(st + 0x288), 0.33333334f, a, 0.5f, b);
            } else {
                func_002AA2E8((float *)(st + 0x30C), 0.050000004f, 0.0027777778f);
            }
        }
        speed = F(0x30C) + F(0x27C);
    } else {
        speed = 0.0f;
    }
    grip = F(0x30C) * 3.0f;
    if (grip > 1.0f) grip = 1.0f;
    x = 0.021816619f;
    if (I(0x338) != 0) x = 0.01658063f;
    limit = func_002AA140(0.05817765f, x, grip);
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
    damping = factor * 0.016f;
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) limit = limit * *(float *)(D_00189E20 + 0x24B8);
        if (limit < 0.000029088826f) limit = 0.000029088826f;
        func_002AA898((float *)(object + 0xF8), HEAD, (float *)(st + 0x308), damping, 0.3f, limit, 0);
    }
    vel = st + 0x290;
    if (D_L04_001B08F0 != 0) {
        if (I(0x64C) != 0 && I(0x71C) != 0) {
            func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
            func_00282CF0(vel, vel, &v20);
            I(0x71C) = 0;
        }
        func_002AF000(v20.f, speed, OF(0xF8), 0.0f);
        func_00282D30(&v20, &v20, 0.025f);
        func_00282CC0(vel, vel, &v20);
        func_002AC9F8((float *)vel, speed);
    } else {
        func_002AF000((float *)vel, speed, OF(0xF8), 0.0f);
        func_002AC9F8((float *)vel, speed);
        v20.q = *(Quad *)(object + 0xD0);
        func_00282F20(v20.f, v20.f, F(0x30C) * (F(0x308) * -1.75f));
        func_00282CC0(vel, vel, &v20);
    }
    dbg = D_001A7CC0;
    if (func_00282948(st + 0x64C) == 0) {
        func_00282D30(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
        func_00282CC0(vel, vel, &v20);
        I(0x71C) = 1;
        dbg = D_001A7CC0;
    }
    if (dbg != 0) D_001B9900 = v20.q;
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
                func_00282CD8(&v70, &v30, pos);
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
        s2 = st + 0x2B0;
        OF(0xF4) = OF(0xF4) + F(0x354);
        func_00282948(st + 0x34C);
        if (I(0x34C) == 0) st[0x349] = 0;
    } else if (S(0x274) == 0) {
        s2 = st + 0x2B0;
        func_00282F20((float *)s2, D_001BFB00, 1.0f);
        func_L04_00347AB8(object + 0xC0, object + 0xF0, st + 0x304, s2, 0.03f, 0.3f, 0.0f);
    } else {
        s2 = st + 0x2B0;
        func_002AF000((float *)s2, 1.0f, func_00283B98(OF(0xF8), 3.1415927f), 0.99483776f);
        func_L04_00347AB8(object + 0xC0, object + 0xF0, st + 0x304, s2, 0.03f, 0.3f, 0.0f);
    }
    OF(0xF0) = x;
    func_L04_00412E38(object, st, 0.15f, 0.004f);
    *(Quad *)(st + 0x2A0) = *(Quad *)(st + 0x290);
    F(0x358) = F(0x2A8);
    {
    int result = func_L04_00413A38(object, pos, vel, prev, &v30, &v50, s2, &flag, 1, &flag2,
                                   F(0x30C) + F(0x27C), F(0x280), 0.16666667f, F(0x24), F(0x20));
    if (result != 0) {
        if (D_L04_001B08F0 != 0) func_00282D30(vel, vel, 0.85f);
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
            func_L04_0040BED0(&v30, (Vec *)vel, flag, object, F(0x30C));
            break;
        case 2:
            if (I(0x4D8) == 0) {
                if (object[0x20] != 3) {
                    float r;
                    func_L04_0040E248(object, st);
                    *(int *)(D_001B9540 + 0x168) = 0x3C;
                    *(int *)(D_001B9540 + 0x188) = 0x5A;
                    *(float *)(D_001B9540 + 0x160) = 0.2f;
                    *(int *)(D_001B9540 + 0x16C) = 0;
                    *(float *)(D_001B9540 + 0x180) = 0.1f;
                    func_L00_002D6900(0x1C);
                    func_0032C700(pos, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.666f, 20.0f, 1, 1, 0, 0);
                    func_L00_00322EC8(st + 0x4E0);
                    func_002E5CF8(3, 0, object);
                    object[0xBC] = 6;
                    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
                    *(s16 *)(object + 0x96) = 0x64;
                    func_00282D30(&v50, &v50, func_002A7878(0.1f, 0.2f));
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3D, (Vec *)pos, object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3E, (Vec *)pos, object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB3F, (Vec *)pos, object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.0f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB40, (Vec *)pos, object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
                    r = func_002A7940();
                    func_002AF000(v70.f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f));
                    func_00282CD8(&v80, &v70, &v50);
                    func_L04_00407078(object, 0xB40, (Vec *)pos, object + 0xF0, 0, 0, &v70, D_L04_001A8F20, D_L04_001A8F20, 0.0f, 0.05f);
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
    func_00282CF0(&v20, &start, pos);
    v20.i[2] = 0;
    F(0x280) = func_00282DF0(&v20);
    if (F(0x280) < 0.01f) I(0x750) = I(0x750) + 1;
    {
        Quad q = *(Quad *)pos;
        *(Quad *)D_00189EA0 = q;
        *(Quad *)(D_00189EA0 + 0x10) = *(Quad *)(object + 0xF0);
        func_L04_002DAD10(q);
    }
}
