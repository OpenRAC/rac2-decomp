/* Second-pass layout/ABI review, 2026-11-03; retained, not linked.
 * Profile: -O2 -G8 -ffunction-sections.
 * US check.py: 5768/5968 bytes,0/2 places; frame0x1C0.
 * Both inverse m[4] and marker v90[4] already hold complete64-byte outputs; no inverse overrun was found. Fresh canonical definitions correct the ignored text return to void and sprite lookup to a32-bit address result with explicit pointer conversion. Scalar x/y helper outputs were verified as int pointers.
 * Remaining: Hero-pointer allocation, serial rounding and call scheduling remain; the equal retail frame does not imply a match.
 * No linked or functional-port qualification; prior measurements follow.
 */
/* Current retained result, 1 November 2026: 5768/5968 bytes. Correct the float helper returns and 64-bit
 * text style parameter. The hero pointer allocation and rounding/call scheduling still differ.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections.
 * Earlier measurements below remain historical where superseded by this note.
 */
/*
 * func_L04_00417308 (5,968 B; levels 04 at 0x00417308 and 11 at 0x00406E08): Sonnet first draft,
 * 2026-10-26 (slate big12), for an Opus finish. HUD draw: boss/target bars, the 9-slot scrolling
 * ruler, the 21-entry marker loop and the final cursor.
 * Profile: -O2 -G8 -ffunction-sections, as its own unit (src/levels/shared/L04_00417308-x.c, cflags
 * line without -Wa). NOT -G0: the non-delay-slot `lw $v0,0x1924($gp)` loads need `.extern NAME,size`
 * emitted at the top of the .s, which cc1 does only for `__attribute__((sda))` at -G8 (at -G0 sda
 * prints a bare `lw` that gas expands to lui+lw). Plain sized externs stay %hi/%lo at -G8 and use
 * $gp only in nomacro delay slots, exactly as retail does for D_001A7340, D_001A79F0, D_001A904C,
 * D_L04_001A8FE8 and the scale float D_L04_001B2D44 (so those carry no sda).
 * sda: D_L04_001B0914 (hero, 0x1924), 001B091C (0x192C), 001B090C (0x191C), 001B0B70/74 (0x1B80/84),
 * 001B24DC (0x34EC).
 * Step 0: one function (one prologue, one jr, no jump table). No matched twin (nearest unmatched
 * func_L11_00444400 0.23, func_L04_00411298 0.22); m2c (box2 big12/out) only as a skeleton, its
 * loops, 0x40800183-style constants and several argument orders were wrong and are hand-fixed here.
 * check.py: 5,768 of 5,968 bytes (both places, same code). cmp.py: opcodes equal 1110 of 1492
 * (difflib, registers ignored), with registers equal 741. Prologue and the first 40 instructions
 * (three ldl/ldr/sdl/sdr struct copies from D_L04_001B0B50/0B60/0B78 as T4/T4/T5 locals) match.
 * Structure notes (all verified against the listing):
 *  - SC(k) = (int)(D_L04_001B2D44 * k + 0.5f), the HUD scale rounding, used about 40 times;
 *    retail keeps 0.5 and the most-used constants in $f20..$f26 across the calls.
 *  - local arrays: A[4] at sp+0, B[4] at 0x10, C[5] at 0x20 (indexed by p[0x360], p[0x320]),
 *    char buf[16] at 0x40, Vec m[4] (matrix) at 0x50, Vec v90[4] (second matrix, row 2 passed to
 *    func_00282D30) at 0x90, vD0/vE0/vF0 at 0xD0/0xE0/0xF0 (vF0 doubles as the 4-word colour
 *    array for func_0028EA58/func_0027EAE8), float tmp 0x100, sy 0x104, sy2 0x108 (both
 *    address-taken for func_L04_0043AD48), hero spill 0x10C, sy3 0x110, six pointer spills
 *    0x114..0x12C. 64-bit params (func_0028FC48/0027FB40/0027FBD8 style, func_002FC560) are
 *    unsigned long long: retail builds 0x8000A6E4 with ori/dsll/ori.
 *  - func_L04_00416E38 is called with no arguments (register pass-through), as retail.
 * Remaining differences, biggest first (frame is 0x1B0 here, 0x1C0 in retail):
 *  1. The hero pointer h is kept in $fp here; retail spills it (lw $v1,0x10C($sp) after every call)
 *     and uses $fp for the marker loop counter, $s6 = -1, $s7 = 1 (retail hoists the constant 1
 *     for `h[0xBC] == 1` in the marker loop, we do not), $s0 = obj, $s2 = e, $s3 = &v90. Most of
 *     the 741-vs-1110 gap is this renumbering. Try making the allocator want h's register less
 *     (a second use of constant 1 in the loop, obj kept live earlier) or use tools/regalloc.py.
 *  2. Code hoisting: the four pointer locals (hp = h + 0x10, arr = p + 0x1E4, pa/pb = p + 0x494/
 *     0x498) are computed right where retail computes them in the source, but here GCC hoists them
 *     (gcse) above func_0027F5B8, so retail's 0x110..0x12C spill stores move and ~30 instructions
 *     are displaced around 0x417DC0..0x417F20. Using the plain expressions at the use sites scored
 *     the same (742). A form that keeps the computation at the source point is needed.
 *  3. Argument evaluation order at the top (0x417460..0x4174C0): retail computes SC(112), SC(142)
 *     and only then loads D_001A7340 for func_0027EB88/func_0029B658; the scheduler here loads it
 *     first.
 *  4. Branch-likely shapes: retail's `if (G[0x68] != 0 || G[0x24] != -1)` block around 0x4175A4
 *     uses bnel/beql with the lhu in the delay slot; ours is bnez with a separate lhu; and the
 *     addiu a0,a1,0x63A8 address of D_001A63A8 is formed once at the top, not per use (try an
 *     `u8 *g = D_001A63A8` local or a struct view).
 *  5. Marker loop (0x4183D0..0x4187B4) and ruler loop (0x4180F8..0x418290) match structurally; only
 *     registers and the sp offsets (0x30 shift from the frame difference) differ.
 * Next steps: fix 1 and 2 first (they explain most single-instruction register diffs), then 3-4.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
typedef struct { s32 v[4]; } T4;
typedef struct { s32 v[5]; } T5;
typedef struct { s32 id; float y; } Slot;
typedef struct { s32 a; s32 flags; char pad[56]; } Rec;

extern T4 D_L04_001B0B50;
extern T4 D_L04_001B0B60;
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
extern char D_L04_001B3190[];
extern char D_L04_001B31A0[];
extern float D_L04_001B31A4;
extern float D_L04_001B31D0;
extern char D_L04_001BDB80[];
extern char D_001A63A8[];
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
extern int func_0028EA58(int, int, int, int, int, void *);
extern void func_0028FC48(int, int, int, int, unsigned long long, int);
extern void func_0029B658(int, int, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern f32 func_002AAA00(void *, float, float, float, float, void *, int);
extern int func_002B6D28(void);
extern int func_002E5CF8(int, int, void *);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern void func_00300AA8(void *, float, float, int, float, void *);
extern s32 func_00336D50(void *, int);
extern void func_L04_0040C880(u8 *);
extern void func_L04_00416E38();
extern void func_L04_00417028(u8 *);
extern void func_L04_0043AD48(void *, void *, int, int, void *, void *, void *);

#define SC(k) ((int)(D_L04_001B2D44 * (k) + 0.5f))
#define I(b, o) (*(s32 *)((b) + (o)))
#define F(b, o) (*(float *)((b) + (o)))
#define CLAMP01(x) do { if ((x) > 1.0f) (x) = 1.0f; if ((x) < 0.0f) (x) = 0.0f; } while (0)

s32 func_L04_00417308(void)
{
    T4 A = D_L04_001B0B50;
    T4 B = D_L04_001B0B60;
    u8 *h = D_L04_001B0914;
    T5 C = D_L04_001B0B78;
    u8 *p = *(u8 **)(h + 0x68);
    u8 *obj;
    u8 *o;
    u8 *e;
    char buf[16];
    Vec m[4];
    Vec v90[4];
    Vec vD0, vE0, vF0;
    float tmp;
    s32 sy, sy2, sy3;
    u8 *hp, *arr, *pa, *pb;
    float f12, f21, fa;
    int n, i, col, idx, v;

    if (h[0xBC] == 1)
        func_L04_00416E38();
    if (D_L04_001B091C > 0) {
        func_L04_00417028(h);
        func_00282948(&D_L04_001B091C);
        if (D_L04_001B091C == 0xAD)
            func_002E5CF8(0xD, 0, h);
    } else if (func_00282C48(F(p, 0x4A4)) > 1.5707964f) {
        func_0027EB88(SC(112.0f), SC(142.0f), 0xAF, D_001A7340 - 0xAF, 0x60, 0x60442D00);
        func_0029B658(0x60, 0x55F0C070, (float)SC(112.0f), (float)SC(142.0f), 175.0f,
                      (float)(D_001A7340 - 0xAF));
        {
            char *s = func_00288FB8(0x2F95);
            func_0027FBD8(D_001A7340 / 2, SC(118.0f), 0x700000E4, s, func_001157AC(s));
        }
        if (I(p, 0x76C) == 0) {
            I(p, 0x76C) = 1;
            if ((*(s32 *)(D_001A63A8 + 0x68) != 0 || *(s32 *)(D_001A63A8 + 0x24) != -1)
                && (u32)(*(u16 *)(D_001A63A8 + 0x72) - 6) >= 2)
                *(u16 *)(D_001A63A8 + 0x72) = 5;
        }
        if (I(p, 0x76C) != 0) {
            if (*(s32 *)(D_001A63A8 + 0x68) == 0 && *(s32 *)(D_001A63A8 + 0x24) == -1) {
                *(u8 **)(D_001A63A8 + 0x28) = h;
                *(s32 *)(D_001A63A8 + 0x24) = I(p, 0x760) + 0xBB8;
            }
            func_002B6D28();
        }
    }
    if (func_00282C48(F(p, 0x4A4)) < 1.5707964f && I(p, 0x76C) != 0) {
        I(p, 0x76C) = 0;
        if ((u32)(*(u16 *)(D_001A63A8 + 0x72) - 6) >= 2)
            *(u16 *)(D_001A63A8 + 0x72) = 5;
    }
    if ((u32)(h[0xBC] - 1) < 4 || D_L04_001A8FE8 < 0x3C)
        func_L04_0040C880(h);
    if (D_L04_001A904C != 0) {
        F(D_L04_001BDB80, 0xB0) = func_00283198(0.56217057f) / func_00283180(0.56217057f);
        func_0027AB40();
        func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x2D), 0x60442D00, 10.0f,
                      (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x2E), 0x55F0C070, 10.0f,
                      (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        n = I(p, 0x360);
        if (n != 0) {
            v = A.v[n - 1];
            vF0.i[3] = v;
            vF0.i[0] = v;
            vF0.i[1] = v;
            vF0.i[2] = v;
            idx = (n == 2) ? 1 : (n == 3) ? 2 : 0;
            func_0028EA58(func_0028E588(0x7568, idx), 0x3E, SC(16.0f), 0x28, SC(35.0f), &vF0);
            f12 = (float)I(p, 0x364) / (float)C.v[I(p, 0x360)];
            CLAMP01(f12);
            func_0027EAE8(0x6F, SC(28.0f), (int)(f12 * 91.0f) + 0x6F, SC(41.0f), 0xFFFFF0, &vF0);
        }
        n = I(p, 0x33C);
        if (n > 0) {
            if (D_L04_001B0B70 != n) {
                if (D_L04_001B0B70 < n)
                    D_L04_001B0B74 = 0x2D;
                else
                    D_L04_001B0B74 = 0;
                D_L04_001B0B70 = I(p, 0x33C);
            }
            if (D_L04_001B0B74 > 0)
                D_L04_001B0B74 = D_L04_001B0B74 - 1;
            col = func_00283D38(0x603F00B2, 0x800000FF, (float)D_L04_001B0B74 * 0.022222223f);
            func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x35), col, 11.0f,
                          (float)SC(10.0f), 1.0f, 1.0f, (float)D_L04_001B0B70);
        } else {
            D_L04_001B0B70 = 0;
        }
        n = I(p, 0x278);
        if (n != 0)
            f12 = (float)n / (float)I(p, 0x650);
        else
            f12 = (float)I(p, 0x338) * 0.004166667f;
        CLAMP01(f12);
        vF0.i[3] = 0x603F00B2;
        vF0.i[0] = 0x603F00B2;
        vF0.i[1] = 0x603F00B2;
        vF0.i[2] = 0x603F00B2;
        func_0027EAE8(0x1A, SC((float)(0x62 - (int)(f12 * 74.0f))), 0x26, SC(98.0f), 0xFFFFF0,
                      &vF0);
        func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x3F), 0x60442D00, 498.0f,
                      (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x40), 0x55F0C070, 498.0f,
                      (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x41), 0x55F0C070, 498.0f,
                      (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        if (D_001A79F0 == 4)
            func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x42), 0x55F0C070, 498.0f,
                          (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        else
            func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x30), 0x55F0C070, 498.0f,
                          (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        if (D_001A79F0 == 4 && (D_L04_002C63C0[D_L04_001B090C].flags & 4))
            func_00300A00((void *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x43), 0x60FFDE8D, 498.0f,
                          (float)SC(10.0f), 1.0f, 1.0f, 0.0f);
        n = I(p, 0x320);
        if ((u32)(n - 1) >= 0x14)
            n = 0x14;
        {
            char *s = func_00288FB8(D_L04_002CA1E0[n - 1]);
            func_0027F5B8(n >= 0xA ? 0x11D : 0x123, SC(24.0f), B.v[n < 4 ? n - 1 : 3], s, -1);
        }
        func_00115DA8(buf, D_L04_001B0B90, D_L04_001A8FE4 + 1, 3);
        func_0027FB40(0x1D5, SC(71.0f), 0x60F0F0F0, buf, func_001157AC(buf));
        func_00283388(m);
        func_00283698(m, D_L04_001B31A0);
        func_0028FC48(0x157, SC(21.0f), 0x1AB, SC(37.0f), 0x25F0C070, 0);
        func_0028FC48(0x151, SC(28.0f), 0x1AB, SC(29.0f), 0x25F0C070, 0);
        func_0028FC48(0x160, SC(45.0f), 0x1AB, SC(46.0f), 0x25F0C070, 0);
        func_00282D30(&vD0, h + 0xC0, F(p, 0x30C) + F(p, 0x27C));
        hp = h + 0x10;
        func_002830C0(&vE0, &vD0, m);
        arr = p + 0x1E4;
        fa = func_00282DB0(&vE0, D_L04_001B31A0);
        pa = p + 0x494;
        pb = p + 0x498;
        func_00282D30(&vD0, D_L04_001B31A0, fa);
        func_00282CD8(&vF0, &vE0, &vD0);
        func_002AA2E8(&D_L04_001B31D0, vE0.f[0] * -1.25f, 0.050000004f);
        i = 0;
        do {
            sy = (int)(D_L04_002605D0[i].y + D_L04_001B31D0);
            if (sy < 0x164 && D_L04_001B31D0 < 0.0f) {
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
                f12 = ((float)sy - 355.0f) * 0.06666667f;
            else if (sy >= 0x195)
                f12 = (420.0f - (float)sy) * 0.06666667f;
            else
                f12 = 1.0f;
            CLAMP01(f12);
            col = func_00283D38(0x10F0C070, 0x25F0C070, f12);
            func_0028FC48(sy, SC(21.0f), sy + 1, SC(55.0f), col, 0);
            i++;
        } while (i < 9);
        func_00282CF0(&vE0, hp, D_L04_001B3190);
        func_002830C0(&vD0, &vE0, m);
        f12 = vD0.f[1] * 0.2f;
        if (f12 > 1.0f)
            f12 = 1.0f;
        if (f12 < -1.0f)
            f12 = -1.0f;
        sy3 = (int)(f12 * 13.0f) + 0x24;
        obj = (u8 *)(u32)func_00336D50((void *)(u32)(D_L04_001A904C + 0x8710), 0x3E);
        f21 = func_00283248(*(float *)D_L04_001B31A0, D_L04_001B31A4);
        i = 0;
        do {
            n = I(arr, i * 4);
            if (n != -1) {
                e = D_L04_001B24DC + (n << 8);
                o = *(u8 **)(e + 0x68);
                if (e[0x20] == 2 || h[0xBC] == 1 || h[0xBC] == 3) {
                    func_00282CF0(&vE0, e + 0x10, D_L04_001B3190);
                    func_002830C0(&vD0, &vE0, m);
                    sy = (int)(vD0.f[0] + vD0.f[0]) + 0x183;
                    v = (int)(vD0.f[1] * 4.0f);
                    sy2 = v + 0x24;
                    if ((u32)(v + 0xD) < 0x1B && sy < 0x1A5 && sy >= 0x168) {
                        if (sy < 0x173)
                            f12 = ((float)sy - 360.0f) * 0.1f;
                        else if (sy >= 0x19A)
                            f12 = (420.0f - (float)sy) * 0.1f;
                        else
                            f12 = 1.0f;
                        if (f12 == 1.0f) {
                            if (sy2 < 0x1D)
                                f12 = ((float)sy2 - 23.0f) * 0.2f;
                            else if (sy2 >= 0x2C)
                                f12 = (49.0f - (float)sy2) * 0.2f;
                        }
                        col = func_00283D38(0x100040E4, 0x600040E4, f12);
                        tmp = func_00283BE0(f21, F(e, 0xF8));
                        if (F(o, 0x1D4) == -1.0f)
                            F(o, 0x1D4) = tmp;
                        else
                            func_002AAA00(o + 0x1D4, tmp, 0.002327106f, 0.002327106f, 4.712389f,
                                          o + 0x1E0, 0);
                        v = I(o, 0x1CC);
                        if (v == -1) {
                            I(o, 0x1CC) = sy;
                        } else {
                            tmp = (float)v;
                            func_002AA548(&tmp, o + 0x1D8, (float)sy, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            I(o, 0x1CC) = (int)tmp;
                        }
                        v = I(o, 0x1D0);
                        if (v == -1) {
                            I(o, 0x1D0) = sy2;
                        } else {
                            tmp = (float)v;
                            func_002AA548(&tmp, o + 0x1DC, (float)sy2, 0.1388889f, 0.1388889f,
                                          5.8333335f);
                            I(o, 0x1D0) = (int)tmp;
                        }
                        vD0.f[0] = 0.0f;
                        vD0.f[1] = F(o, 0x1D4);
                        vD0.f[2] = 0.0f;
                        func_00283410(v90, &vD0);
                        func_00282D30(v90, v90, F(obj, 0xC));
                        func_00282D30(&v90[2], &v90[2], F(obj, 0xC));
                        func_00300AA8(obj, (float)I(o, 0x1CC), (float)SC((float)I(o, 0x1D0)),
                                      col, 0.0f, v90);
                    } else {
                        I(o, 0x1D0) = -1;
                        F(o, 0x1D4) = -1.0f;
                        I(o, 0x1CC) = -1;
                        I(o, 0x1E0) = 0;
                        I(o, 0x1D8) = 0;
                        I(o, 0x1DC) = 0;
                    }
                    func_L04_0043AD48(&sy, &sy2, I(o, 0x120), I(o, 0x124), o + 0x1C4, o + 0x1C8,
                                      p);
                    func_0028FC48(sy - 2, SC((float)(sy2 - 1)), sy + 2, SC((float)(sy2 + 3)),
                                  0x600040E4, 0);
                }
            }
            i++;
        } while (i < 0x15);
        tmp = func_00283BE0(f21, F(h, 0xF8));
        if (F(p, 0x4A4) == -1.0f)
            F(p, 0x4A4) = tmp;
        else
            func_002AAA00(p + 0x4A4, tmp, 0.002327106f, 0.002327106f, 4.712389f, p + 0x4B0, 0);
        I(p, 0x49C) = 0x183;
        v = I(p, 0x4A0);
        if (v == -1) {
            I(p, 0x4A0) = sy3;
        } else {
            tmp = (float)v;
            func_002AA548(&tmp, p + 0x4AC, (float)sy3, 0.1388889f, 0.1388889f, 5.8333335f);
            I(p, 0x4A0) = (int)tmp;
        }
        vD0.f[0] = 0.0f;
        vD0.f[1] = F(p, 0x4A4);
        vD0.f[2] = 0.0f;
        func_00283410(m, &vD0);
        func_00282D30(m, m, F(obj, 0xC));
        func_00282D30(&m[2], &m[2], F(obj, 0xC));
        func_00300AA8(obj, (float)I(p, 0x49C), (float)SC((float)I(p, 0x4A0)), 0x8000A6E4, 0.0f, m);
        func_L04_0043AD48(&sy, &sy2, I(p, 0x314), I(p, 0x318), pa, pb, p);
        func_0028FC48(sy, SC((float)sy2), sy + 4, SC((float)(sy2 + 4)), 0x8000A6E4, 0);
        func_002FC560(0x47, 0x5360B);
        if (h[0x20] != 3) {
            f12 = F(p, 0x28C) * 0.008726647f;
            F(D_L04_001BDB80, 0xB0) = func_00283198(f12) / func_00283180(f12);
            func_0027AB40();
        }
    }
    return 1;
}
