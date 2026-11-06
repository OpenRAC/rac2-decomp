/* 6 November 2026, round 4: best body below (764/768, 0/5 USA). Own unit
 * src/levels/shared/L01_002F1588.c, -O2 -G0 -ffunction-sections -fno-gcse. The
 * func_00326A10 dead-test rounding helper (`result != 0 && D_L01_001B2DC0[0] == active`,
 * active an int local = 1) with 0x8710 as a local gives retail's ghost $s0, s1 = 0x8710,
 * the 0x70 frame and f20..f24 roles; a `camera` local gives $s2. Left: retail keeps only
 * %hi(D_1BD9C0) in $s2 (daddu, then addiu %lo at the start and at the end), here the full
 * address; that one-word shift is most of the rest. With gcse on, %hi stays in $s2 and
 * the ghost too, but gcse propagates 1.0f/0.0f into the f14..f16 moves (744). A start-only
 * camera local (760), helper only in the three draws (736), single-condition test
 * (752/756) and -frac2-gcse-unsplit-edges (744) are worse.
 */
/* Nonmatching interface overlay reconstruction, 2026-10-28. No C credit.
 * Four US checks, 0/5. Retained 736/768B, frame0x70 exact, with -O2 -G0
 * -ffunction-sections. First diagnostic728B had rectangle-top375 rather
 * than the actual later374; retained code corrects that constant. Explicit
 * coordinate/factor lifetimes and narrow unsplit edges give736B; broad
 * -fno-gcse and one truthful bank-equivalent interleaving are identical.
 * Three forms converge. Canonical actual object/flags/five-FP declaration
 * is retained, with no useless profile option. Remaining: camera high-half
 * lifetime and saved GPR versus extra saved FP, literal250 retention, FP
 * conversion/call scheduling and projection restore order.
 * Reopen with independent original source/lifetime evidence.
 *
 * Actual callback user002F14E8 confirms int(void); each exit returns the
 * GP control word. Actual00336D50 returns signed32 address, explicitly
 * cast; actual00300A00 takes a0 object,a1 flags and f12..f16 five floats,
 * returns void. Actual0028E588 returns int and0028E868 returns void.
 * Actual0027EAE8 forwards its color pointer to actual0027EA28, which reads
 * exactly two32-bit words. Both words are assigned before the full8B struct
 * copy and drawing call; no third color or unstored padding is consumed.
 * Raw-only0027AB40 mutation/return interface remains provisional.
 * Unknown external data extents are incomplete; scalar float-to-int casts
 * naturally reproduce the observed cvt.w.s mechanism without handwritten asm.
 */

#include "common.h"
typedef struct { int first, second; } OverlayColorPair;
extern unsigned char *D_L01_001A908C __attribute__((sda));
extern unsigned char D_L01_0027EAC8[];
extern int D_L01_001A90D0[] SDATA(D_L01_001A90D0);
extern int D_L01_001A90CC[] SDATA(D_L01_001A90CC);
extern float D_L01_001A90C4[] SDATA(D_L01_001A90C4);
extern float D_L01_001B2DC4[] __attribute__((sda));
extern unsigned char D_L01_001BD9C0[];
extern void func_0027AB40(void);
extern int func_00336D50(void *, int);
extern void func_00300A00(void *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027EAE8(int, int, int, int, int, const void *);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);

extern int D_L01_001B2DC0[] __attribute__((sda));

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L01_001B2DC0[0] == active)
        scaled = 1.0f;
    return result;
}

int func_L01_002F1588(void)
{
    OverlayColorPair colors, source;
    float oldProjection, span, rounding, unit, zero, height;
    int top, bottom;
    unsigned char *node;
    int x2, y, one, entry;
    unsigned char *camera;
    if (!D_L01_001A908C || *(int *)D_L01_0027EAC8 || *(int *)(D_L01_0027EAC8 + 0x24) != -1)
        return D_L01_001A90D0[0];
    camera = D_L01_001BD9C0;
    oldProjection = *(float *)(camera + 0xB0);
    *(float *)(camera + 0xB0) = 0.6200000047683716f;
    span = 375.0f;
    func_0027AB40();
    rounding = 0.5f;
    one = 1;
    entry = 0x8710;
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 142);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    unit = 1.0f;
    zero = 0.0f;
    func_00300A00(node, 0x60442D00, 250.0f, (float)y, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 143);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    func_00300A00(node, 0x60241700, 250.0f, (float)y, unit, unit, zero);
    node = (unsigned char *)func_00336D50(D_L01_001A908C + entry, 144);
    y = hud_coord(span, D_L01_001B2DC4[0], rounding, one);
    func_00300A00(node, 0x55F0C070, 250.0f, (float)y, unit, unit, zero);
    source.first = (int)0x800050C0;
    source.second = func_00283D38(0x800050C0, 0x80C04000, D_L01_001A90C4[0]);
    colors = source;
    x2 = func_00283CF0(190.0f + func_00283CE0(198) * D_L01_001A90C4[0]);
    top = hud_coord(374.0f, D_L01_001B2DC4[0], rounding, one);
    bottom = hud_coord(388.0f, D_L01_001B2DC4[0], rounding, one);
    func_0027EAE8(190, top, x2, bottom, 0, &colors);
    if (D_L01_001A90CC[0]) {
        int icon = func_0028E588(0xEAA7, D_L01_001A90CC[0] - 1);
        top = hud_coord(352.0f, D_L01_001B2DC4[0], rounding, one);
        bottom = hud_coord(43.0f, D_L01_001B2DC4[0], rounding, one);
        func_0028E868(icon, 139, top, 43, bottom, 128);
    }
    *(float *)(camera + 0xB0) = oldProjection;
    func_0027AB40();
    return D_L01_001A90D0[0];
}
