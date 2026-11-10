/* func_PAL_L08_003D1E50: the hero-NPC state machine shared by Tabora, Dobbo and Grelbin
 * (levels 08, 09, 19), dispatched on moby byte 0x20 over the NPC block at moby+0x68.
 * Own unit: -G8 for the $gp tuning constants, -g for the nop pairs before div.s,
 * -frac2-qcopy for the 16-byte copies, -ffast-math for case 10's min.s.
 * Nothing reads the clamped ratio in case 7: retail still has its div.s and c.lt.s.
 * The PAL copy of func_L08_003CDF98: the same C with PAL's 50 Hz scales and values, the
 * animation changes going through SetAnimation (its one-insn compare sets gcse's table
 * size, which orders the spill slots at sp+0x70..0x7C).
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;

/* $gp-relative tuning constants (retail reads them as one-instruction gp loads). */
extern float D_L08_001AFFD0 __attribute__((sda));
extern float D_L08_001AFFD4 __attribute__((sda));
extern float D_L08_001AFFD8 __attribute__((sda));
extern s32 D_L08_001AFFDC __attribute__((sda));
extern s32 D_L08_001AFFE0 __attribute__((sda));
extern s32 D_L08_001AFFE4 __attribute__((sda));
extern float D_L08_001AFFE8 __attribute__((sda));
extern float D_L08_001AFFF8 __attribute__((sda));
extern float D_L08_001AFFFC __attribute__((sda));
extern float D_L08_001B0000 __attribute__((sda));
extern float D_L08_001B000C __attribute__((sda));
extern float D_L08_001B0010 __attribute__((sda));
extern float D_L08_001B0014 __attribute__((sda));
extern float D_L08_001B0018 __attribute__((sda));
extern float D_L08_001B0070 __attribute__((sda));
extern float D_L08_001B007C __attribute__((sda));
extern s32 D_L08_001B0084 __attribute__((sda));
extern float D_L08_001B0088 __attribute__((sda));
extern float D_L08_001B008C __attribute__((sda));
extern s32 D_L08_001B0090 __attribute__((sda));
extern float D_L08_001B0094 __attribute__((sda));
extern float D_L08_001B0098 __attribute__((sda));
extern float D_L08_001B009C __attribute__((sda));
extern float D_L08_001B00A0 __attribute__((sda));
extern float D_L08_001B00A4 __attribute__((sda));
extern float D_L08_001B00A8 __attribute__((sda));
extern float D_L08_001B00FC __attribute__((sda));
extern float D_L08_001B0100 __attribute__((sda));
extern float D_L08_001B0104 __attribute__((sda));
extern s32 D_L08_001B0108 __attribute__((sda));
extern float D_L08_001B010C __attribute__((sda));
extern float D_L08_001B0124 __attribute__((sda));
extern float D_L08_001B0128 __attribute__((sda));
extern s32 D_L08_001B0130 __attribute__((sda));
extern float D_L08_001B0134 __attribute__((sda));
extern float D_L08_001B0138 __attribute__((sda));
extern float D_L08_001B013C __attribute__((sda));
extern s32 D_L08_001B0140 __attribute__((sda));
extern float D_L08_001B3410;
typedef struct { u8 bytes[0x100]; } HeroCDF98;
extern HeroCDF98 *D_L08_001B29DC;
extern float D_L08_001B2094;
extern float D_L08_001B2098;
extern float D_L08_001B3414;
extern s32 D_00138324[];
typedef struct { float f[0x100]; } StateCDF98;
extern StateCDF98 D_L08_001B99C0;
extern char D_L08_001B9B00[];
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char D_L08_001B0148[];
extern char D_L08_001B0168[];
extern char D_L08_001B0180[];
extern u8 D_001A7B0D;
extern s32 D_0018B650[];
typedef struct { u8 bytes[0x80]; } TargetCDF98;
extern TargetCDF98 *D_L08_001B2ACC;
typedef struct {
    u32 handle;
    u8 active;
    u8 unknown05[0x13];
    void *owner;
    u8 unknown1C[0x54];
} VoiceCDF98;
typedef struct {
    u8 header[0x70];
    VoiceCDF98 voice;
} VoiceSlotCDF98;
extern u8 D_00188660[];
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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern void func_002A93B0(void *);
extern void func_002AA800(void *, int, float, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002AF000(void *, float, float, float);
extern int func_002B0C28(int, int, int);
extern int func_002B3868(void *);
/* Interleaved: each register bank keeps the order of the definition in 002BDCE8.c. */
extern void *func_PAL_002BE9A8(void *, int, void *, float, float, int, int, float, float);
extern void func_002E59F8(int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_002B2BD0(void);
extern void func_PAL_L00_002B3000(void);
extern void func_PAL_L00_002D2668(int, int, float);
extern void func_L01_00323310(int, int);
extern int func_PAL_L08_002D3078(int, int);
extern void func_PAL_L08_003D12C0(void *, void *);
extern void func_L08_003CD648(void *, void *);
extern void func_L08_003CD6C8(void *, void *);
extern void func_PAL_L08_003D1540(void *, void *, float);
extern void func_L08_003CDB38(void *);
extern int func_PAL_L08_003D1A30(void *, void *);

typedef struct {
    u8 unk0[0x80];
    float pos[4];        /* 0x80 */
    u8 unk90[0x33C - 0x90];
    u8 *target;          /* 0x33C */
    s32 unk340;
    u8 unk344[0x34E - 0x344];
    s16 unk34E;
    u8 unk350[0xC20 - 0x350];
    float unkC20;
    u8 unkC24[0xC28 - 0xC24];
    s32 unkC28;
    u8 unkC2C[0xC38 - 0xC2C];
    float unkC38;
    u8 unkC3C[0x1830 - 0xC3C];
    u8 *unk1830;
    u8 unk1834[0x2290 - 0x1834];
    u8 *unk2290;
    s32 unk2294;
} PlayerCDF98;
extern PlayerCDF98 D_00189E20;
#define DI(o) (((s32 *)d)[(o) / 4])
#define DF(o) (((float *)d)[(o) / 4])
#define OB(o) (*(u8 *)(obj + (o)))
static __inline__ void SetAnimation(u8 *p, s32 animation, s32 mode, s32 blend)
{
    if (p[0x43] != animation) func_PAL_002A7E68(p, animation, mode, blend);
}
#define OH(o) (((u16 *)obj)[(o) / 2])

void func_PAL_L08_003D1E50(u8 *obj)
{
    Vec saved;
    union {
        Vec inverse[4];
        struct { Vec velocity, point, joint; } v;
    } scratch;
    u8 *d, *p;
    int i, n, id;
    float t;

    d = *(u8 **)(obj + 0x68);
    qcopy(&saved, d);
    if (OH(0x96) < 0x7FFD)
        OH(0x96) = OH(0x96) + 1;
    switch (OB(0x20)) {
    case 0:
        id = DI(0x6C);
        if (id > 0) {
            HeroCDF98 *table = D_L08_001B29DC;
            qcopy(d, table[id].bytes + 0x10);
            qcopy(d + 0x10, table[id].bytes + 0xF0);
            func_L08_003CDB38(obj);
        } else {
            func_0026FEB8(D_L08_001B0148, *(s16 *)(obj + 0xB2));
        }
        DF(8) = DF(8) + D_L08_001AFFD0;
        func_0029FCC0(obj, 8, d + 0x30);
        func_00282CF0(d + 0x30, obj + 0x10, d + 0x30);
        func_00283698(scratch.inverse, obj + 0xC0);
        func_002830C0(d + 0x30, d + 0x30, scratch.inverse);
        DF(0x3C) = 1.0f;
        SetAnimation(obj, 0, 0, 0xA);
        OB(0x30) = 0xFF;
        OB(0x31) = 0;
        *(s16 *)(obj + 0x32) = 0x3FF;
        OH(0x34) = OH(0x34) | 1;
        func_002A7750(obj, 1, -1);
        DI(0x98) = 0;
        DI(0xB0) = 0;
        break;
    case 1:
        if (D_001A7B0D == 0)
            return;
        {
            if (DI(0x6C) < 0) {
                if (func_00282E48(d, D_00189E20.pos) < D_L08_001AFFD4 && D_00189E20.unk2294 != 0x31) {
                    SetAnimation(obj, 0, 0, 0xA);
                    func_002A7750(obj, 2, -1);
                }
            } else {
                u8 *q = (u8 *)D_0018A15C[0];
                if (q != 0 && *(s16 *)(q + 0xAA) == 0x988 && q == D_L08_001B29DC[DI(0x6C)].bytes) {
                    SetAnimation(obj, 0, 0, 0xA);
                    func_002A7750(obj, 2, -1);
                }
            }
        }
        break;
    case 2: {
        int ok;
        func_L08_003CD6C8(obj, d);
        if (D_00189E20.target == 0 || *(s16 *)(D_00189E20.target + 0xAA) != 0x988) {
            SetAnimation(obj, 0, 0, 0xA);
            qcopy(d, D_L08_001B29DC[DI(0x6C)].bytes + 0x10);
            DF(8) = DF(8) + D_L08_001AFFD0;
            func_002A7750(obj, 1, -1);
        }
        ok = func_002B0C28(7, 0x12f0, 1) != 0;
        if (OB(0x20) == 2 && (D_00138324[0] & 0x40)) {
            if (ok && D_00189E20.target == D_L08_001B29DC[DI(0x6C)].bytes && D_00189E20.unk340 != 0
                && D_00189E20.unk34E == 0) {
                u8 *q;
                func_PAL_L08_002D3078(0x31, 0);
                func_PAL_L00_002D2668(0x87, 0, 3.0f);
                ((s32 *)D_00189E20.unk2290)[0x9C / 4] = -1;
                q = D_L08_001B29DC[DI(0x6C)].bytes;
                func_00282F20(d + 0x20, q + 0xC0, D_L08_001B00FC * 0.020000001f);
                DF(0x28) = D_L08_001B0100 * 0.020000001f;
                DI(0x50) = ((s32)(D_L08_001B0108) * 5 + 2) / 6;
                DF(0x18) = *(float *)(q + 0xF8);
                D_00189E20.unk1830 = obj;
                DI(0x9C) = 0;
                func_002A7750(obj, 3, -1);
            }
        }
        break;
    }
    case 3: {
        if (func_002B3868(obj) != 0) {
            if (DI(0xBC) != -1) {
                func_0026FEB8(D_L08_001B0168);
                func_L01_00323310(DI(0xBC), DI(0xB8));
            }
            DI(0xB0) = 0x19;
        } else if (func_00282948(d + 0xB0) != 0) {
            func_002E5DA0(6, 0, obj, 0x988);
            DI(0xB0) = 0xaf;
        }
        if (DI(0x9C) != 0 || D_00189E20.unkC38 > 10.0f) {
            DI(0x9C) = DI(0x9C) | 4;
            func_002AA800(d + 0x14, 0, D_L08_001AFFE8 * 0.017453294f, D_L08_001B0134 * 0.0003490659f);
            if (D_L08_001B0140 != 0)
                func_00282CC0(d, d, d + 0x20);
            DF(0x28) = DF(0x28) - D_L08_001B010C * 0.00040000002f;
            if (DF(0x28) < -(D_L08_001B0104 * 0.020000001f))
                DI(0x9C) = DI(0x9C) | 1;
            if (D_00189E20.unkC28 & 2) {
                DI(0x9C) = DI(0x9C) | 2;
                func_PAL_L00_002D2668(0x81, 0, 12.0f);
            }
            if (func_00282948(d + 0x50) != 0) {
                if (DI(0x9C) == 7) {
                    if (OH(0x34) & 1) {
                        OH(0x34) = OH(0x34) & 0xFFFE;
                        OB(0x31) = 1;
                        SetAnimation(obj, 1, 0, 5);
                        func_002E5DA0(0, 0, obj, 0x988);
                    }
                    DI(0x50) = (((s32)(D_L08_001AFFDC) * 5 + 2) / 6);
                    func_PAL_L08_002D3078(0x31, 0);
                    func_PAL_L00_002D2668(0x81, 0, 12.0f);
                    ((s32 *)D_00189E20.unk2290)[0x9C / 4] = -1;
                    if (D_L08_001B0140 != 0)
                        DF(0x14) = D_L08_001AFFE8 * 0.017453294f;
                    DF(0x54) = 0.07200001f;
                    qzero_nc(d + 0x20);
                    DI(0xA8) = 0;
                    DF(0x58) = DF(8);
                    func_PAL_L08_003D12C0(d + 0xA8, obj);
                    DF(0x64) = 0.0f;
                    D_L08_001B3410 = D_L08_001B2094;
                    D_L08_001B3414 = D_L08_001B2098;
                    D_L08_001B2094 = D_L08_001B00A4;
                    D_L08_001B2098 = D_L08_001B00A8;
                    D_00189E20.unk1830 = obj;
                    func_002A7750(obj, 5, -1);
                }
            }
            func_L08_003CD648(obj, d);
        }
        DI(0xB4) = 0;
        break;
    }
    case 4:
        if (D_L08_001AFFD8 < func_00282E80(obj + 0x10, D_00189E20.pos)) {
            SetAnimation(obj, 0, 0, 0xA);
            func_002A7750(obj, 1, -1);
        }
        break;
    case 5: {
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = func_002E5DA0(1, 4, obj, 0x988);
        }
        func_PAL_L08_003D12C0(d + 0xA8, obj);
        DF(0x28) = -func_00283198(DF(0x14)) * DF(0x54);
        {
            float c = DF(0x54) * func_00283180(DF(0x14));
            DF(0x20) = c * func_00283180(DF(0x18));
            DF(0x24) = c * func_00283198(DF(0x18));
        }
        if ((((s32)(D_L08_001AFFE0) * 5 + 2) / 6) >= DI(0x50)) {
            if (OH(0x34) & 1) {
                OH(0x34) = OH(0x34) & 0xFFFE;
                OB(0x31) = 1;
                SetAnimation(obj, 1, 0, 0xA);
            }
            {
                float r = func_00283CE0((((s32)(D_L08_001AFFE0) * 5 + 2) / 6) - DI(0x50)) / func_00283CE0(D_L08_001AFFE0);
                DF(0x64) = r;
                if (r > 1.0f)
                    DF(0x64) = 1.0f;
                else if (r < 0.0f)
                    DF(0x64) = 0.0f;
            }
            func_PAL_L08_003D1540(obj, d, DF(0x64));
            func_00282D30(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            func_002AF000(&scratch.v.velocity, DF(0x54), DF(0x18), -DF(0x14));
            func_00282D30(&scratch.v.velocity, &scratch.v.velocity, DF(0x64));
            func_00282CC0(d + 0x20, d + 0x20, &scratch.v.velocity);
        }
        if (D_L08_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        if (func_PAL_L08_003D1A30(obj, &saved) == 0) {
            float sp = DF(0x54) + D_L08_001AFFFC * 0.00040000002f;
            float top = D_L08_001AFFF8 * 0.020000001f;
            float rate;
            DF(0x54) = sp;
            if (top < sp)
                DF(0x54) = top;
            rate = D_L08_001B0000 * 0.0003490659f;
            if (DI(0x50) < ((s32)(D_L08_001AFFDC) * 5 + 2) / 6 - ((s32)(D_L08_001AFFE4) * 5 + 2) / 6 && D_L08_001B0140 != 0)
                DF(0x14) = func_00283BE0(DF(0x14), rate);
            if (DF(0x14) < 0.0f)
                DF(0x14) = 0.0f;
            if (func_00282948(d + 0x50) != 0) {
                SetAnimation(obj, 2, 0, 0xA);
                func_PAL_L00_002D2668(0x82, 0, 12.0f);
                DF(0x40) = 0.0f;
                DF(0x48) = 0.0f;
                DF(0x44) = -(D_L08_001B0000 * 0.0003490659f);
                func_002A7750(obj, 6, -1);
            }
        }
        if (OB(0x60) & 2)
            SetAnimation(obj, 2, 0, 0xA);
        func_L08_003CD648(obj, d);
        break;
    }
    case 6: {
        float t;
        func_PAL_L08_003D12C0(d + 0xA8, obj);
        {
            VoiceSlotCDF98 *slot = (VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70);
            if (slot->voice.owner != obj || slot->voice.active == 0)
                DI(0xAC) = func_002E5DA0(1, 4, obj, 0x988);
        }
        func_PAL_L08_003D1540(obj, d, 1.0f);
        t = DF(0x5C);
        if (t < -0.4f) {
            if (*(u8 *)(D_00189E20.unk2290 + 0x42) != 0x85 && *(u8 *)(D_00189E20.unk2290 + 0x43) != 0x85) {
                func_PAL_L00_002D2668(0x85, 0, 12.0f);
                func_002E5DA0(2, 0, obj, 0x988);
            }
        } else if (t > 0.4f) {
            if (*(u8 *)(D_00189E20.unk2290 + 0x42) != 0x86 && *(u8 *)(D_00189E20.unk2290 + 0x43) != 0x86) {
                func_PAL_L00_002D2668(0x86, 0, 12.0f);
                func_002E5DA0(2, 0, obj, 0x988);
            }
        } else {
            if (D_L08_001B0070 * 4.986656e-05f < DF(0x44)) {
                if (*(u8 *)(D_00189E20.unk2290 + 0x42) != 0x83 && *(u8 *)(D_00189E20.unk2290 + 0x43) != 0x83)
                    func_PAL_L00_002D2668(0x83, 0, 21.0f);
            } else if (DF(0x44) < -D_L08_001B0070 * 4.986656e-05f) {
                if (*(u8 *)(D_00189E20.unk2290 + 0x42) != 0x81 && *(u8 *)(D_00189E20.unk2290 + 0x43) != 0x81) {
                    func_PAL_L00_002D2668(0x81, 0, 21.0f);
                    if (DI(0xB0) == 0) {
                        func_002E5DA0(3, 0, obj, 0x988);
                        DI(0xB0) = 0x25;
                    }
                }
            } else if (*(u8 *)(D_00189E20.unk2290 + 0x42) != 0x82 && *(u8 *)(D_00189E20.unk2290 + 0x43) != 0x82) {
                func_PAL_L00_002D2668(0x82, 0, 17.0f);
            }
        }
        {
            float a = DF(8), b = DF(0x58), c = D_L08_001B0014;
            if (a - b <= c) {
                if (DI(0x98) == 0) {
                    float s = DF(0x54);
                    DF(0x54) = s + (((D_L08_001B0018 * 0.020000001f) - s) * 0.14400001f);
                }
            } else {
                float e = D_L08_001B000C;
                float k = b - a;
                float lo, sp, top;
                k += e;
                k /= e - c;
                if (k > 1.0f)
                    k = 1.0f;
                else if (k < 0.0f)
                    k = 0.0f;
                lo = D_L08_001B0018 * 0.020000001f;
                k = 1.0f - k;
                sp = lo + (k * ((D_L08_001B0010 * 0.020000001f) - lo));
                if (DI(0x98) == 0 || sp < DF(0x54))
                    DF(0x54) = DF(0x54) + ((sp - DF(0x54)) * 0.14400001f);
                top = D_L08_001B0018 * 0.020000001f;
                if (top < DF(0x54))
                    DF(0x54) = top;
            }
        }
        if (DF(0x64) < 1.0f) {
            float w = DF(0x64) + D_L08_001B00A0 * 1.2f;
            DF(0x64) = w;
            if (w > 1.0f)
                DF(0x64) = 1.0f;
            func_002AF000(&scratch.v.velocity, DF(0x54), DF(0x18), -DF(0x14));
            func_00282D30(d + 0x20, d + 0x20, 1.0f - DF(0x64));
            func_00282D30(&scratch.v.velocity, &scratch.v.velocity, DF(0x64));
            func_00282CC0(d + 0x20, d + 0x20, &scratch.v.velocity);
        } else {
            func_002AF000(d + 0x20, DF(0x54), DF(0x18), -DF(0x14));
        }
        if (D_L08_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        D_L08_001B99C0.f[0x3C8 / 4] = D_L08_001B99C0.f[0x3C8 / 4]
            + (((DF(0x28) * D_L08_001B007C) - D_L08_001B99C0.f[0x3C8 / 4]) * 0.72f);
        if (D_L08_001B000C < DF(8) - DF(0x58)) {
            float ang, lim;
            SetAnimation(obj, 2, 0, 3);
            func_PAL_L00_002D2668(0x84, 0, 12.0f);
            ang = DF(0x14);
            lim = D_L08_001B008C * 0.017453294f;
            DI(0x60) = 0;
            DI(0x50) = D_L08_001B0084;
            if (lim < ang)
                DF(0x68) = func_00283BE0(lim, ang) / func_00283CE0(D_L08_001B0084);
            else
                DF(0x68) = 0.0f;
            func_002A7750(obj, 7, -1);
        }
        func_L08_003CD648(obj, d);
        func_PAL_L08_003D1A30(obj, &saved);
        if (D_00189E20.unk2294 != 0x31)
            func_002A7750(obj, 1, -1);
        break;
    }
    case 7: {
        func_PAL_L08_003D12C0(d + 0xA8, obj);
        if (func_00282948(d + 0x50) != 0) {
            DI(0x50) = D_L08_001B0090;
            func_002A7750(obj, 8, -1);
        }
        DF(0x28) = DF(0x28) + (-D_L08_001B0088 * 0.00040000002f);
        func_00282CC0(d, d, d + 0x20);
        DF(0x54) = func_00282DF0(d + 0x20);
        t = func_00283CE0(DI(0x50)) / func_00283CE0(D_L08_001B0084);
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        if (D_L08_001B0140 != 0)
            DF(0x14) = func_00283B98(DF(0x14), DF(0x68));
        func_PAL_L08_003D1540(obj, d, 1.0f);
        func_PAL_L08_003D1A30(obj, &saved);
        func_L08_003CD648(obj, d);
        break;
    }
    case 8: {
        func_PAL_L08_003D12C0(d + 0xA8, obj);
        if (D_L08_001B0094 * 0.017453294f < DF(0x14) && DF(8) - DF(0x58) < D_L08_001B000C) {
            func_PAL_L00_002D2668(0x82, 0, 12.0f);
            SetAnimation(obj, 2, 0, 0xA);
            DF(0x64) = 0.0f;
            func_002A7750(obj, 6, -1);
        } else {
            func_00282948(d + 0x50);
        }
        DF(0x28) = DF(0x28) + (-D_L08_001B0088 * 0.00040000002f);
        if (D_L08_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        DF(0x54) = func_00282DF0(d + 0x20);
        func_PAL_L08_003D1540(obj, d, 1.0f);
        func_L08_003CD648(obj, d);
        func_PAL_L08_003D1A30(obj, &saved);
        break;
    }
    case 9: {
        func_PAL_L08_003D12C0(d + 0xA8, obj);
        if (func_002B3868(obj) != 0) {
            if (DI(0xAC) != -1) {
                if (((VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70))->voice.active != 0)
                    func_002E59F8(DI(0xAC));
            }
            DI(0xAC) = -1;
            func_002E5DA0(4, 0, obj, 0x988);
            DI(0xB0) = 0xc;
        }
        if (D_L08_001B0140 != 0)
            DF(0x18) = func_00283B98(DF(0x18), D_L08_001B0098 * 0.0003490659f);
        DF(0x28) = DF(0x28) + (-D_L08_001B009C * 0.00040000002f);
        if (D_L08_001B0140 != 0)
            func_00282CC0(d, d, d + 0x20);
        func_L08_003CD648(obj, d);
        func_PAL_L08_003D1A30(obj, &saved);
        if (DF(0x28) > 0.0f || DF(8) < 12.0f || func_00282DF0(d + 0x20) < 0.020000001f
            || (s32)OH(0x96) > ((s32)(D_L08_001B0130) * 5 + 2) / 6) {
            func_PAL_002AC718(obj, D_L08_001A8F20, 0, 0.0f, 0.0f, 0xA, 3, 0x10, 4.0f, 2.0f, 9.0f, 1.0f,
                          -1, 15.0f, 1, 1, -1, 0, 0x810001);
            D_0018B650[0] = 0;
            func_PAL_L00_002B3000();
        }
        break;
    }
    case 10: {
        float dist, lim;
        if (DI(0xAC) != -1) {
            if (((VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70))->voice.owner == obj
                    && ((VoiceSlotCDF98 *)(D_00188660 + DI(0xAC) * 0x70))->voice.active != 0)
                func_002E59F8(DI(0xAC));
        }
        DI(0xAC) = -1;
        dist = func_00282E48(d, d + 0x80);
        lim = DF(0x94) < dist ? DF(0x94) : dist;
        if (D_L08_001B0140 != 0) {
            func_002AA800(d + 0x14, 0, 0.0f, D_L08_001B0138 * 0.0003490659f);
            func_002AA800(d + 0x10, 0, 0.0f, D_L08_001B0138 * 0.0003490659f);
        }
        if ((OB(0x60) & 2) && OB(0x42) == 3) {
            SetAnimation(obj, 0, 0, 0xA);
            OB(0x31) = 0;
            OH(0x34) = OH(0x34) | 1;
        }
        if (lim < dist) {
            func_00282CF0(&scratch.v.velocity, d + 0x80, d);
            func_00282F20(&scratch.v.velocity, &scratch.v.velocity, lim * D_L08_001B0128);
            func_00282D30(d + 0x20, d + 0x20, D_L08_001B0124);
            func_00282CC0(d + 0x20, d + 0x20, &scratch.v.velocity);
            if (D_L08_001B0140 != 0)
                func_00282CC0(d, d, d + 0x20);
            func_L08_003CD648(obj, d);
            break;
        }
        qcopy(d, d + 0x80);
        DF(0x94) = 0.0f;
        if (D_00189E20.unkC28 & 2) {
            D_00189E20.unk1830 = 0;
            D_L08_001B2094 = D_L08_001B3410;
            D_L08_001B2098 = D_L08_001B3414;
            DI(0x50) = 0;
            func_PAL_L08_002D3078(0, 1);
            func_L00_002B2BD0();
            SetAnimation(obj, 0, 0, 0xA);
            if (DI(0x6C) > 0) {
                qcopy(d, D_L08_001B29DC[DI(0x6C)].bytes + 0x10);
                func_L08_003CDB38(obj);
            }
            if (DI(0xC4) != -1) {
                func_0026FEB8(D_L08_001B0180);
                func_L01_00323310(DI(0xC4), DI(0xC0));
            }
            func_002A7750(obj, 1, -1);
        }
        break;
    }
    }
    {
        float f;
        s32 *slot;
        if (DF(0) < 10.0f) DF(0) = 10.0f;
        if (DF(0) > 1013.0f) DF(0) = 1013.0f;
        if (DF(4) < 10.0f) DF(4) = 10.0f;
        if (DF(4) > 1013.0f) DF(4) = 1013.0f;
        if (DF(8) < 10.0f) DF(8) = 10.0f;
        if (DF(8) > 1013.0f) DF(8) = 1013.0f;
        if ((u32)(OB(0x20) - 5) < 5) {
            if (OB(0x31) != 0) {
                if (func_00282E48(obj + 0x10, D_L08_001B9B00) < 80.0f) {
                    func_002A93B0(obj);
                    OB(0x6F) = 0x4B;
                }
            }
            func_00282D30(&scratch.v.velocity, d + 0x20, 0.25f);
            for (n = 0; n < 7; n++) {
                func_0029FCC0(obj, n, &scratch.v.joint);
                for (f = 0.0f; f < 1.0f; f += 0.2f) {
                    func_00282D30(&scratch.v.point, d + 0x20, -f);
                    func_00282CC0(&scratch.v.point, &scratch.v.point, &scratch.v.joint);
                    t = 0.0f;
                    if (OB(0x20) >= 7)
                        t = 0.07f;
                    p = func_PAL_002BE9A8(&scratch.v.point, 2, &scratch.v.velocity, t, 0.5f, 0x0E7F7F7F, 0, 1.01f,
                                      func_002A7878(24000.0f, 35000.0f));
                    if (p != 0)
                        p[8] = func_001163B0();
                }
            }
            slot = (s32 *)(d + 0x70);
            for (i = 0; i < 4; i++) {
                if (slot[i] != 0xFF && func_002ACBC8(d, slot[i]) != 0
                    && *(float *)(D_L08_001B2ACC[slot[i]].bytes + 0x38) < D_00189E20.pos[2]) {
                    /* Written out: SetAnimation's int compare would keep 3 in a saved register across the loop. */
                    if (OB(0x43) != 3)
                        func_PAL_002A7E68(obj, 3, 0, 2);
                    func_PAL_L00_002D2668(0x88, 0, 12.0f);
                    qcopy(d + 0x80, D_L08_001B2ACC[slot[i]].bytes + 0x30);
                    DF(0x90) = func_00282E48(D_00189E20.pos, d + 0x80);
                    {
                        float m = func_00282DF0(d + 0x20) > 0.080000006f ? func_00282DF0(d + 0x20) : 0.080000006f;
                        DF(0x94) = m;
                    }
                    D_00189E20.unkC20 = D_L08_001B013C / (DF(0x90) / DF(0x94));
                    func_002A7750(obj, 0xA, -1);
                }
            }
        }
        {
            int j;
            slot = (s32 *)(d + 0xA0);
            for (j = 0; j < 2; j++) {
                if (slot[j] != 0 && slot[j] != 0xFF && (((DI(0xB4) >> j) ^ 1) & 1)
                    && func_002ACBC8(d, slot[j]) != 0 && OB(0x20) != 9) {
                    func_002E5DA0(5, 0, obj, 0x988);
                    DI(0xB4) = DI(0xB4) | (1 << j);
                }
            }
        }
        func_00282948(d + 0x98);
        func_00282948(d + 0xB0);
    }
}
