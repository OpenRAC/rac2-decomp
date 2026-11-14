/* func_US2_L04_004188B8 (6,312 bytes, USA v2.00, levels 04/11): the v2.00 copy of the race HUD
 * func_L04_00417308 (src/levels/shared/L04_00417308-hud-g8.c), ported like the PAL copy
 * (src/pal/levels/shared/L04_0041BC68-hud-g8.c). v2.00 adds a pad debug block (pad word +0x1A0,
 * four $gp counters printed through func_0026FEB8), loads p after it, reads the B table through
 * $gp (sized sda declaration, -Wa,-G16), adds 3.0 to the fuel bar's two y coordinates in mode 1
 * (hud_y3) and uses text id 0x2E2B. FAKEMATCH sites as in the v1.01 and PAL units, plus: the
 * 0x2E2B label and the 0x3F/0x40 sprites pass 1 instead of n20/one4 (allocation windows), psy and
 * psy2 order the spill slots, and a #pragma rac2_sched1_order list (-frac2-sched1-order, owner
 * ruling of 14 November 2026) orders seven insns. The v1.01 header follows. */
/* func_L04_00417308 (5,968 bytes; Barlow and Damosel): the race HUD (ruler, rank rows, markers).
 * A FAKEMATCH unit (owner ruling, 13 November 2026; config/fakematch.tsv): each site is marked
 * below. It builds with the switches of tools/compiler/transformers/l04_17308_rules.py and
 * earlier ones (config/cflags.txt; docs/build/compiler-notes.md). */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
typedef struct { s32 v[4]; } T4;
typedef struct { s32 v[5]; } T5;
typedef struct { s32 id; float y; } Slot;
typedef struct { s32 a; s32 flags; char pad[56]; } Rec;

extern T4 D_L04_001B0B50;
extern s32 D_L04_001B0B60[4] __attribute__((sda));
extern char D_00138180[];
extern s32 D_US2_L04_001B0B3C __attribute__((sda));
extern s32 D_US2_L04_001B0B40 __attribute__((sda));
extern s32 D_US2_L04_001B0B44 __attribute__((sda));
extern s32 D_US2_L04_001B0B48 __attribute__((sda));
extern char D_US2_L04_001B0B50[];
extern void func_0026FEB8(const char *, ...);
extern T5 D_L04_001B0B78;
extern char D_L04_001B0B90[];
extern u8 *D_L04_001B0914 __attribute__((sda));
extern s32 D_L04_001B091C __attribute__((sda));
extern s32 D_L04_001B090C __attribute__((sda));
extern s32 D_L04_001B0B70 __attribute__((sda));
extern s32 D_L04_001B0B74 __attribute__((sda));
extern u8 *D_L04_001B24DC __attribute__((sda));
extern s32 D_L04_001A8FE8;
extern s32 D_L04_001A8FE4;
extern s32 D_001A7340;
extern s32 D_001A79F0;
extern s32 D_L04_001A904C;
extern float D_L04_001B2D44;
extern char D_L04_001B3190[] MACRO_ADDR;
extern float D_L04_001B31A0;
extern float D_L04_001B31A4;
extern float D_L04_001B31A0_view[] __asm__("D_L04_001B31A0") MACRO_ADDR;
extern float D_L04_001B31D0;
extern char D_L04_001BDB80[];
typedef struct { char pad[0x24]; int kind; u8 *owner; char tail[0x3C]; int active; char pad2[6]; u16 state; } OwnerContext;
extern OwnerContext D_001A63A8;
extern Slot D_L04_002605D0[];
extern Rec D_L04_002C63C0[];
extern s32 D_L04_002CA1E0[];

extern int func_001157AC(char *);
extern int func_00115DA8(char *, char *, ...);
extern void func_0027AB40(void);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0027F5B8(int, int, unsigned long long, char *, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);
extern int func_0027FBD8(int, int, unsigned long long, char *, int);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern void func_00283388(void *);
extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern float func_00283BE0(float, float);
extern int func_00283D38(int, int, float);
extern char *func_00288FB8(int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, void *);
extern void func_0028FC48(int, int, int, int, unsigned long long, int);
extern void func_0029B658(int, int, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern f32 func_002AAA00(void *, float, float, float, float, void *, int);
extern int func_002B6D28(void);
extern int func_002E5CF8(int, int, void *);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00300A00(void *, float, int, float, float, float, float);
extern void func_00300AA8(void *, float, float, int, float, void *);
extern s32 func_00336D50(void *, int);
extern void func_L04_0040C880(u8 *);
extern void func_L04_00416E38();
extern void func_L04_00417028(u8 *);
extern void func_L04_0043AD48(void *, void *, int, int, void *, void *, void *);

typedef struct { char pad[0x1C4]; s32 m1C4, m1C8, m1CC, m1D0; float m1D4; s32 m1D8, m1DC, m1E0; } Marker;
#define OM(o) ((Marker *)(o))
#define I(b, o) (*(s32 *)((b) + (o)))
#define F(b, o) (*(float *)((b) + (o)))
#define CLAMP01(x) do { if ((x) > 1.0f) (x) = 1.0f; if ((x) < 0.0f) (x) = 0.0f; } while (0)

extern int D_L04_001B2D40;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord_a(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord_ah(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (scaled == half)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
/* FAKEMATCH: label_y plus a second dead mode test (D_L04_001B2D40 + 1 == active): one more n20 reference, no code */
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    if (D_L04_001B2D40 + 1 == active)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_y3(float value)
{
    float y = value * D_L04_001B2D44 + 0.5f;
    if (D_L04_001B2D40 == 1)
        return (int)(y + 3.0f);
    return (int)y;
}
#define HC(k) hud_coord((k), D_L04_001B2D44, 0.5f)
#define HCN(k) hud_coord_a((k), D_L04_001B2D44, 0.5f, n20)
#define LY2(hd, k) label_y2((void *)(hd), (k), D_L04_001B2D44, 0.5f, 1)
#define LY(hd, k) label_y((void *)(hd), (k), D_L04_001B2D44, 0.5f, 1)

/* FAKEMATCH: order hint (owner ruling, 14 November 2026): the marker heading and the -1.0 constant
   are loaded before the heading call's result is copied out of $f0, so local-alloc gives them $f2
   and $f1 and the result keeps $f0; in both func_002AA548 calls &tmp goes to $a0 before $a1. */
#pragma rac2_sched1_order 3145 3151 3142 3226 3228 3283 3285
s32 func_US2_L04_004188B8(void)
{
    T4 A = D_L04_001B0B50;
    char *pad = D_00138180;
    u8 *h = D_L04_001B0914;
    T5 C = D_L04_001B0B78;
    u8 *p;
    u8 *obj;
    u8 *o;
    u8 *e;
    char buf[16];
    Vec m[4];
    Vec v90[4];
    Vec vD0, vE0, vF0;
    float tmp;
    s32 sy, sy2, sy3;
    u8 *hp;
    s32 *psy, *psy2; /* FAKEMATCH: named &sy and &sy2 declared after hp and before pa: their alter_reg slots 0x108/0x10C follow hp's 0x104 and precede pa's 0x110 */
    u8 *pa, *pb, *arr;
    Vec *m2; /* FAKEMATCH: named &m[2], declared last: its alter_reg slot 0x11C follows arr's 0x118 */
    float fr, fs, fm, fe, f21, fa, fd;
    int n33, n20, ne, i, col, idx, v, va, v3, vy;
    int j;
    int one2;
    int none;
    int one3;
    int one4;
    float half;
    float rh;
    float fz;
    float k15;
    float tenth;
    int mcol;
    Vec *mv;
    char *s;

    if (*(unsigned long long *)(pad + 0x1A0) & 0x400000001ULL) {
        u32 b = *(u32 *)(pad + 0x1A0);
        if (b & 0x1000)
            D_US2_L04_001B0B40++;
        else if (b & 0x4000)
            D_US2_L04_001B0B40--;
        else if (b & 0x8000)
            D_US2_L04_001B0B3C--;
        else if (b & 0x2000)
            D_US2_L04_001B0B3C++;
        else if (b & 0x80)
            D_US2_L04_001B0B44++;
        else if (b & 0x20)
            D_US2_L04_001B0B44--;
        else if (b & 0x2)
            D_US2_L04_001B0B48++;
        else if (b & 0x8)
            D_US2_L04_001B0B48--;
        func_0026FEB8(D_US2_L04_001B0B50, D_US2_L04_001B0B3C, D_US2_L04_001B0B40, D_US2_L04_001B0B44, D_US2_L04_001B0B48);
    }
    n20 = 1;
    p = *(u8 **)(h + 0x68);
    if (h[0xBC] == n20)
        func_L04_00416E38();
    if (D_L04_001B091C > 0) {
        func_L04_00417028(h);
        func_00282948(&D_L04_001B091C);
        if (D_L04_001B091C == 0xAD)
            func_002E5CF8(0xD, 0, h);
    } else if (func_00282C48(F(p, 0x4A4)) > 1.5707964f) {
        func_0027EB88(HC(112.0f), HC(142.0f), 0xAF, D_001A7340 - 0xAF, 0x60, 0x60442D00);
        func_0029B658(0x60, 0x55F0C070, (float)HC(112.0f), (float)HC(142.0f) /* FAKEMATCH: was HCN; drops one n20 ref so n20 lands at 23/250 */, 175.0f,
                      (float)(D_001A7340 - 0xAF));
        {
            int x, y, len;
            do { s = func_00288FB8(0x2E2B); x = D_001A7340 / 2; y = label_y((void *)x, 118.0f, D_L04_001B2D44, 0.5f, 1); } while (0); len = func_001157AC(s);
            func_0027FBD8(x, y, 0x700000E4, s, len);
        }
        if (I(p, 0x76C) == 0) {
            OwnerContext *context = &D_001A63A8;
            I(p, 0x76C) = n20;
            if ((context->active != 0 || context->kind != -1) && (u16)(context->state - 6) >= 2)
                context->state = 5;
        }
        if (I(p, 0x76C) != 0) {
            OwnerContext *context = &D_001A63A8;
            if (!context->active && context->kind == -1) {
                context->kind = I(p, 0x760) + 0xBB8;
                context->owner = h;
            }
            func_002B6D28();
        }
    }
    if (func_00282C48(F(p, 0x4A4)) < 1.5707964f && I(p, 0x76C) != 0) {
        OwnerContext *context = &D_001A63A8;
        I(p, 0x76C) = 0;
        if ((u16)(context->state - 6) >= 2)
            context->state = 5;
    }
    if ((u32)(h[0xBC] - 1) < 4 || D_L04_001A8FE8 < 0x3C)
        func_L04_0040C880(h);
    if (D_L04_001A904C != 0) {
        { float q = func_00283198(0.56217057f) / func_00283180(0.56217057f); u8 *cam = D_L04_001BDB80; F(cam, 0xB0) = q; }
        func_0027AB40();
        { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x2D); func_00300A00(spr, 10.0f, 0x60442D00, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x2E); func_00300A00(spr, 10.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (I(p, 0x360) != 0) {
            float fr;
            va = A.v[I(p, 0x360) - 1];
            vF0.i[0] = va;
            vF0.i[1] = va;
            vF0.i[2] = va;
            vF0.i[3] = va;
            idx = 0;
            switch (I(p, 0x360)) {
            case 1: idx = 0; break;
            case 2: idx = 1; break;
            case 3: idx = 2; break;
            }
            func_0028EA58(func_0028E588(0x7568, idx), 0x3E, HC(17.0f), 0x28, HC(35.0f), &vF0);
            fr = (float)I(p, 0x364) / (float)C.v[I(p, 0x360)];
            if (fr > 1.0f) fr = 1.0f;
            if (fr < 0.0f) fr = 0.0f;
            func_0027EAE8(0x6F, HC(28.0f), (int)(fr * 91.0f) + 0x6F, HC(41.0f), 0xFFFFF0, &vF0);
        }
        n33 = I(p, 0x33C);
        if (n33 > 0) {
            if (D_L04_001B0B70 != n33) {
                if (D_L04_001B0B70 < n33)
                    D_L04_001B0B74 = 0x2D;
                else
                    D_L04_001B0B74 = 0;
                D_L04_001B0B70 = I(p, 0x33C);
            }
            if (D_L04_001B0B74 > 0)
                D_L04_001B0B74 = D_L04_001B0B74 - 1;
            col = func_00283D38(0x603F00B2, 0x800000FF, (float)D_L04_001B0B74 * 0.022222223f);
            { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x35); func_00300A00(spr, 11.0f, col, (float)LY(spr, 10.0f), 1.0f, 1.0f, (float)D_L04_001B0B70); }
        } else {
            D_L04_001B0B70 = 0;
        }
        {
        one4 = 1;
        if (I(p, 0x278) != 0)
            fa = (float)I(p, 0x278) / (float)I(p, 0x650);
        else
            fa = (float)I(p, 0x338) * 0.004166667f;
        if (fa > 1.0f) fa = 1.0f;
        if (fa < 0.0f) fa = 0.0f;
        vF0.i[0] = 0x603F00B2;
        vF0.i[1] = 0x603F00B2;
        vF0.i[2] = 0x603F00B2;
        vF0.i[3] = 0x603F00B2;
        func_0027EAE8(0x1A, hud_y3((float)(0x62 - (int)(fa * 74.0f))), 0x26, hud_y3(98.0f), 0xFFFFF0,
                      &vF0);
        }
        { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x3F); func_00300A00(spr, 498.0f, 0x60442D00, (float)label_y(spr, 10.0f, D_L04_001B2D44, 0.5f, 1), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x40); func_00300A00(spr, 498.0f, 0x55F0C070, (float)label_y(spr, 10.0f, D_L04_001B2D44, 0.5f, 1), 1.0f, 1.0f, 0.0f); }
        { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x41); func_00300A00(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (D_001A79F0 == 4)
            { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x42); func_00300A00(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        else
            { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x30); func_00300A00(spr, 498.0f, 0x55F0C070, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        if (D_001A79F0 == 4 && (D_L04_002C63C0[D_L04_001B090C].flags & 4))
            { void *spr = (void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x43); func_00300A00(spr, 498.0f, 0x60FFDE8D, (float)LY(spr, 10.0f), 1.0f, 1.0f, 0.0f); }
        n20 = I(p, 0x320);
        if ((u32)(n20 - 1) >= 0x14)
            n20 = 0x14;
        {
            int y;
            int c;
            int k;
            mcol = n20 >= 0xA ? 0x11D : 0x123;
            k = D_L04_002CA1E0[n20 - 1]; /* FAKEMATCH: index precomputed outside the group */
            /* FAKEMATCH: call inside the rank-row group so the 24.0 li.s precedes the s copy (0xAF8); label_y4 with n20 active keeps n20 (23/250 = 0.368..0.375 window) above s and below the s1 allocno */
            do { s = func_00288FB8(k); y = label_y4((void *)n20, 24.0f, D_L04_001B2D44, 0.5f, n20); } while (0);
            c = D_L04_001B0B60[n20 < 4 ? n20 - 1 : 3];
            func_0027F5B8(mcol, y, c, s, -1);
        }
        {
            int r = func_00115DA8(buf, D_L04_001B0B90, D_L04_001A8FE4 + 1, 3);
            int y = label_y3((void *)r, 71.0f, D_L04_001B2D44, 0.5f, 1);
            int len = func_001157AC(buf);
            func_0027FB40(0x1D5, y, 0x60F0F0F0, buf, len);
        }
        func_00283388(m);
        func_00283698(m, &D_L04_001B31A0);
        func_0028FC48(0x157, HC(36.0f), 0x1AB, HC(37.0f), 0x25F0C070, 0);
        func_0028FC48(0x151, HC(28.0f), 0x1AB, HC(29.0f), 0x25F0C070, 0);
        func_0028FC48(0x160, HC(45.0f), 0x1AB, HC(46.0f), 0x25F0C070, 0);
        one3 = 1; /* FAKEMATCH: before i = 0 so one3 is born before the &vF0 copy dies */
        i = 0;
        func_00282D30(&vD0, h + 0xC0, F(p, 0x30C) + F(p, 0x27C));
        hp = h + 0x10;
        func_002830C0(&vE0, &vD0, m);
        arr = p + 0x1E4;
        fd = func_00282DB0(&vE0, &D_L04_001B31A0);
        pa = p + 0x494;
        pb = p + 0x498;
        func_00282D30(&vD0, &D_L04_001B31A0, fd);
        func_00282CD8(&vF0, &vE0, &vD0);
        func_002AA2E8(&D_L04_001B31D0, vE0.f[0] * -1.25f, 0.050000004f);
        psy = (s32 *)&tmp; /* FAKEMATCH: dead store, overwritten next: its &tmp, the first, gives tmp its frame slot (0xF0) ahead of sy and sy2 */
        psy = &sy; /* FAKEMATCH: set-once &sy, see decl */
        psy2 = &sy2; /* FAKEMATCH: set-once &sy2, see decl */
        m2 = &m[2]; /* FAKEMATCH: set-once &m[2], see decl */
        for (; i < 9; i++) {
            fz = 0.0f; /* FAKEMATCH: set-once zero, hoisted first (retail preheader order) */
            rh = 0.5f; /* FAKEMATCH: per-iteration ruler half, hoisted by loop.c; reload_cse makes it retail's mov.s f23,f20 (gcse would otherwise copy-propagate the 0.5 register into the ruler) */
            sy = (int)(D_L04_002605D0[i].y + D_L04_001B31D0);
            if (sy < 0x164 && D_L04_001B31D0 < fz /* FAKEMATCH: fz */) {
                if (i == 0)
                    D_L04_002605D0[0].y = D_L04_002605D0[8].y + 8.0f;
                else
                    D_L04_002605D0[i].y = D_L04_002605D0[i - 1].y + 8.0f;
            } else if (sy >= 0x1A4 && D_L04_001B31D0 > 0.0f) {
                if (i == 8)
                    D_L04_002605D0[8].y = D_L04_002605D0[0].y - 8.0f;
                else
                    D_L04_002605D0[i].y = D_L04_002605D0[i + 1].y - 8.0f;
            }
            D_L04_002605D0[i].y = D_L04_002605D0[i].y + D_L04_001B31D0;
            sy = (int)D_L04_002605D0[i].y;
            if (sy < 0x173)
                fr = ((float)sy - 355.0f) * 0.06666667f;
            else if (sy >= 0x195)
                fr = (420.0f - (float)sy) * 0.06666667f;
            else
                fr = 1.0f;
            if (fr > 1.0f) fr = 1.0f;
            if (fr < 0.0f) fr = 0.0f;
            mcol = func_00283D38(0x10F0C070, 0x25F0C070, fr);
            {
                /* FAKEMATCH: set-once copy: sy is read after the top row */
                int y1 = hud_coord_a(21.0f, D_L04_001B2D44, rh, one3);
                func_0028FC48(sy, y1, sy + 1, hud_coord_a(55.0f, D_L04_001B2D44, rh, one3), mcol, 0);
            }
        }
        func_00282CF0(&vE0, hp, D_L04_001B3190);
        func_002830C0(&vD0, &vE0, m);
        fa = vD0.f[1] * 0.2f;
        if (fa > 1.0f)
            fa = 1.0f;
        if (fa < -1.0f)
            fa = -1.0f;
        sy3 = (int)(fa * 13.0f) + 0x24;
        obj = (u8 *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x3E);
        f21 = func_00283248(D_L04_001B31A0, D_L04_001B31A0_view[1]);
        j = 0;
        none = -1; /* FAKEMATCH: set-once -1 after j = 0 puts j's daddu fp before the hoisted -1 (0x1070/0x1090) */
        one2 = 1;
        half = 0.5f;
        tenth = 0.1f;
        do {
            ne = *(s32 *)((int)arr + (j << 2));
            if (ne != none) {
                e = D_L04_001B24DC + (ne << 8);
                o = *(u8 **)(e + 0x68);
                if (e[0x20] == 2 || h[0xBC] == one2 || h[0xBC] == 3) {
                    func_00282CF0(&vE0, e + 0x10, D_L04_001B3190);
                    func_002830C0(&vD0, &vE0, m);
                    sy = (int)(vD0.f[0] + vD0.f[0]) + 0x183;
                    vy = (int)(vD0.f[1] * 4.0f);
                    sy2 = vy + 0x24;
                    if ((u32)(vy + 0xD) < 0x1B && sy < 0x1A5 && sy >= 0x168) {
                        if (sy < 0x173)
                            fm = ((float)sy - 360.0f) * tenth;
                        else if (sy >= 0x19A)
                            fm = (420.0f - (float)sy) * tenth;
                        else
                            fm = 1.0f;
                        if (fm == 1.0f) {
                            if (sy2 < 0x1D)
                                fm = ((float)sy2 - 23.0f) * 0.2f;
                            else if (sy2 >= 0x2C)
                                fm = (49.0f - (float)sy2) * 0.2f;
                        }
                        mcol = func_00283D38(0x100040E4, 0x600040E4, fm);
                        {
                        float t = func_00283BE0(f21, F(e, 0xF8));
                        float cur = OM(o)->m1D4; /* FAKEMATCH: set-once copy: the heading is read before tmp is stored */

                        tmp = t;
                        if (cur == -1.0f)
                            OM(o)->m1D4 = t;
                        else
                            func_002AAA00(o + 0x1D4, t, 0.002327106f, 0.002327106f, 4.712389f,
                                          o + 0x1E0, 0);
                        }
                        v = OM(o)->m1CC;
                        if (v == none) {
                            OM(o)->m1CC = sy;
                        } else {
                            tmp = (float)v;
                            func_002AA548(&tmp, o + 0x1D8, (float)sy, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            OM(o)->m1CC = (int)tmp;
                        }
                        v = OM(o)->m1D0;
                        if (v == none) {
                            OM(o)->m1D0 = sy2;
                        } else {
                            tmp = (float)v;
                            func_002AA548(&tmp, o + 0x1DC, (float)sy2, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            OM(o)->m1D0 = (int)tmp;
                        }
                        vD0.f[1] = OM(o)->m1D4;
                        vD0.f[0] = 0.0f;
                        vD0.f[2] = 0.0f;
                        func_00283410(v90, &vD0);
                        func_00282D30(v90, v90, F(obj, 0xC));
                        func_00282D30(&v90[2], &v90[2], F(obj, 0xC));
                        func_00300AA8(obj, (float)OM(o)->m1CC, (float)label_y(o, (float)OM(o)->m1D0, D_L04_001B2D44, half, one2),
                                      mcol, 0.0f, v90);
                    } else {
                        OM(o)->m1D0 = none;
                        OM(o)->m1D4 = -1.0f;
                        OM(o)->m1CC = none;
                        OM(o)->m1E0 = 0;
                        OM(o)->m1D8 = 0;
                        OM(o)->m1DC = 0;
                    }
                    func_L04_0043AD48(psy, psy2, I(o, 0x120), I(o, 0x124), o + 0x1C4, o + 0x1C8,
                                      p);
                    func_0028FC48(sy - 2, hud_coord_a((float)(sy2 - 1), D_L04_001B2D44, half, one2), sy + 2, hud_coord_a((float)(sy2 + 3), D_L04_001B2D44, half, one2),
                                  0x600040E4, 0);
                }
            }
            j++;
        } while (j < 0x15);
        fa = func_00283BE0(f21, F(h, 0xF8));
        if (F(p, 0x4A4) == -1.0f)
            F(p, 0x4A4) = fa;
        else
            func_002AAA00(p + 0x4A4, fa, 0.002327106f, 0.002327106f, 4.712389f, p + 0x4B0, 0);
        I(p, 0x49C) = 0x183;
        v3 = I(p, 0x4A0);
        if (v3 == -1) {
            I(p, 0x4A0) = sy3;
        } else {
            tmp = (float)v3;
            func_002AA548(&tmp, p + 0x4AC, (float)sy3, 0.1388889f, 0.1388889f, 5.8333335f);
            I(p, 0x4A0) = (int)tmp;
        }
        vD0.f[1] = F(p, 0x4A4);
        vD0.f[0] = 0.0f;
        vD0.f[2] = 0.0f;
        func_00283410(m, &vD0);
        func_00282D30(m, m, F(obj, 0xC));
        func_00282D30(m2, m2, F(obj, 0xC));
        func_00300AA8(obj, (float)I(p, 0x49C), (float)label_y(obj, (float)I(p, 0x4A0), D_L04_001B2D44, 0.5f, 1), 0x8000A6E4, 0.0f, m);
        func_L04_0043AD48(psy, psy2, I(p, 0x314), I(p, 0x318), pa, pb, p);
        func_0028FC48(sy, HC((float)sy2), sy + 4, HC((float)(sy2 + 4)), 0x8000A6E4, 0);
        func_002FC560(0x47, 0x5360B);
        if (h[0x20] != 3) {
            fe = F(p, 0x28C) * 0.008726647f;
            { float q = func_00283198(fe) / func_00283180(fe); u8 *cam = D_L04_001BDB80; F(cam, 0xB0) = q; }
            func_0027AB40();
        }
    }
    return 1;
}
