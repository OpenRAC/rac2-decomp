/* Second-pass layout/ABI review, 2026-11-03; retained, not linked.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -ffast-math.
 * US check.py: 6632/6736 bytes,0/3 places; frame0xF0.
 * The old isolated16-byte &v30 destination was overrun by the inverse helper. A complete64-byte inverse shares actual later velocity/point/joint storage through a union; all whole-matrix consumers receive that matrix object.
 * Remaining: Per-case hero bases, state5/6 FP expression/branch order and allocation remain; no unchanged register-wording replay.
 * No linked or functional-port qualification; prior measurements follow.
 */
/* Hero-NPC state machine shared by Tabora, Dobbo and Grelbin. Retained
 * reconstruction, not functional-gated. USA v1.01: 6,632/6,736 bytes, 0/3 places
 * (2026-11-01); the earlier source emitted 6,624 bytes.
 * Separate-unit profile: -O2 -G8 -ffunction-sections -frac2-qcopy -ffast-math.
 * The fast-math option is retained from the earlier min.s experiment, not evidence
 * of a correct complete function. Never promote this solely on equal size.
 * Voice records now have their real 0x70-byte stride and byte-sized active flag;
 * case 0 captures the table/index once and passes the missing signed object ID to
 * the diagnostic call. D_0018A15C is an absolute pointer slot, not small data.
 * Remaining: per-case hero-base lifetime, state-5/6 floating-point expression and
 * branch order, missing residual computations, and stack/register allocation.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;

/* $gp-relative tuning constants (retail reads them as one-instruction gp loads). */
extern float D_001AFFD0 __attribute__((sda));
extern float D_001AFFD4 __attribute__((sda));
extern float D_001AFFD8 __attribute__((sda));
extern s32 D_001AFFDC __attribute__((sda));
extern s32 D_001AFFE0 __attribute__((sda));
extern s32 D_001AFFE4 __attribute__((sda));
extern float D_001AFFE8 __attribute__((sda));
extern float D_001AFFF8 __attribute__((sda));
extern float D_001AFFFC __attribute__((sda));
extern float D_001B0000 __attribute__((sda));
extern float D_001B000C __attribute__((sda));
extern float D_001B0010 __attribute__((sda));
extern float D_001B0014 __attribute__((sda));
extern float D_001B0018 __attribute__((sda));
extern float D_001B0070 __attribute__((sda));
extern float D_001B007C __attribute__((sda));
extern s32 D_001B0084 __attribute__((sda));
extern float D_001B0088 __attribute__((sda));
extern float D_001B008C __attribute__((sda));
extern s32 D_001B0090 __attribute__((sda));
extern float D_001B0094 __attribute__((sda));
extern float D_001B0098 __attribute__((sda));
extern float D_001B009C __attribute__((sda));
extern float D_001B00A0 __attribute__((sda));
extern float D_001B00A4 __attribute__((sda));
extern float D_001B00A8 __attribute__((sda));
extern float D_001B00FC __attribute__((sda));
extern float D_001B0100 __attribute__((sda));
extern float D_001B0104 __attribute__((sda));
extern s32 D_001B0108 __attribute__((sda));
extern float D_001B010C __attribute__((sda));
extern float D_001B0124 __attribute__((sda));
extern float D_001B0128 __attribute__((sda));
extern s32 D_001B0130 __attribute__((sda));
extern float D_001B0134 __attribute__((sda));
extern float D_001B0138 __attribute__((sda));
extern float D_001B013C __attribute__((sda));
extern s32 D_001B0140 __attribute__((sda));
extern float D_001B3410 __attribute__((sda));
extern s32 D_001B29DC[];
extern float D_001B2094[];
extern float D_001B2098[];
extern float D_001B3414[];
extern s32 D_00138324[];
extern char D_00189E20[];
extern char D_00189EA0[];
extern char D_001B99C0[];
extern char D_001B9B00[];
extern char D_001A8F20[];
extern char D_001B0148[];
extern char D_001B0168[];
extern char D_001B0180[];
extern u8 D_001A7B0D[];
extern s32 D_0018B650[];
extern s32 D_001B2ACC[];
typedef struct {
    u32 handle;
    u8 active;
    u8 unknown05[0x13];
    void *owner;
    u8 unknown1C[0x54];
} VoiceCDF98;
typedef union {
    u8 bytes[0x1730];
    /* The first stride is the header. States 5/6 inspect a slot without first
     * rejecting -1, so that preceding stride must remain addressable. */
    VoiceCDF98 records[53];
} VoiceStateCDF98;
extern VoiceStateCDF98 D_00188660;
extern void *D_0018A15C[];

extern int func_001163B0(void);
extern void func_0026FEB8(void *, ...);
extern void func_0029FCC0(void *, int, void *);
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283698(void *, void *);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283CE0(int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern void func_002A93B0(void *);
extern void func_002AA800(void *, int, float, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002AF000(void *, float, float, float);
extern int func_002B0C28(int, int, int);
extern int func_002B3868(void *);
extern void *func_002BDCE8(void *, int, void *, int, int, float, float, float, float);
extern void func_002E59F8(int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_002B2BD0(void);
extern void func_L00_002B30E8(void);
extern void func_L00_002D2168(int, int, float);
extern void func_L01_00323310(int, int);
extern int func_L08_002D2ED8(int, int);
extern void func_L08_003CD488(void *, void *);
extern void func_L08_003CD648(void *, void *);
extern void func_L08_003CD6C8(void *, void *);
extern void func_L08_003CD708(void *, void *, float);
extern void func_L08_003CDB38(void *);
extern int func_L08_003CDB78(void *, void *);

#define DI(o) (*(s32 *)(d + (o)))
#define DF(o) (*(float *)(d + (o)))
#define OB(o) (*(u8 *)(obj + (o)))
#define OH(o) (*(u16 *)(obj + (o)))
#define GI(o) (*(s32 *)(D_00189E20 + (o)))
#define GF(o) (*(float *)(D_00189E20 + (o)))
#define GP(o) (*(u8 **)(D_00189E20 + (o)))
#define VOICE(i) (D_00188660.records[(i) + 1])

void func_L08_003CDF98(u8 *obj)
{
    Vec saved;
    union {
        Vec inverse[4];
        struct { Vec velocity, point, joint; } vectors;
    } scratch;
#define v30 scratch.vectors.velocity
#define v40 scratch.vectors.point
#define v50 scratch.vectors.joint
    u8 *d, *p, *a70, *a98, *aA0, *aB0;
    int i, n, id;
    float f, t;

    d = *(u8 **)(obj + 0x68);
    qcopy(&saved, d);
    if (OH(0x96) < 0x7FFD)
        OH(0x96) = OH(0x96) + 1;
    switch (OB(0x20)) {
    case 0:
        if (DI(0x6C) > 0) {
            u8 *table = (u8 *)D_001B29DC[0];
            int offset = DI(0x6C) << 8;
            qcopy(d, table + offset + 0x10);
            qcopy(d + 0x10, table + offset + 0xF0);
            func_L08_003CDB38(obj);
        } else {
            func_0026FEB8(D_001B0148, *(s16 *)(obj + 0xB2));
        }
        DF(8) = DF(8) + D_001AFFD0;
        func_0029FCC0(obj, 8, d + 0x30);
        func_00282CF0(d + 0x30, obj + 0x10, d + 0x30);
        func_00283698(scratch.inverse, obj + 0xC0);
        func_002830C0(d + 0x30, d + 0x30, scratch.inverse);
        DF(0x3C) = 1.0f;
        if (OB(0x43) != 0)
            func_002A7470(obj, 0, 0, 0xA);
        OB(0x30) = 0xFF;
        OB(0x31) = 0;
        *(s16 *)(obj + 0x32) = 0x3FF;
        OH(0x34) = OH(0x34) | 1;
        func_002A7750(obj, 1, -1);
        DI(0x98) = 0;
        DI(0xB0) = 0;
        break;
    case 1:
        if (D_001A7B0D[0] == 0)
            return;
        {
            if (DI(0x6C) < 0) {
                if (func_00282E48(d, D_00189EA0) < D_001AFFD4 && *(s32 *)(D_00189EA0 + 0x2214) != 0x31) {
                    if (OB(0x43) != 0)
                        func_002A7470(obj, 0, 0, 0xA);
                    func_002A7750(obj, 2, -1);
                }
            } else {
                u8 *q = (u8 *)D_0018A15C[0];
                if (q != 0 && *(s16 *)(q + 0xAA) == 0x988 && q == (u8 *)D_001B29DC[0] + (DI(0x6C) << 8)) {
                    if (OB(0x43) != 0)
                        func_002A7470(obj, 0, 0, 0xA);
                    func_002A7750(obj, 2, -1);
                }
            }
        }
        break;
    case 2:
        func_L08_003CD6C8(obj, d);
        if (GP(0x33C) == 0 || *(s16 *)(GP(0x33C) + 0xAA) != 0x988) {
            if (OB(0x43) != 0)
                func_002A7470(obj, 0, 0, 0xA);
            qcopy(d, (u8 *)D_001B29DC[0] + (DI(0x6C) << 8) + 0x10);
            DF(8) = DF(8) + D_001AFFD0;
            func_002A7750(obj, 1, -1);
        }
        n = func_002B0C28(7, 0x279E, 1) != 0;
        if (OB(0x20) == 2 && (D_00138324[0] & 0x40)) {
            if (n != 0 && GI(0x33C) == D_001B29DC[0] + (DI(0x6C) << 8) && GI(0x340) != 0
                && *(s16 *)(D_00189E20 + 0x34E) == 0) {
                u8 *q;
                func_L08_002D2ED8(0x31, 0);
                func_L00_002D2168(0x87, 0, 3.0f);
                *(s32 *)(GP(0x2290) + 0x9C) = -1;
                q = (u8 *)D_001B29DC[0] + (DI(0x6C) << 8);
                func_00282F20(d + 0x20, q + 0xC0, D_001B00FC * 0.016666668f);
                DI(0x50) = D_001B0108;
                DF(0x28) = D_001B0100 * 0.016666668f;
                DF(0x18) = *(float *)(q + 0xF8);
                GP(0x1830) = obj;
                DI(0x9C) = 0;
                func_002A7750(obj, 3, -1);
            }
        }
        break;
    case 3:
        if (func_002B3868(obj) != 0) {
            if (DI(0xBC) != -1) {
                func_0026FEB8(D_001B0168);
                func_L01_00323310(DI(0xBC), DI(0xB8));
            }
            DI(0xB0) = 0x1E;
        } else if (func_00282948(d + 0xB0) != 0) {
            func_002E5DA0(6, 0, obj, 0x988);
            DI(0xB0) = 0xD2;
        }
        if (DI(0x9C) == 0 && !(GF(0xC38) > 10.0f)) {
            DI(0xB4) = 0;
        } else {
            DI(0x9C) = DI(0x9C) | 4;
            func_002AA800(d + 0x14, 0, D_001AFFE8 * 0.017453294f, D_001B0134 * 0.00029088825f);
            if (D_001B0140 != 0)
                func_00282CC0(d, d, d + 0x20);
            DF(0x28) = DF(0x28) - D_001B010C * 0.00027777778f;
            if (DF(0x28) < -(D_001B0104 * 0.016666668f))
                DI(0x9C) = DI(0x9C) | 1;
            if (GI(0xC28) & 2) {
                DI(0x9C) = DI(0x9C) | 2;
                func_L00_002D2168(0x81, 0, 15.0f);
            }
            if (func_00282948(d + 0x50) != 0) {
                if (DI(0x9C) == 7) {
                    if (OH(0x34) & 1) {
                        OH(0x34) = OH(0x34) & 0xFFFE;
                        OB(0x31) = 1;
                        if (OB(0x43) != 1)
                            func_002A7470(obj, 1, 0, 5);
                        func_002E5DA0(0, 0, obj, 0x988);
                    }
                    DI(0x50) = D_001AFFDC;
                    func_L08_002D2ED8(0x31, 0);
                    func_L00_002D2168(0x81, 0, 15.0f);
                    *(s32 *)(GP(0x2290) + 0x9C) = -1;
                    if (D_001B0140 != 0)
                        DF(0x14) = D_001AFFE8 * 0.017453294f;
                    DF(0x54) = 0.06f;
                    *(Quad *)(d + 0x20) = 0;
                    DI(0xA8) = 0;
                    DF(0x58) = DF(8);
                    func_L08_003CD488(d + 0xA8, obj);
                    DF(0x64) = 0.0f;
                    D_001B3410 = D_001B2094[0];
                    D_001B3414[0] = D_001B2098[0];
                    D_001B2094[0] = D_001B00A4;
                    D_001B2098[0] = D_001B00A8;
                    GP(0x1830) = obj;
                    func_002A7750(obj, 5, -1);
                }
            }
            func_L08_003CD648(obj, d);
            DI(0xB4) = 0;
        }
        break;
    case 4:
        if (D_001AFFD8 < func_00282E80(obj + 0x10, D_00189EA0)) {
            if (OB(0x43) != 0)
                func_002A7470(obj, 0, 0, 0xA);
            func_002A7750(obj, 1, -1);
        }
        break;
    case 5:
        if (VOICE(DI(0xAC)).owner != obj || VOICE(DI(0xAC)).active == 0)
            DI(0xAC) = func_002E5DA0(1, 4, obj, 0x988);
        func_L08_003CD488(d + 0xA8, obj);
        DF(0x28) = -func_00283198(DF(0x14)) * DF(0x54);
        t = DF(0x54) * func_00283180(DF(0x14));
        DF(0x20) = t * func_00283180(DF(0x18));
        DF(0x24) = t * func_00283198(DF(0x18));
        if (D_001AFFE0 >= DI(0x50)) {
            if (OH(0x34) & 1) {
                OH(0x34) = OH(0x34) & 0xFFFE;
                OB(0x31) = 1;
                if (OB(0x43) != 1)
                    func_002A7470(obj, 1, 0, 0xA);
            }
            t = func_00283CE0(D_001AFFE0 - DI(0x50));
            t = t / func_00283CE0(D_001AFFE0);
            DF(0x64) = t;
            if (t > 1.0f)
                DF(0x64) = 1.0f;
            else if (t < 0.0f)
                DF(0x64) = 0.0f;
            func_L08_003CD708(obj, d, DF(0x64));
            func_00282D30(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            func_002AF000(&v30, DF(0x54), DF(0x18), -DF(0x14));
            func_00282D30(&v30, &v30, DF(0x64));
            func_00282CC0(d + 0x20, d + 0x20, &v30);
        }
        if (D_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        if (func_L08_003CDB78(obj, &saved) == 0) {
            t = DF(0x54) + D_001AFFFC * 0.00027777778f;
            f = D_001AFFF8 * 0.016666668f;
            DF(0x54) = t;
            if (f < t)
                DF(0x54) = f;
            if (DI(0x50) < D_001AFFDC - D_001AFFE4 && D_001B0140 != 0)
                DF(0x14) = func_00283BE0(DF(0x14), D_001B0000 * 0.00029088825f);
            if (DF(0x14) < 0.0f)
                DF(0x14) = 0.0f;
            if (func_00282948(d + 0x50) != 0) {
                if (OB(0x43) != 2)
                    func_002A7470(obj, 2, 0, 0xA);
                func_L00_002D2168(0x82, 0, 15.0f);
                DF(0x48) = 0.0f;
                DF(0x40) = 0.0f;
                DF(0x44) = -(D_001B0000 * 0.00029088825f);
                func_002A7750(obj, 6, -1);
            }
        }
        if ((OB(0x60) & 2) && OB(0x43) != 2)
            func_002A7470(obj, 2, 0, 0xA);
    tail:
        func_L08_003CD648(obj, d);
        break;
    case 6:
        func_L08_003CD488(d + 0xA8, obj);
        if (VOICE(DI(0xAC)).owner != obj || VOICE(DI(0xAC)).active == 0)
            DI(0xAC) = func_002E5DA0(1, 4, obj, 0x988);
        func_L08_003CD708(obj, d, 1.0f);
        t = DF(0x5C);
        if (t < -0.4f) {
            id = 0x85;
            goto voice;
        }
        id = 0x86;
        if (t > 0.4f) {
        voice:
            if (*(u8 *)(GP(0x2290) + 0x42) != id && *(u8 *)(GP(0x2290) + 0x43) != id) {
                func_L00_002D2168(id, 0, 15.0f);
                func_002E5DA0(2, 0, obj, 0x988);
            }
        } else {
            f = DF(0x44);
            if (D_001B0070 * 0.000041555468f < f) {
                if (*(u8 *)(GP(0x2290) + 0x42) != 0x83 && *(u8 *)(GP(0x2290) + 0x43) != 0x83)
                    func_L00_002D2168(0x83, 0, 25.0f);
            } else if (f < -D_001B0070 * 0.000041555468f) {
                if (*(u8 *)(GP(0x2290) + 0x42) != 0x81 && *(u8 *)(GP(0x2290) + 0x43) != 0x81) {
                    func_L00_002D2168(0x81, 0, 25.0f);
                    if (DI(0xB0) == 0) {
                        func_002E5DA0(3, 0, obj, 0x988);
                        DI(0xB0) = 0x2D;
                    }
                }
            } else if (*(u8 *)(GP(0x2290) + 0x42) != 0x82 && *(u8 *)(GP(0x2290) + 0x43) != 0x82) {
                func_L00_002D2168(0x82, 0, 20.0f);
            }
        }
        {
            float a = DF(8), b = DF(0x58), c = D_001B0014;
            if (!(a - b <= c)) {
                float e = D_001B000C;
                f = ((b - a) + e) / (e - c);
                if (f > 1.0f)
                    f = 1.0f;
                else if (f < 0.0f)
                    f = 0.0f;
                t = D_001B0018 * 0.016666668f;
                t = t + ((1.0f - f) * ((D_001B0010 * 0.016666668f) - t));
                if (DI(0x98) == 0 || t < DF(0x54))
                    DF(0x54) = DF(0x54) + ((t - DF(0x54)) * 0.1f);
                t = D_001B0018 * 0.016666668f;
                if (t < DF(0x54))
                    DF(0x54) = t;
            } else if (DI(0x98) == 0) {
                t = DF(0x54);
                DF(0x54) = t + (((D_001B0018 * 0.016666668f) - t) * 0.1f);
            }
        }
        t = DF(0x64);
        if (t < 1.0f) {
            f = t + D_001B00A0;
            DF(0x64) = f;
            if (f > 1.0f)
                DF(0x64) = 1.0f;
            p = d + 0x20;
            func_002AF000(&v30, DF(0x54), DF(0x18), -DF(0x14));
            func_00282D30(p, p, 1.0f - DF(0x64));
            func_00282D30(&v30, &v30, DF(0x64));
            func_00282CC0(p, p, &v30);
        } else {
            p = d + 0x20;
            func_002AF000(p, DF(0x54), DF(0x18), -DF(0x14));
        }
        if (D_001B0140 != 0)
            func_00282CC0(d, d, p);
        *(float *)(D_001B99C0 + 0x3C8) = *(float *)(D_001B99C0 + 0x3C8)
            + (((DF(0x28) * D_001B007C) - *(float *)(D_001B99C0 + 0x3C8)) * 0.5f);
        if (D_001B000C < DF(8) - DF(0x58)) {
            if (OB(0x43) != 2)
                func_002A7470(obj, 2, 0, 3);
            func_L00_002D2168(0x84, 0, 15.0f);
            t = DF(0x14);
            f = D_001B008C * 0.017453294f;
            DI(0x60) = 0;
            DI(0x50) = D_001B0084;
            if (f < t)
                DF(0x68) = func_00283BE0(f, t) / func_00283CE0(D_001B0084);
            else
                DF(0x68) = 0.0f;
            func_002A7750(obj, 7, -1);
        }
        func_L08_003CD648(obj, d);
        func_L08_003CDB78(obj, &saved);
        if (*(s32 *)(D_00189E20 + 0x2294) != 0x31) {
            if (OB(0x43) != 0)
                func_002A7470(obj, 0, 0, 0xA);
            func_002A7750(obj, 1, -1);
        }
        break;
    case 7:
        func_L08_003CD488(d + 0xA8, obj);
        if (func_00282948(d + 0x50) != 0) {
            DI(0x50) = D_001B0090;
            func_002A7750(obj, 8, -1);
        }
        DF(0x28) = DF(0x28) + (-D_001B0088 * 0.00027777778f);
        func_00282CC0(d, d, d + 0x20);
        DF(0x54) = func_00282DF0(d + 0x20);
        func_00283CE0(DI(0x50));
        func_00283CE0(D_001B0084);
        if (D_001B0140 != 0)
            DF(0x14) = func_00283B98(DF(0x14), DF(0x68));
        func_L08_003CD708(obj, d, 1.0f);
        func_L08_003CDB78(obj, &saved);
        goto tail;
    case 8:
        func_L08_003CD488(d + 0xA8, obj);
        if (D_001B0094 * 0.017453294f < DF(0x14) && DF(8) - DF(0x58) < D_001B000C) {
            func_L00_002D2168(0x82, 0, 15.0f);
            if (OB(0x43) != 2)
                func_002A7470(obj, 2, 0, 0xA);
            DF(0x64) = 0.0f;
            func_002A7750(obj, 6, -1);
        } else {
            func_00282948(d + 0x50);
        }
        DF(0x28) = DF(0x28) + (-D_001B0088 * 0.00027777778f);
        if (D_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        DF(0x54) = func_00282DF0(d + 0x20);
        func_L08_003CD708(obj, d, 1.0f);
        func_L08_003CD648(obj, d);
        func_L08_003CDB78(obj, &saved);
        break;
    case 9:
        func_L08_003CD488(d + 0xA8, obj);
        if (func_002B3868(obj) != 0) {
            if (DI(0xAC) != -1) {
                if (VOICE(DI(0xAC)).owner == obj && VOICE(DI(0xAC)).active != 0)
                    func_002E59F8(DI(0xAC));
            }
            DI(0xAC) = -1;
            func_002E5DA0(4, 0, obj, 0x988);
            DI(0xB0) = 0xF;
        }
        if (D_001B0140 != 0)
            DF(0x18) = func_00283B98(DF(0x18), D_001B0098 * 0.00029088825f);
        DF(0x28) = DF(0x28) + (-D_001B009C * 0.00027777778f);
        if (D_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        func_L08_003CD648(obj, d);
        func_L08_003CDB78(obj, &saved);
        if (DF(0x28) > 0.0f || DF(8) < 12.0f || func_00282DF0(d + 0x20) < 0.016666668f
            || D_001B0130 < (s32)OH(0x96)) {
            func_002ABBB8(obj, D_001A8F20, 0, 0.0f, 0.0f, 0xA, 3, 0x10, 4.0f, 2.0f, 9.0f, 1.0f,
                          -1, 15.0f, 1, 1, 0, -1, 0x810001);
            D_0018B650[0] = 0;
            func_L00_002B30E8();
        }
        break;
    case 10: {
        float dist, lim;
        u8 *home;
        if (DI(0xAC) != -1) {
            if (VOICE(DI(0xAC)).owner == obj && VOICE(DI(0xAC)).active != 0)
                func_002E59F8(DI(0xAC));
        }
        home = d + 0x80;
        DI(0xAC) = -1;
        dist = func_00282E48(d, home);
        lim = dist < D_001B0138 ? dist : D_001B0138;
        if (D_001B0140 != 0) {
            func_002AA800(d + 0x14, 0, 0.0f, D_001B0138 * 0.00029088825f);
            func_002AA800(d + 0x10, 0, 0.0f, D_001B0138 * 0.00029088825f);
        }
        if ((OB(0x60) & 2) && OB(0x42) == 3) {
            if (OB(0x43) != 0)
                func_002A7470(obj, 0, 0, 0xA);
            OB(0x31) = 0;
            OH(0x34) = OH(0x34) | 1;
        }
        if (lim < dist) {
            func_00282CF0(&v30, home, d);
            func_00282F20(&v30, &v30, lim * D_001B0128);
            func_00282D30(d + 0x20, d + 0x20, D_001B0124);
            func_00282CC0(d + 0x20, d + 0x20, &v30);
            if (D_001B0140 != 0)
                func_00282CC0(d, d, d + 0x20);
            goto tail;
        }
        qcopy(d, d + 0x80);
        DF(0x94) = 0.0f;
        if (GI(0xC28) & 2) {
            GP(0x1830) = 0;
            D_001B2094[0] = D_001B3410;
            D_001B2098[0] = D_001B3414[0];
            DI(0x50) = 0;
            func_L08_002D2ED8(0, 1);
            func_L00_002B2BD0();
            if (OB(0x43) != 0)
                func_002A7470(obj, 0, 0, 0xA);
            if (DI(0x6C) > 0) {
                qcopy(d, (u8 *)D_001B29DC[0] + (DI(0x6C) << 8) + 0x10);
                func_L08_003CDB38(obj);
            }
            if (DI(0xC4) != -1) {
                func_0026FEB8(D_001B0180);
                func_L01_00323310(DI(0xC4), DI(0xC0));
            }
            func_002A7750(obj, 1, -1);
        }
        break;
    }
    }
    if (DF(0) < 10.0f) DF(0) = 10.0f;
    if (DF(0) > 1013.0f) DF(0) = 1013.0f;
    if (DF(4) < 10.0f) DF(4) = 10.0f;
    if (DF(4) > 1013.0f) DF(4) = 1013.0f;
    if (DF(8) < 10.0f) DF(8) = 10.0f;
    if (DF(8) > 1013.0f) DF(8) = 1013.0f;
    aB0 = d + 0xB0;
    aA0 = d + 0xA0;
    a98 = d + 0x98;
    if ((u32)(OB(0x20) - 5) < 5) {
        a70 = d + 0x70;
        if (OB(0x31) != 0) {
            if (func_00282E48(obj + 0x10, D_001B9B00) < 80.0f) {
                func_002A93B0(obj);
                OB(0x6F) = 0x4B;
            }
        }
        func_00282D30(&v30, d + 0x20, 0.25f);
        n = 0;
        do {
            f = 0.0f;
            func_0029FCC0(obj, n, &v50);
            do {
                t = 0.0f;
                func_00282D30(&v40, d + 0x20, -f);
                func_00282CC0(&v40, &v40, &v50);
                if (OB(0x20) >= 7)
                    t = 0.0425f;
                p = func_002BDCE8(&v40, 2, &v30, 0x0E7F7F7F, 0, t, 0.5f, 1.0099999f,
                                  func_002A7878(24000.0f, 35000.0f));
                f += 0.2f;
                if (p != 0)
                    *(s32 *)(p + 8) = func_001163B0();
            } while (f < 1.0f);
            n++;
        } while (n < 7);
        i = 3;
        p = a70;
        do {
            id = *p;
            if (id != 0xFF && func_002ACBC8(d, id) != 0
                && *(float *)(D_001B2ACC[0] + (*p << 7) + 0x38) < GF(0x88)) {
                if (OB(0x43) != 3)
                    func_002A7470(obj, 3, 0, 3);
                func_L00_002D2168(0x88, 0, 15.0f);
                qcopy(d + 0x80, (u8 *)D_001B2ACC[0] + (*p << 7) + 0x30);
                DF(0x90) = func_00282E48(D_00189E20 + 0x80, d + 0x80);
                f = 0.06666667f;
                if (func_00282DF0(d + 0x20) > 0.06666667f)
                    f = func_00282DF0(d + 0x20);
                DF(0x94) = f;
                GF(0xC20) = D_001B013C / (DF(0x90) / f);
                func_002A7750(obj, 0xA, -1);
            }
            i--;
            p += 4;
        } while (i >= 0);
    }
    p = aA0;
    i = 0;
    do {
        id = *p;
        if (id != 0 && id != 0xFF && (((DI(0xB4) >> i) ^ 1) & 1)
            && func_002ACBC8(d, id) != 0 && OB(0x20) != 9) {
            func_002E5DA0(5, 0, obj, 0x988);
            DI(0xB4) = DI(0xB4) | (1 << i);
        }
        i++;
        p += 4;
    } while (i < 2);
    func_00282948(a98);
    func_00282948(aB0);
}
