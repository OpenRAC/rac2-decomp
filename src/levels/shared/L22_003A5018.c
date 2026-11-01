#include "include_asm.h"

typedef unsigned char u8;
typedef float f32;

/* func_L22_003C9880: the level's pulse settings, read as {low, high} pairs.  A pair's
 * first word is a plain small-data symbol (one instruction, so it can take a call's
 * delay slot, where the assembler gives it the $gp form), its second word
 * `[1]` an offset address, which stays the absolute macro load.  The colour pair
 * at 0x001AFF18 also reads its first word through $gp outside a delay slot:
 * common.h's SDATA view, spelled out (this unit does not include common.h). */
extern float D_L22_001AFF08[] __attribute__((sda));
extern float D_L22_001AFF10[] __attribute__((sda));
extern int D_L22_001AFF18[] __attribute__((sda));
extern int D_L22_001AFF18_gp[] __asm__("D_L22_001AFF18__gp") __attribute__((section(".sdata")));
extern float D_L22_001AFF20[] __attribute__((sda));
extern float D_L22_001A7CD8[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));

/* The per-subtitle history src/game/00289178.c updates (12-byte rows). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory D_0018C958[];

extern void func_002A7750(void *, int, int);
extern f32 func_002A7878(f32 low, f32 high);
extern int func_002E5CF8(int index, int a1, char *a2);
extern void func_00288E18(int, int);
extern f32 func_00282DB0(void *, void *);
extern void func_L22_003C9B60(char *);
extern void func_L22_003C9D48(u8 *);
extern void func_L00_002E6CF0(void (*)(u8 *), void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern int func_00283D38(int, int, f32);

/* Family cbc1388ebe801e68 (116 B, 2 placements): arm one animation slot on a
 * resident object.  Two global guards, a "current slot" guard, then five
 * resident stores in the retail order.
 *
 * The indexed read `p + a1 * 4 + 1152` must be written as a named byte pointer
 * (`w = p + a1 * 4`) followed by the load at `w + 1152`: when the 1152 is folded
 * into the same PLUS chain, gcc canonicalises the commutative `addu` with the
 * scaled index as the first source operand, one byte away from retail.
 */

extern u8 D_001A63A8_4[];

INCLUDE_ASM("asm/levels", func_L22_003A5018);

/* func_L22_003A5BD8 is in L22_003A5BD8-effects-g32.c. */

/* func_L22_003A5F90 is matched in L22_003A5F90.c. */

extern int func_L22_003A48F8(int);

int func_L22_003A6128(f32 f12) {
    union { f32 f; unsigned int u; } c;
    int n = 0;
    int i;
    int idx = 0;

    c.f = f12;
    for (i = 0; i < 32; i++) {
        if (c.u & 1) {
            n++;
            if (n >= 2)
                return 0;
            idx = i;
        }
        c.u >>= 1;
    }
    if (n == 0)
        return 0;
    if (n == 1) {
        if (func_L22_003A48F8(idx) == 0)
            return 1;
    }
    return 0;
}

/* func_L22_003A6230 is defined in L22_003A6230-g8.c. */

/* shared native body of family cbc1388ebe801e68 */
void func_L22_003A6470(u8 *a0, int a1) {
    u8 *g = D_001A63A8_4;
    u8 *p = *(u8 **)(a0 + 104);
    int bit;
    if (*(int *)(g + 104) != 0) return;
    if (*(int *)(g + 36) != -1) return;
    if (a1 == *(int *)(p + 1256)) return;
    bit = 1 << a1;
    { u8 *w = p + a1 * 4; *(int *)(g + 36) = (*(int *)(w + 1152) & 0x3fff) + 2000; }
    *(int *)(g + 40) = 0;
    *(int *)(p + 1256) = a1;
    *(int *)(p + 1252) = 1800;
    *(int *)(p + 1248) |= bit;
}

extern int func_002A77E0(int a0);

extern void func_L22_003A64E8(u8 *a0, int a1, int a2);

/* Arm one animation slot in the range [a1, a2]: a random slot of the range is
 * tried first and the next one after it, wrapping around, until a free slot
 * is found; when every slot of the range is taken, the range is cleared and
 * the last slot tried is armed.
 *
 * The mask lives in the controller at +0x4E0 of the object at +0x68.
 */
void func_L22_003A64E8(u8 *a0, int a1, int a2) {
    u8 *ctl = *(u8 **)(a0 + 0x68);
    int count;
    int rem;
    int i;

    if (a2 < a1)
        return;
    count = a2 - a1 + 1;
    rem = func_002A77E0(count);
    for (i = 0; i < count; i++) {
        int idx = a1 + rem;
        if (((*(int *)(ctl + 0x4E0) >> idx) ^ 1) & 1) {
            func_L22_003A6470(a0, idx);
            return;
        }
        rem = (rem + 1) % count;
    }
    i = 0;
    if (count > 0) {
        int m = *(int *)(ctl + 0x4E0);
        for (; i < count; i++) {
            m &= ~(1 << (a1 + i));
        }
        *(int *)(ctl + 0x4E0) = m;
    }
    func_L22_003A6470(a0, a1 + rem);
}

/* A three-label switch, the third one sharing the default's body: with only two cases cc1
 * emits a comparison chain, and the third label is what makes it build the decision tree
 * (`beq` on the high case, then an `slti` guard on the range, then `bne` on the low one). */
f32 func_L22_003A65E0(u8 *a0) {
    switch (*(short *)(a0 + 0xAA)) {
    case 0xE3A: return *(f32 *)(*(u8 **)(a0 + 0x68) + 0x2C);
    case 0xE3B: return *(f32 *)(*(u8 **)(a0 + 0x68) + 0x44);
    case 0xE3C:
    default: return *(f32 *)(*(u8 **)(a0 + 0x68) + 0x44);
    }
}

/* func_L22_003A6640 is defined in L22_003A6640-g8.c. */

extern u8 D_00189E20[];
extern f32 func_00282E48(void *a0, void *a1);
extern void func_L22_002B70F8(int a0, int a1, void *a2);

void func_L22_003A8BA0(u8 *a0) {
    if (D_00189E20[0x22B4] != 0) return;
    if (func_00282E48(D_00189E20 + 0x80, a0 + 0x10) < 4.0f) {
        func_L22_002B70F8(2, 0x56, a0);
    }
}

extern int func_00283CF0(f32);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_002A8C28(void *, void *, int, f32, f32, f32, int, int, int);

/* Halves whatever the two floats say, doubles it back, rescales it by the
 * controller's rate, then hands the result to the placement call as the alpha;
 * the controller's counter also drives the byte at +0x23 (a 127/40 ramp). */
void func_L22_003AD090(u8 *a0) {
    u8 *obj = a0;
    u8 *sub = *(u8 **)(obj + 0x24);
    u8 *ctl = *(u8 **)(obj + 0x68);
    u8 *resident;
    f32 v;
    int n;

    v = *(f32 *)(obj + 0x2C) / *(f32 *)(sub + 0x24) * 0.5f;
    v += *(f32 *)(ctl + 0x0);
    *(f32 *)(obj + 0x2C) = v + v;
    *(f32 *)(obj + 0x2C) = *(f32 *)(obj + 0x2C) * *(f32 *)(sub + 0x24);
    n = *(int *)(ctl + 0x8);
    if (n < 0x28) *(u8 *)(obj + 0x23) = n * 127 / 40;
    resident = D_00189E20;
    func_002A8C28(*(void **)(resident + 0x2290), obj + 0x10, 0x30000, v,
                  (f32)func_00283CF0(*(f32 *)(ctl + 0xC)), 1.0f, 0, 1, 0);
    if (func_00282948(ctl + 0x8))
        func_0029F338(obj);
}

/* State 0 seeds four lanes (phase offsets, random rates and values); state 1
 * reacts to the player (distance, sound, subtitle 31's history, a facing test that
 * runs func_L22_003C9B60 and registers func_L22_003C9D48); while visible the
 * phase advances and drives the packed colour at +0x78.  Reading the player through pointer locals
 * lets cse derive the first one from the position address the distance call
 * took (`addiu $a0,$s1,-0x80`) and rebuild the second, as retail does. */
void func_L22_003C9880(u8 *obj)
{
    u8 *ctl = *(u8 **)(obj + 0x68);
    int state = obj[0x20];
    int i;

    switch (state) {
    case 0:
        func_002A7750(obj, 1, -1);
        *(short *)(obj + 0x32) = 255;
        {
            float *offset, *rate, *radius;
            i = 0;
            radius = (float *)(ctl + 0x10);
            rate = (float *)(ctl + 0x30);
            offset = (float *)(ctl + 0x20);
            for (; i < 4; i++) {
                *offset++ = (float)i * 0.25f;
                *rate++ = func_002A7878(D_L22_001AFF08[0], D_L22_001AFF08[1]) * (1.0f / 60.0f);
                *radius++ = func_002A7878(D_L22_001AFF10[0], D_L22_001AFF10[1]);
            }
        }
        break;
    case 1: {
        u8 *player;
        SubtitleHistory *history;

        if (func_00282E48(D_00189E20 + 0x80, obj + 0x10) < 3.0f)
            D_L22_001A7CD8[0] = *(float *)ctl;
        player = D_00189E20;
        if (*(int *)(player + 0x2294) == 0x81 && *(int *)(player + 0x1B8) == state)
            func_002E5CF8(0, 0, (char *)obj);
        history = D_0018C958;
        {
            /* unsigned int snapshot: retail tests the u16 with an andi and
             * increments the unmasked value */
            unsigned int count = history[31].count;
            if ((unsigned short)count <= 65534) {
                u8 *player2 = D_00189E20;
                if (*(int *)(player2 + 0x2294) == 0x81)
                    history[31].count = 65535;
                else if (*(u8 **)(player2 + 0x33C) == obj) {
                    /* each arm reads the clock itself: reorg merges the two
                     * reads into the branch's delay slot */
                    if ((unsigned short)count != 0) {
                        unsigned int last = history[31].time;
                        if (D_001A7390[0] - last > 1080 || last == 0)
                            func_00288E18(2504, 31);
                        else if (last < D_001A7390[0])
                            history[31].time = D_001A7390[0];
                    } else {
                        history[31].count = count + 1;
                        if (history[31].time < D_001A7390[0])
                            history[31].time = D_001A7390[0];
                        history[31].levels =
                            (history[31].levels | (1 << D_001A79F0[0])) | 0x80000000;
                    }
                }
            }
        }
        if (func_00282DB0(obj + 0xE0, D_00189E20 + 0x2C0) < -0.6f) {
            func_L22_003C9B60((char *)obj);
            func_L00_002E6CF0(func_L22_003C9D48, obj);
        }
        break;
    }
    }
    if (obj[0x31]) {
        float f;
        *(float *)(ctl + 4) = func_00283B98(*(float *)(ctl + 4),
                                            D_L22_001AFF20[0] * 0.0002908882452175021f);
        f = func_00283198(*(float *)(ctl + 4));
        f = f * f;
        f = f * f;
        *(int *)(obj + 0x78) = func_00283D38(D_L22_001AFF18_gp[0], D_L22_001AFF18[1], f * f);
    }
}

/* func_L22_003C9B60 is defined in L22_003C9B60-g8.c. */

/* func_L22_003C9D48 is in L22_003C9D48-g8.c. */

extern void *func_002A9640(void *a0, int a1, int a2);

extern int func_002A77E0(int a0);

extern int func_002E5DA0(int index, int value, char *object, int kind);

extern void func_002AC728(void *a0, void *a1, int a2, float f12, float f13);

extern int func_002E5CF8(int index, int a1, char *a2);

extern void func_00282F20(float *a0, void *a1, float f12);

extern void func_002B0A68(void *a0, int a1, void *a2, unsigned char a3,
                           float f12, float f13, float f14, float f15);

extern void func_0029F338(void *object);

void func_L22_003D4320(u8 *a0, int a1, int a2) {
    u8 *s0 = a0;
    void *s3;
    int s2;
    int s1;
    float buf[4];

    s3 = func_002A9640(a0, -1, 0);
    if (s3 == 0)
        return;
    if (*(short *)(s0 + 0xAA) == 0x1213) {
        s2 = 0xB;
        s1 = 0xF7F;
    } else {
        s2 = 0xC;
        s1 = 0xE0B;
    }
    func_002E5DA0(s2 + func_002A77E0(3), 0, s0, s1);
    func_002AC728(s0, s0 + 0x10, -1, 2.0f, 13.0f);
    func_002E5CF8(0, 0, s0);
    func_00282F20(buf, s3 + 0x10, 0.23333335f);
    func_002B0A68(s0, 3, buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(s0);
}

extern void func_L22_003D4320(u8 *a0, int a1, int a2);

void func_L22_003D4428(u8 *a0) {
    int v = *(int *)(a0 + 0x68);
    func_L22_003D4320(a0, v, v);
    *(u8 *)(a0 + 0x30) = 0xFF;
}

/* func_L22_003F45D8 is in L22_003F45D8-g8.c. */

/* func_L22_003F52D8 is in L22_003F52D8-g8.c. */

INCLUDE_ASM("asm/levels", func_L22_003F54B8);

/* func_L22_003F5580 is in L22_003A5018-g8.c: it reaches the level's scale factor
 * through $gp, which this -G0 unit cannot produce. */

/* func_L22_003F5688 is defined in L22_003F5688.c. */

/* func_L22_003F58F8 is defined in L22_003A5018-g8.c (it reads $gp data outside a delay slot). */

/* func_L22_003F85A0 is defined in L22_003F85A0-flags-g8.c. */

/* func_L22_003F8658 is defined in L22_003F8658-helper-g8.c. */

/* func_L22_003FB1F8 is in L22_003FB1F8-g8.c. */

/* func_L22_003FB310 is defined in L22_003FB310-g8.c. */

/* func_L22_003FB9B8 is defined in L22_003FB9B8-g8.c. */

/* func_L22_003FBBF0 is in L22_003FBBF0-particles-g8.c. */

/* func_L22_003FC048 is in L22_003FC048-particles-g32.c. */

INCLUDE_ASM("asm/levels", func_L22_003FC338);

/* func_L22_003FC780 is defined in L22_003FC780-helper-g8.c. */


/* func_L22_003FCF08 is defined in L22_003FCF08-g8.c. */

/* func_L22_003FD1E8 is defined in L22_003FD1E8-helper-g8.c. */

/* func_L22_003FD2D8: see L22_003FD2D8-g8.c. */

/* func_L22_003FD958 is defined in L22_003FD958-g8.c. */

/* func_L22_0040DD40 is defined in L22_0040DD40-helper-g8.c. */

extern f32 func_002A7878(f32 low, f32 high);

extern void func_0032C700(void *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          int a8, int a9, int a10, int a11, f32 f12, f32 f13);

void func_L22_0040E2B0(u8 *a0) {
    f32 f = func_002A7878(0.8f, 1.2f);
    func_0032C700(a0, 0, 5, 4, 4, 4, 4, 0, 0, 0, 0, 0, f, 20.0f);
}
